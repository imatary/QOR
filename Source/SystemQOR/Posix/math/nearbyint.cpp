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

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::nearbyintf( float x )
	{
		return rintf( x );
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	double Cmath::nearbyint( double x )
	{
		return (double) nearbyintf((float) x);
	}

#else

	//------------------------------------------------------------------------------
	double Cmath::nearbyint( double x )
	{
		return rint( x );
	}

#endif /* _DOUBLE_IS_32BITS */

};//namespace nsBaseCRT
