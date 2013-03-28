/*
	vid_render_glsl.c

	GLSL version of the renderer

	Copyright (C) 2012 Bill Currie <bill@taniwha.org>

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
#include "glsl/namehack.h"

#include "QF/plugin/general.h"
#include "QF/plugin/vid_render.h"

#include "QF/GLSL/qf_vid.h"

#include "mod_internal.h"
#include "r_internal.h"

#include "glsl/namehack.h"

static vid_model_funcs_t model_funcs = {
	glsl_Mod_LoadExternalTextures,
	glsl_Mod_LoadLighting,
	glsl_Mod_SubdivideSurface,
	glsl_Mod_ProcessTexture,

	Mod_LoadIQM,
	Mod_LoadAliasModel,
	Mod_LoadSpriteModel,

	glsl_Mod_MakeAliasModelDisplayLists,
	glsl_Mod_LoadSkin,
	glsl_Mod_FinalizeAliasModel,
	glsl_Mod_LoadExternalSkins,
	glsl_Mod_IQMFinish,
	0,
	glsl_Mod_SpriteLoadTexture,

	Skin_SetColormap,
	Skin_SetSkin,
	glsl_Skin_SetupSkin,
	Skin_SetTranslation,
	glsl_Skin_ProcessTranslation,
	glsl_Skin_InitTranslations,
};

vid_render_funcs_t glsl_vid_render_funcs = {
	glsl_Draw_Init,
	glsl_Draw_Character,
	glsl_Draw_String,
	glsl_Draw_nString,
	glsl_Draw_AltString,
	glsl_Draw_ConsoleBackground,
	glsl_Draw_Crosshair,
	glsl_Draw_CrosshairAt,
	glsl_Draw_TileClear,
	glsl_Draw_Fill,
	glsl_Draw_TextBox,
	glsl_Draw_FadeScreen,
	glsl_Draw_BlendScreen,
	glsl_Draw_CachePic,
	glsl_Draw_UncachePic,
	glsl_Draw_MakePic,
	glsl_Draw_DestroyPic,
	glsl_Draw_PicFromWad,
	glsl_Draw_Pic,
	glsl_Draw_Picf,
	glsl_Draw_SubPic,

	glsl_SCR_UpdateScreen,
	SCR_DrawRam,
	SCR_DrawTurtle,
	SCR_DrawPause,
	glsl_SCR_CaptureBGR,
	glsl_SCR_ScreenShot,
	SCR_DrawStringToSnap,

	glsl_Fog_Update,
	glsl_Fog_ParseWorldspawn,

	glsl_R_Init,
	glsl_R_ClearState,
	glsl_R_LoadSkys,
	glsl_R_NewMap,
	R_AddEfrags,
	R_RemoveEfrags,
	R_EnqueueEntity,
	glsl_R_LineGraph,
	R_AllocDlight,
	R_AllocEntity,
	glsl_R_RenderView,
	R_DecayLights,
	glsl_R_ViewChanged,
	glsl_R_ClearParticles,
	glsl_R_InitParticles,
	glsl_SCR_ScreenShot_f,
	glsl_r_easter_eggs_f,
	glsl_r_particles_style_f,
	0,
	&model_funcs
};

static void
glsl_vid_render_init (void)
{
	vr_data.vid->set_palette = GLSL_SetPalette;
	vr_data.vid->init_gl = GLSL_Init_Common;
	vr_data.vid->load_gl ();
	vr_funcs = &glsl_vid_render_funcs;
	m_funcs = &model_funcs;
}

static void
glsl_vid_render_shutdown (void)
{
}

static general_funcs_t plugin_info_general_funcs = {
	glsl_vid_render_init,
	glsl_vid_render_shutdown,
};

static general_data_t plugin_info_general_data;

static plugin_funcs_t plugin_info_funcs = {
	&plugin_info_general_funcs,
	0,
	0,
	0,
	0,
	0,
	&glsl_vid_render_funcs,
};

static plugin_data_t plugin_info_data = {
	&plugin_info_general_data,
	0,
	0,
	0,
	0,
	0,
	&vid_render_data,
};

static plugin_t plugin_info = {
	qfp_snd_render,
	0,
	QFPLUGIN_VERSION,
	"0.1",
	"GLSL Renderer",
	"Copyright (C) 1996-1997  Id Software, Inc.\n"
	"Copyright (C) 1999-2012  contributors of the QuakeForge project\n"
	"Please see the file \"AUTHORS\" for a list of contributors",
	&plugin_info_funcs,
	&plugin_info_data,
};

PLUGIN_INFO(vid_render, glsl)
{
	return &plugin_info;
}
