//yaffut_utility.cpp

#include "CompilerQOR.h"
#include "HippoQOR/yaffut_utility.h"

//------------------------------------------------------------------------------
namespace yaffut
{
	//------------------------------------------------------------------------------
	__QOR_INTERFACE( __HIPPO ) inline void equal(const char* e, const char* a, const char* at, const char* expr )
	{
		if(std::string(e) != std::string(a))
		{
			throw failure(e, a, at, expr);
		}
	}

	//------------------------------------------------------------------------------
	__QOR_INTERFACE( __HIPPO ) inline void equal(double e, double a, const char* at, const char* expr )
	{
		double max = std::abs(std::max(e, a));
		max = max < 1.0 ? 1.0 : max;
		if(std::abs(e - a) > std::numeric_limits<double>::epsilon() * max)
		{
			throw failure(e, a, at, expr);
		}
	}

	//------------------------------------------------------------------------------
	__QOR_INTERFACE( __HIPPO ) inline void check(bool b, const char* at, const char* expr )
	{ 
		if(!b)
		{
			throw failure(at, expr);
		}
	}

	//------------------------------------------------------------------------------
	__QOR_INTERFACE( __HIPPO )inline void unequal(const char* e, const char* a, const char* at, const char* expr )
	{
		if(std::string(e) == std::string(a))
		{
			throw failure(e, a, at, expr);
		}
	}

	//------------------------------------------------------------------------------
	__QOR_INTERFACE( __HIPPO )inline void unequal(double e, double a, const char* at, const char* expr )
	{
		double max = std::abs(std::max(e, a));
		max = max < 1.0 ? 1.0 : max;
		if(std::abs(e - a) <= std::numeric_limits<double>::epsilon() * max)
		{
			throw failure(e, a, at, expr);
		}
	}

}//yaffut

