/*
	type.c

	type system

	Copyright (C) 2001 Bill Currie <bill@taniwha.org>

	Author: Bill Currie <bill@taniwha.org>
	Date: 2001/12/11

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
#include <ctype.h>
#include <ctype.h>

#include "QF/alloc.h"
#include "QF/dstring.h"
#include "QF/hash.h"
#include "QF/sys.h"
#include "QF/va.h"

#include "class.h"
#include "def.h"
#include "diagnostic.h"
#include "expr.h"
#include "function.h"
#include "obj_type.h"
#include "options.h"
#include "qfcc.h"
#include "strpool.h"
#include "struct.h"
#include "symtab.h"
#include "type.h"

// simple types.  function types are dynamically allocated
type_t      type_invalid = { ev_invalid, "invalid" };
type_t      type_void = { ev_void, "void" };
type_t      type_string = { ev_string, "string" };
type_t      type_float = { ev_float, "float" };
type_t      type_vector = { ev_vector, "vector" };
type_t      type_entity = { ev_entity, "entity" };
type_t      type_field = {ev_field, "field", ty_none, {{&type_void}} };

// type_function is a void() function used for state defs
type_t      type_function = { ev_func, "function", ty_none, {{&type_void}} };
type_t      type_pointer = { ev_pointer, "pointer", ty_none, {{&type_void}} };
type_t      type_quaternion = { ev_quat, "quaternion" };
type_t      type_integer = { ev_integer, "integer" };
type_t      type_uinteger = { ev_uinteger, "uinteger" };
type_t      type_short = { ev_short, "short" };

type_t     *type_nil;
type_t     *type_default;

// these will be built up further
type_t      type_va_list = { ev_invalid, 0, ty_struct };
type_t      type_param = { ev_invalid, 0, ty_struct };
type_t      type_zero = { ev_invalid, 0, ty_struct };
type_t      type_type_encodings = { ev_invalid, "@type_encodings", ty_struct };

type_t      type_floatfield = { ev_field, ".float", ty_none, {{&type_float}} };

static type_t *free_types;

etype_t
low_level_type (type_t *type)
{
	if (type->type >= ev_type_count)
		internal_error (0, "invalid type");
	if (type->type == ev_type_count)
		internal_error (0, "found 'type count' type");
	if (type->type < ev_invalid)
		return type->type;
	if (is_enum (type))
		return type_default->type;
	if (is_struct (type)) {
		//FIXME does this break anything?
		//maybe the peephole optimizer should do this sort of thing.
		if (type_size (type) == 1)
			return ev_integer;
		return ev_void;
	}
	if (is_array (type))
		return ev_void;
	internal_error (0, "invalid complex type");
}

const char *
type_get_encoding (const type_t *type)
{
	static dstring_t *encoding;

	if (!encoding)
		encoding = dstring_newstr();
	else
		dstring_clearstr (encoding);
	encode_type (encoding, type);
	return save_string (encoding->str);
}

void
chain_type (type_t *type)
{
	if (type->next)
		internal_error (0, "type already chained");
	type->next = pr.types;
	pr.types = type;
	if (!type->encoding)
		type->encoding = type_get_encoding (type);
	if (!type->type_def)
		type->type_def = qfo_encode_type (type);
}

type_t *
new_type (void)
{
	type_t     *type;
	ALLOC (1024, type_t, types, type);
	type->freeable = 1;
	type->allocated = 1;
	return type;
}

void
free_type (type_t *type)
{
	if (!type)
		return;
	if (!type->allocated)		// for statically allocated types
		type->next = 0;
	if (!type->freeable)
		return;
	switch (type->type) {
		case ev_void:
		case ev_string:
		case ev_float:
		case ev_vector:
		case ev_entity:
		case ev_type_count:
		case ev_quat:
		case ev_integer:
		case ev_uinteger:
		case ev_short:
			break;
		case ev_field:
		case ev_pointer:
			free_type (type->t.fldptr.type);
			break;
		case ev_func:
			free_type (type->t.func.type);
			break;
		case ev_invalid:
			if (type->meta == ty_array)
				free_type (type->t.array.type);
			break;
	}
	memset (type, 0, sizeof (type));
	FREE (types, type);
}

type_t *
append_type (type_t *type, type_t *new)
{
	type_t    **t = &type;

	while (*t) {
		switch ((*t)->type) {
			case ev_void:
			case ev_string:
			case ev_float:
			case ev_vector:
			case ev_entity:
			case ev_type_count:
			case ev_quat:
			case ev_integer:
			case ev_uinteger:
			case ev_short:
				internal_error (0, "append to basic type");
			case ev_field:
			case ev_pointer:
				t = &(*t)->t.fldptr.type;
				break;
			case ev_func:
				t = &(*t)->t.func.type;
				break;
			case ev_invalid:
				if ((*t)->meta == ty_array)
					t = &(*t)->t.array.type;
				else
					internal_error (0, "append to object type");
				break;
		}
	}
	*t = new;
	return type;
}

static int
types_same (type_t *a, type_t *b)
{
	int         i, count;

	if (a->type != b->type || a->meta != b->meta)
		return 0;
	switch (a->meta) {
		case ty_none:
			switch (a->type) {
				case ev_field:
				case ev_pointer:
					if (a->t.fldptr.type != b->t.fldptr.type)
						return 0;
				case ev_func:
					if (a->t.func.type != b->t.func.type
						|| a->t.func.num_params != b->t.func.num_params)
						return 0;
					count = a->t.func.num_params;
					if (count < 0)
						count = ~count;	// param count is one's complement
					for (i = 0; i < count; i++)
						if (a->t.func.param_types[i]
							!= b->t.func.param_types[i])
							return 0;
					return 1;
				default:		// other types don't have aux data
					return 1;
			}
			break;
		case ty_struct:
		case ty_union:
		case ty_enum:
			if (strcmp (a->name, b->name))
				return 0;
			if (a->meta == ty_struct)
				return compare_protocols (a->protos, b->protos);
			return 1;
		case ty_array:
			if (a->t.array.type != b->t.array.type
				|| a->t.array.base != b->t.array.base
				|| a->t.array.size != b->t.array.size)
				return 0;
			return 1;
		case ty_class:
			if (a->t.class != b->t.class)
				return 0;
			return compare_protocols (a->protos, b->protos);
	}
	internal_error (0, "we be broke");
}

/*
	find_type

	Returns a preexisting complex type that matches the parm, or allocates
	a new one and copies it out.
*/
type_t *
find_type (type_t *type)
{
	type_t     *check;
	int         i, count;

	if (!type)
		return 0;

	if (type->freeable) {
		switch (type->meta) {
			case ty_none:
				switch (type->type) {
					case ev_field:
					case ev_pointer:
						type->t.fldptr.type = find_type (type->t.fldptr.type);
						break;
					case ev_func:
						type->t.func.type = find_type (type->t.func.type);
						count = type->t.func.num_params;
						if (count < 0)
							count = ~count;	// param count is one's complement
						for (i = 0; i < count; i++)
							type->t.func.param_types[i]
								= find_type (type->t.func.param_types[i]);
						break;
					default:		// other types don't have aux data
						break;
				}
				break;
			case ty_struct:
			case ty_union:
			case ty_enum:
				break;
			case ty_array:
				type->t.array.type = find_type (type->t.array.type);
				break;
			case ty_class:
				break;
		}
	}

	for (check = pr.types; check; check = check->next) {
		if (types_same (check, type))
			return check;
	}

	// allocate a new one
	check = new_type ();
	*check = *type;
	check->freeable = 0;

	chain_type (check);

	return check;
}

