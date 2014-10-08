/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: team.h
 * Date: 19th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry
 * Discription: team class, tracks a team and it's units
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef TEAM_H
#define TEAM_H

// libraries
#include <nds.h>
#include <stdio.h>

// files
//#include "game.h"
#include "unit.h"
#include "types.h"
#include "timer.h"
#include "base.h"
// units
#include "unit_all_stats.h"
#include "unit_demo.h"
#include "unit_gatherer.h"
#include "unit_heavy.h"

// defines
#define UNIT_MAX 20

class base_c;
typedef base_c* base_c_ptr;

class team_c
{
private:
// team
	// team id
	u8 id;
	// used to see if this team is in the game or not
	bool active;
	// base colour palette
	palette_t base_colour;
	
// units	
	// number of units currently in this team
	u8 number_of_units;
	// array of units
	// now an array of pointers, for polymorphism
	unit_c_ptr unit[UNIT_MAX];

// base
	base_c_ptr base;

public:
// team
	// sets up the team with default values
	void init();
	// get active status
	bool get_active();
	// set active status
	void set_active(bool);
	// returns team id
	u8 get_id();
	// set the team's id
	void set_id(u8);
	// set defaults
	void clear_all();
	
// units
	// activate new unit in array, returns id, -1 if fail
	s8 add_unit_array(u16, u16, u8, map_c_ptr map);
	// get a specified unit
	unit_c_ptr get_unit(u8 return_unit);
	
	// delete a unit form the team via id
	void delete_unit(u8);
	// sort the team's units so that the id's are chronological
	void sort_unit_ids();
	// draw this teams units
	void draw_units();
	// idle this teams units
	void idle_units();

// base
	base_c_ptr get_base();
};

// pointer
typedef team_c* team_c_ptr;

#endif

// end of file
