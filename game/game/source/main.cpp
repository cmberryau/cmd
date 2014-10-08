/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: main.cpp
 * Date: 8th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry.
 * Description: entry point of the application
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#define _DEBUG

// main

#include <nds.h>
#include <stdio.h>

// files
#include "engine.h"
#include "timer.h"
#include "event.h"
#include "map.h"
#include "game.h"
#include "intro.h"
#include "d_pad_cursor.h"
#include "soundtable.h"
#include "test_map.h"

engine_c engine;

int main() {

	s8 stat;
	stat = engine.init();

	if( stat != SUCCESS ){
		//Engine failed to init
		return FAILURE;
	}

	// event class testing
	event_c_ptr event = new event_c;
	event->all_default();
	buttons_t buttons;
	
	// map class testing
	map_c_ptr map = new map_c();
	map->define_size(MAP_X_Y_MAX - 1, MAP_X_Y_MAX - 1);
	map->set_draw_map(map_16x16_01);
	map->set_wall_map(map_16x16_01);
	
	// timer class testing
	timer_c timer;
	timer.init();
	time_t unix_ticks = time(NULL);
	timer.start(unix_ticks);
	
	// game class testing
	game_c_ptr game = new game_c;
	game->init();
	game->set_map(map);

	game->add_team_array(); // team 0
	game->get_team(0)->get_base()->init(10,8,map,0);
	game->add_team_array(); // team 1

	game->make_unit((u8)0, (u16)5, (u16)5, (u8)HEAVY);
	game->make_unit((u8)0, (u16)6, (u16)3, (u8)HEAVY);
	game->make_unit((u8)0, (u16)6, (u16)1, (u8)HEAVY);

	game->get_team((u8)0)->delete_unit(0);
	
	game->make_unit((u8)0, (u16)2, (u16)2, (u8)GATHERER);
	game->make_unit((u8)0, (u16)2, (u16)3, (u8)GATHERER);
	//game->make_unit((u8)0, (u16)2, (u16)4, (u8)GATHERER);
	//game->make_unit((u8)0, (u16)6, (u16)4, (u8)GATHERER);
	
	// this unit should not be slected, since it is on another team
	//game->make_unit((u8)1, (u16)6, (u16)6, (u8)DEMO);
	
	// these units should not display
	// PAT NTS - these units are still updating to the unit map
	//game->make_unit((u8)2, (u16)3, (u16)0, (u8)GATHERER);
	//game->make_unit((u8)3, (u16)3, (u16)1, (u8)DEMO);
	
	
	// d-pad cursor
	d_pad_cursor_ptr cursor = new d_pad_cursor_c;
	cursor->init(5, 6, map);

	//engine.initBackgrounds();
	//engine.displayTestBG();

	// set camera for gameplay mode.
	camera_t_ptr new_cam = new camera_t;
	new_cam->x = floattof32( 0.0 );
	new_cam->y = floattof32( -2.0 );
	//new_cam->y = floattof32( 0.0 );
	new_cam->z = floattof32( -30.0 );
	new_cam->rotation.x = -6371;
	//new_cam->rotation.x = 0;
	new_cam->rotation.y = 0;
	new_cam->rotation.z = 0;
	engine.set_camera( BOTTOM, new_cam ); // <-- comment out this line to return to default cam
	delete new_cam;
	
	//consoleDemoInit(); // <-- comment out this line to return top screen graphics

	engine.get_meshtable()->get_background_mesh_00()->set_alpha( 7 );
	engine.get_meshtable()->get_background_mesh_00()->rel_translatei32( inttof32( 0 ), inttof32( 1 ), inttof32( -20 ) ); 

	engine.get_meshtable()->get_background_mesh_01()->set_alpha( 3 );
	engine.get_meshtable()->get_background_mesh_01()->rel_translatei32( inttof32( 0 ), inttof32( 1 ), inttof32( -19 ) ); 

	bool menu = false;

	while (1)
	{
		// update input
		event->update();
		buttons = event->get_buttons();

		if( menu ){
			// Hide all sprites
			
			// Show the sprites for the menu mode

		}else{
			// Hide all sprites
			
			// Show the sprites for the game mode

			if( engine.camera_mode == true ){
				engine.input( event );
				engine.hide_game_2D_objects();
				engine.show_menu_2D_objects();
			}else{
				cursor->update_input( event, game );
				engine.hide_menu_2D_objects();
				engine.show_game_2D_objects();
			}
			// mode change 
			if ( buttons.new_press & KEY_SELECT ){
				if ( engine.camera_mode == true ) engine.camera_mode = false;
				else engine.camera_mode = true;
			}

			if ( buttons.new_press & KEY_START ){
				
			}

			game->idle_all_units();

			engine.start_draw();
			
			engine.show3dbackgrounds();
			cursor->draw();
			map->draw_3d_map();
			game->draw_all_units();

			engine.stop_draw();				
		}
		
		//engine.print_debug_info();
		
		//iprintf("\x1b[0;0Hconsoletest\n");

		//cursor->debug_print(); // 4 to 13
		//map->debug_print_draw_map();// 15 - 23
		//map->debug_print_wall_map();
		
		// tick timer
		timer.tick();
	}
	return SUCCESS;
}

// end of file