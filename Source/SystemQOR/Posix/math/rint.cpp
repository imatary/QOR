
/* @(#)s_rint.c 5.1 93/09/24 */
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
//Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
/*
 * rint(x)
 * Return x rounded to integral value according to the prevailing
 * rounding mode.
 * Method:
 *	Using floating addition.
 * Exception:
 *	Inexact flag raised if x not equal to rint(x).
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::rintf( float x )
	{
		static const float TWO23[ 2 ] = 
		{
			8.3886080000e+06,	// 0x4b000000
			-8.3886080000e+06,	// 0xcb000000
		};

		Cmp_signed__int32 i0,j0,sx;
		Cmp_unsigned__int32 i,i1,ix;
		float t;
		volatile float w;
		get_float_word( i0, x );
		sx = ( i0 >> 31 ) & 1;
		ix = ( i0 & 0x7fffffff );
		j0 = ( ix >> 23 ) - 0x7f;
		if( j0 < 23 ) 
		{
			if( uword_is_zero( ix ) )
			{
				return x;
			}
			if( j0 < 0 ) 
			{
				i1 = ( i0 & 0x07fffff );
				i0 &= 0xfff00000;
				i0 |= ( ( i1 | -i1 ) >> 9 ) & 0x400000;
				set_float_word( x, i0 );
				w = TWO23[ sx ] + x;
				t = w - TWO23[ sx ];
				get_float_word( i0, t );
				set_float_word( t, ( i0 & 0x7fffffff ) | ( sx << 31 ) );
				return t;
			} 
			else 
			{
				i = (0x007fffff) >> j0;
				if( ( i0 & i ) == 0 )
				{
					return x; // x is integral
				}
				i >>= 1;
				if( ( i0 & i ) != 0 )
				{
					i0 = ( i0 & (~i) ) | ( (0x100000) >> j0 );
				}
			}
		} 
		else 
		{
			if( !uword_isfinite( ix ) )
			{
				return x + x; // inf or NaN
			}
			else
			{
				return x;		// x is integral
			}
		}

		set_float_word( x, i0 );
		w = TWO23[ sx ] + x;
		return w - TWO23[ sx ];
	}

#ifdef _DOUBLE_IS_32BITS
	//------------------------------------------------------------------------------
	double Cmath::rint( double x )
	{
		return (double) rintf( (float)x );
	}

#else
	//------------------------------------------------------------------------------
	double Cmath::rint( double x )
	{
		static const double TWO52[ 2 ] = 
		{
			4.50359962737049600000e+15, // 0x43300000, 0x00000000
			-4.50359962737049600000e+15, // 0xC3300000, 0x00000000
		};

		Cmp_signed__int32 i0,j0,sx;
		Cmp_unsigned__int32 i,i1;
		double t;
		volatile double w;
		extract_words( i0, i1, x );
		sx = ( i0 >> 31 ) & 1;
		j0 = ( ( i0 >> 20 ) & 0x7ff ) - 0x3ff;
		if( j0 < 20 ) 
		{
			if( j0 < 0 ) 
			{ 	
				if( ( ( i0 & 0x7fffffff ) | i1 ) == 0 )
				{
					return x;
				}
				i1 |= ( i0 & 0x0fffff );
				i0 &= 0xfffe0000;
				i0 |= ( ( i1 | -i1 ) >> 12 ) & 0x80000;
				set_high_word( x, i0 );
				w = TWO52[ sx ] + x;
				t = w - TWO52[ sx ];
				get_high_word( i0, t );
				set_high_word( t, ( i0 & 0x7fffffff ) | ( sx << 31 ) );
				return t;
			} 
			else 
			{
				i = (0x000fffff) >> j0;
				if( ( ( i0 & i ) | i1 ) == 0 )
				{
					return x; // x is integral
				}
				i >>= 1;
				if( ( ( i0 & i ) | i1 ) != 0 ) 
				{
					if( j0 == 19 )
					{
						i1 = 0x40000000;
					}
					else
					{
						i0 = ( i0 & (~i) ) | ( ( 0x20000 ) >> j0 );
					}
				}
			}
		} 
		else if ( j0 > 51 ) 
		{
			if( j0 == 0x400 )
			{
				return x + x;// inf or NaN
			}
			else 
			{
				return x; // x is integral
			}
		} 
		else 
		{
			i = ( (Cmp_unsigned__int32)(0xffffffff) ) >> ( j0 - 20 );
			if( ( i1 & i ) == 0 )
			{
				return x;// x is integral
			}
			i >>= 1;
			if( ( i1 & i ) != 0 )
			{
				i1 = ( i1 & (~i) ) | ( (0x40000000) >> ( j0 - 20 ) );
			}
		}
		insert_words( x, i0, i1 );
		w = TWO52[ sx ] + x;
		return w - TWO52[ sx ];
	}

#endif//_DOUBLE_IS_32BITS

};//namespace nsBaseCRT
