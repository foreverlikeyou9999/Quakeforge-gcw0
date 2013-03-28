/*
	trace.c

	(description)

	Copyright (C) 1996-1997  Id Software, Inc.
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

#ifdef HAVE_IO_H
# include <io.h>
#endif
#ifdef HAVE_STRING_H
# include <string.h>
#endif
#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif

#include <stdlib.h>

#include "QF/bspfile.h"
#include "QF/dstring.h"
#include "QF/mathlib.h"
#include "QF/qfplist.h"
#include "QF/qtypes.h"
#include "QF/quakefs.h"
#include "QF/script.h"
#include "QF/sys.h"

#include "light.h"
#include "threads.h"
#include "entities.h"
#include "options.h"
#include "properties.h"

entity_t *entities;
int num_entities;
static int max_entities;

/*
	ENTITY FILE PARSING

	If a light has a targetname, generate a unique style in the 32-63 range
*/

int numlighttargets;
const char *lighttargets[32];


static int
LightStyleForTargetname (const char *targetname, qboolean alloc)
{
	int		i;

	for (i = 0; i < numlighttargets; i++)
		if (!strcmp (lighttargets[i], targetname))
			return 32 + i;

	if (!alloc)
		return -1;

	lighttargets[i] = targetname;
	numlighttargets++;
	return numlighttargets - 1 + 32;
}

static void
MatchTargets (void)
{
	int			i, j;

	for (i = 0; i < num_entities; i++) {
		if (!entities[i].target || !entities[i].target[0])
			continue;

		for (j = 0; j < num_entities; j++)
			if (entities[j].targetname
				&& !strcmp (entities[j].targetname, entities[i].target)) {
				entities[i].targetent = &entities[j];
				// set up spotlight values for lighting code to use
				VectorSubtract (entities[i].targetent->origin,
								entities[i].origin, entities[i].spotdir);
				VectorNormalize (entities[i].spotdir);
				if (!entities[i].angle)
					entities[i].spotcone = -cos(20 * M_PI / 180);
				else
					entities[i].spotcone = -cos(entities[i].angle * M_PI / 360);
				break;
			}
		if (j == num_entities) {
			printf ("WARNING: entity at (%i,%i,%i) (%s) has unmatched "
					"target\n",
					(int) entities[i].origin[0], (int) entities[i].origin[1],
					(int) entities[i].origin[2], entities[i].classname);
			continue;
		}
		// set the style on the source ent for switchable lights
		if (entities[j].style) {
			char s[16];

			entities[i].style = entities[j].style;
			sprintf (s, "%i", entities[i].style);
			SetKeyValue (&entities[i], "style", s);
		}

		if (entities[i].spotcone >= 0) {
			VectorZero (entities[i].spotdir);
			entities[i].spotcone = 0;
		}
	}
}

static void
WriteLights (void)
{
	int         i;
	FILE       *f;
	entity_t   *e;

	if (!options.lightsfilename)
		return;
	printf ("building .lights file\n");
	f = fopen (options.lightsfilename, "wb");
	for (i = 0; i < num_entities; i++) {
		e = entities + i;
		if (e->light)
			fprintf(f, "%f %f %f %f %f %f %f %f %f %f %f %f %f %d\n",
					e->origin[0], e->origin[1], e->origin[2],
					e->falloff,
					e->color[0], e->color[1], e->color[2],
					e->subbrightness,
					e->spotdir[0], e->spotdir[1], e->spotdir[2],
					e->spotcone, e->lightoffset, e->style);
	}
	fclose (f);
}

