/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: spritetable.cpp
 * Date: 8th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry.
 * Description: sprite table source file
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#include "spritetable.h"
#include "unit_all_stats.h"
#include "util.h"

/**
 * Method to add a sprite
 */
sprite_c * spritetable_c::addSprite(	const unsigned int * tiles,
										unsigned int tiles_len,
										const unsigned short * pal,
										unsigned int pal_len,
										unsigned int width,
										unsigned int height,
										unsigned int x,
										unsigned int y,
										unsigned int angle,
										bool isRotateScale,
										bool screen ){
	/* for array selection */
	int scr=0;
	if( screen == BOTTOM ){
		scr = 1;
	}

	/* Check to make sure not overrunning the max number of sprites */
	if( currentOAMId[scr] > SPRITE_COUNT || width != height ){
		return false;
	}

	/* Create the info handler entry */
	sprite_c * currentInfo = &spriteInfo[currentOAMId[scr]][scr];

	/* Create the OAM entry */
	SpriteEntry * currentEntry;
	if( screen == BOTTOM ){
		currentEntry = &oamBottomRef->oamBuffer[currentOAMId[scr]];		
	}else{
		currentEntry = &oamTopRef->oamBuffer[currentOAMId[scr]];
	}

	/* Fill the info handler struct */
	currentInfo->oamID = currentOAMId[scr];
	currentInfo->width = width;
	currentInfo->height = height;
	currentInfo->angle = 0; /* Default angle info */
	currentInfo->entry = currentEntry;
	
	/* Fill the OAM entry struct */
	currentEntry->x = x;
	currentEntry->y = y;
	currentEntry->isRotateScale = isRotateScale;

	currentEntry->isSizeDouble = false;
	currentEntry->blendMode = OBJMODE_NORMAL;
	currentEntry->isMosaic = false;
	currentEntry->colorMode = OBJCOLOR_16;
	currentEntry->shape = OBJSHAPE_SQUARE;
	currentEntry->rotationIndex = currentInfo->oamID;

	/* Object size */
	switch( width ){
		case 8:
			currentEntry->size = OBJSIZE_8;
			break;
		case 16:
			currentEntry->size = OBJSIZE_16;
			break;
		case 32:
			currentEntry->size = OBJSIZE_32;
			break;
		case 64:
			currentEntry->size = OBJSIZE_64;
			break;
		default:
			/* Incorrect object size */
			return false;
			break;
	}

	currentEntry->gfxIndex = nextAvailableTileIdx[scr];
	nextAvailableTileIdx[scr] += tiles_len / BYTES_PER_16_COLOR_TILE;
	currentEntry->priority = OBJPRIORITY_0;
	currentEntry->palette = currentInfo->oamID;
	
	if( screen == BOTTOM ){
		/* Copy in the palette */
		dmaCopyHalfWords( SPRITE_DMA_CHANNEL,
						  (const void*)pal,
						  &SPRITE_PALETTE[currentInfo->oamID * COLORS_PER_PALETTE],
						  pal_len );

		/* Copy in the sprite */
		dmaCopyHalfWords( SPRITE_DMA_CHANNEL,
						  (const void*)tiles,
						  &SPRITE_GFX[currentEntry->gfxIndex * OFFSET_MULTIPLIER],
						  tiles_len );
	}else{
		/* Copy in the palette */
		dmaCopyHalfWords( SPRITE_DMA_CHANNEL,
						  (const void*)pal,
						  &SPRITE_PALETTE_SUB[currentInfo->oamID * COLORS_PER_PALETTE],
						  pal_len );

		/* Copy in the sprite */
		dmaCopyHalfWords( SPRITE_DMA_CHANNEL,
						  (const void*)tiles,
						  &SPRITE_GFX_SUB[currentEntry->gfxIndex * OFFSET_MULTIPLIER],
						  tiles_len );
	}

	/* Increment the number of sprites in the table */
	numSprites[scr]++;
	/* Increment the OAM id for that particular OAM */
	currentOAMId[scr]++;

	/* Return the current entry */
	return currentInfo;
}

