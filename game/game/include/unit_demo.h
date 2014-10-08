/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: unit_demo.h
 * Date: 4th of May, 2010.
 * Author(s): Patrick Randell
 * Discription: demo unit class 
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef UNIT_DEMO_H
#define UNIT_DEMO_H

// libraries
#include <nds.h>

// files
#include "unit.h"
#include "unit_all_stats.h"

// demo class
class unit_demo_c : public unit_c
{
protected:
	
public:
	void init(u16 grid_x, u16 grid_y, u8 type, map_c_ptr map);
	void draw();
};
// pointer
typedef unit_demo_c* unit_demo_c_ptr;


#endif