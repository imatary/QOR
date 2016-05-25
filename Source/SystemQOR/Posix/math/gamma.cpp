
/* @(#)er_gamma.c 5.1 93/09/24 */
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
/* __ieee754_gamma_r(x, signgamp)
 * Reentrant version of the logarithm of the Gamma function
 * with user provide pointer for the sign of Gamma(x).
 *
 * Method: See __ieee754_lgamma_r
 */

#include "SystemQOR/Posix/Basemath.h"
#include <math.h>

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
    //------------------------------------------------------------------------------
    float Cmath::gammaf_r( float x, int* signgamp )
    {
        float y;
        struct fexception exc;
        y = __ieee754_gammaf_r( x, signgamp );
        if( m_fdlib_version == _IEEE_ )
        {
            return y;
        }

        if( !finitef( y ) && finitef( x ) )
        {
            exc.name = "gammaf";
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
                // gammaf(-integer) or gamma(0)
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
                // gammaf(finite) overflow
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

    //------------------------------------------------------------------------------
    float Cmath::gammaf( float x )
    {
        float y;
        struct fexception exc;
        y = __ieee754_gammaf_r( x, &m_isigngam );
        if( m_fdlib_version == _IEEE_ )
        {
            return y;
        }

        if( !finitef( y ) && finitef( x ) )
        {
            if( floorf( x ) == x && x <= (float)0.0 )
            {
                // gammaf(-integer) or gammaf(0)
                exc.type = EX_SING;
                exc.name = "gammaf";
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
                    errno = EDOM;
                }
                else if( !matherr( &exc ) )
                {
                    errno = EDOM;
                }
            }
            else
            {
                // gammaf(finite) overflow
                exc.type = EX_OVERFLOW;
                exc.name = "gammaf";
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
    double Cmath::gamma( double x )
    {
        return (double)gammaf( (float)x );
    }

#else

    //------------------------------------------------------------------------------
    double Cmath::gamma_r( double x, int* signgamp )
    {
        double y;
        struct fexception exc;
        y = __ieee754_gamma_r( x, signgamp );
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
            exc.name = "gamma";
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
                // gamma(-integer) or gamma(0)
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
                // gamma(finite) overflow
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
    double Cmath::gamma( double x )
    {
        double y;
        struct fexception exc;
        y = __ieee754_gamma_r( x, &m_isigngam );
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
            exc.name = "gamma";
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

            if( floor( x ) == x && x <= 0.0 )
            {
                // gamma(-integer) or gamma(0)
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
                // gamma(finite) overflow
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

#endif //defined(_DOUBLE_IS_32BITS)

    //------------------------------------------------------------------------------
    double Cmath::__ieee754_gamma_r( double x, int* signgamp )
    {
        return __ieee754_exp( __ieee754_lgamma_r( x, signgamp ) );
    }

    //------------------------------------------------------------------------------
    float Cmath::__ieee754_gammaf_r( float x, int* signgamp )
    {
        return __ieee754_expf( __ieee754_lgammaf_r( x, signgamp ) );
    }

};//namespace nsBaseCRT
