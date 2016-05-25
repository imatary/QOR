
/* @(#)s_finite.c 5.1 93/09/24 */
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
 * finite(x) returns 1 is x is finite, else 0;
 * no branching!
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	int Cmath::finitef( float x )
	{
		Cmp_signed__int32 ix;
		get_float_word( ix, x );
		ix &= 0x7fffffff;
		return ( uword_isfinite( ix ) );
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	int Cmath::finite( double x )
	{
		return finitef((float) x);
	}

#else

	//------------------------------------------------------------------------------
	int Cmath::finite( double x )
	{
		Cmp_signed__int32 hx;
		get_high_word( hx, x );
		return  (int)( (Cmp_unsigned__int32)( ( hx & 0x7fffffff ) - 0x7ff00000 ) >> 31 );
	}

#endif /* _DOUBLE_IS_32BITS */

};//namespace nsBaseCRT