/**
 * Set a particular group's hidden settings
 */
void spritetable_c::set_group_hidden( int group, bool hidden ){
	for( int screen=0; screen < 2; screen++ ){	// Iterate through the screens
		for( int i=0; i < numSprites[screen]; i++ ){	// Iterate through the sprites on the screen
			if( group == spriteInfo[i][screen].get_group() ){	// Check the group
				spriteInfo[i][screen].setHidden( hidden );		// Set it to the hidden value passed
			}
		}
	}
}

/**
 * 
 */

/**
 * Fills the references passed with the appropriate value
 */
void spritetable_c::get_sprite_as_int( int value,
									   const unsigned int ** tiles,
									   unsigned int * tileslen,
									   const unsigned short ** pal,
									   unsigned int * pallen ){
	switch( value ){
		case 0:
			*tiles = dig_0Tiles;
			*tileslen = dig_0TilesLen;
			*pal = dig_0Pal;
			*pallen = dig_0PalLen;
			break;

		case 1:
			*tiles = dig_1Tiles;
			*tileslen = dig_1TilesLen;
			*pal = dig_1Pal;
			*pallen = dig_1PalLen;
			break;

		case 2:
			*tiles = dig_2Tiles;
			*tileslen = dig_2TilesLen;
			*pal = dig_2Pal;
			*pallen = dig_2PalLen;
			break;

		case 3:
			*tiles = dig_3Tiles;
			*tileslen = dig_3TilesLen;
			*pal = dig_3Pal;
			*pallen = dig_3PalLen;
			break;

		case 4:
			*tiles = dig_4Tiles;
			*tileslen = dig_4TilesLen;
			*pal = dig_4Pal;
			*pallen = dig_4PalLen;
			break;

		case 5:
			*tiles = dig_5Tiles;
			*tileslen = dig_5TilesLen;
			*pal = dig_5Pal;
			*pallen = dig_5PalLen;
			break;

		case 6:
			*tiles = dig_6Tiles;
			*tileslen = dig_6TilesLen;
			*pal = dig_6Pal;
			*pallen = dig_6PalLen;
			break;

		case 7:
			*tiles = dig_7Tiles;
			*tileslen = dig_7TilesLen;
			*pal = dig_7Pal;
			*pallen = dig_7PalLen;
			break;

		case 8:
			*tiles = dig_8Tiles;
			*tileslen = dig_8TilesLen;
			*pal = dig_8Pal;
			*pallen = dig_8PalLen;
			break;

		case 9:
			*tiles = dig_9Tiles;
			*tileslen = dig_9TilesLen;
			*pal = dig_9Pal;
			*pallen = dig_9PalLen;
			break;

		default: // error code is backslash
			*tiles = dashTiles;
			*tileslen = dashTilesLen;
			*pal = dashPal;
			*pallen = dashPalLen;
			break;
	}
}

/**
 * Sets the correct sprites to correspond with the parsed
 * integer
 */
void spritetable_c::set_number2digits( sprite_c ** spr, int value ){
	// get the number of digits

	const unsigned int * tiles = NULL;
	unsigned int tileslen = 0;
	const unsigned short * pal = NULL;
	unsigned int pallen = 0;

	int i=0;
	int result=0;
	int current=value;
	int digits=0;

	// Evalute number of digits
	for( int j=0; ; j++ ){
		if( spr[j] == NULL )
			break;

		digits++;
	}

	if( value > 9999 || value < 0 ){
		// Range is 0-99 inclusive
		return;
	}

	// Blank all the digits
	for( int i=0; i<digits; i++ ){
		spr[i]->set_sprite( dig_0Tiles,
						    dig_0TilesLen, 
						    dig_0Pal,
						    dig_0PalLen );		
	}

	// Iterate through the digits
	for( i=0; i<digits; i++ ){
		result = current/pow( 10, digits-( i+1 ) );
		current -= result*pow( 10, digits-( i+1 ) );

		get_sprite_as_int( result, &tiles, &tileslen, &pal, &pallen );

		spr[i]->set_sprite( tiles,
							tileslen,
							pal,
							pallen );
	}
}

