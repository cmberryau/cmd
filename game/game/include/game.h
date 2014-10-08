/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: game.h
 * Date: 19th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry
 * Discription: game class, used to manage teams, units.
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/
#ifndef GAME_H
#define GAME_H

// libraries
#include <nds.h>
#include <stdio.h>

// files
#include "types.h"
#include "team.h"
#include "map.h"
#include "timer.h"

// defines
# define TEAM_MAX 4

// be aware of the team class
class team_c;
typedef team_c* team_c_ptr;

class game_c
{
private:
// teams
	s8 number_of_teams;								// number of teams in the game
	team_c_ptr team[TEAM_MAX];							// array of teams
	map_c_ptr map;									// pointer to the game map
public:
// game
	void init();									// setup the game varaibles and nulls links
	void free_game();								// free all the mem used for the game
// map
	void set_map(map_c_ptr);						// assign the map to this game
	map_c_ptr get_map();							// retruns a pointer to the game's map
// teams
	s8 add_team_array();							// activate a team in the array, returns id of new team, -1 if fail
	team_c_ptr get_team(u8 return_team);			// return the address of a team
// units
	void draw_all_units();							// draw all the units in the game
	void idle_all_units();							// idle all the units in the game
	s8 make_unit(u8 team, s16 x, s16 y, u8 type);	// make a unit, easy way
};
typedef game_c* game_c_ptr;

#endif

// end of file