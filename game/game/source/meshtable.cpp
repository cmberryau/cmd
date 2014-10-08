/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: meshtable.cpp
 * Date: 8th of December, 2009.
 * Author(s): Christopher Berry.
 * Description: meshtable source file
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#include "meshtable.h"
#include "engine.h"

#include "default_dlist.h"

extern engine_c engine;

/**
 * Returns the default mesh
 */
mesh_c * meshtable_c::get_default_mesh(){
	return meshes[MESH_REF_DEFAULT];
}

/**
 * Returns the mesh requested
 */
mesh_c * meshtable_c::get_mesh( int mesh_ref ){
	return meshes[mesh_ref];
}

/**
 * Returns the map tile mesh
 */
mesh_c * meshtable_c::get_map_tile_mesh(){
	return meshes[MESH_REF_MAP_TILE];
}

/**
 * Returns the heavy unit mesh
 */
unitmesh_c * meshtable_c::get_unit_heavy_mesh(){
	return ( unitmesh_c * )meshes[MESH_REF_UNIT_HEAVY];
}

/**
 * Returns the gatherer unit mesh
 */
unitmesh_c * meshtable_c::get_unit_gatherer_mesh(){
	return ( unitmesh_c * )meshes[MESH_REF_UNIT_GATHERER];
}


/**
 * Returns the cursor mesh
 */
mesh_c * meshtable_c::get_cursor_mesh(){
	return meshes[MESH_REF_CURSOR_0];
}

/**
 * Returns the first background mesh
 */
background3d_c * meshtable_c::get_background_mesh_00(){
	return ( background3d_c * )meshes[MESH_REF_BG_0];
}

/**
 * Returns the second background mesh
 */
background3d_c * meshtable_c::get_background_mesh_01(){
	return ( background3d_c * )meshes[MESH_REF_BG_1];
}

/**
 * Returns the material table
 */
materialtable_c * meshtable_c::get_materialtable(){
	return materialtable;
}

/**
 * Default Creator
 * - Creates the default mesh
 * - Creates the meshes, associates with materials
 */
meshtable_c::meshtable_c(){
	/* Init the material table */
	materialtable = new materialtable_c();

	/* Start creating the meshes */
	num_meshes = 0;

	/* Start creating the default mesh */
	meshes[MESH_REF_DEFAULT] = new mesh_c( materialtable->get_default_material(), default_dlist );
	num_meshes++;
	/* Finish creating the default mesh */

	/* Start creating the map tile meshes */
	meshes[MESH_REF_MAP_TILE] = new mesh_c( materialtable->get_material( MAT_REF_TILE01_32_8 ), default_dlist );
	num_meshes++;
	/* Finish creating the map tile meshes */

	/* Begin creating the unit meshes */
	// Heavy Unit mesh
	meshes[MESH_REF_UNIT_HEAVY] = new unitmesh_c( materialtable->get_material( MAT_REF_UNIT_HEAVY_FRONT_32_8 ),
												  materialtable->get_material( MAT_REF_UNIT_HEAVY_BACK_32_8 ),
												  default_dlist );

	meshes[MESH_REF_UNIT_HEAVY]->set_bboard( true );
	num_meshes++;

	// Gatherer Unit mesh
	meshes[MESH_REF_UNIT_GATHERER] = new unitmesh_c( materialtable->get_material( MAT_REF_UNIT_GATHERER_FRONT_32_8 ),
												     materialtable->get_material( MAT_REF_UNIT_GATHERER_BACK_32_8 ),
												  default_dlist );

	meshes[MESH_REF_UNIT_GATHERER]->set_bboard( true );
	num_meshes++;

	/* Finish creating the unit meshes */

	/* Begin creating the cursor mesh */
	meshes[MESH_REF_CURSOR_0] = new mesh_c( materialtable->get_material( MAT_REF_CURSOR_0 ), default_dlist );
	num_meshes++;

	/* Finish creating the cursor mesh */

	/* Begin creating the background meshes */
	meshes[MESH_REF_BG_0] = new background3d_c( materialtable->get_material( MAT_REF_CORRUPT_BG00 ) );
	num_meshes++;

	meshes[MESH_REF_BG_1] = new background3d_c( materialtable->get_material( MAT_REF_CORRUPT_BG01 ) );
	num_meshes++;

	/* Finish creating the background meshes */

	/* Free the materials now that we have loaded them all */
	// TODO - Hardware does not like materials being free'd from RAM - weird.
	//materialtable->free_materials();
}