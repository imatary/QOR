//null_type.h

#ifndef _UNITTEST_NULL_TYPE_H_
#define _UNITTEST_NULL_TYPE_H_

#include "SystemQOR.h"

//------------------------------------------------------------------------------
namespace nsUnitTesting
{
	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __HIPPO ) NullType 
	{

	public: 

		bool operator==(const NullType &) const;
	};

}//nsUnitTesting

#endif//_UNITTEST_NULL_TYPE_H_
