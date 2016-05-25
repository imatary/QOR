//Validation.cpp

//Validate Unit Test capability

#include "HippoQOR/yaffut.h"
#include "HippoQOR/yaffut_test.h"
#include "HippoQOR/yaffut_utility.h"
#include "HippoQOR/Call.h"
#include "HippoQOR/MockRepository.h"
#include "CodeQOR/ClassReg/ClassRegEntry.h"

//------------------------------------------------------------------------------
class IL 
{ 
public:
	void f() {}
	virtual void g() {}
};

//------------------------------------------------------------------------------
class IA 
{ 
public:
	virtual ~IA() {}
	virtual void f() {}
	virtual void g() = 0;
};

//------------------------------------------------------------------------------
namespace 
{
	struct __QOR_INTERFACE( __HIPPO ) testVirtualIsVirtual: public yaffut::Test< testVirtualIsVirtual >
	{
		__QOR_DECLARE_OCLASS_ID( testVirtualIsVirtual );

		testVirtualIsVirtual();
	};

	__QOR_IMPLEMENT_OCLASS_LUID( testVirtualIsVirtual );

	struct __QOR_INTERFACE( __HIPPO ) checkBaseCase: public yaffut::Test< checkBaseCase >
	{
		__QOR_DECLARE_OCLASS_ID( checkBaseCase );

		checkBaseCase();
	};

	__QOR_IMPLEMENT_OCLASS_LUID( checkBaseCase );
}

//template<> yaffut::Registrator< testVirtualIsVirtual, void > yaffut::Test< testVirtualIsVirtual >::s_Registrator;

//FUNC(testVirtualIsVirtual) 
testVirtualIsVirtual::testVirtualIsVirtual()
{
	//yaffut::check (e, __YAFFUT_AT__, "CHECK(" #e ") failed ")
	yaffut::check( nsCompiler::CCompiler::is_virtual( &IL::g ), __YAFFUT_AT__, "CHECK( nsCompiler::CCompiler::is_virtual(&IL::g) ) failed" );
	//YAFFUT_CHECK(is_virtual(&IL::g));

	yaffut::check( !nsCompiler::CCompiler::is_virtual( &IL::f ), __YAFFUT_AT__, "CHECK( !nsCompiler::CCompiler::is_virtual(&IL::f) ) failed" );
	//YAFFUT_CHECK(!is_virtual(&IL::f));
}

checkBaseCase::checkBaseCase()
{
	nsUnitTesting::MockRepository mocks;
	IA *iamock = mocks.InterfaceMock<IA>();
	mocks.ExpectCall(iamock, IA::f);
	mocks.ExpectCall(iamock, IA::g);
	iamock->f();
	iamock->g();
}
