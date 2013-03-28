/*
	client.h

	Client definitions

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

#ifndef _CL_INPUT_H
#define _CL_INPUT_H

#include "QF/input.h"

#include "qw/protocol.h"

void CL_Input_Init (void);
void CL_Input_Init_Cvars (void);
void CL_ClearStates (void);
void CL_SendCmd (void);
void CL_SendMove (usercmd_t *cmd);

void CL_ClearState (void);

void CL_ReadPackets (void);

int  CL_ReadFromServer (void);
void CL_WriteToServer (usercmd_t *cmd);
void CL_BaseMove (usercmd_t *cmd);

float CL_KeyState (kbutton_t *key);

extern kbutton_t   in_left, in_right, in_forward, in_back;
extern kbutton_t   in_lookup, in_lookdown, in_moveleft, in_moveright;
extern kbutton_t   in_use, in_jump, in_attack;
extern kbutton_t   in_up, in_down;
extern int         in_impulse;

#endif
