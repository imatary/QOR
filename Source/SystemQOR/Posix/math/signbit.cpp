/* Copyright (C) 2002 by  Red Hat, Incorporated. All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software
 * is freely granted, provided that this notice is preserved.
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	int Cmath::__signbitf( float x )
	{
		unsigned int w;
		get_float_word( w, x );
		return ( w & 0x80000000 );
	}

	//------------------------------------------------------------------------------
	int Cmath::__signbitd( double x )
	{
		unsigned int msw;
		get_high_word( msw, x );
		return ( msw & 0x80000000 );
	}

};//namespace nsBaseCRT
