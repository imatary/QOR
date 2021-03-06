//Basectype.h

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

//Base CRT class for CCtype

#ifndef SYSTEMQOR_POSIX_CTYPE_H_3
#define SYSTEMQOR_POSIX_CTYPE_H_3

#include "SystemQOR.h"
#include QOR_SYS_PLATFORMTYPES(ctype)
#include "CodeQOR/ClassReg/ClassRegEntry.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	using nsPlatform::locale_t;

	//------------------------------------------------------------------------------
    class __QOR_INTERFACE( __QSYS ) Cctype
    {
    public:

		__QOR_DECLARE_OCLASS_ID( Cctype );

        virtual int isalnum(int c);
		virtual int isalnum_l( int, locale_t );
        virtual int isalpha(int c);
		virtual int isalpha_l( int c, locale_t l );
        virtual int isblank(int c);
		virtual int isblank_l(int c, locale_t l );
        virtual int iscntrl(int c);
		virtual int iscntrl_l( int c, locale_t l );
        virtual int isdigit(int c);
		virtual int isdigit_l( int c, locale_t l );
        virtual int isgraph(int c);
		virtual int isgraph_l( int c, locale_t l );
        virtual int islower(int c);
		virtual int islower_l( int c, locale_t l );
        virtual int isprint(int c);
		virtual int isprint_l( int c, locale_t l );
        virtual int ispunct(int c);
		virtual int ispunct_l( int c, locale_t l );
        virtual int isspace(int c);
		virtual int isspace_l( int c, locale_t l );
        virtual int isupper(int c);
		virtual int isupper_l( int c, locale_t l );
        virtual int isxdigit(int c);
		virtual int isxdigit_l( int c, locale_t l );
        virtual int tolower(int c);
		virtual int tolower_l( int c, locale_t l );
        virtual int toupper(int c);
		virtual int toupper_l( int c, locale_t l );
        virtual int isascii(int c);
        virtual int toascii(int c);
		virtual int isatty( int fd );

		virtual int _ismbbalnum( unsigned int c );

	protected:

        Cctype();
        virtual ~Cctype();

	private:

		Cctype( const Cctype& );
		Cctype& operator = ( const Cctype& );

    };

}//nsBaseCRT

#endif//SYSTEMQOR_POSIX_CTYPE_H_3
