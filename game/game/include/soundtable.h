/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: soundtable.h
 * Date: 13th of January, 2010.
 * Author(s): Christopher Berry.
 * Description: soundbank class header
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef SOUNDTABLE_H
#define SOUNDTABLE_H

#include <nds.h>
#include <maxmod9.h> 
#include "soundbank.h"
#include "soundbank_bin.h"
#include "sound.h"

#define DEFAULT_SOUNDS 20

class soundtable_c{
	private:
		s8 numsounds;
		sound_c sounds[DEFAULT_SOUNDS];
	public:
		void init();
		soundtable_c();
};

#endif /* SOUNDTABLE_H */