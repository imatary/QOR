/* @(#)w_gamma.c 5.1 93/09/24 */
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
/* double gamma(double x)
 * Return  the logarithm of the Gamma function of x or the Gamma function of x,
 * depending on the library mode.
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::tgammaf(float x)
	{
		float y;
		int local_signgam;
		y = __ieee754_gammaf_r( x, &local_signgam );
		if( local_signgam < 0 )
		{
			y = -y;
		}

		if( m_fdlib_version == _IEEE_ )
		{
			return y;
		}

		if( !finitef( y ) && finitef( x ) ) 
		{
			if( floorf( x ) == x && x <= (float)0.0 )
			{
				// tgammaf pole
				return (float)__kernel_standard( (double)x, (double)x, 141 );
			}
			else
			{
				// tgammaf overflow
				return (float)__kernel_standard( (double)x, (double)x, 140 );
			}
		}
		return y;
	}

	//------------------------------------------------------------------------------
	double Cmath::tgamma( double x )
	{
		double y;
		int local_signgam;
		y = __ieee754_gamma_r( x, &local_signgam );
		if( local_signgam < 0 )
		{
			y = -y;
		}

		if( m_fdlib_version == _IEEE_ )
		{
			return y;
		}

		if( !finite( y ) && finite( x ) ) 
		{
			if( floor( x ) == x && x <= 0.0 )
			{
				return __kernel_standard( x, x, 41 ); // tgamma pole
			}
			else
			{
				return __kernel_standard( x, x, 40 ); // tgamma overflow
			}
		}
		return y;

	}

};//namespace nsBaseCRT
