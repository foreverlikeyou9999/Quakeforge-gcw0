/*
	options.h

	command line options handling

	Copyright (C) 2002 Colin Thompson

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

#ifndef __options_h
#define __options_h

#include "QF/qtypes.h"

typedef struct {
	int			verbosity;		// 0=silent
	int			threads;
	int         novis;
	int         extrabit;
	int         attenuation;
	vec_t       extrascale;
	vec_t		distance;
	vec_t		range;
	vec_t       globallightscale;
	vec_t       noise;
	vec_t       cutoff;
	const char *lightsfilename;
	const char *properties_filename;
} options_t;

extern options_t options;
extern struct dstring_s *bspfile;
extern const char *this_program;

int DecodeArgs (int argc, char **argv);
void usage (int status);

#endif//__options_h