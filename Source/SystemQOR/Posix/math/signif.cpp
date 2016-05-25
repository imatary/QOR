
/* @(#)s_signif.c 5.1 93/09/24 */
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
 * significand(x) computes just
 * 	scalb(x, (double) -ilogb(x)),
 * for exercising the fraction-part(F) IEEE 754-1985 test vector.
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::significandf( float x )
	{
		return __ieee754_scalbf( x, (float) -ilogbf( x ) );
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	double Cmath::significand( double x )
	{
		return (double)significandf( (float)x );
	}

#else

	//------------------------------------------------------------------------------
	double Cmath::significand( double x )
	{
		return __ieee754_scalb( x, (double) -ilogb( x ) );
	}

#endif//_DOUBLE_IS_32BITS

};//namespace nsBaseCRT
