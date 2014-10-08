/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: d_pad_cursor.cpp
 * Date: 9th of March, 2010.
 * Author(s): Patrick Randell
 * Discription: see header.
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

// header file
#include "d_pad_cursor.h"
#include "engine.h"

extern engine_c engine;

void d_pad_cursor_c::init(u16 grid_x, u16 grid_y, map_c_ptr map)
{
	grid.x = grid_x;
	grid.y = grid_y;
	this->map = map;
	select_start.x = 0;
	select_start.y = 0;
	select_end.x = 0;
	select_end.y = 0;
	status = NORMAL;
	clear_selection_list();
}

void d_pad_cursor_c::update_input(event_c_ptr event, game_c_ptr game)
{
	screen_input = event->get_touch();
	button_input = event->get_buttons();
	draw_selection = false;
	s8 units_selected = 0;
	u8 i;
	team_c_ptr our_team;
	base_c_ptr our_base;
	vector_2di_t base_grid;

	iprintf("\x1b[0;0H             ");

	// until there is a player class, make this only check team 0
	u8 THIS_TEAM = 0;
	
	// move cursor
	if (button_input.new_press & KEY_UP) grid.x++;
	if (button_input.new_press & KEY_DOWN) grid.x--;
	if (button_input.new_press & KEY_LEFT) grid.y++;
	if (button_input.new_press & KEY_RIGHT) grid.y--;
	
	// check map bounds
	if (grid.y > map->get_y_max()) grid.y = map->get_y_max();
	if (grid.y < 0) grid.y = 0;
	if (grid.x > map->get_x_max()) grid.x = map->get_x_max();
	if (grid.x < 0) grid.x = 0;
	
	if (status == NORMAL)
	{
		// check the draw start
		if (button_input.new_press & KEY_A)
		{
			select_start = grid;
		}
		if (button_input.held & KEY_A) draw_selection = true;
		if (button_input.release & KEY_A)
		{ 
			select_end = grid;
			// check for units
			units_selected = calculate_selected_units(game);
			// check for base
			if (units_selected == 0 && select_start.x == select_end.x && select_start.y == select_end.y)
			{
				our_team = game->get_team(THIS_TEAM);
				our_base = our_team->get_base();
				base_grid = our_base->get_grid();
				
				if (base_grid.x == grid.x && base_grid.y == grid.y)
				{
					// select base
					our_base->build_unit(GATHERER, game);
					iprintf("\x1b[0;0HBuilding Unit");
				}
			}
		}
	}
	else if (status == UNITS_SELECTED)
	{
		if (button_input.new_press & KEY_A)
		{
			// move unit to place
			if (map->wall_map[grid.x][grid.y] != TILE_WALL)
			{
				for (i = 0; i < SELECTION_LIST_MAX; i++)
				{
					selection_list[i]->set_move_goal(grid.x, grid.y);
				}
				//status = NORMAL;
				select_start = grid;
			}
			draw_selection = true;
		}
		else if (button_input.new_press & KEY_B)
		{
			status = NORMAL;
			clear_selection_list();
		}
		if (button_input.release & KEY_A) draw_selection = false;
	}
}

