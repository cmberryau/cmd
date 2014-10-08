/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: background3d.h
 * Date: 10th May, 2010
 * Author(s): Christopher Berry
 * Description: Unit display mesh class source
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#include "unitmesh.h"

/**
 * Function shows back frame
 */
void unitmesh_c::show_back(){
	set_current_frame( BACK_FRAME );
}

/**
 * Function shows front frame
 */
void unitmesh_c::show_front(){
	set_current_frame( FRONT_FRAME );
}

/**
 * Parameterized constructors
 */
unitmesh_c::unitmesh_c( material_c *front, material_c *back ) : mesh_c( front ){
	mat[BACK_FRAME] = back;	// Set the back frame material
	num_frames = 2;			// Set the number of frames
}

unitmesh_c::unitmesh_c( material_c * front, material_c * back, u32 * dlistptr ) : mesh_c( front, dlistptr ){
	mat[BACK_FRAME] = back;	// Set the back frame material
	num_frames = 2;			// Set the number of frames
}