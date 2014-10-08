/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: intro.h
 * Date: 19th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry
 * Description: plays intro.
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef INTRO_H
#define INTRO_H

// libs
#include <nds.h>
#include <stdio.h>

// files
#include "types.h"
#include "event.h"
#include "brightness.h"

// define
#define MENU_OPT_1 1
#define MENU_OPT_2 2
#define MENU_OPT_3 3

// functions 

void play_intro();
int play_menu();

#endif
