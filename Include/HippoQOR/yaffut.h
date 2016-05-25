// Copyright 2006 Rutger E.W. van Beusekom.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __YAFFUT_H__
#define __YAFFUT_H__

#ifdef __GNUC__
#include <cxxabi.h>
#elif _MSC_VER
#pragma warning (disable: 4786)
#endif

#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <stdexcept>
#if defined(__GNUC__) && !defined(_WIN32)
#include <unistd.h>
#endif

#include "HippoQOR/yaffut_factory.h"

//------------------------------------------------------------------------------
namespace yaffut 
{

	std::string const version = "1.0";
    
	template <typename T>
	std::string demangle()
	{
#ifdef __GNUC__
		size_t sz;
		int status;
		char* ptr = abi::__cxa_demangle(typeid(T).name(), 0, &sz, &status);
		std::string name(ptr ? ptr : "", ptr ? strlen(ptr) : 0);
		if(ptr){ free(ptr); }
		std::string::size_type pos = name.rfind("::");
		if(pos != std::string::npos)
		{
		name = name.substr(pos + 2);
		}  
#elif _MSC_VER
		const  type_info& ti( typeid( T ) );
		std::string name(ti.name());
		static const std::string struct_prefix("struct ");
		static const std::string class_prefix("class ");
		static const std::string ptr_postfix(" *");

		std::string::size_type
		at = name.find(struct_prefix);
		if(at != std::string::npos) { name.erase(at, struct_prefix.size()); }
		at = name.find(class_prefix);
		if(at != std::string::npos) { name.erase(at, class_prefix.size()); }
		at = name.find(ptr_postfix);
		if(at != std::string::npos) { name.erase(at, ptr_postfix.size()); }
#else
		std::string name(typeid(T).name());
#endif
		return name;
	}



}

//and for those who prefer macro obscurity over typing
#define TEST(Suite, Case)\
  namespace { struct Case: public yaffut::Test<Suite, Case>{ Case(); }; } \
  Case::Case()

#define FUNC(Case)\
  namespace { struct Case: public yaffut::Test<Case>{ Case(); }; } \
  Case::Case()

#define YAFFUT_STRINGIZE(x) YAFFUT_STRINGIZE_(x)
#define YAFFUT_STRINGIZE_(x) #x

#ifdef __GNUC__
#define __YAFFUT_AT__ __FILE__ ":" YAFFUT_STRINGIZE(__LINE__)": "
#elif _MSC_VER
#define __YAFFUT_AT__ __FILE__ "(" YAFFUT_STRINGIZE(__LINE__)") : "
#endif
#ifndef __AT__
#define __AT__ __YAFFUT_AT__
#endif

#define YAFFUT_EQUAL(e,a) \
  yaffut::equal (e ,a , __YAFFUT_AT__, "EQUAL(" #e " == " #a ") failed ")
#ifndef EQUAL
#define EQUAL YAFFUT_EQUAL
#endif

#define YAFFUT_UNEQUAL(e,a) \
  yaffut::unequal (e, a, __YAFFUT_AT__, "UNEQUAL(" #e " != " #a ") failed ")
#ifndef UNEQUAL
#define UNEQUAL YAFFUT_UNEQUAL
#endif

#define YAFFUT_CHECK(e) \
  yaffut::check (e, __YAFFUT_AT__, "CHECK(" #e ") failed ")
#ifndef CHECK
#define CHECK YAFFUT_CHECK
#endif

#define YAFFUT_FAIL(s) yaffut::fail (s, __YAFFUT_AT__);
#ifndef FAIL
#define FAIL YAFFUT_FAIL
#endif

#define YAFFUT_ASSERT_THROW(s, e) \
  try \
  { \
    s; \
    throw yaffut::failure (__YAFFUT_AT__,  #s " failed to throw"); \
  } \
  catch(const e&){}
#ifndef ASSERT_THROW
#define ASSERT_THROW YAFFUT_ASSERT_THROW
#endif

#ifdef YAFFUT_MAIN
#include <iostream>
int main(int argc, const char* argv[])
{
  return yaffut::Factory::Instance().Main (argc, argv);
}
#endif /* YAFFUT_MAIN */

#endif
