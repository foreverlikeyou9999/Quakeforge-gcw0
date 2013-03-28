/*
	r_part.c

	Interface for particles

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

#include "QF/cvar.h"
#include "QF/qargs.h"
#include "QF/render.h"
#include "QF/sys.h"

#include "compat.h"
#include "r_internal.h"

unsigned int	r_maxparticles, numparticles;
particle_t	   *active_particles, *free_particles, *particles, **freeparticles;
vec3_t			r_pright, r_pup, r_ppn;

/*
  R_MaxParticlesCheck

  Misty-chan: Dynamically change the maximum amount of particles on the fly.
  Thanks to a LOT of help from Taniwha, Deek, Mercury, Lordhavoc, and lots of
  others.
*/
void
R_MaxParticlesCheck (cvar_t *r_particles, cvar_t *r_particles_max)
{
/*
	Catchall. If the user changed the setting to a number less than zero *or*
	if we had a wacky cfg get past the init code check, this will make sure we
	don't have problems. Also note that grabbing the var->int_val is IMPORTANT:
	Prevents a segfault since if we grabbed the int_val of r_particles_max
	we'd sig11 right here at startup.
*/
	if (r_particles && r_particles->int_val)
		r_maxparticles = r_particles_max ? r_particles_max->int_val : 0;
	else
		r_maxparticles = 0;

/*
	Be very careful the next time we do something like this. calloc/free are
	IMPORTANT and the compiler doesn't know when we do bad things with them.
*/
	if (particles)
		free (particles);
	if (freeparticles)
		free (freeparticles);

	particles = 0;
	freeparticles = 0;

	if (r_maxparticles) {
		particles = (particle_t *) calloc (r_maxparticles, sizeof (particle_t));
		freeparticles = (particle_t **) calloc (r_maxparticles,
												sizeof (particle_t *));
	}

	vr_funcs->R_ClearParticles ();

	if (r_init)
		vr_funcs->R_InitParticles ();
}

static int  ramp1[8] = { 0x6f, 0x6d, 0x6b, 0x69, 0x67, 0x65, 0x63, 0x61 };
static int  ramp2[8] = { 0x6f, 0x6e, 0x6d, 0x6c, 0x6b, 0x6a, 0x68, 0x66 };
static int  ramp3[8] = { 0x6d, 0x6b, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01 };

static inline float
slow_grav (void)
{
	return -vr_data.frametime * vr_data.gravity * 0.0375;
}

static inline float
grav (void)
{
	return -vr_data.frametime * vr_data.gravity * 0.05;
}

static inline float
fast_grav (void)
{
	return -vr_data.frametime * vr_data.gravity;
}

static inline void
add_vel (particle_t *part)
{
	VectorMultAdd (part->org, vr_data.frametime, part->vel, part->org);
}

static inline void
sub_slowgrav (particle_t *part)
{
	part->vel[2] -= slow_grav ();
}

static inline void
add_grav (particle_t *part)
{
	part->vel[2] += grav ();
}

static inline void
sub_grav (particle_t *part)
{
	part->vel[2] -= grav ();
}

static inline void
add_fastgrav (particle_t *part)
{
	part->vel[2] += fast_grav ();
}

static inline qboolean
add_ramp (particle_t *part, float time, int max)
{
	part->ramp += vr_data.frametime * time;
	if (part->ramp >= max) {
		part->die = -1;
		return true;
	}
	return false;
}

static inline qboolean
fade_alpha (particle_t *part, float time)
{
	part->alpha -= vr_data.frametime * time;
	if (part->alpha <= 0.0) {
		part->die = -1;
		return true;
	}
	return false;
}

static void
part_phys_static (particle_t *part)
{
	add_vel (part);
}

static void
part_phys_grav (particle_t *part)
{
	add_vel (part);
	add_grav (part);
}

static void
part_phys_fire (particle_t *part)
{
	if (add_ramp (part, 5.0, 6))
		return;
	add_vel (part);
	part->color = ramp3[(int) part->ramp];
	part->alpha = (6.0 - part->ramp) / 6.0;
	sub_grav (part);
}

static void
part_phys_explode (particle_t *part)
{
	if (add_ramp (part, 10.0, 8))
		return;
	add_vel (part);
	part->color = ramp1[(int) part->ramp];
	VectorMultAdd (part->vel, vr_data.frametime * 4.0, part->vel, part->vel);
	add_grav (part);
}

static void
part_phys_explode2 (particle_t *part)
{
	if (add_ramp (part, 15.0, 8))
		return;
	add_vel (part);
	part->color = ramp2[(int) part->ramp];
	VectorMultAdd (part->vel, vr_data.frametime, part->vel, part->vel);
	add_grav (part);
}

static void
part_phys_blob (particle_t *part)
{
	add_vel (part);
	VectorMultAdd (part->vel, vr_data.frametime * 4.0, part->vel, part->vel);
	add_grav (part);
}

static void
part_phys_blob2 (particle_t *part)
{
	add_vel (part);
	part->vel[0] -= part->vel[0] * vr_data.frametime * 4.0;
	part->vel[1] -= part->vel[1] * vr_data.frametime * 4.0;
	add_grav (part);
}

static void
part_phys_smoke (particle_t *part)
{
	if (fade_alpha (part, 0.4))
		return;
	add_vel (part);
	part->scale += vr_data.frametime * 4.0;
	//sub_slowgrav (part);
}

static void
part_phys_smokecloud (particle_t *part)
{
	if (fade_alpha (part, 0.55))
		return;
	add_vel (part);
	part->scale += vr_data.frametime * 50.0;
	sub_slowgrav (part);
}

static void
part_phys_bloodcloud (particle_t *part)
{
	if (fade_alpha (part, 0.25))
		return;
	add_vel (part);
	part->scale += vr_data.frametime * 4.0;
	add_grav (part);
}

static void
part_phys_fallfade (particle_t *part)
{
	if (fade_alpha (part, 1.0))
		return;
	add_vel (part);
	add_fastgrav (part);
}

static void
part_phys_fallfadespark (particle_t *part)
{
	if (add_ramp (part, 15.0, 8))
		return;
	if (fade_alpha (part, 1.0))
		return;
	part->color = ramp1[(int) part->ramp];
	add_vel (part);
	add_fastgrav (part);
}

static void
part_phys_flame (particle_t *part)
{
	if (fade_alpha (part, 0.125))
		return;
	add_vel (part);
	part->scale -= vr_data.frametime * 2.0;
}

static pt_phys_func part_phys[] = {
	part_phys_static,		// pt_static
	part_phys_grav,			// pt_grav
	part_phys_grav,			// pt_slowgrav
	part_phys_fire,			// pt_fire
	part_phys_explode,		// pt_explode
	part_phys_explode2,		// pt_explode2
	part_phys_blob,			// pt_blob
	part_phys_blob2,		// pt_blob2
	part_phys_smoke,		// pt_smoke
	part_phys_smokecloud,	// pt_smokecloud
	part_phys_bloodcloud,	// pt_bloodcloud
	part_phys_static,		// pt_fadespark
	part_phys_static,		// pt_fadespark2
	part_phys_fallfade,		// pt_fallfade
	part_phys_fallfadespark,// pt_fallfadespark
	part_phys_flame,		// pt_flame
};

pt_phys_func
R_ParticlePhysics (ptype_t type)
{
	if (type > pt_flame)
		Sys_Error ("R_ParticlePhysics: invalid particle type");
	return part_phys[type];
}
