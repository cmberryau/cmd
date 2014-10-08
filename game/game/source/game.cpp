/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: game.cpp
 * Date: 19th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry
 * Discription: game class, see header.
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

// header file
#include "game.h"

// functions

// game
void game_c::init()
{
	u8 i;
	number_of_teams = -1;
	// clean teams
	for (i = 0; i < TEAM_MAX; i++)
	{
		team[i] = new team_c;
		team[i]->clear_all();
		team[i]->set_id(i);
	}
	// null map
	map = null;
}

void game_c::free_game()
{
	// latter
}

// map
void game_c::set_map(map_c_ptr map)
{
	this->map = map;
	// be sure that the map has ran it's set_map function
}

map_c_ptr game_c::get_map()
{
	return map;
}

// teams
s8 game_c::add_team_array()
{
	u8 i;
	// find a free team
	for (i = 0; i < TEAM_MAX; i++)
	{
		// if you find one not being used
		if (team[i]->get_active() == false)
		{
			// init the team
			team[i]->init();
			
			// add one to the active unit total
			number_of_teams += 1;
			
			// return the new team id
			return i;
		}
	}
	// no team is free
	return -1;
}

team_c_ptr game_c::get_team(u8 return_team)
{
	if (return_team > TEAM_MAX) return team[0];
	else return team[return_team];
}

// units
void game_c::draw_all_units()
{
	u8 i;
	for (i = 0; i < TEAM_MAX; i++)
	{
		if (team[i]->get_active() == true)
		{
			team[i]->draw_units();
		}
	}
}

void game_c::idle_all_units()
{
	u8 i;
	for (i = 0; i < TEAM_MAX; i++)
	{
		if (team[i]->get_active() == true)
		{
			team[i]->idle_units();
		}
	}
}

s8 game_c::make_unit(u8 team_id, s16 x, s16 y, u8 type)
{
	team[team_id]->add_unit_array(x, y, type, map);
	// for latter use
	return 0;
}

// end of file
