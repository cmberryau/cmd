/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: brighness.cpp
 * Date: 23rd of November, 2008.
 * Author: Patrick Randell.
 * Description: screen brighness level functions.
  * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

// libraries
#include <nds.h>

// defines
#define BRIGHTNESS 0x0400006C
#define SCREEN_BASE 0x1000

// functions

/** void set_brightness(u8 screen, s8 bright);
 *  
 *  Sets the brightness level to a screen.
 *  
 *  u8 screen: screen to address, 0 or 1 for main or sub screen.
 *  s8 bright: level of brightness to set the screen to.
 */
void set_brightness(u8 screen, s8 bright);

// white

/** void fade_norm_white(u8 screen);
 *  
 *  Fades a screen out to white.
 *  
 *  u8 screen: screen to address, 0 or 1 for main or sub screen.
 */
void fade_norm_white(u8 screen);

/** void fade_white_norm(u8 screen);
 *  
 *  Fades a screen back to full brightness from white.
 *  
 *  u8 screen: screen to address, 0 or 1 for main or sub screen.
 */
void fade_white_norm(u8 screen);

/** void fade_norm_white_both();
 *  
 *  Fades both screens out to white at the same time.
 */
void fade_norm_white_both();

/** void fade_white_norm_both();
 *  
 *  Fades both screens in to full brightness from white at the same time.
 */
void fade_white_norm_both();

// black

/** void fade_norm_black(u8 screen);
 *  
 *  Fades a screen to black.
 *  
 *  u8 screen: screen to address, 0 or 1 for main or sub screen.
 */
void fade_norm_black(u8 screen);

/** void fade_black_norm(u8 screen);
 *  
 *  Fades a screen back to full brightness from black.
 *  
 *  u8 screen: screen to address, 0 or 1 for main or sub screen.
 */
void fade_black_norm(u8 screen);

/** void fade_norm_black_both();
 *  
 *  Fades both screens out to black at the same time.
 */
void fade_norm_black_both();

/** void fade_black_norm_both();
 *  
 *  Fades both screens in to full brightness from black at the same time.
 */
void fade_black_norm_both();


#endif // BRIGHTNESS_H

// end of file
