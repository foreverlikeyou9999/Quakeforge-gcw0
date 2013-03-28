/*
	rua_obj.c

	Progs Obj runtime support

	Copyright (C) 2001 Bill Currie

	Author: Bill Currie <bill@taniwha.org>
	Date: 2002/7/21

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

#if defined(_WIN32) && defined(HAVE_MALLOC_H)
#include <malloc.h>
#endif

#include "qfalloca.h"

#include "QF/cvar.h"
#include "QF/dstring.h"
#include "QF/hash.h"
#include "QF/mathlib.h"
#include "QF/pr_obj.h"
#include "QF/progs.h"
#include "QF/ruamoko.h"
#include "QF/sys.h"

#include "compat.h"
#include "rua_internal.h"

typedef struct obj_list_s {
	struct obj_list_s *next;
	void       *data;
} obj_list;

static obj_list *obj_list_free_list;

static obj_list *
obj_list_new (void)
{
	int         i;
	obj_list   *l;

	if (!obj_list_free_list) {
		obj_list_free_list = calloc (128, sizeof (obj_list));
		for (i = 0; i < 127; i++)
			obj_list_free_list[i].next = &obj_list_free_list[i + 1];
	}
	l = obj_list_free_list;
	obj_list_free_list = l->next;
	l->next = 0;
	return l;
}

static void
obj_list_free (obj_list *l)
{
	obj_list   *e;

	if (!l)
		return;

	for (e = l; e->next; e = e->next)
		;
	e->next = obj_list_free_list;
	obj_list_free_list = l;
}

static inline obj_list *
list_cons (void *data, obj_list *next)
{
	obj_list   *l = obj_list_new ();
	l->data = data;
	l->next = next;
	return l;
}

static inline void
list_remove (obj_list **list)
{
	if ((*list)->next) {
		obj_list   *l = *list;
		*list = (*list)->next;
		l->next = 0;
		obj_list_free (l);
	} else {
		obj_list_free (*list);
		*list = 0;
	}
}

typedef struct class_tree {
	pr_class_t *class;
	obj_list   *subclasses;
} class_tree;

class_tree *class_tree_free_list;

static class_tree *
class_tree_new (void)
{
	int         i;
	class_tree *t;

	if (!class_tree_free_list) {
		class_tree_free_list = calloc (128, sizeof (class_tree));
		for (i = 0; i < 127; i++) {
			class_tree *x = &class_tree_free_list[i];
			x->subclasses = (obj_list *) (x + 1);
		}
	}
	t = class_tree_free_list;
	class_tree_free_list = (class_tree *) t->subclasses;
	t->subclasses = 0;
	return t;
}

static int
class_is_subclass_of_class (progs_t *pr, pr_class_t *class,
							pr_class_t *superclass)
{
	while (class) {
		if (class == superclass)
			return 1;
		if (!class->super_class)
			break;
		class = Hash_Find (pr->classes, PR_GetString (pr, class->super_class));
	}
	return 0;
}

static class_tree *
create_tree_of_subclasses_inherited_from (progs_t *pr, pr_class_t *bottom,
										  pr_class_t *upper)
{
	const char *super_class = PR_GetString (pr, bottom->super_class);
	pr_class_t *superclass;
	class_tree *tree, *prev;

	superclass = bottom->super_class ? Hash_Find (pr->classes, super_class)
									 : 0;
	tree = prev = class_tree_new ();
	prev->class = bottom;
	while (superclass != upper) {
		tree = class_tree_new ();
		tree->class = superclass;
		tree->subclasses = list_cons (prev, tree->subclasses);
		super_class = PR_GetString (pr, superclass->super_class);
		superclass = (superclass->super_class ? Hash_Find (pr->classes,
														   super_class)
											  : 0);
		prev = tree;
	}
	return tree;
}

static class_tree *
_obj_tree_insert_class (progs_t *pr, class_tree *tree, pr_class_t *class)
{
	obj_list   *subclasses;
	class_tree *new_tree;

	if (!tree)
		return create_tree_of_subclasses_inherited_from (pr, class, 0);
	if (class == tree->class)
		return tree;
	if ((class->super_class ? Hash_Find (pr->classes,
										 PR_GetString (pr,
											 		   class->super_class))
							: 0) == tree->class) {
		obj_list   *list = tree->subclasses;
		class_tree *node;

		while (list) {
			if (((class_tree *) list->data)->class == class)
				return tree;
			list = list->next;
		}
		node = class_tree_new ();
		node->class = class;
		tree->subclasses = list_cons (node, tree->subclasses);
		return tree;
	}
	if (!class_is_subclass_of_class (pr, class, tree->class))
		return 0;
	for (subclasses = tree->subclasses; subclasses;
		 subclasses = subclasses->next) {
		pr_class_t *aclass = ((class_tree *)subclasses->data)->class;
		if (class_is_subclass_of_class (pr, class, aclass)) {
			subclasses->data = _obj_tree_insert_class (pr, subclasses->data,
													   class);
			return tree;
		}
	}
	new_tree = create_tree_of_subclasses_inherited_from (pr, class,
														 tree->class);
	tree->subclasses = list_cons (new_tree, tree->subclasses);
	return tree;
}

static void
obj_tree_insert_class (progs_t *pr, pr_class_t *class)
{
	obj_list   *list_node;
	class_tree *tree;

	list_node = pr->class_tree_list;
	while (list_node) {
		tree = _obj_tree_insert_class (pr, list_node->data, class);
		if (tree) {
			list_node->data = tree;
			break;
		} else {
			list_node = list_node->next;
		}
	}
	if (!list_node) {
		tree = _obj_tree_insert_class (pr, 0, class);
		pr->class_tree_list = list_cons (tree, pr->class_tree_list);
	}
}

static void
obj_create_classes_tree (progs_t *pr, pr_module_t *module)
{
	pr_symtab_t *symtab = &G_STRUCT (pr, pr_symtab_t, module->symtab);
	int         i;

	for (i = 0; i < symtab->cls_def_cnt; i++) {
		pr_class_t *class = &G_STRUCT (pr, pr_class_t, symtab->defs[i]);
		obj_tree_insert_class (pr, class);
	}
}

static void
obj_destroy_class_tree_node (progs_t *pr, class_tree *tree, int level)
{
	tree->subclasses = (obj_list *) class_tree_free_list;
	class_tree_free_list = tree;
}

static void
obj_preorder_traverse (progs_t *pr, class_tree *tree, int level,
					   void (*func) (progs_t *, class_tree *, int))
{
	obj_list   *node;

	func (pr, tree, level);
	for (node = tree->subclasses; node; node = node->next)
		obj_preorder_traverse (pr, node->data, level + 1, func);
}

static void
obj_postorder_traverse (progs_t *pr, class_tree *tree, int level,
						void (*func) (progs_t *, class_tree *, int))
{
	obj_list   *node;

	for (node = tree->subclasses; node; node = node->next)
		obj_postorder_traverse (pr, node->data, level + 1, func);
	func (pr, tree, level);
}

static const char *
selector_get_key (const void *s, void *_pr)
{
	progs_t    *pr = (progs_t *) _pr;
	return PR_GetString (pr, pr->selector_names[(intptr_t) s]);
}

static const char *
class_get_key (const void *c, void *pr)
{
	return PR_GetString ((progs_t *)pr, ((pr_class_t *)c)->name);
}

static uintptr_t
load_methods_get_hash (const void *m, void *pr)
{
	return (uintptr_t) m;
}

static int
load_methods_compare (const void *m1, const void *m2, void *pr)
{
	return m1 == m2;
}

static inline int
sel_eq (pr_sel_t *s1, pr_sel_t *s2)
{
	if (!s1 || !s2)
		return s1 == s2;
	return s1->sel_id == s2->sel_id;
}

static int
object_is_instance (progs_t *pr, pr_id_t *object)
{
	pr_class_t *class;

	if (object) {
		class = &G_STRUCT (pr, pr_class_t, object->class_pointer);
		return PR_CLS_ISCLASS (class);
	}
	return 0;
}

static string_t
object_get_class_name (progs_t *pr, pr_id_t *object)
{
	pr_class_t *class;

	if (object) {
		class = &G_STRUCT (pr, pr_class_t, object->class_pointer);
		if (PR_CLS_ISCLASS (class)) {
			R_INT (pr) = class->name;
			return class->name;
		}
		if (PR_CLS_ISMETA (class)) {
			R_INT (pr) = ((pr_class_t *)object)->name;
			return ((pr_class_t *)object)->name;
		}
	}
	return PR_SetString (pr, "Nil");
}

//====================================================================

static void
finish_class (progs_t *pr, pr_class_t *class, pointer_t object_ptr)
{
	pr_class_t *meta = &G_STRUCT (pr, pr_class_t, class->class_pointer);
	pr_class_t *val;

	meta->class_pointer = object_ptr;
	if (class->super_class) {
		const char *super_class = PR_GetString (pr, class->super_class);
		const char *class_name = PR_GetString (pr, class->name);
		val = Hash_Find (pr->classes, super_class);
		if (!val)
			PR_Error (pr, "broken class %s: super class %s not found",
					  class_name, super_class);
		meta->super_class = val->class_pointer;
		class->super_class = PR_SetPointer (pr, val);
	} else {
		pointer_t  *ml = &meta->methods;
		while (*ml)
			ml = &G_STRUCT (pr, pr_method_list_t, *ml).method_next;
		*ml = class->methods;
	}
	Sys_MaskPrintf (SYS_RUA_OBJ, "    %x %x %x\n", meta->class_pointer,
					meta->super_class, class->super_class);
}

//====================================================================

static int
add_sel_name (progs_t *pr, const char *name)
{
	int         ind = ++pr->selector_index;
	int         size, i;

	if (pr->selector_index >= pr->selector_index_max) {
		size = pr->selector_index_max + 128;
		pr->selector_sels = realloc (pr->selector_sels,
									 size * sizeof (obj_list *));
		pr->selector_names = realloc (pr->selector_names,
									  size * sizeof (string_t));
		for (i = pr->selector_index_max; i < size; i++) {
			pr->selector_sels[i] = 0;
			pr->selector_names[i] = 0;
		}
		pr->selector_index_max = size;
	}
	pr->selector_names[ind] = PR_SetString (pr, name);
	return ind;
}

static pr_sel_t *
sel_register_typed_name (progs_t *pr, const char *name, const char *types,
						 pr_sel_t *sel)
{
	intptr_t	index;
	int			is_new = 0;
	obj_list   *l;

	Sys_MaskPrintf (SYS_RUA_OBJ, "    Registering SEL %s %s\n", name, types);
	index = (intptr_t) Hash_Find (pr->selector_hash, name);
	if (index) {
		for (l = pr->selector_sels[index]; l; l = l->next) {
			pr_sel_t   *s = l->data;
			if (!types || !s->sel_types) {
				if (!s->sel_types && !types) {
					if (sel) {
						sel->sel_id = index;
						goto done;
					}
					return s;
				}
			} else if (strcmp (PR_GetString (pr, s->sel_types), types) == 0) {
				if (sel) {
					sel->sel_id = index;
					goto done;
				}
				return s;
			}
		}
	} else {
		index = add_sel_name (pr, name);
		is_new = 1;
	}
	if (!sel)
		sel = PR_Zone_Malloc (pr, sizeof (pr_sel_t));

	sel->sel_id = index;
	sel->sel_types = PR_SetString (pr, types);

	l = obj_list_new ();
	l->data = sel;
	l->next = pr->selector_sels[index];
	pr->selector_sels[index] = l;

	if (is_new)
		Hash_Add (pr->selector_hash, (void *) index);
done:
	Sys_MaskPrintf (SYS_RUA_OBJ, "        %d @ %x\n",
					sel->sel_id, PR_SetPointer (pr, sel));
	return sel;
}

static pr_sel_t *
sel_register_name (progs_t *pr, const char *name)
{
	return sel_register_typed_name (pr, name, "", 0);
}

static void
register_selectors_from_list (progs_t *pr, pr_method_list_t *method_list)
{
	int         i;

	for (i = 0; i < method_list->method_count; i++) {
		pr_method_t *method = &method_list->method_list[i];
		const char *name = PR_GetString (pr, method->method_name);
		const char *types = PR_GetString (pr, method->method_types);
		pr_sel_t   *sel = sel_register_typed_name (pr, name, types, 0);
		method->method_name = PR_SetPointer (pr, sel);
	}
}

static void
obj_register_selectors_from_class (progs_t *pr, pr_class_t *class)
{
	pr_method_list_t *method_list = &G_STRUCT (pr, pr_method_list_t,
											   class->methods);
	while (method_list) {
		register_selectors_from_list (pr, method_list);
		method_list = &G_STRUCT (pr, pr_method_list_t,
								 method_list->method_next);
	}
}

static void
obj_init_protocols (progs_t *pr, pr_protocol_list_t *protos)
{
	pr_class_t *proto_class;
	pr_protocol_t *proto;
	int         i;

	if (!protos)
		return;

	if (!(proto_class = Hash_Find (pr->classes, "Protocol"))) {
		pr->unclaimed_proto_list = list_cons (protos,
											  pr->unclaimed_proto_list);
		return;
	}

	for (i = 0; i < protos->count; i++) {
		proto = &G_STRUCT (pr, pr_protocol_t, protos->list[i]);
		if (!proto->class_pointer) {
			proto->class_pointer = PR_SetPointer (pr, proto_class);
			obj_init_protocols (pr, &G_STRUCT (pr, pr_protocol_list_t,
											   proto->protocol_list));
		} else {
			if (proto->class_pointer != PR_SetPointer (pr, proto_class))
				PR_RunError (pr, "protocol broken");
		}
	}
}

static void
class_add_method_list (progs_t *pr, pr_class_t *class, pr_method_list_t *list)
{
	int         i;

	for (i = 0; i < list->method_count; i++) {
		pr_method_t *method = &list->method_list[i];
		if (method->method_name) {
			const char *name = PR_GetString (pr, method->method_name);
			const char *types = PR_GetString (pr, method->method_types);
			pr_sel_t   *sel = sel_register_typed_name (pr, name, types, 0);
			method->method_name = PR_SetPointer (pr, sel);
		}
	}

	list->method_next = class->methods;
	class->methods = PR_SetPointer (pr, list);
}

static void
obj_class_add_protocols (progs_t *pr, pr_class_t *class,
						 pr_protocol_list_t *protos)
{
	if (!protos)
		return;

	protos->next = class->protocols;
	class->protocols = protos->next;
}

static void
finish_category (progs_t *pr, pr_category_t *category, pr_class_t *class)
{
	pr_method_list_t *method_list;
	pr_protocol_list_t *protocol_list;

	if (category->instance_methods) {
		method_list = &G_STRUCT (pr, pr_method_list_t,
								 category->instance_methods);
		class_add_method_list (pr, class, method_list);
	}
	if (category->class_methods) {
		pr_class_t *meta = &G_STRUCT (pr, pr_class_t, class->class_pointer);
		method_list = &G_STRUCT (pr, pr_method_list_t,
								 category->class_methods);
		class_add_method_list (pr, meta, method_list);
	}
	if (category->protocols) {
		protocol_list = &G_STRUCT (pr, pr_protocol_list_t,
								   category->protocols);
		obj_init_protocols (pr, protocol_list);
		obj_class_add_protocols (pr, class, protocol_list);
	}
}

static void
obj_send_message_in_list (progs_t *pr, pr_method_list_t *method_list,
						  pr_class_t *class, pr_sel_t *op)
{
	int         i;

	if (!method_list)
		return;

	obj_send_message_in_list (pr, &G_STRUCT (pr, pr_method_list_t,
											 method_list->method_next),
							  class, op);

	for (i = 0; i < method_list->method_count; i++) {
		pr_method_t *mth = &method_list->method_list[i];
		if (mth->method_name && sel_eq (&G_STRUCT (pr, pr_sel_t,
												   mth->method_name), op)
			&& !Hash_FindElement (pr->load_methods, (void *) (intptr_t) mth->method_imp)) {
			Hash_AddElement (pr->load_methods, (void *) (intptr_t) mth->method_imp);

			PR_ExecuteProgram (pr, mth->method_imp);
			break;
		}
	}
}

static void
send_load (progs_t *pr, class_tree *tree, int level)
{
	pr_sel_t   *load_sel = sel_register_name (pr, "load");
	pr_class_t *class = tree->class;
	pr_class_t *meta = &G_STRUCT (pr, pr_class_t, class->class_pointer);
	pr_method_list_t *method_list = &G_STRUCT (pr, pr_method_list_t,
											   meta->methods);

	obj_send_message_in_list (pr, method_list, class, load_sel);
}

static void
obj_send_load (progs_t *pr)
{
	obj_list   *m;

	if (pr->unresolved_classes) {
		pr_class_t *class = pr->unresolved_classes->data;
		const char *super_class = PR_GetString (pr, class->super_class);
		while (Hash_Find (pr->classes, super_class)) {
			list_remove (&pr->unresolved_classes);
			if (pr->unresolved_classes) {
				class = pr->unresolved_classes->data;
				super_class = PR_GetString (pr, class->super_class);
			} else {
				break;
			}
		}
		if (pr->unresolved_classes)
			return;
	}

	//XXX constant string stuff here (see init.c in libobjc source)

	for (m = pr->module_list; m; m = m->next)
		obj_create_classes_tree (pr, m->data);
	while (pr->class_tree_list) {
		obj_preorder_traverse (pr, pr->class_tree_list->data, 0, send_load);
		obj_postorder_traverse (pr, pr->class_tree_list->data, 0,
								obj_destroy_class_tree_node);
		list_remove (&pr->class_tree_list);
	}
	//XXX callback
	//for (m = pr->module_list; m; m = m->next)
	//	obj_create_classes_tree (pr, m->data);
	obj_list_free (pr->module_list);
	pr->module_list = 0;
}

static pr_method_t *
obj_find_message (progs_t *pr, pr_class_t *class, pr_sel_t *selector)
{
	pr_class_t *c = class;
	pr_method_list_t *method_list;
	pr_method_t *method;
	pr_sel_t   *sel;
	int         i;
	int         dev = developer->int_val;
	string_t   *names;

	if (dev & SYS_RUA_MSG) {
		names = pr->selector_names;
		Sys_Printf ("Searching for %s\n",
					PR_GetString (pr, names[selector->sel_id]));
	}
	while (c) {
		if (dev & SYS_RUA_MSG)
			Sys_Printf ("Checking class %s @ %x\n",
						PR_GetString (pr, c->name),
						PR_SetPointer (pr, c));
		method_list = &G_STRUCT (pr, pr_method_list_t, c->methods);
		while (method_list) {
			if (dev & SYS_RUA_MSG) {
				Sys_Printf ("method list %x\n",
							PR_SetPointer (pr, method_list));
			}
			for (i = 0, method = method_list->method_list;
				 i < method_list->method_count; i++, method++) {
				sel = &G_STRUCT (pr, pr_sel_t, method->method_name);
				if (developer->int_val & SYS_RUA_MSG) {
					names = pr->selector_names;
					Sys_Printf ("  %s\n",
								PR_GetString (pr, names[sel->sel_id]));
				}
				if (sel->sel_id == selector->sel_id) {
					if (dev & SYS_RUA_MSG) {
						names = pr->selector_names;
						Sys_Printf ("found %s: %x\n",
									PR_GetString (pr, names[selector->sel_id]),
									method->method_imp);
					}
					return method;
				}
			}
			method_list = &G_STRUCT (pr, pr_method_list_t,
									 method_list->method_next);
		}
		c = c->super_class ? &G_STRUCT (pr, pr_class_t, c->super_class) : 0;
	}
	return 0;
}

static void
obj_send_initialize (progs_t *pr, pr_class_t *class)
{
	pr_method_list_t *method_list;
	pr_method_t *method;
	pr_sel_t   *sel;
	pr_class_t *class_pointer;
	pr_sel_t   *selector = sel_register_name (pr, "initialize");
	int         i;

	if (PR_CLS_ISINITIALIZED (class))
		return;
	class_pointer = &G_STRUCT (pr, pr_class_t, class->class_pointer);
	PR_CLS_SETINITIALIZED (class);
	PR_CLS_SETINITIALIZED (class_pointer);
	if (class->super_class)
		obj_send_initialize (pr, &G_STRUCT (pr, pr_class_t,
											class->super_class));

	method_list = &G_STRUCT (pr, pr_method_list_t, class_pointer->methods);
	while (method_list) {
		for (i = 0, method = method_list->method_list;
			 i < method_list->method_count; i++, method++) {
			sel = &G_STRUCT (pr, pr_sel_t, method->method_name);
			if (sel->sel_id == selector->sel_id) {
				PR_PushFrame (pr);
				PR_SaveParams (pr);
				// param 0 is known to be the class pointer
				P_POINTER (pr, 1) = method->method_name;
				// pr->pr_argc is known to be 2
				PR_ExecuteProgram (pr, method->method_imp);
				PR_RestoreParams (pr);
				PR_PopFrame (pr);
				return;
			}
		}
		method_list = &G_STRUCT (pr, pr_method_list_t,
								 method_list->method_next);
	}
}

static func_t
get_imp (progs_t *pr, pr_class_t *class, pr_sel_t *sel)
{
	pr_method_t *method = obj_find_message (pr, class, sel);

	return method ? method->method_imp : 0;
}

static func_t
obj_msg_lookup (progs_t *pr, pr_id_t *receiver, pr_sel_t *op)
{
	pr_class_t *class;
	if (!receiver)
		return 0;
	class = &G_STRUCT (pr, pr_class_t, receiver->class_pointer);
	if (PR_CLS_ISCLASS (class)) {
		if (!PR_CLS_ISINITIALIZED (class))
			obj_send_initialize (pr, class);
	} else if (PR_CLS_ISMETA (class)
			   && PR_CLS_ISCLASS ((pr_class_t *) receiver)) {
		if (!PR_CLS_ISINITIALIZED ((pr_class_t *) receiver))
			obj_send_initialize (pr, (pr_class_t *) receiver);
	}
	return get_imp (pr, class, op);
}

static func_t
obj_msg_lookup_super (progs_t *pr, pr_super_t *super, pr_sel_t *op)
{
	pr_class_t *class;

	if (!super->self)
		return 0;

	class = &G_STRUCT (pr, pr_class_t, super->class);
	return get_imp (pr, class, op);
}

static void
obj_verror (progs_t *pr, pr_id_t *object, int code, const char *fmt, int count,
			pr_type_t **args)
{
	dstring_t  *dstr = dstring_newstr ();

	PR_Sprintf (pr, dstr, "obj_verror", fmt, count, args);
	PR_RunError (pr, "%s", dstr->str);
}

static void
dump_ivars (progs_t *pr, pointer_t _ivars)
{
	pr_ivar_list_t *ivars;
	int         i;

	if (!_ivars)
		return;
	ivars = &G_STRUCT (pr, pr_ivar_list_t, _ivars);
	for (i = 0; i < ivars->ivar_count; i++) {
		Sys_Printf ("        %s %s %d\n",
					PR_GetString (pr, ivars->ivar_list[i].ivar_name),
					PR_GetString (pr, ivars->ivar_list[i].ivar_type),
					ivars->ivar_list[i].ivar_offset);
	}
}

static void
rua___obj_exec_class (progs_t *pr)
{
	pr_module_t *module = &P_STRUCT (pr, pr_module_t, 0);
	pr_symtab_t *symtab;
	pr_sel_t   *sel;
	pointer_t  *ptr;
	int         i;
	obj_list  **cell;

	if (!module)
		return;
	symtab = &G_STRUCT (pr, pr_symtab_t, module->symtab);
	if (!symtab)
		return;
	Sys_MaskPrintf (SYS_RUA_OBJ, "Initializing %s module\n"
					"symtab @ %x : %d selector%s @ %x, "
					"%d class%s and %d categor%s\n",
					PR_GetString (pr, module->name), module->symtab,
					symtab->sel_ref_cnt, symtab->sel_ref_cnt == 1 ? "" : "s",
					symtab->refs,
					symtab->cls_def_cnt, symtab->cls_def_cnt == 1 ? "" : "es",
					symtab->cat_def_cnt,
					symtab->cat_def_cnt == 1 ? "y" : "ies");

	pr->module_list = list_cons (module, pr->module_list);

	sel = &G_STRUCT (pr, pr_sel_t, symtab->refs);
	for (i = 0; i < symtab->sel_ref_cnt; i++) {
		const char *name, *types;
		name = PR_GetString (pr, sel->sel_id);
		types = PR_GetString (pr, sel->sel_types);
		sel_register_typed_name (pr, name, types, sel);
		sel++;
	}

	ptr = symtab->defs;
	for (i = 0; i < symtab->cls_def_cnt; i++, ptr++) {
		pr_class_t *class = &G_STRUCT (pr, pr_class_t, *ptr);
		pr_class_t *meta = &G_STRUCT (pr, pr_class_t, class->class_pointer);
		const char *super_class = PR_GetString (pr, class->super_class);

		Sys_MaskPrintf (SYS_RUA_OBJ, "Class %s @ %x\n",
						PR_GetString (pr, class->name), *ptr);
		Sys_MaskPrintf (SYS_RUA_OBJ, "    class pointer: %x\n",
						class->class_pointer);
		Sys_MaskPrintf (SYS_RUA_OBJ, "    super class: %s\n",
						PR_GetString (pr, class->super_class));
		Sys_MaskPrintf (SYS_RUA_OBJ, "    instance variables: %d @ %x\n",
						class->instance_size,
						class->ivars);
		if (developer->int_val & SYS_RUA_OBJ)
			dump_ivars (pr, class->ivars);
		Sys_MaskPrintf (SYS_RUA_OBJ, "    instance methods: %x\n",
						class->methods);
		Sys_MaskPrintf (SYS_RUA_OBJ, "    protocols: %x\n", class->protocols);

		Sys_MaskPrintf (SYS_RUA_OBJ, "    class methods: %x\n", meta->methods);
		Sys_MaskPrintf (SYS_RUA_OBJ, "    instance variables: %d @ %x\n",
						meta->instance_size,
						meta->ivars);
		if (developer->int_val & SYS_RUA_OBJ)
			dump_ivars (pr, meta->ivars);

		class->subclass_list = 0;

		Hash_Add (pr->classes, class);

		obj_register_selectors_from_class (pr, class);
		obj_register_selectors_from_class (pr, meta);

		if (class->protocols) {
			pr_protocol_list_t *protocol_list;
			protocol_list = &G_STRUCT (pr, pr_protocol_list_t,
									   class->protocols);
			obj_init_protocols (pr, protocol_list);
		}

		if (class->super_class && !Hash_Find (pr->classes, super_class))
			pr->unresolved_classes = list_cons (class, pr->unresolved_classes);
	}

	for (i = 0; i < symtab->cat_def_cnt; i++, ptr++) {
		pr_category_t *category = &G_STRUCT (pr, pr_category_t, *ptr);
		const char *class_name = PR_GetString (pr, category->class_name);
		pr_class_t *class = Hash_Find (pr->classes, class_name);

		Sys_MaskPrintf (SYS_RUA_OBJ, "Category %s (%s) @ %x\n",
						PR_GetString (pr, category->class_name),
						PR_GetString (pr, category->category_name), *ptr);
		Sys_MaskPrintf (SYS_RUA_OBJ, "    instance methods: %x\n",
						category->instance_methods);
		Sys_MaskPrintf (SYS_RUA_OBJ, "    class methods: %x\n",
						category->class_methods);
		Sys_MaskPrintf (SYS_RUA_OBJ, "    protocols: %x\n",
						category->protocols);

		if (class) {
			finish_category (pr, category, class);
		} else {
			pr->unclaimed_categories = list_cons (category,
												  pr->unclaimed_categories);
		}
	}

	for (cell = &pr->unclaimed_categories; *cell; ) {
		pr_category_t *category = (*cell)->data;
		const char *class_name = PR_GetString (pr, category->class_name);
		pr_class_t *class = Hash_Find (pr->classes, class_name);

		if (class) {
			list_remove (cell);
			finish_category (pr, category, class);
		} else {
			cell = &(*cell)->next;
		}
	}

	if (pr->unclaimed_proto_list && Hash_Find (pr->classes, "Protocol")) {
		for (cell = &pr->unclaimed_proto_list; *cell; ) {
			obj_init_protocols (pr, (*cell)->data);
			list_remove (cell);
		}
	}

	Sys_MaskPrintf (SYS_RUA_OBJ, "Finished initializing %s module\n",
					PR_GetString (pr, module->name));
	obj_send_load (pr);
	Sys_MaskPrintf (SYS_RUA_OBJ, "Leaving %s module init\n",
					PR_GetString (pr, module->name));
}

static void
rua_obj_error (progs_t *pr)
{
	pr_id_t    *object = &P_STRUCT (pr, pr_id_t, 0);
	int         code = P_INT (pr, 1);
	const char *fmt = P_GSTRING (pr, 2);
	int         count = pr->pr_argc - 3;
	pr_type_t **args = &pr->pr_params[3];

	obj_verror (pr, object, code, fmt, count, args);
}

static void
rua_obj_verror (progs_t *pr)
{
	pr_id_t    *object = &P_STRUCT (pr, pr_id_t, 0);
	int         code = P_INT (pr, 1);
	const char *fmt = P_GSTRING (pr, 2);
	pr_va_list_t *val = (pr_va_list_t *) pr->pr_params[3];
	pr_type_t  *params = &G_STRUCT (pr, pr_type_t, val->list);
	pr_type_t **args = alloca (val->count * sizeof (pr_type_t *));
	int         i;

	for (i = 0; i < val->count; i++)
		args[i] = params + i * pr->pr_param_size;
	obj_verror (pr, object, code, fmt, val->count, args);
}

static void
rua_obj_set_error_handler (progs_t *pr)
{
	//func_t      func = P_INT (pr, 0);
	//arglist
	//XXX
	PR_RunError (pr, "%s, not implemented", __FUNCTION__);
}

static void
rua_obj_msg_lookup (progs_t *pr)
{
	pr_id_t    *receiver = &P_STRUCT (pr, pr_id_t, 0);
	pr_sel_t   *op = &P_STRUCT (pr, pr_sel_t, 1);

	R_INT (pr) = obj_msg_lookup (pr, receiver, op);
}

static void
rua_obj_msg_lookup_super (progs_t *pr)
{
	pr_super_t *super = &P_STRUCT (pr, pr_super_t, 0);
	pr_sel_t   *_cmd = &P_STRUCT (pr, pr_sel_t, 1);

	R_INT (pr) = obj_msg_lookup_super (pr, super, _cmd);
}

static void
rua_obj_msg_sendv (progs_t *pr)
{
	pr_id_t    *receiver = &P_STRUCT (pr, pr_id_t, 0);
	pr_sel_t   *op = &P_STRUCT (pr, pr_sel_t, 1);
	pr_va_list_t *args = (pr_va_list_t *) &P_POINTER (pr, 2);
	pr_type_t  *params = G_GPOINTER (pr, args->list);
	int         count = args->count;
	func_t      imp = obj_msg_lookup (pr, receiver, op);

	count = bound (0, count, 6);
	if (count && pr_boundscheck->int_val)
		PR_BoundsCheckSize (pr, args->list, count * pr->pr_param_size);
	if (!imp)
		PR_RunError (pr, "%s does not respond to %s",
					 PR_GetString (pr, object_get_class_name (pr, receiver)),
					 PR_GetString (pr, pr->selector_names[op->sel_id]));
	if (count)
		memcpy (pr->pr_params[2], params, count * 4 * pr->pr_param_size);
	PR_CallFunction (pr, imp);
}

static void
rua_obj_increment_retaincount (progs_t *pr)
{
	pr_type_t  *obj = &P_STRUCT (pr, pr_type_t, 0);
	R_INT (pr) = ++(*--obj).integer_var;
}

static void
rua_obj_decrement_retaincount (progs_t *pr)
{
	pr_type_t  *obj = &P_STRUCT (pr, pr_type_t, 0);
	R_INT (pr) = --(*--obj).integer_var;
}

static void
rua_obj_get_retaincount (progs_t *pr)
{
	pr_type_t  *obj = &P_STRUCT (pr, pr_type_t, 0);
	R_INT (pr) = (*--obj).integer_var;
}

static void
rua_obj_malloc (progs_t *pr)
{
	int         size = P_INT (pr, 0) * sizeof (pr_type_t);
	void       *mem = PR_Zone_Malloc (pr, size);

	RETURN_POINTER (pr, mem);
}

static void
rua_obj_atomic_malloc (progs_t *pr)
{
	int         size = P_INT (pr, 0) * sizeof (pr_type_t);
	void       *mem = PR_Zone_Malloc (pr, size);

	RETURN_POINTER (pr, mem);
}

static void
rua_obj_valloc (progs_t *pr)
{
	int         size = P_INT (pr, 0) * sizeof (pr_type_t);
	void       *mem = PR_Zone_Malloc (pr, size);

	RETURN_POINTER (pr, mem);
}

static void
rua_obj_realloc (progs_t *pr)
{
	void       *mem = (void*)P_GPOINTER (pr, 0);
	int         size = P_INT (pr, 1) * sizeof (pr_type_t);

	mem = PR_Zone_Realloc (pr, mem, size);
	RETURN_POINTER (pr, mem);
}

static void
rua_obj_calloc (progs_t *pr)
{
	int         size = P_INT (pr, 0) * sizeof (pr_type_t);
	void       *mem = PR_Zone_Malloc (pr, size);

	memset (mem, 0, size);
	RETURN_POINTER (pr, mem);
}

static void
rua_obj_free (progs_t *pr)
{
	void       *mem = (void*)P_GPOINTER (pr, 0);

	PR_Zone_Free (pr, mem);
}

static void
rua_obj_get_uninstalled_dtable (progs_t *pr)
{
	//XXX
	PR_RunError (pr, "%s, not implemented", __FUNCTION__);
}

static void
rua_obj_msgSend (progs_t *pr)
{
	pr_id_t    *self = &P_STRUCT (pr, pr_id_t, 0);
	pr_sel_t   *_cmd = &P_STRUCT (pr, pr_sel_t, 1);
	func_t      imp;

	if (!self) {
		R_INT (pr) = P_INT (pr, 0);
		return;
	}
	if (!_cmd)
		PR_RunError (pr, "null selector");
	imp = obj_msg_lookup (pr, self, _cmd);
	if (!imp)
		PR_RunError (pr, "%s does not respond to %s",
					 PR_GetString (pr, object_get_class_name (pr, self)),
					 PR_GetString (pr, pr->selector_names[_cmd->sel_id]));

	PR_CallFunction (pr, imp);
}

static void
rua_obj_msgSend_super (progs_t *pr)
{
	pr_super_t *super = &P_STRUCT (pr, pr_super_t, 0);
	pr_sel_t   *_cmd = &P_STRUCT (pr, pr_sel_t, 1);
	func_t      imp;

	imp = obj_msg_lookup_super (pr, super, _cmd);
	if (!imp) {
		pr_id_t    *self = &G_STRUCT (pr, pr_id_t, super->self);
		PR_RunError (pr, "%s does not respond to %s",
					 PR_GetString (pr, object_get_class_name (pr, self)),
					 PR_GetString (pr, pr->selector_names[_cmd->sel_id]));
	}
	pr->pr_params[0] = pr->pr_real_params[0];
	P_POINTER (pr, 0) = super->self;
	PR_CallFunction (pr, imp);
}

static void
rua_obj_get_class (progs_t *pr)
{
	const char *name = P_GSTRING (pr, 0);
	pr_class_t *class;

	class = Hash_Find (pr->classes, name);
	if (!class)
		PR_RunError (pr, "could not find class %s", name);
	RETURN_POINTER (pr, class);
}

static void
rua_obj_lookup_class (progs_t *pr)
{
	const char *name = P_GSTRING (pr, 0);
	pr_class_t *class;

	class = Hash_Find (pr->classes, name);
	RETURN_POINTER (pr, class);
}

static void
rua_obj_next_class (progs_t *pr)
{
	//XXX
	PR_RunError (pr, "%s, not implemented", __FUNCTION__);
}

//====================================================================

static void
rua_sel_get_name (progs_t *pr)
{
	pr_sel_t   *sel = &P_STRUCT (pr, pr_sel_t, 0);

	if (sel->sel_id > 0 && sel->sel_id <= pr->selector_index)
		R_STRING (pr) = pr->selector_names[sel->sel_id];
	else
		R_STRING (pr) = 0;
}

static void
rua_sel_get_type (progs_t *pr)
{
	pr_sel_t   *sel = &P_STRUCT (pr, pr_sel_t, 0);

	R_INT (pr) = sel->sel_types;
}

static void
rua_sel_get_uid (progs_t *pr)
{
	const char *name = P_GSTRING (pr, 0);

	RETURN_POINTER (pr, sel_register_typed_name (pr, name, "", 0));
}

static void
rua_sel_register_name (progs_t *pr)
{
	const char *name = P_GSTRING (pr, 0);

	RETURN_POINTER (pr, sel_register_typed_name (pr, name, "", 0));
}

static void
rua_sel_is_mapped (progs_t *pr)
{
	// FIXME might correspond to a string
	pr_sel_t   *sel = &P_STRUCT (pr, pr_sel_t, 0);
	R_INT (pr) = sel->sel_id > 0 && sel->sel_id <= pr->selector_index;
}

//====================================================================

static void
rua_class_get_class_method (progs_t *pr)
{
	pr_class_t *class = &P_STRUCT (pr, pr_class_t, 0);
	pr_sel_t   *aSel = &P_STRUCT (pr, pr_sel_t, 1);
	pr_method_t *method;
	class = &G_STRUCT (pr, pr_class_t, class->class_pointer);
	method = obj_find_message (pr, class, aSel);
	RETURN_POINTER (pr, method);
}

static void
rua_class_get_instance_method (progs_t *pr)
{
	pr_class_t *class = &P_STRUCT (pr, pr_class_t, 0);
	pr_sel_t   *aSel = &P_STRUCT (pr, pr_sel_t, 1);
	pr_method_t *method = obj_find_message (pr, class, aSel);
	RETURN_POINTER (pr, method);
}

#define CLASSOF(x) (&G_STRUCT (pr, pr_class_t, (x)->class_pointer))

static void
rua_class_pose_as (progs_t *pr)
{
	pr_class_t *impostor = &P_STRUCT (pr, pr_class_t, 0);
	pr_class_t *superclass = &P_STRUCT (pr, pr_class_t, 1);
	pointer_t  *subclass;

	subclass = &superclass->subclass_list;
	while (*subclass) {
		pr_class_t *sub = &P_STRUCT (pr, pr_class_t, *subclass);
		pointer_t   nextSub = sub->sibling_class;
		if (sub != impostor) {
			sub->sibling_class = impostor->subclass_list;
			sub->super_class = P_POINTER (pr, 0);	// impostor
			impostor->subclass_list = *subclass;	// sub
			CLASSOF (sub)->sibling_class = CLASSOF (impostor)->sibling_class;
			CLASSOF (sub)->super_class = impostor->class_pointer;
			CLASSOF (impostor)->subclass_list = sub->class_pointer;
		}
		*subclass = nextSub;
	}
	superclass->subclass_list = P_POINTER (pr, 0);	// impostor
	CLASSOF (superclass)->subclass_list = impostor->class_pointer;

	impostor->sibling_class = 0;
	CLASSOF (impostor)->sibling_class = 0;

	//XXX how much do I need to do here?!?
	//class_table_replace (super_class, impostor);
	R_INT (pr) = P_POINTER (pr, 0);	// impostor
}
#undef CLASSOF

static inline pr_id_t *
class_create_instance (progs_t *pr, pr_class_t *class)
{
	int         size = (class->instance_size + 1) * sizeof (pr_type_t);
	pr_type_t  *mem;
	pr_id_t    *id;

	mem = PR_Zone_Malloc (pr, size);
	// redundant memset (id, 0, size);
	id = (pr_id_t *) (mem + 1);
	id->class_pointer = PR_SetPointer (pr, class);
	return id;
}

static void
rua_class_create_instance (progs_t *pr)
{
	pr_class_t *class = &P_STRUCT (pr, pr_class_t, 0);
	pr_id_t    *id = class_create_instance (pr, class);

	RETURN_POINTER (pr, id);
}

static void
rua_class_get_class_name (progs_t *pr)
{
	pr_class_t *class = &P_STRUCT (pr, pr_class_t, 0);
	R_INT (pr) = PR_CLS_ISCLASS (class) ? class->name
										: PR_SetString (pr, "Nil");
}

static void
rua_class_get_instance_size (progs_t *pr)
{
	pr_class_t *class = &P_STRUCT (pr, pr_class_t, 0);
	R_INT (pr) = PR_CLS_ISCLASS (class) ? class->instance_size : 0;
}

static void
rua_class_get_meta_class (progs_t *pr)
{
	pr_class_t *class = &P_STRUCT (pr, pr_class_t, 0);
	R_INT (pr) = PR_CLS_ISCLASS (class) ? class->class_pointer : 0;
}

static void
rua_class_get_super_class (progs_t *pr)
{
	pr_class_t *class = &P_STRUCT (pr, pr_class_t, 0);
	R_INT (pr) = PR_CLS_ISCLASS (class) ? class->super_class : 0;
}

static void
rua_class_get_version (progs_t *pr)
{
	pr_class_t *class = &P_STRUCT (pr, pr_class_t, 0);
	R_INT (pr) = PR_CLS_ISCLASS (class) ? class->version : -1;
}

static void
rua_class_is_class (progs_t *pr)
{
	pr_class_t *class = &P_STRUCT (pr, pr_class_t, 0);
	R_INT (pr) = PR_CLS_ISCLASS (class);
}

static void
rua_class_is_meta_class (progs_t *pr)
{
	pr_class_t *class = &P_STRUCT (pr, pr_class_t, 0);
	R_INT (pr) = PR_CLS_ISMETA (class);
}

static void
rua_class_set_version (progs_t *pr)
{
	pr_class_t *class = &P_STRUCT (pr, pr_class_t, 0);
	if (PR_CLS_ISCLASS (class))
		class->version = P_INT (pr, 1);
}

static void
rua_class_get_gc_object_type (progs_t *pr)
{
	pr_class_t *class = &P_STRUCT (pr, pr_class_t, 0);
	R_INT (pr) = PR_CLS_ISCLASS (class) ? class->gc_object_type : 0;
}

static void
rua_class_ivar_set_gcinvisible (progs_t *pr)
{
	//pr_class_t *impostor = &P_STRUCT (pr, pr_class_t, 0);
	//const char *ivarname = P_GSTRING (pr, 1);
	//int         gcInvisible = P_INT (pr, 2);
	//XXX
	PR_RunError (pr, "%s, not implemented", __FUNCTION__);
}

//====================================================================

static void
rua_method_get_imp (progs_t *pr)
{
	pr_method_t *method = &P_STRUCT (pr, pr_method_t, 0);

	R_INT (pr) = method->method_imp;
}

static void
rua_get_imp (progs_t *pr)
{
	pr_class_t *class = &P_STRUCT (pr, pr_class_t, 0);
	pr_sel_t   *sel = &P_STRUCT (pr, pr_sel_t, 1);

	R_INT (pr) = get_imp (pr, class, sel);
}

//====================================================================

static void
rua_object_dispose (progs_t *pr)
{
	pr_id_t    *object = &P_STRUCT (pr, pr_id_t, 0);
	pr_type_t  *mem = (pr_type_t *) object;
	PR_Zone_Free (pr, mem - 1);
}

static void
rua_object_copy (progs_t *pr)
{
	pr_id_t    *object = &P_STRUCT (pr, pr_id_t, 0);
	pr_class_t *class = &G_STRUCT (pr, pr_class_t, object->class_pointer);
	pr_id_t    *id;

	id = class_create_instance (pr, class);
	memcpy (id, object, sizeof (pr_type_t) * class->instance_size);
	// copy the retain count
	((pr_type_t *) id)[-1] = ((pr_type_t *) object)[-1];
	RETURN_POINTER (pr, id);
}

static void
rua_object_get_class (progs_t *pr)
{
	pr_id_t    *object = &P_STRUCT (pr, pr_id_t, 0);
	pr_class_t *class;

	if (object) {
		class = &G_STRUCT (pr, pr_class_t, object->class_pointer);
		if (PR_CLS_ISCLASS (class)) {
			RETURN_POINTER (pr, class);
			return;
		}
		if (PR_CLS_ISMETA (class)) {
			R_INT (pr) = P_INT (pr, 0);
			return;
		}
	}
	R_INT (pr) = 0;
}

static void
rua_object_get_super_class (progs_t *pr)
{
	pr_id_t    *object = &P_STRUCT (pr, pr_id_t, 0);
	pr_class_t *class;

	if (object) {
		class = &G_STRUCT (pr, pr_class_t, object->class_pointer);
		if (PR_CLS_ISCLASS (class)) {
			R_INT (pr) = class->super_class;
			return;
		}
		if (PR_CLS_ISMETA (class)) {
			R_INT (pr) = ((pr_class_t *)object)->super_class;
			return;
		}
	}
	R_INT (pr) = 0;
}

static void
rua_object_get_meta_class (progs_t *pr)
{
	pr_id_t    *object = &P_STRUCT (pr, pr_id_t, 0);
	pr_class_t *class;

	if (object) {
		class = &G_STRUCT (pr, pr_class_t, object->class_pointer);
		if (PR_CLS_ISCLASS (class)) {
			R_INT (pr) = class->class_pointer;
			return;
		}
		if (PR_CLS_ISMETA (class)) {
			R_INT (pr) = ((pr_class_t *)object)->class_pointer;
			return;
		}
	}
	R_INT (pr) = 0;
}

static void
rua_object_get_class_name (progs_t *pr)
{
	pr_id_t    *object = &P_STRUCT (pr, pr_id_t, 0);

	R_STRING (pr) = object_get_class_name (pr, object);
}

static void
rua_object_is_class (progs_t *pr)
{
	pr_id_t    *object = &P_STRUCT (pr, pr_id_t, 0);

	if (object) {
		R_INT (pr) = PR_CLS_ISCLASS ((pr_class_t*)object);
		return;
	}
	R_INT (pr) = 0;
}

static void
rua_object_is_instance (progs_t *pr)
{
	pr_id_t    *object = &P_STRUCT (pr, pr_id_t, 0);

	R_INT (pr) = object_is_instance (pr, object);
}

static void
rua_object_is_meta_class (progs_t *pr)
{
	pr_id_t    *object = &P_STRUCT (pr, pr_id_t, 0);

	if (object) {
		R_INT (pr) = PR_CLS_ISMETA ((pr_class_t*)object);
		return;
	}
	R_INT (pr) = 0;
}

//====================================================================

static void
rua__i_Object__hash (progs_t *pr)
{
	R_INT (pr) = P_INT (pr, 0);
}

static void
rua__i_Object_error_error_ (progs_t *pr)
{
	pr_id_t    *self = &P_STRUCT (pr, pr_id_t, 0);
	const char *fmt = P_GSTRING (pr, 2);
	dstring_t  *dstr = dstring_new ();
	int         count = pr->pr_argc - 3;
	pr_type_t **args = &pr->pr_params[3];

	dsprintf (dstr, "error: %s (%s)\n%s",
			  PR_GetString (pr, object_get_class_name (pr, self)),
			  object_is_instance (pr, self) ? "instance" : "class", fmt);
	obj_verror (pr, self, 0, dstr->str, count, args);
}

static void
rua__c_Object__conformsToProtocol_ (progs_t *pr)
{
	//pr_id_t    *object = &P_STRUCT (pr, pr_id_t, 0);
	//pr_protocol_t *proto = &P_STRUCT (pr, pr_protocol_t, 2);
	//...
	//XXX
	PR_RunError (pr, "%s, not implemented", __FUNCTION__);
}

static void
rua_PR_FindGlobal (progs_t *pr)
{
	const char *name = P_GSTRING (pr, 0);
	ddef_t     *def;

	R_POINTER (pr) = 0;
	def = PR_FindGlobal (pr, name);
	if (def)
		R_POINTER (pr) = def->ofs;	//FIXME def's can't access > 32k
}

//====================================================================

static builtin_t obj_methods [] = {
	{"__obj_exec_class",			rua___obj_exec_class,			-1},

	{"obj_error",					rua_obj_error,					-1},
	{"obj_verror",					rua_obj_verror,					-1},
	{"obj_set_error_handler",		rua_obj_set_error_handler,		-1},
	{"obj_msg_lookup",				rua_obj_msg_lookup,				-1},
	{"obj_msg_lookup_super",		rua_obj_msg_lookup_super,		-1},
	{"obj_msg_sendv",				rua_obj_msg_sendv,				-1},
	{"obj_increment_retaincount",	rua_obj_increment_retaincount,	-1},
	{"obj_decrement_retaincount",	rua_obj_decrement_retaincount,	-1},
	{"obj_get_retaincount",			rua_obj_get_retaincount,		-1},
	{"obj_malloc",					rua_obj_malloc,					-1},
	{"obj_atomic_malloc",			rua_obj_atomic_malloc,			-1},
	{"obj_valloc",					rua_obj_valloc,					-1},
	{"obj_realloc",					rua_obj_realloc,				-1},
	{"obj_calloc",					rua_obj_calloc,					-1},
	{"obj_free",					rua_obj_free,					-1},
	{"obj_get_uninstalled_dtable",	rua_obj_get_uninstalled_dtable,	-1},
	{"obj_msgSend",					rua_obj_msgSend,				-1},
	{"obj_msgSend_super",			rua_obj_msgSend_super,			-1},

	{"obj_get_class",				rua_obj_get_class,				-1},
	{"obj_lookup_class",			rua_obj_lookup_class,			-1},
	{"obj_next_class",				rua_obj_next_class,				-1},

	{"sel_get_name",				rua_sel_get_name,				-1},
	{"sel_get_type",				rua_sel_get_type,				-1},
	{"sel_get_uid",					rua_sel_get_uid,				-1},
	{"sel_register_name",			rua_sel_register_name,			-1},
	{"sel_is_mapped",				rua_sel_is_mapped,				-1},

	{"class_get_class_method",		rua_class_get_class_method,		-1},
	{"class_get_instance_method",	rua_class_get_instance_method,	-1},
	{"class_pose_as",				rua_class_pose_as,				-1},
	{"class_create_instance",		rua_class_create_instance,		-1},
	{"class_get_class_name",		rua_class_get_class_name,		-1},
	{"class_get_instance_size",		rua_class_get_instance_size,	-1},
	{"class_get_meta_class",		rua_class_get_meta_class,		-1},
	{"class_get_super_class",		rua_class_get_super_class,		-1},
	{"class_get_version",			rua_class_get_version,			-1},
	{"class_is_class",				rua_class_is_class,				-1},
	{"class_is_meta_class",			rua_class_is_meta_class,		-1},
	{"class_set_version",			rua_class_set_version,			-1},
	{"class_get_gc_object_type",	rua_class_get_gc_object_type,	-1},
	{"class_ivar_set_gcinvisible",	rua_class_ivar_set_gcinvisible,	-1},

	{"method_get_imp",				rua_method_get_imp,				-1},
	{"get_imp",						rua_get_imp,					-1},

	{"object_copy",					rua_object_copy,				-1},
	{"object_dispose",				rua_object_dispose,				-1},
	{"object_get_class",			rua_object_get_class,			-1},
	{"object_get_class_name",		rua_object_get_class_name,		-1},
	{"object_get_meta_class",		rua_object_get_meta_class,		-1},
	{"object_get_super_class",		rua_object_get_super_class,		-1},
	{"object_is_class",				rua_object_is_class,			-1},
	{"object_is_instance",			rua_object_is_instance,			-1},
	{"object_is_meta_class",		rua_object_is_meta_class,		-1},

	{"_i_Object__hash",				rua__i_Object__hash,			-1},
	{"_i_Object_error_error_",		rua__i_Object_error_error_,		-1},
	{"_c_Object__conformsToProtocol_", rua__c_Object__conformsToProtocol_, -1},

	{"PR_FindGlobal",				rua_PR_FindGlobal,				-1},//FIXME
	{0}
};

static int
rua_init_finish (progs_t *pr)
{
	pr_class_t **class_list, **class;

	class_list = (pr_class_t **) Hash_GetList (pr->classes);
	if (*class_list) {
		pr_class_t *object_class;
		pointer_t   object_ptr;

		object_class = Hash_Find (pr->classes, "Object");
		if (object_class && !object_class->super_class)
			object_ptr = (pr_type_t *)object_class - pr->pr_globals;
		else
			PR_Error (pr, "root class Object not found");
		for (class = class_list; *class; class++)
			finish_class (pr, *class, object_ptr);
	}
	free (class_list);

	return 1;
}

static int
rua_init_runtime (progs_t *pr)
{
	ddef_t     *def;
	unsigned    i;

	if (!pr->selector_hash)
		pr->selector_hash = Hash_NewTable (1021, selector_get_key, 0, pr);
	else
		Hash_FlushTable (pr->selector_hash);
	pr->selector_index = 0;
	for (i = 0; i < pr->selector_index_max; i++) {
		obj_list_free (pr->selector_sels[i]);
		pr->selector_sels[i] = 0;
		pr->selector_names[i] = 0;
	}

	if (!pr->classes)
		pr->classes = Hash_NewTable (1021, class_get_key, 0, pr);
	else
		Hash_FlushTable (pr->classes);

	if (!pr->load_methods) {
		pr->load_methods = Hash_NewTable (1021, 0, 0, pr);
		Hash_SetHashCompare (pr->load_methods, load_methods_get_hash,
							 load_methods_compare);
	} else {
		Hash_FlushTable (pr->load_methods);
	}

	pr->unresolved_classes = 0;
	pr->unclaimed_categories = 0;
	pr->unclaimed_proto_list = 0;
	pr->module_list = 0;
	pr->class_tree_list = 0;

	if ((def = PR_FindField (pr, ".this")))
		pr->fields.this = def->ofs;

	PR_AddLoadFinishFunc (pr, rua_init_finish);
	return 1;
}

void
RUA_Obj_Init (progs_t *pr, int secure)
{
	PR_RegisterBuiltins (pr, obj_methods);

	PR_AddLoadFunc (pr, rua_init_runtime);
}

func_t
RUA_Obj_msg_lookup (progs_t *pr, pointer_t _self, pointer_t __cmd)
{
	pr_id_t    *self = &G_STRUCT (pr, pr_id_t, _self);
	pr_sel_t   *_cmd = &G_STRUCT (pr, pr_sel_t, __cmd);
	func_t      imp;

	if (!self)
		return 0;
	if (!_cmd)
		PR_RunError (pr, "null selector");
	imp = obj_msg_lookup (pr, self, _cmd);
	if (!imp)
		PR_RunError (pr, "%s does not respond to %s",
					 PR_GetString (pr, object_get_class_name (pr, self)),
					 PR_GetString (pr, pr->selector_names[_cmd->sel_id]));

	return imp;
}
