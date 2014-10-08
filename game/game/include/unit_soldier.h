/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: unit_soldier.h
 * Date: 4th of May, 2010.
 * Author(s): Patrick Randell
 * Discription: soldier unit class 
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef UNIT_SOLDIER_H
#define UNIT_SOLDIER_H

// libraries
#include <nds.h>

// files
#include "unit.h"
#include "unit_all_stats.h"

// soldier class
class unit_soldier_c : public unit_c
{
protected:
	
public:
	void init(u16 grid_x, u16 grid_y, u8 type, map_c_ptr map);
};
// pointer
typedef unit_soldier_c* unit_soldier_c_ptr;

#endif

