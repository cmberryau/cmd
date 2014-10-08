/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: event.h
 * Date: 8th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry
 * Description: event class, checks input and saves what buttons are being pressed so that other 
 * functions can look at the same event.
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef EVENT_H
#define EVENT_H

// files
#include <nds.h>
#include "types.h"

// data types
// button set
typedef struct
{
	int new_press, release, held;
} buttons_t;

// pointer
typedef buttons_t * buttons_t_ptr;

// touch screen
typedef struct
{
	vector_2di_t current, drag_start, drag_end;
} touch_t;

// pointer
typedef touch_t * touch_t_ptr;

// event class
class event_c 
{
private:
	// buttons
	// holds values
	buttons_t buttons;
	
	// touch screen
	// used to check
	touchPosition touch_x_y; 
	// holds current, new press, and release
	touch_t touch; 

public:
	void all_default();
	void update();
	
	buttons_t get_buttons();
	touch_t get_touch();
	
	void print_debug();
};

// pointer
typedef event_c * event_c_ptr;

#endif

// end of file
