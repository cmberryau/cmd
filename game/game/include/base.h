/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: base.h
 * Date: 15th of May, 2010.
 * Author(s): Patrick Randell
 * Description: base class, plsyer can build units here 
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef BASE_H
#define BASE_H

// libs
#include <nds.h>

class game_c;
typedef game_c* game_c_ptr;

// files
#include "types.h"
#include "game.h"
#include "unit_all_stats.h"	// defines for unit bulid list
#include "map.h"
#include "event.h"  
#include "team.h"
#include "grid_pop.h"

// defines
#define UNIT_BUILD_LIST_MAX 6
#define BASE_HP 1000

class base_c
{
protected:
	buttons_t button_input;
	bool active;			// active: a boolean to see if this base is in use or not. 
	vector_2di_t grid;		// grid location
	vector_2df_t grid_draw;	// draw location
	s16 hp_current;			// current amount of hp this base has, less than hp_max
	s16 hp_max;				// max hp this base can have
	s8 team_id;				// id of the team this base belongs to
	int building_time;		// tracking the time this unit is building
	
	// when you have time make this a stack
	u8 unit_build_list[UNIT_BUILD_LIST_MAX];	// list of units to build, uses values defined in "unit_all_stats.h"

	// still need to work out if this is needed
	map_c_ptr map;			// map pointer for giving current map rego
	
public:
	void clear_all();
	void init(u16 grid_x, u16 grid_y, map_c_ptr map, u8 team_id); // activate for game
	void draw();
	void idle();
	void build_unit(u8 unit_type, game_c_ptr game);
	void cancel_unit();
	void set_team_id(u8);
	vector_2di_t get_grid();
	bool get_active();
};
// pointer
typedef base_c* base_c_ptr;

// end of file

#endif
