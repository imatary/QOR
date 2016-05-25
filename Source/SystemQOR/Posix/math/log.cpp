
/* @(#)e_log.c 5.1 93/09/24 */
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
/* __ieee754_log(x)
 * Return the logrithm of x
 *
 * Method :
 *   1. Argument Reduction: find k and f such that
 *			x = 2^k * (1+f),
 *	   where  sqrt(2)/2 < 1+f < sqrt(2) .
 *
 *   2. Approximation of log(1+f).
 *	Let s = f/(2+f) ; based on log(1+f) = log(1+s) - log(1-s)
 *		 = 2s + 2/3 s**3 + 2/5 s**5 + .....,
 *	     	 = 2s + s*R
 *      We use a special Reme algorithm on [0,0.1716] to generate
 * 	a polynomial of degree 14 to approximate R The maximum error
 *	of this polynomial approximation is bounded by 2**-58.45. In
 *	other words,
 *		        2      4      6      8      10      12      14
 *	    R(z) ~ Lg1*s +Lg2*s +Lg3*s +Lg4*s +Lg5*s  +Lg6*s  +Lg7*s
 *  	(the values of Lg1 to Lg7 are listed in the program)
 *	and
 *	    |      2          14          |     -58.45
 *	    | Lg1*s +...+Lg7*s    -  R(z) | <= 2
 *	    |                             |
 *	Note that 2s = f - s*f = f - hfsq + s*hfsq, where hfsq = f*f/2.
 *	In order to guarantee error in log below 1ulp, we compute log
 *	by
 *		log(1+f) = f - s*(f - R)	(if f is not too large)
 *		log(1+f) = f - (hfsq - s*(hfsq+R)).	(better accuracy)
 *
 *	3. Finally,  log(x) = k*ln2 + log(1+f).
 *			    = k*ln2_hi+(f-(hfsq-(s*(hfsq+R)+k*ln2_lo)))
 *	   Here ln2 is split into two floating point number:
 *			ln2_hi + ln2_lo,
 *	   where n*ln2_hi is always exact for |n| < 2000.
 *
 * Special cases:
 *	log(x) is NaN with signal if x < 0 (including -INF) ;
 *	log(+INF) is +INF; log(0) is -INF with signal;
 *	log(NaN) is that NaN with no signal.
 *
 * Accuracy:
 *	according to an error analysis, the error is always less than
 *	1 ulp (unit in the last place).
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
    float Cmath::logf( float x ) // wrapper logf
    {
        float z;
        struct fexception exc;
        z = __ieee754_logf( x );
        if( m_fdlib_version == _IEEE_ || isnanf( x ) || x > (float)0.0 )
        {
            return z;
        }

        exc.name = "logf";
        exc.err = 0;
        exc.arg1 = exc.arg2 = (double)x;
        if( m_fdlib_version == _SVID_ )
        {
            exc.retval = -Huge();
        }
        else
        {
            exc.retval = -HUGE_VAL;
        }

        if( x == (float)0.0 )
        {
            // logf(0)
            exc.type = EX_SING;
            if( m_fdlib_version == _POSIX_ )
            {
                errno = ERANGE;
            }
            else if( !matherr( &exc ) )
            {
                errno = EDOM;
            }
        }
        else
        {
            // logf(x<0)
            exc.type = EX_DOMAIN;
            if( m_fdlib_version == _POSIX_ )
            {
                errno = EDOM;
            }
            else if( !matherr( &exc ) )
            {
                errno = EDOM;
            }
        }

        if( exc.err != 0 )
        {
            errno = exc.err;
        }
        return (float)exc.retval;
    }

#ifdef _DOUBLE_IS_32BITS

    //------------------------------------------------------------------------------
    double Cmath::log(double x)
    {
        return (double)logf( (float)x );
    }

#else

    //------------------------------------------------------------------------------
    double Cmath::log( double x )
    {
        double z;
        struct fexception exc;
        z = __ieee754_log( x );
        if( m_fdlib_version == _IEEE_ || isnan( x ) || x > 0.0 )
        {
            return z;
        }
        exc.name = "log";
        exc.err = 0;
        exc.arg1 = x;
        exc.arg2 = x;
        if( m_fdlib_version == _SVID_ )
        {
            exc.retval = -Huge();
        }
        else
        {
            exc.retval = -HUGE_VAL;
        }

        if( x == 0.0 )
        {
            // log(0)
            exc.type = EX_SING;
            if( m_fdlib_version == _POSIX_ )
            {
                errno = ERANGE;
            }
            else if( !matherr( &exc ) )
            {
                errno = EDOM;
            }
        }
        else
        {
            // log(x<0)
            exc.type = EX_DOMAIN;
            if( m_fdlib_version == _POSIX_ )
            {
                errno = EDOM;
            }
            else if( !matherr( &exc ) )
            {
                errno = EDOM;
            }
        }

        if( exc.err != 0 )
        {
            errno = exc.err;
        }
        return exc.retval;
    }

    //------------------------------------------------------------------------------
    double Cmath::__ieee754_log( double x )
    {
        static const double ln2_hi  =  6.93147180369123816490e-01;	// 3fe62e42 fee00000
        static const double ln2_lo  =  1.90821492927058770002e-10;	// 3dea39ef 35793c76
        static const double two54   =  1.80143985094819840000e+16;  // 43500000 00000000
        static const double Lg1 = 6.666666666666735130e-01;  // 3FE55555 55555593
        static const double Lg2 = 3.999999999940941908e-01;  // 3FD99999 9997FA04
        static const double Lg3 = 2.857142874366239149e-01;  // 3FD24924 94229359
        static const double Lg4 = 2.222219843214978396e-01;  // 3FCC71C5 1D8E78AF
        static const double Lg5 = 1.818357216161805012e-01;  // 3FC74664 96CB03DE
        static const double Lg6 = 1.531383769920937332e-01;  // 3FC39A09 D078C69F
        static const double Lg7 = 1.479819860511658591e-01;  // 3FC2F112 DF3E5244
        static const double zero =  0.0;

        double hfsq, f, s, z, R, w, t1, t2, dk;
        Cmp_signed__int32 k, hx, i, j;
        Cmp_unsigned__int32 lx;

        extract_words( hx, lx, x );

        k = 0;
        if( hx < 0x00100000 )
        {
            // x < 2**-1022
            if( ( ( hx & 0x7fffffff ) | lx ) == 0 )
            {
                return -two54 / zero; // log(+-0)=-inf
            }

            if( hx < 0 )
            {
                return ( x - x ) / zero; // log(-#) = NaN
            }
            k -= 54;
            x *= two54; // subnormal number, scale up x
            get_high_word( hx, x );
        }

        if( hx >= 0x7ff00000 )
        {
            return x + x;
        }

        k += ( hx >> 20 ) - 1023;
        hx &= 0x000fffff;
        i = ( hx + 0x95f64 ) & 0x100000;
        set_high_word( x, hx | ( i ^ 0x3ff00000 ) ); // normalize x or x/2
        k += ( i >> 20 );
        f = x - 1.0;
        if( ( 0x000fffff & ( 2 + hx ) ) < 3 )
        {
            // |f| < 2**-20
            if( f == zero )
            {
                if( k == 0 )
                {
                    return zero;
                }
                else
                {
                    dk = (double)k;
                    return dk * ln2_hi + dk * ln2_lo;
                }
            }
            R = f * f * ( 0.5 - 0.33333333333333333 * f );
            if( k == 0 )
            {
                return f - R;
            }
            else
            {
                dk = (double)k;
                return dk * ln2_hi - ( ( R - dk * ln2_lo ) - f );
            }
        }
        s = f / ( 2.0 + f );
        dk = (double)k;
        z = s * s;
        i = hx - 0x6147a;
        w = z * z;
        j = 0x6b851 - hx;
        t1 = w * ( Lg2 + w * ( Lg4 + w * Lg6 ) );
        t2 = z * ( Lg1 + w * ( Lg3 + w * ( Lg5 + w * Lg7 ) ) );
        i |= j;
        R = t2 + t1;
        if( i > 0 )
        {
            hfsq = 0.5 * f * f;
            if( k == 0 )
            {
                return f - ( hfsq - s * ( hfsq + R ) ) ;
            }
            else
            {
                return dk * ln2_hi - ( ( hfsq - ( s * ( hfsq + R ) + dk * ln2_lo ) ) - f );
            }
        }
        else
        {
            if( k == 0 )
            {
                return f - s * ( f - R );
            }
            else
            {
                return dk * ln2_hi - ( ( s * ( f - R ) - dk * ln2_lo ) - f );
            }
        }
    }

#endif //defined(_DOUBLE_IS_32BITS)

    //------------------------------------------------------------------------------
    float Cmath::__ieee754_logf( float x )
    {
        static const float ln2_hi =   6.9313812256e-01;	// 0x3f317180
        static const float ln2_lo =   9.0580006145e-06;	// 0x3717f7d1
        static const float two25 =    3.355443200e+07;	// 0x4c000000
        static const float Lg1 = 6.6666668653e-01;	// 3F2AAAAB
        static const float Lg2 = 4.0000000596e-01;	// 3ECCCCCD
        static const float Lg3 = 2.8571429849e-01; // 3E924925
        static const float Lg4 = 2.2222198546e-01; // 3E638E29
        static const float Lg5 = 1.8183572590e-01; // 3E3A3325
        static const float Lg6 = 1.5313838422e-01; // 3E1CD04F
        static const float Lg7 = 1.4798198640e-01; // 3E178897
        static const float zero =  0.0;

        float hfsq, f, s, z, R, w, t1, t2, dk;
        Cmp_signed__int32 k, ix, i, j;

        get_float_word( ix, x );

        k = 0;
        if( uword_is_zero( ix & 0x7fffffff ) )
        {
            return -two25 / zero; // log(+-0)=-inf
        }

        if( ix < 0 )
        {
            return ( x - x ) / zero; // log(-#) = NaN
        }

        if( !uword_isfinite( ix ) )
        {
            return x + x;
        }

        if( uword_is_subnormal( ix ) )
        {
            k -= 25; x *= two25; // subnormal number, scale up x
            get_float_word( ix, x );
        }

        k += ( ix >> 23 ) - 127;
        ix &= 0x007fffff;
        i = ( ix + ( 0x95f64 << 3 ) ) & 0x800000;
        set_float_word( x, ix | ( i ^ 0x3f800000 ) ); // normalize x or x/2
        k += ( i >> 23 );
        f = x - (float)1.0;
        if( ( 0x007fffff & ( 15 + ix ) ) < 16 )
        {
            // |f| < 2**-20
            if( f == zero )
            {
                if( k == 0 )
                {
                    return zero;
                }
                else
                {
                    dk = (float)k;
                    return dk * ln2_hi + dk * ln2_lo;
                }
            }

            R = f * f * ( (float)0.5 - (float)0.33333333333333333 * f );
            if( k == 0 )
            {
                return f - R;
            }
            else
            {
                dk = (float)k;
                return dk * ln2_hi - ( ( R - dk * ln2_lo ) - f );
            }
        }

        s = f / ( (float)2.0 + f );
        dk = (float)k;
        z = s * s;
        i = ix - ( 0x6147a << 3 );
        w = z * z;
        j = ( 0x6b851 << 3 ) - ix;
        t1= w * ( Lg2 + w * ( Lg4 + w * Lg6 ) );
        t2= z * ( Lg1 + w * ( Lg3 + w * ( Lg5 + w * Lg7 ) ) );
        i |= j;
        R = t2 + t1;
        if( i > 0 )
        {
            hfsq = (float)0.5 * f * f;
            if( k == 0 )
            {
                return f - ( hfsq - s * ( hfsq + R ) );
            }
            else
            {
                return dk * ln2_hi - ( ( hfsq - ( s * ( hfsq + R ) + dk * ln2_lo ) ) - f );
            }
        }
        else
        {
            if ( k == 0 )
            {
                return f - s * ( f - R );
            }
            else
            {
                return dk * ln2_hi - ( ( s * ( f - R ) - dk * ln2_lo ) - f );
            }
        }
    }

};//namespace nsBaseCRT