/**
 * Sets the displayed value in the global resource field
 */
void spritetable_c::set_res_field( int value ){
	set_number2digits( res_dig, value );
}

/**
 * Sets the displayed value in the local resource field
 */
void spritetable_c::set_local_res_field( int value ){
	set_number2digits( res_local_dig, value );
}

/**
 * Sets the displayed value in the local units field
 */
void spritetable_c::set_local_units_field( int value ){
	set_number2digits( units_local_dig, value );
}

/**
 * Sets the displayed value in the local enemies field
 */
void spritetable_c::set_local_enemies_field( int value ){
	set_number2digits( enemies_local_dig, value );
}

/**
 * Sets the displayed value in the hp field
 */
void spritetable_c::set_hp_field( int value ){
	set_number2digits( hp_dig, value );
}

/**
 * Sets the displayed value in the armor field
 */
void spritetable_c::set_armor_field( int value ){
	set_number2digits( armor_dig, value );
}

/**
 * Sets the displayed value in the ap field
 */
void spritetable_c::set_ap_field( int value ){
	set_number2digits( ap_dig, value );
}

/**
 * Sets the displayed value in the rng field
 */
void spritetable_c::set_rng_field( int value ){
	set_number2digits( rng_dig, value );
}

/**
 * Sets the displayed value in the spd field
 */
void spritetable_c::set_spd_field( int value ){
	set_number2digits( spd_dig, value );
}

/**
 * Sets the displayed value in the cd field
 */
void spritetable_c::set_cd_field( int value ){
	set_number2digits( cd_dig, value );
}

/**
 * Sets the unit icon and descriptions
 */
