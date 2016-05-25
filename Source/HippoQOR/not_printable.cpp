//not_printable

#include "HippoQOR/not_printable.h"

//------------------------------------------------------------------------------
namespace nsUnitTesting
{
	//------------------------------------------------------------------------------
	inline std::ostream &operator<<(std::ostream &os, NotPrintable const&)
	{
		os << "???";
		return os;
	}

}//nsUnitTesting
