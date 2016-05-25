
/* @(#)e_atan2.c 5.1 93/09/24 */
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
/* __ieee754_atan2(y,x)
 * Method :
 *	1. Reduce y to positive by atan2(y,x)=-atan2(-y,x).
 *	2. Reduce x to positive by (if x and y are unexceptional):
 *		ARG (x+iy) = arctan(y/x)   	   ... if x > 0,
 *		ARG (x+iy) = pi - arctan[y/(-x)]   ... if x < 0,
 *
 * Special cases:
 *
 *	ATAN2((anything), NaN ) is NaN;
 *	ATAN2(NAN , (anything) ) is NaN;
 *	ATAN2(+-0, +(anything but NaN)) is +-0  ;
 *	ATAN2(+-0, -(anything but NaN)) is +-pi ;
 *	ATAN2(+-(anything but 0 and NaN), 0) is +-pi/2;
 *	ATAN2(+-(anything but INF and NaN), +INF) is +-0 ;
 *	ATAN2(+-(anything but INF and NaN), -INF) is +-pi;
 *	ATAN2(+-INF,+INF ) is +-pi/4 ;
 *	ATAN2(+-INF,-INF ) is +-3pi/4;
 *	ATAN2(+-INF, (anything but,0,NaN, and INF)) is +-pi/2;
 *
 * Constants:
 * The hexadecimal values are the intended ones for the following
 * constants. The decimal values may be used, provided that the
 * compiler will convert from decimal to binary accurately enough
 * to produce the hexadecimal values shown.
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
    //------------------------------------------------------------------------------
    float Cmath::atan2f( float y, float x )	// wrapper atan2f
    {
        float z;
        struct fexception exc;
        z = __ieee754_atan2f( y, x );
        if( m_fdlib_version == _IEEE_ || isnanf( x ) || isnanf( y ) )
        {
            return z;
        }

        if( x == (float)0.0 && y == (float)0.0 )
        {
            // atan2f(+-0,+-0)
            exc.arg1 = y;
            exc.arg2 = x;
            exc.err = 0;
            exc.type = EX_DOMAIN;
            exc.name = "atan2f";
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
    double Cmath::atan2( double y, double x )
    {
        return (double)atan2f( (float)y, (float)x );
    }

#else

    //------------------------------------------------------------------------------
    double Cmath::atan2( double y, double x )
    {
        double z;
        struct fexception exc;
        z = __ieee754_atan2( y, x );
        if( m_fdlib_version == _IEEE_ || isnan( x ) || isnan( y ) )
        {
            return z;
        }

        if( x == 0.0 && y == 0.0 )
        {
            // atan2(+-0,+-0)
            exc.arg1 = y;
            exc.arg2 = x;
            exc.type = EX_DOMAIN;
            exc.name = "atan2";
            exc.err = 0;
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
    double Cmath::__ieee754_atan2( double y, double x )
    {
        static const double tiny	= 1.0e-300;
        static const double zero	= 0.0;
        static const double pi_o_4  = 7.8539816339744827900E-01; // 0x3FE921FB, 0x54442D18
        static const double pi_o_2  = 1.5707963267948965580E+00; // 0x3FF921FB, 0x54442D18
        static const double pi      = 3.1415926535897931160E+00; // 0x400921FB, 0x54442D18
        static const double pi_lo   = 1.2246467991473531772E-16; // 0x3CA1A626, 0x33145C07

        double z;
        Cmp_signed__int32 k, m, hx, hy, ix, iy;
        Cmp_unsigned__int32 lx, ly;

        extract_words( hx, lx, x );
        ix = hx & 0x7fffffff;
        extract_words( hy, ly, y );
        iy = hy & 0x7fffffff;
        if( ( ( ix | ( ( lx | -lx ) >> 31 ) ) > 0x7ff00000 ) || ( ( iy | ( ( ly | -ly ) >> 31 ) ) > 0x7ff00000 ) )	// x or y is NaN
        {
            return x + y;
        }

        if( ( hx - 0x3ff00000 | lx ) == 0 )
        {
            return atan( y );   // x=1.0
        }

        m = ( ( hy >> 31 ) & 1 ) | ( ( hx >> 30 ) & 2 ); // 2*sign(x)+sign(y)

        // when y = 0
        if( ( iy | ly ) == 0 )
        {
            switch( m )
            {
            case 0:
            case 1: return y; 			// atan(+-0,+anything)=+-0
            case 2: return  pi + tiny;	// atan(+0,-anything) = pi
            case 3: return -pi - tiny;	// atan(-0,-anything) =-pi
            }
        }

        // when x = 0
        if( ( ix | lx ) == 0 )
        {
            return ( hy < 0 ) ? -pi_o_2 - tiny : pi_o_2 + tiny;
        }

        // when x is INF
        if( ix == 0x7ff00000 )
        {
            if( iy == 0x7ff00000 )
            {
                switch( m )
                {
                case 0: return  pi_o_4 + tiny;		// atan(+INF,+INF)
                case 1: return -pi_o_4 - tiny;		// atan(-INF,+INF)
                case 2: return  3.0 * pi_o_4 + tiny;// atan(+INF,-INF)
                case 3: return -3.0 * pi_o_4 - tiny;// atan(-INF,-INF)
                }
            }
            else
            {
                switch( m )
                {
                case 0: return  zero;		// atan(+...,+INF)
                case 1: return -zero;		// atan(-...,+INF)
                case 2: return  pi + tiny;	// atan(+...,-INF)
                case 3: return -pi - tiny;	// atan(-...,-INF)
                }
            }
        }

        // when y is INF
        if( iy == 0x7ff00000 )
        {
            return ( hy < 0 ) ? -pi_o_2 - tiny : pi_o_2 + tiny;
        }

        // compute y/x
        k = ( iy - ix ) >> 20;
        if( k > 60 )
        {
            z = pi_o_2 + 0.5 * pi_lo; 	// |y/x| >  2**60
        }
        else if( hx < 0 && k < -60 )
        {
            z = 0.0;	// |y|/x < -2**60
        }
        else
        {
            z = atan( fabs( y / x ) );		// safe to do y / x
        }

        switch( m )
        {
        case 0: return z;					// atan(+,+)
        case 1:
            {
                Cmp_unsigned__int32 zh;
                get_high_word( zh, z );
                set_high_word( z, zh ^ 0x80000000 );
            }
            return z;						// atan(-,+)
        case 2: return pi - ( z - pi_lo );	// atan(+,-)
        default: // case 3
        return ( z - pi_lo ) - pi;			// atan(-,-)
        }
    }

#endif//defined(_DOUBLE_IS_32BITS)

    //------------------------------------------------------------------------------
    float Cmath::__ieee754_atan2f( float y, float x )
    {
        static const float tiny		= 1.0e-30;
        static const float zero		= 0.0;
        static const float pi_o_4  = 7.8539818525e-01; // 0x3f490fdb
        static const float pi_o_2  = 1.5707963705e+00; // 0x3fc90fdb
        static const float pi      = 3.1415927410e+00;  // 0x40490fdb
        static const float pi_lo   = -8.7422776573e-08; // 0xb3bbbd2e

        float z;
        Cmp_signed__int32 k, m, hx, hy, ix, iy;

        get_float_word( hx, x );
        ix = hx & 0x7fffffff;
        get_float_word( hy, y );
        iy = hy & 0x7fffffff;
        if( uword_isnan( ix ) || uword_isnan( iy ) )	// x or y is NaN
        {
            return x + y;
        }

        if( hx == 0x3f800000 )
        {
            return atanf( y );   // x=1.0
        }

        m = ( ( hy >> 31 ) & 1 ) | ( ( hx >> 30 ) & 2 ); // 2*sign(x)+sign(y)

        // when y = 0
        if( uword_is_zero( iy ) )
        {
            switch( m )
            {
            case 0:
            case 1: return y;	 		// atan(+-0,+anything)=+-0
            case 2: return pi + tiny;	// atan(+0,-anything) = pi
            case 3: return -pi - tiny;	// atan(-0,-anything) =-pi
            }
        }

        // when x = 0
        if( uword_is_zero( ix ) )
        {
            return ( hy < 0 ) ? -pi_o_2 - tiny : pi_o_2 + tiny;
        }

        // when x is INF
        if( uword_is_infinite( ix ) )
        {
            if( uword_is_infinite( iy ) )
            {
                switch( m )
                {
                case 0: return pi_o_4 + tiny;				// atan(+INF,+INF)
                case 1: return -pi_o_4 - tiny;				// atan(-INF,+INF)
                case 2: return (float)3.0 * pi_o_4 + tiny;	// atan(+INF,-INF)
                case 3: return (float)-3.0 * pi_o_4 - tiny;	// atan(-INF,-INF)
                }
            }
            else
            {
                switch( m )
                {
                case 0: return  zero;		// atan(+...,+INF)
                case 1: return -zero;		// atan(-...,+INF)
                case 2: return  pi + tiny;	// atan(+...,-INF)
                case 3: return -pi - tiny;	// atan(-...,-INF)
                }
            }
        }

        // when y is INF
        if( uword_is_infinite( iy ) )
        {
            return ( hy < 0 ) ? -pi_o_2 - tiny : pi_o_2 + tiny;
        }

        // compute y / x
        k = ( iy - ix ) >> 23;
        if( k > 60 )
        {
            z = pi_o_2 + (float)0.5 * pi_lo; 	// |y/x| >  2**60
        }
        else if( hx < 0 && k < -60 )
        {
            z = 0.0; 	// |y|/x < -2**60
        }
        else
        {
            z = atanf( fabsf( y / x ) ); // safe to do y/x
        }

        switch( m )
        {
        case 0: return z;					// atan(+,+)
        case 1:
            {
                Cmp_unsigned__int32 zh;
                get_float_word( zh, z );
                set_float_word( z, zh ^ 0x80000000 );
            }
            return z;						// atan(-,+)
        case 2: return pi - ( z - pi_lo );	// atan(+,-)
        default: // case 3
            return ( z - pi_lo ) - pi;		// atan(-,-)
        }
    }

};//namespace nsBaseCRT
