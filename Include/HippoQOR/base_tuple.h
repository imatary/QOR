//base_tuple.h

#ifndef _UNITTEST_BASE_TUPLE_H_
#define _UNITTEST_BASE_TUPLE_H_

#include "SystemQOR.h"
#include <ostream>

//------------------------------------------------------------------------------
namespace nsUnitTesting
{
	//------------------------------------------------------------------------------
	class base_tuple 
	{
	protected:
	
		base_tuple();

	public: 

		virtual ~base_tuple();
		virtual bool operator==(const base_tuple &) const = 0;
		virtual void printTo(std::ostream &os) const = 0;
	};

}//nsUnitTesting

#endif//_UNITTEST_BASE_TUPLE_H_
