
/* @(#)e_asin.c 5.1 93/09/24 */
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

/* __ieee754_asin(x)
 * Method :
 *	Since  asin(x) = x + x^3/6 + x^5*3/40 + x^7*15/336 + ...
 *	we approximate asin(x) on [0,0.5] by
 *		asin(x) = x + x*x^2*R(x^2)
 *	where
 *		R(x^2) is a rational approximation of (asin(x)-x)/x^3
 *	and its remez error is bounded by
 *		|(asin(x)-x)/x^3 - R(x^2)| < 2^(-58.75)
 *
 *	For x in [0.5,1]
 *		asin(x) = pi/2-2*asin(sqrt((1-x)/2))
 *	Let y = (1-x), z = y/2, s := sqrt(z), and pio2_hi+pio2_lo=pi/2;
 *	then for x>0.98
 *		asin(x) = pi/2 - 2*(s+s*z*R(z))
 *			= pio2_hi - (2*(s+s*z*R(z)) - pio2_lo)
 *	For x<=0.98, let pio4_hi = pio2_hi/2, then
 *		f = hi part of s;
 *		c = sqrt(z) - f = (z-f*f)/(s+f) 	...f+c=sqrt(z)
 *	and
 *		asin(x) = pi/2 - 2*(s+s*z*R(z))
 *			= pio4_hi+(pio4-2s)-(2s*z*R(z)-pio2_lo)
 *			= pio4_hi+(pio4-2f)-(2s*z*R(z)-(pio2_lo+2c))
 *
 * Special cases:
 *	if x is NaN, return x itself;
 *	if |x|>1, return NaN with invalid signal.
 *
 */


