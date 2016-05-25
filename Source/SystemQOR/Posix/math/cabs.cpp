/*
 * cabs f() wrappers for hypot f().
 * 
 * Written by J.T. Conklin, <jtc@wimsey.com>
 * Placed into the Public Domain, 1994.
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{

	//------------------------------------------------------------------------------
	double Cmath::cabs( dcomplex z )
	{
		return hypot( z.x, z.y );
	}

	//------------------------------------------------------------------------------
	float Cmath::cabsf( fcomplex z )
	{
		return hypotf(z.x, z.y);
	}

};//namespace nsBaseCRT
