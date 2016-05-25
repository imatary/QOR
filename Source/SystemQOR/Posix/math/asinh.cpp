
/* @(#)s_asinh.c 5.1 93/09/24 */
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
	<<asinh>>, <<asinhf>>---inverse hyperbolic sine 

INDEX
	asinh
INDEX
	asinhf

ANSI_SYNOPSIS
	#include <math.h>
	double asinh(double <[x]>);
	float asinhf(float <[x]>);

TRAD_SYNOPSIS
	#include <math.h>
	double asinh(<[x]>)
	double <[x]>;

	float asinhf(<[x]>)
	float <[x]>;

DESCRIPTION
<<asinh>> calculates the inverse hyperbolic sine of <[x]>.
<<asinh>> is defined as 
@ifnottex
. sgn(<[x]>) * log(abs(<[x]>) + sqrt(1+<[x]>*<[x]>))
@end ifnottex
@tex
$$sign(x) \times ln\Bigl(|x| + \sqrt{1+x^2}\Bigr)$$
@end tex

<<asinhf>> is identical, other than taking and returning floats.

RETURNS
<<asinh>> and <<asinhf>> return the calculated value.

PORTABILITY
Neither <<asinh>> nor <<asinhf>> are ANSI C.

*/

/* asinh(x)
 * Method :
 *	Based on 
 *		asinh(x) = sign(x) * log [ |x| + sqrt(x*x+1) ]
 *	we have
 *	asinh(x) := x  if  1+x*x=1,
 *		 := sign(x)*(log(x)+ln2)) for large |x|, else
 *		 := sign(x)*log(2|x|+1/(|x|+sqrt(x*x+1))) if|x|>2, else
 *		 := sign(x)*log1p(|x| + x^2/(1 + sqrt(1+x^2)))  
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::asinhf( float x )
	{	
		
		static const float one =  1.0000000000e+00; // 0x3F800000
		static const float ln2 =  6.9314718246e-01; // 0x3f317218
		static const float huge=  1.0000000000e+30; 

		float t, w;
		Cmp_signed__int32 hx, ix;
		get_float_word( hx, x );
		ix = hx & 0x7fffffff;
		if( !uword_isfinite( ix ) )
		{
			return x + x; // x is inf or NaN
		}

		if( ix < 0x31800000 ) 
		{	
			// |x|<2**-28
			if( huge + x > one )
			{
				return x; // return x inexact except 0
			}
		} 

		if( ix > 0x4d800000 ) 
		{	
			// |x| > 2**28
			w = __ieee754_logf( fabsf( x ) ) + ln2;
		} 
		else if( ix > 0x40000000 ) 
		{	
			// 2**28 > |x| > 2.0
			t = fabsf( x );
			w = __ieee754_logf( (float)2.0 * t + one / ( __ieee754_sqrtf( x * x + one ) + t ) );
		} 
		else 
		{
			// 2.0 > |x| > 2**-28
			t = x * x;
			w = log1pf( fabsf( x ) + t / ( one + __ieee754_sqrtf( one + t ) ) );
		}

		if( hx > 0 )
		{
			return w;
		}
		else
		{
			return -w;
		}
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	double Cmath::asinh( double x )
	{
		return (double)asinhf( (float)x );
	}

#else
	
	//------------------------------------------------------------------------------
	double Cmath::asinh( double x )
	{
		static const double one =  1.00000000000000000000e+00; // 0x3FF00000, 0x00000000
		static const double ln2 =  6.93147180559945286227e-01; // 0x3FE62E42, 0xFEFA39EF
		static const double huge=  1.00000000000000000000e+300; 
		double t,w;
		Cmp_signed__int32 hx, ix;
		get_high_word( hx, x );
		ix = hx & 0x7fffffff;
		if( ix >= 0x7ff00000 )
		{
			return x + x; // x is inf or NaN
		}

		if( ix < 0x3e300000 ) 
		{	
			// |x|<2**-28
			if( huge + x > one )
			{
				return x;	// return x inexact except 0
			}
		} 

		if( ix > 0x41b00000 ) 
		{	
			// |x| > 2**28
			w = __ieee754_log( fabs( x ) ) + ln2;
		} 
		else if( ix > 0x40000000 ) 
		{	
			// 2**28 > |x| > 2.0
			t = fabs( x );
			w = __ieee754_log( 2.0 * t + one / ( __ieee754_sqrt( x * x + one ) + t ) );
		} 
		else 
		{
			// 2.0 > |x| > 2**-28
			t = x * x;
			w =log1p( fabs( x ) + t / ( one + __ieee754_sqrt( one + t ) ) );
		}

		if( hx > 0)
		{
			return w;
		}
		else
		{
			return -w;
		}
	}

#endif /* _DOUBLE_IS_32BITS */

};//namespace nsBaseCRT
