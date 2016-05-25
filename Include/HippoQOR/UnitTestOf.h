//UnitTestOf.h

#ifndef _UNITTEST_OF_H_
#define _UNITTEST_OF_H_

#include "CodeQOR/Instancing/sTOB.h"
#include "HippoQOR/NoTest.h"

#define __QOR_DECLARE_UNIT_TEST( _TESTED_CLASS, _TEST_CLASS )					\
	template<> struct nsUnitTesting::unit_test_of< _TESTED_CLASS >				\
	{																			\
		typedef _TEST_CLASS type;												\
		static nsCodeQOR::sTOB< type > instance;								\
	};																			\
	template<> class nsCodeQOR::sTOB< _TEST_CLASS >

#define __QOR_IMPLEMENT_UNIT_TEST( _TESTED_CLASS, _TEST_CLASS )					\
	nsCodeQOR::sTOB< _TEST_CLASS > nsUnitTesting::unit_test_of< _TESTED_CLASS >::instance

//------------------------------------------------------------------------------
namespace nsUnitTesting
{
	//------------------------------------------------------------------------------
	template< class T >
	struct unit_test_of
	{
		typedef CNoTest type;

		static nsCodeQOR::sTOB< type > instance;
	};

	template<> class nsCodeQOR::sTOB< CNoTest >;

}//nsUnitTesting

#endif//_UNITTEST_OF_H_
