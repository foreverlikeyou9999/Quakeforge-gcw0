/*
	options.c

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
#include <stdio.h>
#include <getopt.h>

#include "QF/dstring.h"

#include "options.h"

const char *this_program;

static struct option const long_options[] = {
	{"quiet", no_argument, 0, 'q'},
	{"verbose", no_argument, 0, 'v'},
	{"help", no_argument, 0, 'h'},
	{"version", no_argument, 0, 'V'},
	{"threads", required_argument, 0, 't'},
	{"minimal", no_argument, 0, 'm'},
	{"level", required_argument, 0, 'l'},
	{"file", required_argument, 0, 'f'},
	{NULL, 0, NULL, 0}
};

static const char *short_options =
	"q"		// quiet
	"v"		// verbose
	"h"		// help
	"V"		// version
	"t:"	// threads
	"m"		// minimal vis
	"l:"	// level
	"f:"	// file
	;


void
usage (int status)
{
	printf ("%s - QuakeForge PVS/PHS generation tool\n", this_program);
	printf ("Usage: %s [options]\n", this_program);
	printf (
		"Options:\n"
		"    -q, --quiet               Inhibit usual output\n"
		"    -v, --verbose             Display more output than usual\n"
		"    -h, --help                Display this help and exit\n"
		"    -V, --version             Output version information and exit\n"
		"    -t, --threads [num]       Number of threads to use\n"
		"    -m, --minimal             Perform minimal vis'ing\n"
		"    -l, --level [level]       Vis level to perform\n"
		"    -f, --file [bspfile]      BSP file to vis\n\n");
	exit (status);
}

int
DecodeArgs (int argc, char **argv)
{
	int         c;

	options.verbosity = 0;
	options.bspfile = NULL;
	options.threads = 1;

	while ((c = getopt_long (argc, argv, short_options, long_options, 0))
		   != EOF) {
		switch (c) {
			case 'q':					// quiet
				options.verbosity -= 1;
				break;
			case 'v':					// verbose
				options.verbosity += 1;
				break;
			case 'h':					// help
				usage (0);
				break;
			case 'V':					// version
				printf ("%s version %s\n", PACKAGE_NAME, PACKAGE_VERSION);
				exit (0);
				break;
			case 't':					// threads
				options.threads = atoi (optarg);
				break;
			case 'm':					// minimal vis
				options.minimal = true;
				break;
			case 'l':					// level
				options.level = atoi (optarg);
				break;
			case 'f':					// set filename
				options.bspfile = dstring_strdup (optarg);
				break;
			default:
				usage (1);
		}
	}
	if ((!options.bspfile) && argv[optind] && *(argv[optind]))
		options.bspfile = dstring_strdup (argv[optind++]);

	return optind;
}
