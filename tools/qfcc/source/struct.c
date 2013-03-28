/*
	struct.c

	structure support

	Copyright (C) 2001 Bill Currie <bill@taniwha.org>
	Copyright (C) 2011 Bill Currie <bill@taniwha.org>

	Author: Bill Currie <bill@taniwha.org>
	Date: 2001/12/08
	Date: 2011/01/17

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
#include <stdlib.h>

#include <QF/dstring.h>
#include <QF/hash.h>
#include <QF/pr_obj.h>
#include <QF/sys.h>
#include <QF/va.h>

#include "def.h"
#include "defspace.h"
#include "diagnostic.h"
#include "emit.h"
#include "expr.h"
#include "obj_type.h"
#include "qfcc.h"
#include "reloc.h"
#include "shared.h"
#include "strpool.h"
#include "struct.h"
#include "symtab.h"
#include "type.h"
#include "value.h"

static symbol_t *
find_tag (ty_meta_e meta, symbol_t *tag, type_t *type)
{
	const char *tag_name;
	symbol_t   *sym;

	if (tag) {
		tag_name = va ("tag %s", tag->name);
	} else {
		const char *path = GETSTR (pr.source_file);
		const char *file = strrchr (path, '/');
		if (!file++)
			file = path;
		tag_name = va ("tag .%s.%d", file, pr.source_line);
	}
	sym = symtab_lookup (current_symtab, tag_name);
	if (sym) {
		if (sym->table == current_symtab && sym->type->meta != meta)
			error (0, "%s defined as wrong kind of tag", tag->name);
		if (sym->type->meta == meta)
			return sym;
	}
	sym = new_symbol (tag_name);
	if (!type)
		type = new_type ();
	if (!type->name)
		type->name = sym->name;
	sym->type = type;
	sym->type->type = ev_invalid;
	sym->type->meta = meta;
	sym->sy_type = sy_type;
	return sym;
}

symbol_t *
find_struct (int su, symbol_t *tag, type_t *type)
{
	ty_meta_e   meta = ty_struct;

	if (su == 'u')
		meta = ty_union;

	return find_tag (meta, tag, type);
}

symbol_t *
build_struct (int su, symbol_t *tag, symtab_t *symtab, type_t *type)
{
	symbol_t   *sym = find_struct (su, tag, type);
	symbol_t   *s;

	symtab->parent = 0;		// disconnect struct's symtab from parent scope

	if (sym->table == current_symtab && sym->type->t.symtab) {
		error (0, "%s defined as wrong kind of tag", tag->name);
		return sym;
	}
	for (s = symtab->symbols; s; s = s->next) {
		if (s->sy_type != sy_var)
			continue;
		if (su == 's') {
			s->s.offset = symtab->size;
			symtab->size += type_size (s->type);
		} else {
			int         size = type_size (s->type);
			if (size > symtab->size)
				symtab->size = size;
		}
	}
	if (!type)
		sym->type = find_type (sym->type);	// checks the tag, not the symtab
	sym->type->t.symtab = symtab;
	if (!type && sym->type->type_def->external)	//FIXME should not be necessary
		sym->type->type_def = qfo_encode_type (sym->type);
	return sym;
}

symbol_t *
find_enum (symbol_t *tag)
{
	return find_tag (ty_enum, tag, 0);
}

symtab_t *
start_enum (symbol_t *sym)
{
	if (sym->table == current_symtab && sym->type->t.symtab) {
		error (0, "%s defined as wrong kind of tag", sym->name);
		sym = find_enum (0);
	}
	sym->type->t.symtab = new_symtab (current_symtab, stab_local);
	return sym->type->t.symtab;
}

symbol_t *
finish_enum (symbol_t *sym)
{
	sym->type = find_type (sym->type);
	return sym;
}

void
add_enum (symbol_t *enm, symbol_t *name, expr_t *val)
{
	symbol_t   *sym;
	type_t     *enum_type = enm->type;
	symtab_t   *enum_tab;
	int         value;

	if (name->table == current_symtab)
		error (0, "%s redefined", name->name);
	if (name->table)
		name = new_symbol (name->name);
	name->sy_type = sy_const;
	name->type = enum_type;
	enum_tab = enum_type->t.symtab;
	value = 0;
	if (enum_tab->symbols)
		value = ((symbol_t *)(enum_tab->symtail))->s.value->v.integer_val + 1;
	if (val) {
		if (!is_constant (val))
			error (val, "non-constant initializer");
		else if (!is_integer_val (val))
			error (val, "invalid initializer type");
		else
			value = expr_integer (val);
	}
	name->s.value = new_integer_val (value);
	symtab_addsymbol (enum_tab, name);
	sym = new_symbol_type (name->name, name->type);
	sym->sy_type = sy_const;
	sym->s.value = name->s.value;
	symtab_addsymbol (enum_tab->parent, sym);
}

int
enum_as_bool (type_t *enm, expr_t **zero, expr_t **one)
{
	symtab_t   *symtab = enm->t.symtab;
	symbol_t   *zero_sym = 0;
	symbol_t   *one_sym = 0;
	symbol_t   *sym;
	int         val, v;

	if (!symtab)
		return 0;
	for (sym = symtab->symbols; sym; sym = sym->next) {
		if (sym->sy_type != sy_const)
			continue;
		val = sym->s.value->v.integer_val;
		if (!val) {
			zero_sym = sym;
		} else {
			if (one_sym) {
				v = one_sym->s.value->v.integer_val;
				if (val * val > v * v)
					continue;
			}
			one_sym = sym;
		}

	}
	if (!zero_sym || !one_sym)
		return 0;
	*zero = new_symbol_expr (zero_sym);
	*one = new_symbol_expr (one_sym);
	return 1;
}

symbol_t *
make_structure (const char *name, int su, struct_def_t *defs, type_t *type)
{
	symtab_t   *strct;
	symbol_t   *field;
	symbol_t   *sym = 0;

	if (name)
		sym = new_symbol (name);
	if (su == 'u')
		strct = new_symtab (0, stab_union);
	else
		strct = new_symtab (0, stab_struct);
	while (defs->name) {
		field = new_symbol_type (defs->name, defs->type);
		if (!symtab_addsymbol (strct, field))
			internal_error (0, "duplicate symbol: %s", defs->name);
		defs++;
	}
	sym = build_struct (su, sym, strct, type);
	return sym;
}

def_t *
emit_structure (const char *name, int su, struct_def_t *defs, type_t *type,
				void *data, storage_class_t storage)
{
	int         i, j;
	int         saw_null = 0;
	int         saw_func = 0;
	symbol_t   *struct_sym;
	symbol_t   *field_sym;
	def_t      *struct_def;
	def_t       field_def;

	name = save_string (name);
	if (!type)
		type = make_structure (0, su, defs, 0)->type;
	if (!is_struct (type) || (su == 's' && type->meta != ty_struct)
		|| (su == 'u' && type->meta != ty_union))
		internal_error (0, "structure %s type mismatch", name);
	for (i = 0, field_sym = type->t.symtab->symbols; field_sym;
		 i++, field_sym = field_sym->next) {
		if (!defs[i].name)
			internal_error (0, "structure %s unexpected end of defs", name);
		if (field_sym->type != defs[i].type)
			internal_error (0, "structure %s.%s field type mismatch", name,
							defs[i].name);
		if ((!defs[i].emit && saw_func) || (defs[i].emit && saw_null))
			internal_error (0, "structure %s mixed emit/copy", name);
		if (!defs[i].emit)
			saw_null = 1;
		if (defs[i].emit)
			saw_func = 1;
	}
	if (defs[i].name)
		internal_error (0, "structure %s too many defs", name);
	if (storage != sc_global && storage != sc_static)
		internal_error (0, "structure %s must be global or static", name);

	struct_sym = make_symbol (name, type, pr.far_data, storage);

	struct_def = struct_sym->s.def;
	if (struct_def->initialized)
		internal_error (0, "structure %s already initialized", name);
	struct_def->initialized = struct_def->constant = 1;
	struct_def->nosave = 1;

	for (i = 0, field_sym = type->t.symtab->symbols; field_sym;
		 i++, field_sym = field_sym->next) {
		field_def.type = field_sym->type;
		field_def.name = save_string (va ("%s.%s", name, field_sym->name));
		field_def.space = struct_def->space;
		field_def.offset = struct_def->offset + field_sym->s.offset;
		if (!defs[i].emit) {
			//FIXME relocs? arrays? structs?
			pr_type_t  *val = (pr_type_t *) data;
			memcpy (D_POINTER (void, &field_def), val,
					type_size (field_def.type) * sizeof (pr_type_t));
			data = &val[type_size (field_def.type)];
		} else {
			if (is_array (field_def.type)) {
				type_t     *type = field_def.type->t.array.type;
				for (j = 0; j < field_def.type->t.array.size; j++) {
					defs[i].emit (&field_def, data, j);
					field_def.offset += type_size (type);
				}
			} else {
				defs[i].emit (&field_def, data, 0);
			}
		}
	}
	return struct_def;
}
