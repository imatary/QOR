
/* @(#)s_cbrt.c 5.1 93/09/24 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 *
 */

//Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.

/*
FUNCTION
	<<cbrt>>, <<cbrtf>>---cube root

INDEX
	cbrt
INDEX
	cbrtf

ANSI_SYNOPSIS
	#include <math.h>
	double cbrt(double <[x]>);
	float  cbrtf(float <[x]>);

TRAD_SYNOPSIS
	#include <math.h>
	double cbrt(<[x]>);
	float  cbrtf(<[x]>);

DESCRIPTION
	<<cbrt>> computes the cube root of the argument.

RETURNS
	The cube root is returned. 

PORTABILITY
	<<cbrt>> is in System V release 4.  <<cbrtf>> is an extension.
*/

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	// cbrtf(x)
	// Return cube root of x
	float Cmath::cbrtf( float x ) 
	{	
		static const Cmp_unsigned__int32 B1 = 709958130; // B1 = (84+2/3-0.03306235651)*2**23
		static const Cmp_unsigned__int32 B2 = 642849266; // B2 = (76+2/3-0.03306235651)*2**23

		static const float C =  5.4285717010e-01; // 19/35     = 0x3f0af8b0
		static const float D = -7.0530611277e-01; // -864/1225 = 0xbf348ef1
		static const float E =  1.4142856598e+00; // 99/70     = 0x3fb50750
		static const float F =  1.6071428061e+00; // 45/28     = 0x3fcdb6db
		static const float G =  3.5714286566e-01; // 5/14      = 0x3eb6db6e

		Cmp_signed__int32 hx;
		float r, s, t;
		Cmp_unsigned__int32 sign;
		Cmp_unsigned__int32 high;

		get_float_word( hx, x );
		sign = hx & 0x80000000; // sign= sign(x)
		hx ^= sign;
		if( !uword_isfinite( hx ) )
		{
			return( x + x ); // cbrt(NaN,INF) is itself
		}

		if( uword_is_zero( hx ) )
		{
			return( x ); // cbrt(0) is itself
		}

		set_float_word( x, hx ); // x <- |x|
		// rough cbrt to 5 bits
		if( uword_is_subnormal( hx ) ) 		// subnormal number
		{
			set_float_word( t, 0x4b800000 ); // set t= 2**24
			t *= x;
			get_float_word( high, t );
			set_float_word( t, high / 3 + B2 );
		}
		else
		{
			set_float_word( t, hx / 3 + B1 );
		}

		// new cbrt to 23 bits
		r = t * t / x;
		s = C + r * t;
		t *= G + F / ( s + E + D / s );	

		// retore the sign bit
		get_float_word( high, t );
		set_float_word( t, high | sign );
		return t;
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	double Cmath::cbrt( double x )
	{
		return (double) cbrtf( (float) x );
	}

#else

	//------------------------------------------------------------------------------
	// cbrt(x); Return cube root of x
	double Cmath::cbrt( double x ) 
	{
		static const Cmp_unsigned__int32 B1 = 715094163; // B1 = (682-0.03306235651)*2**20
		static const Cmp_unsigned__int32 B2 = 696219795; // B2 = (664-0.03306235651)*2**20

		static const double C =  5.42857142857142815906e-01; // 19/35     = 0x3FE15F15, 0xF15F15F1
		static const double D = -7.05306122448979611050e-01; // -864/1225 = 0xBFE691DE, 0x2532C834
		static const double E =  1.41428571428571436819e+00; // 99/70     = 0x3FF6A0EA, 0x0EA0EA0F
		static const double F =  1.60714285714285720630e+00; // 45/28     = 0x3FF9B6DB, 0x6DB6DB6E
		static const double G =  3.57142857142857150787e-01; // 5/14      = 0x3FD6DB6D, 0xB6DB6DB7

		Cmp_signed__int32	hx;
		double r, s, t = 0.0, w;
		Cmp_unsigned__int32 sign;
		Cmp_unsigned__int32 high, low;

		get_high_word( hx, x );
		sign = hx & 0x80000000; 		// sign= sign(x)
		hx ^= sign;
		if( hx >= 0x7ff00000 )
		{
			return( x + x ); // cbrt(NaN,INF) is itself
		}

		get_low_word( low, x );
		if( ( hx | low ) == 0 ) 
		{
			return( x );		// cbrt(0) is itself
		}

		set_high_word( x, hx );	// x <- |x|

		// rough cbrt to 5 bits
		if( hx < 0x00100000 ) 		// subnormal number
		{
			set_high_word( t, 0x43500000 );	// set t= 2**54
			t *= x;
			get_high_word( high, t );
			set_high_word( t, high / 3 + B2 );
		}
		else
		{
			set_high_word( t, hx / 3 + B1 );
		}

		// new cbrt to 23 bits, may be implemented in single precision
		r = t * t / x;
		s = C + r * t;
		t *= G + F / ( s + E + D / s );	

		// chopped to 20 bits and make it larger than cbrt(x)
		get_high_word( high, t );
		insert_words( t, high + 0x00000001, 0 );

		// one step newton iteration to 53 bits with error less than 0.667 ulps
		s = t * t;		// t*t is exact
		r = x / s;
		w = t + t;
		r = ( r - t ) / ( w + r );	// r-s is exact
		t = t + t * r;

		// retore the sign bit		
		get_high_word( high, t );
		set_high_word( t, high | sign );
		return t;
	}

#endif//_DOUBLE_IS_32BITS

};//namespace nsBaseCRT


