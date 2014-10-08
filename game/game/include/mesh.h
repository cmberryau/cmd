/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: mesh.h
 * Date: 8th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry
 * Description: mesh class header
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef MESH_H
#define MESH_H

#include <nds.h>

#include "types.h"
#include "material.h"

#define MAX_MESHES 30
#define DEFAULT_MESH_ALPHA	31

#define DEFAULT_FRAME 0
#define MAX_FRAMES 10

#define TOO_MANY_FRAMES -2
#define MESH_ERROR -1

class mesh_c{
	protected:
		bool cam_lock;			// Locked to camera translation
		bool bboard;			// Billboard mode
		bool hidden;			// Hidden or not

		int32 x, y, z;			// Relative position information
		int32 r_x, r_y, r_z;	// Relative rotation information
		int alpha;				// Alpha information

		u32 * dlist;						// Geometry information
		material_c * mat[MAX_FRAMES];		// Material information
		int sel_mat_frame;			// Selected material frame
		int num_frames;			// Number of frames

	public:
		void load();			// Load mesh and material
		void unload();			// Unload mesh and material

		// Absolute translation
		void translatei32( int32 x, int32 y, int32 z ); 

		// Relative translation
		void rel_translatei32( int32 x, int32 y, int32 z ); 

		// Absolute rotation
		void rotateXi( int32 x );
		void rotateYi( int32 y );
		void rotateZi( int32 z );

		// Relative rotation
		void rel_rotateXi( int32 x );
		void rel_rotateYi( int32 y );
		void rel_rotateZi( int32 z );

		// Alpha accessors
		void set_alpha( int alpha );
		int get_alpha();

		// Material frame accessors and mutators
		// TODO Complete these methods
		void set_current_frame( int frame );			// Set the current frame
		int add_frame( material_c * matptr );	// Add a frame - returns the position
		int get_current_frame();				// Returns the position of the current frame
		int get_num_frames();					// Gets the number of frames currently added

		void set_cam_lock( bool enable );	// Setter for camlock mode
		void set_bboard( bool enable );		// Setter for bboard mode

		void draw();// Draw the mesh

		mesh_c( material_c * matptr ); // Directed constructor
		mesh_c( material_c * matptr, u32 * dlistptr ); // Directed constructor

		mesh_c();	// Creator
		~mesh_c();	// Destructor
};

#endif /* MESH_H */