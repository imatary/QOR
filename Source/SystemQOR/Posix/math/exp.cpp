
/* @(#)e_exp.c 5.1 93/09/24 */
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
/* __ieee754_exp(x)
 * Returns the exponential of x.
 *
 * Method
 *   1. Argument reduction:
 *      Reduce x to an r so that |r| <= 0.5*ln2 ~ 0.34658.
 *	Given x, find r and integer k such that
 *
 *               x = k*ln2 + r,  |r| <= 0.5*ln2.
 *
 *      Here r will be represented as r = hi-lo for better
 *	accuracy.
 *
 *   2. Approximation of exp(r) by a special rational function on
 *	the interval [0,0.34658]:
 *	Write
 *	    R(r**2) = r*(exp(r)+1)/(exp(r)-1) = 2 + r*r/6 - r**4/360 + ...
 *      We use a special Reme algorithm on [0,0.34658] to generate
 * 	a polynomial of degree 5 to approximate R. The maximum error
 *	of this polynomial approximation is bounded by 2**-59. In
 *	other words,
 *	    R(z) ~ 2.0 + P1*z + P2*z**2 + P3*z**3 + P4*z**4 + P5*z**5
 *  	(where z=r*r, and the values of P1 to P5 are listed below)
 *	and
 *	    |                  5          |     -59
 *	    | 2.0+P1*z+...+P5*z   -  R(z) | <= 2
 *	    |                             |
 *	The computation of exp(r) thus becomes
 *                             2*r
 *		exp(r) = 1 + -------
 *		              R - r
 *                                 r*R1(r)
 *		       = 1 + r + ----------- (for better accuracy)
 *		                  2 - R1(r)
 *	where
 *			         2       4             10
 *		R1(r) = r - (P1*r  + P2*r  + ... + P5*r   ).
 *
 *   3. Scale back to obtain exp(x):
 *	From step 1, we have
 *	   exp(x) = 2^k * exp(r)
 *
 * Special cases:
 *	exp(INF) is INF, exp(NaN) is NaN;
 *	exp(-INF) is 0, and
 *	for finite argument, only exp(0)=1 is exact.
 *
 * Accuracy:
 *	according to an error analysis, the error is always less than
 *	1 ulp (unit in the last place).
 *
 * Misc. info.
 *	For IEEE double
 *	    if x >  7.09782712893383973096e+02 then exp(x) overflow
 *	    if x < -7.45133219101941108420e+02 then exp(x) underflow
 *
 * Constants:
 * The hexadecimal values are the intended ones for the following
 * constants. The decimal values may be used, provided that the
 * compiler will convert from decimal to binary accurately enough
 * to produce the hexadecimal values shown.
 */

#include "SystemQOR/Posix/Basemath.h"
#include <math.h>

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
    //------------------------------------------------------------------------------
    float Cmath::expf( float x ) // wrapper expf
    {
        static const float o_threshold = 8.8721679688e+01;  // 0x42b17180
        static const float u_threshold = -1.0397208405e+02;  // 0xc2cff1b5

        float z;
        struct fexception exc;
        z = __ieee754_expf( x );
        if( m_fdlib_version == _IEEE_ )
        {
            return z;
        }
        if( finitef( x ) )
        {
            if( x > o_threshold )
            {
                // expf(finite) overflow
                exc.type = EX_OVERFLOW;
                exc.name = "expf";
                exc.err = 0;
                exc.arg1 = exc.arg2 = (double)x;
                if( m_fdlib_version == _SVID_ )
                {
                    exc.retval = Huge();
                }
                else
                {
                    exc.retval = HUGE_VAL;
                }

                if( m_fdlib_version == _POSIX_ )
                {
                    errno = ERANGE;
                }
                else if( !matherr( &exc ) )
                {
                    errno = ERANGE;
                }

                if( exc.err != 0 )
                {
                    errno = exc.err;
                }
                return exc.retval;
            }
            else if( x < u_threshold )
            {
                // expf(finite) underflow
                exc.type = EX_UNDERFLOW;
                exc.name = "expf";
                exc.err = 0;
                exc.arg1 = exc.arg2 = (double)x;
                exc.retval = 0.0;
                if( m_fdlib_version == _POSIX_ )
                {
                    errno = ERANGE;
                }
                else if( !matherr( &exc ) )
                {
                    errno = ERANGE;
                }

                if( exc.err != 0 )
                {
                    errno = exc.err;
                }
                return exc.retval;
            }
        }
        return z;
    }

#ifdef _DOUBLE_IS_32BITS

    //------------------------------------------------------------------------------
    double Cmath::exp( double x )
    {
        return (double)expf( (float)x );
    }

