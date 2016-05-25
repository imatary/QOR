
/* @(#)e_sinh.c 5.1 93/09/24 */
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

/* __ieee754_sinh(x)
 * Method :
 * mathematically sinh(x) if defined to be (exp(x)-exp(-x))/2
 *	1. Replace x by |x| (sinh(-x) = -sinh(x)).
 *	2.
 *		                                    E + E/(E+1)
 *	    0        <= x <= 22     :  sinh(x) := --------------, E=expm1(x)
 *			       			        2
 *
 *	    22       <= x <= lnovft :  sinh(x) := exp(x)/2
 *	    lnovft   <= x <= ln2ovft:  sinh(x) := exp(x/2)/2 * exp(x/2)
 *	    ln2ovft  <  x	    :  sinh(x) := x*shuge (overflow)
 *
 * Special cases:
 *	sinh(x) is |x| if x is +INF, -INF, or NaN.
 *	only sinh(0)=0 is exact for finite x.
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
    //------------------------------------------------------------------------------
    float Cmath::sinhf( float x )
    {
        float z;
        struct fexception exc;
        z = __ieee754_sinhf( x );
        if( m_fdlib_version == _IEEE_ )
        {
            return z;
        }

        if( !finitef( z ) && finitef( x ) )
        {
            // sinhf(finite) overflow
            exc.type = EX_OVERFLOW;
            exc.name = "sinhf";
            exc.err = 0;
            exc.arg1 = exc.arg2 = (double)x;
            if( m_fdlib_version == _SVID_ )
            {
                exc.retval = ( ( x > 0.0 ) ? Huge() : -Huge() );
            }
            else
            {
				exc.retval = ( ( x > 0.0 ) ? nsPlatform::HugeValueF : -nsPlatform::HugeValueF );
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
            return (float)exc.retval;
        }
        else
        {
            return z;
        }
    }

#ifdef _DOUBLE_IS_32BITS

    //------------------------------------------------------------------------------
    double Cmath::sinh( double x )
    {
        return (double)sinhf( (float)x );
    }

#else

    //------------------------------------------------------------------------------
    double Cmath::sinh( double x )
    {
        double z;
        struct fexception exc;
        z = __ieee754_sinh( x );
        if( m_fdlib_version == _IEEE_ )
        {
            return z;
        }
        if( !finite( z ) && finite( x ) )
        {
            // sinh(finite) overflow
#	ifndef HUGE_VAL
#		define HUGE_VAL inf
            double inf = 0.0;

            set_high_word( inf, 0x7ff00000 ); // set inf to infinite
#	endif
            exc.type = EX_OVERFLOW;
            exc.name = "sinh";
            exc.err = 0;
            exc.arg1 = exc.arg2 = x;
            if( m_fdlib_version == _SVID_ )
            {
                exc.retval = ( ( x > 0.0 ) ? Huge() : -Huge() );
            }
            else
            {
                exc.retval = ( ( x > 0.0 ) ? HUGE_VAL : -HUGE_VAL );
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
        else
        {
            return z;
        }
    }

    //------------------------------------------------------------------------------
    double Cmath::__ieee754_sinh( double x )
    {
        static const double one = 1.0;
        static const double shuge = 1.0e307;
        double t, w, h;
        Cmp_signed__int32 ix, jx;
        Cmp_unsigned__int32 lx;

        // High word of |x|.
        get_high_word( jx, x );
        ix = jx & 0x7fffffff;

        // x is INF or NaN
        if( ix >= 0x7ff00000 )
        {
            return x + x;
        }

        h = 0.5;
        if( jx < 0 )
        {
            h = -h;
        }

        // |x| in [0,22], return sign(x)*0.5*(E+E/(E+1)))
        if( ix < 0x40360000 )
        {
            // |x|<22
            if( ix < 0x3e300000 ) 		// |x|<2**-28
            {
                if( shuge + x > one )
                {
                    return x; // sinh(tiny) = tiny with inexact
                }
            }

            t = expm1( fabs( x ) );
            if( ix < 0x3ff00000 )
            {
                return h * ( 2.0 * t - t * t / ( t + one ) );
            }
            return h * ( t + t / ( t + one ) );
        }

        // |x| in [22, log(maxdouble)] return 0.5*exp(|x|)
        if( ix < 0x40862E42 )
        {
            return h * __ieee754_exp( fabs( x ) );
        }

        // |x| in [log(maxdouble), overflowthresold]
        get_low_word( lx, x );

        if( ix < 0x408633CE || ( ix == 0x408633ce && lx <= (Cmp_unsigned__int32)0x8fb9f87d ) )
        {
            w = __ieee754_exp( 0.5 * fabs( x ) );
            t = h * w;
            return t * w;
        }

        // |x| > overflowthresold, sinh(x) overflow
        return x * shuge;
    }

#endif /* defined(_DOUBLE_IS_32BITS) */

    //------------------------------------------------------------------------------
    float Cmath::__ieee754_sinhf( float x )
    {
        static const float one = 1.0;
        static const float shuge = 1.0e37;
        float t, w, h;
        Cmp_signed__int32 ix, jx;

        get_float_word( jx, x );
        ix = jx & 0x7fffffff;

        // x is INF or NaN
        if( !uword_isfinite( ix ) )
        {
            return x + x;
        }

        h = 0.5;
        if( jx < 0 )
        {
            h = -h;
        }

        // |x| in [0,22], return sign(x)*0.5*(E+E/(E+1)))
        if( ix < 0x41b00000 )
        {
            // |x|<22
            if( ix < 0x31800000 ) 		// |x|<2**-28
            {
                if( shuge + x > one )
                {
                    return x; // sinh(tiny) = tiny with inexact
                }
            }
            t = expm1f( fabsf( x ) );
            if( ix < 0x3f800000 )
            {
                return h * ( (float)2.0 * t - t * t / ( t + one ) );
            }
            return h * ( t + t / ( t + one ) );
        }

        // |x| in [22, log(maxdouble)] return 0.5*exp(|x|)
        if( ix <= uword_log_max() )
        {
            return h * __ieee754_expf( fabsf( x ) );
        }

        // |x| in [log(maxdouble), overflowthresold]
        if( ix <= uword_log2_max() )
        {
            w = __ieee754_expf( (float)0.5 * fabsf( x ) );
            t = h * w;
            return t * w;
        }

        // |x| > overflowthresold, sinh(x) overflow
        return x * shuge;
    }

};//namespace nsBaseCRT
