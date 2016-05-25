
/* @(#)s_lrint.c 5.1 93/09/24 */
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
 * lrint(x)
 * Return x rounded to integral value according to the prevailing
 * rounding mode.
 * Method:
 *	Using floating addition.
 * Exception:
 *	Inexact flag raised if x not equal to lrint(x).
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	/*Adding a float, x, to 2^23 will cause the result to be rounded based on
	the fractional part of x, according to the implementation's current rounding
	mode.  2^23 is the smallest float that can be represented using all 23 significant
	digits. */	
	long int Cmath::lrintf( float x )
	{
		static const float TWO23[ 2 ] = 
		{
			8.3886080000e+06, // 0x4b000000
			-8.3886080000e+06, // 0xcb000000
		};

		Cmp_signed__int32 j0,sx;
		Cmp_unsigned__int32 i0;
		float t;
		volatile float w;
		long int result;

		get_float_word( i0, x );

		// Extract sign bit.
		sx = ( i0 >> 31 );

		// Extract exponent field.
		j0 = ( ( i0 & 0x7f800000 ) >> 23 ) - 127;

		if( j0 < (int)( sizeof(long int) * 8 ) - 1 )
		{
			if( j0 < -1 )
			{
				return 0;
			}
			else if( j0 >= 23 )
			{
				result = (long int)( ( i0 & 0x7fffff ) | 0x800000 ) << ( j0 - 23 );
			}
			else
			{
				w = TWO23[ sx ] + x;
				t = w - TWO23[ sx ];
				get_float_word( i0, t );
				// Detect the all-zeros representation of plus and minus zero, which fails the calculation below.
				if( ( i0 & ~( 1 << 31 ) ) == 0 )
				{
					return 0;
				}
				j0 = ( ( i0 >> 23 ) & 0xff ) - 0x7f;
				i0 &= 0x7fffff;
				i0 |= 0x800000;
				result = i0 >> ( 23 - j0 );
			}
		}
		else
		{
			return (long int)x;
		}
		return sx ? -result : result;
	}


#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	long int Cmath::lrint( double x )
	{
		return (double)lrintf( (float)x );
	}

#else

	/*Adding a double, x, to 2^52 will cause the result to be rounded based on
	the fractional part of x, according to the implementation's current rounding
	mode.  2^52 is the smallest double that can be represented using all 52 significant
	digits. */

	//------------------------------------------------------------------------------
	long int Cmath::lrint( double x )
	{
		static const double TWO52[ 2 ] = 
		{
			4.50359962737049600000e+15,		// 0x43300000, 0x00000000
			-4.50359962737049600000e+15,	// 0xC3300000, 0x00000000
		};

		Cmp_signed__int32 i0, j0, sx;
		Cmp_unsigned__int32 i1;
		double t;
		volatile double w;
		long int result;

		extract_words(i0,i1,x);

		// Extract sign bit.
		sx = ( i0 >> 31 ) & 1;

		// Extract exponent field.
		j0 = ( ( i0 & 0x7ff00000 ) >> 20 ) - 1023;

		if( j0 < 20 )
		{
			if( j0 < -1 )
			{
				return 0;
			}
			else
			{
				w = TWO52[ sx ] + x;
				t = w - TWO52[ sx ];
				get_high_word( i0, t );
				// Detect the all-zeros representation of plus and minus zero, which fails the calculation below.
				if( ( i0 & ~( 1 << 31 ) ) == 0 )
				{
					return 0;
				}
				j0 = ( ( i0 & 0x7ff00000 ) >> 20 ) - 1023;
				i0 &= 0x000fffff;
				i0 |= 0x00100000;
				result = i0 >> ( 20 - j0 );
			}
		}
		else if ( j0 < (int)( 8 * sizeof( long int ) ) - 1 )
		{
			if( j0 >= 52 )
			{
				result = ( (long int)( ( i0 & 0x000fffff ) | 0x0010000 ) << ( j0 - 20 ) ) |  ( i1 << ( j0 - 52 ) );
			}
			else
			{
				w = TWO52[ sx ] + x;
				t = w - TWO52[ sx ];
				extract_words( i0, i1, t );
				j0 = ( ( i0 & 0x7ff00000 ) >> 20 ) - 1023;
				i0 &= 0x000fffff;
				i0 |= 0x00100000;
				result = ( (long int) i0 << ( j0 - 20 ) ) | ( i1 >> ( 52 - j0 ) );
			}
		}
		else
		{
			return (long int)x;
		}

		return sx ? -result : result;
	}

#endif//_DOUBLE_IS_32BITS

};//namespace nsBaseCRT

