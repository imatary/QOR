
/* @(#)s_modf.c 5.1 93/09/24 */
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
FUNCTION
       <<modf>>, <<modff>>---split fractional and integer parts

INDEX
	modf
INDEX
	modff

ANSI_SYNOPSIS
	#include <math.h>
	double modf(double <[val]>, double *<[ipart]>);
        float modff(float <[val]>, float *<[ipart]>);

TRAD_SYNOPSIS
	#include <math.h>
	double modf(<[val]>, <[ipart]>)
        double <[val]>;
        double *<[ipart]>;

	float modff(<[val]>, <[ipart]>)
	float <[val]>;
        float *<[ipart]>;

DESCRIPTION
	<<modf>> splits the double <[val]> apart into an integer part
	and a fractional part, returning the fractional part and
	storing the integer part in <<*<[ipart]>>>.  No rounding
	whatsoever is done; the sum of the integer and fractional
	parts is guaranteed to be exactly  equal to <[val]>.   That
	is, if <[realpart]> = modf(<[val]>, &<[intpart]>); then
	`<<<[realpart]>+<[intpart]>>>' is the same as <[val]>.
	<<modff>> is identical, save that it takes and returns
	<<float>> rather than <<double>> values. 

RETURNS
	The fractional part is returned.  Each result has the same
	sign as the supplied argument <[val]>.

PORTABILITY
	<<modf>> is ANSI C. <<modff>> is an extension.

QUICKREF
	modf  ansi pure 
	modff - pure

*/

/*
 * modf(double x, double *iptr) 
 * return fraction part of x, and return x's integral part in *iptr.
 * Method:
 *	Bit twiddling.
 *
 * Exception:
 *	No exception.
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::modff( float x, float* iptr )
	{
		static const float one = 1.0;

		Cmp_signed__int32 i0,j0;
		Cmp_unsigned__int32 i;
		get_float_word( i0, x );
		j0 = ( ( i0 >> 23 ) & 0xff ) - 0x7f; // exponent of x
		if( j0 < 23 ) 
		{	
			// integer part in x
			if( j0 < 0 ) 
			{			
				// |x|<1
				set_float_word( *iptr, i0 & 0x80000000 ); // *iptr = +-0
				return x;
			} 
			else 
			{
				i = (0x007fffff) >> j0;
				if( ( i0 & i ) == 0 ) 
				{
					// x is integral
					Cmp_unsigned__int32 ix;
					*iptr = x;
					get_float_word( ix, x );
					set_float_word( x, ix & 0x80000000 ); // return +-0
					return x;
				} 
				else 
				{
					set_float_word( *iptr, i0 & (~i) );
					return x - *iptr;
				}
			}
		} 
		else 
		{
			// no fraction part
			Cmp_unsigned__int32 ix;
			*iptr = x*one;
			get_float_word( ix, x );
			set_float_word( x, ix & 0x80000000 ); // return +-0
			return x;
		}
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	double Cmath::modf( double x, double* iptr )
	{
		return (double)modff( (float)x, (float*)iptr );
	}

#else

	//------------------------------------------------------------------------------
	double Cmath::modf( double x, double* iptr )
	{
		static const double one = 1.0;

		Cmp_signed__int32 i0, i1, j0;
		Cmp_unsigned__int32 i;
		extract_words( i0, i1, x );
		j0 = ( ( i0 >> 20 ) & 0x7ff ) - 0x3ff;	// exponent of x
		if( j0 < 20 ) 
		{			
			// integer part in high x
			if( j0 < 0 ) 
			{	
				// |x|<1
				insert_words( *iptr, i0 & 0x80000000, 0 );	// *iptr = +-0
				return x;
			} 
			else 
			{
				i = (0x000fffff) >> j0;
				if( ( ( i0 & i ) | i1 ) == 0 ) 
				{		
					// x is integral */
					Cmp_unsigned__int32 high;
					*iptr = x;
					get_high_word( high, x );
					insert_words( x, high & 0x80000000, 0 );	// return +-0
					return x;
				} 
				else 
				{
					insert_words( *iptr, i0 & (~i), 0 );
					return x - *iptr;
				}
			}
		} 
		else if ( j0 > 51 ) 
		{
			// no fraction part
			Cmp_unsigned__int32 high;
			*iptr = x*one;
			get_high_word( high, x );
			insert_words( x, high & 0x80000000, 0 );	// return +-0
			return x;
		} 
		else 
		{			
			// fraction part in low x
			i = ( (Cmp_unsigned__int32)(0xffffffff) ) >> ( j0 - 20 );
			if( ( i1 & i ) == 0 ) 
			{
				// x is integral
				Cmp_unsigned__int32 high;
				*iptr = x;
				get_high_word( high, x );
				insert_words( x, high & 0x80000000, 0 ); // return +-0
				return x;
			} 
			else 
			{
				insert_words( *iptr, i0, i1 & (~i) );
				return x - *iptr;
			}
		}
	}

#endif /* _DOUBLE_IS_32BITS */

};//namespace nsBaseCRT
