/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: dynamic_grid.h
 * Date: 1st of July, 2010.
 * Author(s): Patrick Randell
 * Discription: a dynamic grid system used for searches.
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef DYNAMIC_GRID_H
#define DYNAMIC_GRID_H

// files
#include <nds.h>
#include <types.h>

// types
enum direction_e
{
    UP, DOWN, LEFT, RIGHT
};

// classes

class dynamic_node_c
{
private:
	vector_2di_t location;
	dynamic_node_c* up;
	dynamic_node_c* down;
	dynamic_node_c* left;
	dynamic_node_c* right;


public: 
	dynamic_node_c();
	~dynamic_node_c();
    
    void set_location(int x, int y);
	dynamic_node_c* get_direction(direction_e direction);
};
typedef dynamic_node_c* dynamic_node_c_ptr;

class dynamic_node_container_c
{
private:
    dynamic_node_c_ptr node;
    vector_2di_t location;
	dynamic_node_container_c* up;
	dynamic_node_container_c* down;
	dynamic_node_container_c* left;
	dynamic_node_container_c* right;
    
public:
    dynamic_node_container_c(int x, int y);
	~dynamic_node_container_c();
    
    void set_direction(direction_e direction, dynamic_node_container_c* new_node);
    dynamic_node_container_c* get_direction(direction_e direction);
    dynamic_node_c_ptr get_node();
    void set_node(dynamic_node_c_ptr new_node);
};
typedef dynamic_node_container_c* dynamic_node_container_c_ptr;

class dynamic_grid_c
{
private:
	vector_2di_t max;
	dynamic_node_container_c_ptr zero_zero;
    bool containers_made;
    
public:
	dynamic_grid_c(int x, int y);
	~dynamic_grid_c();

    void reset_grid_nodes();
    dynamic_node_c_ptr get_node(int x, int y);
    dynamic_node_container_c_ptr get_node_container(int x, int y);
    void set_node(int x, int y, dynamic_node_c_ptr new_node);
};
typedef dynamic_grid_c* dynamic_grid_c_ptr;

#endif

// end of file

