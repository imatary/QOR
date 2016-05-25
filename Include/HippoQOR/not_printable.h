//not_printable.h

#ifndef _UNITTESTING_NOT_PRINTABLE_H_
#define _UNITTESTING_NOT_PRINTABLE_H_

#include "SystemQOR.h"
#include <ostream>

//------------------------------------------------------------------------------
namespace nsUnitTesting
{
	//------------------------------------------------------------------------------
	struct NotPrintable 
	{ 
		template <typename T> NotPrintable(T const&) 
		{
		} 
	};

	inline std::ostream &operator<<(std::ostream &os, NotPrintable const&);

}//nsUnitTesting

#endif//_UNITTESTING_NOT_PRINTABLE_H_
