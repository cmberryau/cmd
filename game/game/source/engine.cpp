/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: engine.cpp
 * Date: 8th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry
 * Description: engine class, see header.
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

// header file
#include "engine.h"

extern engine_c engine;

// functions
void incre_ms( void ){
	engine.timer.incre_ms();
}

/**
 * Inits the engine, setting defaults
 */
int engine_c::init(){
	irqSet( IRQ_TIMER0, incre_ms );				// Install the timer interrupt
	TIMER0_DATA = (vuint16)TIMER_FREQ( 1000 );	// Set the frequency of the interrupt
	TIMER0_CR = TIMER_ENABLE | TIMER_IRQ_REQ;	// Enable the timer
	irqEnable( IRQ_TIMER0 );
	irqEnable( IRQ_VBLANK );					// Enable the vblank interrupt
	
	timer.init();
	timer.start( 0 );

	videoSetMode( MODE_0_3D |
				  DISPLAY_BG2_ACTIVE |
				  DISPLAY_SPR_ACTIVE |
				  DISPLAY_SPR_1D );

	videoSetModeSub( MODE_5_2D |
		             DISPLAY_BG2_ACTIVE |
					 DISPLAY_SPR_ACTIVE |
					 DISPLAY_SPR_1D );
	
	glInit();	// init openGL

	vramSetBankA( VRAM_A_TEXTURE );			// Set VRAM bank A for texturing
	vramSetBankB( VRAM_B_TEXTURE );			// Set VRAM bank B for texturing
	vramSetBankC( VRAM_C_SUB_BG );			// Set VRAM bank A for sub BG
	vramSetBankD( VRAM_D_TEXTURE );			// Set VRAM bank D for texturing
	vramSetBankE( VRAM_E_MAIN_BG );			// Set VRAM bank E for main sprites
	//vramSetBankF( VRAM_F_TEX_PALETTE );	// Set VRAM bank F for main BG
	vramSetBankG( VRAM_G_MAIN_SPRITE );		// Set VRAM bank G for main BG
	//vramSetBankH( VRAM_H_SUB_BG );		// Set VRAM bank H for sub BG
	vramSetBankI( VRAM_I_SUB_SPRITE );		// Set VRAM bank I for sub sprites
	
	glViewport( 0, 0, 255, 191 );			// GL viewport
	glClearColor( 0, 0, 0, 31 );			// BG must be opaque for AA to work
	glClearDepth( GL_MAX_DEPTH );			// Set clear depth
	glClearPolyID( 63 );					// BG must have a unique polygon ID for AA to work

	// Enable texturing, blending and antialiasing
	glEnable( GL_TEXTURE_2D | GL_BLEND | GL_ANTIALIAS );

	// Polygon format set, will be replaced and called inside mesh
	glPolyFmt( POLY_ID( 1 ) | POLY_ALPHA( 31 ) | POLY_CULL_NONE );

	// Bottom camera initial settings
	bottom_cam.x = 0;
	bottom_cam.y = 0;
	bottom_cam.z = -60;
	bottom_cam.rotation.x = 0;
	bottom_cam.rotation.y = 0;
	bottom_cam.rotation.z = 0;

	camera_mode = false; // Default camera mode

	ui = new ui_c();
	meshtable = new meshtable_c();

	return SUCCESS;
}

/**
 * Returns the meshtable
 */
meshtable_c * engine_c::get_meshtable(){
	return meshtable;
}

/**
 * Start drawing
 */
void engine_c::start_draw(){
	//glEnable( GL_TEXTURE_2D | GL_BLEND | GL_ANTIALIAS );
	glColor3b( 255,255,255 );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	gluPerspective( 10, 256.0 / 192.0, 0.1, 100 );

	lcdMainOnBottom();

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	/* f32 translation */
	glTranslate3f32( bottom_cam.x, bottom_cam.y, bottom_cam.z );
	
	/* Integer rotation */
	glRotateXi( bottom_cam.rotation.x );
	glRotateYi( bottom_cam.rotation.y );
	glRotateZi( bottom_cam.rotation.z );
}

/**
 * Stop the drawing of the scene
 */
void engine_c::stop_draw(){
	// Flush out the buffer
	glFlush(0);
	// Wait for vblank
	swiWaitForVBlank();
	// Reset ms timer
	//timer.reset_ms();
}

/**
 * Returns the camera object
 */
camera_t engine_c::get_camera(){
	return bottom_cam;
}

/**
 * Processes input
 */
void engine_c::input( event_c_ptr event ){
	buttons_t buttons;
	touch_t touch_screen;
	
	buttons = event->get_buttons();
	touch_screen = event->get_touch();
	
	/* Save some cpu time by computing these only once */
	static const int32 key_scroll = floattof32( KEY_SCROLL_SPEED );
	static const int32 pad_scroll = floattof32( SCROLL_COEFF );

	/* If the scene is current in camera mode */
	if( camera_mode == true ){
		/* Button scene movement */
		if( buttons.new_press & KEY_LEFT ){
			bottom_cam.x += key_scroll;
		}else if( buttons.held & KEY_LEFT ){
			bottom_cam.x += key_scroll;
		}

		if( buttons.new_press & KEY_RIGHT ){
			bottom_cam.x -= key_scroll;
		}else if( buttons.held & KEY_RIGHT ){
			bottom_cam.x -= key_scroll;
		}

		if( buttons.new_press & KEY_UP ){
			bottom_cam.y -= key_scroll;

		}else if( buttons.held & KEY_UP ){
			bottom_cam.y -= key_scroll;
		}

		if( buttons.new_press & KEY_DOWN ){
			bottom_cam.y += key_scroll;
		}else if( buttons.held & KEY_DOWN ){
			bottom_cam.y += key_scroll;
		}

		/* Translate the camera's x and y based on the drag value */
		static int lastx=0, lasty=0;
		int diffx=0, diffy=0;

		/* Player presses the touchpad */
		if( buttons.new_press & KEY_TOUCH ){
			lastx = touch_screen.current.x;
			lasty = touch_screen.current.y;
		}
		/* Continuing to hold on the touchpad */
		if( buttons.held & KEY_TOUCH ){
			/* Determine the difference */
			diffx = touch_screen.current.x - lastx;
			diffy = touch_screen.current.y - lasty;

			/* Calculate the movement factor */
			bottom_cam.x += ( pad_scroll * diffx );
			bottom_cam.y -= ( pad_scroll * diffy );

			/* Set the last dragged values */
			lastx = touch_screen.current.x;
			lasty = touch_screen.current.y;
		}
		/* Player releases the touchpad */
		if( buttons.release & KEY_TOUCH ){
			/* Nothing to happen on release yet */
		}
	}else{ // If the scene is in game mode
		if( buttons.new_press & KEY_UP ){
			ui->get_spritetable()->set_res_field( 1234 );
		}
	}
}

