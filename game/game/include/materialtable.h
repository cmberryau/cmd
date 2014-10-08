/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: materialtable.h
 * Date: 18th of April, 2010.
 * Author(s): Christopher Berry
 * Description: material table class header
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef MATERIALTABLE_H
#define MATERIALTABLE_H

#include "material.h"

// Placeholder textures

#include "demo_tex_bin.h"
#include "demo_pal_bin.h"

#include "tile01_tex_bin.h"
#include "tile01_pal_bin.h"

// Unit textures

// Heavy
// Heavy Front
#include "heavy_front_tex_bin.h"
#include "heavy_front_pal_bin.h"
	
// Heavy Back
#include "heavy_back_tex_bin.h"
#include "heavy_back_pal_bin.h"

// Gatherer
// Gatherer Front
#include "gatherer_front_tex_bin.h"
#include "gatherer_front_pal_bin.h"
	
// Gatherer Back
#include "gatherer_back_tex_bin.h"
#include "gatherer_back_pal_bin.h"

// Cursor textures

// Actual cursor texture
#include "cursor_tex_bin.h"
#include "cursor_pal_bin.h"

// Green texture for selection box
#include "full_green_tex_bin.h"
#include "full_green_pal_bin.h"

// Background textures

#include "corrupt_bg01_tex_bin.h"
#include "corrupt_bg01_pal_bin.h"

#include "corrupt_bg02_tex_bin.h"
#include "corrupt_bg02_pal_bin.h"

#define MAT_REF_DEFAULT_32_8 0

/* Map tile material defines */
#define MAT_REF_TILE01_32_8 1

/* Unit material defines */
#define MAT_REF_UNIT_DEMO_32_8 2

// heavy
#define MAT_REF_UNIT_HEAVY_FRONT_32_8 3
#define MAT_REF_UNIT_HEAVY_BACK_32_8 4

// gatherer
#define MAT_REF_UNIT_GATHERER_FRONT_32_8 5
#define MAT_REF_UNIT_GATHERER_BACK_32_8 6

/* Cursor material defines */
#define MAT_REF_CURSOR_0 7
#define MAT_REF_FULL_GREEN 8

/* Background material defines */
#define MAT_REF_CORRUPT_BG00 9
#define MAT_REF_CORRUPT_BG01 10

class materialtable_c{
	private:
		material_c * materials[MAX_MATERIALS];	// Array of materials
		int num_materials;	// Total number of materials

	public:
		material_c * get_material( int material_ref );	// Returns a pointer to the material object
		material_c * get_full_green();

		material_c * get_default_material();

		void free_materials();

		materialtable_c();
};

#endif /* MATERIALTABLE_H */