//TestExceptions.h

//Unit Test exceptions

#ifndef _UNITTEST_TESTEXCEPTIONS_H_
#define _UNITTEST_TESTEXCEPTIONS_H_

#ifdef	__CQOR_OPTIMIZEINCLUDE
#pragma __CQOR_OPTIMIZEINCLUDE
#endif//__CQOR_OPTIMIZEINCLUDE

#include <exception>
#include <sstream>
#include "HippoQOR/comparer.h"
#include "HippoQOR/tuple.h"


//--------------------------------------------------------------------------------
namespace nsUnitTesting
{
	class MockRepository;

	__QCMP_STATIC_CONSTANT( unsigned int, EXCEPTION_BUFFER_SIZE = 65536 );

	//--------------------------------------------------------------------------------
	class BaseException : public std::exception 
	{
		char buffer[ EXCEPTION_BUFFER_SIZE ];
	public:
		void setException( const char* description, MockRepository* repo );
		const char* what() const throw() { return buffer; }
	};

	//--------------------------------------------------------------------------------
	// exception types
	class ExpectationException : public BaseException 
	{
	public:

		ExpectationException( MockRepository* repo, const base_tuple* tuple, const char* funcName );
	};

	//--------------------------------------------------------------------------------
	class NotImplementedException : public BaseException 
	{
	public:

		NotImplementedException( MockRepository* repo );
	};

	//--------------------------------------------------------------------------------
	class CallMissingException : public BaseException 
	{
	public:

		CallMissingException( MockRepository* repo );
	};

	//--------------------------------------------------------------------------------
	class NoResultSetUpException : public std::exception 
	{
		char buffer[ EXCEPTION_BUFFER_SIZE ];

	public:

		const char* what() const throw();
		NoResultSetUpException( const base_tuple* tuple, const char* funcName );

	};

	//--------------------------------------------------------------------------------
	//Type-safe exception wrapping
	class ExceptionHolder 
	{ 

	public:

		virtual ~ExceptionHolder();

		virtual void rethrow() = 0; 
	};

	//--------------------------------------------------------------------------------
	template <class T>
	class ExceptionWrapper : public ExceptionHolder 
	{

		T exception;

	public:

		//--------------------------------------------------------------------------------
		ExceptionWrapper(T exception) : exception(exception) 
		{
		}

		//--------------------------------------------------------------------------------
		void rethrow() 
		{ 
			throw exception; 
		}
	};

}//nsUnitTesting

#endif//_UNITTEST_TESTEXCEPTIONS_H_