type_t *
field_type (type_t *aux)
{
	type_t      _new;
	type_t     *new = &_new;

	if (aux)
		memset (&_new, 0, sizeof (_new));
	else
		new = new_type ();
	new->type = ev_field;
	new->t.fldptr.type = aux;
	if (aux)
		new = find_type (new);
	return new;
}

type_t *
pointer_type (type_t *aux)
{
	type_t      _new;
	type_t     *new = &_new;

	if (aux)
		memset (&_new, 0, sizeof (_new));
	else
		new = new_type ();
	new->type = ev_pointer;
	new->t.fldptr.type = aux;
	if (aux)
		new = find_type (new);
	return new;
}

type_t *
array_type (type_t *aux, int size)
{
	type_t      _new;
	type_t     *new = &_new;

	if (aux)
		memset (&_new, 0, sizeof (_new));
	else
		new = new_type ();
	new->type = ev_invalid;
	new->meta = ty_array;
	new->t.array.type = aux;
	new->t.array.size = size;
	if (aux)
		new = find_type (new);
	return new;
}

type_t *
based_array_type (type_t *aux, int base, int top)
{
	type_t      _new;
	type_t     *new = &_new;

	if (aux)
		memset (&_new, 0, sizeof (_new));
	else
		new = new_type ();
	new->type = ev_invalid;
	new->meta = ty_array;
	new->t.array.type = aux;
	new->t.array.base = base;
	new->t.array.size = top - base + 1;
	if (aux)
		new = find_type (new);
	return new;
}

