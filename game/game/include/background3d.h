/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: background3d.h
 * Date: 20th April, 2010
 * Author(s): Christopher Berry
 * Description: 3d background class header
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef BACKGROUND3D_H
#define BACKGROUND3D_H

#include <nds.h>

#include "types.h"
#include "mesh.h"
#include "material.h"

#define DEFAULT_BACKGROUND3D_MAXUV	128
#define DEFAULT_MS_PER_STEP			100

#define V0	0
#define V1	1
#define V2	2
#define V3	3

#define V0_UV	5
#define V1_UV	10
#define V2_UV	15
#define V3_UV	20

class background3d_c : public mesh_c{
	protected:
		bool active;

		int step_u;
		int step_v;

		int u[4];
		int v[4];

		int max;

		int ms_per_step_u;
		int ms_per_step_v;

		void updatedlist();
		
	public:
		void single_step_u();
		void single_step_v();

		void set_ms_per_step_u( int ms );
		void set_ms_per_step_v( int ms );

		background3d_c( material_c * matptr );
};

#endif /* BACKGROUND3D_H */