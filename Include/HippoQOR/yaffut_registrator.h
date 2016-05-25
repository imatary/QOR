//yaffut_regsitrator.h

#ifndef _YAFFUT_REGISTRATOR_H_
#define _YAFFUT_REGISTRATOR_H_

#include <string>

//------------------------------------------------------------------------------
namespace yaffut
{
	//------------------------------------------------------------------------------
	template <typename Suite, typename Case>
	struct Registrator
	{
		//------------------------------------------------------------------------------
		Registrator()
		{
			Factory::Instance().Register(TestName(), Create);
		}
	
		//------------------------------------------------------------------------------
		const std::string& TestName()
		{
			static const std::string name(demangle<Suite>() + "::" + demangle<Case>());
			return name;
		}

		//------------------------------------------------------------------------------
		static void Create()
		{
			Case();
		}
	};

	//------------------------------------------------------------------------------
	template <typename Case>
	struct Registrator<Case, void>
	{
		//------------------------------------------------------------------------------
		Registrator()
		{
			Factory::Instance().Register(TestName(), Create);
		}

		//------------------------------------------------------------------------------
		const std::string& TestName()
		{
			static const std::string name ("::" + demangle<Case>());
			return name;
		}

		//------------------------------------------------------------------------------
		static void Create()
		{
			Case();
		}
	};

}//yaffut

#endif//_YAFFUT_REGISTRATOR_H_
