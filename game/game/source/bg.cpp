/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: bg.cpp
 * Date: 5th of May, 2010.
 * Author(s): Christopher Berry.
 * Description: Background object class source file
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#include "bg.h"
#include "ui.h"

/**
 * Setter for the group
 */
void bg_c::set_group( int group ){
	this->group = group;
}

/**
 * Getter for the group
 */
int bg_c::get_group(){
	return group;
}

/**
 * Update the hardware registers
 */
void bg_c::update(){
	// Setup the affine matrix register
	if( sub ){
		if( index == BG_INDEX_2 ){
			REG_BG2PA_SUB = PA;
			REG_BG2PB_SUB = PB;
			REG_BG2PC_SUB = PC;
			REG_BG2PD_SUB = PD;
			REG_BG2X_SUB = X;
			REG_BG2Y_SUB = Y;
		}
	}else{
		if( index == BG_INDEX_2 ){
			REG_BG2PA = PA;
			REG_BG2PB = PB;
			REG_BG2PC = PC;
			REG_BG2PD = PD;
			REG_BG2X = X;
			REG_BG2Y = Y;
		}
	}
}

/**
 * Set the absolute scale
 */
void bg_c::set_scale( int scale ){
	switch( scale ){
		case 1:
			// Normal scale
			PA = 1 << 8;
			PD = 1 << 8;
			break;
		case 2:
			// Double scale
			PA = 1 << 7;
			PD = 1 << 7;			
			break;
		default:
			// Normal scale
			PA = 1 << 8;
			PD = 1 << 8;
			break;
	}
	// Setup the affine matrix register
	update();
}

/**
 * Toggler for the hidden state
 */
void bg_c::set_hidden( bool hidden ){
	if( hidden ){
		hide();
	}else{
		show();
	}
}

/**
 * Copies the BG into the frame memory
 */
void bg_c::show(){
	vu16 bgcr;
		
	// Note that we are assuming the background is on the sub engine
	if( size == 128 ){
		bgcr = BG_BMP16_128x128 |
			   BG_BMP_BASE(0) |
			   BG_PRIORITY(3);
	} else if( size == 256 ){
		bgcr = BG_BMP16_256x256 |
			   BG_BMP_BASE(0) |
			   BG_PRIORITY(3);
	}

	// index assignment
	if( sub){
		if( index == BG_INDEX_2 ){
			REG_BG2CNT_SUB = bgcr;
		} 
	}else{
		if( index == BG_INDEX_2 ){
			REG_BG2CNT = bgcr;
		} 
	}

	// Setup the affine matrix register
	update();

	// We then load the BG into the frame
	if( sub ){
		dmaCopyHalfWords( BG_DMA_CHANNEL,
						  bitmap, 
						  ( uint16 * )BG_BMP_RAM_SUB(0),
						  bitmap_len );
	}else{
		dmaCopyHalfWords( BG_DMA_CHANNEL,
						  bitmap, 
						  ( uint16 * )BG_BMP_RAM(0),
						  bitmap_len );
	}
}

/**
 * Hides the BG
 */
void bg_c::hide(){
	/* We just fill where it was with NULL, seems to work fine */
	if( sub ){
		dmaFillHalfWords( NULL, ( uint16 * )BG_BMP_RAM_SUB(0), bitmap_len );
	}else{
		dmaFillHalfWords( NULL, ( uint16 * )BG_BMP_RAM(0), bitmap_len );
	}
}

/**
 * Constructor
 */
bg_c::bg_c( const unsigned int * bitmapref,
		    unsigned int bitmaplen,
			int bgsize,
			bool bgsub,
			int bgindex ){
	// Set the bitmap information
	bitmap = bitmapref;
	bitmap_len = bitmaplen;

	// Set other information 
	size = bgsize;
	sub = bgsub;	
	index = bgindex;	// Only using one for forseeable future, though extendable
	group = GROUP_GAME;			// Set as the game group as default

	// Default affine matrix attributes
	PA = 1 << 8;
	PB = 0;
	PC = 0;
	PD = 1 << 8;
	X = 0;
	Y = 0;
}