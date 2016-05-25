
/* @(#)er_lgamma.c 5.1 93/09/24 */
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
// Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
/* __ieee754_lgamma_r(x, signgamp)
 * Reentrant version of the logarithm of the Gamma function
 * with user provide pointer for the sign of Gamma(x).
 *
 * Method:
 *   1. Argument Reduction for 0 < x <= 8
 * 	Since gamma(1+s)=s*gamma(s), for x in [0,8], we may
 * 	reduce x to a number in [1.5,2.5] by
 * 		lgamma(1+s) = log(s) + lgamma(s)
 *	for example,
 *		lgamma(7.3) = log(6.3) + lgamma(6.3)
 *			    = log(6.3*5.3) + lgamma(5.3)
 *			    = log(6.3*5.3*4.3*3.3*2.3) + lgamma(2.3)
 *   2. Polynomial approximation of lgamma around its
 *	minimun ymin=1.461632144968362245 to maintain monotonicity.
 *	On [ymin-0.23, ymin+0.27] (i.e., [1.23164,1.73163]), use
 *		Let z = x-ymin;
 *		lgamma(x) = -1.214862905358496078218 + z^2*poly(z)
 *	where
 *		poly(z) is a 14 degree polynomial.
 *   2. Rational approximation in the primary interval [2,3]
 *	We use the following approximation:
 *		s = x-2.0;
 *		lgamma(x) = 0.5*s + s*P(s)/Q(s)
 *	with accuracy
 *		|P/Q - (lgamma(x)-0.5s)| < 2**-61.71
 *	Our algorithms are based on the following observation
 *
 *                             zeta(2)-1    2    zeta(3)-1    3
 * lgamma(2+s) = s*(1-Euler) + --------- * s  -  --------- * s  + ...
 *                                 2                 3
 *
 *	where Euler = 0.5771... is the Euler constant, which is very
 *	close to 0.5.
 *
 *   3. For x>=8, we have
 *	lgamma(x)~(x-0.5)log(x)-x+0.5*log(2pi)+1/(12x)-1/(360x**3)+....
 *	(better formula:
 *	   lgamma(x)~(x-0.5)*(log(x)-1)-.5*(log(2pi)-1) + ...)
 *	Let z = 1/x, then we approximation
 *		f(z) = lgamma(x) - (x-0.5)(log(x)-1)
 *	by
 *	  			    3       5             11
 *		w = w0 + w1*z + w2*z  + w3*z  + ... + w6*z
 *	where
 *		|w - f(z)| < 2**-58.74
 *
 *   4. For negative x, since (G is gamma function)
 *		-x*G(-x)*G(x) = pi/sin(pi*x),
 * 	we have
 * 		G(x) = pi/(sin(pi*x)*(-x)*G(-x))
 *	since G(-x) is positive, sign(G(x)) = sign(sin(pi*x)) for x<0
 *	Hence, for x<0, signgam = sign(sin(pi*x)) and
 *		lgamma(x) = log(|Gamma(x)|)
 *			  = log(pi/(|x*sin(pi*x)|)) - lgamma(-x);
 *	Note: one should avoid compute pi*(-x) directly in the
 *	      computation of sin(pi*(-x)).
 *
 *   5. Special Cases
 *		lgamma(2+s) ~ s*(1-Euler) for tiny s
 *		lgamma(1)=lgamma(2)=0
 *		lgamma(x) ~ -log(x) for tiny x
 *		lgamma(0) = lgamma(inf) = inf
 *	 	lgamma(-integer) = +-inf
 *
 */

