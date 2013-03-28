/*
	dump_modules.c

	Module dumping.

	Copyright (C) 2002 Bill Currie <bill@taniwha.org>

	Author: Bill Currie <bill@taniwha.org>
	Date: 2002/08/19

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

#include "QF/pr_obj.h"
#include "QF/progs.h"
#include "QF/va.h"

#include "qfprogs.h"

static void
dump_methods (progs_t *pr, pr_method_list_t *methods, int class)
{
	int         i;
	char        mark = class ? '+' : '-';
	const char *sel_id;
	const char *types;

	while (methods) {
		pr_method_t *method = methods->method_list;
		for (i = 0; i < methods->method_count; i++) {
			if (PR_StringValid (pr, method->method_name))
				sel_id = PR_GetString (pr, method->method_name);
			else
				sel_id = "<invalid string>";
			if (PR_StringValid (pr, method->method_types))
				types = PR_GetString (pr, method->method_types);
			else
				types = "<invalid string>";
			printf ("        %c%s %d @ %x %s\n",
					mark, sel_id, method->method_imp,
					PR_SetPointer (pr, method), types);
			method++;
		}
		methods = &G_STRUCT (pr, pr_method_list_t, methods->method_next);
	}
}

static void
dump_selector (progs_t *pr, pr_sel_t *sel)
{
	const char *sel_name = "<invalid string>";
	const char *sel_types = "<invalid string>";

	if (PR_StringValid (pr, sel->sel_id))
		sel_name = PR_GetString (pr, sel->sel_id);
	if (PR_StringValid (pr, sel->sel_types))
		sel_types = PR_GetString (pr, sel->sel_types);
	printf ("        %s\n", sel_name);
	if (*sel_types)
		printf ("          %s\n", sel_types);
}

static void
dump_protocol (progs_t *pr, pr_protocol_t *proto)
{
	const char *protocol_name = "<invalid string>";
	printf ("                %d ", proto->class_pointer);
	if (PR_StringValid (pr, proto->protocol_name))
		protocol_name = PR_GetString (pr, proto->protocol_name);
	printf ("<%s>\n", protocol_name);
}

static void
dump_protocol_list (progs_t *pr, pr_protocol_list_t *list)
{
	int         i;
	printf ("            %d\n", list->next);
	printf ("            %d\n", list->count);
	for (i = 0; i < list->count; i++) {
		if (list->list[i] <= 0 || list->list[i] >= pr->globals_size) {
			printf ("invalid pointer\n");
			break;
		}
		dump_protocol (pr, &G_STRUCT (pr, pr_protocol_t, list->list[i]));
	}
}

static void
dump_class (progs_t *pr, pr_class_t *class)
{
	pr_class_t *meta;
	const char *class_name = "<invalid string>";
	const char *super_class_name = "<invalid string>";

	if (!class) {
		printf ("    (nil)\n");
		return;
	}
	meta = &G_STRUCT (pr, pr_class_t, class->class_pointer);
	if (PR_StringValid (pr, class->name))
		class_name = PR_GetString (pr, class->name);
	if (class->super_class) {
		if (PR_StringValid (pr, class->super_class))
			super_class_name = PR_GetString (pr, class->super_class);
		printf ("    %s @ %x : %s\n", class_name, PR_SetPointer (pr, class),
				super_class_name);
	} else {
		printf ("    %s @ %x\n", class_name, PR_SetPointer (pr, class));
	}
	printf ("        meta:%x verion:%d info:%u size:%d\n",
			class->class_pointer, class->version,
			class->info, class->instance_size);
	dump_methods (pr, &G_STRUCT (pr, pr_method_list_t, class->methods), 0);
	dump_methods (pr, &G_STRUCT (pr, pr_method_list_t, meta->methods), 1);
	printf ("        %x\n", class->protocols);
	if (class->protocols)
		dump_protocol_list (pr, &G_STRUCT (pr, pr_protocol_list_t,
										   class->protocols));
}

static void
dump_category (progs_t *pr, pr_category_t *category)
{
	const char *category_name = "<invalid string>";
	const char *class_name = "<invalid string>";

	if (PR_StringValid (pr, category->category_name))
		category_name = PR_GetString (pr, category->category_name);
	if (PR_StringValid (pr, category->class_name))
		class_name = PR_GetString (pr, category->class_name);
	printf ("    %s (%s) @ %d\n", class_name, category_name,
			PR_SetPointer (pr, category));
	dump_methods (pr,
				  &G_STRUCT (pr, pr_method_list_t, category->instance_methods),
				  0);
	dump_methods (pr,
				  &G_STRUCT (pr, pr_method_list_t, category->class_methods),
				  1);
	printf ("        %d\n", category->protocols);
	if (category->protocols)
		dump_protocol_list (pr, &G_STRUCT (pr, pr_protocol_list_t,
										   category->protocols));
}

static void
dump_module (progs_t *pr, pr_module_t *module)
{
	pr_symtab_t *symtab = &G_STRUCT (pr, pr_symtab_t, module->symtab);
	pointer_t  *ptr = symtab->defs;
	pr_sel_t   *sel = &G_STRUCT (pr, pr_sel_t, symtab->refs);
	int         i;
	const char *module_name = "<invalid string>";

	if (PR_StringValid (pr, module->name))
		module_name = PR_GetString (pr, module->name);
	printf ("version:%d size:%d %s\n", module->version, module->size,
			module_name);
	if (!symtab) {
		printf ("    No symtab!\n");
		return;
	}
	printf ("    symtab @ %x selectors:%d @ %x classes:%d categories:%d\n",
			module->symtab, symtab->sel_ref_cnt, symtab->refs,
			symtab->cls_def_cnt, symtab->cat_def_cnt);
	for (i = 0; i < symtab->sel_ref_cnt; i++)
		dump_selector (pr, sel++);
	for (i = 0; i < symtab->cls_def_cnt; i++)
		dump_class (pr, &G_STRUCT (pr, pr_class_t, *ptr++));
	for (i = 0; i < symtab->cat_def_cnt; i++)
		dump_category (pr, &G_STRUCT (pr, pr_category_t, *ptr++));
}

void
dump_modules (progs_t *pr)
{
	unsigned int i;

	for (i = 0; i < pr->progs->numglobaldefs; i++) {
		ddef_t     *def = &pr->pr_globaldefs[i];
		const char *name = "<invalid_string>";

		if (PR_StringValid (pr, def->s_name))
			name = PR_GetString (pr, def->s_name);
		if (strcmp (name, "_OBJ_MODULE") == 0) {
			printf ("module @ %x\n", def->ofs);
			dump_module (pr, &G_STRUCT (pr, pr_module_t, def->ofs));
		}
	}
}
