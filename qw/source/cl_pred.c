/*
	cl_pred.c

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

#include <math.h>

#include "QF/console.h"
#include "QF/cvar.h"
#include "QF/keys.h"

#include "qw/bothdefs.h"
#include "compat.h"
#include "cl_ents.h"
#include "cl_pred.h"
#include "client.h"
#include "qw/pmove.h"

cvar_t     *cl_predict;
cvar_t     *cl_pushlatency;


void
CL_PredictUsercmd (player_state_t * from, player_state_t * to, usercmd_t *u,
				   qboolean clientplayer)
{
	if (!clientplayer) {
		if (VectorIsZero (from->pls.velocity)) {
			VectorCopy (from->pls.origin, to->pls.origin);
			VectorCopy (u->angles, to->viewangles);
			VectorCopy (from->pls.velocity, to->pls.velocity);
			return;
		}
	}

	// split up very long moves
	if (u->msec > 50) {
		player_state_t temp;
		usercmd_t   split;

		split = *u;
		split.msec /= 2;

		CL_PredictUsercmd (from, &temp, &split, clientplayer);
		CL_PredictUsercmd (&temp, to, &split, clientplayer);
		return;
	}

	VectorCopy (from->pls.origin, pmove.origin);
	VectorCopy (u->angles, pmove.angles);
	VectorCopy (from->pls.velocity, pmove.velocity);

	pmove.oldbuttons = from->oldbuttons;
	pmove.oldonground = from->oldonground;
	pmove.waterjumptime = from->waterjumptime;
	pmove.dead = cl.stats[STAT_HEALTH] <= 0;
	if (clientplayer)
		pmove.spectator = cl.spectator;
	else
		pmove.spectator = false;
	pmove.flying = cl.stats[STAT_FLYMODE];

	pmove.cmd = *u;

	PlayerMove ();
	to->waterjumptime = pmove.waterjumptime;
	to->oldbuttons = pmove.oldbuttons;	// Tonik
	to->oldonground = pmove.oldonground;
	VectorCopy (pmove.origin, to->pls.origin);
	VectorCopy (pmove.angles, to->viewangles);
	VectorCopy (pmove.velocity, to->pls.velocity);
	to->onground = onground;
	to->pls.weaponframe = from->pls.weaponframe;
}

void
CL_PredictMove (void)
{
	float       f;
	int         oldphysent, i;
	frame_t    *from, *to = NULL;

	if (cl_pushlatency->value > 0)
		Cvar_Set (cl_pushlatency, "0");

	if (cl.paused)
		return;

	// assume on ground unless prediction says different
	cl.onground = 0;

	cl.time = realtime - cls.latency - cl_pushlatency->value * 0.001;
	if (cl.time > realtime)
		cl.time = realtime;

	if (cl.intermission) {
		return;
	}

	if (!cl.validsequence)
		return;

	if (cls.netchan.outgoing_sequence - cls.netchan.incoming_sequence >=
		UPDATE_BACKUP - 1)
		return;

	VectorCopy (cl.viewangles, cl.simangles);
	cl.simangles[ROLL] = 0;						// FIXME @@@

	// this is the last frame received from the server
	from = &cl.frames[cls.netchan.incoming_sequence & UPDATE_MASK];

	if (!cl_predict->int_val) {
		VectorCopy (from->playerstate[cl.playernum].pls.velocity, cl.simvel);
		VectorCopy (from->playerstate[cl.playernum].pls.origin, cl.simorg);
		return;
	}

	// predict forward until cl.time <= to->senttime
	oldphysent = pmove.numphysent;
	CL_SetSolidPlayers (cl.playernum);

//	to = &cl.frames[cls.netchan.incoming_sequence & UPDATE_MASK];

	for (i = 1; i < UPDATE_BACKUP - 1 && cls.netchan.incoming_sequence + i <
		 cls.netchan.outgoing_sequence; i++) {
		to = &cl.frames[(cls.netchan.incoming_sequence + i) & UPDATE_MASK];
		CL_PredictUsercmd (&from->playerstate[cl.playernum],
						   &to->playerstate[cl.playernum], &to->cmd,
						   true);
		cl.onground = onground;
		if (to->senttime >= cl.time)
			break;
		from = to;
	}

	pmove.numphysent = oldphysent;

	if (i == UPDATE_BACKUP - 1 || !to)
		return;							// net hasn't deliver packets in a
										// long time...

	// now interpolate some fraction of the final frame
	if (to->senttime == from->senttime)
		f = 0;
	else {
		f = (cl.time - from->senttime) / (to->senttime - from->senttime);
		f = bound (0, f, 1);
	}

	for (i = 0; i < 3; i++)
		if (fabs (from->playerstate[cl.playernum].pls.origin[i] -
				  to->playerstate[cl.playernum].pls.origin[i]) > 128) {
			// teleported, so don't lerp
			VectorCopy (to->playerstate[cl.playernum].pls.velocity, cl.simvel);
			VectorCopy (to->playerstate[cl.playernum].pls.origin, cl.simorg);
			return;
		}

	for (i = 0; i < 3; i++) {
		cl.simorg[i] = from->playerstate[cl.playernum].pls.origin[i] +
			f * (to->playerstate[cl.playernum].pls.origin[i] -
				   from->playerstate[cl.playernum].pls.origin[i]);
		cl.simvel[i] = from->playerstate[cl.playernum].pls.velocity[i] +
			f * (to->playerstate[cl.playernum].pls.velocity[i] -
				 from->playerstate[cl.playernum].pls.velocity[i]);
	}
}

void
CL_Prediction_Init_Cvars (void)
{
	cl_predict = Cvar_Get ("cl_predict", "1", CVAR_NONE, NULL,
						  "Set to enable client prediction");
	cl_pushlatency = Cvar_Get ("pushlatency", "-999", CVAR_NONE, NULL,
							   "How much prediction should the client make");
}
