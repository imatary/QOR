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
	float Cmath::fminf( float x, float y )
	{
		if( __fpclassifyf( x ) == FP_NAN )
		{
			return y;
		}

		if( __fpclassifyf( y ) == FP_NAN )
		{
			return x;
		}

		return x < y ? x : y;
	}


#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	double Cmath::fmin( double x, double y )
	{
		return (double)fminf( (float)x, (float)y );
	}

#else

	//------------------------------------------------------------------------------
	double Cmath::fmin( double x, double y )
	{
		if( __fpclassifyd( x ) == FP_NAN )
		{
			return y;
		}

		if( __fpclassifyd( y ) == FP_NAN )
		{
			return x;
		}

		return x < y ? x : y;
	}

#endif//_DOUBLE_IS_32BITS

};//namespace nsBaseCRT
