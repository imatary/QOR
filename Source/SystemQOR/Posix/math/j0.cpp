
/* @(#)e_j0.c 5.1 93/09/24 */
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
/* __ieee754_j0(x), __ieee754_y0(x)
 * Bessel function of the first and second kinds of order zero.
 * Method -- j0(x):
 *	1. For tiny x, we use j0(x) = 1 - x^2/4 + x^4/64 - ...
 *	2. Reduce x to |x| since j0(x)=j0(-x),  and
 *	   for x in (0,2)
 *		j0(x) = 1-z/4+ z^2*R0/S0,  where z = x*x;
 *	   (precision:  |j0-1+z/4-z^2R0/S0 |<2**-63.67 )
 *	   for x in (2,inf)
 * 		j0(x) = sqrt(2/(pi*x))*(p0(x)*cos(x0)-q0(x)*sin(x0))
 * 	   where x0 = x-pi/4. It is better to compute sin(x0),cos(x0)
 *	   as follow:
 *		cos(x0) = cos(x)cos(pi/4)+sin(x)sin(pi/4)
 *			= 1/sqrt(2) * (cos(x) + sin(x))
 *		sin(x0) = sin(x)cos(pi/4)-cos(x)sin(pi/4)
 *			= 1/sqrt(2) * (sin(x) - cos(x))
 * 	   (To avoid cancellation, use
 *		sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
 * 	    to compute the worse one.)
 *
 *	3 Special cases
 *		j0(nan)= nan
 *		j0(0) = 1
 *		j0(inf) = 0
 *
 * Method -- y0(x):
 *	1. For x<2.
 *	   Since
 *		y0(x) = 2/pi*(j0(x)*(ln(x/2)+Euler) + x^2/4 - ...)
 *	   therefore y0(x)-2/pi*j0(x)*ln(x) is an even function.
 *	   We use the following function to approximate y0,
 *		y0(x) = U(z)/V(z) + (2/pi)*(j0(x)*ln(x)), z= x^2
 *	   where
 *		U(z) = u00 + u01*z + ... + u06*z^6
 *		V(z) = 1  + v01*z + ... + v04*z^4
 *	   with absolute approximation error bounded by 2**-72.
 *	   Note: For tiny x, U/V = u0 and j0(x)~1, hence
 *		y0(tiny) = u0 + (2/pi)*ln(tiny), (choose tiny<2**-27)
 *	2. For x>=2.
 * 		y0(x) = sqrt(2/(pi*x))*(p0(x)*cos(x0)+q0(x)*sin(x0))
 * 	   where x0 = x-pi/4. It is better to compute sin(x0),cos(x0)
 *	   by the method mentioned above.
 *	3. Special cases: y0(0)=-inf, y0(x<0)=NaN, y0(inf)=0.
 */

