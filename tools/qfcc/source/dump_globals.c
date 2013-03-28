/*
	dump_globals.c

	Dump progs globals information.

	Copyright (C) 2002 Bill Currie <bill@taniwha.org>

	Author: Bill Currie <bill@taniwha.org>
	Date: 2002/05/16

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

#include <stdlib.h>
#ifdef HAVE_STRING_H
# include <string.h>
#endif
#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif

#include "QF/dstring.h"
#include "QF/progs.h"
#include "QF/va.h"

#include "obj_file.h"
#include "obj_type.h"
#include "qfprogs.h"
#include "reloc.h"
#include "strpool.h"

static int
cmp (const void *_a, const void *_b)
{
	const ddef_t *a = (const ddef_t *)_a;
	const ddef_t *b = (const ddef_t *)_b;

	return a->ofs - b->ofs;
}

static void
dump_def (progs_t *pr, ddef_t *def, int indent)
{
	const char *name;
	const char *type;
	pr_uint_t   offset;
	const char *comment;
	string_t    string;
	const char *str;
	int         saveglobal;

	if (!def->type && !def->ofs && !def->s_name)
		return;

	name = PR_GetString (pr, def->s_name);
	type = pr_type_name[def->type & ~DEF_SAVEGLOBAL];
	saveglobal = (def->type & DEF_SAVEGLOBAL) != 0;
	offset = def->ofs;

	comment = " invalid offset";

	if (offset < pr->progs->numglobals) {
		comment = "";
		switch (def->type & ~DEF_SAVEGLOBAL) {
			case ev_void:
				break;
			case ev_string:
				string = G_INT (pr, offset);
				if (string < 0 || string >= pr->progs->numstrings) {
					str = "invalid string offset";
					comment = va (" %d %s", string, str);
				} else {
					str = quote_string (pr->pr_strings + G_INT (pr, offset));
					comment = va (" %d \"%s\"", string, str);
				}
				break;
			case ev_float:
				comment = va (" %g", G_FLOAT (pr, offset));
				break;
			case ev_vector:
				comment = va (" '%g %g %g'",
							  G_VECTOR (pr, offset)[0],
							  G_VECTOR (pr, offset)[1],
							  G_VECTOR (pr, offset)[2]);
				break;
			case ev_entity:
				break;
			case ev_field:
				comment = va (" %x", G_INT (pr, offset));
				break;
			case ev_func:
				{
					func_t      func = G_FUNCTION (pr, offset);
					int         start;
					if (func >= 0 && func < pr->progs->numfunctions) {
						start = pr->pr_functions[func].first_statement;
						if (start > 0)
							comment = va (" %d @ %x", func, start);
						else
							comment = va (" %d = #%d", func, -start);
					} else {
						comment = va (" %d = illegal function", func);
					}
				}
				break;
			case ev_pointer:
				comment = va (" %x", G_INT (pr, offset));
				break;
			case ev_quat:
				comment = va (" '%g %g %g %g'",
							  G_QUAT (pr, offset)[0],
							  G_QUAT (pr, offset)[1],
							  G_QUAT (pr, offset)[2],
							  G_QUAT (pr, offset)[3]);
				break;
			case ev_integer:
				comment = va (" %d", G_INT (pr, offset));
				break;
			case ev_short:
				break;
			case ev_invalid:
				comment = " struct?";
				break;
			case ev_type_count:
				break;
		}
	}
	printf ("%*s %x %d %s %s%s\n", indent * 12, "",
			offset, saveglobal, name, type, comment);
}

void
dump_globals (progs_t *pr)
{
	unsigned int i;
	ddef_t     *global_defs = pr->pr_globaldefs;

	if (sorted) {
		global_defs = malloc (pr->progs->numglobaldefs * sizeof (ddef_t));
		memcpy (global_defs, pr->pr_globaldefs,
				pr->progs->numglobaldefs * sizeof (ddef_t));
		qsort (global_defs, pr->progs->numglobaldefs, sizeof (ddef_t), cmp);
	}
	for (i = 0; i < pr->progs->numglobaldefs; i++) {
		ddef_t *def = &global_defs[i];
		dump_def (pr, def, 0);
	}
}

void
dump_fields (progs_t *pr)
{
	unsigned int i;
	const char *name;
	const char *type;
	int         offset;
	const char *comment;

	for (i = 0; i < pr->progs->numfielddefs; i++) {
		ddef_t *def = &pr->pr_fielddefs[i];

		name = PR_GetString (pr, def->s_name);
		type = pr_type_name[def->type & ~DEF_SAVEGLOBAL];
		offset = def->ofs;

		comment = "";

		printf ("%d %s %s%s\n", offset, name, type, comment);
	}
}

void
dump_functions (progs_t *pr)
{
	int         i, j;
	const char *name;
	int         start, count;
	const char *comment;

	for (i = 0; i < pr->progs->numfunctions; i++) {
		dfunction_t *func = &pr->pr_functions[i];

		name = PR_GetString (pr, func->s_name);

		comment = "";

		start = func->first_statement;
		if (start > 0)
			comment = va (" @ %x", start);
		else
			comment = va (" = #%d", -start);

		printf ("%-5d %s%s: %d (", i, name, comment, func->numparms);
		if (func->numparms < 0)
			count = -func->numparms - 1;
		else
			count = func->numparms;
		for (j = 0; j < count; j++)
			printf (" %d", func->parm_size[j]);
		printf (") %d @ %x", func->locals, func->parm_start);
		puts ("");
		if (pr->debug) {
			pr_auxfunction_t *aux = pr->auxfunction_map[i];
			if (!aux)
				continue;
			printf ("        %d %s:%d %d %d %d %x\n", aux->function,
					PR_GetString (pr, func->s_file), aux->source_line,
					aux->line_info,
					aux->local_defs, aux->num_locals,
					aux->return_type);
			for (j = 0; j < (int)aux->num_locals; j++)
				dump_def (pr, pr->local_defs + aux->local_defs + j, 1);
		}
	}
}

static const char *
flags_string (pr_uint_t flags)
{
	static dstring_t *str;
	if (!str)
		str = dstring_newstr ();
	dstring_clearstr (str);
	dstring_appendstr (str, (flags & QFOD_INITIALIZED) ? "I" : "-");
	dstring_appendstr (str, (flags & QFOD_CONSTANT)    ? "C" : "-");
	dstring_appendstr (str, (flags & QFOD_ABSOLUTE)    ? "A" : "-");
	dstring_appendstr (str, (flags & QFOD_GLOBAL)      ? "G" : "-");
	dstring_appendstr (str, (flags & QFOD_EXTERNAL)    ? "E" : "-");
	dstring_appendstr (str, (flags & QFOD_LOCAL)       ? "L" : "-");
	dstring_appendstr (str, (flags & QFOD_SYSTEM)      ? "S" : "-");
	dstring_appendstr (str, (flags & QFOD_NOSAVE)      ? "N" : "-");
	dstring_appendstr (str, (flags & QFOD_PARAM)       ? "P" : "-");
	return str->str;
}

void
qfo_globals (qfo_t *qfo)
{
	qfo_def_t  *def;
	int         i;
	int         space;
	int         count = 0;

	for (space = 0; space < qfo->num_spaces; space++) {
		for (i = 0; i < qfo->spaces[space].num_defs; i++, count++) {
			def = &qfo->spaces[space].defs[i];
			printf ("%-5d %2d:%-5x %s %s %s", count, space, def->offset,
					flags_string (def->flags),
					QFO_GETSTR (qfo, def->name),
					QFO_TYPESTR (qfo, def->type));
			if (!(def->flags & QFOD_EXTERNAL) && qfo->spaces[space].d.data)
				printf (" %d",
						qfo->spaces[space].d.data[def->offset].integer_var);
			puts ("");
		}
	}
}

void
qfo_relocs (qfo_t *qfo)
{
	qfo_reloc_t  *reloc;
	qfo_def_t    *def;
	qfo_func_t   *func;
	int           i;

	for (i = 0; i < qfo->num_relocs; i++) {
		reloc = qfo->relocs + i;
		if ((unsigned) reloc->type > rel_def_field_ofs) {
			printf ("%d unknown reloc: %d\n", i, reloc->type);
			continue;
		}
		printf ("%s", reloc_names[reloc->type]);
		def = 0;
		func = 0;
		switch ((reloc_type) reloc->type) {
			case rel_none:
				break;
			case rel_op_a_def:
			case rel_op_b_def:
			case rel_op_c_def:
				def = qfo->defs + reloc->target;
				printf (" op.%c@%x def#%d %s",
						reloc->type - rel_op_a_def + 'a',
						reloc->offset, reloc->target,
						QFO_GETSTR (qfo, def->name));
				break;
			case rel_op_a_op:
			case rel_op_b_op:
			case rel_op_c_op:
				printf (" op.%c op@%x", reloc->type - rel_op_a_def + 'a',
						reloc->offset);
				break;
			case rel_def_op:
				printf (" def@%d:%x op@%d", reloc->space, reloc->offset,
						reloc->target);
				break;
			case rel_def_def:
				def = qfo->defs + reloc->target;
				printf (" def@%d:%x def#%d %s", reloc->space, reloc->offset,
						reloc->target, QFO_GETSTR (qfo, def->name));
				break;
			case rel_def_func:
				func = qfo->funcs + reloc->target;
				//func = qfo->funcs + QFO_FUNCTION (qfo, reloc->space,
				//								  reloc->offset);
				printf (" def@%d:%x func#%d %s %x",
						reloc->space, reloc->offset,
						QFO_FUNCTION (qfo, reloc->space, reloc->offset),
						QFO_GETSTR (qfo, func->name),
						reloc->target);
				break;
			case rel_def_string:
				printf (" def@%d:%x string:%x `%s'",
						reloc->space, reloc->offset, reloc->target,
						quote_string (QFO_GETSTR (qfo, reloc->target)));
				break;
			case rel_def_field:
				def = qfo->defs + reloc->target;
				printf (" def@%d:%x def#%d %s", reloc->space, reloc->offset,
						reloc->target, QFO_GETSTR (qfo, def->name));
				break;
			case rel_op_a_def_ofs:
			case rel_op_b_def_ofs:
			case rel_op_c_def_ofs:
				def = qfo->defs + reloc->target;
				printf (" op.%c@%x def#%d %s",
						reloc->type - rel_op_a_def_ofs + 'a',
						reloc->offset, reloc->target,
						QFO_GETSTR (qfo, def->name));
				break;
			case rel_def_def_ofs:
				def = qfo->defs + reloc->target;
				printf (" def@%d:%x def#%d+%d %s+%d",
						reloc->space, reloc->offset, reloc->target,
						QFO_INT (qfo, reloc->space, reloc->offset),
						QFO_GETSTR (qfo, def->name),
						QFO_INT (qfo, reloc->space, reloc->offset));
				break;
			case rel_def_field_ofs:
				def = qfo->defs + reloc->target;
				printf (" def@%d:%x def#%d+%d %s(%d)+%d",
						reloc->space, reloc->offset, reloc->target,
						QFO_INT (qfo, reloc->space, reloc->offset),
						QFO_GETSTR (qfo, def->name), def->offset,
						QFO_INT (qfo, reloc->space, reloc->offset));
				break;
		}
		if (def && def->flags & QFOD_EXTERNAL)
			printf (" external");
		if (func && qfo->defs[func->def].flags & QFOD_EXTERNAL)
			printf (" external");
		if (def && (i < def->relocs || i >= def->relocs + def->num_relocs))
			printf (" BOGUS def reloc! %d %d %d",
					i, def->relocs, def->num_relocs);
		if (func && (i < func->relocs || i >= func->relocs + func->num_relocs))
			printf (" BOGUS func reloc! %d %d %d",
					i, func->relocs, func->num_relocs);
		puts ("");
	}
}

void
qfo_functions (qfo_t *qfo)
{
	qfo_def_t  *def;
	qfo_func_t *func;
	int         i, d;
	int         space;

	for (i = 0; i < qfo->num_funcs; i++) {
		func = &qfo->funcs[i];
		def = &qfo->defs[func->def];
		for (space = 0; space < qfo->num_spaces; space++) {
			if (!qfo->spaces[space].num_defs)
				continue;
			d = qfo->spaces[space].defs - qfo->defs;
			if (func->def >= d && func->def < d + qfo->spaces[space].num_defs)
				break;
		}
		if (space == qfo->num_spaces)
			space = qfo_near_data_space;
		printf ("%-5d %-5d %s %s %d %s", i, def->offset,
				flags_string (def->flags),
				QFO_GETSTR (qfo, func->name), func->def,
				QFO_GETSTR (qfo, def->name));
		if (!(def->flags & QFOD_EXTERNAL))
			printf (" %d", QFO_FUNCTION (qfo, space, def->offset));
		if (func->code > 0)
			printf (" @ %x", func->code);
		else
			printf (" = #%d", -func->code);
		puts ("");
	}
}

static const char *ty_meta_names[] = {
	"ty_none",
	"ty_struct",
	"ty_union",
	"ty_enum",
	"ty_array",
	"ty_class",
};
#define NUM_META ((int)(sizeof (ty_meta_names) / sizeof (ty_meta_names[0])))

static void
dump_qfo_types (qfo_t *qfo, int base_address)
{
	pointer_t   type_ptr;
	qfot_type_t *type;
	const char *meta;
	int         i, count;

	for (type_ptr = 4; type_ptr < qfo->spaces[qfo_type_space].data_size;
		 type_ptr += type->size) {
		type = &QFO_STRUCT (qfo, qfo_type_space, qfot_type_t, type_ptr);
		if (qfo->spaces[qfo_type_space].data_size - type_ptr < 2) {
			printf ("%-5x overflow, can't check size. %x\n",
					type_ptr + base_address,
					qfo->spaces[qfo_type_space].data_size);
		}
		if (type_ptr + type->size > qfo->spaces[qfo_type_space].data_size) {
			printf ("%-5x overflow by %d words. %x\n", type_ptr + base_address,
					(type_ptr + type->size
					 - qfo->spaces[qfo_type_space].data_size),
					qfo->spaces[qfo_type_space].data_size);
			continue;
		}
		if (type->ty < 0 || type->ty >= NUM_META)
			meta = va ("invalid meta: %d", type->ty);
		else
			meta = ty_meta_names[type->ty];
		printf ("%-5x %-9s %-20s", type_ptr + base_address, meta,
				QFO_TYPESTR (qfo, type_ptr));
		if (type->ty < 0 || type->ty >= NUM_META) {
			puts ("");
			break;
		}
		switch ((ty_meta_e) type->ty) {
			case ty_none:
				printf (" %-10s", (type->t.type < 0
								   || type->t.type >= ev_type_count)
								  ? "invalid type"
								  : pr_type_name[type->t.type]);
				if (type->t.type == ev_func) {
					printf (" %4x %d", type->t.func.return_type,
							count = type->t.func.num_params);
					if (count < 0)
						count = ~count;	//ones complement
					for (i = 0; i < count; i++)
						printf (" %x", type->t.func.param_types[i]);
				} else if (type->t.type == ev_pointer
						   || type->t.type == ev_field) {
					printf (" %4x", type->t.fldptr.aux_type);
				}
				printf ("\n");
				break;
			case ty_struct:
			case ty_union:
			case ty_enum:
				printf (" %s\n", QFO_GETSTR (qfo, type->t.strct.tag));
				for (i = 0; i < type->t.strct.num_fields; i++) {
					printf ("        %-5x %4x %s\n",
							type->t.strct.fields[i].type,
							type->t.strct.fields[i].offset,
							QFO_GETSTR (qfo, type->t.strct.fields[i].name));
				}
				break;
			case ty_array:
				printf (" %-5x %d %d\n", type->t.array.type,
						type->t.array.base, type->t.array.size);
				break;
			case ty_class:
				printf (" %-5x\n", type->t.class);
				break;
		}
	}
}

void
qfo_types (qfo_t *qfo)
{
	dump_qfo_types (qfo, 0);
}

void
dump_types (progs_t *pr)
{
	qfo_mspace_t spaces[qfo_num_spaces];
	qfo_t       qfo;
	ddef_t     *encodings_def;
	qfot_type_encodings_t *encodings;

	encodings_def = PR_FindGlobal (pr, ".type_encodings");
	if (!encodings_def) {
		printf ("no type encodings found");
		return;
	}
	if (encodings_def->ofs > pr->globals_size - 2) {
		printf ("invalid .type_encodings address");
		return;
	}
	encodings = &G_STRUCT (pr, qfot_type_encodings_t, encodings_def->ofs);
	if (encodings->types > pr->globals_size) {
		printf ("invalid encodings block start");
		return;
	}
	if (encodings->types + encodings->size > pr->globals_size) {
		printf ("truncating encodings block size");
		encodings->size = pr->globals_size - encodings->types;
	}
	memset (spaces, 0, sizeof (spaces));
	spaces[qfo_strings_space].type = qfos_string;
	spaces[qfo_strings_space].d.strings = pr->pr_strings;
	spaces[qfo_strings_space].data_size = pr->pr_stringsize;
	spaces[qfo_type_space].type = qfos_type;
	spaces[qfo_type_space].d.data = pr->pr_globals + encodings->types;
	spaces[qfo_type_space].data_size = encodings->size;
	memset (&qfo, 0, sizeof (qfo));
	qfo.spaces = spaces;
	qfo.num_spaces = qfo_num_spaces;
	dump_qfo_types (&qfo, encodings->types);
}