/**
 * Displays the 3D backgrounds
 */
void engine_c::show3dbackgrounds(){
	/* Hack implementation of backgrounds for the presentation */
	static bool snd = true;
	if( snd ){
		engine.get_meshtable()->get_background_mesh_00()->single_step_v();
		snd = false;
	}else{
		snd = true;
	}
	engine.get_meshtable()->get_background_mesh_01()->single_step_v();

	engine.get_meshtable()->get_background_mesh_00()->draw();
	engine.get_meshtable()->get_background_mesh_01()->draw();
}

/**
 * Function hides all menu sprites
 */
void engine_c::hide_menu_sprites(){
	ui->get_spritetable()->set_group_hidden( GROUP_MENU, true );
	ui->update_sprites();
}

/**
 * Function shows all menu sprites
 */
void engine_c::show_menu_sprites(){

}

/**
 * Function hides all game sprites
 */
void engine_c::hide_game_sprites(){
	ui->get_spritetable()->set_group_hidden( GROUP_GAME, true );
	ui->update_sprites();
}

/**
 * Function shows all game sprites
 */
void engine_c::show_game_sprites(){
	ui->get_spritetable()->set_group_hidden( GROUP_GAME, false );
	ui->update_sprites();	
}

/**
 * Function hides all sprites
 */
void engine_c::hide_all_sprites(){
	hide_game_sprites();
	hide_menu_sprites();
}

/**
 * Function shows all sprites
 */
void engine_c::show_all_sprites(){
	show_game_sprites();
	show_menu_sprites();	
}

/**
 * Function hides menu bgs
 */
void engine_c::hide_menu_bgs(){
ui->get_bgtable()->set_group_hidden( GROUP_MENU, true );	
}

/**
 * Function shows menu bgs
 */
void engine_c::show_menu_bgs(){
	ui->get_bgtable()->set_group_hidden( GROUP_MENU, false );	
}

/**
 * Function hides game bgs
 */
void engine_c::hide_game_bgs(){
	ui->get_bgtable()->set_group_hidden( GROUP_GAME, true );	
}

/**
 * Function shows game bgs
 */
void engine_c::show_game_bgs(){
	ui->get_bgtable()->set_group_hidden( GROUP_GAME, false );
}

/**
 * Function hides menu 2D objects
 */
void engine_c::hide_menu_2D_objects(){
	// Calls the functions to hide the bgs and sprites 
	hide_menu_sprites();
	hide_menu_bgs();
}

/**
 * Function shows the menu 2D objects
 */
void engine_c::show_menu_2D_objects(){
	// Calls the functions to show the bgs and sprites 
	show_menu_sprites();
	show_menu_bgs();
}

/**
 * Function hides menu 3D objects
 */
void engine_c::hide_menu_3D_objects(){
	
}

/**
 * Function shows the menu 3D objects
 */
void engine_c::show_menu_3D_objects(){

}

/**
 * Function hides game 2D objects
 */
void engine_c::hide_game_2D_objects(){
	// Calls the functions to hide the bgs and sprites 
	hide_game_sprites();
	hide_game_bgs();	
}

/**
 * Function shows the game 2D objects
 */
void engine_c::show_game_2D_objects(){
	// Calls the functions to show the bgs and sprites 
	show_game_sprites();
	show_game_bgs();
}

/**
 * Function hides game 3D objects
 */
void engine_c::hide_game_3D_objects(){
	
}

/**
 * Function shows the game 3D objects
 */
void engine_c::show_game_3D_objects(){

}

/**
 * Prints out some debug information
 */
void engine_c::print_debug_info(){

	iprintf("\x1b[0;0HR: (%d, %d, %d),      \n", bottom_cam.rotation.x, bottom_cam.rotation.y, bottom_cam.rotation.z);
	iprintf("\x1b[1;0HL: (%d, %d, %d),      \n", bottom_cam.x, bottom_cam.y, bottom_cam.z);

	if (camera_mode == true) iprintf("\x1b[21;0HCamera Mode (select to change)\n");
	else iprintf("\x1b[21;0HGame Mode   (select to change)\n");
}

/**
 * Set's camera information
 */
void engine_c::set_camera( bool screen, camera_t_ptr new_cam )
{
	if (screen == BOTTOM)
	{
		bottom_cam.x = new_cam->x;
		bottom_cam.y = new_cam->y;
		bottom_cam.z = new_cam->z;
		bottom_cam.rotation.x = new_cam->rotation.x;
		bottom_cam.rotation.y = new_cam->rotation.y;
		bottom_cam.rotation.z = new_cam->rotation.z;
	}
	// top screen camera was not needed.
}


// end of file
