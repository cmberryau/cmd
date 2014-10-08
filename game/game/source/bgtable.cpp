/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: bgtable.h
 * Date: 6th of May, 2010.
 * Author(s): Christopher Berry.
 * Description: Background object management class source file
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#include "bgtable.h"
#include "ui.h"

/**
 * Returns the reference to the BG
 */
bg_c * bgtable_c::get_bg( unsigned int ref ){
	// Check the scope of the search
	if( ref <= MAX_BGS ){
		// Make sure not null
		if( bgs[ref] != NULL ){
			return bgs[ref];
		}
	}
	return NULL;
}

/**
 *
 */
void bgtable_c::set_group_hidden( int group, bool hidden ){
	for( int i=0; i<num_bgs; i++ ){
		if( bgs[i]->get_group() == group ){
			bgs[i]->set_hidden( hidden );
		}
	}
}

/**
 * Creator
 */
bgtable_c::bgtable_c(){
	// Start creating the BG entries
	num_bgs = 0;

	/*bgs[TITLE_MENU_BG] = new bg_c( menu_topBitmap, menu_topBitmapLen, 128, false, BG_INDEX_2 );
	num_bgs++;
	bgs[TITLE_MENU_BG]->set_scale( 2 );
	bgs[TITLE_MENU_BG]->set_group( GROUP_MENU );*/

	// Start creating the menu topscreen BG
	bgs[DEFAULT_SCREEN_BG] = new bg_c( ui_topBitmap, ui_topBitmapLen, 256, true, BG_INDEX_2 );
	num_bgs++;
	bgs[DEFAULT_SCREEN_BG]->set_scale( 1 );
	bgs[DEFAULT_SCREEN_BG]->set_group( GROUP_GAME );
	// Finish creating the menu topscreen BG
}
