/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: pathfinding_2009.cpp
 * Date: 4th of April, 2010.
 * Author(s): Patrick Randell
 * Discription: See header.
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

// header file
#include "pathfinding_2009.h"

path_holder_t find_path(s32 start_x, s32 start_y, s32 finish_x, s32 finish_y, map_c_ptr map, list_t_ptr exclude_list)
{
	u8 i, j;
	u8 path_step = 0;
	
	// lists
	bool used_nodes[LEVEL_WIDTH][LEVEL_HEIGHT];
	bool open_nodes[LEVEL_WIDTH][LEVEL_HEIGHT];
	node_t node_b[LEVEL_WIDTH][LEVEL_HEIGHT];
	u8 path_b[MOVE_MAX];
	
	// lowest on open list
	s32 current_lowest_f = MOVE_MAX * 100;
	s8 lowest_f_x = -1;
	s8 lowest_f_y = -1;
	
	// variables for the current node
	s32 current_x = start_x;
	s32 current_y = start_y;
	
	// clear our lists of used and open nodes
	for (i = 0; i < LEVEL_WIDTH; i++)
	{
		for (j = 0; j < LEVEL_HEIGHT; j++)
		{
			used_nodes[i][j] = false;
			open_nodes[i][j] = false;
		}
	}	
	
	// clear the final path list
	for (i = 0; i < MOVE_MAX; i++)
	{
		path_b[i] = 0;
	}   
   
	// make node hold it's location
	node_b[current_x][current_y].x = start_x;
	node_b[current_x][current_y].y = start_y;
	
	// give the first node it's values
	node_b[current_x][current_y].h_value = (abs(node_b[current_x][current_y].x - finish_x) + abs(node_b[current_x][current_y].y - finish_y));
	node_b[current_x][current_y].g_value = 0; //since it's parent node will be NULL as this is the start
	node_b[current_x][current_y].f_value = node_b[current_x][current_y].h_value + node_b[current_x][current_y].g_value;
	
	// parent node
	node_b[current_x][current_y].parent.x = start_x;
	node_b[current_x][current_y].parent.y = start_y;
	
	// start the search
	while (1)
	{
		// check to see if we are finished
		if (current_x == finish_x && current_y == finish_y) break;
		
// ----- To do: check to see it there are still open nodes to check
      
		// add this current one to the used nodes list, and remove it from the open nodes
		used_nodes[current_x][current_y] = true;
		open_nodes[current_x][current_y] = false;
      
		// look up
		if (map->wall_map[current_x][current_y - 1] != TILE_WALL // is not a wall
		&& current_y - 1 >= 0 // is in range of the grid 
		&& open_nodes[current_x][current_y - 1] == false // is not on the open list
		&& used_nodes[current_x][current_y - 1] == false // is yet to be used
		&& check_for_node(exclude_list, current_x, current_y - 1) == false) // is not on the exclude list
		{ 
			// start to give it it's values
			node_b[current_x][current_y - 1].x = current_x;
   			node_b[current_x][current_y - 1].y = current_y - 1;
   			
   			node_b[current_x][current_y - 1].h_value = (abs(node_b[current_x][current_y - 1].x - finish_x) + abs(node_b[current_x][current_y - 1].y - finish_y));
   			node_b[current_x][current_y - 1].g_value = 1 + node_b[current_x][current_y].g_value;
   			node_b[current_x][current_y - 1].f_value = node_b[current_x][current_y - 1].h_value + node_b[current_x][current_y - 1].g_value;
   			
   			node_b[current_x][current_y - 1].parent.x = current_x;
   			node_b[current_x][current_y - 1].parent.y = current_y;
   			
   			// add this node_b to the open list
   			open_nodes[current_x][current_y - 1] = true;
  		} // end if up 		
  		
  		// look down
		if (map->wall_map[current_x][current_y + 1] != TILE_WALL 
		&& current_y + 1 <= LEVEL_HEIGHT 
		&& open_nodes[current_x][current_y + 1] == false 
		&& used_nodes[current_x][current_y + 1] == false
		&& check_for_node(exclude_list, current_x, current_y + 1) == false)
		{
			// start to give it it's values
			node_b[current_x][current_y + 1].x = current_x;
			node_b[current_x][current_y + 1].y = current_y + 1;
   		
			node_b[current_x][current_y + 1].h_value = (abs(node_b[current_x][current_y + 1].x - finish_x) + abs(node_b[current_x][current_y + 1].y - finish_y));
			node_b[current_x][current_y + 1].g_value = 1 + node_b[current_x][current_y].g_value;
			node_b[current_x][current_y + 1].f_value = node_b[current_x][current_y + 1].h_value + node_b[current_x][current_y + 1].g_value;
   		
			node_b[current_x][current_y + 1].parent.x = current_x;
			node_b[current_x][current_y + 1].parent.y = current_y;
   		
			// add this node_b to the open list
			open_nodes[current_x][current_y + 1] = true;
  		} // end if down	
  		
  		// look left
		if (map->wall_map[current_x - 1][current_y] != TILE_WALL 
		&& current_x - 1 >= 0 
		&& open_nodes[current_x - 1][current_y] == false 
		&& used_nodes[current_x - 1][current_y] == false
		&& check_for_node(exclude_list, current_x - 1, current_y) == false)
		{
			// start to give it it's values
			node_b[current_x - 1][current_y].x = current_x - 1;
			node_b[current_x - 1][current_y].y = current_y;
   		
			node_b[current_x - 1][current_y].h_value = (abs(node_b[current_x - 1][current_y].x - finish_x) + abs(node_b[current_x - 1][current_y].y - finish_y));
			node_b[current_x - 1][current_y].g_value = 1 + node_b[current_x][current_y].g_value;
			node_b[current_x - 1][current_y].f_value = node_b[current_x - 1][current_y].h_value + node_b[current_x - 1][current_y].g_value;
   		
			node_b[current_x - 1][current_y].parent.x = current_x;
			node_b[current_x - 1][current_y].parent.y = current_y;
   		
			// add this node_b to the open list
			open_nodes[current_x - 1][current_y] = true;
  		} // end if left 		
  		
  		// look right
		if (map->wall_map[current_x + 1][current_y] != TILE_WALL 
		&& current_x + 1 <= LEVEL_WIDTH 
		&& open_nodes[current_x + 1][current_y] == false 
		&& used_nodes[current_x + 1][current_y] == false
		&& check_for_node(exclude_list, current_x + 1, current_y) == false)
		{
			// start to give it it's values
			node_b[current_x + 1][current_y].x = current_x + 1;
			node_b[current_x + 1][current_y].y = current_y;
			
			node_b[current_x + 1][current_y].h_value = (abs(node_b[current_x + 1][current_y].x - finish_x) + abs(node_b[current_x + 1][current_y].y - finish_y));
			node_b[current_x + 1][current_y].g_value = 1 + node_b[current_x][current_y].g_value;
			node_b[current_x + 1][current_y].f_value = node_b[current_x + 1][current_y].h_value + node_b[current_x + 1][current_y].g_value;
			
			node_b[current_x + 1][current_y].parent.x = current_x;
			node_b[current_x + 1][current_y].parent.y = current_y;
			
			// add this node_b to the open list
			open_nodes[current_x + 1][current_y] = true;
  		} // end if right
		
		// set lowest to max
  		current_lowest_f = MOVE_MAX * 10;
  		
  		// decide on the new current node
  		// search for the lowest
		for (i = 0; i < LEVEL_WIDTH; i++)
		{
			for (j = 0; j < LEVEL_HEIGHT; j++)
			{
				if (open_nodes[i][j] == true && used_nodes[i][j] == false)
				{
					if (node_b[i][j].f_value < current_lowest_f)
					{
						current_lowest_f = node_b[i][j].f_value;
						lowest_f_x = node_b[i][j].x;
						lowest_f_y = node_b[i][j].y;
					}   
				}   
			}
		}
 		current_x = lowest_f_x;
 		current_y = lowest_f_y;
	} // end while
	
 	while (1)
 	{
		if (node_b[current_x][current_y].parent.x == current_x && node_b[current_x][current_y].parent.y == (current_y - 1)) path_b[path_step] = UP_B;
		else if (node_b[current_x][current_y].parent.x == current_x && node_b[current_x][current_y].parent.y == (current_y + 1)) path_b[path_step] = DOWN_B;
		else if (node_b[current_x][current_y].parent.x == (current_x - 1) && node_b[current_x][current_y].parent.y == current_y) path_b[path_step] = LEFT_B;
		else if (node_b[current_x][current_y].parent.x == (current_x + 1) && node_b[current_x][current_y].parent.y == current_y) path_b[path_step] = RIGHT_B;
		else path_b[path_step] = 0;
		path_step++;
 	   
		// check to see if we are finished
		if (current_x == start_x && current_y == start_y) break;
		
		if (path_b[path_step-1] == UP_B) current_y--;
		if (path_b[path_step-1] == DOWN_B) current_y++;
		if (path_b[path_step-1] == LEFT_B) current_x--;
		if (path_b[path_step-1] == RIGHT_B) current_x++;
	} // end while  
	
	// swap directions to make same as unit and grid
	for (i = 0; i < MOVE_MAX; i++)
	{
		if (path_b[i] == UP_B) path_b[i] = RIGHT_B;
		else if (path_b[i] == DOWN_B) path_b[i] = LEFT_B;
		else if (path_b[i] == LEFT_B) path_b[i] = DOWN_B;
		else if (path_b[i] == RIGHT_B) path_b[i] = UP_B;
	}
	
	/*
	//print the path
	for (i=0;i<MOVEMAX;i++)
	{
	   	if (path_b[i] == UP_B) iprintf("\x1b[%d;0Hup    ",i);
 		else if (path_b[i] == DOWN_B) iprintf("\x1b[%d;0Hdown  ",i);
 		else if (path_b[i] == LEFT_B) iprintf("\x1b[%d;0Hleft  ",i);
 		else if (path_b[i] == RIGHT_B) iprintf("\x1b[%d;0Hright ",i);
 		else i++;
	}
	*/
	
	path_holder_t finished_path;
	for (i = 0; i < MOVE_MAX; i++) finished_path.path[i] = path_b[i];
	
	return finished_path;
}   


