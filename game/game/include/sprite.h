/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: sprite.h
 * Date: 8th of December, 2009.
 * Author(s): Christopher Berry.
 * Description: sprite class header file
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef SPRITE_H
#define SPRITE_H

#include <nds.h>
#include "types.h"

class sprite_c{
	private:
		static const int BYTES_PER_16_COLOR_TILE = 32;
		static const int COLORS_PER_PALETTE = 16;
		static const int BOUNDARY_VALUE = 32;
		static const int OFFSET_MULTIPLIER = BOUNDARY_VALUE / sizeof(SPRITE_GFX[0]);

	public:
		bool hidden;			// Is sprite hidden?
		bool screen;			// What screen this is to be displayed on
		int oamID;				// The OAM ID for this sprite
		int width;				// Width of the sprite
		int height;				// Height of the sprite
		int angle;				// Angle of the sprite
		SpriteEntry * entry;	// The OAM sprite entry for the sprite

		int group;				// Group that the sprite belongs to
		void set_group( int group );	// Setter for the group
		int get_group();				// Getter for the group

		void translate2i(  int x, int y );	// Translate the sprite
		void setPosition2i( int x, int y );	// Absolute positioning
		void setScreen( bool screen );		// Change the sprite's screen
		void setHidden( bool hidden );		// Set the sprite's visibility

		void set_sprite(	const unsigned int * tiles,
									unsigned int tiles_len,
									const unsigned short * pal,
									unsigned int pal_len );

		void set_sprite();					// Set the actual sprite reference

		sprite_c();				// Creator for the sprite class
};

#endif /* SPRITE_H */