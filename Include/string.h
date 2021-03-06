//string.h

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

//NOTE: This file is included by <windows.h> when used under Windows: Beware circular dependencies

#ifndef QOR_STRING_H_3
#define QOR_STRING_H_3

#ifndef _QSYS_STRING_DEFINES
#   include "SystemQOR.h"
#	include <wchar.h>
#else
#	include <stdarg.h>
__QCMP_STARTLINKAGE_C
	__QOR_INTERFACE( __CQOR ) wchar_t* __QCMP_CALLCON wcscpy( wchar_t* __QCMP_RESTRICT s1, const wchar_t* __QCMP_RESTRICT s2 );
__QCMP_ENDLINKAGE_C
#endif

#include <stddef.h>
#include QOR_SYS_PLATFORMTYPES(string)

typedef nsPlatform::errno_t errno_t;
typedef nsPlatform::locale_t locale_t;
#ifndef _INC_CRTDEFS
typedef nsPlatform::_locale_t _locale_t;
#endif

__QCMP_STARTLINKAGE_C

    __QOR_INTERFACE( __CQOR ) void* memccpy( void* __QCMP_RESTRICT, const void* __QCMP_RESTRICT, int, size_t );
    __QOR_INTERFACE( __CQOR ) void* memchr(const void *s, int c, size_t n);
#if (!__QCMP_DECLS_MEMCMP || __CQOR )
    __QOR_INTERFACE( __CQOR ) int memcmp(const void *s1, const void *s2, size_t n);
#else
	int memcmp( const void *s1, const void *s2, size_t n );
#endif

#if (!__QCMP_DECLS_MEMCPY || __CQOR )
    __QOR_INTERFACE( __CQOR ) void* memcpy( void* __QCMP_RESTRICT s1, const void* __QCMP_RESTRICT s2, size_t n );
#else
	void* memcpy( void* __QCMP_RESTRICT s1, const void* __QCMP_RESTRICT s2, size_t n );
#endif

    __QOR_INTERFACE( __CQOR ) errno_t memcpy_s( void* s1, size_t DstSize, const void* s2, size_t MaxCount );
    __QOR_INTERFACE( __CQOR ) void* memmove( void* s1, const void* s2, size_t n );
    __QOR_INTERFACE( __CQOR ) errno_t memmove_s( void* s1, size_t DstSize, const void* s2, size_t MaxCount );

#if (!__QCMP_DECLS_MEMSET || __CQOR )
    __QOR_INTERFACE( __CQOR ) void* memset( void* s, int c, size_t n );
#else
	void* __cdecl memset( void* s, int c, size_t n );
#endif

	__QOR_INTERFACE( __CQOR ) char* stpcpy( char* __QCMP_RESTRICT, const char* __QCMP_RESTRICT );
	__QOR_INTERFACE( __CQOR ) char* stpncpy( char* __QCMP_RESTRICT, const char* __QCMP_RESTRICT, size_t );

#if (!__QCMP_DECLS_STRCAT || __CQOR )
    __QOR_INTERFACE( __CQOR ) char* strcat( char* __QCMP_RESTRICT s1, const char* __QCMP_RESTRICT s2 );
#else
    extern char* strcat( char* __QCMP_RESTRICT s1, const char* __QCMP_RESTRICT s2 );
#endif

    __QOR_INTERFACE( __CQOR ) errno_t strcat_s( char* s1, size_t SizeInBytes, const char* s2 );
    __QOR_INTERFACE( __CQOR ) char* strchr( const char* s, int c );
#if (!__QCMP_DECLS_STRCMP || __CQOR )
    __QOR_INTERFACE( __CQOR ) int strcmp( const char* s1, const char* s2 );
#else
    extern int strcmp( const char* s1, const char* s2);
#endif
    __QOR_INTERFACE( __CQOR ) int strcoll( const char* s1, const char* s2 );
	__QOR_INTERFACE( __CQOR ) int strcoll_l( const char*, const char*, locale_t );

#if (!__QCMP_DECLS_STRCPY || __CQOR )
    __QOR_INTERFACE( __CQOR ) char* strcpy( char* __QCMP_RESTRICT s1, const char* __QCMP_RESTRICT s2 );
#else
	extern char* strcpy( char* __QCMP_RESTRICT s1, const char* __QCMP_RESTRICT s2 );
#endif
    __QOR_INTERFACE( __CQOR ) errno_t strcpy_s( char* s1, size_t SizeInBytes, const char* s2 );
    __QOR_INTERFACE( __CQOR ) size_t strcspn( const char* s1, const char* s2 );

