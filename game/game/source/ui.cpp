/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: ui.cpp
 * Date: 5th of May, 2010.
 * Author(s): Christopher Berry.
 * Description: user interface management class source file
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#include "ui.h"

#include <stdio.h>

#define BG_DMA_CHANNEL 3

/**
 * Updates the OAMs
 */
void ui_c::update_sprites(){
	updateTopOAM( oamTop );
	updateBottomOAM( oamBottom );
}

/**
 * Returns the bg table
 */
bgtable_c * ui_c::get_bgtable(){
	return bgtable;
}

/**
 * Returns the sprite table
 */
spritetable_c * ui_c::get_spritetable(){
	return spritetable;
}

/**
 * Clears the OAM memory
 */
void ui_c::initOAM(OAMTable * oam) {
    for (int i = 0; i < SPRITE_COUNT; i++) {
        oam->oamBuffer[i].attribute[0] = ATTR0_DISABLED;
        oam->oamBuffer[i].attribute[1] = 0;
        oam->oamBuffer[i].attribute[2] = 0;
    }
    for (int i = 0; i < MATRIX_COUNT; i++) {
        oam->matrixBuffer[i].hdx = 1 << 8;
        oam->matrixBuffer[i].hdy = 0;
        oam->matrixBuffer[i].vdx = 0;
        oam->matrixBuffer[i].vdy = 1 << 8;
    }
}

/**
 * Updates the top OAM table
 */
void ui_c::updateTopOAM( OAMTable * oam ) {
    DC_FlushAll();
    dmaCopyHalfWords( SPRITE_DMA_CHANNEL,
                      oam->oamBuffer,
                      OAM_SUB,
                      SPRITE_COUNT * sizeof( SpriteEntry ) );
}

/**
 * Updates the bottom OAM table
 */
void ui_c::updateBottomOAM( OAMTable * oam ) {
    DC_FlushAll();
    dmaCopyHalfWords( SPRITE_DMA_CHANNEL,
                      oam->oamBuffer,
                      OAM,
                      SPRITE_COUNT * sizeof( SpriteEntry ) );
}

/**
 * Inits the console
 */
void ui_c::init_console(){
	// Init the console
	consoleInit( &console, 3, BgType_ExRotation, BgSize_ER_256x256, 20, 2, false, false );

	// Init the console font
	init_font();

	// Set the window for the console
	consoleSetWindow( &console, 0, 0, 100, 14 );

	// Submit the BG layer information for the console
	REG_BG3PA_SUB = 1 << 8;
    REG_BG3PB_SUB = 0;
    REG_BG3PC_SUB = 0;
    REG_BG3PD_SUB = 1 << 8;
    REG_BG2X_SUB = 0;
    REG_BG2Y_SUB = 0;
}

/**
 * Inits the console font
 */
void ui_c::init_font(){
	// Init the console font
	font.gfx = (u16*)white_fontTiles;
	font.pal = (u16*)white_fontPal;
	font.numChars = 95;
	font.numColors =  white_fontPalLen / 2;
	font.bpp = 8;
	font.asciiOffset = 32;
	font.convertSingleColor = false;
	
	// Set the font for the console
	consoleSetFont( &console, &font);
}

/**
 * Constructor
 */
ui_c::ui_c(){
	// Initialize all the different parts of the UI

	// Create the OAM tables
	oamTop = new OAMTable();
	oamBottom = new OAMTable();

	// Clear the two OAM tables
	initOAM( oamTop );
	initOAM( oamBottom );

	// Create the sprite management object
	spritetable = new spritetable_c( oamTop, oamBottom );

	// Update the HW OAM tables
	updateTopOAM( oamTop );
	updateBottomOAM( oamBottom );

	// Init the console
	//init_console();

	// Init the backgrounds
	bgtable = new bgtable_c();

	/*iprintf("\x1b[0;0H00" );
	iprintf("\x1b[1;0H01" );
	iprintf("\x1b[2;0H02" );
	iprintf("\x1b[3;0H03" );
	iprintf("\x1b[4;0H04" );
	iprintf("\x1b[5;0H05" );
	iprintf("\x1b[6;0H06" );
	iprintf("\x1b[7;0H07" );
	iprintf("\x1b[8;0H08" );
	iprintf("\x1b[9;0H09" );
	iprintf("\x1b[10;0H10" );
	iprintf("\x1b[11;0H11" );
	iprintf("\x1b[12;0H12" );
	iprintf("\x1b[13;0H13" );
	iprintf("\x1b[14;0H14" );
	iprintf("\x1b[15;0H15" );
	iprintf("\x1b[16;0H16" );
	iprintf("\x1b[17;0H17" );
	iprintf("\x1b[18;0H18" );
	iprintf("\x1b[19;0H19" );
	iprintf("\x1b[20;0H20" );
	iprintf("\x1b[21;0H21" );
	iprintf("\x1b[22;0H22" );
	iprintf("\x1b[23;0H23" );*/
}