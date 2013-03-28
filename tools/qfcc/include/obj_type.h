/*
	obj_type.h

	object file type encoding support

	Copyright (C) 2011 Bill Currie <bill@taniwha.org>

	Author: Bill Currie <bill@taniwha.org>
	Date: 2011/02/18

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

#ifndef __obj_type_h
#define __obj_type_h

/** \defgroup qfcc_qfo_type Object file type encoding
	\ingroup qfcc_qfo

	All \c pointer_t \c type fields are pointers within the type qfo_space.
*/
//@{

#include "QF/pr_comp.h"

#include "type.h"

typedef struct qfot_fldptr_s {
	pr_int_t    type;				///< ev_field or ev_pointer
	pointer_t   aux_type;			///< referenced type
} qfot_fldptr_t;

typedef struct qfot_func_s {
	pr_int_t    type;				///< always ev_func
	pointer_t   return_type;		///< return type of the function
	pr_int_t    num_params;			///< ones compliment count of the
									///< parameters. -ve values indicate the
									///< number of real parameters before the
									///< ellipsis
	pointer_t   param_types[1];		///< variable length list of parameter
									///< types
} qfot_func_t;

typedef struct qfot_var_s {
	pointer_t   type;				///< type of field or self reference for
									///< enum
	string_t    name;				///< name of field/enumerator
	pr_int_t    offset;				///< value for enum, 0 for union
} qfot_var_t;

typedef struct qfot_struct_s {
	string_t    tag;				///< struct/union/enum tag
	pr_int_t    num_fields;			///< number of fields/enumerators
	qfot_var_t  fields[1];			///< variable length list of
									///< fields/enumerators
} qfot_struct_t;

typedef struct qfot_array_s {
	pointer_t   type;				///< element type
	pr_int_t    base;				///< start index of array
	pr_int_t    size;				///< number of elements in array
} qfot_array_t;

/**	QFO type encoding.

	\note As this holds a union of all type representations, and those
	representations may contain variable arrays, sizeof() will return only
	one, rather useless, value. It is also not suitable for direct use in
	arrays.
*/
typedef struct qfot_type_s {
	pr_int_t    ty;					///< meta type: ty_meta_e
	pr_int_t    size;				///< total word size of this encoding
	string_t    encoding;			///< Objective-QC encoding
	union {
		pr_int_t    type;			///< basic type: etype_t
		qfot_fldptr_t fldptr;		///< ty_none, ev_pointer/ev_field
		qfot_func_t func;			///< ty_none, ev_func
		qfot_struct_t strct;		///< ty_struct/ty_union/ty_enum
		qfot_array_t array;			///< ty_array
		pointer_t   class;			///< ty_class
	}           t;
} qfot_type_t;

typedef struct qfot_type_encodings_s {
	pointer_t   types;
	pr_int_t    size;
} qfot_type_encodings_t;

struct type_s;
struct def_s *qfo_encode_type (struct type_s *type);

//@}

#endif//__obj_type_h
