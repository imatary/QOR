
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
FUNCTION
<<scalbn>>, <<scalbnf>>---scale by power of two
INDEX
    scalbn
INDEX
    scalbnf

ANSI_SYNOPSIS
    #include <math.h>
    double scalbn(double <[x]>, int <[y]>);
    float scalbnf(float <[x]>, int <[y]>);

TRAD_SYNOPSIS
    #include <math.h>
    double scalbn(<[x]>,<[y]>)
    double <[x]>;
    int <[y]>;
    float scalbnf(<[x]>,<[y]>)
    float <[x]>;
    int <[y]>;

DESCRIPTION
<<scalbn>> and <<scalbnf>> scale <[x]> by <[n]>, returning <[x]> times
2 to the power <[n]>.  The result is computed by manipulating the
exponent, rather than by actually performing an exponentiation or
multiplication.

RETURNS
<[x]> times 2 to the power <[n]>.

PORTABILITY
Neither <<scalbn>> nor <<scalbnf>> is required by ANSI C or by the System V
Interface Definition (Issue 2).

*/

/*
 * scalbn (double x, int n)
 * scalbn(x,n) returns x* 2**n  computed by  exponent
 * manipulation rather than by actually performing an
 * exponentiation or a multiplication.
 */
//Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.

#include "SystemQOR/Posix/Basemath.h"
#include QOR_SYS_PLATFORMTYPES(math)

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
    //------------------------------------------------------------------------------
    float Cmath::scalbnf( float x, int n )
    {
        static const float two25  = 3.355443200e+07;	// 0x4c000000
        static const float twom25 = 2.9802322388e-08;	// 0x33000000
        static const float huge   = 1.0e+30;
        static const float tiny   = 1.0e-30;

        Cmp_signed__int32  k,ix;
        Cmp_unsigned__int32 hx;

        get_float_word( ix, x );
        hx = ix & 0x7fffffff;
        k = hx >> 23;		// extract exponent
        if( uword_is_zero( hx ) )
        {
            return x;
        }

        if( !uword_isfinite( hx ) )
        {
            return x + x;		// NaN or Inf
        }

        if( uword_is_subnormal( hx ) )
        {
            x *= two25;
            get_float_word( ix, x );
            k = ( ( ix & 0x7f800000 ) >> 23 ) - 25;
            if( n < -50000 )
            {
                return tiny * x; //underflow
            }
        }

        k = k + n;
        if( k > largest_exp() )
        {
            return huge * copysignf( huge, x ); // overflow
        }

        if( k > 0 ) 				// normal result
        {
            set_float_word( x, ( ix & 0x807fffff ) | ( k << 23 ) );
            return x;
        }

        if( k < smallest_exp() )
        {
            if( n > ( INT_MAX > 50000 ? 50000 : 30000 ) ) 	// in case integer overflow in n+k
            {
                return huge * copysignf( huge, x );	//overflow
            }
            else
            {
                return tiny * copysignf( tiny, x );	//underflow
            }
        }

        k += 25;				// subnormal result
        set_float_word( x, ( ix & 0x807fffff ) | ( k << 23 ) );
        return x * twom25;
    }

#ifdef _DOUBLE_IS_32BITS

    //------------------------------------------------------------------------------
    double Cmath::scalbn( double x, int n )
    {
        return (double)scalbnf( (float)x, n );
    }

#else

    //------------------------------------------------------------------------------
    double Cmath::scalbn( double x, int n )
    {
        static const double two54   =  1.80143985094819840000e+16; // 0x43500000, 0x00000000
        static const double twom54  =  5.55111512312578270212e-17; // 0x3C900000, 0x00000000
        static const double huge   = 1.0e+300;
        static const double tiny   = 1.0e-300;

        Cmp_signed__int32  k, hx, lx;
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
            if( n < -50000 )
            {
                return tiny * x; //underflow
            }
        }

        if( k == 0x7ff )
        {
            return x + x;		// NaN or Inf
        }

        k = k + n;
        if( k > 0x7fe )
        {
            return huge * copysign( huge, x ); // overflow
        }

        if( k > 0 ) 				// normal result
        {
            set_high_word( x, ( hx & 0x800fffff ) | ( k << 20 ) );
            return x;
        }

        if( k <= -54 )
        {
            if( n > 50000 ) 	// in case integer overflow in n+k
            {
                return huge * copysign( huge, x ); //overflow
            }
            else
            {
                return tiny * copysign( tiny, x ); //underflow
            }
        }
        k += 54;				// subnormal result
        set_high_word( x, ( hx & 0x800fffff ) | ( k << 20 ) );
        return x * twom54;
    }

#endif // _DOUBLE_IS_32BITS

};//namespace nsBaseCRT
