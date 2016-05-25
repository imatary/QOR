
/* @(#)s_ceil.c 5.1 93/09/24 */
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
 * ceil(x)
 * Return x rounded toward -inf to integral value
 * Method:
 *	Bit twiddling.
 * Exception:
 *	Inexact flag raised if x not equal to ceil(x).
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::ceilf( float x )
	{
		static const float huge = 1.0e30;
		Cmp_signed__int32 i0, j0;
		Cmp_unsigned__int32 i, ix;
		get_float_word( i0, x );
		ix = ( i0 & 0x7fffffff );
		j0 = ( ix >> 23 ) - 0x7f;
		if( j0 < 23 ) 
		{
			if( j0 < 0 ) 
			{ 	
				// raise inexact if x != 0
				if( huge + x >(float)0.0 ) 
				{
					// return 0*sign(x) if |x|<1
					if( i0 < 0 ) 
					{
						i0 = 0x80000000;
					} 
					else if( !uword_is_zero( ix ) ) 
					{ 
						i0 = 0x3f800000;
					}
				}
			} 
			else 
			{
				i = (0x007fffff) >> j0;
				if( ( i0 & i ) == 0 )
				{
					return x; // x is integral
				}

				if( huge + x >(float)0.0 ) 
				{	
					// raise inexact flag
					if( i0 > 0 )
					{
						i0 += (0x00800000) >> j0;
					}
					i0 &= (~i);
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
				return x;	// x is integral
			}
		}

		set_float_word( x, i0 );
		return x;
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	double Cmath::ceil( double x )
	{
		return (double)ceilf( (float)x );
	}

#else

	//------------------------------------------------------------------------------
	double Cmath::ceil( double x )
	{
		static const double huge = 1.0e300;
		Cmp_signed__int32 i0, i1, j0;
		Cmp_unsigned__int32 i, j;
		extract_words( i0, i1, x );
		j0 = ( ( i0 >> 20 ) & 0x7ff ) - 0x3ff;
		if( j0 < 20 ) 
		{
			if( j0 < 0 ) 
			{
				// raise inexact if x != 0
				if( huge + x >0.0 ) 
				{
					// return 0*sign(x) if |x|<1
					if( i0 < 0 ) 
					{
						i0 = 0x80000000;
						i1 = 0;
					}
					else if( ( i0 | i1 ) != 0 )
					{
						i0 = 0x3ff00000;
						i1 = 0;
					}
				}
			} 
			else 
			{
				i = (0x000fffff) >> j0;
				if( ( ( i0 & i ) | i1 ) == 0 )
				{
					return x; // x is integral
				}

				if( huge + x > 0.0 ) 
				{	
					// raise inexact flag
					if( i0 > 0 )
					{
						i0 += (0x00100000) >> j0;
					}
					i0 &= (~i);
					i1 = 0;
				}
			}
		} 
		else if( j0 > 51 ) 
		{
			if( j0 == 0x400 )
			{
				return x + x; // inf or NaN
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
				return x; // x is integral
			}

			if( huge + x > 0.0 ) 
			{
				// raise inexact flag
				if( i0 > 0 ) 
				{
					if( j0 == 20 )
					{
						i0 += 1; 
					}
					else 
					{
						j = i1 + ( 1 << ( 52 - j0 ) );
						if( j < i1 )
						{
							i0 += 1; // got a carry
						}
						i1 = j;
					}
				}
				i1 &= (~i);
			}
		}
		insert_words( x, i0, i1 );
		return x;
	}

#endif//_DOUBLE_IS_32BITS

};//namespace nsBaseCRT