#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{

    //------------------------------------------------------------------------------
    float Cmath::asinf( float x ) // wrapper asinf
    {
        float z;
        struct fexception exc;
        z = __ieee754_asinf( x );
        if( m_fdlib_version == _IEEE_ || isnanf( x ) )
        {
            return z;
        }

        if( fabsf( x ) > (float)1.0 )
        {
            // asinf(|x|>1)
            exc.type = EX_DOMAIN;
            exc.name = "asinf";
            exc.err = 0;
            exc.arg1 = exc.arg2 = (double)x;
            exc.retval = 0.0;
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
    double Cmath::asin( double x )
    {
        return (double)asinf( (float)x );
    }

#else

    //------------------------------------------------------------------------------
    double Cmath::asin( double x ) // wrapper asin
    {
        double z;
        struct fexception exc;
        z = __ieee754_asin( x );
        if( m_fdlib_version == _IEEE_ || isnan( x ) )
        {
            return z;
        }

        if( fabs( x ) > 1.0 )
        {
            // asin(|x|>1)
            exc.type = EX_DOMAIN;
            exc.name = "asin";
            exc.err = 0;
            exc.arg1 = exc.arg2 = x;
            exc.retval = 0.0;
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
    double Cmath::__ieee754_asin( double x )
    {
        static const double one =  1.00000000000000000000e+00; // 0x3FF00000, 0x00000000
        static const double huge =  1.000e+300;
        static const double pio2_hi =  1.57079632679489655800e+00; // 0x3FF921FB, 0x54442D18
        static const double pio2_lo =  6.12323399573676603587e-17; // 0x3C91A626, 0x33145C07
        static const double pio4_hi =  7.85398163397448278999e-01; // 0x3FE921FB, 0x54442D18
        // coefficient for R(x^2)
        static const double pS0 =  1.66666666666666657415e-01; // 0x3FC55555, 0x55555555
        static const double pS1 = -3.25565818622400915405e-01; // 0xBFD4D612, 0x03EB6F7D
        static const double pS2 =  2.01212532134862925881e-01; // 0x3FC9C155, 0x0E884455
        static const double pS3 = -4.00555345006794114027e-02; // 0xBFA48228, 0xB5688F3B
        static const double pS4 =  7.91534994289814532176e-04; // 0x3F49EFE0, 0x7501B288
        static const double pS5 =  3.47933107596021167570e-05; // 0x3F023DE1, 0x0DFDF709
        static const double qS1 = -2.40339491173441421878e+00; // 0xC0033A27, 0x1C8A2D4B
        static const double qS2 =  2.02094576023350569471e+00; // 0x40002AE5, 0x9C598AC8
        static const double qS3 = -6.88283971605453293030e-01; // 0xBFE6066C, 0x1B8D0159
        static const double qS4 =  7.70381505559019352791e-02; // 0x3FB3B8C5, 0xB12E9282

        double t, w, p, q, c, r, s;
        Cmp_signed__int32 hx, ix;
        get_high_word( hx, x );
        ix = hx & 0x7fffffff;
        if( ix >= 0x3ff00000 )
        {
            // |x|>= 1
            Cmp_unsigned__int32 lx;
            get_low_word( lx, x );
            if( ( ( ix - 0x3ff00000 ) | lx ) == 0 )
            {
                // asin(1)=+-pi/2 with inexact
                return x * pio2_hi + x * pio2_lo;
            }
            return ( x - x ) / ( x - x ); // asin(|x|>1) is NaN
        }
        else if( ix < 0x3fe00000 )
        {
            // |x|<0.5
            if( ix < 0x3e400000 )
            {
                // if |x| < 2**-27
                if( huge + x > one )
                {
                    return x; // return x with inexact if x!=0
                }
            }
            else
            {
                t = x * x;
                p = t * ( pS0 + t * ( pS1 + t * ( pS2 + t * ( pS3 + t * ( pS4 + t * pS5 ) ) ) ) );
                q = one + t * ( qS1 + t * ( qS2 + t * ( qS3 + t * qS4 ) ) );
                w = p / q;
                return x + x * w;
            }
        }

        // 1> |x|>= 0.5
        w = one - fabs( x );
        t = w * 0.5;
        p = t * ( pS0 + t * ( pS1 + t * ( pS2 + t * ( pS3 + t * ( pS4 + t * pS5 ) ) ) ) );
        q = one + t * ( qS1 + t * ( qS2 + t * ( qS3 + t * qS4 ) ) );
        s = __ieee754_sqrt( t );
        if( ix >= 0x3FEF3333 )
        {
            // if |x| > 0.975
            w = p / q;
            t = pio2_hi - ( 2.0 * ( s + s * w ) - pio2_lo );
        }
        else
        {
            w  = s;
            set_low_word( w, 0 );
            c  = ( t - w * w ) / ( s + w );
            r  = p / q;
            p  = 2.0 * s * r - ( pio2_lo - 2.0 * c );
            q  = pio4_hi - 2.0 * w;
            t  = pio4_hi - ( p - q );
        }

        if( hx > 0 )
        {
            return t;
        }
        else
        {
            return -t;
        }
    }

#endif//defined(_DOUBLE_IS_32BITS)

    //------------------------------------------------------------------------------
    float Cmath::__ieee754_asinf( float x )
    {
        static const float one = 1.0000000000e+00; // 0x3F800000
        static const float huge = 1.000e+30;
        static const float pio2_hi = 1.57079637050628662109375f;
        static const float pio2_lo = -4.37113900018624283e-8f;
        static const float pio4_hi = 0.785398185253143310546875f;
        // coefficient for R(x^2)
        static const float pS0 =  1.6666667163e-01; // 0x3e2aaaab
        static const float pS1 = -3.2556581497e-01; // 0xbea6b090
        static const float pS2 =  2.0121252537e-01; // 0x3e4e0aa8
        static const float pS3 = -4.0055535734e-02; // 0xbd241146
        static const float pS4 =  7.9153501429e-04; // 0x3a4f7f04
        static const float pS5 =  3.4793309169e-05; // 0x3811ef08
        static const float qS1 = -2.4033949375e+00; // 0xc019d139
        static const float qS2 =  2.0209457874e+00; // 0x4001572d
        static const float qS3 = -6.8828397989e-01; // 0xbf303361
        static const float qS4 =  7.7038154006e-02; // 0x3d9dc62e

        float t, w, p, q, c, r, s;
        Cmp_signed__int32 hx, ix;
        get_float_word( hx, x );
        ix = hx & 0x7fffffff;
        if( ix == 0x3f800000 )
        {
            // asin(1)=+-pi/2 with inexact
            return x * pio2_hi + x * pio2_lo;
        }
        else if( ix > 0x3f800000 )
        {
            // |x|>= 1
            return ( x - x ) / ( x - x ); // asin(|x|>1) is NaN
        }
        else if( ix < 0x3f000000 )
        {
            // |x|<0.5
            if( ix < 0x32000000 )
            {
                // if |x| < 2**-27
                if( huge + x > one )
                {
                    return x;// return x with inexact if x!=0
                }
            }
            else
            {
                t = x * x;
                p = t * ( pS0 + t * ( pS1 + t * ( pS2 + t * ( pS3 + t * ( pS4 + t * pS5 ) ) ) ) );
                q = one + t * ( qS1 + t * ( qS2 + t * ( qS3 + t * qS4 ) ) );
                w = p / q;
                return x + x * w;
            }
        }

        // 1> |x|>= 0.5
        w = one - fabsf( x );
        t = w * (float)0.5;
        p = t * ( pS0 + t * ( pS1 + t * ( pS2 + t * ( pS3 + t * ( pS4 + t * pS5 ) ) ) ) );
        q = one + t * ( qS1 + t * ( qS2 + t * ( qS3 + t * qS4 ) ) );
        s = __ieee754_sqrtf( t );

        if( ix >= 0x3F79999A )
        {
            // if |x| > 0.975
            w = p / q;
            t = pio2_hi - ( (float)2.0 * ( s + s * w ) - pio2_lo );
        }
        else
        {
            Cmp_signed__int32 iw;
            w  = s;
            get_float_word( iw, w );
            set_float_word( w, iw & 0xfffff000 );
            c  = ( t - w * w ) / ( s + w );
            r  = p / q;
            p  = (float)2.0 * s * r - ( pio2_lo - (float)2.0 * c );
            q  = pio4_hi - (float)2.0 * w;
            t  = pio4_hi - ( p - q );
        }

        if( hx > 0 )
        {
            return t;
        }
        else
        {
            return -t;
        }
    }

};//namespace nsBaseCRT