#include "SystemQOR/Posix/Basemath.h"
#include <math.h>

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
    //------------------------------------------------------------------------------
    float Cmath::lgammaf( float x )
    {
        float y;
        struct fexception exc;
        y = __ieee754_lgammaf_r( x, &m_isigngam );
        if( m_fdlib_version == _IEEE_ )
        {
            return y;
        }

        if( !finitef( y ) && finitef( x ) )
        {
            exc.name = "lgammaf";
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

            if( floorf( x ) == x && x <= (float)0.0 )
            {
                // lgammaf(-integer)
                exc.type = EX_SING;
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
                // lgammaf(finite) overflow
                exc.type = EX_OVERFLOW;
                if( m_fdlib_version == _POSIX_ )
                {
                    errno = ERANGE;
                }
                else if( !matherr( &exc ) )
                {
                    errno = ERANGE;
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
            return y;
        }
    }

#ifdef _DOUBLE_IS_32BITS

    //------------------------------------------------------------------------------
    double Cmath::lgamma( double x )
    {
        return (double)lgammaf( (float)x );
    }

#else

    //------------------------------------------------------------------------------
    double Cmath::lgamma_r( double x, int* signgamp )
    {
        double y;
        struct fexception exc;
        y = __ieee754_lgamma_r( x, signgamp );
        if( m_fdlib_version == _IEEE_ )
        {
            return y;
        }

        if( !finite( y ) && finite( x ) )
        {
#	ifndef HUGE_VAL
#		define HUGE_VAL inf
            double inf = 0.0;
            set_high_word( inf, 0x7ff00000 ); // set inf to infinite
#	endif
            exc.name = "lgamma";
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

            if( floor( x ) == x && x <= 0.0 )
            {
                // lgamma(-integer)
                exc.type = EX_SING;
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
                // lgamma(finite) overflow
                exc.type = EX_OVERFLOW;
                if( m_fdlib_version == _POSIX_ )
                {
                    errno = ERANGE;
                }
                else if( !matherr( &exc ) )
                {
                    errno = ERANGE;
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
            return y;
        }
    }

    //------------------------------------------------------------------------------
    double Cmath::lgamma( double x )
    {
        double y;
        struct fexception exc;
        y = __ieee754_lgamma_r( x, &m_isigngam );
        if( m_fdlib_version == _IEEE_ )
        {
            return y;
        }

        if( !finite( y ) && finite( x ) )
        {
#	ifndef HUGE_VAL
#		define HUGE_VAL inf
            double inf = 0.0;
            set_high_word( inf, 0x7ff00000 ); // set inf to infinite
#	endif
            exc.name = "lgamma";
            exc.err = 0;
            exc.arg1 = x;
            exc.arg2 = x;
            if( m_fdlib_version == _SVID_ )
            {
                exc.retval = Huge();
            }
            else
            {
                exc.retval = HUGE_VAL;
            }

            if( floor( x ) == x && x <= 0.0 )
            {
                // lgamma(-integer)
                exc.type = EX_SING;
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
                // lgamma(finite) overflow
                exc.type = EX_OVERFLOW;
                if( m_fdlib_version == _POSIX_ )
                {
                    errno = ERANGE;
                }
                else if( !matherr( &exc ) )
                {
                    errno = ERANGE;
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
            return y;
        }
    }

#endif /* defined(_DOUBLE_IS_32BITS) */

    //------------------------------------------------------------------------------
    double Cmath::sin_pi( double x )
    {
        static const double two52=  4.50359962737049600000e+15; // 0x43300000, 0x00000000
        static const double half=  5.00000000000000000000e-01; // 0x3FE00000, 0x00000000
        static const double one =  1.00000000000000000000e+00; // 0x3FF00000, 0x00000000
        static const double pi  =  3.14159265358979311600e+00; // 0x400921FB, 0x54442D18
        static const double a0  =  7.72156649015328655494e-02; // 0x3FB3C467, 0xE37DB0C8
        static const double a1  =  3.22467033424113591611e-01; // 0x3FD4A34C, 0xC4A60FAD
        static const double a2  =  6.73523010531292681824e-02; // 0x3FB13E00, 0x1A5562A7
        static const double a3  =  2.05808084325167332806e-02; // 0x3F951322, 0xAC92547B
        static const double a4  =  7.38555086081402883957e-03; // 0x3F7E404F, 0xB68FEFE8
        static const double a5  =  2.89051383673415629091e-03; // 0x3F67ADD8, 0xCCB7926B
        static const double a6  =  1.19270763183362067845e-03; // 0x3F538A94, 0x116F3F5D
        static const double a7  =  5.10069792153511336608e-04; // 0x3F40B6C6, 0x89B99C00
        static const double a8  =  2.20862790713908385557e-04; // 0x3F2CF2EC, 0xED10E54D
        static const double a9  =  1.08011567247583939954e-04; // 0x3F1C5088, 0x987DFB07
        static const double a10 =  2.52144565451257326939e-05; // 0x3EFA7074, 0x428CFA52
        static const double a11 =  4.48640949618915160150e-05; // 0x3F07858E, 0x90A45837
        static const double tc  =  1.46163214496836224576e+00; // 0x3FF762D8, 0x6356BE3F
        static const double tf  = -1.21486290535849611461e-01; // 0xBFBF19B9, 0xBCC38A42
        // tt = -(tail of tf)
        static const double tt  = -3.63867699703950536541e-18; // 0xBC50C7CA, 0xA48A971F
        static const double t0  =  4.83836122723810047042e-01; // 0x3FDEF72B, 0xC8EE38A2
        static const double t1  = -1.47587722994593911752e-01; // 0xBFC2E427, 0x8DC6C509
        static const double t2  =  6.46249402391333854778e-02; // 0x3FB08B42, 0x94D5419B
        static const double t3  = -3.27885410759859649565e-02; // 0xBFA0C9A8, 0xDF35B713
        static const double t4  =  1.79706750811820387126e-02; // 0x3F9266E7, 0x970AF9EC
        static const double t5  = -1.03142241298341437450e-02; // 0xBF851F9F, 0xBA91EC6A
        static const double t6  =  6.10053870246291332635e-03; // 0x3F78FCE0, 0xE370E344
        static const double t7  = -3.68452016781138256760e-03; // 0xBF6E2EFF, 0xB3E914D7
        static const double t8  =  2.25964780900612472250e-03; // 0x3F6282D3, 0x2E15C915
        static const double t9  = -1.40346469989232843813e-03; // 0xBF56FE8E, 0xBF2D1AF1
        static const double t10 =  8.81081882437654011382e-04; // 0x3F4CDF0C, 0xEF61A8E9
        static const double t11 = -5.38595305356740546715e-04; // 0xBF41A610, 0x9C73E0EC
        static const double t12 =  3.15632070903625950361e-04; // 0x3F34AF6D, 0x6C0EBBF7
        static const double t13 = -3.12754168375120860518e-04; // 0xBF347F24, 0xECC38C38
        static const double t14 =  3.35529192635519073543e-04; // 0x3F35FD3E, 0xE8C2D3F4
        static const double u0  = -7.72156649015328655494e-02; // 0xBFB3C467, 0xE37DB0C8
        static const double u1  =  6.32827064025093366517e-01; // 0x3FE4401E, 0x8B005DFF
        static const double u2  =  1.45492250137234768737e+00; // 0x3FF7475C, 0xD119BD6F
        static const double u3  =  9.77717527963372745603e-01; // 0x3FEF4976, 0x44EA8450
        static const double u4  =  2.28963728064692451092e-01; // 0x3FCD4EAE, 0xF6010924
        static const double u5  =  1.33810918536787660377e-02; // 0x3F8B678B, 0xBF2BAB09
        static const double v1  =  2.45597793713041134822e+00; // 0x4003A5D7, 0xC2BD619C
        static const double v2  =  2.12848976379893395361e+00; // 0x40010725, 0xA42B18F5
        static const double v3  =  7.69285150456672783825e-01; // 0x3FE89DFB, 0xE45050AF
        static const double v4  =  1.04222645593369134254e-01; // 0x3FBAAE55, 0xD6537C88
        static const double v5  =  3.21709242282423911810e-03; // 0x3F6A5ABB, 0x57D0CF61
        static const double s0  = -7.72156649015328655494e-02; // 0xBFB3C467, 0xE37DB0C8
        static const double s1  =  2.14982415960608852501e-01; // 0x3FCB848B, 0x36E20878
        static const double s2  =  3.25778796408930981787e-01; // 0x3FD4D98F, 0x4F139F59
        static const double s3  =  1.46350472652464452805e-01; // 0x3FC2BB9C, 0xBEE5F2F7
        static const double s4  =  2.66422703033638609560e-02; // 0x3F9B481C, 0x7E939961
        static const double s5  =  1.84028451407337715652e-03; // 0x3F5E26B6, 0x7368F239
        static const double s6  =  3.19475326584100867617e-05; // 0x3F00BFEC, 0xDD17E945
        static const double r1  =  1.39200533467621045958e+00; // 0x3FF645A7, 0x62C4AB74
        static const double r2  =  7.21935547567138069525e-01; // 0x3FE71A18, 0x93D3DCDC
        static const double r3  =  1.71933865632803078993e-01; // 0x3FC601ED, 0xCCFBDF27
        static const double r4  =  1.86459191715652901344e-02; // 0x3F9317EA, 0x742ED475
        static const double r5  =  7.77942496381893596434e-04; // 0x3F497DDA, 0xCA41A95B
        static const double r6  =  7.32668430744625636189e-06; // 0x3EDEBAF7, 0xA5B38140
        static const double w0  =  4.18938533204672725052e-01; // 0x3FDACFE3, 0x90C97D69
        static const double w1  =  8.33333333333329678849e-02; // 0x3FB55555, 0x5555553B
        static const double w2  = -2.77777777728775536470e-03; // 0xBF66C16C, 0x16B02E5C
        static const double w3  =  7.93650558643019558500e-04; // 0x3F4A019F, 0x98CF38B6
        static const double w4  = -5.95187557450339963135e-04; // 0xBF4380CB, 0x8C0FE741
        static const double w5  =  8.36339918996282139126e-04; // 0x3F4B67BA, 0x4CDAD5D1
        static const double w6  = -1.63092934096575273989e-03; // 0xBF5AB89D, 0x0B9E43E4
        static const double zero = 0.00000000000000000000e+00;

        double y, z;
        Cmp_signed__int32 n, ix;

        get_high_word( ix, x );
        ix &= 0x7fffffff;

        if( ix < 0x3fd00000 )
        {
            return __kernel_sin( pi * x, zero, 0 );
        }
        y = -x;		// x is assume negative

        //argument reduction, make sure inexact flag not raised if input is an integer

        z = floor( y );
        if( z != y )
        {
            // inexact anyway
            y *= 0.5;
            y = 2.0 * ( y - floor( y ) ); // y = |x| mod 2.0
            n = (Cmp_signed__int32)( y * 4.0 );
        }
        else
        {
            if( ix >= 0x43400000 )
            {
                y = zero;
                n = 0; // y must be even
            }
            else
            {
                if( ix < 0x43300000 )
                {
                    z = y + two52; // exact
                }
                get_low_word( n, z );
                n &= 1;
                y = n;
                n <<= 2;
            }
        }

        switch( n )
        {
        case 0:   y = __kernel_sin( pi * y, zero, 0 );
            break;
        case 1:
        case 2:   y = __kernel_cos( pi * ( 0.5 - y ), zero );
            break;
        case 3:
        case 4:   y = __kernel_sin( pi * ( one - y ), zero, 0 );
            break;
        case 5:
        case 6:   y = -__kernel_cos( pi * ( y - 1.5 ), zero );
            break;
        default:  y = __kernel_sin( pi * ( y - 2.0 ), zero, 0 );
            break;
        }
        return -y;
    }

    //------------------------------------------------------------------------------
    double Cmath::__ieee754_lgamma_r( double x, int* signgamp )
    {
        static const double zero = 0.00000000000000000000e+00;
        static const double half=  5.00000000000000000000e-01; // 0x3FE00000, 0x00000000
        static const double one =  1.00000000000000000000e+00; // 0x3FF00000, 0x00000000
        static const double pi  =  3.14159265358979311600e+00; // 0x400921FB, 0x54442D18
        static const double a0  =  7.72156649015328655494e-02; // 0x3FB3C467, 0xE37DB0C8
        static const double a1  =  3.22467033424113591611e-01; // 0x3FD4A34C, 0xC4A60FAD
        static const double a2  =  6.73523010531292681824e-02; // 0x3FB13E00, 0x1A5562A7
        static const double a3  =  2.05808084325167332806e-02; // 0x3F951322, 0xAC92547B
        static const double a4  =  7.38555086081402883957e-03; // 0x3F7E404F, 0xB68FEFE8
        static const double a5  =  2.89051383673415629091e-03; // 0x3F67ADD8, 0xCCB7926B
        static const double a6  =  1.19270763183362067845e-03; // 0x3F538A94, 0x116F3F5D
        static const double a7  =  5.10069792153511336608e-04; // 0x3F40B6C6, 0x89B99C00
        static const double a8  =  2.20862790713908385557e-04; // 0x3F2CF2EC, 0xED10E54D
        static const double a9  =  1.08011567247583939954e-04; // 0x3F1C5088, 0x987DFB07
        static const double a10 =  2.52144565451257326939e-05; // 0x3EFA7074, 0x428CFA52
        static const double a11 =  4.48640949618915160150e-05; // 0x3F07858E, 0x90A45837
        static const double tc  =  1.46163214496836224576e+00; // 0x3FF762D8, 0x6356BE3F
        static const double tf  = -1.21486290535849611461e-01; // 0xBFBF19B9, 0xBCC38A42
        static const double tt  = -3.63867699703950536541e-18; // 0xBC50C7CA, 0xA48A971F
        static const double t0  =  4.83836122723810047042e-01; // 0x3FDEF72B, 0xC8EE38A2
        static const double t1  = -1.47587722994593911752e-01; // 0xBFC2E427, 0x8DC6C509
        static const double t2  =  6.46249402391333854778e-02; // 0x3FB08B42, 0x94D5419B
        static const double t3  = -3.27885410759859649565e-02; // 0xBFA0C9A8, 0xDF35B713
        static const double t4  =  1.79706750811820387126e-02; // 0x3F9266E7, 0x970AF9EC
        static const double t5  = -1.03142241298341437450e-02; // 0xBF851F9F, 0xBA91EC6A
        static const double t6  =  6.10053870246291332635e-03; // 0x3F78FCE0, 0xE370E344
        static const double t7  = -3.68452016781138256760e-03; // 0xBF6E2EFF, 0xB3E914D7
        static const double t8  =  2.25964780900612472250e-03; // 0x3F6282D3, 0x2E15C915
        static const double t9  = -1.40346469989232843813e-03; // 0xBF56FE8E, 0xBF2D1AF1
        static const double t10 =  8.81081882437654011382e-04; // 0x3F4CDF0C, 0xEF61A8E9
        static const double t11 = -5.38595305356740546715e-04; // 0xBF41A610, 0x9C73E0EC
        static const double t12 =  3.15632070903625950361e-04; // 0x3F34AF6D, 0x6C0EBBF7
        static const double t13 = -3.12754168375120860518e-04; // 0xBF347F24, 0xECC38C38
        static const double t14 =  3.35529192635519073543e-04; // 0x3F35FD3E, 0xE8C2D3F4
        static const double u0  = -7.72156649015328655494e-02; // 0xBFB3C467, 0xE37DB0C8
        static const double u1  =  6.32827064025093366517e-01; // 0x3FE4401E, 0x8B005DFF
        static const double u2  =  1.45492250137234768737e+00; // 0x3FF7475C, 0xD119BD6F
        static const double u3  =  9.77717527963372745603e-01; // 0x3FEF4976, 0x44EA8450
        static const double u4  =  2.28963728064692451092e-01; // 0x3FCD4EAE, 0xF6010924
        static const double u5  =  1.33810918536787660377e-02; // 0x3F8B678B, 0xBF2BAB09
        static const double v1  =  2.45597793713041134822e+00; // 0x4003A5D7, 0xC2BD619C
        static const double v2  =  2.12848976379893395361e+00; // 0x40010725, 0xA42B18F5
        static const double v3  =  7.69285150456672783825e-01; // 0x3FE89DFB, 0xE45050AF
        static const double v4  =  1.04222645593369134254e-01; // 0x3FBAAE55, 0xD6537C88
        static const double v5  =  3.21709242282423911810e-03; // 0x3F6A5ABB, 0x57D0CF61
        static const double s0  = -7.72156649015328655494e-02; // 0xBFB3C467, 0xE37DB0C8
        static const double s1  =  2.14982415960608852501e-01; // 0x3FCB848B, 0x36E20878
        static const double s2  =  3.25778796408930981787e-01; // 0x3FD4D98F, 0x4F139F59
        static const double s3  =  1.46350472652464452805e-01; // 0x3FC2BB9C, 0xBEE5F2F7
        static const double s4  =  2.66422703033638609560e-02; // 0x3F9B481C, 0x7E939961
        static const double s5  =  1.84028451407337715652e-03; // 0x3F5E26B6, 0x7368F239
        static const double s6  =  3.19475326584100867617e-05; // 0x3F00BFEC, 0xDD17E945
        static const double r1  =  1.39200533467621045958e+00; // 0x3FF645A7, 0x62C4AB74
        static const double r2  =  7.21935547567138069525e-01; // 0x3FE71A18, 0x93D3DCDC
        static const double r3  =  1.71933865632803078993e-01; // 0x3FC601ED, 0xCCFBDF27
        static const double r4  =  1.86459191715652901344e-02; // 0x3F9317EA, 0x742ED475
        static const double r5  =  7.77942496381893596434e-04; // 0x3F497DDA, 0xCA41A95B
        static const double r6  =  7.32668430744625636189e-06; // 0x3EDEBAF7, 0xA5B38140
        static const double w0  =  4.18938533204672725052e-01; // 0x3FDACFE3, 0x90C97D69
        static const double w1  =  8.33333333333329678849e-02; // 0x3FB55555, 0x5555553B
        static const double w2  = -2.77777777728775536470e-03; // 0xBF66C16C, 0x16B02E5C
        static const double w3  =  7.93650558643019558500e-04; // 0x3F4A019F, 0x98CF38B6
        static const double w4  = -5.95187557450339963135e-04; // 0xBF4380CB, 0x8C0FE741
        static const double w5  =  8.36339918996282139126e-04; // 0x3F4B67BA, 0x4CDAD5D1
        static const double w6  = -1.63092934096575273989e-03; // 0xBF5AB89D, 0x0B9E43E4

        double t, y, z, nadj, p, p1, p2, p3, q, r, w;
        Cmp_signed__int32 i, hx, lx, ix;

        extract_words( hx, lx, x );

        // purge off +-inf, NaN, +-0, and negative arguments
        *signgamp = 1;
        ix = hx & 0x7fffffff;
        if( ix >= 0x7ff00000 )
        {
            return x * x;
        }

        if( ( ix | lx ) == 0 )
        {
            return one / zero;
        }

        if( ix < 0x3b900000 )
        {
            // |x|<2**-70, return -log(|x|)
            if( hx < 0 )
            {
                *signgamp = -1;
                return -__ieee754_log( -x );
            }
            else
            {
                return -__ieee754_log( x );
            }
        }

        if( hx < 0 )
        {
            if( ix >= 0x43300000 ) // |x|>=2**52, must be -integer
            {
                return one / zero;
            }

            t = sin_pi( x );
            if( t == zero )
            {
                return one / zero; // -integer
            }

            nadj = __ieee754_log( pi / fabs( t * x ) );
            if( t < zero )
            {
                *signgamp = -1;
            }
            x = -x;
        }

        // purge off 1 and 2
        if( ( ( ( ix - 0x3ff00000 ) | lx ) == 0 ) || ( ( ( ix - 0x40000000 ) | lx ) == 0 ) )
        {
            r = 0;
        }// for x < 2.0
        else if( ix < 0x40000000 )
        {
            if( ix <= 0x3feccccc )
            {
                // lgamma(x) = lgamma(x+1)-log(x)
                r = -__ieee754_log( x );
                if( ix >= 0x3FE76944 )
                {
                    y = one - x;
                    i = 0;
                }
                else if( ix >= 0x3FCDA661 )
                {
                    y = x - ( tc - one );
                    i = 1;
                }
                else
                {
                    y = x;
                    i = 2;
                }
            }
            else
            {
                r = zero;
                if( ix >= 0x3FFBB4C3 )
                {
                    y = 2.0 - x;
                    i = 0;
                } // [1.7316,2]
                else if( ix >= 0x3FF3B4C4 )
                {
                    y = x - tc;
                    i = 1;
                } // [1.23,1.73]
                else
                {
                    y = x - one;
                    i = 2;
                }
            }

            switch( i )
            {
            case 0:
                z = y * y;
                p1 = a0 + z * ( a2 + z * ( a4 + z * ( a6 + z * ( a8 + z * a10 ) ) ) );
                p2 = z * ( a1 + z * ( a3 + z * ( a5 + z * ( a7 + z * ( a9 + z * a11 ) ) ) ) );
                p = y * p1 + p2;
                r += ( p - 0.5 * y );
                break;
            case 1:
                z = y * y;
                w = z * y;
                p1 = t0 + w * ( t3 + w * ( t6 + w * ( t9 + w * t12 ) ) ); // parallel comp
                p2 = t1 + w * ( t4 + w * ( t7 + w * ( t10 + w * t13 ) ) );
                p3 = t2 + w * ( t5 + w * ( t8 + w * ( t11 + w * t14 ) ) );
                p = z * p1 - ( tt - w * ( p2 + y * p3 ) );
                r += ( tf + p );
                break;
            case 2:
                p1 = y * ( u0 + y * ( u1 + y * ( u2 + y * ( u3 + y * ( u4 + y * u5 ) ) ) ) );
                p2 = one + y * ( v1 + y * ( v2 + y * ( v3 + y * ( v4 + y * v5 ) ) ) );
                r += ( -0.5 * y + p1 / p2 );
            }
        }
        else if( ix < 0x40200000 )
        {
            // x < 8.0
            i = (Cmp_signed__int32)x;
            t = zero;
            y = x - (double)i;
            p = y * ( s0 + y * ( s1 + y * ( s2 + y * ( s3 + y * ( s4 + y * ( s5 + y * s6 ) ) ) ) ) );
            q = one + y * ( r1 + y * ( r2 + y * ( r3 + y * ( r4 + y * ( r5 + y * r6 ) ) ) ) );
            r = half * y + p / q;
            z = one; // lgamma(1+s) = log(s) + lgamma(s)

            switch( i )
            {
            case 7: z *= ( y + 6.0 ); // FALLTHRU
            case 6: z *= ( y + 5.0 ); // FALLTHRU
            case 5: z *= ( y + 4.0 ); // FALLTHRU
            case 4: z *= ( y + 3.0 ); // FALLTHRU
            case 3: z *= ( y + 2.0 ); // FALLTHRU
            r += __ieee754_log( z );
            break;
            }
            // 8.0 <= x < 2**58
        }
        else if( ix < 0x43900000 )
        {
            t = __ieee754_log( x );
            z = one / x;
            y = z * z;
            w = w0 + z * ( w1 + y * ( w2 + y * ( w3 + y * ( w4 + y * ( w5 + y * w6 ) ) ) ) );
            r = ( x - half ) * ( t - one ) + w;
        }
        else
        {
            // 2**58 <= x <= inf
            r =  x * ( __ieee754_log( x ) - one );
        }

        if( hx < 0 )
        {
            r = nadj - r;
        }
        return r;
    }

    //------------------------------------------------------------------------------
    float Cmath::sin_pif( float x )
    {
        static const float two23 =8.3886080000e+06; // 0x4b000000
        static const float half = 5.0000000000e-01; // 0x3f000000
        static const float one =  1.0000000000e+00; // 0x3f800000
        static const float pi  =  3.1415927410e+00; // 0x40490fdb
        static const float a0  =  7.7215664089e-02; // 0x3d9e233f
        static const float a1  =  3.2246702909e-01; // 0x3ea51a66
        static const float a2  =  6.7352302372e-02; // 0x3d89f001
        static const float a3  =  2.0580807701e-02; // 0x3ca89915
        static const float a4  =  7.3855509982e-03; // 0x3bf2027e
        static const float a5  =  2.8905137442e-03; // 0x3b3d6ec6
        static const float a6  =  1.1927076848e-03; // 0x3a9c54a1
        static const float a7  =  5.1006977446e-04; // 0x3a05b634
        static const float a8  =  2.2086278477e-04; // 0x39679767
        static const float a9  =  1.0801156895e-04; // 0x38e28445
        static const float a10 =  2.5214456400e-05; // 0x37d383a2
        static const float a11 =  4.4864096708e-05; // 0x383c2c75
        static const float tc  =  1.4616321325e+00; // 0x3fbb16c3
        static const float tf  = -1.2148628384e-01; // 0xbdf8cdcd
        // tt = -(tail of tf)
        static const float tt  =  6.6971006518e-09; // 0x31e61c52
        static const float t0  =  4.8383611441e-01; // 0x3ef7b95e
        static const float t1  = -1.4758771658e-01; // 0xbe17213c
        static const float t2  =  6.4624942839e-02; // 0x3d845a15
        static const float t3  = -3.2788541168e-02; // 0xbd064d47
        static const float t4  =  1.7970675603e-02; // 0x3c93373d
        static const float t5  = -1.0314224288e-02; // 0xbc28fcfe
        static const float t6  =  6.1005386524e-03; // 0x3bc7e707
        static const float t7  = -3.6845202558e-03; // 0xbb7177fe
        static const float t8  =  2.2596477065e-03; // 0x3b141699
        static const float t9  = -1.4034647029e-03; // 0xbab7f476
        static const float t10 =  8.8108185446e-04; // 0x3a66f867
        static const float t11 = -5.3859531181e-04; // 0xba0d3085
        static const float t12 =  3.1563205994e-04; // 0x39a57b6b
        static const float t13 = -3.1275415677e-04; // 0xb9a3f927
        static const float t14 =  3.3552918467e-04; // 0x39afe9f7
        static const float u0  = -7.7215664089e-02; // 0xbd9e233f
        static const float u1  =  6.3282704353e-01; // 0x3f2200f4
        static const float u2  =  1.4549225569e+00; // 0x3fba3ae7
        static const float u3  =  9.7771751881e-01; // 0x3f7a4bb2
        static const float u4  =  2.2896373272e-01; // 0x3e6a7578
        static const float u5  =  1.3381091878e-02; // 0x3c5b3c5e
        static const float v1  =  2.4559779167e+00; // 0x401d2ebe
        static const float v2  =  2.1284897327e+00; // 0x4008392d
        static const float v3  =  7.6928514242e-01; // 0x3f44efdf
        static const float v4  =  1.0422264785e-01; // 0x3dd572af
        static const float v5  =  3.2170924824e-03; // 0x3b52d5db
        static const float s0  = -7.7215664089e-02; // 0xbd9e233f
        static const float s1  =  2.1498242021e-01; // 0x3e5c245a
        static const float s2  =  3.2577878237e-01; // 0x3ea6cc7a
        static const float s3  =  1.4635047317e-01; // 0x3e15dce6
        static const float s4  =  2.6642270386e-02; // 0x3cda40e4
        static const float s5  =  1.8402845599e-03; // 0x3af135b4
        static const float s6  =  3.1947532989e-05; // 0x3805ff67
        static const float r1  =  1.3920053244e+00; // 0x3fb22d3b
        static const float r2  =  7.2193557024e-01; // 0x3f38d0c5
        static const float r3  =  1.7193385959e-01; // 0x3e300f6e
        static const float r4  =  1.8645919859e-02; // 0x3c98bf54
        static const float r5  =  7.7794247773e-04; // 0x3a4beed6
        static const float r6  =  7.3266842264e-06; // 0x36f5d7bd
        static const float w0  =  4.1893854737e-01; // 0x3ed67f1d
        static const float w1  =  8.3333335817e-02; // 0x3daaaaab
        static const float w2  = -2.7777778450e-03; // 0xbb360b61
        static const float w3  =  7.9365057172e-04; // 0x3a500cfd
        static const float w4  = -5.9518753551e-04; // 0xba1c065c
        static const float w5  =  8.3633989561e-04; // 0x3a5b3dd2
        static const float w6  = -1.6309292987e-03; // 0xbad5c4e8
        static const float zero=  0.0000000000e+00;

        float y,z;
        Cmp_signed__int32 n,ix;

        get_float_word( ix, x );
        ix &= 0x7fffffff;

        if( ix < 0x3e800000 )
        {
            return __kernel_sinf( pi * x, zero, 0 );
        }
        y = -x;		// x is assume negative

        //argument reduction, make sure inexact flag not raised if input is an integer

        z = floorf( y );
        if( z != y )
        {
            // inexact anyway
            y *= (float)0.5;
            y = (float)2.0 * ( y - floorf( y ) ); // y = |x| mod 2.0
            n = (Cmp_signed__int32)( y * (float)4.0 );
        }
        else
        {
            if( ix >= 0x4b800000 )
            {
                y = zero;
                n = 0; // y must be even
            }
            else
            {
                if( ix < 0x4b000000 )
                {
                    z = y + two23; // exact
                }
                get_float_word( n, z );
                n &= 1;
                y = n;
                n <<= 2;
            }
        }

        switch( n )
        {
        case 0:   y = __kernel_sinf( pi * y, zero, 0 );
            break;
        case 1:
        case 2:   y = __kernel_cosf( pi * ( (float)0.5 - y ), zero );
            break;
        case 3:
        case 4:   y = __kernel_sinf( pi * ( one - y ), zero, 0 );
            break;
        case 5:
        case 6:   y = -__kernel_cosf( pi * ( y - (float)1.5 ), zero );
            break;
        default:  y = __kernel_sinf( pi * ( y - (float)2.0 ), zero, 0 );
            break;
        }
        return -y;
    }

    //------------------------------------------------------------------------------
    float Cmath::__ieee754_lgammaf_r( float x, int* signgamp )
    {
        static const float half = 5.0000000000e-01; // 0x3f000000
        static const float one =  1.0000000000e+00; // 0x3f800000
        static const float pi  =  3.1415927410e+00; // 0x40490fdb
        static const float a0  =  7.7215664089e-02; // 0x3d9e233f
        static const float a1  =  3.2246702909e-01; // 0x3ea51a66
        static const float a2  =  6.7352302372e-02; // 0x3d89f001
        static const float a3  =  2.0580807701e-02; // 0x3ca89915
        static const float a4  =  7.3855509982e-03; // 0x3bf2027e
        static const float a5  =  2.8905137442e-03; // 0x3b3d6ec6
        static const float a6  =  1.1927076848e-03; // 0x3a9c54a1
        static const float a7  =  5.1006977446e-04; // 0x3a05b634
        static const float a8  =  2.2086278477e-04; // 0x39679767
        static const float a9  =  1.0801156895e-04; // 0x38e28445
        static const float a10 =  2.5214456400e-05; // 0x37d383a2
        static const float a11 =  4.4864096708e-05; // 0x383c2c75
        static const float tc  =  1.4616321325e+00; // 0x3fbb16c3
        static const float tf  = -1.2148628384e-01; // 0xbdf8cdcd
        // tt = -(tail of tf)
        static const float tt  =  6.6971006518e-09; // 0x31e61c52
        static const float t0  =  4.8383611441e-01; // 0x3ef7b95e
        static const float t1  = -1.4758771658e-01; // 0xbe17213c
        static const float t2  =  6.4624942839e-02; // 0x3d845a15
        static const float t3  = -3.2788541168e-02; // 0xbd064d47
        static const float t4  =  1.7970675603e-02; // 0x3c93373d
        static const float t5  = -1.0314224288e-02; // 0xbc28fcfe
        static const float t6  =  6.1005386524e-03; // 0x3bc7e707
        static const float t7  = -3.6845202558e-03; // 0xbb7177fe
        static const float t8  =  2.2596477065e-03; // 0x3b141699
        static const float t9  = -1.4034647029e-03; // 0xbab7f476
        static const float t10 =  8.8108185446e-04; // 0x3a66f867
        static const float t11 = -5.3859531181e-04; // 0xba0d3085
        static const float t12 =  3.1563205994e-04; // 0x39a57b6b
        static const float t13 = -3.1275415677e-04; // 0xb9a3f927
        static const float t14 =  3.3552918467e-04; // 0x39afe9f7
        static const float u0  = -7.7215664089e-02; // 0xbd9e233f
        static const float u1  =  6.3282704353e-01; // 0x3f2200f4
        static const float u2  =  1.4549225569e+00; // 0x3fba3ae7
        static const float u3  =  9.7771751881e-01; // 0x3f7a4bb2
        static const float u4  =  2.2896373272e-01; // 0x3e6a7578
        static const float u5  =  1.3381091878e-02; // 0x3c5b3c5e
        static const float v1  =  2.4559779167e+00; // 0x401d2ebe
        static const float v2  =  2.1284897327e+00; // 0x4008392d
        static const float v3  =  7.6928514242e-01; // 0x3f44efdf
        static const float v4  =  1.0422264785e-01; // 0x3dd572af
        static const float v5  =  3.2170924824e-03; // 0x3b52d5db
        static const float s0  = -7.7215664089e-02; // 0xbd9e233f
        static const float s1  =  2.1498242021e-01; // 0x3e5c245a
        static const float s2  =  3.2577878237e-01; // 0x3ea6cc7a
        static const float s3  =  1.4635047317e-01; // 0x3e15dce6
        static const float s4  =  2.6642270386e-02; // 0x3cda40e4
        static const float s5  =  1.8402845599e-03; // 0x3af135b4
        static const float s6  =  3.1947532989e-05; // 0x3805ff67
        static const float r1  =  1.3920053244e+00; // 0x3fb22d3b
        static const float r2  =  7.2193557024e-01; // 0x3f38d0c5
        static const float r3  =  1.7193385959e-01; // 0x3e300f6e
        static const float r4  =  1.8645919859e-02; // 0x3c98bf54
        static const float r5  =  7.7794247773e-04; // 0x3a4beed6
        static const float r6  =  7.3266842264e-06; // 0x36f5d7bd
        static const float w0  =  4.1893854737e-01; // 0x3ed67f1d
        static const float w1  =  8.3333335817e-02; // 0x3daaaaab
        static const float w2  = -2.7777778450e-03; // 0xbb360b61
        static const float w3  =  7.9365057172e-04; // 0x3a500cfd
        static const float w4  = -5.9518753551e-04; // 0xba1c065c
        static const float w5  =  8.3633989561e-04; // 0x3a5b3dd2
        static const float w6  = -1.6309292987e-03; // 0xbad5c4e8
        static const float zero=  0.0000000000e+00;

        float t, y, z, nadj, p, p1, p2, p3, q, r, w;
        Cmp_signed__int32 i, hx, ix;

        get_float_word( hx, x );

        // purge off +-inf, NaN, +-0, and negative arguments
        *signgamp = 1;
        ix = hx & 0x7fffffff;
        if( ix >= 0x7f800000 )
        {
            return x * x;
        }

        if( ix == 0 )
        {
            return one / zero;
        }

        if( ix < 0x1c800000 )
        {
            // |x|<2**-70, return -log(|x|)
            if( hx < 0 )
            {
                *signgamp = -1;
                return -__ieee754_logf( -x );
            }
            else
            {
                return -__ieee754_logf( x );
            }
        }

        if( hx < 0 )
        {
            if( ix >= 0x4b000000 ) // |x|>=2**23, must be -integer
            {
                return one / zero;
            }
            t = sin_pif( x );
            if( t == zero )
            {
                return one / zero; // -integer
            }
            nadj = __ieee754_logf( pi / fabsf( t * x ) );
            if( t < zero )
            {
                *signgamp = -1;
            }
            x = -x;
        }

        // purge off 1 and 2
        if( ix == 0x3f800000 || ix == 0x40000000 )
        {
            r = 0;
        }// for x < 2.0
        else if( ix < 0x40000000 )
        {
            if( ix <= 0x3f666666 )
            {
                // lgamma(x) = lgamma(x+1)-log(x)
                r = -__ieee754_logf( x );
                if( ix >= 0x3f3b4a20 )
                {
                    y = one - x;
                    i = 0;
                }
                else if( ix >= 0x3e6d3308 )
                {
                    y = x - ( tc - one );
                    i = 1;
                }
                else
                {
                    y = x;
                    i=2;
                }
            }
            else
            {
                r = zero;
                if( ix >= 0x3fdda618 )
                {
                    y = (float)2.0 - x;
                    i = 0;
                } // [1.7316,2]
                else if( ix >= 0x3F9da620 )
                {
                    y = x - tc;
                    i = 1;
                } // [1.23,1.73]
                else
                {
                    y = x - one;
                    i = 2;
                }
            }

            switch( i )
            {
            case 0:
                z = y * y;
                p1 = a0 + z * ( a2 + z * ( a4 + z * ( a6 + z * ( a8 + z * a10 ) ) ) );
                p2 = z * ( a1 + z * ( a3 + z * ( a5 + z * ( a7 + z * ( a9 + z * a11 ) ) ) ) );
                p = y * p1 + p2;
                r += ( p - (float)0.5 * y );
                break;
            case 1:
                z = y * y;
                w = z * y;
                p1 = t0 + w * ( t3 + w * ( t6 + w * ( t9 + w * t12 ) ) ); // parallel comp
                p2 = t1 + w * ( t4 + w * ( t7 + w * ( t10 + w * t13 ) ) );
                p3 = t2 + w * ( t5 + w * ( t8 + w * ( t11 + w * t14 ) ) );
                p  = z * p1 -( tt - w * ( p2 + y * p3 ) );
                r += ( tf + p );
                break;
            case 2:
                p1 = y * ( u0 + y * ( u1 + y * ( u2 + y * ( u3 + y * ( u4 + y * u5 ) ) ) ) );
                p2 = one + y * ( v1 + y * ( v2 + y * ( v3 + y * ( v4 + y * v5 ) ) ) );
                r += ( -(float)0.5 * y + p1 / p2 );
            }
        }
        else if( ix <0x41000000 )
        {
            // x < 8.0
            i = (Cmp_signed__int32)x;
            t = zero;
            y = x -(float)i;
            p = y * ( s0 + y * ( s1 + y * ( s2 + y * ( s3 + y * ( s4 + y * ( s5 + y * s6 ) ) ) ) ) );
            q = one + y * ( r1 + y * ( r2 + y * ( r3 + y * ( r4 + y * ( r5 + y * r6 ) ) ) ) );
            r = half * y + p / q;
            z = one; // lgamma(1+s) = log(s) + lgamma(s)
            switch( i )
            {
                case 7: z *= ( y + (float)6.0 ); // FALLTHRU
                case 6: z *= ( y + (float)5.0 ); // FALLTHRU
                case 5: z *= ( y + (float)4.0 ); // FALLTHRU
                case 4: z *= ( y + (float)3.0 ); // FALLTHRU
                case 3: z *= ( y + (float)2.0 ); // FALLTHRU
                r += __ieee754_logf( z );
                break;
            }

            // 8.0 <= x < 2**58
        }
        else if( ix < 0x5c800000 )
        {
            t = __ieee754_logf( x );
            z = one / x;
            y = z * z;
            w = w0 + z * ( w1 + y * ( w2 + y * ( w3 + y * ( w4 + y * ( w5 + y * w6 ) ) ) ) );
            r = ( x - half ) * ( t - one ) + w;
        }
        else
        {
            // 2**58 <= x <= inf
            r = x * ( __ieee754_logf( x ) - one );
        }

        if( hx < 0 )
        {
            r = nadj - r;
        }
        return r;
    }

    //------------------------------------------------------------------------------
    float Cmath::lgammaf_r( float x, int* signgamp )
    {
        float y;
        struct fexception exc;
        y = __ieee754_lgammaf_r( x, signgamp );
        if( m_fdlib_version == _IEEE_ )
        {
            return y;
        }

        if( !finitef( y ) && finitef( x ) )
        {
#	ifndef HUGE_VAL
#		define HUGE_VAL inf
            double inf = 0.0;
            set_high_word( inf, 0x7ff00000 ); // set inf to infinite
#	endif
            exc.name = "lgammaf";
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

            if( floorf( x ) == x && x <= (float)0.0 )
            {
                // lgammaf(-integer) or lgamma(0)
                exc.type = EX_SING;
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
                // lgammaf(finite) overflow
                exc.type = EX_OVERFLOW;
                if( m_fdlib_version == _POSIX_ )
                {
                    errno = ERANGE;
                }
                else if( !matherr( &exc ) )
                {
                    errno = ERANGE;
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
            return y;
        }
    }

};//namespace nsBaseCRT
