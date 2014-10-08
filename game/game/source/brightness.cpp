/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: brighness.cpp
 * Date: 23rd of November, 2008.
 * Author: Patrick Randell, Christopher Berry
 * Description: brighness level functions, see header.
  * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

// header file
#include "brightness.h"

void set_brightness(u8 screen, s8 bright) 
{
	u16 mode = 1 << 14;
	// check if on negative scale
	if (bright < 0) 
	{
		mode = 2 << 14;
		bright = -bright;
	}
	// keep brigtness level in range
	if (bright > 31)
	{ 
		bright = 31;
	}
	// set brightness
	*(volatile u16 *)(BRIGHTNESS + (SCREEN_BASE * screen)) = bright + mode;
}

// white

void fade_norm_white(u8 screen)
{
	u8 i;
	for (i = 0; i < 32; i++)
	{
		set_brightness(screen, i);
		swiWaitForVBlank();
	}
}

void fade_white_norm(u8 screen)
{
	u8 i;
	for (i = 32; i > 0; i--)
	{
		set_brightness(screen, i);
		swiWaitForVBlank();
	}
}

void fade_norm_white_both()
{
	u8 i;
	for (i = 0; i < 32; i++)
	{
		set_brightness(0, i);
		set_brightness(1, i);
		swiWaitForVBlank();
	}
}

void fade_white_norm_both()
{
	u8 i;
	for (i = 32; i > 0; i--)
	{
		set_brightness(0, i);
		set_brightness(1, i);
		swiWaitForVBlank();
	}
}

// black

void fade_norm_black(u8 screen)
{
	s8 i;
	for (i = 0; i > -32; i--)
	{
		set_brightness(screen, i);
		swiWaitForVBlank();
	}
}


void fade_black_norm(u8 screen)
{
	s8 i;
	for (i = -32; i < 0; i++)
	{
		set_brightness(screen, i);
		swiWaitForVBlank();
	}
}


void fade_norm_black_both()
{
	s8 i;
	for (i = 0; i > -32; i--)
	{
		set_brightness(0, i);
		set_brightness(1, i);
		swiWaitForVBlank();
	}
}


void fade_black_norm_both()
{
	s8 i;
	for (i = -32; i < 0; i++)
	{
		set_brightness(0, i);
		set_brightness(1, i);
		swiWaitForVBlank();
	}
}

// end of file
