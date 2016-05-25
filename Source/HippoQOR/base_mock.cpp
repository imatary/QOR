//base_mock.cpp

#include "HippoQOR/base_mock.h"

//------------------------------------------------------------------------------
namespace nsUnitTesting
{
	//------------------------------------------------------------------------------
	void base_mock::destroy() 
	{ 
		unwriteVft(); 
		delete this; 
	}

	//------------------------------------------------------------------------------
	base_mock::~base_mock() 
	{
	}

	//------------------------------------------------------------------------------
	void* base_mock::rewriteVft(void* newVf) 
	{
		void *oldVf = *(void **)this;
		*(void **)this = newVf;
		return oldVf;
	}
	
	//------------------------------------------------------------------------------
	void base_mock::unwriteVft() 
	{
		*(void **)this = (*(void ***)this)[-1];
	}

}//nsUnitTesting
