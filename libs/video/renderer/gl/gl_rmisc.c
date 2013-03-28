/*
	gl_rmisc.c

	(description)

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
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#define NH_DEFINE
#include "namehack.h"

#ifdef HAVE_STRING_H
# include <string.h>
#endif
#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif

#if defined(_WIN32) && defined(HAVE_MALLOC_H)
#include <malloc.h>
#endif

#include <stdlib.h>
#include <stdio.h>

#include "QF/cmd.h"
#include "QF/cvar.h"
#include "QF/draw.h"
#include "QF/quakefs.h"
#include "QF/render.h"
#include "QF/screen.h"
#include "QF/skin.h"
#include "QF/sys.h"
#include "QF/vid.h"
#include "QF/GL/defines.h"
#include "QF/GL/funcs.h"
#include "QF/GL/qf_rmain.h"
#include "QF/GL/qf_rsurf.h"
#include "QF/GL/qf_textures.h"
#include "QF/GL/qf_vid.h"

#include "mod_internal.h"
#include "r_internal.h"
#include "varrays.h"

/*
	R_Envmap_f

	Grab six views for environment mapping tests
*/
static void
R_Envmap_f (void)
{
	byte        buffer[256 * 256 * 4];

	qfglDrawBuffer (GL_FRONT);
	qfglReadBuffer (GL_FRONT);
	gl_envmap = true;

	r_refdef.vrect.x = 0;
	r_refdef.vrect.y = 0;
	r_refdef.vrect.width = 256;
	r_refdef.vrect.height = 256;

	r_refdef.viewangles[0] = 0;
	r_refdef.viewangles[1] = 0;
	r_refdef.viewangles[2] = 0;
	gl_R_RenderView ();
	qfglReadPixels (0, 0, 256, 256, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	QFS_WriteFile ("env0.rgb", buffer, sizeof (buffer));

	r_refdef.viewangles[1] = 90;
	gl_R_RenderView ();
	qfglReadPixels (0, 0, 256, 256, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	QFS_WriteFile ("env1.rgb", buffer, sizeof (buffer));

	r_refdef.viewangles[1] = 180;
	gl_R_RenderView ();
	qfglReadPixels (0, 0, 256, 256, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	QFS_WriteFile ("env2.rgb", buffer, sizeof (buffer));

	r_refdef.viewangles[1] = 270;
	gl_R_RenderView ();
	qfglReadPixels (0, 0, 256, 256, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	QFS_WriteFile ("env3.rgb", buffer, sizeof (buffer));

	r_refdef.viewangles[0] = -90;
	r_refdef.viewangles[1] = 0;
	gl_R_RenderView ();
	qfglReadPixels (0, 0, 256, 256, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	QFS_WriteFile ("env4.rgb", buffer, sizeof (buffer));

	r_refdef.viewangles[0] = 90;
	r_refdef.viewangles[1] = 0;
	gl_R_RenderView ();
	qfglReadPixels (0, 0, 256, 256, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	QFS_WriteFile ("env5.rgb", buffer, sizeof (buffer));

	gl_envmap = false;
	qfglDrawBuffer (GL_BACK);
	qfglReadBuffer (GL_BACK);
	vid.end_rendering ();
}

void
gl_R_LoadSky_f (void)
{
	if (Cmd_Argc () != 2) {
		Sys_Printf ("loadsky <name> : load a skybox\n");
		return;
	}

	gl_R_LoadSkys (Cmd_Argv (1));
}

void
gl_R_Init (void)
{
	R_Init_Cvars ();
	gl_R_Particles_Init_Cvars ();

	Cmd_AddCommand ("timerefresh", gl_R_TimeRefresh_f,
					"Tests the current refresh rate for the current location");
	Cmd_AddCommand ("envmap", R_Envmap_f, "No Description");
	Cmd_AddCommand ("pointfile", gl_R_ReadPointFile_f,
					"Load a pointfile to determine map leaks");
	Cmd_AddCommand ("loadsky", gl_R_LoadSky_f, "Load a skybox");

	Draw_Init ();
	SCR_Init ();
	gl_R_InitBubble ();

	GDT_Init ();

	gl_texture_number = gl_R_InitGraphTextures (gl_texture_number);

	gl_texture_number = gl_Skin_Init_Textures (gl_texture_number);

	r_init = 1;
	gl_R_InitParticles ();
	gl_R_InitSprites ();
	gl_Fog_Init ();
	Skin_Init ();
}

static void
register_textures (model_t *model)
{
	int         i;
	texture_t  *tex;

	for (i = 0; i < model->numtextures; i++) {
		tex = model->textures[i];
		if (!tex)
			continue;
		gl_R_AddTexture (tex);
	}
}

void
gl_R_NewMap (model_t *worldmodel, struct model_s **models, int num_models)
{
	int         i;
	texture_t  *tex;

	for (i = 0; i < 256; i++)
		d_lightstylevalue[i] = 264;		// normal light value

	memset (&r_worldentity, 0, sizeof (r_worldentity));
	r_worldentity.model = worldmodel;

	R_FreeAllEntities ();

	// clear out efrags in case the level hasn't been reloaded
	for (i = 0; i < r_worldentity.model->numleafs; i++)
		r_worldentity.model->leafs[i].efrags = NULL;

	// Force a vis update
	r_viewleaf = NULL;
	R_MarkLeaves ();

	gl_R_ClearParticles ();

	GL_BuildLightmaps (models, num_models);

	// identify sky texture
	gl_mirrortexturenum = -1;
	gl_R_ClearTextures ();
	for (i = 0; i < r_worldentity.model->numtextures; i++) {
		tex = r_worldentity.model->textures[i];
		if (!tex)
			continue;
		if (!strncmp (tex->name, "sky", 3)) {
			gl_R_InitSky (tex);
		}
		if (!strncmp (tex->name, "window02_1", 10))
			gl_mirrortexturenum = i;
	}

	gl_R_InitSurfaceChains (r_worldentity.model);
	gl_R_AddTexture (r_notexture_mip);
	register_textures (r_worldentity.model);
	for (i = 0; i < num_models; i++) {
		if (!models[i])
			continue;
		if (*models[i]->name == '*')
			continue;
		if (models[i] != r_worldentity.model && models[i]->type == mod_brush)
			register_textures (models[i]);
	}
}

void
gl_R_ViewChanged (float aspect)
{
}

/*
  R_TimeRefresh_f

  For program optimization
  LordHavoc: improved appearance and accuracy of timerefresh
*/
void
gl_R_TimeRefresh_f (void)
{
	double      start, stop, time;
	int         i;

	vid.end_rendering ();

	start = Sys_DoubleTime ();
	for (i = 0; i < 128; i++) {
		r_refdef.viewangles[1] = i * (360.0 / 128.0);
		gl_R_RenderView ();
		vid.end_rendering ();
	}

	stop = Sys_DoubleTime ();
	time = stop - start;
	Sys_MaskPrintf (SYS_DEV, "%f seconds (%f fps)\n", time, 128 / time);
}
