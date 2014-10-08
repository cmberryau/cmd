/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: meshtable.h
 * Date: 8th of December, 2009.
 * Author(s): Christopher Berry.
 * Description: meshtable header file
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef MESHTABLE_H
#define MESHTABLE_H

#include "mesh.h"
#include "background3d.h"
#include "unitmesh.h"
#include "materialtable.h"

#define MESH_REF_DEFAULT 0

/* Map tile defines */
#define MESH_REF_MAP_TILE	1

/* Unit mesh defines */
#define MESH_REF_UNIT_HEAVY 2
#define MESH_REF_UNIT_GATHERER 3

/* Cursor mesh defines */
#define MESH_REF_CURSOR_0	4

/* Background mesh defines */
#define MESH_REF_BG_0		5
#define MESH_REF_BG_1		6

class meshtable_c{
	private:
		materialtable_c * materialtable;
		mesh_c * meshes[MAX_MESHES];
		int num_meshes;

public:
		mesh_c * get_default_mesh();
		mesh_c * get_mesh( int mesh_ref );
		mesh_c * get_map_tile_mesh();
		mesh_c * get_cursor_mesh();

		unitmesh_c * get_unit_heavy_mesh();
		unitmesh_c * get_unit_gatherer_mesh();

		background3d_c * get_background_mesh_00();
		background3d_c * get_background_mesh_01();
		
		materialtable_c * get_materialtable();
	
		meshtable_c();
};

#endif /* MESHTABLE_H */