#else

    //------------------------------------------------------------------------------
    double Cmath::exp( double x ) // wrapper exp
    {
        static const double o_threshold=  7.09782712893383973096e+02;  // 0x40862E42, 0xFEFA39EF
        static const double u_threshold= -7.45133219101941108420e+02;  // 0xc0874910, 0xD52D3051

        double z;
        struct fexception exc;
        z = __ieee754_exp( x );
        if( m_fdlib_version == _IEEE_ )
        {
            return z;
        }

        if( finite( x ) )
        {
            if( x > o_threshold )
            {
                // exp(finite) overflow
#	ifndef HUGE_VAL
#		define HUGE_VAL inf
                double inf = 0.0;
                set_high_word( inf, 0x7ff00000 ); // set inf to infinite
#	endif
                exc.type = EX_OVERFLOW;
                exc.name = "exp";
                exc.err = 0;
                exc.arg1 = exc.arg2 = x;
                if( m_fdlib_version == _SVID_ )
                {
                    exc.retval = Huge();
                }
                else
                {
                    exc.retval = HUGE_VAL;
                }
                if( m_fdlib_version == _POSIX_ )
                {
                    errno = ERANGE;
                }
                else if( !matherr( &exc ) )
                {
                    errno = ERANGE;
                }
                if( exc.err != 0 )
                {
                    errno = exc.err;
                }
                return exc.retval;
            }
            else if( x < u_threshold )
            {
                // exp(finite) underflow
                exc.type = EX_UNDERFLOW;
                exc.name = "exp";
                exc.err = 0;
                exc.arg1 = exc.arg2 = x;
                exc.retval = 0.0;
                if( m_fdlib_version == _POSIX_ )
                {
                    errno = ERANGE;
                }
                else if( !matherr( &exc ) )
                {
                    errno = ERANGE;
                }

                if( exc.err != 0 )
                {
                    errno = exc.err;
                }
                return exc.retval;
            }
        }
        return z;
    }

    //------------------------------------------------------------------------------
    double Cmath::__ieee754_exp( double x ) // default IEEE double exp
    {
        static const double one	= 1.0;
        static const double halF[ 2 ] = {0.5,-0.5,};
        static const double huge = 1.0e+300;
        static const double twom1000 = 9.33263618503218878990e-302;     // 2**-1000=0x01700000,0
        static const double o_threshold =  7.09782712893383973096e+02;  // 0x40862E42, 0xFEFA39EF
        static const double u_threshold = -7.45133219101941108420e+02;  // 0xc0874910, 0xD52D3051
        static const double ln2HI[ 2 ] =
        {	6.93147180369123816490e-01,		// 0x3fe62e42, 0xfee00000
            -6.93147180369123816490e-01,	// 0xbfe62e42, 0xfee00000
        };
        static const double ln2LO[ 2 ] =
        {	1.90821492927058770002e-10,  // 0x3dea39ef, 0x35793c76
            -1.90821492927058770002e-10, // 0xbdea39ef, 0x35793c76
        };
        static const double invln2 = 1.44269504088896338700e+00; // 0x3ff71547, 0x652b82fe
        static const double P1 =  1.66666666666666019037e-01; // 0x3FC55555, 0x5555553E
        static const double P2 = -2.77777777770155933842e-03; // 0xBF66C16C, 0x16BEBD93
        static const double P3 =  6.61375632143793436117e-05; // 0x3F11566A, 0xAF25DE2C
        static const double P4 = -1.65339022054652515390e-06; // 0xBEBBBD41, 0xC5D26BF1
        static const double P5 =  4.13813679705723846039e-08; // 0x3E663769, 0x72BEA4D0

        double y, hi, lo, c, t;
        Cmp_signed__int32 k, xsb;
        Cmp_unsigned__int32 hx;

        get_high_word( hx, x );
        xsb = ( hx >> 31 ) & 1;	// sign bit of x
        hx &= 0x7fffffff;		// high word of |x|

        // filter out non-finite argument
        if( hx >= 0x40862E42 )
        {
            // if |x|>=709.78...
            if( hx >= 0x7ff00000 )
            {
                Cmp_unsigned__int32 lx;
                get_low_word( lx, x );
                if( ( ( hx & 0xfffff ) | lx ) != 0 )
                {
                    return x + x;		// NaN
                }
                else
                {
                    return ( xsb == 0 ) ? x : 0.0; // exp(+-inf)={inf,0}
                }
            }

            if( x > o_threshold )
            {
                return huge * huge; // overflow
            }

            if( x < u_threshold )
            {
                return twom1000 * twom1000; // underflow
            }
        }

        // argument reduction
        if( hx > 0x3fd62e42 )
        {
            // if  |x| > 0.5 ln2
            if( hx < 0x3FF0A2B2 )
            {
                // and |x| < 1.5 ln2
                hi = x - ln2HI[ xsb ];
                lo = ln2LO[ xsb ];
                k = 1 - xsb - xsb;
            }
            else
            {
                k = invln2 * x + halF[ xsb ];
                t = k;
                hi = x - t * ln2HI[ 0 ]; // t*ln2HI is exact here
                lo = t * ln2LO[ 0 ];
            }
            x  = hi - lo;
        }
        else if( hx < 0x3e300000 )
        {
            // when |x|<2**-28
            if( huge + x > one )
            {
                return one + x;// trigger inexact
            }
        }
        else
        {
            k = 0;
        }

        // x is now in primary range
        t  = x * x;
        c  = x - t * ( P1 + t * ( P2 + t * ( P3 + t * ( P4 + t * P5 ) ) ) );
        if( k == 0 )
        {
            return one - ( ( x * c ) / ( c - 2.0 ) - x );
        }
        else
        {
            y = one - ( ( lo - ( x * c ) / ( 2.0 - c ) ) - hi );
        }

        if( k >= -1021 )
        {
            Cmp_unsigned__int32 hy;
            get_high_word( hy, y );
            set_high_word( y, hy + ( k << 20 ) ); // add k to y's exponent
            return y;
        }
        else
        {
            Cmp_unsigned__int32 hy;
            get_high_word( hy, y );
            set_high_word( y, hy + ( ( k + 1000 ) << 20 ) ); // add k to y's exponent
            return y * twom1000;
        }
    }

