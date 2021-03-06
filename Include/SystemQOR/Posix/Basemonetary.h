//Basemonetary.h

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

//Base CRT class for Cmonetary

#ifndef SYSTEMQOR_POSIX_MONETARY_H_3
#define SYSTEMQOR_POSIX_MONETARY_H_3

#include "SystemQOR.h"
#include QOR_SYS_PLATFORMTYPES(monetary)
#include "CodeQOR/ClassReg/ClassRegEntry.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	using nsPlatform::ssize_t;
	using nsPlatform::locale_t;
	using nsPlatform::va_list;

    //------------------------------------------------------------------------------
    class __QOR_INTERFACE( __QSYS ) Cmonetary
    {
        
	public:

		__QOR_DECLARE_OCLASS_ID( Cmonetary );

		virtual ssize_t strfmon( char*, size_t, const char*, va_list vargs );
		virtual ssize_t strfmon_l( char*, size_t, locale_t, const char*, va_list vargs );

	protected:

		Cmonetary();
		virtual ~Cmonetary();

	private:

		Cmonetary( const Cmonetary& );
		Cmonetary& operator = ( const Cmonetary& );
    };

}//nsBaseCRT

#endif//SYSTEMQOR_POSIX_MONETARY_H_3
