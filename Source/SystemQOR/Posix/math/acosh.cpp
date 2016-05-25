
/* @(#)e_acosh.c 5.1 93/09/24 */
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

/* __ieee754_acosh(x)
 * Method :
 *	Based on
 *		acosh(x) = log [ x + sqrt(x*x-1) ]
 *	we have
 *		acosh(x) := log(x)+ln2,	if x is large; else
 *		acosh(x) := log(2x-1/(sqrt(x*x-1)+x)) if x>2; else
 *		acosh(x) := log1p(t+sqrt(2.0*t+t*t)); where t=x-1.
 *
 * Special cases:
 *	acosh(x) is NaN with signal if x<1.
 *	acosh(NaN) is NaN without signal.
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
    //------------------------------------------------------------------------------
    float Cmath::__ieee754_acoshf( float x )
    {
        static const float one	= 1.0;
        static const float ln2	= 6.9314718246e-01;  // 0x3f317218

        float t;
        Cmp_signed__int32 hx;
        get_float_word( hx, x );
        if( hx < 0x3f800000 )
        {
            // x < 1
            return ( x - x ) / ( x - x );
        }
        else if( hx >= 0x4d800000 )
        {
            // x > 2**28
            if( !uword_isfinite( hx ) )
            {
                // x is inf of NaN
                return x + x;
            }
            else
            {
                return __ieee754_logf( x ) + ln2; // acosh(huge)=log(2x)
            }
        }
        else if ( hx == 0x3f800000 )
        {
            return 0.0; // acosh(1) = 0
        }
        else if ( hx > 0x40000000 )
        {
            // 2**28 > x > 2
            t = x * x;
            return __ieee754_logf( (float)2.0 * x - one / ( x + __ieee754_sqrtf( t - one ) ) );
        }
        else
        {
            // 1<x<2
            t = x - one;
            return log1pf( t + __ieee754_sqrtf( (float)2.0 * t + t * t ) );
        }
    }

    //------------------------------------------------------------------------------
    float Cmath::acoshf( float x ) // wrapper acoshf
    {
        float z;
        struct fexception exc;
        z = __ieee754_acoshf( x );
        if( m_fdlib_version == _IEEE_ || isnanf( x ) )
        {
            return z;
        }
        if( x < (float)1.0 )
        {
            // acoshf(x<1)
            exc.type = EX_DOMAIN;
            exc.name = "acoshf";
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
    double Cmath::acosh( double x )
    {
        return (double)acoshf( (float)x );
    }

#else

    //------------------------------------------------------------------------------
    double Cmath::acosh( double x ) // wrapper acosh
    {
        double z;
        struct fexception exc;
        z = __ieee754_acosh( x );
        if( m_fdlib_version == _IEEE_ || isnan( x ) )
        {
            return z;
        }
        if( x < 1.0 )
        {
            // acosh(x<1)
            exc.type = EX_DOMAIN;
            exc.name = "acosh";
            exc.err = 0;
            exc.arg1 = exc.arg2 = x;
            exc.retval = infinity();
            if( m_fdlib_version == _POSIX_ )
            {
                errno = EDOM;
            }
            else if ( !matherr( &exc ) )
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
    double Cmath::__ieee754_acosh( double x )
    {
        static const double one	= 1.0;
        static const double ln2	= 6.93147180559945286227e-01;  // 0x3FE62E42, 0xFEFA39EF

        double t;
        Cmp_signed__int32 hx;
        Cmp_unsigned__int32 lx;
        extract_words( hx, lx, x );
        if( hx < 0x3ff00000 )
        {
            // x < 1
            return ( x - x ) / ( x - x );
        }
        else if( hx >= 0x41b00000 )
        {
            // x > 2**28
            if( hx >= 0x7ff00000 )
            {
                // x is inf of NaN
                return x + x;
            }
            else
            {
                return __ieee754_log( x ) + ln2; // acosh(huge)=log(2x)
            }
        }
        else if( ( ( hx - 0x3ff00000 ) | lx ) == 0 )
        {
            return 0.0; // acosh(1) = 0
        }
        else if( hx > 0x40000000 )
        {
            // 2**28 > x > 2
            t = x * x;
            return __ieee754_log( 2.0 * x - one / ( x + __ieee754_sqrt( t - one ) ) );
        }
        else
        {
            // 1<x<2
            t = x - one;
            return log1p( t + __ieee754_sqrt( 2.0 * t + t * t ) );
        }
    }

#endif//defined(_DOUBLE_IS_32BITS)

};//namespace nsBaseCRT
