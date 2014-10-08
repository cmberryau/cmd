/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: unit.cpp
 * Date: 19th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry
 * Discription: unit class, see header.
 * Copyright: (c) SteelCat 2009-2010 
==================================================================================================*/

// header file
#include "unit.h"
#include "engine.h"

extern engine_c engine;

// functions
void unit_c::init(u16 grid_x, u16 grid_y, u8 type, map_c_ptr map)
{
	grid.x = grid_x;
	grid.y = grid_y;
	grid_draw.x = grid.x;
	grid_draw.y = grid.y;
	move_goal.x = grid.x;
	move_goal.y = grid.y;

	name_id = DEFAULT_NAME_ID;
	hp_current = DEFAULT_HP;
	hp_max = DEFAULT_HP;
	armor = DEFAULT_ARMOR;
	attack_damage = DEFAULT_ATTACK_DAMAGE;
	atack_cooldown = DEFAULT_ATTACK_COOLDOWN;
	attention_range = DEFAULT_ATTENTION_RANGE;
	speed = DEFAULT_SPEED;
	cost = DEFAULT_COST;
	build_time = DEFAULT_BUILD_TIME;

	move_lag = 8; // so gap is 0.125
	clear_path();
	path_place = 0;
	this->map = map;
	map->unit_map[grid.x][grid.y] = TILE_STILL_UNIT; // register location with master map
	time_out_counter = 0;
	face_direction = DOWN;
	this->active = true;

	// testing - 
	exclude_list = new list_t;
	init_list(exclude_list);
}

u8 unit_c::get_id()
{
	return id;
}

void unit_c::set_id(u8 id)
{
	this->id = id;
}

void unit_c::set_team_id(u8 team_id)
{
	this->team_id = team_id;
}

void unit_c::set_team_pal(palette_t pal)
{
	team_pal = pal;
}

