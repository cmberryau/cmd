/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: event.cpp
 * Date: 8th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry
 * Description: event class, see header.
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

// header
#include "event.h"
#include <stdio.h>

void event_c::all_default()
{
	buttons.new_press = 0;
	buttons.release = 0;
	buttons.held = 0;
	
	touch.current.x = 0;
	touch.current.y = 0;
	touch.drag_start.x = 0;
	touch.drag_start.y = 0;
	touch.drag_end.x = 0;
	touch.drag_end.y = 0;
}

void event_c::update()
{
	// buttons
	scanKeys();
	
	buttons.new_press = keysDown();
	buttons.release = keysUp();
	buttons.held = keysHeld();
	
	// touch screen
	touchPosition touch_x_y; // used to check
	
	// Read the position
	touchRead( &touch_x_y );

	// NOTE:If the touch screen is at ( 0,0 ) then it is considered to be not-active
	/* New press on the touchpad */
	if( buttons.new_press & KEY_TOUCH ){
		touch.current.x = touch_x_y.px;
		touch.current.y = touch_x_y.py;
		
		touch.drag_start.x = touch_x_y.px;
		touch.drag_start.y = touch_x_y.py;
	}
	/* Continuing to hold on the touchpad */
	if( buttons.held & KEY_TOUCH ){
		touch.current.x = touch_x_y.px;
		touch.current.y = touch_x_y.py;
	}
	/* Release the stylus from the touchpad */
	if( buttons.release & KEY_TOUCH ){
		touch.drag_end.x = touch.current.x;
		touch.drag_end.y = touch.current.y;
		
		touch.current.x = 0;
		touch.current.y = 0; 
	}
}

buttons_t event_c::get_buttons()
{
	return buttons;
}

touch_t event_c::get_touch()
{
	return touch;
}

void event_c::print_debug()
{
	// button order a,b,select,start,right,left,up,down,r,l,x,y
	iprintf("\x1b[4;0HEvent Debug\nA     : %4d %4d %4d  \nB     : %4d %4d %4d  \nSELECT: %4d %4d %4d  \nSTART : %4d %4d %4d  \nRIGHT : %4d %4d %4d  \nLEFT  : %4d %4d %4d  \nUP    : %4d %4d %4d  \nDOWN  : %4d %4d %4d  \nR     : %4d %4d %4d  \nL     : %4d %4d %4d  \nX     : %4d %4d %4d  \nY     : %4d %4d %4d  \n",
	(buttons.new_press & KEY_A), (buttons.held & KEY_A), (buttons.release & KEY_A),
	(buttons.new_press & KEY_B), (buttons.held & KEY_B), (buttons.release & KEY_B),
	(buttons.new_press & KEY_SELECT), (buttons.held & KEY_SELECT), (buttons.release & KEY_SELECT),
	(buttons.new_press & KEY_START), (buttons.held & KEY_START), (buttons.release & KEY_START),
	(buttons.new_press & KEY_RIGHT), (buttons.held & KEY_RIGHT), (buttons.release & KEY_RIGHT),
	(buttons.new_press & KEY_LEFT), (buttons.held & KEY_LEFT), (buttons.release & KEY_LEFT),
	(buttons.new_press & KEY_UP), (buttons.held & KEY_UP), (buttons.release & KEY_UP),
	(buttons.new_press & KEY_DOWN), (buttons.held & KEY_DOWN), (buttons.release & KEY_DOWN),
	(buttons.new_press & KEY_R), (buttons.held & KEY_R), (buttons.release & KEY_R),
	(buttons.new_press & KEY_L), (buttons.held & KEY_L), (buttons.release & KEY_L),
	(buttons.new_press & KEY_X), (buttons.held & KEY_X), (buttons.release & KEY_X),
	(buttons.new_press & KEY_Y), (buttons.held & KEY_Y), (buttons.release & KEY_Y)
	);

	iprintf("\x1b[17;0HTouch Screen\nCurrent    : %4d %4d \nDrag Start : %4d %4d \nDrag End   : %4d %4d \n",
	touch.current.x, touch.current.y, touch.drag_start.x,
	touch.drag_start.y, touch.drag_end.x, touch.drag_end.y);
}

// end of file 
