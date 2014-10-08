/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: map.cpp
 * Date: 19th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry
 * Discription: map class, see header.
 * Copyright: (c) SteelCat 2009-2010 
==================================================================================================*/

// header file
#include "map.h"
#include "engine.h"

extern engine_c engine;

void map_c::set_draw_map(map_holder_c_ptr new_map)
{
	u8 i, j;
	for (i = 0; i < MAP_X_Y_MAX; i++)
	{
		for (j = 0; j < MAP_X_Y_MAX; j++)
		{
			draw_map[i][j] = new_map->map[i][j];
		}
	}
	clear_unit_map();
}

void map_c::set_draw_map(const s8 new_map[][MAP_X_Y_MAX])
{
	u8 i, j;
	for (i = 0; i < MAP_X_Y_MAX; i++)
	{
		for (j = 0; j < MAP_X_Y_MAX; j++)
		{
			draw_map[i][j] = new_map[i][j];
		}
	}
	clear_unit_map();
}

void map_c::set_wall_map(map_holder_c_ptr new_map)
{
	u8 i, j;
	for (i = 0; i < MAP_X_Y_MAX; i++)
	{
		for (j = 0; j < MAP_X_Y_MAX; j++)
		{
			this->wall_map[i][j] = new_map->map[i][j];
		}
	}
	clear_unit_map();
}

void map_c::set_wall_map(const s8 new_map[][MAP_X_Y_MAX])
{
	u8 i, j;
	for (i = 0; i < MAP_X_Y_MAX; i++)
	{
		for (j = 0; j < MAP_X_Y_MAX; j++)
		{
			wall_map[i][j] = new_map[i][j];
		}
	}
	clear_unit_map();
}

void map_c::draw_3d_map()
{
	u8 i, j;
	u8 x_gap, y_gap;

	x_gap = TILE_X; 
	y_gap = TILE_Y; 
	
	glPushMatrix();
	// angle grid
	glRotateZ( 45 );
	
	glTranslate3f32( inttof32( -1 ), inttof32( -1 ), inttof32( 0 ) );
	for (i = 0; i < size.x ; i++)
	{
		glTranslate3f32( inttof32( 0 ), inttof32( 1 ), inttof32( 0 ) );
		for (j = 0; j < size.y ; j++)
		{
			glTranslate3f32( inttof32( 1 ), inttof32( 0 ), inttof32( 0 ) );
			/* Draw the tile */
			if (draw_map[j][i] == 1){
				/* Tile type 1 */
				engine.get_meshtable()->get_map_tile_mesh()->draw();
			}
			else if (draw_map[j][i] == 2){
				/* Tile type 2 */
				engine.get_meshtable()->get_map_tile_mesh()->draw();
			}
			else if (draw_map[j][i] == 0){
				/* Tile type 0 - blank */
			} 
		}
		glTranslate3f32( inttof32( -j ), inttof32( 0 ), inttof32( 0 ) );
	}
	glPopMatrix( 1 );
}

void map_c::debug_print_draw_map()
{
	// 8x8
	iprintf("\x1b[15;0H%d%d%d%d%d%d%d%d\n%d%d%d%d%d%d%d%d\n%d%d%d%d%d%d%d%d\n%d%d%d%d%d%d%d%d\n%d%d%d%d%d%d%d%d\n%d%d%d%d%d%d%d%d\n%d%d%d%d%d%d%d%d\n%d%d%d%d%d%d%d%d\n",
	draw_map[0][0],draw_map[1][0],draw_map[2][0],draw_map[3][0],draw_map[4][0],draw_map[5][0],draw_map[6][0],draw_map[7][0],
	draw_map[0][1],draw_map[1][1],draw_map[2][1],draw_map[3][1],draw_map[4][1],draw_map[5][1],draw_map[6][1],draw_map[7][1],
	draw_map[0][2],draw_map[1][2],draw_map[2][2],draw_map[3][2],draw_map[4][2],draw_map[5][2],draw_map[6][2],draw_map[7][2],
	draw_map[0][3],draw_map[1][3],draw_map[2][3],draw_map[3][3],draw_map[4][3],draw_map[5][3],draw_map[6][3],draw_map[7][3],
	draw_map[0][4],draw_map[1][4],draw_map[2][4],draw_map[3][4],draw_map[4][4],draw_map[5][4],draw_map[6][4],draw_map[7][4],
	draw_map[0][5],draw_map[1][5],draw_map[2][5],draw_map[3][5],draw_map[4][5],draw_map[5][5],draw_map[6][5],draw_map[7][5],
	draw_map[0][6],draw_map[1][6],draw_map[2][6],draw_map[3][6],draw_map[4][6],draw_map[5][6],draw_map[6][6],draw_map[7][6],
	draw_map[0][7],draw_map[1][7],draw_map[2][7],draw_map[3][7],draw_map[4][7],draw_map[5][7],draw_map[6][7],draw_map[7][7]
	);
}

