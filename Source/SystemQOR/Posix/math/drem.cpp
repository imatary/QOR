/*
 * drem f() wrappers for remainder f().
 * 
 * Written by J.T. Conklin, <jtc@wimsey.com>
 * Placed into the Public Domain, 1994.
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	double Cmath::drem( double x, double y )
	{
		return remainder(x, y);
	}

	//------------------------------------------------------------------------------
	float Cmath::dremf( float x, float y )
	{
		return remainderf(x, y);
	}

};//namespace nsBaseCRT
