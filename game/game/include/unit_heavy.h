/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: unit_heavy.h
 * Date: 4th of May, 2010.
 * Author(s): Patrick Randell
 * Discription: heavy unit class 
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef UNIT_HEAVY_H
#define UNIT_HEAVY_H

// libraries
#include <nds.h>

// files
#include "unit.h"
#include "unit_all_stats.h"

// heavy class
class unit_heavy_c : public unit_c
{
protected:
	
public:
	void init(u16 grid_x, u16 grid_y, u8 type, map_c_ptr map);
	void draw();
};
// pointer
typedef unit_heavy_c* unit_heavy_c_ptr;


#endif