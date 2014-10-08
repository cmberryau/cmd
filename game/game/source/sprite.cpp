/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: sprite.cpp
 * Date: 8th of December, 2009.
 * Author(s): Christopher Berry.
 * Description: sprite class source file
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#include "sprite.h"
#include "ui.h"

/**
 * Set the absolute position of the sprite
 */

void sprite_c::setPosition2i( int x, int y ){
	// TODO - COMPLETE
}

/**
 * Set the screen that the sprite is displayed on
 */
void sprite_c::setScreen( bool screen ){
	// TODO - COMPLETE
}

/**
 * Set the sprite's visibility
 */
void sprite_c::setHidden( bool hidden ){
	entry->isRotateScale = !hidden;
	entry->isHidden = hidden;
}

/**
 * Relative translation of sprite
 */
void sprite_c::translate2i( int x, int y ){
	entry->x += x;
	entry->y += y;
}

/**
 * Changes the sprite reference
 */
void sprite_c::set_sprite(	const unsigned int * tiles,
							unsigned int tiles_len,
							const unsigned short * pal,
							unsigned int pal_len ){

	if( screen == BOTTOM ){
		// Copy in the palette
		dmaCopyHalfWords( SPRITE_DMA_CHANNEL,
						  (const void*)pal,
						  &SPRITE_PALETTE[oamID * COLORS_PER_PALETTE],
						  pal_len );

		// Copy in the sprite
		dmaCopyHalfWords( SPRITE_DMA_CHANNEL,
						  (const void*)tiles,
						  &SPRITE_GFX[entry->gfxIndex * OFFSET_MULTIPLIER],
						  tiles_len );
	}else{
		// Copy in the palette
		dmaCopyHalfWords( SPRITE_DMA_CHANNEL,
						  (const void*)pal,
						  &SPRITE_PALETTE_SUB[oamID * COLORS_PER_PALETTE],
						  pal_len );

		// Copy in the sprite
		dmaCopyHalfWords( SPRITE_DMA_CHANNEL,
						  (const void*)tiles,
						  &SPRITE_GFX_SUB[entry->gfxIndex * OFFSET_MULTIPLIER],
						  tiles_len );
	}
}

/**
 * Setter for the group
 */
void sprite_c::set_group( int group ){
	this->group = group;
}

/**
 * Getter for the group
 */
int sprite_c::get_group(){
	return group;
}

/**
 * Creator the sprite information holder
 */
sprite_c::sprite_c(){
	hidden = false; // Shown as default
	screen = TOP;	// Topscreen is default
	width = 8;	
	height = 8;
	angle = 0;
	entry = NULL;
	group = GROUP_GAME;	// sprite group that it belongs to
}