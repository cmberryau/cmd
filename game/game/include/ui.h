/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: ui.h
 * Date: 5th of May, 2010.
 * Author(s): Christopher Berry.
 * Description: user interface management class header file
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef UI_H
#define UI_H

#include "spritetable.h"
#include "bgtable.h"
#include "white_font.h"

#define GROUP_GAME 0 
#define GROUP_MENU 1

class ui_c{
	private:
		OAMTable *oamTop, *oamBottom;				// Client side OAM
		spritetable_c *spritetable;					// Sprite management object
		bgtable_c *bgtable;

		PrintConsole console;						// Console for printing
		ConsoleFont font;							// Font for the console

		void initOAM( OAMTable * oam );				// Clears the passed OAM table
		void updateTopOAM( OAMTable * oam );		// Copies passed version of the OAM into the one in use after vblank
		void updateBottomOAM( OAMTable * oam );		// Copies passed version of the OAM into the one in use after vblank

		void init_console();						// Inits the console
		void init_font();							// Inits the font

	public:
		spritetable_c * get_spritetable();			// returns the sprite table
		bgtable_c * get_bgtable();					// returns the bg table

		void update_sprites();						// Update the sprites

		void hideall();								// Hides all the UI elements
		void showall();								// Shows all the UI elements

		ui_c();										// Creator
};

#endif /* UI_H */