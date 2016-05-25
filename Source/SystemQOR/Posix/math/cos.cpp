
/* @(#)k_cos.c 5.1 93/09/24 */
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
 * __kernel_cos( x,  y )
 * kernel cos function on [-pi/4, pi/4], pi/4 ~ 0.785398164
 * Input x is assumed to be bounded by ~pi/4 in magnitude.
 * Input y is the tail of x. 
 *
 * Algorithm
 *	1. Since cos(-x) = cos(x), we need only to consider positive x.
 *	2. if x < 2^-27 (hx<0x3e400000 0), return 1 with inexact if x!=0.
 *	3. cos(x) is approximated by a polynomial of degree 14 on
 *	   [0,pi/4]
 *		  	                 4            14
 *	   	cos(x) ~ 1 - x*x/2 + C1*x + ... + C6*x
 *	   where the remez error is
 *	
 * 	|              2     4     6     8     10    12     14 |     -58
 * 	|cos(x)-(1-.5*x +C1*x +C2*x +C3*x +C4*x +C5*x  +C6*x  )| <= 2
 * 	|    					               | 
 * 
 * 	               4     6     8     10    12     14 
 *	4. let r = C1*x +C2*x +C3*x +C4*x +C5*x  +C6*x  , then
 *	       cos(x) = 1 - x*x/2 + r
 *	   since cos(x+y) ~ cos(x) - sin(x)*y 
 *			  ~ cos(x) - x*y,
 *	   a correction term is necessary in cos(x) and hence
 *		cos(x+y) = 1 - (x*x/2 - (r - x*y))
 *	   For better accuracy when x > 0.3, let qx = |x|/4 with
 *	   the last 32 bits mask off, and if x > 0.78125, let qx = 0.28125.
 *	   Then
 *		cos(x+y) = (1-qx) - ((x*x/2-qx) - (r-x*y)).
 *	   Note that 1-qx and (x*x/2-qx) is EXACT here, and the
 *	   magnitude of the latter is at least a quarter of x*x/2,
 *	   thus, reducing the rounding error in the subtraction.
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------	
	float Cmath::cosf( float x )
	{
		static const float one = 1.0;
		float y[ 2 ], z = 0.0;
		Cmp_signed__int32 n, ix;

		get_float_word( ix, x );

		// |x| ~< pi/4 
		ix &= 0x7fffffff;
		if( ix <= 0x3f490fd8 )
		{
			return __kernel_cosf( x, z );
		}// cos(Inf or NaN) is NaN
		else if( !uword_isfinite( ix ) )
		{
			return x-x;
		}// argument reduction needed 
		else 
		{
			n = __ieee754_rem_pio2f( x, y );
			switch( n & 3 ) 
			{
			case 0: return  __kernel_cosf( y[ 0 ], y[ 1 ] );
			case 1: return -__kernel_sinf( y[ 0 ], y[ 1 ], 1 );
			case 2: return -__kernel_cosf( y[ 0 ], y[ 1 ] );
			default:
				return __kernel_sinf( y[ 0 ], y[ 1 ], 1 );
			}
		}
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	double Cmath::cos( double x )
	{
		return (double)cosf( (float)x );
	}

#else

	//------------------------------------------------------------------------------
	double Cmath::cos( double x )
	{
		double y[ 2 ], z = 0.0;
		Cmp_signed__int32 n, ix;

		// High word of x.
		get_high_word( ix, x );

		// |x| ~< pi/4
		ix &= 0x7fffffff;
		if( ix <= 0x3fe921fb ) 
		{
			return __kernel_cos( x, z );
		}// cos(Inf or NaN) is NaN
		else if ( ix >= 0x7ff00000 )
		{
			return x - x;
		}// argument reduction needed
		else 
		{
			n = __ieee754_rem_pio2( x, y );
			switch( n & 3 ) 
			{
			case 0: return __kernel_cos( y[ 0 ], y[ 1 ] );
			case 1: return -__kernel_sin( y[ 0 ], y[ 1 ], 1);
			case 2: return -__kernel_cos( y[ 0 ], y[ 1 ] );
			default:
			return __kernel_sin( y[ 0 ], y[ 1 ], 1 );
			}
		}
	}

	//------------------------------------------------------------------------------
	double Cmath::__kernel_cos( double x, double y )
	{
		static const double one =  1.00000000000000000000e+00; // 0x3FF00000, 0x00000000
		static const double C1  =  4.16666666666666019037e-02; // 0x3FA55555, 0x5555554C
		static const double C2  = -1.38888888888741095749e-03; // 0xBF56C16C, 0x16C15177
		static const double C3  =  2.48015872894767294178e-05; // 0x3EFA01A0, 0x19CB1590
		static const double C4  = -2.75573143513906633035e-07; // 0xBE927E4F, 0x809C52AD
		static const double C5  =  2.08757232129817482790e-09; // 0x3E21EE9E, 0xBDB4B1C4
		static const double C6  = -1.13596475577881948265e-11; // 0xBDA8FAE9, 0xBE8838D4

		double a, hz, z, r, qx;
		Cmp_signed__int32 ix;
		get_high_word( ix, x );
		ix &= 0x7fffffff; // ix = |x|'s high word
		if( ix < 0x3e400000 ) 
		{
			// if x < 2**27
			if( ( (int)x ) == 0 )
			{
				return one;		// generate inexact
			}
		}

		z = x * x;
		r = z * ( C1 + z * ( C2 + z * ( C3 + z * ( C4 + z * ( C5 + z * C6 ) ) ) ) );
		if( ix < 0x3FD33333 )
		{
			// if |x| < 0.3
			return one - ( 0.5 * z - ( z * r - x * y ) );
		}
		else 
		{
			if( ix > 0x3fe90000 ) 
			{	
				// x > 0.78125
				qx = 0.28125;
			} 
			else 
			{
				insert_words( qx, ix - 0x00200000, 0 ); // x/4
			}
			hz = 0.5 * z - qx;
			a = one - qx;
			return a - ( hz - ( z * r - x * y ) );
		}
	}

#endif//defined(_DOUBLE_IS_32BITS)

	//------------------------------------------------------------------------------
	float Cmath::__kernel_cosf( float x, float y )
	{
		static const float one =  1.0000000000e+00; // 0x3f800000
		static const float C1  =  4.1666667908e-02; // 0x3d2aaaab
		static const float C2  = -1.3888889225e-03; // 0xbab60b61
		static const float C3  =  2.4801587642e-05; // 0x37d00d01
		static const float C4  = -2.7557314297e-07; // 0xb493f27c
		static const float C5  =  2.0875723372e-09; // 0x310f74f6
		static const float C6  = -1.1359647598e-11; // 0xad47d74e

		float a, hz, z, r, qx;
		Cmp_signed__int32 ix;
		get_float_word( ix, x );
		ix &= 0x7fffffff; // ix = |x|'s high word
		if( ix < 0x32000000 ) 
		{
			// if x < 2**27
			if( ( (int)x ) == 0 )
			{
				return one; // generate inexact
			}
		}
		z = x * x;
		r = z * ( C1 + z * ( C2 + z * ( C3 + z * ( C4 + z * ( C5 + z * C6 ) ) ) ) );
		if( ix < 0x3e99999a ) // if |x| < 0.3
		{
			return one - ( (float)0.5 * z - ( z * r - x * y ) );
		}
		else 
		{
			if( ix > 0x3f480000 ) 
			{
				// x > 0.78125
				qx = (float)0.28125;
			} 
			else 
			{
				set_float_word( qx, ix - 0x01000000 ); // x/4
			}
			hz = (float)0.5 * z - qx;
			a  = one - qx;
			return a - ( hz - ( z * r - x * y ) );
		}
	}

};//namespace nsBaseCRT
