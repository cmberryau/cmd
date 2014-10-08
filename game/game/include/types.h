/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: types.h
 * Date: 8th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry
 * Description: types that commonly appear in other files.
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef TYPES_H
#define TYPES_H

//liraries
#include <nds.h>

// defines

#define SUCCESS 0
#define FAILURE 1

#define TOP false
#define BOTTOM true

#ifndef null
#define null NULL
#endif

// types

//rendermode enum
enum rendermode_t{
	_3D_BOTH_SCREENS,
	_3D_ONE_SCREEN
};

// 2d vector float
typedef struct
{
	float x, y;
} vector_2df_t;

// 2d vector interger
typedef struct
{
	int x, y;
} vector_2di_t;

// spec type ints

// unsigned
typedef struct
{
	u8 x, y;
} vector_2d_u8_t;
typedef struct
{
	u16 x, y;
} vector_2d_u16_t;
typedef struct
{
	u32 x, y;
} vector_2d_u32_t;

// signed
typedef struct
{
	s8 x, y;
} vector_2d_s8_t;
typedef struct
{
	s16 x, y;
} vector_2d_s16_t;
typedef struct
{
	s32 x, y;
} vector_2d_s32_t;

// 3d vector float
typedef struct
{
	float x, y, z;
} vector_3df_t;

// 3d vector interger
typedef struct
{
	int x, y, z;
} vector_3di_t;

// palette
typedef struct
{
	float r, g, b;
} palette_t;

// pointer
typedef palette_t * palette_t_ptr;

// camera
typedef struct
{
	int32 x, y, z;
	vector_3di_t rotation;
} camera_t;

// pointer
typedef camera_t * camera_t_ptr;


#endif

// end of file

