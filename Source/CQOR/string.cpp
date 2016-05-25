//string.cpp

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

//Generic string implementation

#include "CQOR/CQORPolicy.h"
#include <string.h>
#include <errno.h>
#include "SystemQOR.h"
#include QOR_SYS_PLATFORMHEADER(string.h)
#include "CodeQOR/Tracing/FunctionContextBase.h"
#include "CodeQOR/ErrorSystem/Error.h"
#include "CQOR.h"

//--------------------------------------------------------------------------------
namespace
{
	nsPlatform::Cstring _string;
}//anonymous

__QCMP_STARTLINKAGE_C

//--------------------------------------------------------------------------------
///memccpy
__QOR_INTERFACE( __CQOR ) void* memccpy( void* __QCMP_RESTRICT s1, const void* __QCMP_RESTRICT s2, int c, size_t n )
{
    __QCS_FCONTEXT( "memccpy" );

    void* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _string.memccpy( s1, s2, c, n );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
///memcpy
//#if (!__QCMP_DECLS_MEMCPY)
//#endif
//#pragma function memcpy
__QOR_INTERFACE( __CQOR ) void* __QCMP_CALLCON memcpy( void* __QCMP_RESTRICT s1, const void* __QCMP_RESTRICT s2, size_t n )
{
    __QCS_FCONTEXT( "memcpy" );

    void* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _string.memcpy( s1, s2, n );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
///memcpy_s
///
__QOR_INTERFACE( __CQOR ) errno_t memcpy_s( void* s1, size_t DstSize, const void* s2, size_t MaxCount )
{
    __QCS_FCONTEXT( "memcpy_s" );

    errno_t errResult = 0;
    __QCS_PROTECT
    {
        errResult = _string.memcpy_s( s1, DstSize, s2, MaxCount );
    }__QCS_ENDPROTECT
    return errResult;
}

//--------------------------------------------------------------------------------
///memmove
///
__QOR_INTERFACE( __CQOR ) void* memmove( void* s1, const void* s2, size_t n )
{
    __QCS_FCONTEXT( "memmove" );

    void* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _string.memmove( s1, s2, n );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
///memmove_s
///
__QOR_INTERFACE( __CQOR ) errno_t memmove_s( void* s1, size_t DstSize, const void* s2, size_t MaxCount )
{
    __QCS_FCONTEXT( "memmove_s" );

    errno_t errResult = 0;
    __QCS_PROTECT
    {
        errResult = _string.memmove_s( s1, DstSize, s2, MaxCount );
    }__QCS_ENDPROTECT
    return errResult;
}

//--------------------------------------------------------------------------------
///strcpy
__QOR_INTERFACE( __CQOR ) char* strcpy( char* __QCMP_RESTRICT s1, const char* __QCMP_RESTRICT s2 )
{
    __QCS_FCONTEXT( "strcpy" );

    char* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _string.strcpy( s1, s2 );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
///strcpy_s
///
__QOR_INTERFACE( __CQOR ) errno_t strcpy_s( char* s1, size_t SizeInBytes, const char* s2 )
{
    __QCS_FCONTEXT( "strcpy_s" );

    errno_t errResult = 0;
    __QCS_PROTECT
    {
        errResult = _string.strcpy_s( s1, SizeInBytes, s2 );
    }__QCS_ENDPROTECT
    return errResult;
}

//--------------------------------------------------------------------------------
///strncpy
///
__QOR_INTERFACE( __CQOR ) char* strncpy( char* __QCMP_RESTRICT s1, const char* __QCMP_RESTRICT s2, size_t n )
{
    __QCS_FCONTEXT( "strncpy" );

    char* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _string.strncpy( s1, s2, n );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
///strncpy_s
///
__QOR_INTERFACE( __CQOR ) errno_t strncpy_s( char* s1, size_t SizeInBytes, const char* s2, size_t MaxCount )
{
    __QCS_FCONTEXT( "strncpy_s" );

    errno_t errResult = 0;
    __QCS_PROTECT
    {
        errResult = _string.strncpy_s( s1, SizeInBytes, s2, MaxCount );
    }__QCS_ENDPROTECT
    return errResult;
}

//--------------------------------------------------------------------------------
///strcat
//#if (!__QCMP_DECLS_STRCAT)
//#endif
__QOR_INTERFACE( __CQOR ) char* strcat( char* __QCMP_RESTRICT s1, const char* __QCMP_RESTRICT s2 )
{
    __QCS_FCONTEXT( "strcat" );

    char* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _string.strcat( s1, s2 );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
///strcat_s
///
__QOR_INTERFACE( __CQOR ) errno_t strcat_s( char* s1, size_t SizeInBytes, const char* s2 )
{
    __QCS_FCONTEXT( "strcat_s" );

    errno_t errResult = 0;
    __QCS_PROTECT
    {
        errResult = _string.strcat_s( s1, SizeInBytes, s2 );
    }__QCS_ENDPROTECT
    return errResult;
}

//--------------------------------------------------------------------------------
///strncat
///
__QOR_INTERFACE( __CQOR ) char* strncat( char* __QCMP_RESTRICT s1, const char* __QCMP_RESTRICT s2, size_t n )
{
    __QCS_FCONTEXT( "strncat" );

    char* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _string.strncat( s1, s2, n );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
///strncat_s
///
__QOR_INTERFACE( __CQOR ) errno_t strncat_s( char* s1, size_t SizeInBytes, const char* s2, size_t MaxCount )
{
    __QCS_FCONTEXT( "strncat_s" );

    errno_t errResult = 0;
    __QCS_PROTECT
    {
        errResult = _string.strncat_s( s1, SizeInBytes, s2, MaxCount );
    }__QCS_ENDPROTECT
    return errResult;
}

//--------------------------------------------------------------------------------
///memcmp
//#if (!__QCMP_DECLS_MEMCMP)
//#endif
__QOR_INTERFACE( __CQOR ) int memcmp( const void* s1, const void* s2, size_t n )
{
    __QCS_FCONTEXT( "memcmp" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _string.memcmp( s1, s2, n );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///strcmp
//#if (!__QCMP_DECLS_STRCMP)
__QOR_INTERFACE( __CQOR ) int __QCMP_CALLCON strcmp( const char* s1, const char* s2 )
{
    __QCS_FCONTEXT( "strcmp" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _string.strcmp( s1, s2 );//nsCompiler::CCompiler::strcmp( s1, s2 );
    }__QCS_ENDPROTECT
    return iResult;
}
//#endif

//--------------------------------------------------------------------------------
///strcoll
///
__QOR_INTERFACE( __CQOR ) int strcoll( const char* s1, const char* s2 )
{
    __QCS_FCONTEXT( "strcoll" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _string.strcoll( s1, s2 );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///strncmp
///
__QOR_INTERFACE( __CQOR ) int strncmp( const char* s1, const char* s2, size_t n )
{
    __QCS_FCONTEXT( "strncmp" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _string.strncmp( s1, s2, n );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///strxfrm
///
__QOR_INTERFACE( __CQOR ) size_t strxfrm( char* __QCMP_RESTRICT s1, const char* __QCMP_RESTRICT s2, size_t n )
{
    __QCS_FCONTEXT( "strxfrm" );

    size_t Result = 0;
    __QCS_PROTECT
    {
        Result = _string.strxfrm( s1, s2, n );
    }__QCS_ENDPROTECT
    return Result;
}

//--------------------------------------------------------------------------------
///memchr
///
__QOR_INTERFACE( __CQOR ) void* memchr( const void* s, int c, size_t n )
{
    __QCS_FCONTEXT( "memchr" );

    void* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _string.memchr( s, c, n );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
///strchr
///
__QOR_INTERFACE( __CQOR ) char* strchr( const char* s, int c )
{
    __QCS_FCONTEXT( "strchr" );

    char* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _string.strchr( s, c);
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
///strcspn
///
__QOR_INTERFACE( __CQOR ) size_t strcspn( const char* s1, const char* s2 )
{
    __QCS_FCONTEXT( "strcspn" );

    size_t Result = 0;
    __QCS_PROTECT
    {
        Result = _string.strcspn( s1, s2 );
    }__QCS_ENDPROTECT
    return Result;
}

//--------------------------------------------------------------------------------
///strpbrk
///
__QOR_INTERFACE( __CQOR ) char* strpbrk( const char* s1, const char* s2 )
{
    __QCS_FCONTEXT( "strpbrk" );

    char* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _string.strpbrk( s1, s2 );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
///strrchr
///
__QOR_INTERFACE( __CQOR ) char* strrchr( const char* s, int c )
{
    __QCS_FCONTEXT( "strrchr" );

    char* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _string.strrchr( s, c );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
///strspn
///
__QOR_INTERFACE( __CQOR ) size_t strspn( const char* s1, const char* s2 )
{
    __QCS_FCONTEXT( "strspn" );

    size_t Result = 0;
    __QCS_PROTECT
    {
        Result = _string.strspn( s1, s2 );
    }__QCS_ENDPROTECT
    return Result;
}

//--------------------------------------------------------------------------------
///strstr
///
__QOR_INTERFACE( __CQOR ) char* strstr( const char* s1, const char* s2 )
{
    __QCS_FCONTEXT( "strstr" );

    char* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _string.strstr( s1, s2 );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
///strtok
///
__QOR_INTERFACE( __CQOR ) char* strtok( char* __QCMP_RESTRICT s1, const char* __QCMP_RESTRICT s2 )
{
    __QCS_FCONTEXT( "strtok" );

    char* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _string.strtok( s1, s2 );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
///strtok_r
///
__QOR_INTERFACE( __CQOR ) char* strtok_r( char* s1, const char* s2, char** ppContext )
{
    __QCS_FCONTEXT( "strtok_r" );

    char* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _string.strtok_r( s1, s2, ppContext );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
///strtok_s
///
__QOR_INTERFACE( __CQOR ) char* strtok_s( char* s1, const char* s2, char** ppContext )
{
    __QCS_FCONTEXT( "strtok_s" );

    char* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _string.strtok_s( s1, s2, ppContext );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
///memset
#if (!__QCMP_DECLS_MEMSET)
__QOR_INTERFACE( __CQOR )
#endif
void* __QCMP_CALLCON memset( void* s, int c, size_t n )
{
    __QCS_FCONTEXT( "memset" );

    void* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _string.memset( s, c, n );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
#ifndef OS_EXPORTS_STRING_STRERROR
///strerror
///
__QOR_INTERFACE( __CQOR ) char* strerror( int errnum )
{
    __QCS_FCONTEXT( "strerror" );

    char* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _string.strerror( errnum );
    }__QCS_ENDPROTECT
    return pResult;
}
#endif

//--------------------------------------------------------------------------------
///strerror_r
///
__QOR_INTERFACE( __CQOR ) int strerror_r( int errnum, char* strerrbuf, size_t buflen )
{
    __QCS_FCONTEXT( "strerror_r" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _string.strerror_r( errnum, strerrbuf, buflen );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///strerror_s
///
__QOR_INTERFACE( __CQOR ) errno_t strerror_s( char* Buf, size_t SizeInBytes, int ErrNum )
{
    __QCS_FCONTEXT( "strerror_s" );

    errno_t errResult = 0;
    __QCS_PROTECT
    {
        errResult = _string.strerror_s( Buf, SizeInBytes, ErrNum );
    }__QCS_ENDPROTECT
    return errResult;
}

//--------------------------------------------------------------------------------
///strlen
//#if (!__QCMP_DECLS_STRLEN)
__QOR_INTERFACE( __CQOR ) size_t strlen( const char* s )
{
    __QCS_FCONTEXT( "strlen" );

    size_t Result = 0;
    __QCS_PROTECT
    {
        Result = _string.strlen( s );
    }__QCS_ENDPROTECT
    return Result;
}
//#endif

//--------------------------------------------------------------------------------
///strnlen
///
__QOR_INTERFACE( __CQOR ) size_t strnlen( const char* s, size_t MaxCount )
{
    __QCS_FCONTEXT( "strnlen" );

    size_t Result = 0;
    __QCS_PROTECT
    {
        Result = _string.strnlen( s, MaxCount );
    }__QCS_ENDPROTECT
    return Result;
}

//--------------------------------------------------------------------------------
///strnicoll
///
__QOR_INTERFACE( __CQOR ) int strnicoll ( const char* _string1, const char* _string2, size_t count )
{
    __QCS_FCONTEXT( "strnicoll" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _string.strnicoll( _string1, _string2, count );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///stricmp
///
__QOR_INTERFACE( __CQOR ) int stricmp( const char* s1, const char* s2 )
{
    __QCS_FCONTEXT( "stricmp" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _string.stricmp( s1, s2 );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///strnicmp
///
__QOR_INTERFACE( __CQOR ) int strnicmp( const char* s1, const char* s2, size_t n )
{
    __QCS_FCONTEXT( "strnicmp" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _string.strnicmp( s1, s2, n );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///strdup
///
__QOR_INTERFACE( __CQOR ) char* strdup( char const* str )
{
    __QCS_FCONTEXT( "strdup" );

    char* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _string.strdup( str );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
//_strdup
__QOR_INTERFACE( __CQOR ) char* _strdup( char const* str )
{
    __QCS_FCONTEXT( "_strdup" );

    char* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _string.strdup( str );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int strcoll_l( const char*, const char*, locale_t )
{
	//TODO:
	return 0;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) Cmp__int64 strtoll_l( const char* nptr, char** endptr, int base, ::locale_t )
{
	//TODO:
	return 0;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) Cmp_unsigned__int64 strtoull_l( const char* nptr, char** endptr, int base, ::locale_t locale )
{
	//TODO:
	return 0;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) size_t strxfrm_l( char* __QCMP_RESTRICT, const char* __QCMP_RESTRICT, size_t, locale_t )
{
	//TODO:
	return 0;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) double strtold_l( const char* nptr, char** endptr, ::locale_t locale )
{
	//TODO:
	return 0;
}

__QCMP_ENDLINKAGE_C