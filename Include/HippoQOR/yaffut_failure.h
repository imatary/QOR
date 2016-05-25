//yaffut_failure.h

#ifndef _YAFFUT_FAILURE_H_
#define _YAFFUT_FAILURE_H_

#include <exception>
#include <string>
#include <sstream>

#include "HippoQOR/yaffut.h"

//------------------------------------------------------------------------------
namespace yaffut 
{
	//------------------------------------------------------------------------------
	class failure: public std::exception
	{
		std::string failure_;

	public:
	
		//------------------------------------------------------------------------------
		template <typename Expected, typename Actual>
		failure(const Expected& e, Actual& a, const char* at = "", const char* expr = "")
		{
			std::ostringstream os;
			os << at << expr << "\nexpected: "
			<< "(" << demangle<Expected>() << ") " << e
			<< " != actual: " << "(" << demangle<Actual>() << ") " << a;
			failure_ = os.str();
		}

		failure(const char* at = "", const char* expr = "");
		virtual ~failure() throw();
		virtual const char* what() const throw();
	};

}//yaffut

#endif//_YAFFUT_FAILURE_H_
