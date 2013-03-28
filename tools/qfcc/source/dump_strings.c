/*
	dump_strings.c

	Dump progs strings.

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

#include "QF/progs.h"
#include "QF/sys.h"

#include "qfprogs.h"

void
dump_strings (progs_t *pr)
{
	int i = 0;
	char *s = pr->pr_strings;

	printf ("%d ", 0);
	while (i++ < pr->progs->numstrings) {
		switch (*s) {
			case 0:
				fputs ("\n", stdout);
				if (i < pr->progs->numstrings)
					printf ("%d ", i);
				break;
			case 9:
				fputs ("\\t", stdout);
				break;
			case 10:
				fputs ("\\n", stdout);
				break;
			case 13:
				fputs ("\\r", stdout);
				break;
			default:
				fputc (sys_char_map[(unsigned char)*s], stdout);
				break;
		}
		s++;
	}
}
