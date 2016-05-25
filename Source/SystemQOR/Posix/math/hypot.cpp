
/* @(#)e_hypot.c 5.1 93/09/24 */
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
/* __ieee754_hypot(x,y)
 *
 * Method :
 *	If (assume round-to-nearest) z=x*x+y*y
 *	has error less than sqrt(2)/2 ulp, than
 *	sqrt(z) has error less than 1 ulp (exercise).
 *
 *	So, compute sqrt(x*x+y*y) with some care as
 *	follows to get the error below 1 ulp:
 *
 *	Assume x>y>0;
 *	(if possible, set rounding to round-to-nearest)
 *	1. if x > 2y  use
 *		x1*x1+(y*y+(x2*(x+x1))) for x*x+y*y
 *	where x1 = x with lower 32 bits cleared, x2 = x-x1; else
 *	2. if x <= 2y use
 *		t1*y1+((x-y)*(x-y)+(t1*y2+t2*y))
 *	where t1 = 2x with lower 32 bits cleared, t2 = 2x-t1,
 *	y1= y with lower 32 bits chopped, y2 = y-y1.
 *
 *	NOTE: scaling may be necessary if some argument is too
 *	      large or too tiny
 *
 * Special cases:
 *	hypot(x,y) is INF if x or y is +INF or -INF; else
 *	hypot(x,y) is NAN if x or y is NAN.
 *
 * Accuracy:
 * 	hypot(x,y) returns sqrt(x^2+y^2) with error less
 * 	than 1 ulps (units in the last place)
 */

