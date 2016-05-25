//LIN_regex.h

// Copyright Querysoft Limited 2013
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

//Linux overrides for regex

#ifndef SYSTEMQOR_LIN_REGEX_H_3
#define SYSTEMQOR_LIN_REGEX_H_3

#include "SystemQOR/Linux/types/regex_types.h"
//#include "SystemQOR/Posix/Baseregex.h"

//--------------------------------------------------------------------------------
namespace nsLinux
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __QSYS ) Cregex //: public nsBaseCRT::Cregex
	{
	public:

		Cregex(){}
		~Cregex(){}

		virtual int regcomp(regex_t *__restrict, const char *__restrict, int);
		virtual int regexec(const regex_t *__restrict, const char *__restrict, size_t, regmatch_t *__restrict, int);
		virtual void regfree(regex_t *);

		virtual size_t regerror(int, const regex_t *__restrict, char *__restrict, size_t);

	private:

		Cregex( const Cregex& );
		Cregex& operator = ( const Cregex& );

	};

}//nsLinux

#endif//SYSTEMQOR_LIN_REGEX_H_3