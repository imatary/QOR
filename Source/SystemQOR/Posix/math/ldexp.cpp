
/* @(#)s_ldexp.c 5.1 93/09/24 */
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
       <<ldexp>>, <<ldexpf>>---load exponent

INDEX
	ldexp
INDEX
	ldexpf

ANSI_SYNOPSIS
       #include <math.h>
       double ldexp(double <[val]>, int <[exp]>);
       float ldexpf(float <[val]>, int <[exp]>);

TRAD_SYNOPSIS
       #include <math.h>

       double ldexp(<[val]>, <[exp]>)
              double <[val]>;
              int <[exp]>;

       float ldexpf(<[val]>, <[exp]>)
              float <[val]>;
              int <[exp]>;


DESCRIPTION
<<ldexp>> calculates the value 
@ifnottex
<[val]> times 2 to the power <[exp]>.
@end ifnottex
@tex
$val\times 2^{exp}$.
@end tex
<<ldexpf>> is identical, save that it takes and returns <<float>>
rather than <<double>> values.

RETURNS
<<ldexp>> returns the calculated value.

Underflow and overflow both set <<errno>> to <<ERANGE>>.
On underflow, <<ldexp>> and <<ldexpf>> return 0.0.
On overflow, <<ldexp>> returns plus or minus <<HUGE_VAL>>.

PORTABILITY
<<ldexp>> is ANSI. <<ldexpf>> is an extension.
              
*/   

#include <errno.h>
//#include "../CQOR/platform/Includes.h"
#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::ldexpf( float value, int exp )
	{
		if( !finitef( value ) || value == (float)0.0 )
		{
			return value;
		}
		value = scalbnf( value, exp );
		if( !finitef( value ) || value == (float)0.0 )
		{
			errno = ERANGE;
		}
		return value;
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	double Cmath::ldexp( double value, int exp )
	{
		return (double)ldexpf( (float)value, exp );
	}

#else

	//------------------------------------------------------------------------------
	double Cmath::ldexp( double value, int exp )
	{
		if( !finite( value ) || value == 0.0 )
		{
			return value;
		}

		value = scalbn( value, exp );
		if( !finite( value ) || value == 0.0 )
		{
			errno = ERANGE;
		}
		return value;
	}
#endif//_DOUBLE_IS_32BITS
};//namespace nsBaseCRT
