/**
 * Map tile display lists
 */

#ifndef DEFAULT_DLIST_H
#define DEFAULT_DLIST_H

u32 default_dlist[] = {
	22, //0

	FIFO_COMMAND_PACK( FIFO_BEGIN, FIFO_NOP, FIFO_NOP, FIFO_NOP ), //1

	GL_QUAD, //2

	FIFO_COMMAND_PACK( FIFO_COLOR, FIFO_TEX_COORD, FIFO_VERTEX16, FIFO_NOP ), //3

	RGB15( 31,31,31 ), //4
	TEXTURE_PACK( 0, inttot16 (32 ) ), //5
	VERTEX_PACK( inttov16( 0 ), inttov16( 0 ) ), //6
	VERTEX_PACK( floattov16( 0.0 ), 0 ), //7

	FIFO_COMMAND_PACK( FIFO_COLOR, FIFO_TEX_COORD, FIFO_VERTEX16, FIFO_NOP ), //8

	RGB15( 31,31,31 ), //9
	TEXTURE_PACK( inttot16( 32 ), inttot16( 32 ) ), //10
	VERTEX_PACK( inttov16( 1 ), inttov16( 0 ) ), //11
	VERTEX_PACK( floattov16( 0.0 ), 0 ), //12

	FIFO_COMMAND_PACK( FIFO_COLOR, FIFO_TEX_COORD, FIFO_VERTEX16, FIFO_NOP ), //13

	RGB15( 31,31,31 ), //14
	TEXTURE_PACK( inttot16( 32 ), 0 ), //15
	VERTEX_PACK( inttov16( 1 ), inttov16( 1 ) ), //16
	VERTEX_PACK( floattov16( 0.0 ), 0 ), //17

	FIFO_COMMAND_PACK( FIFO_COLOR, FIFO_TEX_COORD, FIFO_VERTEX16, FIFO_END ), //18

	RGB15( 31,31,31 ), //19
	TEXTURE_PACK( 0, 0 ), //20
	VERTEX_PACK( inttov16( 0 ), inttov16( 1 ) ), //21
	VERTEX_PACK( floattov16( 0.0 ), 0 ), //22
};

#endif /* DEFAULT_DLIST_H */