void d_pad_cursor_c::draw()
{
	// draw cursor
	glPushMatrix();
	// angle for grid
	glRotateZ(45);
	// translate into position
	glTranslatef(grid.x, grid.y, 0);
	// call the cursor display list
	engine.get_meshtable()->get_cursor_mesh()->draw();
	// Return the matrix stack back one
	glPopMatrix(1);
	if (draw_selection == true && status == NORMAL)
	{
		// draw selection area
		glPushMatrix();
			// angle for grid
			glRotateZ(45);
			// lines
			engine.get_meshtable()->get_materialtable()->get_full_green()->use();
			
			if (select_start.x == grid.x && select_start.y == grid.y)
			{
				glBegin(GL_QUADS);
				glVertex3f(select_start.x, select_start.y, 0.1);glVertex3f(select_start.x, select_start.y, 0.1);glVertex3f(select_start.x + TILE_X, select_start.y, 0.1);glVertex3f(select_start.x + TILE_X, select_start.y, 0.1);
				glVertex3f(select_start.x + TILE_X, select_start.y, 0.1);glVertex3f(select_start.x + TILE_X, select_start.y, 0.1);glVertex3f(select_start.x + TILE_X, select_start.y + TILE_Y, 0.1);glVertex3f(select_start.x + TILE_X, select_start.y + TILE_Y, 0.1);
				glVertex3f(select_start.x + TILE_X, select_start.y + TILE_Y, 0.1);glVertex3f(select_start.x + TILE_X, select_start.y + TILE_Y, 0.1);glVertex3f(select_start.x, select_start.y + TILE_Y, 0.1);glVertex3f(select_start.x, select_start.y + TILE_Y, 0.1);
				glVertex3f(select_start.x, select_start.y + TILE_Y, 0.1);glVertex3f(select_start.x, select_start.y + TILE_Y, 0.1);glVertex3f(select_start.x, select_start.y, 0.1);glVertex3f(select_start.x, select_start.y, 0.1);
				glEnd();
			}
			else if (select_start.x == grid.x && select_start.y != grid.y)
			{
				glBegin(GL_QUADS);
				glVertex3f(select_start.x, select_start.y, 0.1);glVertex3f(select_start.x, select_start.y, 0.1);glVertex3f(select_start.x + TILE_X, select_start.y, 0.1);glVertex3f(select_start.x + TILE_X, select_start.y, 0.1);
				glVertex3f(select_start.x + TILE_X, select_start.y, 0.1);glVertex3f(select_start.x + TILE_X, select_start.y, 0.1);glVertex3f(select_start.x + TILE_X, grid.y, 0.1);glVertex3f(select_start.x + TILE_X, grid.y, 0.1);
				glVertex3f(select_start.x + TILE_X, grid.y, 0.1);glVertex3f(select_start.x + TILE_X, grid.y, 0.1);glVertex3f(select_start.x, grid.y, 0.1);glVertex3f(select_start.x, grid.y, 0.1);
				glVertex3f(select_start.x, grid.y, 0.1);glVertex3f(select_start.x, grid.y, 0.1);glVertex3f(select_start.x, select_start.y, 0.1);glVertex3f(select_start.x, select_start.y, 0.1);
				glEnd();
			}
			else if (select_start.x != grid.x && select_start.y == grid.y)
			{
				glBegin(GL_QUADS);
				glVertex3f(select_start.x, select_start.y, 0.1);glVertex3f(select_start.x, select_start.y, 0.1);glVertex3f(grid.x, select_start.y, 0.1);glVertex3f(grid.x, select_start.y, 0.1);
				glVertex3f(grid.x, select_start.y, 0.1);glVertex3f(grid.x, select_start.y, 0.1);glVertex3f(grid.x, select_start.y + TILE_Y, 0.1);glVertex3f(grid.x, select_start.y + TILE_Y, 0.1);
				glVertex3f(grid.x, select_start.y + TILE_Y, 0.1);glVertex3f(grid.x, select_start.y + TILE_Y, 0.1);glVertex3f(select_start.x, select_start.y + TILE_Y, 0.1);glVertex3f(select_start.x, select_start.y + TILE_Y, 0.1);
				glVertex3f(select_start.x, select_start.y + TILE_Y, 0.1);glVertex3f(select_start.x, select_start.y + TILE_Y, 0.1);glVertex3f(select_start.x, select_start.y, 0.1);glVertex3f(select_start.x, select_start.y, 0.1);
				glEnd();
			}
			else
			{
				glBegin(GL_QUADS);
				glVertex3f(select_start.x, select_start.y, 0.1);glVertex3f(select_start.x, select_start.y, 0.1);glVertex3f(select_start.x, grid.y, 0.1);glVertex3f(select_start.x, grid.y, 0.1);
				glVertex3f(select_start.x, grid.y, 0.1);glVertex3f(select_start.x, grid.y, 0.1);glVertex3f(grid.x, grid.y, 0.1);glVertex3f(grid.x, grid.y, 0.1);
				glVertex3f(grid.x, grid.y, 0.1);glVertex3f(grid.x, grid.y, 0.1);glVertex3f(grid.x, select_start.y, 0.1);glVertex3f(grid.x, select_start.y, 0.1);
				glVertex3f(grid.x, select_start.y, 0.1);glVertex3f(grid.x, select_start.y, 0.1);glVertex3f(select_start.x, select_start.y, 0.1);glVertex3f(select_start.x, select_start.y, 0.1);
				glEnd();
			}
		glPopMatrix(1);
	}
}

