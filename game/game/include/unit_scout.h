/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: unit_scout.h
 * Date: 4th of May, 2010.
 * Author(s): Patrick Randell
 * Discription: scout unit class 
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef UNIT_SCOUT_H
#define UNIT_SCOUT_H

// libraries
#include <nds.h>

// files
#include "unit.h"
#include "unit_all_stats.h"

// scout class
class unit_scout_c : public unit_c
{
protected:
	
public:
	void init(u16 grid_x, u16 grid_y, u8 type, map_c_ptr map);
};
// pointer
typedef unit_scout_c* unit_scout_c_ptr;


#endif