#include "SystemQOR/Posix/Basemath.h"
#include <math.h>

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
    //------------------------------------------------------------------------------
    float Cmath::hypotf( float x, float y ) // wrapper hypotf
    {
        float z;
        struct fexception exc;
        z = __ieee754_hypotf( x, y );
        if( m_fdlib_version == _IEEE_ )
        {
            return z;
        }
        if( ( !finitef( z ) ) && finitef( x ) && finitef( y ) )
        {
            // hypotf(finite,finite) overflow
            exc.type = EX_OVERFLOW;
            exc.name = "hypotf";
            exc.err = 0;
            exc.arg1 = (double)x;
            exc.arg2 = (double)y;
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


#ifdef _DOUBLE_IS_32BITS

    //------------------------------------------------------------------------------
    double Cmath::hypot( double x, double y )
    {
        return (double)hypotf( (float)x, (float)y );
    }

#else

    //------------------------------------------------------------------------------
    double Cmath::hypot( double x, double y ) // wrapper hypot
    {
        double z;
        struct fexception exc;
        z = __ieee754_hypot( x, y );
        if( m_fdlib_version == _IEEE_ )
        {
            return z;
        }

        if( (!finite( z ) ) && finite( x ) && finite( y ) )
        {
            // hypot(finite,finite) overflow
#	ifndef HUGE_VAL
#		define HUGE_VAL inf
            double inf = 0.0;

            set_high_word( inf, 0x7ff00000 ); // set inf to infinite
#	endif
            exc.type = EX_OVERFLOW;
            exc.name = "hypot";
            exc.err = 0;
            exc.arg1 = x;
            exc.arg2 = y;
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
    double Cmath::__ieee754_hypot( double x, double y )
    {
        double a = x, b = y, t1, t2, y1, y2, w;
        Cmp_signed__int32 j, k, ha, hb;

        get_high_word( ha, x );
        ha &= 0x7fffffff;
        get_high_word( hb, y );
        hb &= 0x7fffffff;
        if( hb > ha )
        {
            a = y;
            b = x;
            j = ha;
            ha = hb;
            hb = j;
        }
        else
        {
            a = x;
            b = y;
        }
        set_high_word( a, ha ); // a <- |a|
        set_high_word( b, hb ); // b <- |b|

        if( ( ha - hb ) > 0x3c00000 )
        {
            return a + b;
        } // x/y > 2**60
        k = 0;

        if( ha > 0x5f300000 )
        {
            // a>2**500
            if( ha >= 0x7ff00000 )
            {
                // Inf or NaN
                Cmp_unsigned__int32 low;
                w = a + b; // for sNaN
                get_low_word( low, a );
                if( ( ( ha & 0xfffff ) | low ) == 0 )
                {
                    w = a;
                }
                get_low_word( low, b );
                if( ( ( hb ^ 0x7ff00000 ) | low ) == 0 )
                {
                    w = b;
                }
                return w;
            }

            // scale a and b by 2**-600
            ha -= 0x25800000; hb -= 0x25800000;	k += 600;
            set_high_word( a, ha );
            set_high_word( b, hb );
        }

        if( hb < 0x20b00000 )
        {
            // b < 2**-500
            if( hb <= 0x000fffff )
            {
                // subnormal b or 0
                Cmp_unsigned__int32 low;
                get_low_word( low, b );
                if( ( hb | low ) == 0 )
                {
                    return a;
                }
                t1 = 0;
                set_high_word( t1, 0x7fd00000 ); // t1=2^1022
                b *= t1;
                a *= t1;
                k -= 1022;
            }
            else
            {
                // scale a and b by 2^600
                ha += 0x25800000; 	// a *= 2^600
                hb += 0x25800000;	// b *= 2^600
                k -= 600;
                set_high_word( a, ha );
                set_high_word( b, hb );
            }
        }

        // medium size a and b
        w = a - b;
        if( w > b )
        {
            t1 = 0;
            set_high_word( t1, ha );
            t2 = a - t1;
            w  = __ieee754_sqrt( t1 * t1 - ( b * ( -b ) - t2 * ( a + t1 ) ) );
        }
        else
        {
            a = a + a;
            y1 = 0;
            set_high_word( y1, hb );
            y2 = b - y1;
            t1 = 0;
            set_high_word( t1, ha + 0x00100000 );
            t2 = a - t1;
            w = __ieee754_sqrt( t1 * y1 - ( w * (-w) - ( t1 * y2 + t2 * b ) ) );
        }

        if( k != 0 )
        {
            Cmp_unsigned__int32 high;
            t1 = 1.0;
            get_high_word( high, t1 );
            set_high_word( t1, high + ( k << 20 ) );
            return t1 * w;
        }
        else
        {
            return w;
        }
    }

#endif//defined(_DOUBLE_IS_32BITS)

    //------------------------------------------------------------------------------
    float Cmath::__ieee754_hypotf( float x, float y )
    {
        float a = x, b = y, t1, t2, y1, y2, w;
        Cmp_signed__int32 j, k, ha, hb;

        get_float_word( ha, x );
        ha &= 0x7fffffffL;
        get_float_word( hb, y );
        hb &= 0x7fffffffL;
        if( hb > ha )
        {
            a = y;
            b = x;
            j = ha;
            ha = hb;
            hb = j;
        }
        else
        {
            a = x;
            b = y;
        }

        set_float_word( a, ha ); // a <- |a|
        set_float_word( b, hb ); // b <- |b|
        if( ( ha - hb ) > 0xf000000L )
        {
            return a + b; // x/y > 2**30
        }

        k = 0;
        if( ha > 0x58800000L )
        {
            // a>2**50
            if( !uword_isfinite( ha ) )
            {
                // Inf or NaN
                w = a + b; // for sNaN
                if( uword_is_infinite( ha ) )
                {
                    w = a;
                }

                if( uword_is_infinite( hb ) )
                {
                    w = b;
                }
                return w;
            }
            // scale a and b by 2**-68
            ha -= 0x22000000L;
            hb -= 0x22000000L;
            k += 68;
            set_float_word( a, ha );
            set_float_word( b, hb );
        }

        if( hb < 0x26800000L )
        {
            // b < 2**-50
            if( uword_is_zero( hb ) )
            {
                return a;
            }
            else if( uword_is_subnormal( hb ) )
            {
                set_float_word( t1, 0x7e800000L ); // t1=2^126
                b *= t1;
                a *= t1;
                k -= 126;
            }
            else
            {
                // scale a and b by 2^68
                ha += 0x22000000; 	// a *= 2^68
                hb += 0x22000000;	// b *= 2^68
                k -= 68;
                set_float_word( a, ha );
                set_float_word( b, hb );
            }
        }

        // medium size a and b
        w = a - b;
        if( w > b )
        {
            set_float_word( t1, ha & 0xfffff000L );
            t2 = a - t1;
            w  = __ieee754_sqrtf( t1 * t1 - ( b * (-b) - t2 * ( a + t1 ) ) );
        }
        else
        {
            a = a + a;
            set_float_word( y1, hb & 0xfffff000L );
            y2 = b - y1;
            set_float_word( t1, ha + 0x00800000L );
            t2 = a - t1;
            w  = __ieee754_sqrtf( t1 * y1 - ( w * (-w) - ( t1 * y2 + t2 * b ) ) );
        }

        if( k != 0 )
        {
            set_float_word( t1, 0x3f800000L + ( k << 23 ) );
            return t1 * w;
        }
        else
        {
            return w;
        }
    }

};//namespace nsBaseCRT
