
/* @(#)e_scalb.c 5.1 93/09/24 */
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

/*
 * __ieee754_scalb(x, fn) is provide for
 * passing various standard test suite. One
 * should use scalbn() instead.
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
    //------------------------------------------------------------------------------
    float Cmath::scalbf( float x, float fn )
    {
        float z;
        struct fexception exc;
        z = __ieee754_scalbf( x, fn );
        if( m_fdlib_version == _IEEE_ )
        {
            return z;
        }
        if( !( finitef( z ) || isnanf( z ) ) && finitef( x ) )
        {
            // scalbf overflow; SVID also returns +-HUGE_VAL
            exc.type = EX_OVERFLOW;
            exc.name = "scalbf";
            exc.err = 0;
            exc.arg1 = (double)x;
            exc.arg2 = (double)fn;
			exc.retval = x > 0.0 ? nsPlatform::HugeValueF : -nsPlatform::HugeValueF;
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

        if( z == (float)0.0 && z != x )
        {
            // scalbf underflow
            exc.type = EX_UNDERFLOW;
            exc.name = "scalbf";
            exc.err = 0;
            exc.arg1 = (double)x;
            exc.arg2 = (double)fn;
            exc.retval = copysign( 0.0, x );
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

        if( !finitef( fn ) )
        {
            errno = ERANGE;
        }

        return z;
    }

#ifdef _DOUBLE_IS_32BITS

    //------------------------------------------------------------------------------
    double Cmath::scalb( double x, double fn )
    {
        return (double)scalbf( (float)x, (float)fn );
    }

#else

    //------------------------------------------------------------------------------
    double Cmath::scalb( double x, double fn )
    {
        double z;
#	ifndef HUGE_VAL
#		define HUGE_VAL inf
        double inf = 0.0;
        set_high_word( inf, 0x7ff00000 ); // set inf to infinite
#	endif

        struct fexception exc;
        z = __ieee754_scalb( x, fn );
        if( m_fdlib_version == _IEEE_ )
        {
            return z;
        }

        if( !( finite( z ) || isnan( z ) ) && finite( x ) )
        {
            // scalb overflow; SVID also returns +-HUGE_VAL
            exc.type = EX_OVERFLOW;
            exc.name = "scalb";
            exc.err = 0;
            exc.arg1 = x;
            exc.arg2 = fn;
            exc.retval = x > 0.0 ? HUGE_VAL : -HUGE_VAL;
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

        if( z == 0.0 && z != x )
        {
            // scalb underflow
            exc.type = EX_UNDERFLOW;
            exc.name = "scalb";
            exc.err = 0;
            exc.arg1 = x;
            exc.arg2 = fn;
            exc.retval = copysign( 0.0, x );
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

        if( !finite( fn ) )
        {
            errno = ERANGE;
        }

        return z;
    }

    //------------------------------------------------------------------------------
    double Cmath::__ieee754_scalb( double x, double fn )
    {
        if( isnan( x ) || isnan( fn ) )
        {
            return x * fn;
        }

        if( !finite( fn ) )
        {
            if( fn > 0.0 )
            {
                return x * fn;
            }
            else
            {
                return x / ( -fn );
            }
        }

        if( rint( fn ) != fn )
        {
            return ( fn - fn ) / ( fn - fn );
        }
        if( fn > 65000.0 )
        {
            return scalbn( x, 65000 );
        }
        if( -fn > 65000.0 )
        {
            return scalbn( x, -65000 );
        }
        return scalbn( x, (int)fn );
    }

#endif//defined(_DOUBLE_IS_32BITS)

    //------------------------------------------------------------------------------
    float Cmath::__ieee754_scalbf( float x, float fn )
    {
        if( isnanf( x ) || isnanf( fn ) )
        {
            return x * fn;
        }

        if( !finitef( fn ) )
        {
            if( fn > (float)0.0 )
            {
                return x * fn;
            }
            else
            {
                return x / ( -fn );
            }
        }

        if( rintf( fn ) != fn )
        {
            return ( fn - fn ) / ( fn - fn );
        }

		if( INT_MAX > 65000 )
		{
			if( fn > (float)65000.0 )
			{
				return scalbnf( x, 65000 );
			}
			if( -fn > (float)65000.0 )
			{
				return scalbnf( x,-65000 );
			}
		}
		else
		{
			
			if( fn > (float)32000.0 )
			{
				return scalbnf( x, 32000 );
			}
			if( -fn > (float)32000.0 )
			{
				return scalbnf( x,-32000 );
			}
		}
        return scalbnf( x,(int)fn );
    }

};//namespace nsBaseCRT
