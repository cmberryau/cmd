/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: map.h
 * Date: 19th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry
 * Description: map class, 
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef MAP_H
#define MAP_H

// libs
#include <nds.h>
#include <stdio.h> // only for debug printing

// files
#include "types.h"

// defines
#define TILE_X 1
#define TILE_Y 1
#define MAP_X_Y_MAX 16

// values for diffrernt array types
enum array_type_e
{
	DRAW, WALL, UNIT
};

// master map values, 
// always use these defines when referencing anything to do with the map
#define TILE_WALL			0 // units cannot move to this tile
#define TILE_FREE			1 // nothing on map
#define TILE_STILL_UNIT		2 // tile contains a unit that is not moving
#define TILE_MOVING_UNIT	3 // a unit is curently using this tile to move

// map holder for passing map data around
class map_holder_c
{
public:
	s8 map[MAP_X_Y_MAX][MAP_X_Y_MAX];
	void copy_array(const s8 new_map[][MAP_X_Y_MAX])
	{
		u8 i, j;
		for (i = 0; i < MAP_X_Y_MAX; i++)
		{
			for (j = 0; j < MAP_X_Y_MAX; j++)
			{
				map[i][j] = new_map[i][j];
			}
		} 
	}
	void fill(s8 value) 
	{
		u8 i, j;
		for (i = 0; i < MAP_X_Y_MAX; i++)
		{
			for (j = 0; j < MAP_X_Y_MAX; j++)
			{
				map[i][j] = value;
			}
		}
	}
};
typedef map_holder_c* map_holder_c_ptr;


class map_c
{
private:
// new
	s8* draw_array;
	s8* wall_array;
	s8* unit_array;
	u8 size_x;
	u8 size_y;
	u16 size_total;

// old
	vector_2di_t size;
	
public:
// new
	map_c(u8 x, u8 y);
	map_c(){}; // delete after implimentation
	~map_c();
	
	u8 array_to_x(u16 array_id);
	u8 array_to_y(u16 array_id);
	void flood(array_type_e array_type, u8 flood_type);
	void set_array(array_type_e array_type, u8* source);
	u8 get_size_x();
	u8 get_size_y();


// old
	// map array, this is public for now
	s8 draw_map[MAP_X_Y_MAX][MAP_X_Y_MAX];
	s8 wall_map[MAP_X_Y_MAX][MAP_X_Y_MAX];
	s8 unit_map[MAP_X_Y_MAX][MAP_X_Y_MAX];
	
	// sets the map array
//	void set_map(const int map[][MAP_X_Y_MAX]);
	void set_draw_map(map_holder_c_ptr new_map);
	void set_draw_map(const s8 new_map[][MAP_X_Y_MAX]);
	void set_wall_map(map_holder_c_ptr new_map);
	void set_wall_map(const s8 new_map[][MAP_X_Y_MAX]);

	// init function used to input variables
	void define_size(u16 x, u16 y)
	{ size.x = x; size.y = y; }
	
	int get_x_max() { return size.x; }
	int get_y_max() { return size.y; }

	// draws the map tiles in the grid
	void draw_3d_map();
	
	void debug_print_draw_map();
	void debug_print_wall_map();
	
	void clear_unit_map();
};
// pointer
typedef map_c* map_c_ptr;

// functions
void clear_unit_map(int map[][MAP_X_Y_MAX]);

#endif

// end of file
