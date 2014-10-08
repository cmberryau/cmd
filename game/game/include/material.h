/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: material.h
 * Date: 8th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry
 * Description: material class header
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef MATERIAL_H
#define MATERIAL_H

#include "types.h"

#include "default_alpha_tex_bin.h"
#include "default_alpha_pal_bin.h"

#define DEFAULT_MATERIAL_SIZE 32
#define MAX_MATERIALS 350
#define MAX_PALETTES 5

#define DEFAULT_TEX_ID				0	
#define DEFAULT_TEX_LEN				0
#define DEFAULT_PALETTE_OFFSET		0
#define DEFAULT_NUM_PALETTES		1
#define DEFAULT_SELECTED_PALETTE	0
#define DEFAULT_PALETTE_INDEX		0

struct material_file_info_t{
	u8 * tex;

	u8 * pal[MAX_PALETTES];
	u32 pal_len[MAX_PALETTES];
	s8 num_pal;
};

class material_c{
	private:
		int id;			/* GL texture ID */
		int size;		/* Texture size */

		u8 * tex;		/* Texture */
		u32 tex_len;	/* Texture length */

		u8 * pal[MAX_PALETTES];			/* Palette */
		u32 pal_len[MAX_PALETTES];		/* Palette length */
		u32 pal_offset[MAX_PALETTES];	/* Palette offset */
		s8 num_pal;
		s8 selected_pal;

		bool loaded;	/* Texture & Palette loaded */

	public:
		int use();		/* Enable the texture */
		int load();		/* Load the texture */

		int unload_from_client();	/* Unload the texture from client memory */
		int unload_from_server();	/* Unload the texture from server memory */

		material_c( material_file_info_t file_info ); // Directed constructor

		material_c();   // Default creator
		~material_c();  // Default destructor
};

#endif /* MATERIAL_H */