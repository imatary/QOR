//base_mock

#include "SystemQOR.h"

#ifndef _UNITTEST_BASE_MOCK_H_
#define _UNITTEST_BASE_MOCK_H_

//------------------------------------------------------------------------------
namespace nsUnitTesting
{
	//------------------------------------------------------------------------------
	// base type
	class __QOR_INTERFACE( __HIPPO ) base_mock 
	{

	public:

		void destroy();
		virtual ~base_mock();
		void *rewriteVft(void *newVf);
		void unwriteVft();
	};

}//nsUnitTesting

#endif//_UNITTEST_BASE_MOCK_H_
