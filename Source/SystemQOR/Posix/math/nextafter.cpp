
/* @(#)s_nextafter.c 5.1 93/09/24 */
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
       <<nextafter>>, <<nextafterf>>---get next number

INDEX
	nextafter
INDEX
	nextafterf

ANSI_SYNOPSIS
       #include <math.h>
       double nextafter(double <[val]>, double <[dir]>);
       float nextafterf(float <[val]>, float <[dir]>);

TRAD_SYNOPSIS
       #include <math.h>

       double nextafter(<[val]>, <[dir]>)
              double <[val]>;
              double <[exp]>;

       float nextafter(<[val]>, <[dir]>)
              float <[val]>;
              float <[dir]>;


DESCRIPTION
<<nextafter>> returns the double-precision floating-point number
closest to <[val]> in the direction toward <[dir]>.  <<nextafterf>>
performs the same operation in single precision.  For example,
<<nextafter(0.0,1.0)>> returns the smallest positive number which is
representable in double precision.

RETURNS
Returns the next closest number to <[val]> in the direction toward
<[dir]>.

PORTABILITY
	Neither <<nextafter>> nor <<nextafterf>> is required by ANSI C
	or by the System V Interface Definition (Issue 2).
*/

/* IEEE functions
 *	nextafter(x,y)
 *	return the next machine floating-point number of x in the
 *	direction toward y.
 *   Special cases:
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::nextafterf( float x, float y )
	{
		Cmp_signed__int32 hx, hy, ix, iy;

		get_float_word( hx, x );
		get_float_word( hy, y );
		ix = hx & 0x7fffffff;		// |x|
		iy = hy & 0x7fffffff;		// |y|

		if( uword_isnan( ix ) || uword_isnan( iy ) )
		{
			return x + y;
		}

		if( x == y )
		{
			return x;		// x=y, return x
		}

		if( uword_is_zero( ix ) ) 
		{	
			// x == 0
			set_float_word( x, ( hy & 0x80000000 ) | uword_min() );
			y = x * x;
			if( y == x )
			{
				return y;
			}
			else
			{
				return x;	// raise underflow flag
			}
		}

		if( hx >= 0 ) 
		{
			// x > 0
			if( hx > hy ) 
			{
				// x > y, x -= ulp
				hx -= 1;
			} 
			else 
			{
				// x < y, x += ulp
				hx += 1;
			}
		} 
		else 
		{	// x < 0
			if( hy >= 0 || hx > hy )
			{	
				// x < y, x -= ulp
				hx -= 1;
			} 
			else 
			{	// x > y, x += ulp
				hx += 1;
			}
		}

		hy = hx & 0x7f800000;
		if( hy > uword_max() )
		{
			return x + x;	// overflow
		}

		if( hy < 0x00800000 ) 
		{ 
			// underflow
			y = x * x;
			if( y != x ) 
			{
				// raise underflow flag
				set_float_word( y, hx );
				return y;
			}
		}
		set_float_word( x, hx );
		return x;
	}


#ifdef _DOUBLE_IS_32BITS
	//------------------------------------------------------------------------------
	double Cmath::nextafter( double x, double y )
	{
		return (double)nextafterf( (float)x, (float)x );
	}

#else

	//------------------------------------------------------------------------------
	double Cmath::nextafter( double x, double y )
	{
		Cmp_signed__int32	hx, hy, ix, iy;
		Cmp_unsigned__int32 lx, ly;

		extract_words( hx, lx, x );
		extract_words( hy, ly , y );
		ix = hx & 0x7fffffff;		// |x|
		iy = hy & 0x7fffffff;		// |y|

		if( ( ( ix >= 0x7ff00000 ) && ( ( ix - 0x7ff00000 ) | lx ) != 0 ) ||   // x is nan 
			( ( iy >= 0x7ff00000 ) && ( ( iy - 0x7ff00000 ) | ly ) != 0 ) )    // y is nan
		{
		   return x + y;
		}

		if( x == y )
		{
			return x;		// x=y, return x
		}

		if( ( ix | lx ) == 0 ) 
		{	
			// x == 0
			insert_words( x, hy & 0x80000000, 1 );	// return +-minsubnormal
			y = x * x;
			if( y == x )
			{
				return y;
			}
			else 
			{
				return x;	// raise underflow flag
			}
		} 

		if( hx >= 0 ) 
		{	
			// x > 0
			if( hx > hy || ( ( hx == hy ) && ( lx > ly ) ) ) 
			{
				// x > y, x -= ulp
				if( lx==0 ) 
				{
					hx -= 1;
				}
				lx -= 1;
			} 
			else 
			{
				// x < y, x += ulp
				lx += 1;
				if( lx == 0 )
				{
					hx += 1;
				}
			}
		} 
		else 
		{				
			// x < 0
			if( hy >= 0 || hx > hy || ( ( hx == hy ) && ( lx > ly ) ) ) 
			{
				// x < y, x -= ulp
				if( lx == 0 )
				{
					hx -= 1;
				}
				lx -= 1;
			} 
			else 
			{
				// x > y, x += ulp
				lx += 1;
				if( lx == 0 )
				{
					hx += 1;
				}
			}
		}

		hy = hx & 0x7ff00000;
		if( hy >= 0x7ff00000 )
		{
			return x + x; // overflow
		}

		if( hy < 0x00100000 ) 
		{		
			// underflow
			y = x * x;
			if( y != x ) 
			{	
				// raise underflow flag
				insert_words( y, hx, lx );
				return y;
			}
		}
		insert_words( x, hx, lx );
		return x;
	}

#endif /* _DOUBLE_IS_32BITS */

};//namespace nsBaseCRT
