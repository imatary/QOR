//LinQL.cpp

#include "LinQL/LinQL.h"
#include "CodeQOR/ClassReg/ClassReg.h"

#ifndef QOR_MONOLITHIC

__QCMP_STARTLINKAGE_C

	__QCMP_EXPORT nsCodeQOR::mxGUID QORidentity( void )
	{
		static nsCodeQOR::mxGUID LinQL = { 0xb3360f07, 0xd07d, 0x4440, { 0xb3, 0xd7, 0xbd, 0x01, 0xc0, 0xc7, 0x7c, 0xef } };
		return LinQL;
	}

__QCMP_ENDLINKAGE_C

#endif
