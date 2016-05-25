
/* @(#)e_fmod.c 5.1 93/09/24 */
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
/*
 * __ieee754_fmod(x,y)
 * Return x mod y in exact arithmetic
 * Method: shift and subtract
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
    //------------------------------------------------------------------------------
    float Cmath::fmodf( float x, float y ) // wrapper fmodf
    {
        float z;
        struct fexception exc;
        z = __ieee754_fmodf( x, y );
        if( m_fdlib_version == _IEEE_ || isnanf( y ) || isnanf( x ) )
        {
            return z;
        }

        if( y == (float)0.0 )
        {
            // fmodf(x,0)
            exc.type = EX_DOMAIN;
            exc.name = "fmodf";
            exc.err = 0;
            exc.arg1 = (double)x;
            exc.arg2 = (double)y;
            if( m_fdlib_version == _SVID_ )
            {
                exc.retval = x;
            }
            else
            {
                exc.retval = infinity();
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
        else
        {
            return z;
        }
    }

    //------------------------------------------------------------------------------
    float Cmath::__ieee754_fmodf( float x, float y )
    {
        static const float one = 1.0;
        static const float Zero[] = { 0.0, -0.0, };

        Cmp_signed__int32 n, hx, hy, hz, ix, iy, sx, i;

        get_float_word( hx, x );
        get_float_word( hy, y );
        sx = hx & 0x80000000; // sign of x
        hx ^= sx; // |x|
        hy &= 0x7fffffff; // |y|

        // purge off exception values
        if( uword_is_zero( hy ) || !uword_isfinite( hx ) || uword_isnan( hy ) )
        {
            return ( x * y ) / ( x * y );
        }

        if( hx < hy )
        {
            return x;			// |x|<|y| return x
        }

        if( hx == hy )
        {
            return Zero[ (Cmp_unsigned__int32)sx >> 31 ]; // |x|=|y| return x*0
        }

        // Note: y cannot be zero if we reach here.

        // determine ix = ilogb(x)
        if( uword_is_subnormal( hx ) )
        {
            // subnormal x
            for( ix = -126, i = ( hx << 8 ); i > 0; i <<= 1 )
            {
                ix -= 1;
            }
        }
        else
        {
            ix = ( hx >> 23 ) - 127;
        }

        // determine iy = ilogb(y)
        if( uword_is_subnormal( hy ) )
        {
            // subnormal y
            for( iy = -126, i = ( hy << 8 ); i >= 0; i <<= 1 )
            {
                iy -= 1;
            }
        }
        else
        {
            iy = ( hy >> 23 ) - 127;
        }

        // set up {hx,lx}, {hy,ly} and align y to x
        if( ix >= -126 )
        {
            hx = 0x00800000 | ( 0x007fffff & hx );
        }
        else
        {
            // subnormal x, shift x to normal
            n = -126 - ix;
            hx = hx << n;
        }

        if( iy >= -126 )
        {
            hy = 0x00800000 | ( 0x007fffff & hy );
        }
        else
        {
            // subnormal y, shift y to normal
            n = -126 - iy;
            hy = hy << n;
        }

        // fix point fmod
        n = ix - iy;
        while( n-- )
        {
            hz = hx - hy;
            if( hz < 0 )
            {
                hx = hx + hx;
            }
            else
            {
                if( hz == 0 ) // return sign(x)*0
                {
                    return Zero[ (Cmp_unsigned__int32)sx >> 31 ];
                }
                hx = hz + hz;
            }
        }

        hz = hx - hy;
        if( hz >= 0 )
        {
            hx = hz;
        }

        // convert back to floating value and restore the sign
        if( hx == 0 ) // return sign(x)*0
        {
            return Zero[ (Cmp_unsigned__int32)sx >> 31 ];
        }

        while( hx < 0x00800000 )
        {
            // normalize x
            hx = hx + hx;
            iy -= 1;
        }

        if( iy >= -126 )
        {
            // normalize output
            hx = ( ( hx - 0x00800000 ) | ( ( iy + 127 ) << 23 ) );
            set_float_word( x, hx | sx );
        }
        else
        {
            // subnormal output
            // If denormals are not supported, this code will generate a zero representation.
            n = -126 - iy;
            hx >>= n;
            set_float_word( x, hx | sx );
            x *= one; // create necessary signal
        }
        return x; // exact output
    }

#ifdef _DOUBLE_IS_32BITS

    //------------------------------------------------------------------------------
    double Cmath::fmod( double x, double y )
    {
        return (double)fmodf( (float)x, (float)y );
    }

#else

    //------------------------------------------------------------------------------
    double Cmath::fmod( double x, double y ) // wrapper fmod
    {
        double z;
        struct fexception exc;
        z = __ieee754_fmod( x, y );
        if( m_fdlib_version == _IEEE_ || isnan( y ) || isnan( x ) )
        {
            return z;
        }
        if( y == 0.0 )
        {
            // fmod(x,0)
            exc.type = EX_DOMAIN;
            exc.name = "fmod";
            exc.arg1 = x;
            exc.arg2 = y;
            exc.err = 0;
            if( m_fdlib_version == _SVID_ )
            {
                exc.retval = x;
            }
            else
            {
                exc.retval = infinity();
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
            return exc.retval;
        }
        else
        {
            return z;
        }
    }

    //------------------------------------------------------------------------------
    double Cmath::__ieee754_fmod( double x, double y )
    {
        static const double one = 1.0;
        static const double Zero[] = { 0.0, -0.0, };

        Cmp_signed__int32 n, hx, hy, hz, ix, iy, sx, i;
        Cmp_unsigned__int32 lx, ly, lz;

        extract_words( hx, lx, x );
        extract_words( hy, ly, y );
        sx = hx & 0x80000000; // sign of x
        hx ^= sx;		// |x|
        hy &= 0x7fffffff; // |y|

        // purge off exception values
        if( ( hy | ly ) == 0 || ( hx >= 0x7ff00000 ) ||	// y=0,or x not finite
            ( ( hy | ( ( ly | -ly ) >> 31 ) ) > 0x7ff00000 ) )	// or y is NaN
        {
            return ( x * y ) / ( x * y );
        }

        if( hx <= hy )
        {
            if( ( hx < hy ) || ( lx < ly ) )
            {
                return x; // |x|<|y| return x
            }

            if( lx == ly )
            {
                return Zero[ (Cmp_unsigned__int32)sx >> 31 ]; // |x|=|y| return x*0
            }
        }

        // determine ix = ilogb(x)
        if( hx < 0x00100000 )
        {
            // subnormal x
            if( hx == 0 )
            {
                for( ix = -1043, i = lx; i > 0; i <<= 1 )
                {
                    ix -= 1;
                }
            }
            else
            {
                for( ix = -1022, i = ( hx << 11 ); i > 0; i <<= 1 )
                {
                    ix -= 1;
                }
            }
        }
        else
        {
            ix = ( hx >> 20 ) - 1023;
        }

        // determine iy = ilogb(y)
        if( hy < 0x00100000 )
        {
            // subnormal y
            if( hy == 0 )
            {
                for( iy = -1043, i = ly; i > 0; i <<= 1 )
                {
                    iy -= 1;
                }
            }
            else
            {
                for( iy = -1022, i = ( hy << 11 ); i > 0; i <<= 1 )
                {
                    iy -= 1;
                }
            }
        }
        else
        {
            iy = ( hy >> 20 ) - 1023;
        }

        // set up {hx,lx}, {hy,ly} and align y to x
        if( ix >= -1022 )
        {
            hx = 0x00100000 | ( 0x000fffff & hx );
        }
        else
        {
            // subnormal x, shift x to normal
            n = -1022 - ix;
            if( n <= 31 )
            {
                hx = ( hx << n ) | ( lx >> ( 32 - n ) );
                lx <<= n;
            }
            else
            {
                hx = lx << ( n - 32 );
                lx = 0;
            }
        }

        if( iy >= -1022 )
        {
            hy = 0x00100000 | ( 0x000fffff & hy );
        }
        else
        {
            // subnormal y, shift y to normal
            n = -1022-iy;
            if( n <= 31 )
            {
                hy = ( hy << n ) | ( ly >> ( 32 - n ) );
                ly <<= n;
            }
            else
            {
                hy = ly << ( n - 32 );
                ly = 0;
            }
        }

        // fix point fmod
        n = ix - iy;
        while( n-- )
        {
            hz = hx - hy;
            lz = lx - ly;
            if( lx < ly )
            {
                hz -= 1;
            }

            if( hz < 0 )
            {
                hx = hx + hx + ( lx >> 31 );
                lx = lx + lx;
            }
            else
            {
                if( ( hz | lz ) == 0 ) 		// return sign(x)*0
                {
                    return Zero[ (Cmp_unsigned__int32)sx >> 31 ];
                }
                hx = hz + hz + ( lz >> 31 );
                lx = lz + lz;
            }
        }

        hz = hx - hy;
        lz = lx - ly;
        if( lx < ly )
        {
            hz -= 1;
        }

        if( hz >= 0 )
        {
            hx = hz;
            lx = lz;
        }

        // convert back to floating value and restore the sign
        if( ( hx | lx ) == 0 ) // return sign(x)*0
        {
            return Zero[ (Cmp_unsigned__int32)sx >> 31 ];
        }

        while( hx < 0x00100000 )
        {
            // normalize x
            hx = hx + hx + ( lx >> 31 );
            lx = lx + lx;
            iy -= 1;
        }

        if( iy >= -1022 )
        {
            // normalize output
            hx = ( ( hx - 0x00100000 ) | ( ( iy + 1023 ) << 20 ) );
            insert_words( x, hx | sx, lx );
        }
        else
        {
            // subnormal output
            n = -1022 - iy;
            if( n <= 20 )
            {
                lx = ( lx >> n ) | ( (Cmp_unsigned__int32)hx << ( 32 - n ) );
                hx >>= n;
            }
            else if ( n <= 31 )
            {
                lx = ( hx << ( 32 - n ) ) | ( lx >> n );
                hx = sx;
            }
            else
            {
                lx = hx >> ( n - 32 );
                hx = sx;
            }
            insert_words( x, hx | sx, lx );
            x *= one; // create necessary signal
        }
        return x; // exact output
    }

#endif//defined(_DOUBLE_IS_32BITS)


};//namespace nsBaseCRT
