/*
	pr_parse.c

	map and savegame parsing

	Copyright (C) 1996-1997  Id Software, Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

	See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to:

		Free Software Foundation, Inc.
		59 Temple Place - Suite 330
		Boston, MA  02111-1307, USA

*/
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef HAVE_STRING_H
# include <string.h>
#endif
#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif
#include <stdarg.h>
#include <stdio.h>

#include "qfalloca.h"

#if defined(_WIN32) && defined(HAVE_MALLOC_H)
#include <malloc.h>
#endif

#include "QF/cbuf.h"
#include "QF/crc.h"
#include "QF/cvar.h"
#include "QF/dstring.h"
#include "QF/hash.h"
#include "QF/mathlib.h"
#include "QF/progs.h"
#include "QF/qdefs.h"
#include "QF/qfplist.h"
#include "QF/qendian.h"
#include "QF/quakefs.h"
#include "QF/script.h"
#include "QF/sys.h"
#include "QF/zone.h"
#include "QF/va.h"

#include "compat.h"

/*
	PR_UglyValueString

	Returns a string describing *data in a type specific manner
	Easier to parse than PR_ValueString
*/
static const char *
PR_UglyValueString (progs_t *pr, etype_t type, pr_type_t *val)
{
	static dstring_t *line = 0;
	ddef_t		*def;
	dfunction_t	*f;

	if (!line)
		line = dstring_new ();

	type &= ~DEF_SAVEGLOBAL;

	switch (type) {
		case ev_string:
			dsprintf (line, "%s", PR_GetString (pr, val->string_var));
			break;
		case ev_entity:
			dsprintf (line, "%d",
					  NUM_FOR_BAD_EDICT (pr, PROG_TO_EDICT (pr, val->entity_var)));
			break;
		case ev_func:
			f = pr->pr_functions + val->func_var;
			dsprintf (line, "%s", PR_GetString (pr, f->s_name));
			break;
		case ev_field:
			def = PR_FieldAtOfs (pr, val->integer_var);
			dsprintf (line, "%s", PR_GetString (pr, def->s_name));
			break;
		case ev_void:
			dstring_copystr (line, "void");
			break;
		case ev_float:
			dsprintf (line, "%.9g", val->float_var);
			break;
		case ev_integer:
			dsprintf (line, "%d", val->integer_var);
			break;
		case ev_vector:
			dsprintf (line, "%.9g %.9g %.9g", VectorExpand (val->vector_var));
			break;
		case ev_quat:
			dsprintf (line, "%.9g %.9g %.9g %.9g", QuatExpand (val->quat_var));
			break;
		default:
			dsprintf (line, "bad type %i", type);
			break;
	}

	return line->str;
}

VISIBLE plitem_t *
ED_EntityDict (progs_t *pr, edict_t *ed)
{
	plitem_t   *entity = PL_NewDictionary ();
	pr_uint_t   i;
	int         j;
	int         type;
	const char *name;
	const char *value;
	pr_type_t  *v;

	if (!ed->free) {
		for (i = 0; i < pr->progs->numfielddefs; i++) {
			ddef_t     *d = &pr->pr_fielddefs[i];

			name = PR_GetString (pr, d->s_name);
			if (!name[0])
				continue;					// skip unnamed fields
			if (name[strlen (name) - 2] == '_')
				continue;					// skip _x, _y, _z vars

			v = &ed->v[d->ofs];

			// if the value is still all 0, skip the field
			type = d->type & ~DEF_SAVEGLOBAL;
			for (j = 0; j < pr_type_size[type]; j++)
				if (v[j].integer_var)
					break;
			if (j == pr_type_size[type])
				continue;

			value = PR_UglyValueString (pr, type, v);
			PL_D_AddObject (entity, name, PL_NewString (value));
		}
	}
	return entity;
}

/*
	ARCHIVING GLOBALS

	FIXME: need to tag constants, doesn't really work
*/

VISIBLE plitem_t *
ED_GlobalsDict (progs_t *pr)
{
	plitem_t   *globals = PL_NewDictionary ();
	pr_uint_t   i;
	const char *name;
	const char *value;
	ddef_t     *def;
	int         type;

	for (i = 0; i < pr->progs->numglobaldefs; i++) {
		def = &pr->pr_globaldefs[i];
		type = def->type;
		if (!(def->type & DEF_SAVEGLOBAL))
			continue;
		type &= ~DEF_SAVEGLOBAL;

		if (type != ev_string && type != ev_float && type != ev_entity)
			continue;

		name = PR_GetString (pr, def->s_name);
		value = PR_UglyValueString (pr, type, &pr->pr_globals[def->ofs]);
		PL_D_AddObject (globals, name, PL_NewString (value));
	}
	return globals;
}


