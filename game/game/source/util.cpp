/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: util.cpp
 * Date: 2nd of August, 2010.
 * Author(s): Christopher Berry.
 * Description: Utility source file
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

int pow( int base, int exponent ){
	int result=base;

	if( exponent == 0 )
		return 1;

	for( int i=0; i<exponent-1; i++ )
		result*=base;

	return result;
}