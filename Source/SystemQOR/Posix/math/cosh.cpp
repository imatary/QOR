
/* @(#)e_cosh.c 5.1 93/09/24 */
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
/* __ieee754_cosh(x)
 * Method :
 * mathematically cosh(x) if defined to be (exp(x)+exp(-x))/2
 *	1. Replace x by |x| (cosh(x) = cosh(-x)).
 *	2.
 *		                                        [ exp(x) - 1 ]^2
 *	    0        <= x <= ln2/2  :  cosh(x) := 1 + -------------------
 *			       			           2*exp(x)
 *
 *		                                  exp(x) +  1/exp(x)
 *	    ln2/2    <= x <= 22     :  cosh(x) := -------------------
 *			       			          2
 *	    22       <= x <= lnovft :  cosh(x) := exp(x)/2
 *	    lnovft   <= x <= ln2ovft:  cosh(x) := exp(x/2)/2 * exp(x/2)
 *	    ln2ovft  <  x	    :  cosh(x) := huge*huge (overflow)
 *
 * Special cases:
 *	cosh(x) is |x| if x is +INF, -INF, or NaN.
 *	only cosh(0)=1 is exact for finite x.
 */

#include "SystemQOR/Posix/Basemath.h"
#include <math.h>

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
    //------------------------------------------------------------------------------
    float Cmath::coshf( float x ) // wrapper coshf
    {
        float z;
        struct fexception exc;
        z = __ieee754_coshf( x );
        if( m_fdlib_version == _IEEE_ || isnanf( x ) )
        {
            return z;
        }

        if( fabsf( x ) > (float)8.9415985107e+01 )
        {
            // coshf(finite) overflow
            exc.type = EX_OVERFLOW;
            exc.name = "coshf";
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
            return (float)exc.retval;
        }
        else
        {
            return z;
        }
    }

    //------------------------------------------------------------------------------
#ifdef _DOUBLE_IS_32BITS

    //------------------------------------------------------------------------------
    double Cmath::cosh( double x )
    {
        return (double)coshf( (float)x );
    }

#else

    //------------------------------------------------------------------------------
    double Cmath::cosh( double x ) // wrapper cosh
    {
        double z;
        struct fexception exc;
        z = __ieee754_cosh( x );
        if( m_fdlib_version == _IEEE_ || isnan( x ) )
        {
            return z;
        }

        if( fabs( x ) > 7.10475860073943863426e+02 )
        {
            // cosh(finite) overflow
            exc.type = EX_OVERFLOW;
            exc.name = "cosh";
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
        else
        {
            return z;
        }
    }

    //------------------------------------------------------------------------------
    double Cmath::__ieee754_cosh( double x )
    {
        static const double one = 1.0;
        static const double half = 0.5;
        static const double huge = 1.0e300;

        double t,w;
        Cmp_signed__int32 ix;
        Cmp_unsigned__int32 lx;

        // High word of |x|.
        get_high_word( ix, x );
        ix &= 0x7fffffff;

        // x is INF or NaN
        if( ix >= 0x7ff00000 )
        {
            return x * x;
        }

        // |x| in [0,0.5*ln2], return 1+expm1(|x|)^2/(2*exp(|x|))
        if( ix < 0x3fd62e43 )
        {
            t = expm1( fabs( x ) );
            w = one + t;
            if( ix < 0x3c800000 )
            {
                return w;	// cosh(tiny) = 1
            }
            return one + ( t * t ) / ( w + w );
        }

        // |x| in [0.5*ln2,22], return (exp(|x|)+1/exp(|x|)/2;
        if( ix < 0x40360000 )
        {
            t = __ieee754_exp( fabs( x ) );
            return half * t + half / t;
        }

        // |x| in [22, log(maxdouble)] return half*exp(|x|)
        if( ix < 0x40862E42 )
        {
            return half * __ieee754_exp( fabs( x ) );
        }

        // |x| in [log(maxdouble), overflowthresold]
        get_low_word( lx, x );
        if( ix < 0x408633CE || ( ix == 0x408633ce && lx <= (Cmp_unsigned__int32)0x8fb9f87d ) )
        {
            w = __ieee754_exp( half * fabs( x ) );
            t = half * w;
            return t * w;
        }

        // |x| > overflowthresold, cosh(x) overflow
        return huge * huge;
    }

#endif//defined(_DOUBLE_IS_32BITS)

    //------------------------------------------------------------------------------
    float Cmath::__ieee754_coshf( float x )
    {
        static const float one = 1.0;
        static const float half = 0.5;
        static const float huge = 1.0e30;

        float t, w;
        Cmp_signed__int32 ix;

        get_float_word( ix, x );
        ix &= 0x7fffffff;

        // x is INF or NaN
        if( !uword_isfinite( ix ) )
        {
            return x * x;
        }

        // |x| in [0,0.5*ln2], return 1+expm1(|x|)^2/(2*exp(|x|))
        if( ix < 0x3eb17218 )
        {
            t = expm1f( fabsf( x ) );
            w = one + t;
            if( ix < 0x24000000 )
            {
                return w;	// cosh(tiny) = 1
            }
            return one + ( t * t ) / ( w + w );
        }

        // |x| in [0.5*ln2,22], return (exp(|x|)+1/exp(|x|)/2;
        if( ix < 0x41b00000 )
        {
            t = __ieee754_expf( fabsf( x ) );
            return half * t + half / t;
        }

        // |x| in [22, log(maxdouble)] return half*exp(|x|)
        if( ix <= uword_log_max() )
        {
            return half * __ieee754_expf( fabsf( x ) );
        }

        // |x| in [log(maxdouble), overflowthresold]
        if( ix <= uword_log2_max() )
        {
            w = __ieee754_expf( half * fabsf( x ) );
            t = half * w;
            return t * w;
        }

        // |x| > overflowthresold, cosh(x) overflow
        return huge * huge;
    }

};//namespace nsBaseCRT
