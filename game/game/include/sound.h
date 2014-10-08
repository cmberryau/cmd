/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: sound.h
 * Date: 13th of January, 2010.
 * Author(s): Christopher Berry.
 * Description: sound class, contains methods for playing sound.
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef SOUND_H
#define SOUND_H

#include "soundbank.h"

class sound_c{
	private:

	public:
	void play( bool loop );
	void stop();
	//sound_c();
};

#endif /* SOUND_H */