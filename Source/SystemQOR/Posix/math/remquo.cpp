/* Copyright (C) 2002 by  Red Hat, Incorporated. All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software
 * is freely granted, provided that this notice is preserved.
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::remquof( float x, float y, int* quo ) // wrapper remquof
	{
		int signx, signy, signres;
		int wx;
		int wy;
		float x_over_y;

		get_float_word( wx, x );
		get_float_word( wy, y );

		signx = ( wx & 0x80000000 ) >> 31;
		signy = ( wy & 0x80000000 ) >> 31;

		signres = ( signx ^ signy ) ? -1 : 1;

		x_over_y = fabsf( x / y );

		*quo = signres * ( lrintf( x_over_y ) & 0x7f );

		return remainderf( x, y );
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	double Cmath::remquo( double x, double y, int* quo ) // wrapper remquof 
	{
		return (double)remquof( (float)x, (float)y, quo );
	}

#else

	//------------------------------------------------------------------------------
	double Cmath::remquo( double x, double y, int* quo )	// wrapper remquo
	{
		int signx, signy, signres;
		int mswx;
		int mswy;
		double x_over_y;

		get_high_word( mswx, x );
		get_high_word( mswy, y );

		signx = ( mswx & 0x80000000 ) >> 31;
		signy = ( mswy & 0x80000000 ) >> 31;

		signres = ( signx ^ signy ) ? -1 : 1;

		x_over_y = fabs( x / y );

		*quo = signres * ( lrint( x_over_y ) & 0x7f );

		return remainder( x, y );
	}

	#endif /* defined(_DOUBLE_IS_32BITS) */

};//namespace nsBaseCRT
