/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: soundtable.cpp
 * Date: 13th of January, 2010.
 * Author(s): Christopher Berry.
 * Description: soundbank class; manages sounds
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#include "soundtable.h"

void soundtable_c::init(){
	mmInitDefaultMem((mm_addr)soundbank_bin);
	mmLoad( MOD_FLATOUTLIES );
	mmStart( MOD_FLATOUTLIES, MM_PLAY_LOOP );
}

soundtable_c::soundtable_c(){
	numsounds = 0;
}