s8 d_pad_cursor_c::calculate_selected_units(game_c_ptr game)
{
	// clear the list for a new selection
	clear_selection_list();
	// used to note what type of selection has taken place
	selection_case = 0;
	u8 units_selected = 0;
	
	// find selection case
	/*
	case 1:
		S---+
		| u |
		+---E
	*/
	if (select_start.x < select_end.x && select_start.y > select_end.y) selection_case = 1;
	/*
	case 2:
		+---S
		| u |
		E---+
	*/
	else if (select_start.x > select_end.x && select_start.y > select_end.y) selection_case = 2;
	/*
	case 3:
		E---+
		| u |
		+---S
	*/
	else if (select_start.x > select_end.x && select_start.y < select_end.y) selection_case = 3;
	/*
	case 4:
		+---E
		| u |
		S---+
	*/
	else if (select_start.x < select_end.x && select_start.y < select_end.y) selection_case = 4;
	
	// now find what units have been selected
	
	// until there is a player class, make this only check team 0
	u8 THIS_TEAM = 0;
	
	u8 i;
	
	// get the team
	team_c_ptr current_team;
	current_team = game->get_team(THIS_TEAM);
	
	// pointer to hold current unit
	unit_c_ptr current_unit;
	vector_2di_t unit_grid;
	
	for (i = 0; i < UNIT_MAX; i++)
	{
		// get the new unit to check
		current_unit = current_team->get_unit(i);
		unit_grid = current_unit->get_grid();

		if (current_unit == null) continue;

		// check for a single unit selection
		if (unit_grid.x == select_start.x)
		{
			if (unit_grid.y == select_start.y)
			{
				units_selected++;
				add_unit_to_selection_list(current_unit);
				continue;
			}
		}

		// now we have the unit's info, we can check the selection area
		switch (selection_case)
		{
		case 1:
			if (unit_grid.x >= select_start.x && unit_grid.x < select_end.x)
			{
				if (unit_grid.y < select_start.y && unit_grid.y >= select_end.y)
				{
					// add to slection list
					units_selected++;
					add_unit_to_selection_list(current_unit);
				}
			}
			break;
		case 2:
			if (unit_grid.x < select_start.x && unit_grid.x >= select_end.x)
			{
				if (unit_grid.y < select_start.y && unit_grid.y >= select_end.y)
				{
					units_selected++;
					add_unit_to_selection_list(current_unit);
				}
			}
			break;
		case 3:
			if (unit_grid.x < select_start.x && unit_grid.x >= select_end.x)
			{
				if (unit_grid.y >= select_start.y && unit_grid.y < select_end.y)
				{
					units_selected++;
					add_unit_to_selection_list(current_unit);
				}
			}
			break;
		case 4:
			if (unit_grid.x >= select_start.x && unit_grid.x < select_end.x)
			{
				if (unit_grid.y >= select_start.y && unit_grid.y < select_end.y)
				{
					units_selected++;
					add_unit_to_selection_list(current_unit);
				}
			}
			break;
		} // selection case
	} // for all units
	
	// the selected_units array should now contain the selected units.
	
	// update cursor status
	if (selection_list[0] != null) status = UNITS_SELECTED;
	else status = NORMAL;

	return units_selected;
}

