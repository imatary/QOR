/*
 * isinf(x) returns 1 if x is infinity, else 0;
 * no branching!
 *
 * isinf is a <math.h> macro in the C99 standard.  It was previously
 * implemented as a function by newlib and is declared as such in
 * <ieeefp.h>.  Newlib supplies it here as a function if the user
 * chooses to use <ieeefp.h> or needs to link older code compiled with the
 * previous <math.h> declaration.
 */

#include "SystemQOR/Posix/Basemath.h"
//TODO: #include <ieeefp.h>

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	int Cmath::isinff( float x )
	{
		Cmp_signed__int32 ix;
		get_float_word( ix, x );
		ix &= 0x7fffffff;
		return uword_is_infinite( ix );
	}

#ifdef _DOUBLE_IS_32BITS

#pragma TODO( "? undef" )
	#undef isinf

	//------------------------------------------------------------------------------
	int Cmath::isinf( double x)
	{
		return isinff( (float)x );
	}

#else

	//------------------------------------------------------------------------------
	int Cmath::isinf( double x )
	{
		Cmp_signed__int32 hx,lx;
		extract_words( hx, lx, x );
		hx &= 0x7fffffff;
		hx |= (Cmp_unsigned__int32)( lx | ( - lx ) ) >> 31;	
		hx = 0x7ff00000 - hx;
		return 1 - (int)( (Cmp_unsigned__int32)( hx | ( -hx ) ) >> 31 );
	}

#endif//_DOUBLE_IS_32BITS

};//namespace nsBaseCRT
