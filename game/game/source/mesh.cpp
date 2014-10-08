/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: mesh.cpp
 * Date: 8th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry
 * Description: mesh class source
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

// header file
#include "mesh.h"
#include "engine.h"

extern engine_c engine;

/**
 * Setter for the current frame
 */
void mesh_c::set_current_frame( int frame ){
	sel_mat_frame = frame;	// Set the frame
}

/**
 * Adds a frame to the list for animation
 * returns -1 on error
 * returns -2 on too many frames
 * returns new frame position on success 
 */
int mesh_c::add_frame( material_c * matptr ){

	if( num_frames >= MAX_FRAMES ){ // Make sure we haven't exceeded the max frames already
		return TOO_MANY_FRAMES;
	}

	if( !matptr ){	// Check to make sure the pointer is not null
		return MESH_ERROR;
	}

	mat[num_frames] = matptr;	// Assign the pointer at the next available position

	num_frames++;			// Increment the number of frames
	return num_frames-1;	// Return the position of the new frame
}

/**
 * Returns the current frame
 */
int mesh_c::get_current_frame(){
	return sel_mat_frame;
}

/**
 * Returns the number of frames
 */
int mesh_c::get_num_frames(){
	return num_frames;
}

/**
 * This function draws the mesh
 */
void mesh_c::draw(){
	// Push the matrix down
	glPushMatrix();
	
	// Set the default color
	glColor3b( 255, 255, 255 );

	// Set alpha
	glPolyFmt( POLY_ID( 1 ) | POLY_ALPHA( alpha ) | POLY_CULL_NONE );

	// Check bboard mode
	if( bboard ){
		// Undo the camera rotation
		glRotateYi( -engine.get_camera().rotation.y );
		glRotateXi( -engine.get_camera().rotation.x );
	}

	// Rotate the mesh
	glRotateXi( r_x );
	glRotateYi( r_y );
	glRotateZi( r_z );

	// Check camera lock mode
	if( cam_lock ){
		// Apply the camera translation
		glTranslate3f32( -engine.get_camera().x, -engine.get_camera().y , inttof32( 0 ) );
	}

	// Translate the mesh
	glTranslate3f32( x, y, z );
	
	// If the material is null
	if( mat[sel_mat_frame] == null ){
		// TODO Error material should go here
	}else{
		// Enable the particular texture
		mat[sel_mat_frame]->use();
		
		// Call the display list
		if( !dlist ){
			// display list not loaded
		}else{
			glCallList( dlist );
		}
	}

	// Pop the matrix
	glPopMatrix(1);
}



/**
 * Alpha setter
 */
void mesh_c::set_alpha( int alpha ){
	this->alpha = alpha;
}

/**
 * Alpha getter
 */
int mesh_c::get_alpha(){
	return alpha;
}

/**
 * Setter for billboard mode
 */
void mesh_c::set_bboard( bool enable ){
	bboard = enable;
}

/**
 * Setter for camlock mode
 */
void mesh_c::set_cam_lock( bool enable ){
	cam_lock = enable;
}

/**
 * Absolute rotation in X
 */
void mesh_c::rotateXi( int32 x ){
	r_x = x;
}

/**
 * Absolute rotation in Y
 */
void mesh_c::rotateYi( int32 y ){
	r_y = y;
}

/**
 * Absolute rotation in Z
 */
void mesh_c::rotateZi( int32 z ){
	r_z = z;
}

/**
 * Relative rotation in X
 */
void mesh_c::rel_rotateXi( int32 x ){
	r_x += x;
}

/**
 * Relative rotation in Y
 */
void mesh_c::rel_rotateYi( int32 y ){
	r_y += y;
}

/**
 * Relative rotation in Z
 */
void mesh_c::rel_rotateZi( int32 z ){
	r_z += z;
}

/**
 * Absolute translation
 */
void mesh_c::translatei32( int32 x, int32 y, int32 z ){
	this->x = x;
	this->y = y;
	this->z = z;
}

/**
 * Relative translation
 */
void mesh_c::rel_translatei32( int32 x, int32 y, int32 z ){
	this->x += x;
	this->y += y;
	this->z += z;
}

/**
 * Mesh Creators
 */

/**
 * Static members
 */

/**
 * Directed constructor
 * - Parameterized material pointer
 */
mesh_c::mesh_c( material_c * matptr ){
	mat[DEFAULT_FRAME] = matptr;
	dlist = NULL;

	bboard = false;
	hidden = false;

	alpha = DEFAULT_MESH_ALPHA; // Set default alpha

	// Set default translation values
	x = 0;
	y = x;
	z = y;

	// Set default rotation values
	r_x = 0;
	r_y = r_x;
	r_z = r_y;	

	// Set default frame values
	sel_mat_frame = DEFAULT_FRAME;
	num_frames = 1;
}

/**
 * Directed constructor
 * - Parameterized material pointer
 * - Parameterized display list pointer
 */
mesh_c::mesh_c( material_c * matptr, u32 * dlistptr ){
	mat[DEFAULT_FRAME] = matptr;
	dlist = dlistptr;

	cam_lock = false;
	bboard = false;
	hidden = false;

	alpha = DEFAULT_MESH_ALPHA; // Set default alpha

	// Set default translation values
	x = 0;
	y = x;
	z = y;

	// Set default rotation values
	r_x = 0;
	r_y = r_x;
	r_z = r_y;	

	// Set default frame values
	sel_mat_frame = DEFAULT_FRAME;
	num_frames = 1;
}

/**
 * Default destructor
 */
mesh_c::~mesh_c(){
	/* Free the display list */
	//free( dlist );
}
