
/* @(#)e_atanh.c 5.1 93/09/24 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 *
 */
//Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
/* __ieee754_atanh(x)
 * Method :
 *    1.Reduced x to positive by atanh(-x) = -atanh(x)
 *    2.For x>=0.5
 *                  1              2x                          x
 *	atanh(x) = --- * log(1 + -------) = 0.5 * log1p(2 * --------)
 *                  2             1 - x                      1 - x
 *
 * 	For x<0.5
 *	atanh(x) = 0.5*log1p(2x+2x*x/(1-x))
 *
 * Special cases:
 *	atanh(x) is NaN if |x| > 1 with signal;
 *	atanh(NaN) is that NaN with no signal;
 *	atanh(+-1) is +-INF with signal.
 *
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
    //------------------------------------------------------------------------------
    float Cmath::atanhf( float x )		// wrapper atanhf
    {
        float z, y;
        struct fexception exc;
        z = __ieee754_atanhf( x );
        if( m_fdlib_version == _IEEE_ || isnanf( x ) )
        {
            return z;
        }
        y = fabsf( x );
        if( y >= (float)1.0 )
        {
            if( y > (float)1.0 )
            {
                // atanhf(|x|>1)
                exc.type = EX_DOMAIN;
                exc.name = "atanhf";
                exc.err = 0;
                exc.arg1 = exc.arg2 = (double)x;
                exc.retval = infinity();
                if( m_fdlib_version == _POSIX_ )
                {
                    errno = EDOM;
                }
                else if( !matherr( &exc ) )
                {
                    errno = EDOM;
                }
            }
            else
            {
                // atanhf(|x|=1)
                exc.type = EX_SING;
                exc.name = "atanhf";
                exc.err = 0;
                exc.arg1 = exc.arg2 = (double)x;
                exc.retval = x / 0.0;	// sign(x)*inf
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
    double Cmath::atanh( double x )
    {
        return (double)atanhf( (float)x );
    }

#else

    //------------------------------------------------------------------------------
    double Cmath::atanh( double x )		// wrapper atanh
    {
        double z, y;
        struct fexception exc;
        z = __ieee754_atanh( x );
        if( m_fdlib_version == _IEEE_ || isnan( x ) )
        {
            return z;
        }
        y = fabs( x );
        if( y >= 1.0 )
        {
            if( y > 1.0 )
            {
                // atanh(|x|>1)
                exc.type = EX_DOMAIN;
                exc.name = "atanh";
                exc.err = 0;
                exc.arg1 = exc.arg2 = x;
                exc.retval = infinity();
                if( m_fdlib_version == _POSIX_ )
                {
                    errno = EDOM;
                }
                else if( !matherr( &exc ) )
                {
                    errno = EDOM;
                }
            }
            else
            {
                // atanh(|x|=1)
                exc.type = EX_SING;
                exc.name = "atanh";
                exc.err = 0;
                exc.arg1 = exc.arg2 = x;
                exc.retval = x / 0.0;	// sign(x)*inf
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
    double Cmath::__ieee754_atanh( double x )
    {
        static const double one = 1.0, huge = 1e300;
        static const double zero = 0.0;
        double t;
        Cmp_signed__int32 hx, ix;
        Cmp_unsigned__int32 lx;
        extract_words( hx, lx, x );
        ix = hx & 0x7fffffff;
        if( ( ix | ( ( lx | ( -lx ) ) >> 31 ) ) > 0x3ff00000 ) // |x|>1
        {
            return ( x - x ) / ( x - x );
        }

        if( ix == 0x3ff00000 )
        {
            return x / zero;
        }

        if( ix < 0x3e300000 && ( huge + x ) > zero )
        {
            return x;	// x<2**-28
        }
        set_high_word( x, ix );
        if( ix < 0x3fe00000 )
        {
            // x < 0.5
            t = x + x;
            t = 0.5 * log1p( t + t * x / ( one - x ) );
        }
        else
        {
            t = 0.5 * log1p( ( x + x ) / ( one - x ) );
        }

        if( hx >= 0 )
        {
            return t;
        }
        else
        {
            return -t;
        }
    }

#endif /* defined(_DOUBLE_IS_32BITS) */

    float Cmath::__ieee754_atanhf( float x )
    {
        static const float one = 1.0;
        static const float huge = 1e30;
        static const float zero = 0.0;

        float t;
        Cmp_signed__int32 hx, ix;
        get_float_word( hx, x );
        ix = hx & 0x7fffffff;
        if( ix > 0x3f800000 ) 		// |x|>1
        {
            return ( x - x ) / ( x - x );
        }

        if( ix == 0x3f800000 )
        {
            return x / zero;
        }

        if( ix < 0x31800000 && ( huge + x ) > zero )
        {
            return x;	// x<2**-28
        }

        set_float_word( x, ix );
        if( ix < 0x3f000000 )
        {
            // x < 0.5
            t = x + x;
            t = (float)0.5 * log1pf( t + t * x / ( one - x ) );
        }
        else
        {
            t = (float)0.5 * log1pf( ( x + x ) / ( one - x ) );
        }
        if( hx >= 0 )
        {
            return t;
        }
        else
        {
            return -t;
        }
    }

};//namespace nsBaseCRT