void
print_type_str (dstring_t *str, const type_t *type)
{
	if (!type) {
		dasprintf (str, " (null)");
		return;
	}
	switch (type->type) {
		case ev_field:
			dasprintf (str, ".(");
			print_type_str (str, type->t.fldptr.type);
			dasprintf (str, ")");
			break;
		case ev_func:
			print_type_str (str, type->t.func.type);
			if (type->t.func.num_params == -1) {
				dasprintf (str, "(...)");
			} else {
				int         c, i;
				dasprintf (str, "(");
				if ((c = type->t.func.num_params) < 0)
					c = ~c;		// num_params is one's compliment
				for (i = 0; i < c; i++) {
					if (i)
						dasprintf (str, ", ");
					print_type_str (str, type->t.func.param_types[i]);
				}
				if (type->t.func.num_params < 0)
						dasprintf (str, ", ...");
				dasprintf (str, ")");
			}
			break;
		case ev_pointer:
			if (obj_is_id (type)) {
				dasprintf (str, "id");
				if (type->t.fldptr.type->protos)
					print_protocollist (str, type->t.fldptr.type->protos);
				break;
			}
			if (type == &type_SEL) {
				dasprintf (str, "SEL");
				break;
			}
			dasprintf (str, "(*");
			print_type_str (str, type->t.fldptr.type);
			dasprintf (str, ")");
			break;
		case ev_invalid:
			switch (type->meta) {
				case ty_class:
					dasprintf (str, " %s", type->t.class->name);
					if (type->protos)
						print_protocollist (str, type->protos);
					break;
				case ty_enum:
					dasprintf (str, " enum %s", type->name);
					break;
				case ty_struct:
					dasprintf (str, " struct %s", type->name);
					break;
				case ty_union:
					dasprintf (str, " union %s", type->name);
					break;
				case ty_array:
					print_type_str (str, type->t.array.type);
					if (type->t.array.base) {
						dasprintf (str, "[%d..%d]", type->t.array.base,
								type->t.array.base + type->t.array.size - 1);
					} else {
						dasprintf (str, "[%d]", type->t.array.size);
					}
					break;
				case ty_none:
					break;
			}
			break;
		default:
			dasprintf (str, " %s", pr_type_name[type->type]);
			break;
	}
}

void
print_type (const type_t *type)
{
	dstring_t  *str = dstring_newstr ();
	print_type_str (str, type);
	printf ("%s\n", str->str);
	dstring_delete (str);
}

const char *
encode_params (const type_t *type)
{
	const char *ret;
	dstring_t  *encoding = dstring_newstr ();
	int         i, count;

	if (type->t.func.num_params < 0)
		count = -type->t.func.num_params - 1;
	else
		count = type->t.func.num_params;
	for (i = 0; i < count; i++)
		encode_type (encoding, type->t.func.param_types[i]);
	if (type->t.func.num_params < 0)
		dasprintf (encoding, ".");

	ret = save_string (encoding->str);
	dstring_delete (encoding);
	return ret;
}

static void
encode_class (dstring_t *encoding, const type_t *type)
{
	class_t    *class = type->t.class;
	const char *name ="?";

	if (class->name)
		name = class->name;
	dasprintf (encoding, "{%s@}", name);
}

static void
encode_struct (dstring_t *encoding, const type_t *type)
{
	const char *name ="?";
	char        su = ' ';

	if (type->name)
		name = type->name;
	if (type->meta == ty_union)
		su = '-';
	else
		su = '=';
	dasprintf (encoding, "{%s%c}", name, su);
}

static void
encode_enum (dstring_t *encoding, const type_t *type)
{
	const char *name ="?";

	if (type->name)
		name = type->name;
	dasprintf (encoding, "{%s#}", name);
}

