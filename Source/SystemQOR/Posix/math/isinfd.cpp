/*
 * __isinfd(x) returns 1 if x is infinity, else 0;
 * no branching!
 * Added by Cygnus Support.
 */

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{

#ifndef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	int Cmath::__isinfd( double x )
	{
		Cmp_signed__int32 hx,lx;
		extract_words( hx, lx, x );
		hx &= 0x7fffffff;
		hx |= (Cmp_unsigned__int32)( lx | ( -lx ) ) >> 31;	
		hx = 0x7ff00000 - hx;
		return 1 - (int)( (Cmp_unsigned__int32)( hx | ( -hx ) ) >> 31 );
	}

#endif /* _DOUBLE_IS_32BITS */

};//namespace nsBaseCRT
