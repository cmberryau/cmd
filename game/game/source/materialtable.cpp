/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: materialtable.cpp
 * Date: 18th of April, 2010.
 * Author(s): Christopher Berry
 * Description: material table class source
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#include "materialtable.h"

/**
 * Returns the default material
 */
material_c * materialtable_c::get_default_material(){
	return materials[MAT_REF_DEFAULT_32_8];
}

/**
 * Returns the material requested
 */
material_c * materialtable_c::get_material( int material_ref ){
	return materials[material_ref];
}

/**
 * Returns the full green material
 */
material_c * materialtable_c::get_full_green(){
	return materials[MAT_REF_FULL_GREEN];
}

/**
 * Frees the material objects in client memory space
 */
void materialtable_c::free_materials(){
	/* Unload materials from the client */
	materials[MAT_REF_DEFAULT_32_8]->unload_from_client();
	materials[MAT_REF_UNIT_DEMO_32_8]->unload_from_client();
}

/**
 * Default Creator
 * - Creates the default material
 * - Creates the series of materials
 */
materialtable_c::materialtable_c(){
	/* Start creating the default material */
	num_materials = 0;	// Set the current number of materials

	materials[MAT_REF_DEFAULT_32_8] = new material_c();  // Create the default material
	materials[MAT_REF_DEFAULT_32_8]->load();				   // Load the default material	
	num_materials++;
	/* Finish creating the default material */

	/* Begin creating the map tile materials */
	material_file_info_t file_info_map_tile_32_8;

	file_info_map_tile_32_8.tex = (u8*)tile01_tex_bin;
	file_info_map_tile_32_8.pal[0] = (u8*)tile01_pal_bin;
	file_info_map_tile_32_8.pal_len[0] = tile01_pal_bin_size;
	file_info_map_tile_32_8.num_pal = 1;

	materials[MAT_REF_TILE01_32_8] = new material_c( file_info_map_tile_32_8 );
	materials[MAT_REF_TILE01_32_8]->load();
	num_materials++;

	/* Finish creating the map tile materials */

	/* Begin creating the unit materials */
	material_file_info_t file_info_unit_demo_32_8;
	
	/* Create the file info struct */
	file_info_unit_demo_32_8.tex = (u8*)demo_tex_bin;
	file_info_unit_demo_32_8.pal[0] = (u8*)demo_pal_bin;
	file_info_unit_demo_32_8.pal_len[0] = demo_pal_bin_size;
	file_info_unit_demo_32_8.num_pal = 1;
	
	/* Create the material entry */
	materials[MAT_REF_UNIT_DEMO_32_8] = new material_c( file_info_unit_demo_32_8 );
	materials[MAT_REF_UNIT_DEMO_32_8]->load();
	num_materials++;

	// Heavy Front
	material_file_info_t file_info_unit_heavy_front_32_8;

	file_info_unit_heavy_front_32_8.tex = (u8*)heavy_front_tex_bin;
	file_info_unit_heavy_front_32_8.pal[0] = (u8*)heavy_front_pal_bin;
	file_info_unit_heavy_front_32_8.pal_len[0] = heavy_front_pal_bin_size;
	file_info_unit_heavy_front_32_8.num_pal = 1;

	materials[MAT_REF_UNIT_HEAVY_FRONT_32_8] = new material_c( file_info_unit_heavy_front_32_8 );
	materials[MAT_REF_UNIT_HEAVY_FRONT_32_8]->load();
	num_materials++;

	// Heavy Back
	material_file_info_t file_info_unit_heavy_back_32_8;

	file_info_unit_heavy_back_32_8.tex = (u8*)heavy_back_tex_bin;
	file_info_unit_heavy_back_32_8.pal[0] = (u8*)heavy_back_pal_bin;
	file_info_unit_heavy_back_32_8.pal_len[0] = heavy_back_pal_bin_size;
	file_info_unit_heavy_back_32_8.num_pal = 1;

	materials[MAT_REF_UNIT_HEAVY_BACK_32_8] = new material_c( file_info_unit_heavy_back_32_8 );
	materials[MAT_REF_UNIT_HEAVY_BACK_32_8]->load();
	num_materials++;

	// Gatherer Front
	material_file_info_t file_info_unit_gatherer_front_32_8;

	file_info_unit_gatherer_front_32_8.tex = (u8*)gatherer_front_tex_bin;
	file_info_unit_gatherer_front_32_8.pal[0] = (u8*)gatherer_front_pal_bin;
	file_info_unit_gatherer_front_32_8.pal_len[0] = gatherer_front_pal_bin_size;
	file_info_unit_gatherer_front_32_8.num_pal = 1;

	materials[MAT_REF_UNIT_GATHERER_FRONT_32_8] = new material_c( file_info_unit_gatherer_front_32_8 );
	materials[MAT_REF_UNIT_GATHERER_FRONT_32_8]->load();
	num_materials++;

	// Gatherer Back
	material_file_info_t file_info_unit_gatherer_back_32_8;

	file_info_unit_gatherer_back_32_8.tex = (u8*)gatherer_back_tex_bin;
	file_info_unit_gatherer_back_32_8.pal[0] = (u8*)gatherer_back_pal_bin;
	file_info_unit_gatherer_back_32_8.pal_len[0] = gatherer_back_pal_bin_size;
	file_info_unit_gatherer_back_32_8.num_pal = 1;

	materials[MAT_REF_UNIT_GATHERER_BACK_32_8] = new material_c( file_info_unit_gatherer_back_32_8 );
	materials[MAT_REF_UNIT_GATHERER_BACK_32_8]->load();
	num_materials++;

	/* Finish creating the unit materials */

	/* Begin creating the cursor materials */
	material_file_info_t file_info_cursor_tile_32_8;
	
	file_info_cursor_tile_32_8.tex = (u8*)cursor_tex_bin;
	file_info_cursor_tile_32_8.pal[0] = (u8*)cursor_pal_bin;
	file_info_cursor_tile_32_8.pal_len[0] = cursor_pal_bin_size;
	file_info_cursor_tile_32_8.num_pal = 1;

	materials[MAT_REF_CURSOR_0] = new material_c( file_info_cursor_tile_32_8 );
	materials[MAT_REF_CURSOR_0]->load();
	num_materials++;

	material_file_info_t file_info_full_green_tile_32_8;
	
	file_info_full_green_tile_32_8.tex = (u8*)full_green_tex_bin;
	file_info_full_green_tile_32_8.pal[0] = (u8*)full_green_pal_bin;
	file_info_full_green_tile_32_8.pal_len[0] = full_green_pal_bin_size;
	file_info_full_green_tile_32_8.num_pal = 1;

	materials[MAT_REF_FULL_GREEN] = new material_c( file_info_full_green_tile_32_8 );
	materials[MAT_REF_FULL_GREEN]->load();
	num_materials++;	

	/* Finish creating the cursor materials */

	/* Begin creating the background materials */
	material_file_info_t file_info_corrupt_bg01_32_8;
	
	file_info_corrupt_bg01_32_8.tex = (u8*)corrupt_bg01_tex_bin;
	file_info_corrupt_bg01_32_8.pal[0] = (u8*)corrupt_bg01_pal_bin;
	file_info_corrupt_bg01_32_8.pal_len[0] = corrupt_bg01_pal_bin_size;
	file_info_corrupt_bg01_32_8.num_pal = 1;

	materials[MAT_REF_CORRUPT_BG00] = new material_c( file_info_corrupt_bg01_32_8 );
	materials[MAT_REF_CORRUPT_BG00]->load();
	num_materials++;

	material_file_info_t file_info_corrupt_bg02_32_8;
	
	file_info_corrupt_bg02_32_8.tex = (u8*)corrupt_bg02_tex_bin;
	file_info_corrupt_bg02_32_8.pal[0] = (u8*)corrupt_bg02_pal_bin;
	file_info_corrupt_bg02_32_8.pal_len[0] = corrupt_bg02_pal_bin_size;
	file_info_corrupt_bg02_32_8.num_pal = 1;

	materials[MAT_REF_CORRUPT_BG01] = new material_c( file_info_corrupt_bg02_32_8 );
	materials[MAT_REF_CORRUPT_BG01]->load();
	num_materials++;

	/* Finish creating th background materials */
}