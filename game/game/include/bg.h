/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: bg.h
 * Date: 5th of May, 2010.
 * Author(s): Christopher Berry.
 * Description: Background object class header file
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef BG_H
#define BG_H

#define DEFAULT_BG_INDEX 2
#define BG_INDEX_2 2
#define BG_INDEX_3 3
#define BG_DMA_CHANNEL 3

#include <nds.h>

class bg_c{
	private:
		const unsigned int * bitmap;		// Bitmap data
		unsigned int bitmap_len;			// Length of the bitmap data
		unsigned int PA, PB, PC, PD, X, Y;	// Matrix values

		int index;							// Background index
		int size;							// Size of the background
		bool sub;							// Sub or main engine

		int group;							// Group that the bg belongs

		void update();						// Update the hw registers
	public:
		void set_scale( int scale );		// Sets the scale for the background

		void set_hidden( bool hidden );		// Bool toggler for hidden state
		void show();						// Show the background
		void hide();						// Hide the background

		void set_group( int group );		// Setter for the group
		int get_group();					// Getter for the group

		bg_c( const unsigned int * bitmap,	// Creator
			  unsigned int bitmap_len,
			  int bgsize,
			  bool bgsub,
			  int bgindex );								
};

#endif /* BG_H */