
/* @(#)s_fabs.c 5.1 93/09/24 */
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
// Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
/*
FUNCTION
       <<fabs>>, <<fabsf>>---absolute value (magnitude)
INDEX
	fabs
INDEX
	fabsf

ANSI_SYNOPSIS
	#include <math.h>
       double fabs(double <[x]>);
       float fabsf(float <[x]>);

TRAD_SYNOPSIS
	#include <math.h>
       double fabs(<[x]>) 
       double <[x]>;

       float fabsf(<[x]>)
       float <[x]>;

DESCRIPTION
<<fabs>> and <<fabsf>> calculate 
@tex
$|x|$, 
@end tex
the absolute value (magnitude) of the argument <[x]>, by direct
manipulation of the bit representation of <[x]>.

RETURNS
The calculated value is returned.  No errors are detected.

PORTABILITY
<<fabs>> is ANSI.
<<fabsf>> is an extension.

*/

/*
 * fabs(x) returns the absolute value of x.
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::fabsf( float x )
	{
		Cmp_unsigned__int32 ix;
		get_float_word( ix, x );
		set_float_word( x, ix & 0x7fffffff );
		return x;
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	double Cmath::fabs( double x )
	{
		return (double)fabsf( (float)x );
	}

#else

	//------------------------------------------------------------------------------
	double Cmath::fabs( double x )
	{
		Cmp_unsigned__int32 high;
		get_high_word( high, x );
		set_high_word( x, high & 0x7fffffff );
		return x;
	}

#endif//_DOUBLE_IS_32BITS

};//namespace nsBaseCRT
