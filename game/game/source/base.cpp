/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: d_pad_cursor.cpp
 * Date: 9th of March, 2010.
 * Author(s): Patrick Randell
 * Discription: see header.
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

// header file 
#include "base.h"
#include "engine.h"

extern engine_c engine;

// functions

void base_c::clear_all()
{
	active = false;
	grid.x = -1;
	grid.y = -1;
	grid_draw.x = -1;
	grid_draw.y = -1;
	hp_current = 0;
	hp_max = BASE_HP;
	team_id = -1;
	map = null;
	building_time = 0;

	u8 i;
	for (i = 0; i < UNIT_BUILD_LIST_MAX; i++)
	{
		unit_build_list[i] = DEFAULT;
	}
}

void base_c::init(u16 grid_x, u16 grid_y, map_c_ptr map, u8 team_id)
{
	active = true;
	grid.x = grid_x;
	grid.y = grid_y;
	grid_draw.x = grid.x;
	grid_draw.y = grid.y;
	hp_current = BASE_HP;
	hp_max = BASE_HP;
	this->team_id = team_id;
	this->map = map;
	building_time = 0;

	map->unit_map[grid.x][grid.y] = TILE_STILL_UNIT;
}

void base_c::draw()
{
	if (this->active == true)
	{
		glPushMatrix();
			glRotateZ(45); // angle for grid
			glTranslatef(grid_draw.x, grid_draw.y, 0.1); // translate into position
			engine.get_meshtable()->get_default_mesh()->draw();
		glPopMatrix(1);
	}
}

void base_c::idle()
{
	if (building_time > 0)
	{
		building_time--;
	}


}

void base_c::build_unit(u8 unit_type, game_c_ptr game)
{
	iprintf("\x1b[0;0HBuilding Unit");
	vector_2d_u8_t free_space, base_grid;
	base_grid.x = grid.x;
	base_grid.y = grid.y;
	
	free_space = get_free_space(base_grid, game->get_map());
	game->make_unit(team_id, free_space.x, free_space.y, unit_type);
}

vector_2di_t base_c::get_grid(){return grid;}
bool base_c::get_active(){return active;}
// end of file
