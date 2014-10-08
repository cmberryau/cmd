/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: unit_soldier.cpp
 * Date: 4th of May, 2010.
 * Author(s): Patrick Randell
 * Discription: soldier unit class , see header file
 * Copyright: (c) SteelCat 2009-2010 
==================================================================================================*/

// header file
#include "unit_soldier.h"
#include "engine.h"

extern engine_c engine;

// functions
void unit_soldier_c::init(u16 grid_x, u16 grid_y, u8 type, map_c_ptr map)
{
	this->active = true;
	grid.x = grid_x;
	grid.y = grid_y;
	grid_draw.x = grid.x;
	grid_draw.y = grid.y;
	move_goal.x = grid.x;
	move_goal.y = grid.y;

	name_id = SOLDIER_NAME_ID;
	hp_current = SOLDIER_HP;
	hp_max = SOLDIER_HP;
	armor = SOLDIER_ARMOR;
	attack_damage = SOLDIER_ATTACK_DAMAGE;
	atack_cooldown = SOLDIER_ATTACK_COOLDOWN;
	attention_range = SOLDIER_ATTENTION_RANGE;
	speed = SOLDIER_SPEED;
	cost = SOLDIER_COST;
	build_time = SOLDIER_BUILD_TIME;

	move_lag = 8; // so gap is 0.125
	clear_path();
	path_place = 0;
	this->map = map;
	map->unit_map[grid.x][grid.y] = TILE_STILL_UNIT; // register location with master map
	time_out_counter = 0;
	face_direction = DOWN;

	// testing - 
	exclude_list = new list_t;
	init_list(exclude_list);
	waiting_room_time = 0;
}

// end of file