void unit_c::idle()
{
	if (time_out_counter > 0)
	{
		time_out_counter--;
		return;
	}
	
	// reset map rego
	//map->unit_map[grid.x][grid.y] = TILE_FREE; 
	
	// check to see if at goal
	if ((grid.x != move_goal.x || grid.y != move_goal.y) && path[0] == UNDEFINED)
	{
		u8 i;
		path_holder_t ph;
		clear_path();
		// path to goal is to be requested
		ph = find_path(move_goal.x, move_goal.y, grid.x, grid.y, map, exclude_list);
		
		for (i = 0; i < MOVE_MAX; i++)
		{
			// print
			//if (ph.path[i] == UP_B) iprintf("\x1b[%d;0Hup    ",i);
			//else if (ph.path[i] == DOWN_B) iprintf("\x1b[%d;0Hdown  ",i);
			//else if (ph.path[i] == LEFT_B) iprintf("\x1b[%d;0Hleft  ",i);
			//else if (ph.path[i] == RIGHT_B) iprintf("\x1b[%d;0Hright ",i);
			//else if (ph.path[i] == 0) iprintf("\x1b[%d;0H      ",i);
			
			// copy
			if (ph.path[i] == UP_B) path[i] = UP;
			else if (ph.path[i] == DOWN_B) path[i] = DOWN;
			else if (ph.path[i] == LEFT_B) path[i] = LEFT;
			else if (ph.path[i] == RIGHT_B) path[i] = RIGHT;
		}
		path_place = 0;
	}
	else
	{
		// no path needed
		step_counter = 0;
		map->unit_map[grid.x][grid.y] = TILE_STILL_UNIT;
		delete_list(exclude_list);
	}
	
	float step_dist = 0.125f; // this value has to be 1 / move_lag
	vector_2d_u8_t new_goal;
	vector_2d_u8_t current_goal;
	
	if (grid.x != move_goal.x || grid.y != move_goal.y)
	{
		step_counter++;

		if (path[path_place] == UP)
		{
			face_direction = UP;
			if (map->unit_map[grid.x + 1][grid.y] == TILE_STILL_UNIT)
			{
				
				// check if this is the goal
				if (grid.x + 1 == move_goal.x && grid.y == move_goal.y)
				{
					// find a new goal close to the first goal
					current_goal.x = move_goal.x;
					current_goal.y = move_goal.y;
					new_goal = get_free_space(current_goal, map);
					move_goal.x = new_goal.x;
					move_goal.y = new_goal.y;
				}
				
				grid_push(exclude_list, grid.x + 1, grid.y);
				clear_path();
				time_out_counter = 4;
				grid_draw.x = grid.x;
				return;
			}
			else if (map->unit_map[grid.x + 1][grid.y] == TILE_MOVING_UNIT)
			{
				if (grid.x + 1 == move_goal.x && grid.y == move_goal.y)
				{
					current_goal.x = move_goal.x;
					current_goal.y = move_goal.y;
					new_goal = get_free_space(current_goal, map);
					move_goal.x = new_goal.x;
					move_goal.y = new_goal.y;
				}
				
				time_out_counter = 4;
				grid_draw.x = grid.x;
				return;
			}
			else
			{
				map->unit_map[grid.x][grid.y] = TILE_MOVING_UNIT;
				
				grid_draw.x += step_dist;
				if (step_counter == move_lag)
				{
					grid.x++;
					step_counter = 0;
					path_place++;
					grid_draw.x = grid.x;
					map->unit_map[grid.x - 1][grid.y] = TILE_FREE;
					map->unit_map[grid.x][grid.y] = TILE_MOVING_UNIT;
				}
			}
		}
		
		else if (path[path_place] == DOWN)
		{
			face_direction = DOWN;
			if (map->unit_map[grid.x - 1][grid.y] == TILE_STILL_UNIT)
			{
				if (grid.x - 1 == move_goal.x && grid.y == move_goal.y)
				{
					current_goal.x = move_goal.x;
					current_goal.y = move_goal.y;
					new_goal = get_free_space(current_goal, map);
					move_goal.x = new_goal.x;
					move_goal.y = new_goal.y;
				}

				grid_push(exclude_list, grid.x - 1, grid.y);
				clear_path();
				time_out_counter = 4;
				grid_draw.x = grid.x;
				return;
			}
			else if (map->unit_map[grid.x - 1][grid.y] == TILE_MOVING_UNIT)
			{
				if (grid.x - 1 == move_goal.x && grid.y == move_goal.y)
				{
					current_goal.x = move_goal.x;
					current_goal.y = move_goal.y;
					new_goal = get_free_space(current_goal, map);
					move_goal.x = new_goal.x;
					move_goal.y = new_goal.y;
				}
				
				time_out_counter = 4;
				grid_draw.x = grid.x;
				return;
			}
			else
			{
				map->unit_map[grid.x][grid.y] = TILE_MOVING_UNIT;
				grid_draw.x -= step_dist;
				if (step_counter == move_lag)
				{
					grid.x--;
					step_counter = 0;
					path_place++;
					grid_draw.x = grid.x;
					map->unit_map[grid.x + 1][grid.y] = TILE_FREE;
					map->unit_map[grid.x][grid.y] = TILE_MOVING_UNIT;
				}
			}
		}
		
		else if (path[path_place] == LEFT)
		{
			face_direction = LEFT;
			if (map->unit_map[grid.x][grid.y + 1] == TILE_STILL_UNIT)
			{
				if (grid.x == move_goal.x && grid.y + 1 == move_goal.y)
				{
					current_goal.x = move_goal.x;
					current_goal.y = move_goal.y;
					new_goal = get_free_space(current_goal, map);
					move_goal.x = new_goal.x;
					move_goal.y = new_goal.y;
				}
				
				grid_push(exclude_list, grid.x, grid.y + 1);
				clear_path();
				time_out_counter = 4;
				grid_draw.y = grid.y;
				return;
			}
			else if (map->unit_map[grid.x][grid.y + 1] == TILE_MOVING_UNIT)
			{
				if (grid.x == move_goal.x && grid.y + 1 == move_goal.y)
				{
					current_goal.x = move_goal.x;
					current_goal.y = move_goal.y;
					new_goal = get_free_space(current_goal, map);
					move_goal.x = new_goal.x;
					move_goal.y = new_goal.y;
				}

				time_out_counter = 4;
				grid_draw.y = grid.y;
				return;
			}
			else
			{
				map->unit_map[grid.x][grid.y] = TILE_MOVING_UNIT;
				grid_draw.y += step_dist;
				if (step_counter == move_lag)
				{
					grid.y++;
					step_counter = 0;
					path_place++;
					grid_draw.y = grid.y;
					map->unit_map[grid.x][grid.y - 1] = TILE_FREE;
					map->unit_map[grid.x][grid.y] = TILE_MOVING_UNIT;
				}
			}
		}
		
		else if (path[path_place] == RIGHT)
		{
			face_direction = RIGHT;
			if (map->unit_map[grid.x][grid.y - 1] == TILE_STILL_UNIT)
			{
				if (grid.x == move_goal.x && grid.y - 1 == move_goal.y)
				{
					current_goal.x = move_goal.x;
					current_goal.y = move_goal.y;
					new_goal = get_free_space(current_goal, map);
					move_goal.x = new_goal.x;
					move_goal.y = new_goal.y;
				}

				grid_push(exclude_list, grid.x, grid.y - 1);
				clear_path();
				time_out_counter = 4;
				grid_draw.y = grid.y;
				return;
			}
			if (map->unit_map[grid.x][grid.y - 1] == TILE_MOVING_UNIT)
			{
				if (grid.x == move_goal.x && grid.y - 1 == move_goal.y)
				{
					current_goal.x = move_goal.x;
					current_goal.y = move_goal.y;
					new_goal = get_free_space(current_goal, map);
					move_goal.x = new_goal.x;
					move_goal.y = new_goal.y;
				}
				
				time_out_counter = 4;
				grid_draw.y = grid.y;
				return;
			}
			else
			{
				map->unit_map[grid.x][grid.y] = TILE_MOVING_UNIT;
				
				grid_draw.y -= step_dist;
				if (step_counter == move_lag)
				{
					grid.y--;
					step_counter = 0;
					path_place++;
					grid_draw.y = grid.y;
					map->unit_map[grid.x][grid.y + 1] = TILE_FREE;
					map->unit_map[grid.x][grid.y] = TILE_MOVING_UNIT;
				}
			}
		}

		if (path[path_place + 1] == UNDEFINED) path_place = 0;
		path[path_place] = UNDEFINED;
		clear_path();
	}
	
}

