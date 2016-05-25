
/* @(#)e_log10.c 5.1 93/09/24 */
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
/* __ieee754_log10(x)
 * Return the base 10 logarithm of x
 *
 * Method :
 *	Let log10_2hi = leading 40 bits of log10(2) and
 *	    log10_2lo = log10(2) - log10_2hi,
 *	    ivln10   = 1/log(10) rounded.
 *	Then
 *		n = ilogb(x),
 *		if(n<0)  n = n+1;
 *		x = scalbn(x,-n);
 *		log10(x) := n*log10_2hi + (n*log10_2lo + ivln10*log(x))
 *
 * Note 1:
 *	To guarantee log10(10**n)=n, where 10**n is normal, the rounding
 *	mode must set to Round-to-Nearest.
 * Note 2:
 *	[1/log(10)] rounded to 53 bits has error  .198   ulps;
 *	log10 is monotonic at all binary break points.
 *
 * Special cases:
 *	log10(x) is NaN with signal if x < 0;
 *	log10(+INF) is +INF with no signal; log10(0) is -INF with signal;
 *	log10(NaN) is that NaN with no signal;
 *	log10(10**N) = N  for N=0,1,...,22.
 *
 * Constants:
 * The hexadecimal values are the intended ones for the following constants.
 * The decimal values may be used, provided that the compiler will convert
 * from decimal to binary accurately enough to produce the hexadecimal values
 * shown.
 */

#include "SystemQOR/Posix/Basemath.h"
#include <math.h>

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
    //------------------------------------------------------------------------------
    float Cmath::log10f( float x )
    {
        float z;
        struct fexception exc;
        z = __ieee754_log10f( x );
        if( m_fdlib_version == _IEEE_ || isnanf( x ) )
        {
            return z;
        }

        if( x <= (float)0.0 )
        {
            exc.name = "log10f";
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
                // log10f(0)
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
                // log10f(x<0)
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
        else
        {
            return z;
        }
    }

#ifdef _DOUBLE_IS_32BITS

    //------------------------------------------------------------------------------
    double Cmath::log10( double x )
    {
        return (double)log10f( (float)x );
    }

#else

    //------------------------------------------------------------------------------
    double Cmath::log10( double x )
    {
        double z;
        struct fexception exc;
        z = __ieee754_log10( x );
        if( m_fdlib_version == _IEEE_ || isnan( x ) )
        {
            return z;
        }

        if( x <= 0.0 )
        {
#	ifndef HUGE_VAL
#		define HUGE_VAL inf
            double inf = 0.0;

            set_high_word( inf, 0x7ff00000 ); // set inf to infinite
#	endif
            exc.name = "log10";
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
                // log10(0)
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
                // log10(x<0)
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
        else
        {
            return z;
        }
    }

    //------------------------------------------------------------------------------
    double Cmath::__ieee754_log10( double x )
    {
        static const double two54		=  1.80143985094819840000e+16; // 0x43500000, 0x00000000
        static const double ivln10		=  4.34294481903251816668e-01; // 0x3FDBCB7B, 0x1526E50E
        static const double log10_2hi	=  3.01029995663611771306e-01; // 0x3FD34413, 0x509F6000
        static const double log10_2lo	=  3.69423907715893078616e-13; // 0x3D59FEF3, 0x11F12B36
        static const double zero		=  0.0;

        double y,z;
        Cmp_signed__int32 i, k, hx;
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

            if ( hx < 0 )
            {
                return ( x - x ) / zero; // log(-#) = NaN
            }

            k -= 54;
            x *= two54; // subnormal number, scale up x
            get_high_word( hx, x );
        }

        if( hx >= 0x7ff00000 )
        {
            return x+x;
        }

        k += ( hx >> 20 ) - 1023;
        i  = ( (Cmp_unsigned__int32) k & 0x80000000 ) >> 31;
        hx = ( hx & 0x000fffff ) | ( ( 0x3ff - i ) << 20 );
        y  = (double)( k + i );
        set_high_word( x, hx );
        z  = y * log10_2lo + ivln10 * __ieee754_log( x );
        return z + y * log10_2hi;
    }

#endif//defined(_DOUBLE_IS_32BITS)


    //------------------------------------------------------------------------------
    float Cmath::__ieee754_log10f( float x )
    {
        static const float two25      =  3.3554432000e+07; // 0x4c000000
        static const float ivln10     =  4.3429449201e-01; // 0x3ede5bd9
        static const float log10_2hi  =  3.0102920532e-01; // 0x3e9a2080
        static const float log10_2lo  =  7.9034151668e-07; // 0x355427db
        static const float zero   =  0.0;

        float y,z;
        Cmp_signed__int32 i, k, hx;

        get_float_word( hx, x );

        k = 0;
        if( uword_is_zero( hx & 0x7fffffff ) )
        {
            return -two25 / zero; // log(+-0)=-inf
        }

        if( hx < 0 )
        {
            return ( x - x ) / zero; // log(-#) = NaN
        }

        if( !uword_isfinite( hx ) )
        {
            return x + x;
        }

        if( uword_is_subnormal( hx ) )
        {
            k -= 25;
            x *= two25; // subnormal number, scale up x
            get_float_word( hx, x );
        }

        k += ( hx >> 23 ) - 127;
        i  = ( (Cmp_unsigned__int32)k & 0x80000000 ) >> 31;
        hx = ( hx & 0x007fffff ) | ( ( 0x7f - i ) << 23 );
        y  = (float)( k + i );
        set_float_word( x, hx );
        z  = y * log10_2lo + ivln10 * __ieee754_logf( x );
        return  z + y * log10_2hi;
    }

};//namespace nsBaseCRT
