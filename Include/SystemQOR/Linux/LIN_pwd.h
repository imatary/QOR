//LIN_pwd.h

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

//Linux overrides for pwd

#ifndef SYSTEMQOR_LIN_PWD_H_3
#define SYSTEMQOR_LIN_PWD_H_3

#include "SystemQOR/Linux/types/pwd_types.h"
//#include "SystemQOR/Posix/Baseregex.h"

//--------------------------------------------------------------------------------
namespace nsLinux
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __QSYS ) Cpwd //: public nsBaseCRT::Cregex
	{
	public:

		Cpwd(){}
		~Cpwd(){}

		virtual void setpwent (void);
		virtual void endpwent (void);
		virtual passwd *getpwent (void);

		virtual passwd *getpwuid (uid_t);
		virtual passwd *getpwnam (const char *);
		int getpwuid_r ( uid_t, passwd *, char *, size_t, passwd** );
		int getpwnam_r ( const char *, passwd*, char *, size_t, passwd** );

#ifdef _GNU_SOURCE
		virtual passwd* fgetpwent( FILE* );
		virtual int putpwent( const passwd*, FILE* );
#endif

	private:

		Cpwd( const Cpwd& );
		Cpwd& operator = ( const Cpwd& );

	};

}//nsLinux

#endif//SYSTEMQOR_LIN_REGEX_H_3