void spritetable_c::set_unit( int unit ){
	switch( unit ){
		case GATHERER:
			unit_icon->set_sprite( gatherer_32Tiles,
		       gatherer_32TilesLen, 
			   gatherer_32Pal,
			   gatherer_32PalLen );

			unit_desc->set_sprite( gatherer_textTiles,
		       gatherer_textTilesLen, 
			   gatherer_textPal,
			   gatherer_textPalLen );

			abil_01_icon->set_sprite( repairTiles,
		       repairTilesLen, 
			   repairPal,
			   repairPalLen );

			abil_02_icon->set_sprite( gatherTiles,
		       gatherTilesLen, 
			   gatherPal,
			   gatherPalLen );

			abil_01_desc->set_sprite( text_repairTiles,
		       text_repairTilesLen, 
			   text_repairPal,
			   text_repairPalLen );

			abil_02_desc->set_sprite( text_gatherTiles,
		       text_gatherTilesLen, 
			   text_gatherPal,
			   text_gatherPalLen );
			break;

		case SCOUT:
			unit_icon->set_sprite( scout_32Tiles,
		       scout_32TilesLen, 
			   scout_32Pal,
			   scout_32PalLen );

			unit_desc->set_sprite( scout_textTiles,
		       scout_textTilesLen, 
			   scout_textPal,
			   scout_textPalLen );

			abil_01_icon->set_sprite( detectTiles,
		       detectTilesLen, 
			   detectPal,
			   detectPalLen );

			abil_01_desc->set_sprite( text_detectTiles,
		       text_detectTilesLen, 
			   text_detectPal,
			   text_detectPalLen );
			break;

		case SOLDIER:
			unit_icon->set_sprite( soldier_32Tiles,
		       soldier_32TilesLen, 
			   soldier_32Pal,
			   soldier_32PalLen );

			unit_desc->set_sprite( soldier_textTiles,
		       soldier_textTilesLen, 
			   soldier_textPal,
			   soldier_textPalLen ); 

			abil_01_icon->set_sprite( slowTiles,
		       slowTilesLen, 
			   slowPal,
			   slowPalLen );

			abil_01_desc->set_sprite( text_slowTiles,
		       text_slowTilesLen, 
			   text_slowPal,
			   text_slowPalLen );
			break;

		case DEMO:
			unit_icon->set_sprite( demo_32Tiles,
		       demo_32TilesLen, 
			   demo_32Pal,
			   demo_32PalLen );

			unit_desc->set_sprite( demo_textTiles,
		       demo_textTilesLen, 
			   demo_textPal,
			   demo_textPalLen );

			abil_01_icon->set_sprite( stealthTiles,
		       stealthTilesLen, 
			   stealthPal,
			   stealthPalLen );

			abil_01_desc->set_sprite( text_stealthTiles,
		       text_stealthTilesLen, 
			   text_stealthPal,
			   text_stealthPalLen );

			abil_02_icon->set_sprite( piercearmorTiles,
		       piercearmorTilesLen, 
			   piercearmorPal,
			   piercearmorPalLen );

			abil_02_desc->set_sprite( text_piercearmorTiles,
		       text_piercearmorTilesLen, 
			   text_piercearmorPal,
			   text_piercearmorPalLen );
			break;

		case HEAVY:
			unit_icon->set_sprite( heavy_32Tiles,
		       heavy_32TilesLen, 
			   heavy_32Pal,
			   heavy_32PalLen );

			unit_desc->set_sprite( heavy_textTiles,
		       heavy_textTilesLen, 
			   heavy_textPal,
			   heavy_textPalLen );

			abil_01_icon->set_sprite( aoeTiles,
		       aoeTilesLen, 
			   aoePal,
			   aoePalLen );

			abil_01_desc->set_sprite( text_aoeTiles,
		       text_aoeTilesLen, 
			   text_aoePal,
			   text_aoePalLen );

			abil_02_icon->set_sprite( heavyarmorTiles,
		       heavyarmorTilesLen, 
			   heavyarmorPal,
			   heavyarmorPalLen );

			abil_02_desc->set_sprite( text_heavyarmorTiles,
		       text_heavyarmorTilesLen, 
			   text_heavyarmorPal,
			   text_heavyarmorPalLen );
			break;

		default:
			// incorrect parameter
			break;
	}
}

/**
 * Creator for spritetable
 */
