/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: unit.h
 * Date: 19th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry
 * Discription: unit class, 
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef UNIT_H
#define UNIT_H

// libraries
#include <nds.h>
#include <stdio.h>

// files
#include "types.h"
#include "timer.h"
#include "unit_all_stats.h"

#include "pathfinding_2009.h"
#include "grid_pop.h"

// defines
#define UNIT_MINI_PATH 40

#define X_MOD 0
#define Y_MOD 1

#define TOLERANCE_TIME 5

enum unit_status_e
{
	IDLE, MOVING, TIMED_OUT
};

// new unit class
class unit_c
{
protected:
// unit	
	u8 id;					// holds a value to identify this unit
	bool active;			// active: a boolean to see if this unit is in use or not. 
	vector_2di_t grid;		// grid location
	vector_2df_t grid_draw;	// draw location

// gameplay stats
	u8 name_id;			// unit type name id
	s8 hp_current;		// current amount of hp this unit has, less than hp_max
	s8 hp_max;			// max hp this unit can have
	u8 armor;			// the amount of damage is reduced by armor
	u8 attack_damage;	// amount of damage the standard attack does
	u8 atack_cooldown;	// frames before the unit can attack again
	u8 attention_range;	// range that the unit will consider attacking while idle
	u8 speed;			// speed that the unit can move around the map
	u8 cost;			// the amount of money that is spent to build this unit
	u16 build_time;		// amount of frames it takes to build this unit
	
	bool trigger_ability_1;
	bool trigger_ability_2;

// team
	u8 team_id;			// id of the team this unit belongs to
	palette_t team_pal;	// pallette from team this unit belongs to
// map
	map_c_ptr map;		// map pointer for giving current map rego

// movement
	u8 step_counter;							// step counter for moving accross tiles
	u8 time_out_counter;						// counter for when the unit must wait for another movement to move
	u8 face_direction;							// direction that the uit is facing
	vector_2di_t move_goal;						// goal to move to in the map
	path_direction_e path[UNIT_MINI_PATH];		// path to follow
	u8 path_place;								// value to keep track of current place in path

	u8 move_lag; // remove this

	// testing - 
	list_t_ptr exclude_list;
	u8 waiting_room_time;		// how long this unit will wait for a moving unit to get out of the way before it will move around it

public:
	/** init unit
	 * 
	 * this is called when the unit is made.
	 * makes the unit an active unit.
	 * 
	 * param u16 grid_x spawn location x on map
	 * param u16 grid_y spawn location y on map
	 * param u8 type the type of unit to create
	 * param map_c_ptr map pointer to the map for the unit to remember
	 */
	virtual void init(u16 grid_x, u16 grid_y, u8 type, map_c_ptr map);

	/** abilities (1 and 2)
	 * 
	 * Each unit type has 2 abilities that are defined in thier class
	 */
	virtual void ability_1();
	virtual void ability_2();
	
	/** draw
	 * 
	 * 
	 */
	virtual void draw();
	
	u8 get_id();								// returns unit's id
	void set_id(u8);							// set the unit's id
	void set_team_id(u8);						// set pointer back to team
	void set_team_pal(palette_t);				// set this unit's team id
	void idle();								// update time-related event for the unit, eg: animation
	void clear_all();							// clear the unit as if it was not in use
	void set_active(bool);						// set this unit in use or not
	bool get_active();							// see if this unit is in use or not
	vector_2di_t get_grid();					// get the unit's grid location
	void set_move_goal(int goal_x, int goal_y);	// set new goal to move to
	void draw_path();							// debug function for drawing paths
	void clear_path();							// clear path array
	void set_move_lag(u8 value);				// set unit movement lag
	void grid_move(int mod, int x_or_y);		// move unit during idle
};
// pointer
typedef unit_c* unit_c_ptr;


#endif

// end of file
