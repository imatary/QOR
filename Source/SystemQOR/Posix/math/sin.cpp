
/* @(#)k_sin.c 5.1 93/09/24 */
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
/* __kernel_sin( x, y, iy)
 * kernel sin function on [-pi/4, pi/4], pi/4 ~ 0.7854
 * Input x is assumed to be bounded by ~pi/4 in magnitude.
 * Input y is the tail of x.
 * Input iy indicates whether y is 0. (if iy=0, y assume to be 0). 
 *
 * Algorithm
 *	1. Since sin(-x) = -sin(x), we need only to consider positive x. 
 *	2. if x < 2^-27 (hx<0x3e400000 0), return x with inexact if x!=0.
 *	3. sin(x) is approximated by a polynomial of degree 13 on
 *	   [0,pi/4]
 *		  	         3            13
 *	   	sin(x) ~ x + S1*x + ... + S6*x
 *	   where
 *	
 * 	|sin(x)         2     4     6     8     10     12  |     -58
 * 	|----- - (1+S1*x +S2*x +S3*x +S4*x +S5*x  +S6*x   )| <= 2
 * 	|  x 					           | 
 * 
 *	4. sin(x+y) = sin(x) + sin'(x')*y
 *		    ~ sin(x) + (1-x*x/2)*y
 *	   For better accuracy, let 
 *		     3      2      2      2      2
 *		r = x *(S2+x *(S3+x *(S4+x *(S5+x *S6))))
 *	   then                   3    2
 *		sin(x) = x + (S1*x + (x *(r-y/2)+y))
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::sinf( float x )
	{
		float y[ 2 ], z = 0.0;
		Cmp_signed__int32 n, ix;

		get_float_word( ix, x );

		// |x| ~< pi/4
		ix &= 0x7fffffff;
		if( ix <= 0x3f490fd8 )
		{
			return __kernel_sinf( x, z, 0 );
		}// sin(Inf or NaN) is NaN
		else if( !uword_isfinite( ix ) )
		{
			return x - x;
		}// argument reduction needed
		else 
		{
			n = __ieee754_rem_pio2f( x, y );
			switch( n & 3 ) 
			{
			case 0: return  __kernel_sinf( y[ 0 ], y[ 1 ], 1 );
			case 1: return  __kernel_cosf( y[ 0 ], y[ 1 ] );
			case 2: return -__kernel_sinf( y[ 0 ], y[ 1 ], 1 );
			default:
			return -__kernel_cosf( y[ 0 ], y[ 1 ] );
			}
		}
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	double Cmath::sin( double x )
	{
		return (double)sinf( (float)x );
	}

#else

	//------------------------------------------------------------------------------
	double Cmath::sin( double x )
	{
		double y[ 2 ], z = 0.0;
		Cmp_signed__int32 n, ix;

		// High word of x.
		get_high_word( ix, x );

		// |x| ~< pi/4
		ix &= 0x7fffffff;
		if( ix <= 0x3fe921fb )
		{
			return __kernel_sin( x, z, 0 );
		}// sin(Inf or NaN) is NaN
		else if ( ix >= 0x7ff00000 )
		{
			return x - x;
		}// argument reduction needed
		else 
		{
			n = __ieee754_rem_pio2( x, y );
			switch( n & 3 ) 
			{
			case 0: return  __kernel_sin( y[ 0 ], y[ 1 ], 1 );
			case 1: return  __kernel_cos( y[ 0 ], y[ 1 ] );
			case 2: return -__kernel_sin( y[ 0 ], y[ 1 ], 1 );
			default:
			return -__kernel_cos( y[ 0 ], y[ 1 ] );
			}
		}
	}

	//------------------------------------------------------------------------------
	double Cmath::__kernel_sin( double x, double y, int iy )
	{
		static const double half =  5.00000000000000000000e-01; // 0x3FE00000, 0x00000000
		static const double S1  = -1.66666666666666324348e-01; // 0xBFC55555, 0x55555549
		static const double S2  =  8.33333333332248946124e-03; // 0x3F811111, 0x1110F8A6
		static const double S3  = -1.98412698298579493134e-04; // 0xBF2A01A0, 0x19C161D5
		static const double S4  =  2.75573137070700676789e-06; // 0x3EC71DE3, 0x57B1FE7D
		static const double S5  = -2.50507602534068634195e-08; // 0xBE5AE5E6, 0x8A2B9CEB
		static const double S6  =  1.58969099521155010221e-10; // 0x3DE5D93A, 0x5ACFD57C

		double z, r, v;
		Cmp_signed__int32 ix;
		get_high_word( ix, x );
		ix &= 0x7fffffff; // high word of x
		if( ix < 0x3e400000 ) // |x| < 2**-27
		{
			if( (int)x == 0 )
			{
				return x;
			}
		} // generate inexact
		z = x * x;
		v = z * x;
		r = S2 + z * ( S3 + z * ( S4 + z * ( S5 + z * S6 ) ) );

		if( iy == 0 )
		{
			return x + v * ( S1 + z * r );
		}
		else
		{
			return x - ( ( z * ( half * y - v * r ) - y ) - v * S1 );
		}
	}

#endif//defined(_DOUBLE_IS_32BITS)

	//------------------------------------------------------------------------------
	float Cmath::__kernel_sinf( float x, float y, int iy )
	{
		static const float half =  5.0000000000e-01;// 0x3f000000
		static const float S1  = -1.6666667163e-01; // 0xbe2aaaab
		static const float S2  =  8.3333337680e-03; // 0x3c088889
		static const float S3  = -1.9841270114e-04; // 0xb9500d01
		static const float S4  =  2.7557314297e-06; // 0x3638ef1b
		static const float S5  = -2.5050759689e-08; // 0xb2d72f34
		static const float S6  =  1.5896910177e-10; // 0x2f2ec9d3

		float z, r, v;
		Cmp_signed__int32 ix;
		get_float_word( ix, x );
		ix &= 0x7fffffff; // high word of x
		if( ix < 0x32000000 ) // |x| < 2**-27
		{
			if( (int)x == 0 )
			{
				return x;
			}
		}// generate inexact
		z = x * x;
		v = z * x;
		r = S2 + z * ( S3 + z * ( S4 + z * ( S5 + z * S6 ) ) );
		if( iy == 0 )
		{
			return x + v * ( S1 + z * r );
		}
		else
		{
			return x - ( ( z * ( half * y - v * r ) - y ) - v * S1 );
		}
	}

};//namespace nsBaseCRT