//==================================================================================================================================================================

s8 find_path_b(path_holder_t_ptr final_path,s32 start_x, s32 start_y, s32 finish_x, s32 finish_y, map_c_ptr map, list_t_ptr exclude_list)
{
	u8 i, j;
	u8 path_step = 0;
	
	// lists
	bool used_nodes[LEVEL_WIDTH][LEVEL_HEIGHT];
	bool open_nodes[LEVEL_WIDTH][LEVEL_HEIGHT];
	node_t node_b[LEVEL_WIDTH][LEVEL_HEIGHT];
	u8 path_b[MOVE_MAX];
	
	// lowest on open list
	s32 current_lowest_f = MOVE_MAX * 100;
	s8 lowest_f_x = -1;
	s8 lowest_f_y = -1;
	
	// variables for the current node
	s32 current_x = start_x;
	s32 current_y = start_y;
	
	// clear our lists of used and open nodes
	for (i = 0; i < LEVEL_WIDTH; i++)
	{
		for (j = 0; j < LEVEL_HEIGHT; j++)
		{
			used_nodes[i][j] = false;
			open_nodes[i][j] = false;
		}
	}	
	
	// clear the final path list
	for (i = 0; i < MOVE_MAX; i++)
	{
		path_b[i] = 0;
	}   
   
	// make node hold it's location
	node_b[current_x][current_y].x = start_x;
	node_b[current_x][current_y].y = start_y;
	
	// give the first node it's values
	node_b[current_x][current_y].h_value = (abs(node_b[current_x][current_y].x - finish_x) + abs(node_b[current_x][current_y].y - finish_y));
	node_b[current_x][current_y].g_value = 0; //since it's parent node will be NULL as this is the start
	node_b[current_x][current_y].f_value = node_b[current_x][current_y].h_value + node_b[current_x][current_y].g_value;
	
	// parent node
	node_b[current_x][current_y].parent.x = start_x;
	node_b[current_x][current_y].parent.y = start_y;

	bool can_continue = false;
	u8 loop_checker = 0;
	
	// start the search
	while (1)
	{
		// check to see if we are finished
		if (current_x == finish_x && current_y == finish_y) break;
		
		// check to see it there are still open nodes to check
		can_continue = false;
		for (i = 0; i < LEVEL_WIDTH; i++)
		{
			for (j = 0; j < LEVEL_HEIGHT; j++)
			{
				if (open_nodes[i][j] == true)
				{
					can_continue = true;
					loop_checker = 0;
				}
			}
		}
		if (can_continue == false)
		{
			if (loop_checker == LOOP_CHECKS)
			{
				// return an error
				return PATH_BAD;
			}
		}

		
		// add this current one to the used nodes list, and remove it from the open nodes
		used_nodes[current_x][current_y] = true;
		open_nodes[current_x][current_y] = false;
		
		// look up
		if (map->wall_map[current_x][current_y - 1] != TILE_WALL // is not a wall
		&& current_y - 1 >= 0 // is in range of the grid 
		&& open_nodes[current_x][current_y - 1] == false // is not on the open list
		&& used_nodes[current_x][current_y - 1] == false // is yet to be used
		&& check_for_node(exclude_list, current_x, current_y - 1) == false) // is not on the exclude list
		{ 
			// start to give it it's values
			node_b[current_x][current_y - 1].x = current_x;
   			node_b[current_x][current_y - 1].y = current_y - 1;
   			
   			node_b[current_x][current_y - 1].h_value = (abs(node_b[current_x][current_y - 1].x - finish_x) + abs(node_b[current_x][current_y - 1].y - finish_y));
   			node_b[current_x][current_y - 1].g_value = 1 + node_b[current_x][current_y].g_value;
   			node_b[current_x][current_y - 1].f_value = node_b[current_x][current_y - 1].h_value + node_b[current_x][current_y - 1].g_value;
   			
   			node_b[current_x][current_y - 1].parent.x = current_x;
   			node_b[current_x][current_y - 1].parent.y = current_y;
   			
   			// add this node_b to the open list
   			open_nodes[current_x][current_y - 1] = true;
  		} // end if up 		
  		
  		// look down
		if (map->wall_map[current_x][current_y + 1] != TILE_WALL 
		&& current_y + 1 <= LEVEL_HEIGHT 
		&& open_nodes[current_x][current_y + 1] == false 
		&& used_nodes[current_x][current_y + 1] == false
		&& check_for_node(exclude_list, current_x, current_y + 1) == false)
		{
			// start to give it it's values
			node_b[current_x][current_y + 1].x = current_x;
			node_b[current_x][current_y + 1].y = current_y + 1;
   		
			node_b[current_x][current_y + 1].h_value = (abs(node_b[current_x][current_y + 1].x - finish_x) + abs(node_b[current_x][current_y + 1].y - finish_y));
			node_b[current_x][current_y + 1].g_value = 1 + node_b[current_x][current_y].g_value;
			node_b[current_x][current_y + 1].f_value = node_b[current_x][current_y + 1].h_value + node_b[current_x][current_y + 1].g_value;
   		
			node_b[current_x][current_y + 1].parent.x = current_x;
			node_b[current_x][current_y + 1].parent.y = current_y;
   		
			// add this node_b to the open list
			open_nodes[current_x][current_y + 1] = true;
  		} // end if down	
  		
  		// look left
		if (map->wall_map[current_x - 1][current_y] != TILE_WALL 
		&& current_x - 1 >= 0 
		&& open_nodes[current_x - 1][current_y] == false 
		&& used_nodes[current_x - 1][current_y] == false
		&& check_for_node(exclude_list, current_x - 1, current_y) == false)
		{
			// start to give it it's values
			node_b[current_x - 1][current_y].x = current_x - 1;
			node_b[current_x - 1][current_y].y = current_y;
   		
			node_b[current_x - 1][current_y].h_value = (abs(node_b[current_x - 1][current_y].x - finish_x) + abs(node_b[current_x - 1][current_y].y - finish_y));
			node_b[current_x - 1][current_y].g_value = 1 + node_b[current_x][current_y].g_value;
			node_b[current_x - 1][current_y].f_value = node_b[current_x - 1][current_y].h_value + node_b[current_x - 1][current_y].g_value;
   		
			node_b[current_x - 1][current_y].parent.x = current_x;
			node_b[current_x - 1][current_y].parent.y = current_y;
   		
			// add this node_b to the open list
			open_nodes[current_x - 1][current_y] = true;
  		} // end if left 		
  		
  		// look right
		if (map->wall_map[current_x + 1][current_y] != TILE_WALL 
		&& current_x + 1 <= LEVEL_WIDTH 
		&& open_nodes[current_x + 1][current_y] == false 
		&& used_nodes[current_x + 1][current_y] == false
		&& check_for_node(exclude_list, current_x + 1, current_y) == false)
		{
			// start to give it it's values
			node_b[current_x + 1][current_y].x = current_x + 1;
			node_b[current_x + 1][current_y].y = current_y;
			
			node_b[current_x + 1][current_y].h_value = (abs(node_b[current_x + 1][current_y].x - finish_x) + abs(node_b[current_x + 1][current_y].y - finish_y));
			node_b[current_x + 1][current_y].g_value = 1 + node_b[current_x][current_y].g_value;
			node_b[current_x + 1][current_y].f_value = node_b[current_x + 1][current_y].h_value + node_b[current_x + 1][current_y].g_value;
			
			node_b[current_x + 1][current_y].parent.x = current_x;
			node_b[current_x + 1][current_y].parent.y = current_y;
			
			// add this node_b to the open list
			open_nodes[current_x + 1][current_y] = true;
  		} // end if right
		
		// set lowest to max
  		current_lowest_f = MOVE_MAX * 10;
  		
  		// decide on the new current node
  		// search for the lowest
		for (i = 0; i < LEVEL_WIDTH; i++)
		{
			for (j = 0; j < LEVEL_HEIGHT; j++)
			{
				if (open_nodes[i][j] == true && used_nodes[i][j] == false)
				{
					if (node_b[i][j].f_value < current_lowest_f)
					{
						current_lowest_f = node_b[i][j].f_value;
						lowest_f_x = node_b[i][j].x;
						lowest_f_y = node_b[i][j].y;
					}   
				}   
			}
		}
 		current_x = lowest_f_x;
 		current_y = lowest_f_y;
	} // end while
	
 	while (1)
 	{
		if (node_b[current_x][current_y].parent.x == current_x && node_b[current_x][current_y].parent.y == (current_y - 1)) path_b[path_step] = UP_B;
		else if (node_b[current_x][current_y].parent.x == current_x && node_b[current_x][current_y].parent.y == (current_y + 1)) path_b[path_step] = DOWN_B;
		else if (node_b[current_x][current_y].parent.x == (current_x - 1) && node_b[current_x][current_y].parent.y == current_y) path_b[path_step] = LEFT_B;
		else if (node_b[current_x][current_y].parent.x == (current_x + 1) && node_b[current_x][current_y].parent.y == current_y) path_b[path_step] = RIGHT_B;
		else path_b[path_step] = 0;
		path_step++;
 	   
		// check to see if we are finished
		if (current_x == start_x && current_y == start_y) break;
		
		if (path_b[path_step-1] == UP_B) current_y--;
		if (path_b[path_step-1] == DOWN_B) current_y++;
		if (path_b[path_step-1] == LEFT_B) current_x--;
		if (path_b[path_step-1] == RIGHT_B) current_x++;
	} // end while  
	
	// swap directions to make same as unit and grid
	for (i = 0; i < MOVE_MAX; i++)
	{
		if (path_b[i] == UP_B) path_b[i] = RIGHT_B;
		else if (path_b[i] == DOWN_B) path_b[i] = LEFT_B;
		else if (path_b[i] == LEFT_B) path_b[i] = DOWN_B;
		else if (path_b[i] == RIGHT_B) path_b[i] = UP_B;
	}
	
	for (i = 0; i < MOVE_MAX; i++) final_path->path[i] = path_b[i];
	
	return PATH_GOOD;
}   



