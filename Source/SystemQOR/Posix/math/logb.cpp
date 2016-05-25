
/* @(#)s_logb.c 5.1 93/09/24 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 */
//Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
/*
 * double logb(x)
 * IEEE 754 logb. Included to pass IEEE test suite. Not recommend.
 * Use ilogb instead.
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::logbf( float x )
	{
		Cmp_signed__int32 ix;
		get_float_word( ix, x );
		ix &= 0x7fffffff;			// high |x|
		if( uword_is_zero( ix ) )
		{
			return (float)-1.0 / fabsf( x );
		}

		if( !uword_isfinite( ix ) )
		{
			return x * x;
		}

		if( ( ix >>= 23 ) == 0 ) 	// IEEE 754 logb
		{
			return -126.0; 
		}
		else
		{
			return (float)( ix - 127 ); 
		}
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	double Cmath::logb( double x )
	{
		return (double)logbf( (float)x );
	}

#else

	//------------------------------------------------------------------------------
	double Cmath::logb( double x )
	{
		Cmp_signed__int32 lx,ix;
		extract_words( ix, lx, x );
		ix &= 0x7fffffff;			// high |x|
		if( ( ix | lx ) == 0 )
		{
			return -1.0 / fabs( x );
		}

		if( ix >= 0x7ff00000 )
		{
			return x * x;
		}

		if( ( ix >>= 20 ) == 0 ) 			// IEEE 754 logb
		{
			return -1022.0; 
		}
		else
		{
			return (double) ( ix - 1023 ); 
		}
	}

#endif /* _DOUBLE_IS_32BITS */

};//namespace nsBaseCRT
