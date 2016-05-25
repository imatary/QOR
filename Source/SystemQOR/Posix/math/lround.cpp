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
	long int Cmath::lroundf( float x )
	{
		Cmp_signed__int32 exponent_less_127;
		Cmp_unsigned__int32 w;
		long int result;
		Cmp_signed__int32 sign;

		get_float_word( w, x );
		exponent_less_127 = ( ( w & 0x7f800000 ) >> 23 ) - 127;
		sign = ( w & 0x80000000 ) != 0 ? -1 : 1;
		w &= 0x7fffff;
		w |= 0x800000;

		if( exponent_less_127 < ( 8 * sizeof(long int) ) - 1 )
		{
			if( exponent_less_127 < 0 )
			{
				return exponent_less_127 < -1 ? 0 : sign;
			}
			else if( exponent_less_127 >= 23 )
			{
				result = (long int) w << ( exponent_less_127 - 23 );
			}
			else
			{
				w += 0x400000 >> exponent_less_127;
				result = w >> ( 23 - exponent_less_127 );
			}
		}
		else
		{
			return (long int)x;
		}

		return sign * result;
	}


#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	long int Cmath::lround( double x )
	{
		return (double) lroundf( (float)x );
	}

#else

	//------------------------------------------------------------------------------
	long int Cmath::lround( double x )
	{
		Cmp_signed__int32 sign, exponent_less_1023;	
		Cmp_unsigned__int32 msw, lsw;// Most significant word, least significant word.
		long int result;

		extract_words( msw, lsw, x );

		// Extract sign.
		sign = ( ( msw & 0x80000000 ) ? -1 : 1 );
		// Extract exponent field.
		exponent_less_1023 = ( ( msw & 0x7ff00000 ) >> 20 ) - 1023;
		msw &= 0x000fffff;
		msw |= 0x00100000;

		if( exponent_less_1023 < 20 )
		{
			if( exponent_less_1023 < 0 )
			{
				if( exponent_less_1023 < -1 )
				{
					return 0;
				}
				else
				{
					return sign;
				}
			}
			else
			{
				msw += 0x80000 >> exponent_less_1023;
				result = msw >> ( 20 - exponent_less_1023 );
			}
		}
		else if( exponent_less_1023 < ( 8 * sizeof(long int) ) - 1 )
		{
			if( exponent_less_1023 >= 52 )
			{
				result = ( (long int) msw << ( exponent_less_1023 - 20 ) ) | ( lsw << ( exponent_less_1023 - 52 ) );
			}
			else
			{
				unsigned int tmp = lsw + ( 0x80000000 >> ( exponent_less_1023 - 20 ) );
				if( tmp < lsw )
				{
					++msw;
				}
				result = ( (long int) msw << ( exponent_less_1023 - 20 ) ) | ( tmp >> ( 52 - exponent_less_1023 ) );
			}
		}
		else
		{
			return (long int)x;// Result is too large to be represented by a long int.
		}

		return sign * result;
	}

#endif /* _DOUBLE_IS_32BITS */

};//namespace nsBaseCRT