void unit_c::draw()
{
	// this function should not be called if the unit isn't active,
	// but just in case...
	if (this->active == true)
	{
		glPushMatrix();
		glRotateZ(45); // angle for grid
		glTranslatef(grid_draw.x, grid_draw.y, 0); // translate into position
		//glTranslatef(grid.x, grid.y, 0); // for snap movement
		glPushMatrix();
			//glRotateZ(-45);
			
			// quick fix: moves unit above grid point
			glTranslatef(0.0f, 0.0f, 0.1f); // (-(TILE_X / 2), (TILE_Y / 4), 0)
			
			// face_direction should be set to UP, DOWN, LEFT, or RIGHT
			
		switch (this->team_id)
		{
			case 0:
				engine.get_meshtable()->get_default_mesh()->draw();
				break;
			case 1:
				engine.get_meshtable()->get_default_mesh()->draw();
				break;
			case 2:
				engine.get_meshtable()->get_default_mesh()->draw();
				break;
			default:
				engine.get_meshtable()->get_default_mesh()->draw();
				break;
		}
		glPopMatrix(1);

		// Return the matrix stack back one
		glPopMatrix(1);
		
		// debug - draw path
		//if (path[path_place] != UNDEFINED) draw_path();
	}
}

void unit_c::draw_path()
{
	u8 current_x = grid.x;
	u8 current_y = grid.y;
	u8 next_x = current_x;
	u8 next_y = current_y;
	u8 path_step = path_place;
	
	glPushMatrix();
		// angle for grid
		glRotateZ(45);
		// center of block
		glTranslatef(0.5f, 0.5f, 0);
		
		// lines
		glColor3f(0.0, 1.0, 0.0);
		
		// first line
		if (path[path_step] == UP) next_x++;
		else if (path[path_step]  == DOWN) next_x--;
		else if (path[path_step]  == LEFT) next_y++;
		else if (path[path_step]  == RIGHT) next_y--;
		
		glBegin(GL_QUADS);
			glVertex3f(next_x, next_y, 0.1);
			glVertex3f(next_x, next_y, 0.1);
			glVertex3f(current_x, current_y, 0.1);
			glVertex3f(current_x, current_y, 0.1);
		glEnd();
		
		// the rest of the lines
		while (path[path_step + 1] != UNDEFINED)
		{
			if (path[path_step + 1] == UP) next_x++;
			else if (path[path_step + 1]  == DOWN) next_x--;
			else if (path[path_step + 1]  == LEFT) next_y++;
			else if (path[path_step + 1]  == RIGHT) next_y--;
			
			glBegin(GL_QUADS);
				glVertex3f(current_x, current_y, 0.1);
				glVertex3f(current_x, current_y, 0.1);
				glVertex3f(next_x, next_y, 0.1);
				glVertex3f(next_x, next_y, 0.1);
			glEnd();
			
			path_step++;
			current_x = next_x;
			current_y = next_y;
			
		}
	glPopMatrix(1);
}

