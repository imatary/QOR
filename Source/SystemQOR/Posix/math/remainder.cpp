
/* @(#)e_remainder.c 5.1 93/09/24 */
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
/* __ieee754_remainder(x,p)
 * Return :
 * 	returns  x REM p  =  x - [x/p]*p as if in infinite
 * 	precise arithmetic, where [x/p] is the (infinite bit)
 *	integer nearest x/p (in half way case choose the even one).
 * Method :
 *	Based on fmod() return x-[x/p]chopped*p exactlp.
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
    //------------------------------------------------------------------------------
    float Cmath::remainderf( float x, float y )
    {
        float z;
        struct fexception exc;
        z = __ieee754_remainderf( x, y );
        if( m_fdlib_version == _IEEE_ || isnanf( y ) )
        {
            return z;
        }

        if( y == (float)0.0 )
        {
            // remainderf(x,0)
            exc.type = EX_DOMAIN;
            exc.name = "remainderf";
            exc.err = 0;
            exc.arg1 = (double)x;
            exc.arg2 = (double)y;
            exc.retval = infinity();
            if( m_fdlib_version == _POSIX_ )
            {
                errno = EDOM;
            }
            else if( !matherr( &exc ) )
            {
                errno = EDOM;
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
    double Cmath::remainder( double x, double y )
    {
        return (double)remainderf( (float)x, (float)y );
    }

#else

    //------------------------------------------------------------------------------
    double Cmath::remainder( double x, double y )
    {
        double z;
        struct fexception exc;
        z = __ieee754_remainder( x, y );
        if( m_fdlib_version == _IEEE_ || isnan( y ) )
        {
            return z;
        }
        if( y == 0.0 )
        {
            // remainder(x,0)
            exc.type = EX_DOMAIN;
            exc.name = "remainder";
            exc.err = 0;
            exc.arg1 = x;
            exc.arg2 = y;
            exc.retval = infinity();
            if( m_fdlib_version == _POSIX_ )
            {
                errno = EDOM;
            }
            else if( !matherr( &exc ) )
            {
                errno = EDOM;
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
    double Cmath::__ieee754_remainder( double x, double p )
    {
        static const double zero = 0.0;
        Cmp_signed__int32 hx, hp;
        Cmp_unsigned__int32 sx, lx, lp;
        double p_half;

        extract_words( hx, lx, x );
        extract_words( hp, lp, p );
        sx = hx & 0x80000000;
        hp &= 0x7fffffff;
        hx &= 0x7fffffff;

        // purge off exception values
        if( ( hp | lp ) == 0 )
        {
            return ( x * p ) / ( x * p ); // p = 0
        }

        if( ( hx >= 0x7ff00000 ) ||			// x not finite
            ( ( hp >= 0x7ff00000 ) &&		// p is NaN
            ( ( ( hp - 0x7ff00000 ) | lp ) != 0 ) ) )
        {
            return ( x * p ) / ( x * p );
        }

        if( hp <= 0x7fdfffff )
        {
            x = __ieee754_fmod( x, p + p ); // now x < 2p
        }

        if( ( ( hx - hp ) | ( lx - lp ) ) == 0 )
        {
            return zero * x;
        }

        x = fabs( x );
        p = fabs( p );

        if( hp < 0x00200000 )
        {
            if( x + x > p )
            {
                x -= p;
                if( x + x >= p )
                {
                    x -= p;
                }
            }
        }
        else
        {
            p_half = 0.5 * p;
            if( x > p_half )
            {
                x -= p;
                if( x >= p_half )
                {
                    x -= p;
                }
            }
        }
        get_high_word( hx, x );
        set_high_word( x, hx ^ sx );
        return x;
    }

#endif//defined(_DOUBLE_IS_32BITS)

    //------------------------------------------------------------------------------
    float Cmath::__ieee754_remainderf( float x, float p )
    {
        static const float zero = 0.0;
        Cmp_signed__int32 hx, hp;
        Cmp_unsigned__int32 sx;
        float p_half;

        get_float_word( hx, x );
        get_float_word( hp, p );
        sx = hx & 0x80000000;
        hp &= 0x7fffffff;
        hx &= 0x7fffffff;

        // purge off exception values
        if( uword_is_zero( hp ) || !uword_isfinite( hx ) || uword_isnan( hp ) )
        {
            return ( x * p ) / ( x * p );
        }

        if( hp <= uword_half_max() )
        {
            x = __ieee754_fmodf( x, p + p ); // now x < 2p
        }

        if( ( hx - hp ) == 0 )
        {
            return zero * x;
        }

        x = fabsf( x );
        p = fabsf( p );
        if( hp < 0x01000000 )
        {
            if( x + x > p )
            {
                x -= p;
                if( x + x >= p )
                {
                    x -= p;
                }
            }
        }
        else
        {
            p_half = (float)0.5*p;
            if( x > p_half )
            {
                x -= p;
                if( x >= p_half )
                {
                    x -= p;
                }
            }
        }
        get_float_word( hx, x );
        set_float_word( x, hx ^ sx );
        return x;
    }

};//namespace nsBaseCRT
