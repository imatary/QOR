//yaffut_utility.h

#ifndef _YAFFUT_UTILITY_H_
#define _YAFFUT_UTILITY_H_

#include <string>
#include "yaffut_failure.h"

//------------------------------------------------------------------------------
namespace yaffut
{
	//------------------------------------------------------------------------------
	template <typename Expected, typename Actual>
	inline void equal(const Expected& e, const Actual& a, const char* at = "", const char* expr = "")
	{
		if(e != a)
		{
			throw failure(e, a, at, expr);
		}
	}


	__QOR_INTERFACE( __HIPPO ) inline void equal(const char* e, const char* a, const char* at = "", const char* expr = "");
	__QOR_INTERFACE( __HIPPO ) inline void equal(double e, double a, const char* at = "", const char* expr = "");
	__QOR_INTERFACE( __HIPPO ) inline void check(bool b, const char* at = "", const char* expr = "");

	//------------------------------------------------------------------------------
	template< typename Expected, typename Actual >
	inline void unequal( const Expected& e, const Actual& a, const char* at = "", const char* expr = "" )
	{
		if(e == a)
		{
			throw failure(e, a, at, expr);
		}
	}

	__QOR_INTERFACE( __HIPPO ) inline void unequal(const char* e, const char* a, const char* at = "", const char* expr = "");
	__QOR_INTERFACE( __HIPPO ) inline void unequal(double e, double a, const char* at = "", const char* expr = "");

	//------------------------------------------------------------------------------
	template <typename T>
	void fail(const T& expr, const char* at = "")
	{
		std::ostringstream os;
		os << expr;
		throw failure(at, os.str().c_str());
	}

	//------------------------------------------------------------------------------
	template <typename E, typename T>
	void assert_throw(const T& functor, const char* at = "")
	{
		try
		{
			functor();
			throw failure (at, " statement failed to throw");
		}
		catch(const E&){}
	}

	//------------------------------------------------------------------------------
	template <typename E>
	void assert_throw(void(*pf)(), const char* at = "")
	{
		try
		{
			(*pf)();
			throw failure (at, " statement failed to throw");
		}
		catch(const E&){}
	}

	//------------------------------------------------------------------------------
	template <typename E, typename T>
	void assert_throw(T* pt, void(T::*mf)(), const char* at = "")
	{
		try
		{
			(pt->*mf)();
			throw yaffut::failure (at, "statement failed to throw");
		}
		catch(const E&){}
	}

}//yaffut

#endif//_YAFFUT_UTILITY_H_
