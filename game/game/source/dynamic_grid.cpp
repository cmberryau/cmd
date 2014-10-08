/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: dynamic_grid.cpp
 * Date: 1st of July, 2010.
 * Author(s): Patrick Randell
 * Description: see header file.
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

// header
#include "dynamic_grid.h"

// functions
dynamic_node_c::dynamic_node_c()
{
	// null links of surrounding nodes
    this->up = null;
	this->down = null;
	this->left = null;
	this->right = null;
    
    location.x = -1;
    location.y = -1;
}

dynamic_node_c::~dynamic_node_c()
{
	// null links of surrounding nodes to this node
	if (this->up != null)
		this->up->down = null;
	if (this->down != null)
		this->down->up = null;
	if (this->left != null)
		this->left->right = null;
	if (this->right != null)
		this->right->left = null;
	
	// null local links just to make sure
	this->up = null;
	this->down = null;
	this->left = null;
	this->right = null;
}

void dynamic_node_c::set_location(int x, int y)
{
    location.x = x;
    location.y = y;
}

dynamic_node_c_ptr dynamic_node_c::get_direction(direction_e direction)
{
    if (direction == UP)
        return up;
    if (direction == DOWN)
        return down;
    if (direction == LEFT)
        return left;
    if (direction == RIGHT)
        return right;
        
    return null;
} 

//========================================================

dynamic_node_container_c::dynamic_node_container_c(int x, int y)
{
    node = null;
    
    location.x = x;
    location.y = y;
    up = null;
    down = null;
    left = null;
    right = null;
}

dynamic_node_container_c::~dynamic_node_container_c()
{
    // null links of surrounding nodes to this node
	if (this->up != null)
		this->up->down = null;
	if (this->down != null)
		this->down->up = null;
	if (this->left != null)
		this->left->right = null;
	if (this->right != null)
		this->right->left = null;
	
	// null local links just to make sure
	this->up = null;
	this->down = null;
	this->left = null;
	this->right = null;
    
    if (node != null)
        delete node;
}
 
void dynamic_node_container_c::set_direction(direction_e direction, dynamic_node_container_c* new_node)
{
    if (direction == UP)
        up = new_node;
    if (direction == DOWN)
        down = new_node;
    if (direction == LEFT)
        left = new_node;
    if (direction == RIGHT)
        right = new_node;
}

dynamic_node_container_c_ptr dynamic_node_container_c::get_direction(direction_e direction)
{
    if (direction == UP)
        return up;
    if (direction == DOWN)
        return down;
    if (direction == LEFT)
        return left;
    if (direction == RIGHT)
        return right;
        
    return null;
}   

dynamic_node_c_ptr dynamic_node_container_c::get_node()
{
    return node;
}

void dynamic_node_container_c::set_node(dynamic_node_c_ptr new_node)
{
    node = new_node;
}

//=======================================================

dynamic_grid_c::dynamic_grid_c(int x, int y)
{
    int i, j;
    dynamic_node_container_c_ptr x_track_node, y_track_node, new_node, current_node, next_row;
    bool first_node;

	x_track_node = null;
    
    max.x = x; 
    max.y = y;
    first_node = true;
    
    // creating containers 
    for (i = 0; i < max.x; i++)
    {
        // see if we have to make the zero-zero
        if (first_node == true)
        {
            x_track_node = new dynamic_node_container_c(i, 0);
            zero_zero = x_track_node; 
            first_node = false;
        }
        
        // set the start of the upwards expansion
        y_track_node = x_track_node;
        
        // expand upwards
        for (j = 1; j < max.y; j++)
        {
            new_node = new dynamic_node_container_c(i, j);
            
            y_track_node->set_direction(UP, new_node);
            new_node->set_direction(DOWN, y_track_node);
            y_track_node = y_track_node->get_direction(UP);
        }
        
        // make a new node to the right of the bottom x node
        if (i + 1 < max.x)
        {
            new_node = new dynamic_node_container_c(i + 1, 0);
            
            x_track_node->set_direction(RIGHT, new_node);
            new_node->set_direction(LEFT, x_track_node);
            x_track_node = x_track_node->get_direction(RIGHT);
        }
    }
    
    // now all nodes are made, finish off all links
    current_node = zero_zero;
    bool on_edge = true;
    
    for (i = 0; i < max.x; i++)
    {
        on_edge = true;
        next_row = current_node->get_direction(RIGHT);
        
        if (next_row != null)
        {
            on_edge = false;
        }
        
        // move up
        if (on_edge == false)
        {
            current_node = current_node->get_direction(UP);
            next_row = next_row->get_direction(UP);
        }
        else
        {
            current_node = current_node->get_direction(UP);
            // and the next row is null, so don't access it
        }
        
        for (j = 1; j < max.y; j++)
        {
            if (on_edge == false)
            {
                // set left and right
                current_node->set_direction(RIGHT, next_row);
                next_row->set_direction(LEFT, current_node);
                
                // move up
                current_node = current_node->get_direction(UP);
                next_row = next_row->get_direction(UP);
            }
            else
            {
                // set right
                current_node->set_direction(RIGHT, next_row);
                
                // move up
                current_node = current_node->get_direction(UP);
            }
        }
        
        // move right
        current_node = current_node->get_direction(RIGHT);
        next_row = next_row->get_direction(RIGHT);
    }
}

dynamic_grid_c::~dynamic_grid_c()
{
    // delete all the nodes
    
    
}

void dynamic_grid_c::reset_grid_nodes()
{
    // delete all nodes from containers
}

dynamic_node_c_ptr dynamic_grid_c::get_node(int x, int y)
{
    int x_finder, y_finder;
    dynamic_node_container_c_ptr current_node;
    
    x_finder = 0;
    y_finder = 0;
    current_node = zero_zero;
    
    if (x >= max.x || y >= max.y)
    {
        return null;
    }
    
    while (x_finder != x)
    {
        current_node = current_node->get_direction(RIGHT);
        x_finder++;
    }
    
    while (y_finder != y)
    {
        current_node = current_node->get_direction(UP);
        y_finder++;
    }
    
    return current_node->get_node();
}

dynamic_node_container_c_ptr dynamic_grid_c::get_node_container(int x, int y)
{
    int x_finder, y_finder;
    dynamic_node_container_c_ptr current_node;
    
    x_finder = 0;
    y_finder = 0;
    current_node = zero_zero;
    
    if (x >= max.x || y >= max.y)
    {
        return null;
    }
    
    while (x_finder != x)
    {
        current_node = current_node->get_direction(RIGHT);
        x_finder++;
    }
    
    while (y_finder != y)
    {
        current_node = current_node->get_direction(UP);
        y_finder++;
    }
    
    return current_node;
}

void dynamic_grid_c::set_node(int x, int y, dynamic_node_c_ptr new_node)
{
    dynamic_node_container_c_ptr target_node;
    
    target_node = get_node_container(x, y);
    new_node->set_location(x, y);
    target_node->set_node(new_node);
}

// end of file
