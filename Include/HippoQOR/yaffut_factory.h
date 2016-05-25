//yaffut_factory.h

#ifndef _YAFFUT_FACTORY_H_
#define _YAFFUT_FACTORY_H_

#include <string>
#include <iostream>
#include <map>

//------------------------------------------------------------------------------
namespace yaffut 
{
	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __HIPPO ) Factory
	{
	public:

		typedef void (*Create_t) ();

	private:

		typedef std::map<std::string, Create_t> Tests_t;  
		Tests_t m_Tests;  
		size_t m_fail;
		size_t m_pass;

	private:

		Factory();
		static bool EqualsSuiteName (std::string const &name, std::string const& s);

	public:

		~Factory();
		static Factory& Instance();
		void Register(const std::string& name, Create_t create);
		size_t Fail( void );
		void List(const std::string& name);
		void Run(const std::string& name);
		void Report( void );
		int Main (int argc, const char* argv[]);
	};

}//yaffut

#endif//_YAFFUT_FACTORY_H_
