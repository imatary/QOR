//comparer.cpp

#include "HippoQOR/comparer.h"

//--------------------------------------------------------------------------------
namespace nsUnitTesting
{
	//--------------------------------------------------------------------------------
	inline bool operator==(NotComparable, NotComparable)
	{
		return false;
	}

}//nsUnitTesting
