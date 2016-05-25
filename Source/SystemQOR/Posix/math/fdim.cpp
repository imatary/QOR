/* Copyright (C) 2002 by  Red Hat, Incorporated. All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software
 * is freely granted, provided that this notice is preserved.
 */

#include "SystemQOR/Posix/Basemath.h"
#include <math.h>

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::fdimf( float x, float y )
	{
		int c = __fpclassifyf( x );
		if( c == FP_NAN || c == FP_INFINITE )
		{
			return HUGE_VAL;
		}

		return x > y ? x - y : 0.0;
	}

#ifdef _DOUBLE_IS_32BITS
	//------------------------------------------------------------------------------
	double Cmath::fdim( double x, double y )
	{
	  return (double)fdimf( (float)x, (float)y );
	}

#else

	//------------------------------------------------------------------------------
	double Cmath::fdim( double x, double y )
	{
		int c = __fpclassifyd( x );
		if( c == FP_NAN || c == FP_INFINITE )
		{
			return HUGE_VAL;
		}
		return x > y ? x - y : 0.0;
	}

#endif /* _DOUBLE_IS_32BITS */

};//namespace nsBaseCRT