static int
ED_NewString (progs_t *pr, const char *string)
{
	char		*new, *new_p;
	int			i, l;

	l = strlen (string) + 1;
	new = alloca (l);
	new_p = new;

	for (i = 0; i < l; i++) {
		if (string[i] == '\\' && i < l - 1) {
			i++;
			if (string[i] == 'n')
				*new_p++ = '\n';
			else
				*new_p++ = '\\';
		} else
			*new_p++ = string[i];
	}

	return PR_SetString (pr, new);
}


/*
	ED_ParseEval

	Can parse either fields or globals
	returns false if error
*/
VISIBLE qboolean
ED_ParseEpair (progs_t *pr, pr_type_t *base, ddef_t *key, const char *s)
{
	int			i;
	char		*string;
	ddef_t		*def;
	char		*v, *w;
	pr_type_t	*d;
	dfunction_t	*func;

	d = &base[key->ofs];

	switch (key->type & ~DEF_SAVEGLOBAL) {
		case ev_string:
			d->string_var = ED_NewString (pr, s);
			break;

		case ev_float:
			d->float_var = atof (s);
			break;

		case ev_vector:
			string = strdup (s);
			v = string;
			w = string;
			for (i = 0; i < 3; i++) {
				while (*v && *v != ' ')
					v++;
				*v = 0;
				d->vector_var[i] = atof (w);
				w = v = v + 1;
			}
			free (string);
			break;

		case ev_entity:
			d->entity_var = EDICT_TO_PROG (pr, EDICT_NUM (pr, atoi (s)));
			break;

		case ev_field:
			def = PR_FindField (pr, s);
			if (!def) {
				Sys_Printf ("Can't find field %s\n", s);
				return false;
			}
			d->integer_var = G_INT (pr, def->ofs);
			break;

		case ev_func:
			func = PR_FindFunction (pr, s);
			if (!func) {
				Sys_Printf ("Can't find function %s\n", s);
				return false;
			}
			d->func_var = func - pr->pr_functions;
			break;

		default:
			break;
	}
	return true;
}

/*
	ED_ParseOld

	The entities are directly placed in the array, rather than allocated with
	ED_Alloc, because otherwise an error loading the map would have entity
	number references out of order.

	Creates a server's entity / program execution context by
	parsing textual entity definitions out of an ent file.

	Used for both fresh maps and savegame loads.  A fresh map would also need
	to call ED_CallSpawnFunctions () to let the objects initialize themselves.
*/

VISIBLE plitem_t *
ED_ConvertToPlist (progs_t *pr, script_t *script)
{
	plitem_t   *plist = PL_NewArray ();
	plitem_t   *ent;
	plitem_t   *key;
	plitem_t   *value;
	const char *token;
	int         anglehack;

	while (Script_GetToken (script, 1)) {
		token = script->token->str;
		if (!strequal (token, "{"))
			PR_Error (pr, "ED_ParseEntity: EOF without closing brace");
		ent = PL_NewDictionary ();
		while (1) {
			if (!Script_GetToken (script, 1))
				PR_Error (pr, "ED_ParseEntity: EOF without closing brace");
			token = script->token->str;
			if (strequal (token, "}"))
				break;
			anglehack = 0;
			if (strequal (token, "angle")) {
				key = PL_NewString ("angles");
				anglehack = 1;
			} else if (strequal (token, "light")) {
				key = PL_NewString ("light_lev");
			} else {
				key = PL_NewString (token);
			}
			if (!Script_TokenAvailable (script, 0))
				PR_Error (pr, "ED_ParseEntity: EOL without value");
			Script_GetToken (script, 0);
			token = script->token->str;
			if (strequal (token, "}"))
				PR_Error (pr, "ED_ParseEntity: closing brace without data");
			if (anglehack)
				value = PL_NewString (va ("0 %s 0", token));
			else
				value = PL_NewString (token);
			PL_D_AddObject (ent, PL_String (key), value);
			PL_Free (key);
		}
		PL_A_AddObject (plist, ent);
	}
	return plist;
}


VISIBLE void
ED_InitGlobals (progs_t *pr, plitem_t *globals)
{
	ddef_t      vector_def;
	ddef_t     *global;
	plitem_t   *keys;
	int         count;
	const char *global_name;
	const char *value;

	keys = PL_D_AllKeys (globals);
	count = PL_A_NumObjects (keys);
	while (count--) {
		global_name = PL_String (PL_ObjectAtIndex (keys, count));
		value = PL_String (PL_ObjectForKey (globals, global_name));
		global = PR_FindGlobal (pr, global_name);
		//FIXME should this be here?
		//This is a hardcoded fix for a design mistake in the original qcc
		//(saving global vector components rather than the whole vector).
		if (!global) {
			int         len = strlen (global_name);
			const char *tag = global_name + len - 2;
			if (len > 2 && tag[0] == '_' && strchr ("xyz", tag[1])) {
				char       *vector_name = strdup (global_name);
				vector_name[len - 2] = 0;
				global = PR_FindGlobal (pr, vector_name);
				if (global) {
					if ((global->type & ~DEF_SAVEGLOBAL) == ev_vector) {
						vector_def = *global;
						vector_def.ofs += tag[1] - 'x';
						vector_def.type = ev_float;
						global = &vector_def;
					} else {
						global = 0;
					}
				}
			}
		}
		if (!global) {
			Sys_Printf ("'%s' is not a global\n", global_name);
			continue;
		}
		if (!ED_ParseEpair (pr, pr->pr_globals, global, value))
			PR_Error (pr, "ED_InitGlobals: parse error");
	}
	PL_Free (keys);
}

