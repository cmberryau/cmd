/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: background3d.h
 * Date: 10th May, 2010
 * Author(s): Christopher Berry
 * Description: Unit display mesh class header
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef UNITMESH_H
#define UNITMESH_H

#include <nds.h>

#include "types.h"
#include "mesh.h"
#include "material.h"

#define FRONT_FRAME 0
#define BACK_FRAME 1

class unitmesh_c : public mesh_c{
	public:
		void show_back();
		void show_front();
		unitmesh_c( material_c * front, material_c * back, u32 * dlistptr );
		unitmesh_c( material_c * front, material_c * back );
};

#endif /* UNITMESH_H */