void
LoadEntities (void)
{
	const char *key;
	double      vec[4];
	entity_t   *entity;
	epair_t    *epair;
	float       cutoff_range;
	float       intensity;
	plitem_t   *dict;
	script_t   *script;

	script = Script_New ();
	Script_Start (script, "ent data", bsp->entdata);

	// start parsing
	max_entities = num_entities = 0;
	entities = 0;

	// go through all the entities
	while (Script_GetToken (script, 1)) {
		// parse the opening brace
		if (strcmp (script->token->str, "{"))
			fprintf (stderr, "LoadEntities: found %s when expecting {\n",
					 script->token->str);

		if (num_entities == max_entities) {
			max_entities += 128;
			entities = realloc (entities, max_entities * sizeof (entity_t));
		}
		entity = &entities[num_entities];
		num_entities++;

		memset (entity, 0, sizeof (*entity));
		entity->color[0] = entity->color[1] = entity->color[2] = 1.0f;
		VectorCopy (entity->color, entity->color2);
		entity->falloff = DEFAULTFALLOFF * DEFAULTFALLOFF;
		entity->lightradius = 0;
		entity->lightoffset = LIGHTDISTBIAS;
		entity->attenuation = options.attenuation;

		dict = PL_NewDictionary ();

		// go through all the keys in this entity
		while (1) {
			// parse key
			if (!Script_GetToken (script, 1))
				fprintf (stderr, "LoadEntities: EOF without closing brace");
			if (!strcmp (script->token->str, "}"))
				break;
			key = strdup (script->token->str);

			// parse value
			// FIXME shouldn't cross line
			if (!Script_GetToken (script, 1))
				fprintf (stderr, "LoadEntities: EOF without closing brace");
			if (!strcmp (script->token->str, "}"))
				fprintf (stderr, "LoadEntities: closing brace without data");

			epair = calloc (1, sizeof (epair_t));
			epair->key = key;
			epair->value = strdup (script->token->str);
			epair->next = entity->epairs;
			entity->epairs = epair;

			PL_D_AddObject (dict, key, PL_NewString (script->token->str));

			if (!strcmp (key, "classname"))
				entity->classname = epair->value;
			else if (!strcmp (key, "target"))
				entity->target = epair->value;
			else if (!strcmp (key, "targetname"))
				entity->targetname = epair->value;
			else if (!strcmp (key, "origin")) {
				// scan into doubles, then assign
				// which makes it vec_t size independent
				if (sscanf (script->token->str, "%lf %lf %lf",
							&vec[0], &vec[1], &vec[2]) != 3)
					fprintf (stderr, "LoadEntities: not 3 values for origin");
				else
					VectorCopy (vec, entity->origin);
			}
		}

		if (options.verbosity > 1 && entity->targetname)
			printf ("%s %d %d\n", entity->targetname, entity->light,
					entity->style);

		// all fields have been parsed
		if (entity->classname && !strncmp (entity->classname, "light", 5)) {
			set_properties (entity, dict);
			if (!entity->light)
				entity->light = DEFAULTLIGHTLEVEL;
			if (!entity->noise)
				entity->noise = options.noise;
			if (!entity->persistence)
				entity->persistence = 1;
		}
		PL_Free (dict);

		if (entity->light) {
			// convert to subtraction to the brightness for the whole light,
			// so it will fade nicely, rather than being clipped off
			VectorScale (entity->color2,
						 entity->light * 16384.0 * options.globallightscale,
						 entity->color2);
			entity->color[0] *= entity->color2[0];
			entity->color[1] *= entity->color2[1];
			entity->color[2] *= entity->color2[2];

			if (entity->lightradius)
				entity->subbrightness = 1.0 / (entity->lightradius
											   * entity->lightradius
											   * entity->falloff
											   + LIGHTDISTBIAS);
			if (entity->subbrightness < (1.0 / 1048576.0))
				entity->subbrightness = (1.0 / 1048576.0);

			intensity = entity->light;
			if (intensity < 0)
				intensity = -intensity;
			switch (entity->attenuation) {
				case LIGHT_RADIUS:
					// default radius is intensity (same as LIGHT_LINEAR)
					if (!entity->radius)
						entity->radius = intensity;
					break;
				case LIGHT_LINEAR:
					// don't allow radius to be greater than intensity
					if (entity->radius > intensity || entity->radius == 0)
						entity->radius = intensity;
					break;
				case LIGHT_REALISTIC:
					if (options.cutoff) {
						// approximate limit for faster lighting
						cutoff_range = sqrt (intensity / options.cutoff);
						if (!entity->radius || cutoff_range < entity->radius)
							entity->radius = cutoff_range;
					}
					break;
				case LIGHT_INVERSE:
					if (options.cutoff) {
						// approximate limit for faster lighting
						cutoff_range = intensity / options.cutoff;
						if (!entity->radius || cutoff_range < entity->radius)
							entity->radius = cutoff_range;
					}
					break;
				case LIGHT_NO_ATTEN:
					break;
				case LIGHT_LH:
					break;
			}
		}

		if (entity->classname && !strcmp (entity->classname, "light")) {
			if (entity->targetname && entity->targetname[0]
				&& !entity->style) {
				char s[16];

				entity->style = LightStyleForTargetname (entity->targetname,
														 true);
				sprintf (s, "%i", entity->style);
				SetKeyValue (entity, "style", s);
			}
		}
	}

	if (options.verbosity >= 0)
		printf ("%d entities read\n", num_entities);

	MatchTargets ();

	WriteLights();

	novislights = (entity_t **)calloc (num_entities, sizeof (entity_t *));
}

const char *
ValueForKey (entity_t *ent, const char *key)
{
	epair_t		*ep;

	for (ep = ent->epairs; ep; ep = ep->next)
		if (!strcmp (ep->key, key))
			return ep->value;
	return "";
}

void
SetKeyValue (entity_t *ent, const char *key, const char *value)
{
	epair_t		*ep;

	for (ep = ent->epairs; ep; ep = ep->next)
		if (!strcmp (ep->key, key)) {
			ep->value = strdup (value);
			return;
		}
	ep = malloc (sizeof (*ep));
	ep->next = ent->epairs;
	ent->epairs = ep;
	ep->key = strdup (key);
	ep->value = strdup (value);
}

float
FloatForKey (entity_t *ent, const char *key)
{
	const char*k;

	k = ValueForKey (ent, key);
	return atof (k);
}

entity_t *
FindEntityWithKeyPair (const char *key, const char *value)
{
	entity_t   *ent;
	epair_t    *ep;
	int         i;

	for (i = 0; i < num_entities; i++) {
		ent = &entities[i];
		for (ep = ent->epairs; ep; ep = ep->next) {
			if (!strcmp (ep->key, key)) {
				if (!strcmp (ep->value, value))
					return ent;
				break;
			}
		}
	}
	return 0;
}

void
GetVectorForKey (entity_t *ent, const char *key, vec3_t vec)
{
	const char *k;

	k = ValueForKey (ent, key);
	sscanf (k, "%f %f %f", &vec[0], &vec[1], &vec[2]);
}

void
WriteEntitiesToString (void)
{
	dstring_t  *buf;
	epair_t		*ep;
	int			i;

	buf = dstring_newstr ();

	if (options.verbosity >= 0)
		printf ("%i switchable light styles\n", numlighttargets);

	for (i = 0; i < num_entities; i++) {
		ep = entities[i].epairs;
		if (!ep)
			continue;		// ent got removed

		dstring_appendstr (buf, "{\n");

		for (ep = entities[i].epairs; ep; ep = ep->next) {
			dasprintf (buf, "\"%s\" \"%s\"\n", ep->key, ep->value);
		}
		dstring_appendstr (buf, "}\n");
	}
	BSP_AddEntities (bsp, buf->str, buf->size);
}
