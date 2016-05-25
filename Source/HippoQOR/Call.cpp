//Call.cpp

#include "HippoQOR/Call.h"

//--------------------------------------------------------------------------------
namespace nsUnitTesting
{
	//--------------------------------------------------------------------------------
	ReturnValueHolder::~ReturnValueHolder() 
	{
	}

	//--------------------------------------------------------------------------------
	Call::Call(RegistrationType expectation, base_mock *mock, int funcIndex, int X, const char *funcName, const char *fileName) 
		: retVal(0), 
		eHolder(0), 
		mock(mock), 
		functor(0),
		funcIndex(funcIndex), 
		expectation(expectation),
		satisfied(false),
		lineno(X),
		funcName(funcName),
		fileName(fileName)
	{
	}

	//--------------------------------------------------------------------------------
	Call::~Call() 
	{
		delete eHolder;
		delete functor;
		delete retVal;
	}


}//nsUnitTesting
