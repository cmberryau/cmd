/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: grid_pop.h
 * Date: 8th of May, 2010.
 * Author(s): Patrick Randell
 * Discription: grid-pop algoritm. This uses a map to find an empty place for a unit.
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef GRID_POP_H
#define GRID_POP_H

// files
#include "types.h"
#include "map.h"

// types
typedef struct grid_node_pre
{
	vector_2d_u8_t data;
	bool checked;
	struct grid_node_pre* next;
} grid_node_t;
typedef grid_node_t* grid_node_t_ptr;

typedef struct list_pre
{
	grid_node_t_ptr head;
	u8 node_count;
} list_t;
typedef list_t* list_t_ptr;

// functions

/** get_free_space
  * 
  * uses the given map to find the closest spare grid space
  * to the given position.
  */
vector_2d_u8_t get_free_space(vector_2d_u8_t current, map_c_ptr map);

void init_list(list_t_ptr list);
void grid_push(list_t_ptr list, u8 x, u8 y);
void grid_push_fifo(list_t_ptr list, u8 x, u8 y);
grid_node_t_ptr grid_pop(list_t_ptr list);
grid_node_t_ptr get_free_space(list_t_ptr list);
void delete_list(list_t_ptr list);
bool check_for_node(list_t_ptr, u8 x, u8 y);
bool check_if_free(map_c_ptr map, list_t_ptr open_list, list_t_ptr used, grid_node_t_ptr node);

#endif 