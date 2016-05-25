// UnitTestBase.h

#ifndef _UNITTEST_UNITTESTBASE_H_
#define _UNITTEST_UNITTESTBASE_H_

#ifdef	__CQOR_OPTIMIZEINCLUDE
#pragma __CQOR_OPTIMIZEINCLUDE
#endif//__CQOR_OPTIMIZEINCLUDE

#include "CodeQOR/DataStructures/TFLink.h"

//--------------------------------------------------------------------------------
namespace nsUnitTesting
{

	class __QOR_INTERFACE( __HIPPO ) CUnitTestCollection;
	typedef __QOR_INTERFACE( __HIPPO ) nsCodeQOR::CTFLink< CUnitTestCollection* > CUnitTestRecursiveList;

	__QOR_INTERFACE( __HIPPO ) CUnitTestCollection* UnitTests( CUnitTestCollection* pUnitTestCollection );

	//--------------------------------------------------------------------------------
	//Recursive collection of Unit tests
	//Derive each unit test and test collection from this class
	//Override Test to halt recursion at each test node
	class __QOR_INTERFACE( __HIPPO ) CUnitTestCollection : public CUnitTestRecursiveList
	{
	public:

		CUnitTestCollection();
		virtual bool Test();

	};

}//nsUnitTesting

#endif//_UNITTEST_UNITTESTBASE_H_
