/* @(#)s_scalbn.c 5.1 93/09/24 */
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
 * scalbn (double x, int n)
 * scalbn(x,n) returns x* 2**n  computed by  exponent
 * manipulation rather than by actually performing an
 * exponentiation or a multiplication.
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::scalblnf( float x, long int n )
	{
		static const float two25  = 3.355443200e+07;	// 0x4c000000
		static const float twom25 = 2.9802322388e-08;	// 0x33000000
		static const float huge   = 1.0e+30;
		static const float tiny   = 1.0e-30;

		Cmp_signed__int32 k, ix;
		get_float_word( ix, x );
		k = ( ix & 0x7f800000 ) >> 23; // extract exponent
		if( k == 0 ) 
		{				
			// 0 or subnormal x
			if( ( ix & 0x7fffffff ) == 0 )
			{
				return x; // +-0
			}
			x *= two25;
			get_float_word( ix, x );
			k = ( ( ix & 0x7f800000 ) >> 23 ) - 25;
		}

		if( k == 0xff )
		{
			return x + x; // NaN or Inf
		}

		k = k + n;
		if( n > 50000 || k > 0xfe )
		{
			return huge * copysignf( huge, x ); // overflow
		}

		if( n < -50000 )
		{
			return tiny * copysignf( tiny, x ); //underflow
		}

		if( k > 0 ) // normal result
		{
			set_float_word( x, ( ix & 0x807fffff ) | ( k << 23 ) );
			return x;
		}

		if( k <= -25 )
		{
			return tiny * copysignf( tiny, x ); //underflow
		}

		k += 25;				// subnormal result
		set_float_word( x, ( ix & 0x807fffff ) | ( k << 23 ) );
		return x * twom25;
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	double Cmath::scalbln( double x, long int n )
	{
		return (double)scalblnf( (float)x, n );
	}

#else

	//------------------------------------------------------------------------------
	double Cmath::scalbln( double x, long int n )
	{

		static const double two54   =  1.80143985094819840000e+16; // 0x43500000, 0x00000000
		static const double twom54  =  5.55111512312578270212e-17; // 0x3C900000, 0x00000000
		static const double huge   = 1.0e+300;
		static const double tiny   = 1.0e-300;

		Cmp_signed__int32 k,hx,lx;
		extract_words( hx, lx, x );
		k = ( hx & 0x7ff00000 ) >> 20;		// extract exponent
		if( k == 0 ) 
		{
			// 0 or subnormal x
			if( ( lx | ( hx & 0x7fffffff ) ) == 0 )
			{
				return x; // +-0
			}
			x *= two54;
			get_high_word( hx, x );
			k = ( ( hx & 0x7ff00000 ) >> 20 ) - 54;
		}

		if( k == 0x7ff )
		{
			return x + x;		// NaN or Inf
		}

		k = k + n;
		if( n > 50000 || k >  0x7fe )
		{
			return huge * copysign( huge, x ); // overflow
		}

		if( n < -50000 )
		{
			return tiny * copysign( tiny, x ); //underflow
		}

		if( k > 0 ) 				// normal result
		{
			set_high_word( x, ( hx & 0x800fffff ) | ( k << 20 ) );
			return x;
		}

		if( k <= -54 )
		{
			return tiny * copysign( tiny, x ); 	//underflow
		}

		k += 54;				// subnormal result
		set_high_word( x, ( hx & 0x800fffff ) | ( k << 20 ) );
		return x * twom54;
	}

#endif //_DOUBLE_IS_32BITS

};//namespace nsBaseCRT