VISIBLE void
ED_InitEntity (progs_t *pr, plitem_t *entity, edict_t *ent)
{
	ddef_t     *field;
	plitem_t   *keys;
	const char *field_name;
	const char *value;
	int         count;
	int         init = 0;

	keys = PL_D_AllKeys (entity);
	count = PL_A_NumObjects (keys);
	while (count--) {
		field_name = PL_String (PL_ObjectAtIndex (keys, count));
		value = PL_String (PL_ObjectForKey (entity, field_name));
		field = PR_FindField (pr, field_name);
		if (!field) {
			if (!pr->parse_field
				|| !pr->parse_field (pr, field_name, value)) {
				Sys_Printf ("'%s' is not a field\n", field_name);
				continue;
			}
		} else {
			if (!ED_ParseEpair (pr, ent->v, field, value))
				PR_Error (pr, "ED_InitEntity: parse error");
		}
		init = 1;
	}
	PL_Free (keys);
	if (!init)
		ent->free = 1;
}

static void
ED_SpawnEntities (progs_t *pr, plitem_t *entity_list)
{
	edict_t    *ent;
	int         inhibit = 0;
	plitem_t   *entity;
	plitem_t   *item;
	int         i;
	int         count;
	const char *classname;
	dfunction_t *func;
	pr_int_t    max_edicts = pr->pr_edictareasize / pr->pr_edict_size;

	max_edicts -= *pr->num_edicts;
	count = PL_A_NumObjects (entity_list);
	for (i = 0; i < count; i++) {
		entity = PL_ObjectAtIndex (entity_list, i);

		item = PL_ObjectForKey (entity, "classname");
		if (!item)
			PR_Error (pr, "no classname for entity %d", i);
		classname = PL_String (item);
		if (strequal (classname, "worldspawn"))
			ent = EDICT_NUM (pr, 0);
		else
			ent = ED_Alloc (pr);

		// don't allow the last edict to be used, as otherwise we can't detect
		// too many edicts
		if (NUM_FOR_EDICT (pr, ent) >= pr->max_edicts - 1)
			PR_Error (pr, "too many entities: %d > %d", count, max_edicts);

		ED_InitEntity (pr, entity, ent);

		// remove things from different skill levels or deathmatch
		if (pr->prune_edict && pr->prune_edict (pr, ent)) {
			ED_Free (pr, ent);
			inhibit++;
			continue;
		}

		//XXX should the field be checked instead of going direct?
		func = PR_FindFunction (pr, classname);
		if (!func) {
			Sys_Printf ("No spawn function for :\n");
			ED_Print (pr, ent);
			ED_Free (pr, ent);
			continue;
		}

		*pr->globals.self = EDICT_TO_PROG (pr, ent);
		PR_ExecuteProgram (pr, func - pr->pr_functions);
		if (pr->flush)
			pr->flush ();
	}
}

VISIBLE plitem_t *
ED_Parse (progs_t *pr, const char *data)
{
	script_t	*script;
	plitem_t    *entity_list = 0;

	script = Script_New ();
	Script_Start (script, "ent data", data);

	if (Script_GetToken (script, 1)) {
		if (strequal (script->token->str, "(")) {
			// new style (plist) entity data
			entity_list = PL_GetPropertyList (data);
		} else {
			// oldstyle entity data
			Script_UngetToken (script);
			entity_list = ED_ConvertToPlist (pr, script);
		}
	}
	Script_Delete (script);
	return entity_list;
}

VISIBLE void
ED_LoadFromFile (progs_t *pr, const char *data)
{
	plitem_t    *entity_list;

	if (pr->edict_parse) {
		PR_PushFrame (pr);
		PR_RESET_PARAMS (pr);
		P_INT (pr, 0) = PR_SetTempString (pr, data);
		PR_ExecuteProgram (pr, pr->edict_parse);
		PR_PopFrame (pr);
		return;
	}
	entity_list = ED_Parse (pr, data);
	if (entity_list) {
		ED_SpawnEntities (pr, entity_list);
		PL_Free (entity_list);
	}
}

VISIBLE void
ED_EntityParseFunction (progs_t *pr)
{
	pr->edict_parse = P_FUNCTION (pr, 0);
}
