// sincos -- currently no more efficient than two separate calls to sin and cos.

#include "SystemQOR/Posix/Basemath.h"
#include <errno.h>

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	void Cmath::sincosf( float x, float* sinx, float* cosx )
	{
		*sinx = sinf( x );
		*cosx = cosf( x );
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	void Cmath::sincos( double x, double* sinx, double* cosx )
	{
		*sinx = sinf( (float)x );
		*cosx = cosf( (float)x );
	}

#else
	
	//------------------------------------------------------------------------------
	void Cmath::sincos( double x, double* sinx, double* cosx )
	{
		*sinx = sin( x );
		*cosx = cos( x );
	}

#endif//defined(_DOUBLE_IS_32BITS)

};//namespace nsBaseCRT