#ifndef OS_EXPORTS_STRING_STRERROR
    __QOR_INTERFACE( __CQOR ) char* strerror( int errnum );
#endif
	__QOR_INTERFACE( __CQOR ) char* strerror_l( int, locale_t );
    __QOR_INTERFACE( __CQOR ) int strerror_r( int errnum, char* strerrbuf, size_t buflen );
    __QOR_INTERFACE( __CQOR ) errno_t strerror_s( char* Buf, size_t SizeInBytes, int ErrNum );
#if (!__QCMP_DECLS_STRLEN || __CQOR )
    __QOR_INTERFACE( __CQOR ) size_t strlen( const char* s );
#else
    extern size_t strlen( const char* s );
#endif

    __QOR_INTERFACE( __CQOR ) char* strncat( char* __QCMP_RESTRICT s1, const char* __QCMP_RESTRICT s2, size_t n );
    __QOR_INTERFACE( __CQOR ) errno_t strncat_s( char* s1, size_t SizeInBytes, const char* s2, size_t MaxCount );
    __QOR_INTERFACE( __CQOR ) int strncmp( const char* s1, const char* s2, size_t n );
    __QOR_INTERFACE( __CQOR ) char* strncpy( char* __QCMP_RESTRICT s1, const char* __QCMP_RESTRICT s2, size_t n );
    __QOR_INTERFACE( __CQOR ) errno_t strncpy_s( char* s1, size_t SizeInBytes, const char* s2, size_t MaxCount );
	__QOR_INTERFACE( __CQOR ) char* strndup( const char*, size_t );
	__QOR_INTERFACE( __CQOR ) size_t strnlen( const char* s, size_t MaxCount );
    __QOR_INTERFACE( __CQOR ) char* strpbrk( const char* s1, const char* s2 );
    __QOR_INTERFACE( __CQOR ) char* strrchr( const char* s, int c );
	__QOR_INTERFACE( __CQOR ) char* strsignal(int);
    __QOR_INTERFACE( __CQOR ) size_t strspn( const char* s1, const char* s2 );
    __QOR_INTERFACE( __CQOR ) char* strstr( const char* s1, const char* s2 );
    __QOR_INTERFACE( __CQOR ) char* strtok( char* __QCMP_RESTRICT s1, const char* __QCMP_RESTRICT s2 );
    __QOR_INTERFACE( __CQOR ) char* strtok_r( char*, const char*, char** );
    __QOR_INTERFACE( __CQOR ) char* strtok_s( char* s1, const char* s2, char** ppContext );
    __QOR_INTERFACE( __CQOR ) size_t strxfrm( char* __QCMP_RESTRICT s1, const char* __QCMP_RESTRICT s2, size_t n );
	__QOR_INTERFACE( __CQOR ) size_t strxfrm_l( char* __QCMP_RESTRICT, const char* __QCMP_RESTRICT, size_t, locale_t );
    __QOR_INTERFACE( __CQOR ) char* strdup( char const* str );

    //MSW Compatible Extensions
    __QOR_INTERFACE( __CQOR ) int stricmp( const char* s1, const char* s2 );
    __QOR_INTERFACE( __CQOR ) int strnicmp( const char* s1, const char* s2, size_t n );
    __QOR_INTERFACE( __CQOR ) int strnicoll ( const char* _string1, const char* _string2, size_t count );
	__QOR_INTERFACE( __CQOR ) size_t _strxfrm_l( char* strDest, const char* strSource, size_t count, ::_locale_t locale );
	__QOR_INTERFACE( __CQOR ) int _stricmp( const char* string1, const char* string2 );
	__QOR_INTERFACE( __CQOR ) int _strcoll_l( const char* string1, const char* string2, ::_locale_t locale );
	__QOR_INTERFACE( __CQOR ) char* _strdate( char* datestr );
	__QOR_INTERFACE( __CQOR ) errno_t _strdate_s( char* buffer, size_t numberOfElements );
	__QOR_INTERFACE( __CQOR ) char* _strdup_dbg( const char* strSource, int blockType, const char* filename, int linenumber );
	__QOR_INTERFACE( __CQOR ) char* _strerror( const char* strErrMsg );
	__QOR_INTERFACE( __CQOR ) errno_t _strerror_s( char* buffer, size_t numberOfElements, const char* strErrMsg );
	__QOR_INTERFACE( __CQOR ) int _stricmp( const char* string1, const char* string2 );
	__QOR_INTERFACE( __CQOR ) int _stricmp_l( const char* string1, const char* string2, ::_locale_t locale );
	__QOR_INTERFACE( __CQOR ) int _stricoll( const char* string1, const char* string2 );
	__QOR_INTERFACE( __CQOR ) int _stricoll_l( const char* string1, const char* string2, ::_locale_t locale );
	__QOR_INTERFACE( __CQOR ) char* _strlwr( char* str);
	__QOR_INTERFACE( __CQOR ) char* _strlwr_l( char* str, ::_locale_t locale );
	__QOR_INTERFACE( __CQOR ) errno_t _strlwr_s( char* str, size_t numberOfElements );
	__QOR_INTERFACE( __CQOR ) errno_t _strlwr_s_l( char* str, size_t numberOfElements, ::_locale_t locale );
	__QOR_INTERFACE( __CQOR ) int _strncoll( const char* string1, const char* string2, size_t count );
	__QOR_INTERFACE( __CQOR ) int _strncoll_l( const char* string1, const char* string2, size_t count, ::_locale_t locale );
	__QOR_INTERFACE( __CQOR ) int _strnicmp( const char* string1, const char* string2, size_t count );
	__QOR_INTERFACE( __CQOR ) int _strnicmp_l( const char* string1, const char* string2, size_t count, ::_locale_t locale );
	__QOR_INTERFACE( __CQOR ) int _strnicoll( const char* string1, const char* string2, size_t count );
	__QOR_INTERFACE( __CQOR ) int _strnicoll_l( const char* string1, const char* string2, size_t count, ::_locale_t locale );
	__QOR_INTERFACE( __CQOR ) char* _strnset( char* str, int c, size_t count );
	__QOR_INTERFACE( __CQOR ) errno_t _strnset_s( char* str, size_t numberOfElements, int c, size_t count );
	__QOR_INTERFACE( __CQOR ) char* _strrev( char* str );
	__QOR_INTERFACE( __CQOR ) char* _strset( char* str, int c );
	__QOR_INTERFACE( __CQOR ) errno_t _strset_s( char* str, size_t numberOfElements, int c );
	__QOR_INTERFACE( __CQOR ) char* _strtime( char* timestr );
	__QOR_INTERFACE( __CQOR ) errno_t _strtime_s( char* buffer, size_t numberOfElements );
	__QOR_INTERFACE( __CQOR ) double _strtod_l( const char* nptr, char** endptr, ::_locale_t locale );
	__QOR_INTERFACE( __CQOR ) double strtold_l( const char* nptr, char** endptr, ::locale_t locale );
	__QOR_INTERFACE( __CQOR ) Cmp__int64 _strtoi64( const char* nptr, char** endptr, int base );
	__QOR_INTERFACE( __CQOR ) Cmp__int64 _strtoi64_l( const char* nptr, char** endptr, int base, ::_locale_t locale );
	__QOR_INTERFACE( __CQOR ) Cmp__int64 strtoll_l( const char* nptr, char** endptr, int base, ::locale_t );
	__QOR_INTERFACE( __CQOR ) long _strtol_l( const char* nptr, char** endptr, int base, ::_locale_t locale );
	__QOR_INTERFACE( __CQOR ) Cmp_unsigned__int64 _strtoui64( const char* nptr, char** endptr, int base );
	__QOR_INTERFACE( __CQOR ) Cmp_unsigned__int64 _strtoui64_l( const char* nptr, char** endptr, int base, ::_locale_t locale );
	__QOR_INTERFACE( __CQOR ) Cmp_unsigned__int64 strtoull_l( const char* nptr, char** endptr, int base, ::locale_t locale );
	__QOR_INTERFACE( __CQOR ) unsigned long _strtoul_l( const char* nptr, char** endptr, int base, ::_locale_t locale );
	__QOR_INTERFACE( __CQOR ) char* _strupr( char* str );
	__QOR_INTERFACE( __CQOR ) char* _strupr_l( char* str, ::_locale_t locale );
	__QOR_INTERFACE( __CQOR ) errno_t _strupr_s( char* str, size_t numberOfElements );
	__QOR_INTERFACE( __CQOR ) errno_t _strupr_s_l( char* str, size_t numberOfElements, ::_locale_t locale );
	__QOR_INTERFACE( __CQOR ) void* _memccpy( void* dest, const void* src, int c, size_t count );
	__QOR_INTERFACE( __CQOR ) int _memicmp( const void* buf1, const void* buf2, size_t count );
	__QOR_INTERFACE( __CQOR ) int _memicmp_l( const void* buf1, const void* buf2, size_t count, ::_locale_t locale );

__QCMP_ENDLINKAGE_C

#endif//QOR_STRING_H_3