void
encode_type (dstring_t *encoding, const type_t *type)
{
	if (!type)
		return;
	switch (type->type) {
		case ev_void:
			dasprintf (encoding, "v");
			break;
		case ev_string:
			dasprintf (encoding, "*");
			break;
		case ev_float:
			dasprintf (encoding, "f");
			break;
		case ev_vector:
			dasprintf (encoding, "V");
			break;
		case ev_entity:
			dasprintf (encoding, "E");
			break;
		case ev_field:
			dasprintf (encoding, "F");
			encode_type (encoding, type->t.fldptr.type);
			break;
		case ev_func:
			dasprintf (encoding, "(");
			encode_type (encoding, type->t.func.type);
			dasprintf (encoding, "%s)", encode_params (type));
			break;
		case ev_pointer:
			if (type == &type_id) {
				dasprintf (encoding, "@");
				break;
			}
			if (type == &type_SEL) {
				dasprintf (encoding, ":");
				break;
			}
			if (type == &type_Class) {
				dasprintf (encoding, "#");
				break;
			}
			type = type->t.fldptr.type;
			dasprintf (encoding, "^");
			encode_type (encoding, type);
			break;
		case ev_quat:
			dasprintf (encoding, "Q");
			break;
		case ev_integer:
			dasprintf (encoding, "i");
			break;
		case ev_uinteger:
			dasprintf (encoding, "I");
			break;
		case ev_short:
			dasprintf (encoding, "s");
			break;
		case ev_invalid:
			switch (type->meta) {
				case ty_class:
					encode_class (encoding, type);
					break;
				case ty_enum:
					encode_enum (encoding, type);
					break;
				case ty_struct:
				case ty_union:
					encode_struct (encoding, type);
					break;
				case ty_array:
					dasprintf (encoding, "[");
					dasprintf (encoding, "%d", type->t.array.size);
					if (type->t.array.base)
						dasprintf (encoding, ":%d", type->t.array.base);
					dasprintf (encoding, "=");
					encode_type (encoding, type->t.array.type);
					dasprintf (encoding, "]");
					break;
				case ty_none:
					dasprintf (encoding, "?");
					break;
			}
			break;
		case ev_type_count:
			dasprintf (encoding, "?");
			break;
	}
}

int
is_void (const type_t *type)
{
	return type->type == ev_void;
}

int
is_enum (const type_t *type)
{
	if (type->type == ev_invalid && type->meta == ty_enum)
		return 1;
	return 0;
}

int
is_integral (const type_t *type)
{
	etype_t     t = type->type;

	if (t == ev_integer || t == ev_uinteger || t == ev_short)
		return 1;
	return is_enum (type);
}

int
is_float (const type_t *type)
{
	return type->type == ev_float;
}

int
is_scalar (const type_t *type)
{
	return is_float (type) || is_integral (type);
}

int
is_math (const type_t *type)
{
	etype_t     t = type->type;

	return t == ev_vector || t == ev_quat || is_scalar (type);
}

int
is_struct (const type_t *type)
{
	if (type->type == ev_invalid
		&& (type->meta == ty_struct || type->meta == ty_union))
		return 1;
	return 0;
}

int
is_pointer (const type_t *type)
{
	if (type->type == ev_pointer)
		return 1;
	return 0;
}

int
is_array (const type_t *type)
{
	if (type->type == ev_invalid && type->meta == ty_array)
		return 1;
	return 0;
}

int
type_assignable (const type_t *dst, const type_t *src)
{
	int         ret;

	// same type
	if (dst == src)
		return 1;
	// any field = any field
	if (dst->type == ev_field && src->type == ev_field)
		return 1;
	// pointer = array
	if (is_pointer (dst) && is_array (src)) {
		if (dst->t.fldptr.type == src->t.array.type)
			return 1;
		return 0;
	}
	if (!is_pointer (dst) || !is_pointer (src))
		return is_scalar (dst) && is_scalar (src);

	// pointer = pointer
	// give the object system first shot because the pointee types might have
	// protocols attached.
	ret = obj_types_assignable (dst, src);
	// ret < 0 means obj_types_assignable can't decide
	if (ret >= 0)
		return ret;

	dst = dst->t.fldptr.type;
	src = src->t.fldptr.type;
	if (is_void (dst))
		return 1;
	if (is_void (src))
		return 1;
	return 0;
}

