//ACodeString.h

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

//A class to raise the semantic level of ASCII strings embedded in the code
//It is intended that this will assist in automatic translation lookup 
//of hard coded strings in the future

#ifndef CODEQOR_DATASTRUCTS_ACODESTRING_H_1
#define CODEQOR_DATASTRUCTS_ACODESTRING_H_1

#include "CompilerQOR.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "CodeQOR.h"
#include "CodeQOR/DataStructures/TLRef.h"
#include "CodeQOR/Macros/ClassIdentityMacros.h"

//--------------------------------------------------------------------------------
namespace nsCodeQOR
{
    struct __QOR_INTERFACE( __CODEQOR ) CACodeString;
                                
#if ( !__QOR_UNICODE )									//Set the type of string objects for code stings
    typedef CACodeString CCodeString;
#endif

	class __QOR_INTERFACE( __CODEQOR ) CChar8;

    //--------------------------------------------------------------------------------
    //A wide character string wrapper
    struct __QOR_INTERFACE( __CODEQOR ) CACodeString
    {
    public:

        CACodeString( const char* cpString );
		CACodeString( const CACodeString& Src );
        CACodeString& operator = ( const CACodeString& Src );
        operator const char*( void ) const;
        const char* c_str( void ) const;
        CTLRef< CChar8 > str( void ) const;

		void Translate( void );

        //private: //To keep this as a POD type, no private members. Otherwise some GCC can't initialize

        const char* m_pOrg;
		mutable char* m_pTrans;
    };

}//nsCodeQOR

#endif//CODEQOR_DATASTRUCTS_WCODESTRING_H_1