//==================================================================================================================================================================

path_holder_t find_path_malloc(s32 start_x, s32 start_y, s32 finish_x, s32 finish_y, map_c_ptr map, list_t_ptr exclude_list)
{
	u8 i, j;
	u8 path_step = 0;
	
	// lists
	
	list_t_ptr used_list = new list_t;
	list_t_ptr open_list = new list_t;


	bool used_nodes[LEVEL_WIDTH][LEVEL_HEIGHT];
	bool open_nodes[LEVEL_WIDTH][LEVEL_HEIGHT];
	node_t node_b[LEVEL_WIDTH][LEVEL_HEIGHT];
	u8 path_b[MOVE_MAX];
	
	// lowest on open list
	s32 current_lowest_f = MOVE_MAX * 100;
	s8 lowest_f_x = -1;
	s8 lowest_f_y = -1;
	
	// variables for the current node
	s32 current_x = start_x;
	s32 current_y = start_y;
	
	// clear our lists of used and open nodes
	for (i = 0; i < LEVEL_WIDTH; i++)
	{
		for (j = 0; j < LEVEL_HEIGHT; j++)
		{
			used_nodes[i][j] = false;
			open_nodes[i][j] = false;
		}
	}	
	
	// clear the final path list
	for (i = 0; i < MOVE_MAX; i++)
	{
		path_b[i] = 0;
	}   
   
	// make node hold it's location
	node_b[current_x][current_y].x = start_x;
	node_b[current_x][current_y].y = start_y;
	
	// give the first node it's values
	node_b[current_x][current_y].h_value = (abs(node_b[current_x][current_y].x - finish_x) + abs(node_b[current_x][current_y].y - finish_y));
	node_b[current_x][current_y].g_value = 0; //since it's parent node will be NULL as this is the start
	node_b[current_x][current_y].f_value = node_b[current_x][current_y].h_value + node_b[current_x][current_y].g_value;
	
	// parent node
	node_b[current_x][current_y].parent.x = start_x;
	node_b[current_x][current_y].parent.y = start_y;
	
	// start the search
	while (1)
	{
		// check to see if we are finished
		if (current_x == finish_x && current_y == finish_y) break;
		
// ----- To do: check to see it there are still open nodes to check
      
		// add this current one to the used nodes list, and remove it from the open nodes
		used_nodes[current_x][current_y] = true;
		open_nodes[current_x][current_y] = false;
      
		// look up
		if (map->wall_map[current_x][current_y - 1] != TILE_WALL // is not a wall
		&& current_y - 1 >= 0 // is in range of the grid 
		&& open_nodes[current_x][current_y - 1] == false // is not on the open list
		&& used_nodes[current_x][current_y - 1] == false // is yet to be used
		&& check_for_node(exclude_list, current_x, current_y - 1) == false) // is not on the exclude list
		{ 
			// start to give it it's values
			node_b[current_x][current_y - 1].x = current_x;
   			node_b[current_x][current_y - 1].y = current_y - 1;
   			
   			node_b[current_x][current_y - 1].h_value = (abs(node_b[current_x][current_y - 1].x - finish_x) + abs(node_b[current_x][current_y - 1].y - finish_y));
   			node_b[current_x][current_y - 1].g_value = 1 + node_b[current_x][current_y].g_value;
   			node_b[current_x][current_y - 1].f_value = node_b[current_x][current_y - 1].h_value + node_b[current_x][current_y - 1].g_value;
   			
   			node_b[current_x][current_y - 1].parent.x = current_x;
   			node_b[current_x][current_y - 1].parent.y = current_y;
   			
   			// add this node_b to the open list
   			open_nodes[current_x][current_y - 1] = true;
  		} // end if up 		
  		
  		// look down
		if (map->wall_map[current_x][current_y + 1] != TILE_WALL 
		&& current_y + 1 <= LEVEL_HEIGHT 
		&& open_nodes[current_x][current_y + 1] == false 
		&& used_nodes[current_x][current_y + 1] == false
		&& check_for_node(exclude_list, current_x, current_y + 1) == false)
		{
			// start to give it it's values
			node_b[current_x][current_y + 1].x = current_x;
			node_b[current_x][current_y + 1].y = current_y + 1;
   		
			node_b[current_x][current_y + 1].h_value = (abs(node_b[current_x][current_y + 1].x - finish_x) + abs(node_b[current_x][current_y + 1].y - finish_y));
			node_b[current_x][current_y + 1].g_value = 1 + node_b[current_x][current_y].g_value;
			node_b[current_x][current_y + 1].f_value = node_b[current_x][current_y + 1].h_value + node_b[current_x][current_y + 1].g_value;
   		
			node_b[current_x][current_y + 1].parent.x = current_x;
			node_b[current_x][current_y + 1].parent.y = current_y;
   		
			// add this node_b to the open list
			open_nodes[current_x][current_y + 1] = true;
  		} // end if down	
  		
  		// look left
		if (map->wall_map[current_x - 1][current_y] != TILE_WALL 
		&& current_x - 1 >= 0 
		&& open_nodes[current_x - 1][current_y] == false 
		&& used_nodes[current_x - 1][current_y] == false
		&& check_for_node(exclude_list, current_x - 1, current_y) == false)
		{
			// start to give it it's values
			node_b[current_x - 1][current_y].x = current_x - 1;
			node_b[current_x - 1][current_y].y = current_y;
   		
			node_b[current_x - 1][current_y].h_value = (abs(node_b[current_x - 1][current_y].x - finish_x) + abs(node_b[current_x - 1][current_y].y - finish_y));
			node_b[current_x - 1][current_y].g_value = 1 + node_b[current_x][current_y].g_value;
			node_b[current_x - 1][current_y].f_value = node_b[current_x - 1][current_y].h_value + node_b[current_x - 1][current_y].g_value;
   		
			node_b[current_x - 1][current_y].parent.x = current_x;
			node_b[current_x - 1][current_y].parent.y = current_y;
   		
			// add this node_b to the open list
			open_nodes[current_x - 1][current_y] = true;
  		} // end if left 		
  		
  		// look right
		if (map->wall_map[current_x + 1][current_y] != TILE_WALL 
		&& current_x + 1 <= LEVEL_WIDTH 
		&& open_nodes[current_x + 1][current_y] == false 
		&& used_nodes[current_x + 1][current_y] == false
		&& check_for_node(exclude_list, current_x + 1, current_y) == false)
		{
			// start to give it it's values
			node_b[current_x + 1][current_y].x = current_x + 1;
			node_b[current_x + 1][current_y].y = current_y;
			
			node_b[current_x + 1][current_y].h_value = (abs(node_b[current_x + 1][current_y].x - finish_x) + abs(node_b[current_x + 1][current_y].y - finish_y));
			node_b[current_x + 1][current_y].g_value = 1 + node_b[current_x][current_y].g_value;
			node_b[current_x + 1][current_y].f_value = node_b[current_x + 1][current_y].h_value + node_b[current_x + 1][current_y].g_value;
			
			node_b[current_x + 1][current_y].parent.x = current_x;
			node_b[current_x + 1][current_y].parent.y = current_y;
			
			// add this node_b to the open list
			open_nodes[current_x + 1][current_y] = true;
  		} // end if right
		
		// set lowest to max
  		current_lowest_f = MOVE_MAX * 10;
  		
  		// decide on the new current node
  		// search for the lowest
		for (i = 0; i < LEVEL_WIDTH; i++)
		{
			for (j = 0; j < LEVEL_HEIGHT; j++)
			{
				if (open_nodes[i][j] == true && used_nodes[i][j] == false)
				{
					if (node_b[i][j].f_value < current_lowest_f)
					{
						current_lowest_f = node_b[i][j].f_value;
						lowest_f_x = node_b[i][j].x;
						lowest_f_y = node_b[i][j].y;
					}   
				}   
			}
		}
 		current_x = lowest_f_x;
 		current_y = lowest_f_y;
	} // end while
	
 	while (1)
 	{
		if (node_b[current_x][current_y].parent.x == current_x && node_b[current_x][current_y].parent.y == (current_y - 1)) path_b[path_step] = UP_B;
		else if (node_b[current_x][current_y].parent.x == current_x && node_b[current_x][current_y].parent.y == (current_y + 1)) path_b[path_step] = DOWN_B;
		else if (node_b[current_x][current_y].parent.x == (current_x - 1) && node_b[current_x][current_y].parent.y == current_y) path_b[path_step] = LEFT_B;
		else if (node_b[current_x][current_y].parent.x == (current_x + 1) && node_b[current_x][current_y].parent.y == current_y) path_b[path_step] = RIGHT_B;
		else path_b[path_step] = 0;
		path_step++;
 	   
		// check to see if we are finished
		if (current_x == start_x && current_y == start_y) break;
		
		if (path_b[path_step-1] == UP_B) current_y--;
		if (path_b[path_step-1] == DOWN_B) current_y++;
		if (path_b[path_step-1] == LEFT_B) current_x--;
		if (path_b[path_step-1] == RIGHT_B) current_x++;
	} // end while  
	
	// swap directions to make same as unit and grid
	for (i = 0; i < MOVE_MAX; i++)
	{
		if (path_b[i] == UP_B) path_b[i] = RIGHT_B;
		else if (path_b[i] == DOWN_B) path_b[i] = LEFT_B;
		else if (path_b[i] == LEFT_B) path_b[i] = DOWN_B;
		else if (path_b[i] == RIGHT_B) path_b[i] = UP_B;
	}
	
	/*
	//print the path
	for (i=0;i<MOVEMAX;i++)
	{
	   	if (path_b[i] == UP_B) iprintf("\x1b[%d;0Hup    ",i);
 		else if (path_b[i] == DOWN_B) iprintf("\x1b[%d;0Hdown  ",i);
 		else if (path_b[i] == LEFT_B) iprintf("\x1b[%d;0Hleft  ",i);
 		else if (path_b[i] == RIGHT_B) iprintf("\x1b[%d;0Hright ",i);
 		else i++;
	}
	*/
	
	path_holder_t finished_path;
	for (i = 0; i < MOVE_MAX; i++) finished_path.path[i] = path_b[i];
	
	return finished_path;
}   

// end of file