int
type_size (const type_t *type)
{
	if (!type)
		return 0;
	switch (type->type) {
		case ev_void:
		case ev_string:
		case ev_float:
		case ev_vector:
		case ev_entity:
		case ev_field:
		case ev_func:
		case ev_pointer:
		case ev_quat:
		case ev_integer:
		case ev_uinteger:
		case ev_short:
		case ev_type_count:
			return pr_type_size[type->type];
		case ev_invalid:
			switch (type->meta) {
				case ty_enum:
					if (!type->t.symtab)
						return 0;
					return type_size (&type_integer);
				case ty_struct:
				case ty_union:
					if (!type->t.symtab)
						return 0;
					return type->t.symtab->size;
				case ty_class:
					{
						class_t    *class = type->t.class;
						int         size;
						if (!class->ivars)
							return 0;
						size = class->ivars->size;
						if (class->super_class)
							size += type_size (class->super_class->type);
						return size;
					}
				case ty_array:
					return type->t.array.size * type_size (type->t.array.type);
				case ty_none:
					return 0;
			}
			break;
	}
	return 0;
}

void
init_types (void)
{
	static struct_def_t zero_struct[] = {
		{"string_val",       &type_string},
		{"float_val",        &type_float},
		{"entity_val",       &type_entity},
		{"field_val",        &type_field},
		{"func_val",         &type_function},
		{"pointer_val",      &type_pointer},
		{"vector_val",       &type_vector},
		{"int_val",          &type_integer},
		{"uint_val",         &type_uinteger},
		{"integer_val",      &type_integer},
		{"uinteger_val",     &type_uinteger},
		{"quaternion_val",   &type_quaternion},
		{0, 0}
	};
	static struct_def_t param_struct[] = {
		{"string_val",       &type_string},
		{"float_val",        &type_float},
		{"vector_val",       &type_vector},
		{"entity_val",       &type_entity},
		{"field_val",        &type_field},
		{"func_val",         &type_function},
		{"pointer_val",      &type_pointer},
		{"int_val",          &type_integer},
		{"uint_val",         &type_uinteger},
		{"integer_val",      &type_integer},
		{"uinteger_val",     &type_uinteger},
		{"quaternion_val",   &type_quaternion},
		{0, 0}
	};
	static struct_def_t vector_struct[] = {
		{"x", &type_float},
		{"y", &type_float},
		{"z", &type_float},
		{0, 0}
	};
	static struct_def_t quaternion_struct[] = {
		{"s", &type_float},
		{"v", &type_vector},
		{0, 0}
	};
	static struct_def_t type_encoding_struct[] = {
		{"types",	&type_pointer},
		{"size",	&type_integer},
		{0, 0}
	};

	type_nil = &type_quaternion;
	type_default = &type_integer;
	if (options.code.progsversion == PROG_ID_VERSION) {
		// vector can't be part of .zero for v6 progs because for v6 progs,
		// .zero is only one word wide.
		zero_struct[6].name = 0;
		// v6 progs don't have integers or quaternions
		param_struct[7].name = 0;
		type_nil = &type_vector;
		type_default = &type_float;
	}

	make_structure ("@zero", 'u', zero_struct, &type_zero);
	make_structure ("@param", 'u', param_struct, &type_param);
	make_structure ("@vector", 's', vector_struct, &type_vector);
	type_vector.type = ev_vector;
	type_vector.meta = ty_none;

	make_structure ("@type_encodings", 's', type_encoding_struct,
					&type_type_encodings);

	if (options.traditional)
		return;

	make_structure ("@quaternion", 's', quaternion_struct, &type_quaternion);
	type_quaternion.type = ev_quat;
	type_quaternion.meta = ty_none;
}

void
chain_initial_types (void)
{
	static struct_def_t va_list_struct[] = {
		{"count", &type_integer},
		{"list",  0},				// type will be filled in at runtime
		{0, 0}
	};

	chain_type (&type_void);
	chain_type (&type_string);
	chain_type (&type_float);
	chain_type (&type_vector);
	type_entity.t.symtab = pr.entity_fields;
	chain_type (&type_entity);
	chain_type (&type_field);
	chain_type (&type_function);
	chain_type (&type_pointer);
	chain_type (&type_floatfield);
	if (!options.traditional) {
		chain_type (&type_quaternion);
		chain_type (&type_integer);
		chain_type (&type_uinteger);
		chain_type (&type_short);
	}

	chain_type (&type_param);
	chain_type (&type_zero);
	chain_type (&type_type_encodings);

	va_list_struct[1].type = pointer_type (&type_param);
	make_structure ("@va_list", 's', va_list_struct, &type_va_list);
	chain_type (&type_va_list);
}