void unit_c::clear_all()
{
	active = false;
	grid.x = -1;
	grid.y = -1;
	team_id = 0;
	move_goal.x = grid.x;
	move_goal.y = grid.y;
}

void unit_c::set_active(bool status)
{
	active = status;
}

bool unit_c::get_active()
{
	return active;
}

vector_2di_t unit_c::get_grid()
{
	return grid;
}

void unit_c::set_move_goal(int goal_x, int goal_y)
{
	move_goal.x = goal_x;
	move_goal.y = goal_y;
	clear_path();
}

void unit_c::clear_path()
{
	u8 i;
	
	for (i = 0; i < (UNIT_MINI_PATH); i++)
	{
		path[i] = UNDEFINED;
	}
}

void unit_c::set_move_lag(u8 value)
{
	move_lag = value;
}

void unit_c::grid_move(int mod, int x_or_y)
{
	
	float step_dist = 0.25f; // this value has to be 1 / move_lag
	
	int mod_x = 0, mod_y = 0;
	
	if (x_or_y == X_MOD)
	{
		mod_x = mod;
		mod_y = 0;
	}
	else if (x_or_y == Y_MOD)
	{
		mod_x = 0;
		mod_y = mod;
	}
	else return;
	
	if (map->unit_map[grid.y + mod_y][grid.x + mod_x] == TILE_STILL_UNIT)
	{
		// latter, make this look for a new path with new blockade
		// for now, treat same as moving unit blockade
		time_out_counter = 4;
		if (x_or_y == X_MOD) grid_draw.x = grid.x;
		else if (x_or_y == Y_MOD) grid_draw.y = grid.y;
		return;
	}
	else if (map->unit_map[grid.y + mod_y][grid.x + mod_x] == TILE_MOVING_UNIT)
	{
		time_out_counter = 4;
		if (x_or_y == X_MOD) grid_draw.x = grid.x;
		else if (x_or_y == Y_MOD) grid_draw.y = grid.y;
		return;
	}
	else
	{
		map->unit_map[grid.y][grid.x] = TILE_MOVING_UNIT;
		
		if (mod > 0)
		{
			if (x_or_y == X_MOD) grid_draw.x += step_dist;
			else if (x_or_y == Y_MOD) grid_draw.y += step_dist;
		}
		else if (mod < 0)
		{
			if (x_or_y == X_MOD) grid_draw.x -= step_dist;
			else if (x_or_y == Y_MOD) grid_draw.y -= step_dist;
		}
		
		if (step_counter == move_lag)
		{
			// has reached the next grid space
			if (mod > 0)
			{
				if (x_or_y == X_MOD) grid.x++;
				else if (x_or_y == Y_MOD) grid.y++;
			}
			else if (mod < 0)
			{
				if (x_or_y == X_MOD) grid.x--;
				else if (x_or_y == Y_MOD) grid.y--;
			}
			
			step_counter = 0;
			path_place++;
			if (x_or_y == X_MOD) grid_draw.x = grid.x;
			else if (x_or_y == Y_MOD) grid_draw.y = grid.y;
			map->unit_map[grid.y - mod_y][grid.x - mod_x] = TILE_FREE;
			map->unit_map[grid.y][grid.x] = TILE_MOVING_UNIT;
		}
	}
}

void unit_c::ability_1()
{
}
	
void unit_c::ability_2()
{
}

// end of file
