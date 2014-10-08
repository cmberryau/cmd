/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: grid_pop.cpp
 * Date: 8th of May, 2010.
 * Author(s): Patrick Randell
 * Description: see header file.
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

// header file
#include "grid_pop.h"

// functions

vector_2d_u8_t get_free_space(vector_2d_u8_t current, map_c_ptr map)
{
	vector_2d_u8_t result;
	bool space_found = false;

	list_t_ptr open_list = new list_t;
	list_t_ptr used_list = new list_t;
	init_list(open_list);
	init_list(used_list);

	// add the base node to the used list
	grid_push(used_list, current.x, current.y);
	
	//add the first 4 nodes to get the ball rolling
	grid_push(open_list, current.x + 1, current.y);
	grid_push(open_list, current.x - 1, current.y);
	grid_push(open_list, current.x, current.y + 1);
	grid_push(open_list, current.x, current.y - 1);
	
	grid_node_t_ptr current_node;

	while (space_found == false)
	{
		// get top node
		current_node = grid_pop(open_list);

		// check if it's free
		if (check_if_free(map,open_list,used_list, current_node) == true)
		{
			space_found = true;
			result.x = current_node->data.x;
			result.y = current_node->data.y;
			continue;
		}

		// expand from this node,
		// up
		if (check_for_node(used_list, current_node->data.x, current_node->data.y + 1) == false
		&&  map->wall_map[current_node->data.x][current_node->data.y + 1] == TILE_FREE
		)
		{
			grid_push_fifo(open_list, current_node->data.x, current_node->data.y + 1);
		}
		// down
		if (check_for_node(used_list, current_node->data.x, current_node->data.y - 1) == false
		&&  map->wall_map[current_node->data.x][current_node->data.y - 1] == TILE_FREE)
		{
			grid_push_fifo(open_list, current_node->data.x, current_node->data.y - 1);
		}
		// left
		if (check_for_node(used_list, current_node->data.x - 1, current_node->data.y) == false
		&&  map->wall_map[current_node->data.x - 1][current_node->data.y] == TILE_FREE)
		{
			grid_push_fifo(open_list, current_node->data.x - 1, current_node->data.y);
		}
		// right
		if (check_for_node(used_list, current_node->data.x + 1, current_node->data.y) == false
		&&  map->wall_map[current_node->data.x + 1][current_node->data.y] == TILE_FREE)
		{
			grid_push_fifo(open_list, current_node->data.x + 1, current_node->data.y);
		}

		// add it to the used list
		grid_push(used_list, current_node->data.x, current_node->data.y);
	}

	return result;
}

void init_list(list_t_ptr list)
{
	list->head = null;
	list->node_count = 0;
}

void grid_push(list_t_ptr list, u8 x, u8 y)
{
	grid_node_t_ptr new_node = new grid_node_t;
	new_node->data.x = x;
	new_node->data.y = y;
	new_node->next = list->head;
	list->head = new_node;
	list->node_count++;
}

void grid_push_fifo(list_t_ptr list, u8 x, u8 y)
{
	grid_node_t_ptr new_node = new grid_node_t;
	new_node->data.x = x;
	new_node->data.y = y;
	new_node->next = null;
	
	grid_node_t_ptr current_node;
	current_node = list->head;

	while (current_node->next != null)
	{
		current_node = current_node->next;
	}
	current_node->next = new_node;
	list->node_count++;
}

grid_node_t_ptr grid_pop(list_t_ptr list)
{
	grid_node_t_ptr return_node;
	return_node = list->head;
	if (list->head != null) list->head = list->head->next;
	else list->head = null;
	list->node_count--;
	return return_node;
}
void delete_list(list_t_ptr list)
{
	grid_node_t_ptr current_node;
	current_node = list->head;
	while (current_node != null)
	{
		list->head = list->head->next;
		delete current_node;
		current_node = list->head;
	}
}

bool check_for_node(list_t_ptr list, u8 x, u8 y)
{
	grid_node_t_ptr current_node;
	current_node = list->head;
	if (current_node == null)
	{
		return false;
	}
	while (current_node != null)
	{
		if (current_node->data.x == x)
		{
			if (current_node->data.y == y)
			{
				return true;
			}
		}
		current_node = current_node->next;
	}	
	return false;
}

bool check_if_free(map_c_ptr map, list_t_ptr open_list, list_t_ptr used_list, grid_node_t_ptr node)
{
	if (map->wall_map[node->data.x][node->data.y] != TILE_WALL
	&&  map->unit_map[node->data.x][node->data.y] != TILE_STILL_UNIT
	&&  node->data.x >= 0
	&&  node->data.y >= 0
	&&  node->data.x <= map->get_x_max()
	&&  node->data.y <= map->get_y_max()
	&&  check_for_node(used_list, node->data.x, node->data.y) == false)
	{
		return true;
	}
	return false;
}

// end if file
