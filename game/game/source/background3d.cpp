/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: background3d.cpp
 * Date: 20th April, 2010
 * Author(s): Christopher Berry
 * Description: 3d background source file
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#include "background3d.h"
#include "background_dlist.h"
#include "engine.h"

/**
 * Updates the display list
 */
void background3d_c::updatedlist(){
	dlist[V0_UV] = TEXTURE_PACK( inttot16 ( u[V0] ), inttot16 ( v[V0] ) );
	dlist[V1_UV] = TEXTURE_PACK( inttot16 ( u[V1] ), inttot16 ( v[V1] ) );
	dlist[V2_UV] = TEXTURE_PACK( inttot16 ( u[V2] ), inttot16 ( v[V2] ) );
	dlist[V3_UV] = TEXTURE_PACK( inttot16 ( u[V3] ), inttot16 ( v[V3] ) );
}

/**
 * Set the ms per step in the u direction
 */
void background3d_c::set_ms_per_step_u( int ms ){
	ms_per_step_u = ms;
}

/**
 * Set the ms per step in the v direction
 */
void background3d_c::set_ms_per_step_v( int ms ){
	ms_per_step_v = ms;
}

/**
 * Single step of the texture in the u
 */
void background3d_c::single_step_u(){
	if( !active ){
		return;
	}

	if( step_u == max ){
		u[V0] = 0;
		u[V1] = max;
		u[V2] = max;
		u[V3] = 0;

		step_u=0;
	}
	u[V0]++;
	u[V1]++;
	u[V2]++;
	u[V3]++;
	
	step_u++;

	/* Update the display list */
	updatedlist();
}

/**
 * Single step of the texture in the v
 */
void background3d_c::single_step_v(){
	if( !active ){
		return;
	}

	if( step_v == max ){
		v[V0] = max;
		v[V1] = max;
		v[V2] = 0;
		v[V3] = 0;

		step_v=0;
	}
	v[V0]++;
	v[V1]++;
	v[V2]++;
	v[V3]++;	
	
	step_v++;

	/* Update the display list */
	updatedlist();
}

/**
 * Default creator
 */
background3d_c::background3d_c( material_c * matptr ) : mesh_c( matptr ){
	int array_size = sizeof( background_dlist ) / sizeof( u32 );
	dlist = (u32*)malloc( array_size*sizeof(u32) );
	memcpy( dlist, background_dlist, array_size*sizeof(u32) );

	max = DEFAULT_BACKGROUND3D_MAXUV;
	step_u = max;
	step_v = max;

	u[V0] = 0;
	u[V1] = max;
	u[V2] = max;
	u[V3] = 0;

	v[V0] = max;
	v[V1] = max;
	v[V2] = 0;
	v[V3] = 0;

	ms_per_step_u = DEFAULT_MS_PER_STEP;
	ms_per_step_v = DEFAULT_MS_PER_STEP;

	active = true;

	cam_lock = true;
	bboard = true;

	/* Update the display list */
	updatedlist();
}
