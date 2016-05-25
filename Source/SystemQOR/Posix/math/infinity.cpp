/*
 * infinity () returns the representation of infinity.
 * Added by Cygnus Support.
 */

/*
FUNCTION
	<<infinity>>, <<infinityf>>---representation of infinity

INDEX
	infinity
INDEX
	infinityf

ANSI_SYNOPSIS
	#include <math.h>
	double infinity(void);
	float infinityf(void);

TRAD_SYNOPSIS
	#include <math.h>
	double infinity();
	float infinityf();


DESCRIPTION
	<<infinity>> and <<infinityf>> return the special number IEEE
	infinity in double- and single-precision arithmetic
	respectively.

QUICKREF
	infinity - pure

*/

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::infinityf()
	{
		float x;
		set_float_word( x, 0x7f800000 );
		return x;
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	double Cmath::infinity()
	{
		return (double)infinityf();
	}

#else

	//------------------------------------------------------------------------------
	double Cmath::infinity()
	{
		double x;
		insert_words( x, 0x7ff00000, 0 );
		return x;
	}

#endif /* _DOUBLE_IS_32BITS */

};//namespace nsBaseCRT
