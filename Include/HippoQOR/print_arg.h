//print_arg.h

#ifndef _UNITTEST_PRINT_ARG_H_
#define _UNITTEST_PRINT_ARG_H_

#include "SystemQOR.h"
#include "HippoQOR/null_type.h"
#include <ostream>

//------------------------------------------------------------------------------
namespace nsUnitTesting
{
	//------------------------------------------------------------------------------
	template <typename T>
	struct printArg 
	{
		static inline void print(std::ostream &os, T arg, bool withComma)
		{
			if (withComma) os << ",";
			os << arg;
		}
	};

	//------------------------------------------------------------------------------
	template <>
	struct printArg<NullType>
	{
		static void print(std::ostream &, NullType , bool)
		{
		}
	};

}//nsUnitTesting

#endif//_UNITTEST_PRINT_ARG_H_
