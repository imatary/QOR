/*
 * nan () returns a nan.
 * Added by Cygnus Support.
 */

/*
FUNCTION
	<<nan>>, <<nanf>>---representation of ``Not a Number''

INDEX
	nan
INDEX
	nanf

ANSI_SYNOPSIS
	#include <math.h>
	double nan(const char *);
	float nanf(const char *);

TRAD_SYNOPSIS
	#include <math.h>
	double nan();
	float nanf();


DESCRIPTION
	<<nan>> and <<nanf>> return an IEEE NaN (Not a Number) in
	double- and single-precision arithmetic respectively.  The
	argument is currently disregarded.

QUICKREF
	nan - pure

*/

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::nanf( const char* unused )
	{
		float x;
		set_float_word( x, 0x7fc00000 );
		return x;
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	double Cmath::nan( const char* arg )
	{
		return (double)nanf( arg );
	}

#else

	//------------------------------------------------------------------------------
	double Cmath::nan( const char* unused )
	{
		double x;

		insert_words( x, 0x7ff80000, 0 );
		return x;
	}

#endif /* _DOUBLE_IS_32BITS */

};//namespace nsBaseCRT
