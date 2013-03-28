/*
	alloc.h

	High-tide allocator.

	Copyright (C) 2012 Bill Currie <bill@taniwha.org>

	Author: Bill Currie <bill@taniwha.org>
	Date: 2012/12/06

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

#ifndef __QF_alloc_h
#define __QF_alloc_h

#include <stdlib.h>
#include <string.h>

/** \defgroup alloc High-tide allocator.
	\ingroup utils
*/
//@{

#ifndef DEBUG_QF_MEMORY
/**	High-tide structure allocator for use in linked lists.

	Using a free-list with the name of \c free_NAME, return a single element.
	The type of the element must be a structure with a field named \c next.
	When the free-list is empty, memory is claimed from the system in blocks.
	elements may be returned to the pool by linking them into the free-list.

	\param s		The number of structures in the block.
	\param t		The structure type.
	\param n		The \c NAME portion of the \c free_NAME free-list.
	\param v		The destination of the pointer to the allocated
					element. The contents of the allocated element will be
					memset to 0.

	\hideinitializer
*/
#define ALLOC(s, t, n, v)							\
	do {											\
		if (!free_##n) {							\
			int         i;							\
			free_##n = malloc ((s) * sizeof (t));	\
			for (i = 0; i < (s) - 1; i++)			\
				free_##n[i].next = &free_##n[i + 1];\
			free_##n[i].next = 0;					\
		}											\
		v = free_##n;								\
		free_##n = free_##n->next;					\
		memset (v, 0, sizeof (*v));					\
	} while (0)

/** Free a block allocated by #ALLOC

	\param n		The \c NAME portion of the \c free_NAME free-list.
	\param p		The pointer to the block to be freed.

	\hideinitializer
*/
#define FREE(n, p)			\
	do {					\
		p->next = free_##n;	\
		free_##n = p->next;	\
	} while (0)
#else
#define ALLOC(s, t, n, v)								\
	do {												\
		__attribute__((unused)) t **dummy = &free_##n;	\
		v = (t *) calloc (1, sizeof (t));				\
	} while (0)

#define FREE(n, p)			do { free (p); } while (0)
#endif

//@}

#endif//__QF_alloc_h
