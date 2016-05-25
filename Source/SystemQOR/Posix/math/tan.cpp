
/* @(#)k_tan.c 5.1 93/09/24 */
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
/* __kernel_tan( x, y, k )
 * kernel tan function on [-pi/4, pi/4], pi/4 ~ 0.7854
 * Input x is assumed to be bounded by ~pi/4 in magnitude.
 * Input y is the tail of x.
 * Input k indicates whether tan (if k=1) or 
 * -1/tan (if k= -1) is returned.
 *
 * Algorithm
 *	1. Since tan(-x) = -tan(x), we need only to consider positive x. 
 *	2. if x < 2^-28 (hx<0x3e300000 0), return x with inexact if x!=0.
 *	3. tan(x) is approximated by a odd polynomial of degree 27 on
 *	   [0,0.67434]
 *		  	         3             27
 *	   	tan(x) ~ x + T1*x + ... + T13*x
 *	   where
 *	
 * 	        |tan(x)         2     4            26   |     -59.2
 * 	        |----- - (1+T1*x +T2*x +.... +T13*x    )| <= 2
 * 	        |  x 					| 
 * 
 *	   Note: tan(x+y) = tan(x) + tan'(x)*y
 *		          ~ tan(x) + (1+x*x)*y
 *	   Therefore, for better accuracy in computing tan(x+y), let 
 *		     3      2      2       2       2
 *		r = x *(T2+x *(T3+x *(...+x *(T12+x *T13))))
 *	   then
 *		 		    3    2
 *		tan(x+y) = x + (T1*x + (x *(r+y)+y))
 *
 *      4. For x in [0.67434,pi/4],  let y = pi/4 - x, then
 *		tan(x) = tan(pi/4-y) = (1-tan(y))/(1+tan(y))
 *		       = 1 - 2*(tan(y) - (tan(y)^2)/(1+tan(y)))
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::tanf( float x )
	{
		float y[ 2 ], z = 0.0;
		Cmp_signed__int32 n, ix;

		get_float_word( ix, x );

		// |x| ~< pi/4
		ix &= 0x7fffffff;
		if( ix <= 0x3f490fda )
		{
			return __kernel_tanf( x, z, 1 );
		}// tan(Inf or NaN) is NaN
		else if ( !uword_isfinite( ix ) ) 
		{
			return x - x; // NaN
		}// argument reduction needed
		else 
		{
			n = __ieee754_rem_pio2f( x, y );
			return __kernel_tanf( y[ 0 ], y[ 1 ], 1 - ( ( n & 1 ) << 1 ) ); //   1 -- n even -1 -- n odd
		}
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	double Cmath::tan( double x )
	{
		return (double)tanf( (float)x );
	}

#else

	//------------------------------------------------------------------------------
	double Cmath::tan( double x )
	{
		double y[ 2 ], z = 0.0;
		Cmp_signed__int32 n, ix;

		// High word of x.
		get_high_word( ix, x );

		// |x| ~< pi/4
		ix &= 0x7fffffff;
		if( ix <= 0x3fe921fb )
		{
			return __kernel_tan( x, z, 1 );
		}// tan(Inf or NaN) is NaN
		else if ( ix >= 0x7ff00000 )
		{
			return x - x; // NaN
		}// argument reduction needed
		else 
		{
			n = __ieee754_rem_pio2( x, y );
			return __kernel_tan( y[ 0 ], y[ 1 ], 1 - ( ( n & 1 ) << 1 ) ); // 1 -- n even -1 -- n odd
		}
	}

	//------------------------------------------------------------------------------
	double Cmath::__kernel_tan( double x, double y, int iy )
	{
		static const double one   =  1.00000000000000000000e+00; // 0x3FF00000, 0x00000000
		static const double pio4  =  7.85398163397448278999e-01; // 0x3FE921FB, 0x54442D18
		static const double pio4lo=  3.06161699786838301793e-17; // 0x3C81A626, 0x33145C07
		static const double T[] =  
		{
			3.33333333333334091986e-01, // 0x3FD55555, 0x55555563
			1.33333333333201242699e-01, // 0x3FC11111, 0x1110FE7A
			5.39682539762260521377e-02, // 0x3FABA1BA, 0x1BB341FE
			2.18694882948595424599e-02, // 0x3F9664F4, 0x8406D637
			8.86323982359930005737e-03, // 0x3F8226E3, 0xE96E8493
			3.59207910759131235356e-03, // 0x3F6D6D22, 0xC9560328
			1.45620945432529025516e-03, // 0x3F57DBC8, 0xFEE08315
			5.88041240820264096874e-04, // 0x3F4344D8, 0xF2F26501
			2.46463134818469906812e-04, // 0x3F3026F7, 0x1A8D1068
			7.81794442939557092300e-05, // 0x3F147E88, 0xA03792A6
			7.14072491382608190305e-05, // 0x3F12B80F, 0x32F0A7E9
			-1.85586374855275456654e-05,// 0xBEF375CB, 0xDB605373
			2.59073051863633712884e-05, // 0x3EFB2A70, 0x74BF7AD4
		};

		double z, r, v, w, s;
		Cmp_signed__int32 ix, hx;
		get_high_word( hx, x );
		ix = hx & 0x7fffffff; // high word of |x|
		if( ix < 0x3e300000 ) // x < 2**-28
		{
			if( (int) x == 0 ) 
			{
				// generate inexact
				Cmp_unsigned__int32 low;
				get_low_word( low, x );
				if( ( ( ix | low ) | ( iy + 1 ) ) == 0 )
				{
					return one / fabs( x );
				}
				else 
				{
					return ( iy == 1 ) ? x : -one / x;
				}
			}
		}

		if( ix >= 0x3FE59428 ) 
		{ 
			// |x|>=0.6744
			if( hx < 0 ) 
			{
				x = -x;
				y = -y;
			}
			z = pio4 - x;
			w = pio4lo - y;
			x = z + w;
			y = 0.0;
		}
		z = x * x;
		w = z * z;
		/* Break x^5*(T[1]+x^2*T[2]+...) into
		*	  x^5(T[1]+x^4*T[3]+...+x^20*T[11]) +
		*	  x^5(x^2*(T[2]+x^4*T[4]+...+x^22*[T12]))
		*/
		r = T[ 1 ] + w * ( T[ 3 ] + w * ( T[ 5 ] + w * ( T[ 7 ] + w * ( T[ 9 ] + w * T[ 11 ] ) ) ) );
		v = z * ( T[ 2 ] + w * ( T[ 4 ] + w * ( T[ 6 ] + w * ( T[ 8 ] + w * ( T[ 10 ] + w * T[ 12 ] ) ) ) ) );
		s = z * x;
		r = y + z * ( s * ( r + v ) + y );
		r += T[ 0 ] * s;
		w = x + r;
		if( ix >= 0x3FE59428 ) 
		{
			v = (double)iy;
			return (double)( 1 - ( ( hx >> 30 ) & 2 ) ) * ( v - 2.0 * ( x - ( w * w / ( w + v ) - r ) ) );
		}

		if( iy == 1 )
		{
			return w;
		}
		else 
		{
			// if allow error up to 2 ulp, simply return -1.0/(x+r) here compute -1.0/(x+r) accurately
			double a, t;
			z = w;
			set_low_word( z, 0 );
			v = r - ( z - x ); // z + v = r + x
			t = a = -1.0 / w; // a = -1.0 / w
			set_low_word( t, 0 );
			s  = 1.0 + t * z;
			return t + a * ( s + t * v );
		}
	}

