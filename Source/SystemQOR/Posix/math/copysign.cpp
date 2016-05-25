
/* @(#)s_copysign.c 5.1 93/09/24 */
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

/*
FUNCTION
<<copysign>>, <<copysignf>>---sign of <[y]>, magnitude of <[x]>

INDEX
	copysign
INDEX
	copysignf

ANSI_SYNOPSIS
	#include <math.h>
	double copysign (double <[x]>, double <[y]>);
	float copysignf (float <[x]>, float <[y]>);

TRAD_SYNOPSIS
	#include <math.h>
	double copysign (<[x]>, <[y]>)
	double <[x]>;
	double <[y]>;

	float copysignf (<[x]>, <[y]>)
	float <[x]>;
	float <[y]>;

DESCRIPTION
<<copysign>> constructs a number with the magnitude (absolute value)
of its first argument, <[x]>, and the sign of its second argument,
<[y]>.

<<copysignf>> does the same thing; the two functions differ only in
the type of their arguments and result.

RETURNS
<<copysign>> returns a <<double>> with the magnitude of
<[x]> and the sign of <[y]>.
<<copysignf>> returns a <<float>> with the magnitude of
<[x]> and the sign of <[y]>.

PORTABILITY
<<copysign>> is not required by either ANSI C or the System V Interface
Definition (Issue 2).

*/

/*
 * copysign(double x, double y)
 * copysign(x,y) returns a value with the magnitude of x and
 * with the sign bit of y.
 */
//Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::copysignf( float x, float y )
	{
		Cmp_unsigned__int32 ix, iy;
		get_float_word( ix, x );
		get_float_word( iy, y );
		set_float_word( x, ( ix & 0x7fffffff ) | ( iy & 0x80000000 ) );
		return x;
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	double Cmath::copysign( double x, double y )
	{
		return (double) copysignf( (float)x, (float)y );
	}

#else

	//------------------------------------------------------------------------------
	double Cmath::copysign( double x, double y )
	{
		Cmp_unsigned__int32 hx, hy;		
		get_high_word( hx, x );
		get_high_word( hy, y );
		set_high_word( x, ( hx & 0x7fffffff ) | ( hy & 0x80000000 ) );
		return x;
	}

#endif /* _DOUBLE_IS_32BITS */

};//namespace nsBaseCRT

