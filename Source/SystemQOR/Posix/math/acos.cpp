
/* @(#)e_acos.c 5.1 93/09/24 */
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

/* __ieee754_acos(x)
 * Method :
 *	acos(x)  = pi/2 - asin(x)
 *	acos(-x) = pi/2 + asin(x)
 * For |x|<=0.5
 *	acos(x) = pi/2 - (x + x*x^2*R(x^2))	(see asin.c)
 * For x>0.5
 * 	acos(x) = pi/2 - (pi/2 - 2asin(sqrt((1-x)/2)))
 *		= 2asin(sqrt((1-x)/2))
 *		= 2s + 2s*z*R(z) 	...z=(1-x)/2, s=sqrt(z)
 *		= 2f + (2c + 2s*z*R(z))
 *     where f=hi part of s, and c = (z-f*f)/(s+f) is the correction term
 *     for f so that f+c ~ sqrt(z).
 * For x<-0.5
 *	acos(x) = pi - 2asin(sqrt((1-|x|)/2))
 *		= pi - 0.5*(s+s*z*R(z)), where z=(1-|x|)/2,s=sqrt(z)
 *
 * Special cases:
 *	if x is NaN, return x itself;
 *	if |x|>1, return NaN with invalid signal.
 *
 * Function needed: sqrt
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
    //------------------------------------------------------------------------------
    float Cmath::acosf( float x )
    {
        float z;
        struct fexception exc;
        z = __ieee754_acosf( x );
        if( m_fdlib_version == _IEEE_ || isnanf( x ) )
        {
            return z;
        }

        if( fabsf( x ) > (float)1.0 )
        {
            // acosf(|x|>1)
            exc.type = EX_DOMAIN;
            exc.name = "acosf";
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

    //------------------------------------------------------------------------------
    float Cmath::__ieee754_acosf( float x )
    {
__QCMP_WARNING_PUSH
__QCMP_WARNING_DISABLE( __QCMP_WARN_TRUNCATION_FROM_DOUBLE_TO_FLOAT, "Intentional truncation of values" )
        static const float one =  1.0000000000e+00; // 0x3F800000
        static const float pi =  3.1415925026e+00; // 0x40490fda
        static const float pio2_hi =  1.5707962513e+00; // 0x3fc90fda
        static const float pio2_lo =  7.5497894159e-08; // 0x33a22168
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
__QCMP_WARNING_POP

        float z, p, q, r, w, s, c, df;
        Cmp_signed__int32 hx, ix;
        get_float_word( hx, x );
        ix = hx & 0x7fffffff;
        if( ix == 0x3f800000 )
        {
            // |x|==1
            if( hx > 0 )
            {
                return 0.0;	// acos(1) = 0
            }
            else
            {
                return pi + (float)2.0 * pio2_lo; // acos(-1)= pi
            }
        }
        else if( ix > 0x3f800000 )
        {
            // |x| >= 1
            return ( x - x ) / ( x - x ); // acos(|x|>1) is NaN
        }

        if( ix < 0x3f000000 )
        {
            // |x| < 0.5
            if( ix <= 0x23000000 )
            {
                return pio2_hi + pio2_lo; //if|x|<2**-57
            }
            z = x * x;
            p = z * ( pS0 + z * ( pS1 + z * ( pS2 + z * ( pS3 + z *( pS4 + z * pS5 ) ) ) ) );
            q = one + z * ( qS1 + z * ( qS2 + z * ( qS3 + z * qS4 ) ) );
            r = p / q;
            return pio2_hi - ( x - ( pio2_lo - x * r ) );
        }
        else if( hx < 0 )
        {
            // x < -0.5
            z = ( one + x ) * (float)0.5;
            p = z * ( pS0 + z * ( pS1 + z * ( pS2 + z * ( pS3 + z * ( pS4 + z * pS5 ) ) ) ) );
            q = one + z * ( qS1 + z * ( qS2 + z * ( qS3 + z * qS4 ) ) );
            s = __ieee754_sqrtf( z );
            r = p / q;
            w = r * s - pio2_lo;
            return pi - (float)2.0 * ( s + w );
        }
        else
        {
            // x > 0.5
            Cmp_signed__int32 idf;
            z = ( one - x ) * (float)0.5;
            s = __ieee754_sqrtf( z );
            df = s;
            get_float_word( idf, df );
            set_float_word( df, idf & 0xfffff000 );
            c  = ( z - df * df ) / ( s + df );
            p = z * ( pS0 + z * ( pS1 + z * ( pS2 + z * ( pS3 + z * ( pS4 + z * pS5 ) ) ) ) );
            q = one + z * ( qS1 + z * ( qS2 + z * ( qS3 + z * qS4 ) ) );
            r = p / q;
            w = r * s + c;
            return (float)2.0 * ( df + w );
        }
    }

#ifdef _DOUBLE_IS_32BITS

    //------------------------------------------------------------------------------
    double Cmath::acos( double x )
    {
        return (double) acosf( (float)x );
    }

#else

    //------------------------------------------------------------------------------
    double Cmath::acos( double x )
    {
        double z;
        struct fexception exc;
        z = __ieee754_acos( x );
        if( m_fdlib_version == _IEEE_ || isnan( x ) )
        {
            return z;
        }

        if( fabs( x ) > 1.0 )
        {
            // acos(|x|>1)
            exc.type = EX_DOMAIN;
            exc.name = "acos";
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
    double Cmath::__ieee754_acos( double x )
    {
        static const double one = 1.00000000000000000000e+00; // 0x3FF00000, 0x00000000
        static const double pi = 3.14159265358979311600e+00; // 0x400921FB, 0x54442D18
        static const double pio2_hi = 1.57079632679489655800e+00; // 0x3FF921FB, 0x54442D18
        static const double pio2_lo = 6.12323399573676603587e-17; // 0x3C91A626, 0x33145C07
        static const double pS0 = 1.66666666666666657415e-01; // 0x3FC55555, 0x55555555
        static const double pS1 = -3.25565818622400915405e-01; // 0xBFD4D612, 0x03EB6F7D
        static const double pS2 = 2.01212532134862925881e-01; // 0x3FC9C155, 0x0E884455
        static const double pS3 = -4.00555345006794114027e-02; // 0xBFA48228, 0xB5688F3B
        static const double pS4 = 7.91534994289814532176e-04; // 0x3F49EFE0, 0x7501B288
        static const double pS5 = 3.47933107596021167570e-05; // 0x3F023DE1, 0x0DFDF709
        static const double qS1 = -2.40339491173441421878e+00; // 0xC0033A27, 0x1C8A2D4B
        static const double qS2 = 2.02094576023350569471e+00; // 0x40002AE5, 0x9C598AC8
        static const double qS3 = -6.88283971605453293030e-01; // 0xBFE6066C, 0x1B8D0159
        static const double qS4 = 7.70381505559019352791e-02; // 0x3FB3B8C5, 0xB12E9282

        double z, p, q, r, w, s, c, df;
        Cmp_signed__int32 hx,ix;
        get_high_word( hx, x );
        ix = hx & 0x7fffffff;
        if( ix >= 0x3ff00000 )
        {	// |x| >= 1
            Cmp_unsigned__int32 lx;
            get_low_word( lx, x );
            if( ( ( ix - 0x3ff00000 ) | lx ) == 0 )
            {
                // |x|==1
                if( hx > 0 )
                {
                    return 0.0;		// acos(1) = 0
                }
                else
                {
                    return pi + 2.0 * pio2_lo; // acos(-1)= pi
                }
            }
            return ( x - x ) / ( x - x ); // acos(|x|>1) is NaN
        }

        if( ix < 0x3fe00000 )
        {
            // |x| < 0.5
            if( ix <= 0x3c600000 )
            {
                return pio2_hi + pio2_lo; //if|x|<2**-57
            }
            z = x * x;
            p = z * ( pS0 + z * ( pS1 + z * ( pS2 + z * ( pS3 + z * ( pS4 + z * pS5 ) ) ) ) );
            q = one + z * ( qS1 + z * ( qS2 + z * ( qS3 + z * qS4 ) ) );
            r = p / q;
            return pio2_hi - ( x - ( pio2_lo - x * r ) );
        }
        else if ( hx < 0 )
        {
            // x < -0.5
            z = ( one + x ) * 0.5;
            p = z * ( pS0 + z * ( pS1 + z * ( pS2 + z * ( pS3 + z * ( pS4 + z * pS5 ) ) ) ) );
            q = one + z * ( qS1 + z * ( qS2 + z * ( qS3 + z * qS4 ) ) );
            s = __ieee754_sqrt( z );
            r = p / q;
            w = r * s - pio2_lo;
            return pi - 2.0 * ( s + w );
        }
        else
        {
            // x > 0.5
            z = ( one - x ) * 0.5;
            s = __ieee754_sqrt( z );
            df = s;
            set_low_word( df, 0 );
            c  = ( z - df * df ) / ( s + df );
            p = z * ( pS0 + z * ( pS1 + z * ( pS2 + z * ( pS3 + z * ( pS4 + z * pS5 ) ) ) ) );
            q = one + z * ( qS1 + z * ( qS2 + z * ( qS3 + z * qS4 ) ) );
            r = p / q;
            w = r * s + c;
            return 2.0 * ( df + w );
        }
    }

#endif//defined(_DOUBLE_IS_32BITS)

}//namespace nsBaseCRT
