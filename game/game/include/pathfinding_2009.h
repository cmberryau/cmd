/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: pathfinding_2009.h
 * Date: 4th of April, 2010.
 * Author(s): Patrick Randell
 * Discription: Handles algorithms for AI paths. This version has not been converted into a class,
 *     but is currently being used. I plan to change to the class based pathfinding method once it
 *     has been sorted out. The suffix in the file name is 2009 because I originally wrote this 
 *     version of this pathfinding algorithm early 2009.
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef PATHFINDING_2009_H
#define PATHFINDING_2009_H

// libs
#include <nds.h>
#include <stdio.h>

// files
#include "grid_pop.h"
#include "test_map.h"

// get tile types from map.c
#include "map.h"

// defines
#define LEVEL_WIDTH		MAP_X_Y_MAX
#define LEVEL_HEIGHT	MAP_X_Y_MAX
#define MOVE_MAX		128//(MAP_X_Y_MAX * MAP_X_Y_MAX) / 2

#define PATH_GOOD		1
#define PATH_BAD		-1
#define LOOP_CHECKS		5

// directions
#define UP_B	1
#define DOWN_B	2
#define LEFT_B	3
#define RIGHT_B	4

enum path_direction_e
{
	UNDEFINED, UP, DOWN, LEFT, RIGHT
};

// structs
// object Type
typedef struct{
   s8 x;
   s8 y;
} object_t;

// node
typedef struct
{
   s8 x; // location
   s8 y;
   s32 h_value; // heuristic values
   s32 g_value;
   s32 f_value;
   object_t parent; // parent
} node_t;

// path finder
typedef struct
{
	u8 path[MOVE_MAX];
} path_holder_t;
typedef path_holder_t* path_holder_t_ptr;

// functions
path_holder_t find_path(s32 start_x, s32 start_y, s32 finish_x, s32 finish_y, map_c_ptr map, list_t_ptr exclude_list);
s8 find_path_b(path_holder_t_ptr final_path,s32 start_x, s32 start_y, s32 finish_x, s32 finish_y, map_c_ptr map, list_t_ptr exclude_list);

#endif

// end of file
