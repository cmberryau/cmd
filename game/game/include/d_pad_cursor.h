/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: d_pad_cursor.h
 * Date: 9th of March, 2010.
 * Author(s): Patrick Randell
 * Discription: cursor that can be moved with the d-pad.
 * Copyright: (c) SteelCat 2009-2010

==================================================================================================*/

#ifndef D_PAD_CURSOR_H
#define D_PAD_CURSOR_H

// libraries

// files
#include "types.h"
#include "event.h"
#include "map.h"
#include "game.h"
#include "unit.h"

// defines

#define SELECTION_LIST_MAX 16

// status enum

enum status_e
{
	NORMAL, UNITS_SELECTED
};

class d_pad_cursor_c
{
private:
	touch_t screen_input;
	buttons_t button_input;
	
	// status
	status_e status;

	// grid location
	vector_2di_t grid;
	vector_2di_t select_start;
	vector_2di_t select_end;
	
	bool draw_selection;
	
	// pointer to map
	map_c_ptr map;
	
	// this variable is currently a member of the class for debugging,
	// best to ajust this this to a function's member further down the track.
	u8 selection_case;
	
	// selection list
	u8 units_in_list;
	unit_c_ptr selection_list[SELECTION_LIST_MAX];
	
public:

	void init(u16 grid_x, u16 grid_y, map_c_ptr map);
	
	// get input from the user
	void update_input(event_c_ptr event, game_c_ptr game);
	void draw();
	s8 calculate_selected_units(game_c_ptr game); // returns number of units selected
	void debug_print();
	void add_unit_to_selection_list(unit_c_ptr new_unit);
	void clear_selection_list();
};

// pointer
typedef d_pad_cursor_c * d_pad_cursor_ptr;

#endif

// end of file