#endif//defined(_DOUBLE_IS_32BITS)

	//------------------------------------------------------------------------------
	float Cmath::__kernel_tanf( float x, float y, int iy )
	{
		static const float one   =  1.0000000000e+00; // 0x3f800000
		static const float pio4  =  static_cast< float >( 7.8539812565e-01 ); // 0x3f490fda
		static const float pio4lo=  static_cast< float >( 3.7748947079e-08 ); // 0x33222168
		static const float T[] =  
		{
			static_cast< float >( 3.3333334327e-01 ), // 0x3eaaaaab
			static_cast< float >( 1.3333334029e-01 ), // 0x3e088889
			static_cast< float >( 5.3968254477e-02 ), // 0x3d5d0dd1
			static_cast< float >( 2.1869488060e-02 ), // 0x3cb327a4
			static_cast< float >( 8.8632395491e-03 ), // 0x3c11371f
			static_cast< float >( 3.5920790397e-03 ), // 0x3b6b6916
			static_cast< float >( 1.4562094584e-03 ), // 0x3abede48
			static_cast< float >( 5.8804126456e-04 ), // 0x3a1a26c8
			static_cast< float >( 2.4646313977e-04 ), // 0x398137b9
			static_cast< float >( 7.8179444245e-05 ), // 0x38a3f445
			static_cast< float >( 7.1407252108e-05 ), // 0x3895c07a
			static_cast< float >( -1.8558637748e-05 ),// 0xb79bae5f
			static_cast< float >( 2.5907305826e-05 ), // 0x37d95384
		};

		float z, r, v, w, s;
		Cmp_signed__int32 ix, hx;
		get_float_word( hx, x );
		ix = hx & 0x7fffffff; // high word of |x|
		if( ix < 0x31800000 ) // x < 2**-28
		{
			if( (int)x == 0 ) 
			{
				// generate inexact
				if( ( ix | ( iy + 1 ) ) == 0 )
				{
					return one / fabsf( x );
				}
				else 
				{
					return ( iy == 1 ) ? x : -one / x;
				}
			}
		}

		if( ix >= 0x3f2ca140 ) 
		{
			// |x|>=0.6744
			if( hx < 0 ) 
			{
				x = -x;
				y = -y;
			}
			z = pio4 - x;
			w = pio4lo - y;
			x = z + w;
			y = 0.0;
		}
		z = x * x;
		w = z * z;
		/* Break x^5*(T[1]+x^2*T[2]+...) into
		*	  x^5(T[1]+x^4*T[3]+...+x^20*T[11]) +
		*	  x^5(x^2*(T[2]+x^4*T[4]+...+x^22*[T12]))
		*/
		r = T[ 1 ] + w * ( T[ 3 ] + w * ( T[ 5 ] + w * ( T[ 7 ] + w * ( T[ 9 ] + w * T[ 11 ] ) ) ) );
		v = z * ( T[ 2 ] + w * ( T[ 4 ] + w * ( T[ 6 ] + w * ( T[ 8 ] + w * ( T[ 10 ] + w * T[ 12 ] ) ) ) ) );
		s = z * x;
		r = y + z * ( s * ( r + v ) + y );
		r += T[ 0 ] * s;
		w = x + r;
		if( ix >= 0x3f2ca140 ) 
		{
			v = (float)iy;
			return (float)( 1 - ( ( hx >> 30 ) & 2 ) ) * ( v - (float)2.0 * ( x - ( w * w / ( w + v ) - r ) ) );
		}

		if( iy == 1 ) 
		{
			return w;
		}
		else 
		{ 
			// if allow error up to 2 ulp, simply return -1.0/(x+r) here compute -1.0/(x+r) accurately
			float a, t;
			Cmp_signed__int32 i;
			z = w;
			get_float_word( i, z );
			set_float_word( z, i & 0xfffff000 );
			v = r - ( z - x ); // z+v = r+x
			t = a = -(float)1.0 / w; // a = -1.0 / w
			get_float_word( i, t );
			set_float_word( t, i & 0xfffff000 );
			s = (float)1.0 + t * z;
			return t + a * ( s + t * v );
		}
	}

};//namespace nsBaseCRT
