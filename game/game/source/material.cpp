/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: material.cpp
 * Date: 8th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry
 * Description: material source file
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#include "material.h"

/**
 * Load the material, and it's information
 */
int material_c::load(){
	if( loaded ){		// Check if the texture is already loaded
		return SUCCESS;
	}

	/* decide on the compatible GL size enum */
	GL_TEXTURE_SIZE_ENUM glcsize = TEXTURE_SIZE_8;

	switch( size ){
		case 8:
			glcsize = TEXTURE_SIZE_8;
			break;
		case 16:
			glcsize = TEXTURE_SIZE_16;
			break;
		case 32:
			glcsize = TEXTURE_SIZE_32;
			break;
		case 64:
			glcsize = TEXTURE_SIZE_64;
			break;
		case 128:
			glcsize = TEXTURE_SIZE_128;
			break;
		case 256:
			glcsize = TEXTURE_SIZE_256;
			break;
		default:
			/* Size out of bounds */
			break;
	}

	/* create the room */
	glGenTextures( 1, &id );

	/* bind the texture */
	glBindTexture( 0, id );

	/* Provide the texture information */
	glTexImage2D( 0, 0, GL_RGB32_A3, glcsize, glcsize, 0, TEXGEN_TEXCOORD | GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T, (u8*)tex );

	/* Provide the palette information */
	for( int i=0;i <num_pal; i++ ){
		pal_offset[i] = gluTexLoadPal( (u16*)pal[i], pal_len[i], GL_RGB32_A3 );
		/* Load the palette information */
		glTexLoadPal( (u16*)pal[i], pal_len[i], pal_offset[i] );
	}


	/* set the loaded flag as true */
	loaded = true;

	return SUCCESS;
}

/**
 * Unloads the texture from the server end
 * - Should be used to destroy the texture in VRAM
 */
int material_c::unload_from_server(){
	void * texptr;
	texptr = glGetTexturePointer( id );
	free( texptr );
	/* set the loaded flag as false */
	loaded = false;
	return SUCCESS;
}

/**
 * Unload the texture from client storage
 * - Should be used after all textures are loaded
 */
int material_c::unload_from_client(){
	/* Free the textures */
	free( tex );
	free( pal );	
	return SUCCESS;
}

/**
 * Use the material, called before mesh calls
 */
int material_c::use(){
	/* Check the texture pointer */
	if( !loaded ){
		return FAILURE;
	}
	/* Only attempt to use the texture if it is loaded */
	if( loaded ){
		glBindTexture( 0, id );
		glColorTable( GL_RGB32_A3, pal_offset[selected_pal] ); 
	}
	return SUCCESS;
}

/**
 * Material creators
 */

/**
 * Static members
 */

/**
 * Default creator
 * - Uses default texture & properties
 */
material_c::material_c(){
	size = DEFAULT_MATERIAL_SIZE;				// Size of the texture

	id = DEFAULT_TEX_ID;						// Texture ID						 

	loaded = false;								 // Is the texture loaded?

	tex = (u8*)default_alpha_tex_bin;			// Default texture binary
	tex_len = DEFAULT_TEX_LEN;					// Byte length of the texture

	pal[DEFAULT_PALETTE_INDEX] = (u8*)default_alpha_pal_bin;	// Default palette binary
	pal_offset[DEFAULT_PALETTE_INDEX] = DEFAULT_PALETTE_OFFSET;	// Palette offset
	pal_len[DEFAULT_PALETTE_INDEX] = default_alpha_pal_bin_size;// Byte length of the palette
	selected_pal = DEFAULT_SELECTED_PALETTE;					// Default selected palette
	num_pal = DEFAULT_NUM_PALETTES;								// Default number of palettes
}

/**
 * Directed constructor
 */
material_c::material_c( material_file_info_t file_info ){
	size = DEFAULT_MATERIAL_SIZE;

	id = DEFAULT_TEX_ID;	// Texture ID

	loaded = false;

	/* Gather texture information */
	tex = file_info.tex;
	tex_len = DEFAULT_TEX_LEN;

	/* Gather palette information */
	for( int i=0; i<file_info.num_pal; i++ ){
		pal[i] = file_info.pal[i];
		pal_offset[i] = DEFAULT_PALETTE_OFFSET;
		pal_len[i] = file_info.pal_len[i];
	}

	/* Set the initally selected palette to index 0 */
	selected_pal = DEFAULT_SELECTED_PALETTE;
	num_pal = file_info.num_pal;

	/* Verify the information sent */
	if( !tex || !pal ){
		// TODO Error material should go here
	}
}

/**
 * Default destructor
 */
material_c::~material_c(){
	/* Free the textures */
	free( tex );
	free( pal );
}