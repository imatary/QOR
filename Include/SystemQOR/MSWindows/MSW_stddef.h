//MSW_stddef.h

//MSWindows overrides for stddef

#ifndef _CQOR_MSW_STDDEF_H_
#define _CQOR_MSW_STDDEF_H_

#include "SystemQOR/Posix/Basestddef.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __QSYS ) Cstddef : public nsBaseCRT::Cstddef
	{
	public:
		
	};
};


#endif//_CQOR_MSW_STDDEF_H_

