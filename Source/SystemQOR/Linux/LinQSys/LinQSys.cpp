//LinQSys.cpp

#include "LinQSys/LinQSys.h"

#ifndef QOR_MONOLITHIC

__QCMP_STARTLINKAGE_C

	//------------------------------------------------------------------------------
	__QCMP_EXPORT nsCodeQOR::mxGUID QORidentity( void )
	{
		static nsCodeQOR::mxGUID LinQSys = { 0x111bc0c9, 0xb4cf, 0x4b8d, { 0x91, 0xec, 0xd0, 0x63, 0xd4, 0xce, 0x7, 0x7a } };
		return LinQSys;
	}

__QCMP_ENDLINKAGE_C

#endif//
