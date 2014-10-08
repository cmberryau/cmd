/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: spritetable.h
 * Date: 8th of December, 2009.
 * Author(s): Christopher Berry.
 * Description: spritetable header file
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef SPRITETABLE_H
#define SPRITETABLE_H

#include <nds.h>
#include <assert.h>

#include "sprite.h"
#include "sprite_assets.h"

static const uint8 SPRITE_DMA_CHANNEL = 3;

class spritetable_c{
	private:
		static const int BYTES_PER_16_COLOR_TILE = 32;
		static const int COLORS_PER_PALETTE = 16;
		static const int BOUNDARY_VALUE = 32;
		static const int OFFSET_MULTIPLIER = BOUNDARY_VALUE / sizeof(SPRITE_GFX[0]);

		int nextAvailableTileIdx[2];				// Keeps track of available tiles on top oam
		int currentOAMId[2];						// Keeps track of the current OAMid on top oam
		sprite_c spriteInfo[SPRITE_COUNT][2];		// Sprite info handler array 
		s8 numSprites[2];							// Total number of sprites on top oam

		OAMTable * oamTopRef, *oamBottomRef;		// OAM table reference

		sprite_c * res_dig[5];
		sprite_c * unit_tot[5];

		sprite_c * res_local_dig[3];
		sprite_c * units_local_dig[3];
		sprite_c * enemies_local_dig[3];

		sprite_c * hp_dig[3];
		sprite_c * armor_dig[3];
		sprite_c * ap_dig[3];

		sprite_c * rng_dig[3];
		sprite_c * spd_dig[3];
		sprite_c * cd_dig[3];

		sprite_c * unit_desc;
		sprite_c * unit_icon;

		sprite_c * abil_01_icon;
		sprite_c * abil_02_icon;

		sprite_c * abil_01_desc;
		sprite_c * abil_02_desc;

		void get_sprite_as_int( int value,
								const unsigned int ** tiles,
								unsigned int * tileslen,
								const unsigned short ** pal,
								unsigned int * pallen );

		void set_number2digits( sprite_c ** spr, int value );
		
	public:

		void set_res_field( int value );

		void set_local_res_field( int value );
		void set_local_units_field( int value );
		void set_local_enemies_field( int value );

		void set_hp_field( int value );
		void set_armor_field( int value );
		void set_ap_field( int value );

		void set_rng_field( int value );
		void set_spd_field( int value );
		void set_cd_field( int value );

		void set_unit( int unit );			// sets the unit icon, desc and ability 1 and 2

		sprite_c * addSprite( const unsigned int * tiles, // Function to add a sprite
							  unsigned int tileslen,
							  const unsigned short * pal,
							  unsigned int pallen,
							  unsigned int width,
							  unsigned int height,
							  unsigned int x,
							  unsigned int y,
							  unsigned int angle,
							  bool isRotateScale,
							  bool screen );

		void set_group_hidden( int group, bool hidden );	// Setter for hiding sprites 		

		spritetable_c( OAMTable * oamTop, OAMTable * oamBottom ); // Creator
};

#endif /* SPRITETABLE_H */