//yaffut_test.h

#ifndef _YAFFUT_TEST_H_
#define _YAFFUT_TEST_H_

#include "HippoQOR/yaffut_registrator.h"

//------------------------------------------------------------------------------
namespace yaffut
{
	//------------------------------------------------------------------------------
	template <typename Suite, typename Case = void>
	struct Test: public virtual Suite
	{
		static Registrator<Suite, Case> s_Registrator;

		Test(): Suite()
		{
			Registrator<Suite, Case>* forceInstance = &s_Registrator;
			forceInstance = 0;
		}
	};

	template< typename Suite, typename Case > Registrator< Suite, Case > Test< Suite, Case >::s_Registrator;

	//------------------------------------------------------------------------------
	template <typename Case>
	struct Test<Case, void>
	{
		static Registrator<Case, void> s_Registrator;

		Test()
		{
			Registrator<Case, void>* forceInstance = &s_Registrator;
			forceInstance = 0;
		}
	};

	template <typename Case> Registrator< Case, void > Test< Case, void >::s_Registrator;

}//yaffut

#endif//_YAFFUT_TEST_H_