void map_c::debug_print_wall_map()
{
	// 8x8
	iprintf("\x1b[15;0H%d%d%d%d%d%d%d%d\n%d%d%d%d%d%d%d%d\n%d%d%d%d%d%d%d%d\n%d%d%d%d%d%d%d%d\n%d%d%d%d%d%d%d%d\n%d%d%d%d%d%d%d%d\n%d%d%d%d%d%d%d%d\n%d%d%d%d%d%d%d%d\n",
	wall_map[0][0],wall_map[1][0],wall_map[2][0],wall_map[3][0],wall_map[4][0],wall_map[5][0],wall_map[6][0],wall_map[7][0],
	wall_map[0][1],wall_map[1][1],wall_map[2][1],wall_map[3][1],wall_map[4][1],wall_map[5][1],wall_map[6][1],wall_map[7][1],
	wall_map[0][2],wall_map[1][2],wall_map[2][2],wall_map[3][2],wall_map[4][2],wall_map[5][2],wall_map[6][2],wall_map[7][2],
	wall_map[0][3],wall_map[1][3],wall_map[2][3],wall_map[3][3],wall_map[4][3],wall_map[5][3],wall_map[6][3],wall_map[7][3],
	wall_map[0][4],wall_map[1][4],wall_map[2][4],wall_map[3][4],wall_map[4][4],wall_map[5][4],wall_map[6][4],wall_map[7][4],
	wall_map[0][5],wall_map[1][5],wall_map[2][5],wall_map[3][5],wall_map[4][5],wall_map[5][5],wall_map[6][5],wall_map[7][5],
	wall_map[0][6],wall_map[1][6],wall_map[2][6],wall_map[3][6],wall_map[4][6],wall_map[5][6],wall_map[6][6],wall_map[7][6],
	wall_map[0][7],wall_map[1][7],wall_map[2][7],wall_map[3][7],wall_map[4][7],wall_map[5][7],wall_map[6][7],wall_map[7][7]
	);
}
void map_c::clear_unit_map()
{
	u8 i, j;
	
	for (i = 0; i < MAP_X_Y_MAX; i++)
	{
		for (j = 0; j < MAP_X_Y_MAX; j++)
		{
			unit_map[i][j] = TILE_FREE;
		}
	}
}

// new
map_c::map_c(u8 x, u8 y)
{
	size_x = x;
	size_y = y;
	size_total = x * y;
	draw_array = new s8[size_total];
	flood(DRAW, TILE_FREE);
	wall_array = new s8[size_total];
	flood(WALL, TILE_FREE);
	unit_array = new s8[size_total];
	flood(UNIT, TILE_FREE);
}

map_c::~map_c()
{
	delete &draw_array;
	delete &wall_array;
	delete &unit_array;
}

u8 map_c::array_to_x(u16 array_id)
{
	u16 current = 0;
	u8 x_count = 0;
	u8 y_count = 0;
	
	while (current != array_id)
	{
		if (x_count == size_x)
		{
			x_count = 0;
			y_count++;
		}
		x_count++;
		current++;
	}
	return x_count;
}

u8 map_c::array_to_y(u16 array_id)
{
	u16 current = 0;
	u8 x_count = 0;
	u8 y_count = 0;
	
	while (current != array_id)
	{
		if (x_count == size_x)
		{
			x_count = 0;
			y_count++;
		}
		x_count++;
		current++;
	}
	return y_count;
}

void map_c::flood(array_type_e array_type, u8 flood_type)
{
	s8* array;

	if (array_type == DRAW) array = draw_array;
	else if (array_type == WALL) array = wall_array;
	else if (array_type == UNIT) array = unit_array;
	else return;

	u16 i;
	for (i = 0; i < size_total; i++)
	{
		array[i] = flood_type;
	}
}

void map_c::set_array(array_type_e array_type, u8* source)
{
	s8* array;

	if (array_type == DRAW) array = draw_array;
	else if (array_type == WALL) array = wall_array;
	else if (array_type == UNIT) array = unit_array;
	else return;

	u16 i;
	for (i = 0; i < size_total; i++)
	{
		array[i] = source[i];
	}
}

u8 map_c::get_size_x()
{
	return size_x;
}

u8 map_c::get_size_y()
{
	return size_y;
}

// end of file