#include "SystemQOR/Posix/Basemath.h"
#include <math.h>
#include "CodeQOR/Tracing/FunctionContextBase.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
    //------------------------------------------------------------------------------
    float Cmath::j0f( float x ) // wrapper j0f
    {
        struct fexception exc;
        float z = __ieee754_j0f( x );
        if( m_fdlib_version == _IEEE_ || isnanf( x ) )
        {
            return z;
        }
        if( fabsf( x ) > (float)X_TLOSS )
        {
            // j0f(|x|>X_TLOSS)
            exc.type = EX_TLOSS;
            exc.name = "j0f";
            exc.err = 0;
            exc.arg1 = exc.arg2 = (double)x;
            exc.retval = 0.0;
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
    float Cmath::y0f( float x ) // wrapper y0f
    {
        float z;
        struct fexception exc;
        z = __ieee754_y0f( x );
        if( m_fdlib_version == _IEEE_ || isnanf( x ) )
        {
            return z;
        }

        if( x <= (float)0.0 )
        {
            // y0f(0) = -inf  or y0f(x<0) = NaN
            exc.type = EX_DOMAIN;	// should be SING for IEEE y0f(0)
            exc.name = "y0f";
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

        if( x > (float)X_TLOSS )
        {
            // y0f(x>X_TLOSS)
            exc.type = EX_TLOSS;
            exc.name = "y0f";
            exc.err = 0;
            exc.arg1 = exc.arg2 = (double)x;
            exc.retval = 0.0;
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
    double Cmath::j0( double x )
    {
        return (double)j0f( (float)x );
    }

    //------------------------------------------------------------------------------
    double Cmath::y0( double x )
    {
        return (double)y0f( (float)x );
    }

#else

    //------------------------------------------------------------------------------
    double Cmath::j0( double x )
    {
        struct fexception exc;
        double z = __ieee754_j0( x );
        if( m_fdlib_version == _IEEE_ || isnan( x ) )
        {
            return z;
        }

        if( fabs( x ) > X_TLOSS )
        {
            // j0(|x|>X_TLOSS)
            exc.type = EX_TLOSS;
            exc.name = "j0";
            exc.err = 0;
            exc.arg1 = exc.arg2 = x;
            exc.retval = 0.0;
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
    double Cmath::y0( double x )
    {
        __QCS_FCONTEXT( "Cmath::y0" );
        double z = 0;
        __QCS_PROTECT
        {
            struct fexception exc;
            z = __ieee754_y0( x );
            if( !( m_fdlib_version == _IEEE_ || isnan( x ) ) )
            {
                if( x <= 0.0 )
                {
                    // y0(0) = -inf or y0(x<0) = NaN
                    exc.type = EX_DOMAIN;	// should be SING for IEEE y0(0)
                    exc.name = "y0";
                    exc.err = 0;
                    exc.arg1 = exc.arg2 = x;
                    if( m_fdlib_version == _SVID_ )
                    {
                        exc.retval = -Huge();
                    }
                    else
                    {
                        exc.retval = -HUGE_VAL;
                    }

                    if( m_fdlib_version == _POSIX_ )
                    {
                        errno = EDOM;
                    }
                    else if( !matherr(&exc) )
                    {
                        errno = EDOM;
                    }

                    if( exc.err != 0 )
                    {
                        errno = exc.err;
                    }
                    z = exc.retval;
                }
                else if( x > X_TLOSS )
                {
                    // y0(x>X_TLOSS)
                    exc.type = EX_TLOSS;
                    exc.name = "y0";
                    exc.err = 0;
                    exc.arg1 = exc.arg2 = x;
                    exc.retval = 0.0;
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
                    z = exc.retval;
                }
            }
        }__QCS_ENDPROTECT
        return z;
    }

    //------------------------------------------------------------------------------
    double Cmath::__ieee754_j0( double x )
    {
        static const double huge 	= 1e300;
        static const double one	= 1.0;
        static const double invsqrtpi=  5.64189583547756279280e-01; // 0x3FE20DD7, 0x50429B6D
        static const double tpi      =  6.36619772367581382433e-01; // 0x3FE45F30, 0x6DC9C883
        // R0/S0 on [0, 2.00]
        static const double R02  =  1.56249999999999947958e-02; // 0x3F8FFFFF, 0xFFFFFFFD
        static const double R03  = -1.89979294238854721751e-04; // 0xBF28E6A5, 0xB61AC6E9
        static const double R04  =  1.82954049532700665670e-06; // 0x3EBEB1D1, 0x0C503919
        static const double R05  = -4.61832688532103189199e-09; // 0xBE33D5E7, 0x73D63FCE
        static const double S01  =  1.56191029464890010492e-02; // 0x3F8FFCE8, 0x82C8C2A4
        static const double S02  =  1.16926784663337450260e-04; // 0x3F1EA6D2, 0xDD57DBF4
        static const double S03  =  5.13546550207318111446e-07; // 0x3EA13B54, 0xCE84D5A9
        static const double S04  =  1.16614003333790000205e-09; // 0x3E1408BC, 0xF4745D8F
        static const double zero = 0.0;

        double z, s, c, ss, cc, r, u, v;
        Cmp_signed__int32 hx,ix;

        get_high_word( hx, x );
        ix = hx & 0x7fffffff;
        if( ix >= 0x7ff00000 )
        {
            return one / ( x * x );
        }

        x = fabs( x );
        if( ix >= 0x40000000 )
        {
            // |x| >= 2.0
            s = sin( x );
            c = cos( x );
            ss = s - c;
            cc = s + c;
            if( ix < 0x7fe00000 )
            {
                // make sure x+x not overflow
                z = -cos( x + x );
                if( ( s * c ) < zero )
                {
                    cc = z / ss;
                }
                else
                {
                    ss = z / cc;
                }
            }
            /*j0(x) = 1/sqrt(pi) * (P(0,x)*cc - Q(0,x)*ss) / sqrt(x)
            * y0(x) = 1/sqrt(pi) * (P(0,x)*ss + Q(0,x)*cc) / sqrt(x)
            */
            if( ix > 0x48000000 )
            {
                z = ( invsqrtpi * cc ) / __ieee754_sqrt( x );
            }
            else
            {
                u = pzero( x ); v = qzero( x );
                z = invsqrtpi * ( u * cc - v * ss ) / __ieee754_sqrt( x );
            }
            return z;
        }

        if( ix < 0x3f200000 )
        {
            // |x| < 2**-13
            if( huge + x > one )
            {
                // raise inexact if x != 0
                if( ix < 0x3e400000 )
                {
                    return one;	// |x|<2**-27
                }
                else
                {
                    return one - 0.25 * x * x;
                }
            }
        }
        z = x * x;
        r = z * ( R02 + z * ( R03 + z * ( R04 + z * R05 ) ) );
        s = one + z * ( S01 + z * ( S02 + z * ( S03 + z * S04 ) ) );
        if( ix < 0x3FF00000 )
        {
            // |x| < 1.00
            return one + z * ( -0.25 + ( r / s ) );
        }
        else
        {
            u = 0.5 * x;
            return( ( one + u ) * ( one - u ) + z * ( r / s ) );
        }
    }

    //------------------------------------------------------------------------------
    double Cmath::__ieee754_y0( double x )
    {
        static const double zero = 0.0;
        static const double one	= 1.0;
        static const double invsqrtpi=  5.64189583547756279280e-01; // 0x3FE20DD7, 0x50429B6D
        static const double tpi      =  6.36619772367581382433e-01; // 0x3FE45F30, 0x6DC9C883

        static const double u00  = -7.38042951086872317523e-02; // 0xBFB2E4D6, 0x99CBD01F
        static const double u01  =  1.76666452509181115538e-01; // 0x3FC69D01, 0x9DE9E3FC
        static const double u02  = -1.38185671945596898896e-02; // 0xBF8C4CE8, 0xB16CFA97
        static const double u03  =  3.47453432093683650238e-04; // 0x3F36C54D, 0x20B29B6B
        static const double u04  = -3.81407053724364161125e-06; // 0xBECFFEA7, 0x73D25CAD
        static const double u05  =  1.95590137035022920206e-08; // 0x3E550057, 0x3B4EABD4
        static const double u06  = -3.98205194132103398453e-11; // 0xBDC5E43D, 0x693FB3C8
        static const double v01  =  1.27304834834123699328e-02; // 0x3F8A1270, 0x91C9C71A
        static const double v02  =  7.60068627350353253702e-05; // 0x3F13ECBB, 0xF578C6C1
        static const double v03  =  2.59150851840457805467e-07; // 0x3E91642D, 0x7FF202FD
        static const double v04  =  4.41110311332675467403e-10; // 0x3DFE5018, 0x3BD6D9EF

        double z, s, c, ss, cc, u, v;
        Cmp_signed__int32 hx, ix, lx;

        extract_words( hx, lx, x );
        ix = 0x7fffffff & hx;
        // Y0(NaN) is NaN, y0(-inf) is Nan, y0(inf) is 0
        if( ix >= 0x7ff00000 )
        {
            return one / ( x + x * x );
        }

        if( ( ix | lx ) == 0 )
        {
            return -one / zero;
        }

        if( hx < 0 )
        {
            return zero / zero;
        }

        if( ix >= 0x40000000 )
        {
            // |x| >= 2.0
            /* y0(x) = sqrt(2/(pi*x))*(p0(x)*sin(x0)+q0(x)*cos(x0))
            * where x0 = x-pi/4
            *      Better formula:
            *              cos(x0) = cos(x)cos(pi/4)+sin(x)sin(pi/4)
            *                      =  1/sqrt(2) * (sin(x) + cos(x))
            *              sin(x0) = sin(x)cos(3pi/4)-cos(x)sin(3pi/4)
            *                      =  1/sqrt(2) * (sin(x) - cos(x))
            * To avoid cancellation, use
            *              sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
            * to compute the worse one.
            */
            s = sin( x );
            c = cos( x );
            ss = s - c;
            cc = s + c;
            /*j0(x) = 1/sqrt(pi) * (P(0,x)*cc - Q(0,x)*ss) / sqrt(x)
            * y0(x) = 1/sqrt(pi) * (P(0,x)*ss + Q(0,x)*cc) / sqrt(x)
            */
            if( ix < 0x7fe00000 )
            {
                // make sure x+x not overflow
                z = -cos( x + x );
                if( ( s * c ) < zero )
                {
                    cc = z / ss;
                }
                else
                {
                    ss = z / cc;
                }
            }

            if( ix > 0x48000000 )
            {
                z = ( invsqrtpi * ss ) / __ieee754_sqrt( x );
            }
            else
            {
                u = pzero( x );
                v = qzero( x );
                z = invsqrtpi * ( u * ss + v * cc ) / __ieee754_sqrt( x );
            }
            return z;
        }

        if( ix <= 0x3e400000 )
        {
            // x < 2**-27
            return( u00 + tpi * __ieee754_log( x ) );
        }
        z = x * x;
        u = u00 + z * ( u01 + z * ( u02 + z * ( u03 + z * ( u04 + z * ( u05 + z * u06 ) ) ) ) );
        v = one + z * ( v01 + z * ( v02 + z * ( v03 + z * v04 ) ) );
        return( u / v  + tpi * ( __ieee754_j0( x ) * __ieee754_log( x ) ) );
    }

    //------------------------------------------------------------------------------
    /* The asymptotic expansions of pzero is
    *	1 - 9/128 s^2 + 11025/98304 s^4 - ...,	where s = 1/x.
    * For x >= 2, We approximate pzero by
    * 	pzero(x) = 1 + (R/S)
    * where  R = pR0 + pR1*s^2 + pR2*s^4 + ... + pR5*s^10
    * 	  S = 1 + pS0*s^2 + ... + pS4*s^10
    * and
    *	| pzero(x)-1-R/S | <= 2  ** ( -60.26)
    */
    double Cmath::pzero( double x )
    {
        static const double one	= 1.0;

        static const double pR8[ 6 ] =
        {
            // for x in [inf, 8]=1/[0,0.125]
            0.00000000000000000000e+00, // 0x00000000, 0x00000000
            -7.03124999999900357484e-02, // 0xBFB1FFFF, 0xFFFFFD32
            -8.08167041275349795626e+00, // 0xC02029D0, 0xB44FA779
            -2.57063105679704847262e+02, // 0xC0701102, 0x7B19E863
            -2.48521641009428822144e+03, // 0xC0A36A6E, 0xCD4DCAFC
            -5.25304380490729545272e+03, // 0xC0B4850B, 0x36CC643D
        };

        static const double pS8[ 5 ] =
        {
            1.16534364619668181717e+02, // 0x405D2233, 0x07A96751
            3.83374475364121826715e+03, // 0x40ADF37D, 0x50596938
            4.05978572648472545552e+04, // 0x40E3D2BB, 0x6EB6B05F
            1.16752972564375915681e+05, // 0x40FC810F, 0x8F9FA9BD
            4.76277284146730962675e+04, // 0x40E74177, 0x4F2C49DC
        };

        static const double pR5[ 6 ] =
        {
            // for x in [8,4.5454]=1/[0.125,0.22001]
            -1.14125464691894502584e-11, // 0xBDA918B1, 0x47E495CC
            -7.03124940873599280078e-02, // 0xBFB1FFFF, 0xE69AFBC6
            -4.15961064470587782438e+00, // 0xC010A370, 0xF90C6BBF
            -6.76747652265167261021e+01, // 0xC050EB2F, 0x5A7D1783
            -3.31231299649172967747e+02, // 0xC074B3B3, 0x6742CC63
            -3.46433388365604912451e+02, // 0xC075A6EF, 0x28A38BD7
        };

        static const double pS5[ 5 ] =
        {
            6.07539382692300335975e+01, // 0x404E6081, 0x0C98C5DE
            1.05125230595704579173e+03, // 0x40906D02, 0x5C7E2864
            5.97897094333855784498e+03, // 0x40B75AF8, 0x8FBE1D60
            9.62544514357774460223e+03, // 0x40C2CCB8, 0xFA76FA38
            2.40605815922939109441e+03, // 0x40A2CC1D, 0xC70BE864
        };

        static const double pR3[ 6 ] =
        {
            // for x in [4.547,2.8571]=1/[0.2199,0.35001]
            -2.54704601771951915620e-09, // 0xBE25E103, 0x6FE1AA86
            -7.03119616381481654654e-02, // 0xBFB1FFF6, 0xF7C0E24B
            -2.40903221549529611423e+00, // 0xC00345B2, 0xAEA48074
            -2.19659774734883086467e+01, // 0xC035F74A, 0x4CB94E14
            -5.80791704701737572236e+01, // 0xC04D0A22, 0x420A1A45
            -3.14479470594888503854e+01, // 0xC03F72AC, 0xA892D80F
        };

        static const double pS3[ 5 ] =
        {
            3.58560338055209726349e+01, // 0x4041ED92, 0x84077DD3
            3.61513983050303863820e+02, // 0x40769839, 0x464A7C0E
            1.19360783792111533330e+03, // 0x4092A66E, 0x6D1061D6
            1.12799679856907414432e+03, // 0x40919FFC, 0xB8C39B7E
            1.73580930813335754692e+02, // 0x4065B296, 0xFC379081
        };

        static const double pR2[ 6 ] =
        {
            // for x in [2.8570,2]=1/[0.3499,0.5]
            -8.87534333032526411254e-08, // 0xBE77D316, 0xE927026D
            -7.03030995483624743247e-02, // 0xBFB1FF62, 0x495E1E42
            -1.45073846780952986357e+00, // 0xBFF73639, 0x8A24A843
            -7.63569613823527770791e+00, // 0xC01E8AF3, 0xEDAFA7F3
            -1.11931668860356747786e+01, // 0xC02662E6, 0xC5246303
            -3.23364579351335335033e+00, // 0xC009DE81, 0xAF8FE70F
        };

        static const double pS2[ 5 ] =
        {
            2.22202997532088808441e+01, // 0x40363865, 0x908B5959
            1.36206794218215208048e+02, // 0x4061069E, 0x0EE8878F
            2.70470278658083486789e+02, // 0x4070E786, 0x42EA079B
            1.53875394208320329881e+02, // 0x40633C03, 0x3AB6FAFF
            1.46576176948256193810e+01, // 0x402D50B3, 0x44391809
        };

        const double* p,*q;
        double z, r, s;
        Cmp_signed__int32 ix;
        get_high_word( ix, x );
        ix &= 0x7fffffff;
        if( ix >= 0x40200000 )
        {
            p = pR8;
            q = pS8;
        }
        else if( ix >= 0x40122E8B )
        {
            p = pR5;
            q = pS5;
        }
        else if( ix >= 0x4006DB6D )
        {
            p = pR3;
            q = pS3;
        }
        else
        {
            p = pR2;
            q = pS2;
        }
        z = one / ( x * x );
        r = p[ 0 ] + z * ( p[ 1 ] + z * ( p[ 2 ] + z * ( p[ 3 ] + z * ( p[ 4 ] + z * p[ 5 ] ) ) ) );
        s = one + z * ( q[ 0 ] + z * ( q[ 1 ] + z * ( q[ 2 ] + z * ( q[ 3 ] + z * q[ 4 ] ) ) ) );
        return one + r / s;
    }

    //------------------------------------------------------------------------------
    /* For x >= 8, the asymptotic expansions of qzero is
    *	-1/8 s + 75/1024 s^3 - ..., where s = 1/x.
    * We approximate qzero by
    * 	qzero(x) = s*(-1.25 + (R/S))
    * where  R = qR0 + qR1*s^2 + qR2*s^4 + ... + qR5*s^10
    * 	  S = 1 + qS0*s^2 + ... + qS5*s^12
    * and
    *	| qzero(x)/s +1.25-R/S | <= 2  ** ( -61.22)
    */
    double Cmath::qzero( double x )
    {
        static const double one	= 1.0;

        static const double qR8[ 6 ] =
        {
            // for x in [inf, 8]=1/[0,0.125]
            0.00000000000000000000e+00, // 0x00000000, 0x00000000
            7.32421874999935051953e-02, // 0x3FB2BFFF, 0xFFFFFE2C
            1.17682064682252693899e+01, // 0x40278952, 0x5BB334D6
            5.57673380256401856059e+02, // 0x40816D63, 0x15301825
            8.85919720756468632317e+03, // 0x40C14D99, 0x3E18F46D
            3.70146267776887834771e+04, // 0x40E212D4, 0x0E901566
        };

        static const double qS8[ 6 ] =
        {
            1.63776026895689824414e+02, // 0x406478D5, 0x365B39BC
            8.09834494656449805916e+03, // 0x40BFA258, 0x4E6B0563
            1.42538291419120476348e+05, // 0x41016652, 0x54D38C3F
            8.03309257119514397345e+05, // 0x412883DA, 0x83A52B43
            8.40501579819060512818e+05, // 0x4129A66B, 0x28DE0B3D
            -3.43899293537866615225e+05, // 0xC114FD6D, 0x2C9530C5
        };

        static const double qR5[ 6 ] =
        {
            // for x in [8,4.5454]=1/[0.125,0.22001]
            1.84085963594515531381e-11, // 0x3DB43D8F, 0x29CC8CD9
            7.32421766612684765896e-02, // 0x3FB2BFFF, 0xD172B04C
            5.83563508962056953777e+00, // 0x401757B0, 0xB9953DD3
            1.35111577286449829671e+02, // 0x4060E392, 0x0A8788E9
            1.02724376596164097464e+03, // 0x40900CF9, 0x9DC8C481
            1.98997785864605384631e+03, // 0x409F17E9, 0x53C6E3A6
        };

        static const double qS5[ 6 ] =
        {
            8.27766102236537761883e+01, // 0x4054B1B3, 0xFB5E1543
            2.07781416421392987104e+03, // 0x40A03BA0, 0xDA21C0CE
            1.88472887785718085070e+04, // 0x40D267D2, 0x7B591E6D
            5.67511122894947329769e+04, // 0x40EBB5E3, 0x97E02372
            3.59767538425114471465e+04, // 0x40E19118, 0x1F7A54A0
            -5.35434275601944773371e+03, // 0xC0B4EA57, 0xBEDBC609
        };

        static const double qR3[ 6 ] =
        {
            // for x in [4.547,2.8571]=1/[0.2199,0.35001]
            4.37741014089738620906e-09, // 0x3E32CD03, 0x6ADECB82
            7.32411180042911447163e-02, // 0x3FB2BFEE, 0x0E8D0842
            3.34423137516170720929e+00, // 0x400AC0FC, 0x61149CF5
            4.26218440745412650017e+01, // 0x40454F98, 0x962DAEDD
            1.70808091340565596283e+02, // 0x406559DB, 0xE25EFD1F
            1.66733948696651168575e+02, // 0x4064D77C, 0x81FA21E0
        };

        static const double qS3[ 6 ] =
        {
            4.87588729724587182091e+01, // 0x40486122, 0xBFE343A6
            7.09689221056606015736e+02, // 0x40862D83, 0x86544EB3
            3.70414822620111362994e+03, // 0x40ACF04B, 0xE44DFC63
            6.46042516752568917582e+03, // 0x40B93C6C, 0xD7C76A28
            2.51633368920368957333e+03, // 0x40A3A8AA, 0xD94FB1C0
            -1.49247451836156386662e+02, // 0xC062A7EB, 0x201CF40F
        };

        static const double qR2[ 6 ] =
        {	// for x in [2.8570,2]=1/[0.3499,0.5]
            1.50444444886983272379e-07, // 0x3E84313B, 0x54F76BDB
            7.32234265963079278272e-02, // 0x3FB2BEC5, 0x3E883E34
            1.99819174093815998816e+00, // 0x3FFFF897, 0xE727779C
            1.44956029347885735348e+01, // 0x402CFDBF, 0xAAF96FE5
            3.16662317504781540833e+01, // 0x403FAA8E, 0x29FBDC4A
            1.62527075710929267416e+01, // 0x403040B1, 0x71814BB4
        };

        static const double qS2[ 6 ] =
        {
            3.03655848355219184498e+01, // 0x403E5D96, 0xF7C07AED
            2.69348118608049844624e+02, // 0x4070D591, 0xE4D14B40
            8.44783757595320139444e+02, // 0x408A6645, 0x22B3BF22
            8.82935845112488550512e+02, // 0x408B977C, 0x9C5CC214
            2.12666388511798828631e+02, // 0x406A9553, 0x0E001365
            -5.31095493882666946917e+00, // 0xC0153E6A, 0xF8B32931
        };

        const double* p, *q;
        double s, r, z;
        Cmp_signed__int32 ix;
        get_high_word( ix, x );
        ix &= 0x7fffffff;
        if( ix >= 0x40200000 )
        {
            p = qR8;
            q = qS8;
        }
        else if( ix >= 0x40122E8B )
        {
            p = qR5;
            q= qS5;
        }
        else if( ix >= 0x4006DB6D )
        {
            p = qR3;
            q = qS3;
        }
        else
        {
            p = qR2;
            q = qS2;
        }
        z = one / ( x * x );
        r = p[ 0 ] + z * ( p[ 1 ] + z * ( p[ 2 ] + z * ( p[ 3 ] + z * ( p[ 4 ] + z * p[ 5 ] ) ) ) );
        s = one + z * ( q[ 0 ] + z * ( q[ 1 ] + z * ( q[ 2 ] + z * ( q[ 3 ] + z * ( q[ 4 ] + z * q[ 5 ] ) ) ) ) );
        return ( -.125 + r / s ) / x;
    }

#endif //defined(_DOUBLE_IS_32BITS)

    //------------------------------------------------------------------------------
    float Cmath::__ieee754_j0f( float x )
    {
        static const float huge = 1e30;
        static const float one = 1.0;
        static const float invsqrtpi = 5.6418961287e-01; // 0x3f106ebb
        static const float tpi =  6.3661974669e-01; // 0x3f22f983
        // R0/S0 on [0, 2.00]
        static const float R02 =  1.5625000000e-02; // 0x3c800000
        static const float R03 = -1.8997929874e-04; // 0xb947352e
        static const float R04 =  1.8295404516e-06; // 0x35f58e88
        static const float R05 = -4.6183270541e-09; // 0xb19eaf3c
        static const float S01 =  1.5619102865e-02; // 0x3c7fe744
        static const float S02 =  1.1692678527e-04; // 0x38f53697
        static const float S03 =  5.1354652442e-07; // 0x3509daa6
        static const float S04 =  1.1661400734e-09; // 0x30a045e8

        static const float zero = 0.0;

        float z, s, c, ss, cc, r, u, v;
        Cmp_signed__int32 hx, ix;

        get_float_word( hx, x );
        ix = hx & 0x7fffffff;
        if( !uword_isfinite( ix ) )
        {
            return one / ( x * x );
        }
        x = fabsf( x );
        if( ix >= 0x40000000 )
        {
            // |x| >= 2.0
            s = sinf( x );
            c = cosf( x );
            ss = s - c;
            cc = s + c;
            if( ix <= uword_half_max() )
            {
                // make sure x+x not overflow
                z = -cosf( x + x );
                if( ( s * c ) < zero )
                {
                    cc = z / ss;
                }
                else
                {
                    ss = z / cc;
                }
            }
            /*j0(x) = 1/sqrt(pi) * (P(0,x)*cc - Q(0,x)*ss) / sqrt(x)
            * y0(x) = 1/sqrt(pi) * (P(0,x)*ss + Q(0,x)*cc) / sqrt(x)
            */
            if( ix > 0x80000000 )
            {
                z = ( invsqrtpi * cc ) / __ieee754_sqrtf( x );
            }
            else
            {
                u = pzerof( x );
                v = qzerof( x );
                z = invsqrtpi * ( u * cc - v * ss ) / __ieee754_sqrtf( x );
            }
            return z;
        }

        if( ix < 0x39000000 )
        {
            // |x| < 2**-13
            if( huge + x > one )
            {
                // raise inexact if x != 0
                if( ix < 0x32000000 )
                {
                    return one;	// |x|<2**-27
                }
                else
                {
                    return one - (float)0.25 * x * x;
                }
            }
        }
        z = x * x;
        r =  z * ( R02 + z * ( R03 + z * ( R04 + z * R05 ) ) );
        s =  one + z * ( S01 + z * ( S02 + z * ( S03 + z * S04 ) ) );
        if( ix < 0x3F800000 )
        {
            // |x| < 1.00
            return one + z * ( (float)-0.25 + ( r / s ) );
        }
        else
        {
            u = (float)0.5 * x;
            return( ( one + u ) * ( one - u ) + z * ( r / s ) );
        }
    }

    //------------------------------------------------------------------------------
    float Cmath::__ieee754_y0f( float x )
    {
        static const float zero = 0.0;
        static const float one = 1.0;
        static const float invsqrtpi = 5.6418961287e-01; // 0x3f106ebb
        static const float tpi = 6.3661974669e-01; // 0x3f22f983
        // R0/S0 on [0, 2.00]
        static const float u00 = -7.3804296553e-02; // 0xbd9726b5
        static const float u01 =  1.7666645348e-01; // 0x3e34e80d
        static const float u02 = -1.3818567619e-02; // 0xbc626746
        static const float u03 =  3.4745343146e-04; // 0x39b62a69
        static const float u04 = -3.8140706238e-06; // 0xb67ff53c
        static const float u05 =  1.9559013964e-08; // 0x32a802ba
        static const float u06 = -3.9820518410e-11; // 0xae2f21eb
        static const float v01 =  1.2730483897e-02; // 0x3c509385
        static const float v02 =  7.6006865129e-05; // 0x389f65e0
        static const float v03 =  2.5915085189e-07; // 0x348b216c
        static const float v04 =  4.4111031494e-10; // 0x2ff280c2

        float z, s, c, ss, cc, u, v;
        Cmp_signed__int32 hx, ix;

        get_float_word( hx, x );
        ix = 0x7fffffff & hx;
        // Y0(NaN) is NaN, y0(-inf) is Nan, y0(inf) is 0
        if( !uword_isfinite( ix ) )
        {
            return one / ( x + x * x );
        }

        if( uword_is_zero( ix ) )
        {
            return -one / zero;
        }

        if( hx < 0 )
        {
            return zero / zero;
        }

        if( ix >= 0x40000000 )
        {
            // |x| >= 2.0
            /* y0(x) = sqrt(2/(pi*x))*(p0(x)*sin(x0)+q0(x)*cos(x0))
            * where x0 = x-pi/4
            *      Better formula:
            *              cos(x0) = cos(x)cos(pi/4)+sin(x)sin(pi/4)
            *                      =  1/sqrt(2) * (sin(x) + cos(x))
            *              sin(x0) = sin(x)cos(3pi/4)-cos(x)sin(3pi/4)
            *                      =  1/sqrt(2) * (sin(x) - cos(x))
            * To avoid cancellation, use
            *              sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
            * to compute the worse one.
            */
            s = sinf( x );
            c = cosf( x );
            ss = s - c;
            cc = s + c;
            /*j0(x) = 1/sqrt(pi) * (P(0,x)*cc - Q(0,x)*ss) / sqrt(x)
            * y0(x) = 1/sqrt(pi) * (P(0,x)*ss + Q(0,x)*cc) / sqrt(x)
            */
            if( ix <= uword_half_max() )
            {	// make sure x+x not overflow
                z = -cosf( x + x );
                if( ( s * c ) < zero )
                {
                    cc = z / ss;
                }
                else
                {
                    ss = z / cc;
                }
            }

            if( ix > 0x80000000 )
            {
                z = ( invsqrtpi * ss ) / __ieee754_sqrtf( x );
            }
            else
            {
                u = pzerof( x );
                v = qzerof( x );
                z = invsqrtpi * ( u * ss + v * cc ) / __ieee754_sqrtf( x );
            }
            return z;
        }

        if( ix <= 0x32000000 )
        {
            // x < 2**-27
            return( u00 + tpi * __ieee754_logf( x ) );
        }
        z = x * x;
        u = u00 + z * ( u01 + z * ( u02 + z * ( u03 + z * ( u04 + z * ( u05 + z * u06 ) ) ) ) );
        v = one + z * ( v01 + z * ( v02 + z * ( v03 + z * v04 ) ) );
        return( u / v + tpi * ( __ieee754_j0f( x ) * __ieee754_logf( x ) ) );
    }

    //------------------------------------------------------------------------------
    /* The asymptotic expansions of pzero is
    *	1 - 9/128 s^2 + 11025/98304 s^4 - ...,	where s = 1/x.
    * For x >= 2, We approximate pzero by
    * 	pzero(x) = 1 + (R/S)
    * where  R = pR0 + pR1*s^2 + pR2*s^4 + ... + pR5*s^10
    * 	  S = 1 + pS0*s^2 + ... + pS4*s^10
    * and
    *	| pzero(x)-1-R/S | <= 2  ** ( -60.26)
    */
    float Cmath::pzerof( float x )
    {
        static const float one = 1.0;

        static const float pR8[ 6 ] =
        {
            // for x in [inf, 8]=1/[0,0.125]
            0.0000000000e+00, // 0x00000000
            -7.0312500000e-02, // 0xbd900000
            -8.0816707611e+00, // 0xc1014e86
            -2.5706311035e+02, // 0xc3808814
            -2.4852163086e+03, // 0xc51b5376
            -5.2530439453e+03, // 0xc5a4285a
        };

        static const float pS8[ 5 ] =
        {
            1.1653436279e+02, // 0x42e91198
            3.8337448730e+03, // 0x456f9beb
            4.0597855469e+04, // 0x471e95db
            1.1675296875e+05, // 0x47e4087c
            4.7627726562e+04, // 0x473a0bba
        };

        static const float pR5[ 6 ] =
        {
            // for x in [8,4.5454]=1/[0.125,0.22001]
            -1.1412546255e-11, // 0xad48c58a
            -7.0312492549e-02, // 0xbd8fffff
            -4.1596107483e+00, // 0xc0851b88
            -6.7674766541e+01, // 0xc287597b
            -3.3123129272e+02, // 0xc3a59d9b
            -3.4643338013e+02, // 0xc3ad3779
        };

        static const float pS5[ 5 ] =
        {
            6.0753936768e+01, // 0x42730408
            1.0512523193e+03, // 0x44836813
            5.9789707031e+03, // 0x45bad7c4
            9.6254453125e+03, // 0x461665c8
            2.4060581055e+03, // 0x451660ee
        };

        static const float pR3[ 6 ] =
        {
            // for x in [4.547,2.8571]=1/[0.2199,0.35001]
            -2.5470459075e-09, // 0xb12f081b
            -7.0311963558e-02, // 0xbd8fffb8
            -2.4090321064e+00, // 0xc01a2d95
            -2.1965976715e+01, // 0xc1afba52
            -5.8079170227e+01, // 0xc2685112
            -3.1447946548e+01, // 0xc1fb9565
        };

        static const float pS3[ 5 ] =
        {
            3.5856033325e+01, // 0x420f6c94
            3.6151397705e+02, // 0x43b4c1ca
            1.1936077881e+03, // 0x44953373
            1.1279968262e+03, // 0x448cffe6
            1.7358093262e+02, // 0x432d94b8
        };

        static const float pR2[ 6 ] =
        {
            // for x in [2.8570,2]=1/[0.3499,0.5]
            -8.8753431271e-08, // 0xb3be98b7
            -7.0303097367e-02, // 0xbd8ffb12
            -1.4507384300e+00, // 0xbfb9b1cc
            -7.6356959343e+00, // 0xc0f4579f
            -1.1193166733e+01, // 0xc1331736
            -3.2336456776e+00, // 0xc04ef40d
        };

        static const float pS2[ 5 ] =
        {
            2.2220300674e+01, // 0x41b1c32d
            1.3620678711e+02, // 0x430834f0
            2.7047027588e+02, // 0x43873c32
            1.5387539673e+02, // 0x4319e01a
            1.4657617569e+01, // 0x416a859a
        };

        const float* p, *q;
        float z, r, s;
        Cmp_signed__int32 ix;
        get_float_word( ix, x );
        ix &= 0x7fffffff;
        if( ix >= 0x41000000 )
        {
            p = pR8;
            q = pS8;
        }
        else if( ix >= 0x40f71c58 )
        {
            p = pR5;
            q = pS5;
        }
        else if( ix >= 0x4036db68 )
        {
            p = pR3;
            q = pS3;
        }
        else
        {
            p = pR2;
            q = pS2;
        }
        z = one / ( x * x );
        r = p[ 0 ] + z * ( p[ 1 ] + z * ( p[ 2 ] + z * ( p[ 3 ] + z * ( p[ 4 ] + z * p[ 5 ] ) ) ) );
        s = one + z * ( q[ 0 ] + z * ( q[ 1 ] + z * ( q[ 2 ] + z * ( q[ 3 ] + z * q[ 4 ] ) ) ) );
        return one + r / s;
    }

    //------------------------------------------------------------------------------
    /* For x >= 8, the asymptotic expansions of qzero is
    *	-1/8 s + 75/1024 s^3 - ..., where s = 1/x.
    * We approximate qzero by
    * 	qzero(x) = s*(-1.25 + (R/S))
    * where  R = qR0 + qR1*s^2 + qR2*s^4 + ... + qR5*s^10
    * 	  S = 1 + qS0*s^2 + ... + qS5*s^12
    * and
    *	| qzero(x)/s +1.25-R/S | <= 2  ** ( -61.22)
    */
    float Cmath::qzerof( float x )
    {
        static const float one = 1.0;

        static const float qR8[ 6 ] =
        {
            // for x in [inf, 8]=1/[0,0.125]
            0.0000000000e+00, // 0x00000000
            7.3242187500e-02, // 0x3d960000
            1.1768206596e+01, // 0x413c4a93
            5.5767340088e+02, // 0x440b6b19
            8.8591972656e+03, // 0x460a6cca
            3.7014625000e+04, // 0x471096a0
        };

        static const float qS8[ 6 ] =
        {
            1.6377603149e+02, // 0x4323c6aa
            8.0983447266e+03, // 0x45fd12c2
            1.4253829688e+05, // 0x480b3293
            8.0330925000e+05, // 0x49441ed4
            8.4050156250e+05, // 0x494d3359
            -3.4389928125e+05, // 0xc8a7eb69
        };

        static const float qR5[ 6 ] =
        {
            // for x in [8,4.5454]=1/[0.125,0.22001]
            1.8408595828e-11, // 0x2da1ec79
            7.3242180049e-02, // 0x3d95ffff
            5.8356351852e+00, // 0x40babd86
            1.3511157227e+02, // 0x43071c90
            1.0272437744e+03, // 0x448067cd
            1.9899779053e+03, // 0x44f8bf4b
        };

        static const float qS5[ 6 ] =
        {
            8.2776611328e+01, // 0x42a58da0
            2.0778142090e+03, // 0x4501dd07
            1.8847289062e+04, // 0x46933e94
            5.6751113281e+04, // 0x475daf1d
            3.5976753906e+04, // 0x470c88c1
            -5.3543427734e+03, // 0xc5a752be
        };

        static const float qR3[ 6 ] =
        {
            // for x in [4.547,2.8571]=1/[0.2199,0.35001]
            4.3774099900e-09, // 0x3196681b
            7.3241114616e-02, // 0x3d95ff70
            3.3442313671e+00, // 0x405607e3
            4.2621845245e+01, // 0x422a7cc5
            1.7080809021e+02, // 0x432acedf
            1.6673394775e+02, // 0x4326bbe4
        };

        static const float qS3[ 6 ] =
        {
            4.8758872986e+01, // 0x42430916
            7.0968920898e+02, // 0x44316c1c
            3.7041481934e+03, // 0x4567825f
            6.4604252930e+03, // 0x45c9e367
            2.5163337402e+03, // 0x451d4557
            -1.4924745178e+02, // 0xc3153f59
        };

        static const float qR2[ 6 ] =
        {
            // for x in [2.8570,2]=1/[0.3499,0.5]
            1.5044444979e-07, // 0x342189db
            7.3223426938e-02, // 0x3d95f62a
            1.9981917143e+00, // 0x3fffc4bf
            1.4495602608e+01, // 0x4167edfd
            3.1666231155e+01, // 0x41fd5471
            1.6252708435e+01, // 0x4182058c
        };

        static const float qS2[ 6 ] =
        {
            3.0365585327e+01, // 0x41f2ecb8
            2.6934811401e+02, // 0x4386ac8f
            8.4478375244e+02, // 0x44533229
            8.8293585205e+02, // 0x445cbbe5
            2.1266638184e+02, // 0x4354aa98
            -5.3109550476e+00, // 0xc0a9f358
        };

        const float* p, *q;
        float s, r, z;
        Cmp_signed__int32 ix;
        get_float_word( ix, x );
        ix &= 0x7fffffff;
        if( ix >= 0x41000000 )
        {
            p = qR8;
            q = qS8;
        }
        else if( ix >= 0x40f71c58 )
        {
            p = qR5;
            q = qS5;
        }
        else if( ix >= 0x4036db68 )
        {
            p = qR3;
            q = qS3;
        }
        else
        {
            p = qR2;
            q = qS2;
        }
        z = one / ( x * x );
        r = p[ 0 ] + z * ( p[ 1 ] + z * ( p[ 2 ] + z * ( p[ 3 ] + z * ( p[ 4 ] + z * p[ 5 ] ) ) ) );
        s = one + z * ( q[ 0 ] + z * ( q[ 1 ] + z * ( q[ 2 ] + z * ( q[ 3 ] + z * ( q[ 4 ] + z * q[ 5 ] ) ) ) ) );
        return ( -(float).125 + r / s ) / x;
    }

};//namespace nsBaseCRT
