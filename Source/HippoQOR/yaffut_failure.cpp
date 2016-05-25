//yaffut_failure.cpp

#include "HippoQOR/yaffut_failure.h"

//------------------------------------------------------------------------------
namespace yaffut 
{
	//------------------------------------------------------------------------------
	failure::failure(const char* at, const char* expr )
	{
		std::ostringstream os;
		os << at << expr;
		failure_ = os.str();
	}

	//------------------------------------------------------------------------------
	failure::~failure() throw() 
	{
	}

	//------------------------------------------------------------------------------
	const char* failure::what() const throw() 
	{ 
		return failure_.c_str(); 
	}

}//yaffut