spritetable_c::spritetable_c( OAMTable * oamTop, OAMTable * oamBottom ){
	/* Clear the number of sprites */
	numSprites[0]=0;numSprites[1]=0;

	/* Assign the OAM references */
	oamTopRef = oamTop;
	oamBottomRef = oamBottom;

	//=============

	abil_01_icon = addSprite( repairTiles,
		       repairTilesLen, 
			   repairPal,
			   repairPalLen,
			   16,
			   16,
			   149, 
			   150, 
			   0,
			   true,
			   TOP );

	abil_02_icon = addSprite( gatherTiles,
		       gatherTilesLen, 
			   gatherPal,
			   gatherPalLen,
			   16,
			   16,
			   149, 
			   167, 
			   0,
			   true,
			   TOP );	

	//=============

	unit_desc = addSprite( gatherer_textTiles,
		       gatherer_textTilesLen, 
			   gatherer_textPal,
			   gatherer_textPalLen,
			   64,
			   64,
			   6, 
			   133, 
			   0,
			   true,
			   TOP );	

	unit_icon = addSprite( gatherer_32Tiles,
		       gatherer_32TilesLen, 
			   gatherer_32Pal,
			   gatherer_32PalLen,
			   32,
			   32,
			   9, 
			   152, 
			   0,
			   true,
			   TOP );	

	//=============

	res_dig[0] = addSprite(	dig_0Tiles,
							dig_0TilesLen, 
							dig_0Pal,
							dig_0PalLen,
							16,
							16,
							24, 
							8, 
							0,
							true,
							TOP );

	res_dig[1] = addSprite(	dig_0Tiles,
							dig_0TilesLen, 
							dig_0Pal,
							dig_0PalLen,
							16,
							16,
							29, 
							8, 
							0,
							true,
							TOP );

	res_dig[2] = addSprite( dig_0Tiles,
							dig_0TilesLen, 
							dig_0Pal,
							dig_0PalLen,
							16,
							16,
							34, 
							8, 
							0,
							true,
							TOP );

	res_dig[3] = addSprite( dig_0Tiles,
							dig_0TilesLen, 
							dig_0Pal,
							dig_0PalLen,
							16,
							16,
							39, 
							8, 
							0,
							true,
							TOP );

	//=============

	unit_tot[0] = addSprite( dig_0Tiles,
							 dig_0TilesLen, 
							 dig_0Pal,
							 dig_0PalLen,
							 16,
							 16,
							 24, 
							 26, 
							 0,
							 true,
							 TOP );

	unit_tot[1] = addSprite( dashTiles,
							 dashTilesLen, 
							 dashPal,
							 dashPalLen,
							 16,
							 16,
							 29, 
							 26, 
							 0,
							 true,
							 TOP );

	unit_tot[2] = addSprite( dig_0Tiles,
							 dig_0TilesLen, 
							 dig_0Pal,
							 dig_0PalLen,
							 16,
							 16,
							 34, 
							 26, 
							 0,
							 true,
							 TOP );

	unit_tot[3] = addSprite( dig_0Tiles,
							 dig_0TilesLen, 
							 dig_0Pal,
							 dig_0PalLen,
							 16,
							 16,
							 39, 
							 26, 
							 0,
							 true,
							 TOP );

	//=============

	res_local_dig[0] = addSprite( dig_0Tiles,
		       dig_0TilesLen, 
			   dig_0Pal,
			   dig_0PalLen,
			   16,
			   16,
			   24, 
			   69, 
			   0,
			   true,
			   TOP );

	res_local_dig[1] = addSprite( dig_0Tiles,
		       dig_0TilesLen, 
			   dig_0Pal,
			   dig_0PalLen,
			   16,
			   16,
			   30, 
			   69, 
			   0,
			   true,
			   TOP );

	//=============

	units_local_dig[0] = addSprite( dig_0Tiles,
		       dig_0TilesLen, 
			   dig_0Pal,
			   dig_0PalLen,
			   16,
			   16,
			   24, 
			   86, 
			   0,
			   true,
			   TOP );

	units_local_dig[1] = addSprite( dig_0Tiles,
		       dig_0TilesLen, 
			   dig_0Pal,
			   dig_0PalLen,
			   16,
			   16,
			   30, 
			   86, 
			   0,
			   true,
			   TOP );

	//=============

	enemies_local_dig[0] = addSprite( dig_0Tiles,
		       dig_0TilesLen, 
			   dig_0Pal,
			   dig_0PalLen,
			   16,
			   16,
			   24, 
			   104, 
			   0,
			   true,
			   TOP );

	enemies_local_dig[1] = addSprite( dig_0Tiles,
		       dig_0TilesLen, 
			   dig_0Pal,
			   dig_0PalLen,
			   16,
			   16,
			   30, 
			   104, 
			   0,
			   true,
			   TOP );

	//==============

	hp_dig[0] = addSprite( dig_0Tiles,
		       dig_0TilesLen, 
			   dig_0Pal,
			   dig_0PalLen,
			   16,
			   16,
			   70, 
			   134, 
			   0,
			   true,
			   TOP );

	hp_dig[1] = addSprite( dig_0Tiles,
		       dig_0TilesLen, 
			   dig_0Pal,
			   dig_0PalLen,
			   16,
			   16,
			   76, 
			   134, 
			   0,
			   true,
			   TOP );

	//=============

	armor_dig[0] = addSprite( dig_0Tiles,
		       dig_0TilesLen, 
			   dig_0Pal,
			   dig_0PalLen,
			   16,
			   16,
			   70, 
			   151, 
			   0,
			   true,
			   TOP );

	armor_dig[1] = addSprite( dig_0Tiles,
		       dig_0TilesLen, 
			   dig_0Pal,
			   dig_0PalLen,
			   16,
			   16,
			   76, 
			   151, 
			   0,
			   true,
			   TOP );

	ap_dig[0] = addSprite( dig_0Tiles,
		       dig_0TilesLen, 
			   dig_0Pal,
			   dig_0PalLen,
			   16,
			   16,
			   70, 
			   169, 
			   0,
			   true,
			   TOP );

	ap_dig[1] = addSprite( dig_0Tiles,
		       dig_0TilesLen, 
			   dig_0Pal,
			   dig_0PalLen,
			   16,
			   16,
			   76, 
			   169, 
			   0,
			   true,
			   TOP );

	//==============

	rng_dig[0] = addSprite( dig_0Tiles,
		       dig_0TilesLen, 
			   dig_0Pal,
			   dig_0PalLen,
			   16,
			   16,
			   121, 
			   134, 
			   0,
			   true,
			   TOP );

	rng_dig[1] = addSprite( dig_0Tiles,
		       dig_0TilesLen, 
			   dig_0Pal,
			   dig_0PalLen,
			   16,
			   16,
			   127, 
			   134, 
			   0,
			   true,
			   TOP );

	//=============

	spd_dig[0] = addSprite( dig_0Tiles,
		       dig_0TilesLen, 
			   dig_0Pal,
			   dig_0PalLen,
			   16,
			   16,
			   121, 
			   151, 
			   0,
			   true,
			   TOP );

	spd_dig[1] = addSprite( dig_0Tiles,
		       dig_0TilesLen, 
			   dig_0Pal,
			   dig_0PalLen,
			   16,
			   16,
			   127, 
			   151, 
			   0,
			   true,
			   TOP );

	//=============

	cd_dig[0] = addSprite( dig_0Tiles,
		       dig_0TilesLen, 
			   dig_0Pal,
			   dig_0PalLen,
			   16,
			   16,
			   121, 
			   169, 
			   0,
			   true,
			   TOP );

	cd_dig[1] = addSprite( dig_0Tiles,
		       dig_0TilesLen, 
			   dig_0Pal,
			   dig_0PalLen,
			   16,
			   16,
			   127, 
			   169, 
			   0,
			   true,
			   TOP );

	//=============

	abil_01_desc = addSprite( text_repairTiles,
		       text_repairTilesLen, 
			   text_repairPal,
			   text_repairPalLen,
			   64,
			   64,
			   170, 
			   153, 
			   0,
			   true,
			   TOP );

	abil_02_desc = addSprite( text_gatherTiles,
		       text_gatherTilesLen, 
			   text_gatherPal,
			   text_gatherPalLen,
			   64,
			   64,
			   170, 
			   170, 
			   0,
			   true,
			   TOP );

	//=============

	addSprite( dpadTiles,
		       dpadTilesLen, 
			   dpadPal,
			   dpadPalLen,
			   64,
			   64,
			   192,
			   128,
			   0,
			   true,
			   BOTTOM );

	int i,incre = 2; // old value: 16
	for( i=0;i<9;i++ ){
		addSprite( unit_slotTiles,
				   unit_slotTilesLen, 
				   unit_slotPal,
				   unit_slotPalLen,
				   16,
				   16,
				   incre,
				   174, // old value: 144
				   0,
				   true,
				   BOTTOM );
		incre+=18;
	}
}