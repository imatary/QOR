/* Infinity as a constant value.   This is used for HUGE_VAL.
 * Added by Cygnus Support.
 */

#include <float.h>
#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	// Float version of infinity.
	const union Cmath::__fmath __infinityf[ 1 ] =
	{
		{
			{ 0x7f800000 }
		}
	};

	// Double version of infinity.
#ifndef _DOUBLE_IS_32BITS
#	ifdef _QARCH_BIG_ENDIAN
		const union Cmath::__dmath __infinity[ 1 ] =
		{
			{
				{ 0x7ff00000, 0 }
			}
		};
#	else
		const union Cmath::__dmath __infinity[ 1 ] =
		{
			{
				{ 0, 0x7ff00000 }
			}
		};
#	endif
#else///defined (_DOUBLE_IS_32BITS)
		const union Cmath::__dmath __infinity[ 1 ] =
		{
			{
				{ 0x7f800000, 0 }
			}
		};
#endif//defined (_DOUBLE_IS_32BITS)

	// Long double version of infinity.
#ifdef _QARCH_BIG_ENDIAN
		const union Cmath::__ldmath __infinityld[ 1 ] =
		{
            {
                { LDBL_MANT_DIG == 24 ? 0x7f800000 :( LDBL_MANT_DIG == 53 ? 0x7ff00000 : 0x7fff0000 ), 0, 0, 0 }
			}
		};
#else//_QARCH_LITTLE_ENDIAN
		const union Cmath::__ldmath __infinityld[ 1 ] =
		{
			{
				{ LDBL_MANT_DIG == 24 ? 0x7f800000 : ( LDBL_MANT_DIG == 53 ? 0x7ff00000 : 0 ),
				  LDBL_MANT_DIG == 24 ? 0 : ( LDBL_MANT_DIG == 53 ? 0 : 0x80000000 ),
				  LDBL_MANT_DIG == 24 ? 0 : ( LDBL_MANT_DIG == 53 ? 0 : 0x00007fff ),
				  0 }
			}
		};

#endif//_QARCH_LITTLE_ENDIAN


};//namespace nsBaseCRT