#endif//defined(_DOUBLE_IS_32BITS)

    //------------------------------------------------------------------------------
    float Cmath::__ieee754_expf( float x ) // default IEEE double exp
    {
        static const float one = 1.0;
        static const float halF[ 2 ] = { 0.5, -0.5, };
        static const float huge	= 1.0e+30;
        static const float twom100 = 7.8886090522e-31;	// 2**-100=0x0d800000
        static const float ln2HI[ 2 ] =
        {
            6.9313812256e-01,	// 0x3f317180/
            -6.9313812256e-01,	// 0xbf317180
        };

        static const float ln2LO[ 2 ] =
        {
            9.0580006145e-06,  	// 0x3717f7d1
            -9.0580006145e-06,	// 0xb717f7d1
        };

        static const float invln2 = 1.4426950216e+00; 	// 0x3fb8aa3b
        static const float P1 =  1.6666667163e-01;		// 0x3e2aaaab
        static const float P2 = -2.7777778450e-03;		// 0xbb360b61
        static const float P3 =  6.6137559770e-05;		// 0x388ab355
        static const float P4 = -1.6533901999e-06;		// 0xb5ddea0e
        static const float P5 =  4.1381369442e-08;		// 0x3331bb4c

        float y, hi, lo, c, t;
        Cmp_signed__int32 k, xsb, sx;
        Cmp_unsigned__int32 hx;

        get_float_word( sx, x );
        xsb = ( sx >> 31 ) & 1; // sign bit of x
        hx = sx & 0x7fffffff;	// high word of |x|

        // filter out non-finite argument
        if( uword_isnan( hx ) )
        {
            return x + x;	 	// NaN
        }

        if( uword_is_infinite( hx ) )
        {
            return ( xsb == 0 ) ? x : 0.0;		// exp(+-inf)={inf,0}
        }

        if( sx > uword_log_max() )
        {
            return huge * huge; // overflow
        }

        if( sx < 0 && hx > uword_log_min() )
        {
            return twom100 * twom100; // underflow
        }

        // argument reduction
        if( hx > 0x3eb17218 )
        {
            // if  |x| > 0.5 ln2
            if( hx < 0x3F851592 )
            {
                // and |x| < 1.5 ln2
                hi = x - ln2HI[ xsb ];
                lo = ln2LO[ xsb ];
                k = 1 - xsb - xsb;
            }
            else
            {
                k = invln2 * x + halF[ xsb ];
                t = k;
                hi = x - t * ln2HI[ 0 ]; // t*ln2HI is exact here
                lo = t * ln2LO[ 0 ];
            }
            x  = hi - lo;
        }
        else if( hx < 0x31800000 )
        {
            // when |x|<2**-28
            if( huge + x > one )
            {
                return one + x;// trigger inexact
            }
        }
        else
        {
            k = 0;
        }

        // x is now in primary range
        t = x * x;
        c = x - t * ( P1 + t * ( P2 + t * ( P3 + t * ( P4 + t * P5 ) ) ) );
        if( k == 0 )
        {
            return one - ( ( x * c ) / ( c - (float)2.0 ) - x );
        }
        else
        {
            y = one - ( ( lo - ( x * c ) / ( (float)2.0 - c ) ) - hi );
        }

        if( k >= -125 )
        {
            Cmp_unsigned__int32 hy;
            get_float_word( hy, y );
            set_float_word( y, hy + ( k << 23 ) ); // add k to y's exponent
            return y;
        }
        else
        {
            Cmp_unsigned__int32 hy;
            get_float_word( hy, y );
            set_float_word( y, hy + ( ( k + 100 ) << 23 ) ); // add k to y's exponent
            return y * twom100;
        }
    }

};//namespace nsBaseCRT
