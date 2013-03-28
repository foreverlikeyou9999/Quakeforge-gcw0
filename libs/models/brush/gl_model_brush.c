/*
	gl_model_brush.c

	gl support routines for model loading and caching

	Copyright (C) 1996-1997  Id Software, Inc.

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
// models are the only shared resource between a client and server running
// on the same machine.

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef HAVE_STRING_H
# include <string.h>
#endif
#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif

#include "QF/cvar.h"
#include "QF/dstring.h"
#include "QF/image.h"
#include "QF/qendian.h"
#include "QF/quakefs.h"
#include "QF/sys.h"
#include "QF/va.h"
#include "QF/GL/qf_textures.h"

#include "compat.h"
#include "mod_internal.h"
#include "r_internal.h"


void
gl_Mod_ProcessTexture (texture_t *tx)
{
	char		name[32];

	if (!strncmp (tx->name, "sky", 3))
		return;
	snprintf (name, sizeof (name), "fb_%s", tx->name);
	tx->gl_fb_texturenum =
		Mod_Fullbright ((byte *) (tx + 1), tx->width, tx->height, name);
	tx->gl_texturenum =
		GL_LoadTexture (tx->name, tx->width, tx->height, (byte *) (tx + 1),
						true, false, 1);
}

static tex_t *
Mod_LoadAnExternalTexture (char * tname, char *mname)
{
	char		rname[32];
	tex_t	   *image;

	memcpy (rname, tname, strlen (tname) + 1);

	if (rname[0] == '*') rname[0] = '#';

	image = LoadImage (va ("textures/%.*s/%s", (int) strlen (mname + 5) - 4,
						   mname + 5, rname));
	if (!image)
		image = LoadImage (va ("maps/%.*s/%s",
								   (int) strlen (mname + 5) - 4,
								   mname + 5, rname));
//	if (!image)
//			image = LoadImage (va ("textures/bmodels/%s", rname));
	if (!image)
			image = LoadImage (va ("textures/%s", rname));
	if (!image)
			image = LoadImage (va ("maps/%s", rname));

	return image;
}

void
gl_Mod_LoadExternalTextures (model_t *mod)
{
	int			i;
	tex_t	   *base, *luma;
	texture_t  *tx;

	for (i = 0; i < mod->numtextures; i++) {
		tx = mod->textures[i];
		if (!tx)
			continue;

		if ((base = Mod_LoadAnExternalTexture (tx->name, mod->name))) {
			tx->gl_texturenum =
				GL_LoadTexture (tx->name, base->width, base->height,
								base->data, true, false,
								base->format > 2 ? base->format : 1);

			luma = Mod_LoadAnExternalTexture (va ("%s_luma", tx->name),
											  mod->name);
			if (!luma)
				luma = Mod_LoadAnExternalTexture (va ("%s_glow", tx->name),
												  mod->name);

			tx->gl_fb_texturenum = 0;

			if (luma) {
				tx->gl_fb_texturenum =
					GL_LoadTexture (va ("fb_%s", tx->name), luma->width,
									luma->height, luma->data, true, true,
									luma->format > 2 ? luma->format : 1);
			} else if (base->format < 3) {
				tx->gl_fb_texturenum =
					Mod_Fullbright (base->data, base->width, base->height,
									va ("fb_%s", tx->name));
			}
		}
	}
}

void
gl_Mod_LoadLighting (bsp_t *bsp)
{
	byte        d;
	byte       *in, *out, *data;
	dstring_t  *litfilename = dstring_new ();
	size_t      i;
	int         ver;

	dstring_copystr (litfilename, loadmodel->name);
	loadmodel->lightdata = NULL;
	if (mod_lightmap_bytes > 1) {
		// LordHavoc: check for a .lit file to load
		QFS_StripExtension (litfilename->str, litfilename->str);
		dstring_appendstr (litfilename, ".lit");
		data = (byte *) QFS_LoadHunkFile (litfilename->str);
		if (data) {
			if (data[0] == 'Q' && data[1] == 'L' && data[2] == 'I'
				&& data[3] == 'T') {
				ver = LittleLong (((int32_t *) data)[1]);
				if (ver == 1) {
					Sys_MaskPrintf (SYS_DEV, "%s loaded", litfilename->str);
					loadmodel->lightdata = data + 8;
					return;
				} else
					Sys_MaskPrintf (SYS_DEV,
									"Unknown .lit file version (%d)\n", ver);
			} else
				Sys_MaskPrintf (SYS_DEV, "Corrupt .lit file (old version?)\n");
		}
	}
	// LordHavoc: oh well, expand the white lighting data
	if (!bsp->lightdatasize) {
		dstring_delete (litfilename);
		return;
	}
	loadmodel->lightdata = Hunk_AllocName (bsp->lightdatasize
											* mod_lightmap_bytes,
										   litfilename->str);
	in = bsp->lightdata;
	out = loadmodel->lightdata;

	if (mod_lightmap_bytes > 1)
		for (i = 0; i < bsp->lightdatasize ; i++) {
			d = vid.gammatable[*in++];
			*out++ = d;
			*out++ = d;
			*out++ = d;
		}
	else
		for (i = 0; i < bsp->lightdatasize ; i++)
			*out++ = vid.gammatable[*in++];
	dstring_delete (litfilename);
}

msurface_t *warpface;


static void
BoundPoly (int numverts, float *verts, vec3_t mins, vec3_t maxs)
{
	float      *v;
	int         i, j;

	mins[0] = mins[1] = mins[2] = 9999;
	maxs[0] = maxs[1] = maxs[2] = -9999;
	v = verts;
	for (i = 0; i < numverts; i++)
		for (j = 0; j < 3; j++, v++) {
			if (*v < mins[j])
				mins[j] = *v;
			if (*v > maxs[j])
				maxs[j] = *v;
		}
}

static void
SubdividePolygon (int numverts, float *verts)
{
	float       frac, m, s, t;
	float       dist[64];
	float      *v;
	int         b, f, i, j, k;
	glpoly_t   *poly;
	vec3_t      mins, maxs;
	vec3_t      front[64], back[64];

	if (numverts > 60)
		Sys_Error ("numverts = %i", numverts);

	BoundPoly (numverts, verts, mins, maxs);

	for (i = 0; i < 3; i++) {
		m = (mins[i] + maxs[i]) * 0.5;
		m = gl_subdivide_size->value * floor (m / gl_subdivide_size->value +
											  0.5);
		if (maxs[i] - m < 8)
			continue;
		if (m - mins[i] < 8)
			continue;

		// cut it
		v = verts + i;
		for (j = 0; j < numverts; j++, v += 3)
			dist[j] = *v - m;

		// wrap cases
		dist[j] = dist[0];
		v -= i;
		VectorCopy (verts, v);

		f = b = 0;
		v = verts;
		for (j = 0; j < numverts; j++, v += 3) {
			if (dist[j] >= 0) {
				VectorCopy (v, front[f]);
				f++;
			}
			if (dist[j] <= 0) {
				VectorCopy (v, back[b]);
				b++;
			}
			if (dist[j] == 0 || dist[j + 1] == 0)
				continue;
			if ((dist[j] > 0) != (dist[j + 1] > 0)) {
				// clip point
				frac = dist[j] / (dist[j] - dist[j + 1]);
				for (k = 0; k < 3; k++)
					front[f][k] = back[b][k] = v[k] + frac * (v[3 + k] - v[k]);
				f++;
				b++;
			}
		}

		SubdividePolygon (f, front[0]);
		SubdividePolygon (b, back[0]);
		return;
	}

	poly = Hunk_Alloc (sizeof (glpoly_t) + (numverts - 4) * VERTEXSIZE *
					   sizeof (float));
	poly->next = warpface->polys;
	warpface->polys = poly;
	poly->numverts = numverts;
	for (i = 0; i < numverts; i++, verts += 3) {
		VectorCopy (verts, poly->verts[i]);
		s = DotProduct (verts, warpface->texinfo->vecs[0]);
		t = DotProduct (verts, warpface->texinfo->vecs[1]);
		poly->verts[i][3] = s;
		poly->verts[i][4] = t;
	}
}

/*
	Mod_SubdivideSurface

	Breaks a polygon up along axial 64 unit
	boundaries so that turbulent and sky warps
	can be done reasonably.
*/
void
gl_Mod_SubdivideSurface (msurface_t *fa)
{
	float      *vec;
	int         lindex, numverts, i;
	vec3_t      verts[64];

	warpface = fa;

	// convert edges back to a normal polygon
	numverts = 0;
	for (i = 0; i < fa->numedges; i++) {
		lindex = loadmodel->surfedges[fa->firstedge + i];

		if (lindex > 0)
			vec = loadmodel->vertexes[loadmodel->edges[lindex].v[0]].position;
		else
			vec = loadmodel->vertexes[loadmodel->edges[-lindex].v[1]].position;
		VectorCopy (vec, verts[numverts]);
		numverts++;
	}

	SubdividePolygon (numverts, verts[0]);
}