void d_pad_cursor_c::debug_print()
{
	iprintf("\x1b[4;0HCursor Debug\nGrid : %4d, %4d  \nStart: %4d, %4d  \nEnd  : %4d %4d  \nSelection case: %d \nUnits in list: %d  \nStatus code: %d",
	grid.x, grid.y,
	select_start.x, select_start.y,
	select_end.x, select_end.y,
	selection_case,
	units_in_list,
	status);
	
	vector_2di_t grid;
	
	if (units_in_list >= 1)
	{
		grid = selection_list[0]->get_grid();
		iprintf("\x1b[11;0H0: (%d,%d)\n",
		selection_list[0]->get_grid().x,
		selection_list[0]->get_grid().y);
	} else printf("\x1b[11;0H0:      \n");
	if (units_in_list >= 2)
	{
		grid = selection_list[1]->get_grid();
		iprintf("\x1b[11;10H1: (%d,%d)\n",
		selection_list[1]->get_grid().x,
		selection_list[1]->get_grid().y);
	} else printf("\x1b[11;10H1:      \n");
	if (units_in_list >= 3)
	{
		grid = selection_list[2]->get_grid();
		iprintf("\x1b[11;20H2: (%d,%d)\n",
		selection_list[2]->get_grid().x,
		selection_list[2]->get_grid().y);
	} else printf("\x1b[11;20H2:      \n");
	if (units_in_list >= 4)
	{
		grid = selection_list[3]->get_grid();
		iprintf("\x1b[12;0H3: (%d,%d)\n",
		selection_list[3]->get_grid().x,
		selection_list[3]->get_grid().y);
	} else printf("\x1b[12;0H3:      \n");
	if (units_in_list >= 5)
	{
		grid = selection_list[4]->get_grid();
		iprintf("\x1b[12;10H4: (%d,%d)\n",
		selection_list[4]->get_grid().x,
		selection_list[4]->get_grid().y);
	} else printf("\x1b[12;10H4:      \n");
	if (units_in_list >= 6)
	{
		grid = selection_list[5]->get_grid();
		iprintf("\x1b[12;20H5: (%d,%d)\n",
		selection_list[5]->get_grid().x,
		selection_list[5]->get_grid().y);
	} else printf("\x1b[12;20H5:      \n");
	if (units_in_list >= 7)
	{
		grid = selection_list[6]->get_grid();
		iprintf("\x1b[13;0H6: (%d,%d)\n",
		selection_list[6]->get_grid().x,
		selection_list[6]->get_grid().y);
	} else printf("\x1b[13;0H6:      \n");
	if (units_in_list >= 8)
	{
		grid = selection_list[7]->get_grid();
		iprintf("\x1b[13;10H7: (%d,%d)\n",
		selection_list[7]->get_grid().x,
		selection_list[7]->get_grid().y);
	} else printf("\x1b[13;10H7:      \n");
	if (units_in_list >= 9)
	{
		grid = selection_list[8]->get_grid();
		iprintf("\x1b[13;20H8: (%d,%d)\n",
		selection_list[8]->get_grid().x,
		selection_list[8]->get_grid().y);
	} else printf("\x1b[13;20H8:      \n"); 
	
}

void d_pad_cursor_c::add_unit_to_selection_list(unit_c_ptr new_unit)
{
	// check that we have room in the selected units array to save the unit
	// if we have room add the unit to the next free place
	// if not, exit function
	
	if (units_in_list >= SELECTION_LIST_MAX) return;
	u8 i;
	
	for (i = 0; i < SELECTION_LIST_MAX; i++)
	{
		if (selection_list[i] == null)
		{
			selection_list[i] = new_unit;
			units_in_list++;
			break;
		}
	}
	
}

void d_pad_cursor_c::clear_selection_list()
{
	// links are only pointers to the units in the game structure, 
	// so we can just null the links
	u8 i;
	for (i = 0; i < SELECTION_LIST_MAX; i++)
	{
		selection_list[i] = null;
	}
	units_in_list = 0;
}
