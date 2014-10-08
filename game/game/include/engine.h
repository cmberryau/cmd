/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: engine.h
 * Date: 8th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry
 * Description: engine class. this will prob be replaced with the game->team->unit structure.
 * should have an init, darw_start, draw_end, idle/input, print_debug.
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef ENGINE_H
#define ENGINE_H

// libraries
#include <nds.h>
#include <assert.h>
#include <stdio.h>

// files
#include "types.h"

#include "event.h"
#include "timer.h"

// UI
#include "ui.h"

// 3D
#include "meshtable.h"

#define SCROLL_COEFF 0.03
#define KEY_SCROLL_SPEED 0.1

/**
 * Engine class;
 * - Manages cameras
 * - Manages sprite table
 * - Manages mesh table
 * - Manages drawing order
 */
class engine_c{
	private:
		camera_t bottom_cam;				// Cameras
		meshtable_c * meshtable;			// Mesh table
		ui_c * ui;							// UI object

		void hide_menu_sprites();			// Hide the menu sprites
		void show_menu_sprites();			// Show the menu sprites

		void hide_game_sprites();			// Hide the game sprites
		void show_game_sprites();			// Show the game sprites

		void hide_all_sprites();			// Hide all sprites
		void show_all_sprites();			// Show all sprites

		void hide_menu_bgs();				// Hide menu bgs
		void show_menu_bgs();				// Show meny bgs

		void hide_game_bgs();				// Hide game bgs
		void show_game_bgs();				// show game bgs

	public:
		timer_c timer;						// Timer for the engine
		bool camera_mode;					// Camera mode

		int init();							// Inits the engine and default properties

		meshtable_c * get_meshtable();		// Return the meshtable
		camera_t get_camera();				// Get the camera object

		void input(event_c_ptr event);		// Parses input

		void start_draw();					// Start drawing
		void stop_draw();					// Finishes the drawing for the last screen

		void hide_menu_2D_objects();		// Hide the menu 2D objects
		void show_menu_2D_objects();		// Show the menu 2D objects

		void hide_menu_3D_objects();		// Hide the menu 3D objects
		void show_menu_3D_objects();		// Show the menu 3D objects

		void hide_game_2D_objects();		// Hide the game 2D objects
		void show_game_2D_objects();		// Show the game 2D objects

		void hide_game_3D_objects();		// Hide the game 3D objects
		void show_game_3D_objects();		// Show the game 3D objects

		void show3dbackgrounds();			// Displays the 3D backgrounds

		void print_debug_info();			// Debugging function

		void set_camera(bool screen, camera_t_ptr new_cam);		// Uses the given camera to set new values for the given screen
};

// pointer
typedef engine_c * engine_c_ptr;

#endif

// end of file

