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

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::roundf( float x )
	{
		int signbit;
		Cmp_unsigned__int32 w;
		// Most significant word, least significant word.
		int exponent_less_127;

		get_float_word( w, x );

		// Extract sign bit.
		signbit = w & 0x80000000;

		// Extract exponent field.
		exponent_less_127 = (int)( ( w & 0x7f800000 ) >> 23 ) - 127;

		if( exponent_less_127 < 23 )
		{
			if( exponent_less_127 < 0 )
			{
				w &= 0x80000000;
				if( exponent_less_127 == -1 )
				{
					// Result is +1.0 or -1.0.
					w |= ( 127 << 23 );
				}
			}
			else
			{
				unsigned int exponent_mask = 0x007fffff >> exponent_less_127;
				if( ( w & exponent_mask ) == 0 )
				{					
					return x;// x has an integral value.
				}

				w += 0x00400000 >> exponent_less_127;
				w &= ~exponent_mask;
			}
		}
		else
		{
			if( exponent_less_127 == 128 )
			{			
				return x + x;// x is NaN or infinite.
			}
			else
			{
				return x;
			}
		}
		set_float_word( x, w );
		return x;
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	double Cmath::round( double x )
	{
		return (double)roundf( (float)x );
	}

#else

	//------------------------------------------------------------------------------
	double Cmath::round( double x )
	{
		// Most significant word, least significant word.
		Cmp_signed__int32 msw, exponent_less_1023;
		Cmp_unsigned__int32 lsw;

		extract_words( msw, lsw, x );

		// Extract exponent field.
		exponent_less_1023 = ( ( msw & 0x7ff00000 ) >> 20 ) - 1023;

		if( exponent_less_1023 < 20 )
		{
			if( exponent_less_1023 < 0 )
			{
				msw &= 0x80000000;
				if( exponent_less_1023 == -1 )
				{
					// Result is +1.0 or -1.0.
					msw |= ( 1023 << 20 );
				}
				lsw = 0;
			}
			else
			{
				Cmp_unsigned__int32 exponent_mask = 0x000fffff >> exponent_less_1023;
				if( ( msw & exponent_mask ) == 0 && lsw == 0 )
				{
					return x;// x is an integral value.
				}

				msw += 0x00080000 >> exponent_less_1023;
				msw &= ~exponent_mask;
				lsw = 0;
			}
		}
		else if ( exponent_less_1023 > 51 )
		{
			if( exponent_less_1023 == 1024 )
			{
				return x + x;// x is NaN or infinite.
			}
			else
			{
				return x;
			}
		}
		else
		{
			Cmp_unsigned__int32 exponent_mask = 0xffffffff >> ( exponent_less_1023 - 20 );
			Cmp_unsigned__int32 tmp;

			if( ( lsw & exponent_mask ) == 0 )
			{
				return x;// x is an integral value.
			}

			tmp = lsw + ( 1 << ( 51 - exponent_less_1023 ) );
			if( tmp < lsw )
			{
				msw += 1;
			}
			lsw = tmp;
			lsw &= ~exponent_mask;
		}

		insert_words( x, msw, lsw );
		return x;
	}

#endif//_DOUBLE_IS_32BITS

};//namespace nsBaseCRT
