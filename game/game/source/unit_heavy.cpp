/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: unit_heavy.cpp
 * Date: 4th of May, 2010.
 * Author(s): Patrick Randell
 * Discription: heavy unit class , see header file
 * Copyright: (c) SteelCat 2009-2010 
==================================================================================================*/

// header file
#include "unit_heavy.h"
#include "engine.h"

extern engine_c engine;

// functions
void unit_heavy_c::init(u16 grid_x, u16 grid_y, u8 type, map_c_ptr map)
{
	this->active = true;
	grid.x = grid_x;
	grid.y = grid_y;
	grid_draw.x = grid.x;
	grid_draw.y = grid.y;
	move_goal.x = grid.x;
	move_goal.y = grid.y;

	name_id = HEAVY_NAME_ID;
	hp_current = HEAVY_HP;
	hp_max = HEAVY_HP;
	armor = HEAVY_ARMOR;
	attack_damage = HEAVY_ATTACK_DAMAGE;
	atack_cooldown = HEAVY_ATTACK_COOLDOWN;
	attention_range = HEAVY_ATTENTION_RANGE;
	speed = HEAVY_SPEED;
	cost = HEAVY_COST;
	build_time = HEAVY_BUILD_TIME;

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

void unit_heavy_c::draw()
{
	if (this->active == true)
	{
		glPushMatrix();
		glRotateZ(45);
		glTranslatef(grid_draw.x, grid_draw.y, 0);
		glPushMatrix();
		glRotateZ(-45);
		glTranslatef(-0.5f, 0.25f, 0.0f); // (-(TILE_X / 2), (TILE_Y / 4), 0)
		// face_direction should be set to UP, DOWN, LEFT, or RIGHT
		switch (this->team_id)
		{
			case 0:
				if( face_direction == DOWN ){
					engine.get_meshtable()->get_unit_heavy_mesh()->show_front();					
				}
				else if( face_direction == UP ){
					engine.get_meshtable()->get_unit_heavy_mesh()->show_back();
				}
				engine.get_meshtable()->get_unit_heavy_mesh()->draw();
				break;
			case 1:
				break;
			case 2:
				break;
			default:
				break;
		}
		glPopMatrix(1);
		glPopMatrix(1);
	}
}

// end of file
