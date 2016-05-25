//Baseinttypes.cpp

#include "SystemQOR/Posix/Baseinttypes.h"
#include "CodeQOR/Tracing/FunctionContextBase.h"
#include <wchar.h>
#include <stdlib.h>

//--------------------------------------------------------------------------------
namespace nsBaseCRT
{
	__QOR_IMPLEMENT_OCLASS_LUID( Cinttypes );

	//--------------------------------------------------------------------------------
	Cinttypes::Cinttypes()
	{
		__QCS_MEMBER_FCONTEXT( "Cinttypes::Cinttypes" );
	}

	//--------------------------------------------------------------------------------
	Cinttypes::~Cinttypes()
	{
		__QCS_MEMBER_FCONTEXT( "Cinttypes::~Cinttypes" );
	}

	//--------------------------------------------------------------------------------
	///The imaxabs() function shall compute the absolute value of an integer j. If the 
	///result cannot be represented, the behavior is undefined.
	intmax_t Cinttypes::imaxabs( intmax_t j )
	{
		__QCS_MEMBER_FCONTEXT( "Cinttypes::imaxabs" );
		return j < 0 ? -j : j;
	}

	//--------------------------------------------------------------------------------
	///The imaxdiv() function shall compute numer / denom and numer % denom in a single operation.
	///The imaxdiv() function shall return a structure of type imaxdiv_t, comprising 
	///both the quotient and the remainder. The structure shall contain (in either order) 
	///the members quot (the quotient) and rem (the remainder), each of which has type intmax_t.
	imaxdiv_t Cinttypes::imaxdiv( intmax_t numer, intmax_t denom )
	{
		__QCS_MEMBER_FCONTEXT( "Cinttypes::imaxdiv" );
		intmax_t intResult = numer / denom;
		intmax_t intRem = numer - ( denom * intResult );
		imaxdiv_t iResult;
		iResult.quot = intResult;
		iResult.rem = intRem;
		return iResult;
	}


	//--------------------------------------------------------------------------------
	///These functions shall be equivalent to the strtol(), strtoll(), strtoul(), and 
	///strtoull() functions, except that the initial portion of the string shall be 
	///converted to intmax_t and uintmax_t representation, respectively.
	intmax_t Cinttypes::strtoimax( const char* __QCMP_RESTRICT nptr, char** __QCMP_RESTRICT endptr, int base )
	{
		__QCS_MEMBER_FCONTEXT( "Cinttypes::strtoimax" );
		intmax_t itResult = strtol( nptr, endptr, base );
		return itResult;
	}


	//--------------------------------------------------------------------------------
	///These functions shall be equivalent to the strtol(), strtoll(), strtoul(), and 
	///strtoull() functions, except that the initial portion of the string shall be 
	///converted to intmax_t and uintmax_t representation, respectively.
	uintmax_t Cinttypes::strtoumax( const char* __QCMP_RESTRICT nptr, char** __QCMP_RESTRICT endptr, int base )
	{
		__QCS_MEMBER_FCONTEXT( "Cinttypes::strtoumax" );
		uintmax_t uitResult = strtoul( nptr, endptr, base );
		return uitResult;
	}

	//--------------------------------------------------------------------------------
	///These functions shall be equivalent to the wcstol(), wcstoll(), wcstoul(), and 
	///wcstoull() functions, respectively, except that the initial portion of the wide 
	///string shall be converted to intmax_t and uintmax_t representation, respectively.
	intmax_t Cinttypes::wcstoimax( const wchar_t* __QCMP_RESTRICT nptr, wchar_t** __QCMP_RESTRICT endptr, int base )
	{
		__QCS_MEMBER_FCONTEXT( "Cinttypes::wcstoimax" );
		intmax_t itResult = wcstol( nptr, endptr, base );
		return itResult;
	}

	//--------------------------------------------------------------------------------
	///These functions shall be equivalent to the wcstol(), wcstoll(), wcstoul(), and 
	///wcstoull() functions, respectively, except that the initial portion of the wide 
	///string shall be converted to intmax_t and uintmax_t representation, respectively.
	uintmax_t Cinttypes::wcstoumax( const wchar_t* __QCMP_RESTRICT nptr, wchar_t** __QCMP_RESTRICT endptr, int base )
	{
		__QCS_MEMBER_FCONTEXT( "Cinttypes::wcstoumax" );
		uintmax_t uitResult = wcstoul( nptr, endptr, base );
		return uitResult;
	}

}//nsBaseCRT
