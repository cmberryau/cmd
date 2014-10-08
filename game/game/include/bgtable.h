/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: bgtable.h
 * Date: 6th of May, 2010.
 * Author(s): Christopher Berry.
 * Description: Background object management class header file
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef BGTABLE_H
#define BGTABLE_H

#include <nds.h>
#include "bg.h"
#include "bg_assets.h"

/* Max number of BGs */
#define MAX_BGS 10

/* BG reference defines */
#define DEFAULT_SCREEN_BG 0
#define TITLE_MENU_BG 1

class bgtable_c{
	private:
		bg_c * bgs[MAX_BGS];				// Array of BGs
		int num_bgs;

	public:
		bg_c * get_bg( unsigned int ref );	// Method to get a background reference from the table

		void set_group_hidden( int group, bool hidden );	// Setter for hiding sprites

		bgtable_c();						// Creator
};

#endif /* BGTABLE_H */