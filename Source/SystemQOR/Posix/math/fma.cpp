#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::fmaf( float x, float y, float z )
	{
		// Let the implementation handle this.
		return ( x * y ) + z;
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	double Cmath::fma( double x, double y, double z )
	{
		return (double) fmaf( (float)x, (float)y, (float)z );
	}

#else

	//------------------------------------------------------------------------------
	double Cmath::fma( double x, double y, double z )
	{
		// Implementation defined.
		return ( x * y ) + z;
	}

#endif /* _DOUBLE_IS_32BITS */

};//namespace nsBaseCRT
