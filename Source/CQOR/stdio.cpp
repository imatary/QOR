//stdio.cpp

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

//Generic stdio implementation

#include "CQOR/CQORPolicy.h"
#include <stdio.h>
#include <errno.h>
#include "SystemQOR.h"
#include QOR_SYS_PLATFORMHEADER(stdio.h)
#include "CQOR.h"
#include "CodeQOR/Tracing/FunctionContextBase.h"
#include "CodeQOR/ErrorSystem/Error.h"

//--------------------------------------------------------------------------------
namespace
{
	nsPlatform::Cstdio _stdio;
}//anonymous

__QCMP_STARTLINKAGE_C

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) FILE* _stderr( void )
{
	__QCS_FCONTEXT( "_stderr" );

	FILE* pResult = 0;
	__QCS_PROTECT
	{
		pResult = _stdio._stderr();
	}__QCS_ENDPROTECT
	return pResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) FILE* _stdin( void )
{
	__QCS_FCONTEXT( "_stdin" );

	FILE* pResult = 0;
	__QCS_PROTECT
	{
		pResult = _stdio._stdin();
	}__QCS_ENDPROTECT
	return pResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) FILE* _stdout( void )
{
	__QCS_FCONTEXT( "_stdout" );

	FILE* pResult = 0;
	__QCS_PROTECT
	{
		pResult = _stdio._stdout();
	}__QCS_ENDPROTECT
	return pResult;
}

//--------------------------------------------------------------------------------
///clearerr
__QOR_INTERFACE( __CQOR ) void clearerr( FILE* stream )
{
    __QCS_FCONTEXT( "clearerr" );

    __QCS_PROTECT
    {
        _stdio.clearerr( stream );
    }__QCS_ENDPROTECT
}

//--------------------------------------------------------------------------------
///clearerr_s
__QOR_INTERFACE( __CQOR ) errno_t clearerr_s( FILE* stream )
{
    __QCS_FCONTEXT( "clearerr_s" );

    errno_t eResult = 0;
    __QCS_PROTECT
    {
        eResult = _stdio.clearerr_s( stream );
    }__QCS_ENDPROTECT
    return eResult;
}

//--------------------------------------------------------------------------------
/*
//implemented in unistd.cpp
///ctermid
__QOR_INTERFACE( __CQOR ) char* ctermid( char* pszTermPath )
{
    __QCS_FCONTEXT( "ctermid" );

    char* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _stdio.ctermid( pszTermPath );
    }__QCS_ENDPROTECT
    return pResult;
}
*/
//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int dprintf( int fd, const char* __QCMP_RESTRICT format, ... )
{
	__QCS_FCONTEXT( "dprintf" );

	int iResult = 0;
	__QCS_PROTECT
	{
        va_list args;
        va_start(args, format);
        iResult = _stdio.dprintf( fd, format, args );
        va_end(args);
	}__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
///fclose
__QOR_INTERFACE( __CQOR ) int fclose( FILE* stream )
{
    __QCS_FCONTEXT( "fclose" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.fclose( stream );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///fdopen
__QOR_INTERFACE( __CQOR ) FILE* fdopen( int fd, const char* mode )
{
    __QCS_FCONTEXT( "fdopen" );
    FILE* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _stdio.fdopen( fd, mode );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
///feof
__QOR_INTERFACE( __CQOR ) int feof( FILE *stream )
{
    __QCS_FCONTEXT( "feof" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.feof( stream );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///ferrror
__QOR_INTERFACE( __CQOR ) int ferror( FILE* stream )
{
    __QCS_FCONTEXT( "ferror" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.ferror( stream );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///fflush
__QOR_INTERFACE( __CQOR ) int fflush( FILE* stream )
{
    __QCS_FCONTEXT( "fflush" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.fflush( stream );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///fgetc
__QOR_INTERFACE( __CQOR ) int fgetc( FILE* stream )
{
    __QCS_FCONTEXT( "fgetc" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.fgetc( stream );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///fgetpos
__QOR_INTERFACE( __CQOR ) int fgetpos( FILE* __QCMP_RESTRICT stream, fpos_t* __QCMP_RESTRICT pos )
{
    __QCS_FCONTEXT( "fgetpos" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.fgetpos( stream, pos );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///fgets
__QOR_INTERFACE( __CQOR ) char* fgets( char* __QCMP_RESTRICT s, int n, FILE* __QCMP_RESTRICT stream )
{
    __QCS_FCONTEXT( "fgets" );

    char* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _stdio.fgets( s, n, stream );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
///fileno
__QOR_INTERFACE( __CQOR ) int fileno( FILE* stream )
{
    __QCS_FCONTEXT( "fileno" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.fileno( stream );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///flockfile
__QOR_INTERFACE( __CQOR ) void flockfile( FILE* stream )
{
    __QCS_FCONTEXT( "flockfile" );

    __QCS_PROTECT
    {
        _stdio.flockfile( stream );
    }__QCS_ENDPROTECT
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) FILE* fmemopen( void* __QCMP_RESTRICT buf, size_t size, const char* __QCMP_RESTRICT szMode )
{
    __QCS_FCONTEXT( "fmemopen" );

	FILE* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _stdio.fmemopen( buf, size, szMode );
    }__QCS_ENDPROTECT
	return pResult;
}

//--------------------------------------------------------------------------------
///fopen
__QOR_INTERFACE( __CQOR ) FILE* fopen( const char* __QCMP_RESTRICT filename, const char* __QCMP_RESTRICT mode )
{
    __QCS_FCONTEXT( "fopen" );

    FILE* pFile = 0;
    __QCS_PROTECT
    {
        pFile = _stdio.fopen( filename, mode );
    }__QCS_ENDPROTECT
    return pFile;
}

//--------------------------------------------------------------------------------
///fopen_s
__QOR_INTERFACE( __CQOR ) errno_t fopen_s( FILE** ppFile, const char* szFilename, const char* szMode )
{
    __QCS_FCONTEXT( "fopen_s" );

    errno_t eResult = 0;
    __QCS_PROTECT
    {
        eResult = _stdio.fopen_s( ppFile, szFilename, szMode );
    }__QCS_ENDPROTECT
    return eResult;
}

//--------------------------------------------------------------------------------
///fprintf
__QOR_INTERFACE( __CQOR ) int fprintf( FILE* __QCMP_RESTRICT stream, const char* __QCMP_RESTRICT format, ... )
{
    __QCS_FCONTEXT( "fprintf" );

    int iResult = 0;
    __QCS_PROTECT
    {
        va_list args;
        va_start(args, format);
        iResult = _stdio.fprintf( stream, format, args );
        va_end(args);
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///fprintf_s
__QOR_INTERFACE( __CQOR ) int fprintf_s( FILE* stream, const char* format, ... )
{
    __QCS_FCONTEXT( "fprintf_s" );

    int iResult = 0;
    __QCS_PROTECT
    {
        va_list args;
        va_start( args, format );
        iResult = _stdio.fprintf_s( stream, format, args );
        va_end( args );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///fputc
__QOR_INTERFACE( __CQOR ) int fputc( int c, FILE* stream )
{
    __QCS_FCONTEXT( "fputc" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.fputc( c, stream );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///fputs
__QOR_INTERFACE( __CQOR ) int fputs( const char* __QCMP_RESTRICT s, FILE* __QCMP_RESTRICT stream )
{
    __QCS_FCONTEXT( "fputs" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.fputs( s, stream );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
//fread
__QOR_INTERFACE( __CQOR ) size_t fread( void* __QCMP_RESTRICT ptr, size_t size, size_t nmemb, FILE* __QCMP_RESTRICT stream )
{
    __QCS_FCONTEXT( "fread" );

    size_t Result = 0;
    __QCS_PROTECT
    {
        Result = _stdio.fread( ptr, size, nmemb, stream );
    }__QCS_ENDPROTECT
    return Result;
}

//--------------------------------------------------------------------------------
///fread_s
__QOR_INTERFACE( __CQOR ) size_t fread_s( void* ptr, size_t DstSize, size_t ElementSize, size_t Count, FILE* pFile )
{
    __QCS_FCONTEXT( "fread_s" );

    size_t Result = 0;
    __QCS_PROTECT
    {
        Result = _stdio.fread_s( ptr, DstSize, ElementSize, Count, pFile );
    }__QCS_ENDPROTECT
    return Result;
}

//--------------------------------------------------------------------------------
///freopen
__QOR_INTERFACE( __CQOR ) FILE* freopen( const char* __QCMP_RESTRICT filename, const char* __QCMP_RESTRICT mode, FILE * __QCMP_RESTRICT stream )
{
    __QCS_FCONTEXT( "freopen" );

    FILE* pFile = 0;
    __QCS_PROTECT
    {
        pFile = _stdio.freopen( filename, mode, stream );
    }__QCS_ENDPROTECT
    return pFile;
}

//--------------------------------------------------------------------------------
///freopen_s
__QOR_INTERFACE( __CQOR ) errno_t freopen_s( FILE** ppFile, const char* szFilename, const char* szMode, FILE* pOldFile )
{
    __QCS_FCONTEXT( "freopen_s" );

    errno_t eResult = 0;
    __QCS_PROTECT
    {
        eResult = _stdio.freopen_s( ppFile, szFilename, szMode, pOldFile );
    }__QCS_ENDPROTECT
    return eResult;
}

//--------------------------------------------------------------------------------
///fscanf
__QOR_INTERFACE( __CQOR ) int fscanf( FILE* __QCMP_RESTRICT stream, const char* /*__QCMP_RESTRICT*/ format, ... )
{
    __QCS_FCONTEXT( "fscanf" );

    int iResult = 0;
    __QCS_PROTECT
    {
        va_list args;
        va_start( args, format );
        iResult = _stdio.fscanf( stream, format, args );
        va_end( args );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///fscanf_s
__QOR_INTERFACE( __CQOR ) int fscanf_s( FILE* pFile, const char* format, ... )
{
    __QCS_FCONTEXT( "fscanf_s" );

    int iResult = 0;
    __QCS_PROTECT
    {
        va_list args;
        va_start( args, format );
        iResult = _stdio.fscanf_s( pFile, format, args );
        va_end( args );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///fseek
__QOR_INTERFACE( __CQOR ) int fseek( FILE* stream, long int offset, int whence )
{
    __QCS_FCONTEXT( "fseek" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.fseek( stream, offset, whence );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///fseeko
__QOR_INTERFACE( __CQOR ) int fseeko( FILE* stream, off_t offset, int whence )
{
    __QCS_FCONTEXT( "fseeko" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.fseeko( stream, offset, whence );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///fsetpos
__QOR_INTERFACE( __CQOR ) int fsetpos( FILE* stream, const fpos_t* pos )
{
    __QCS_FCONTEXT( "fsetpos" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.fsetpos( stream, pos );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///ftell
__QOR_INTERFACE( __CQOR ) long int ftell( FILE* stream )
{
    __QCS_FCONTEXT( "ftell" );

    long int liResult = 0;
    __QCS_PROTECT
    {
        liResult = _stdio.ftell( stream );
    }__QCS_ENDPROTECT
    return liResult;
}

//--------------------------------------------------------------------------------
///ftello
__QOR_INTERFACE( __CQOR ) off_t ftello( FILE* stream )
{
    __QCS_FCONTEXT( "ftello" );

    off_t Result = 0;
    __QCS_PROTECT
    {
        Result = _stdio.ftello( stream );
    }__QCS_ENDPROTECT
    return Result;
}

//--------------------------------------------------------------------------------
///ftrylockfile
__QOR_INTERFACE( __CQOR ) int ftrylockfile( FILE* stream )
{
    __QCS_FCONTEXT( "ftrylockfile" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.ftrylockfile( stream );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///funlockfile
__QOR_INTERFACE( __CQOR ) void funlockfile( FILE* stream )
{
    __QCS_FCONTEXT( "funlockfile" );

    __QCS_PROTECT
    {
        _stdio.funlockfile( stream );
    }__QCS_ENDPROTECT
}

//--------------------------------------------------------------------------------
///fwrite
__QOR_INTERFACE( __CQOR ) size_t fwrite( const void* __QCMP_RESTRICT ptr, size_t size, size_t nmemb, FILE* __QCMP_RESTRICT stream )
{
    __QCS_FCONTEXT( "fwrite" );

    size_t Result = 0;
    __QCS_PROTECT
    {
        Result = _stdio.fwrite( ptr, size, nmemb, stream );
    }__QCS_ENDPROTECT
    return Result;
}

//--------------------------------------------------------------------------------
///getc
__QOR_INTERFACE( __CQOR ) int getc( FILE* stream )
{
    __QCS_FCONTEXT( "getc" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.getc( stream );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///getchar
__QOR_INTERFACE( __CQOR ) int getchar( void )
{
    __QCS_FCONTEXT( "getchar" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.getchar();
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///getc_unlocked
__QOR_INTERFACE( __CQOR ) int getc_unlocked( FILE* pFile )
{
    __QCS_FCONTEXT( "getc_unlocked" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.getc_unlocked( pFile );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///getchar_unlocked
__QOR_INTERFACE( __CQOR ) int getchar_unlocked( void )
{
    __QCS_FCONTEXT( "getchar_unlocked" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.getchar_unlocked();
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) ssize_t getdelim( char** __QCMP_RESTRICT lineptr, size_t* __QCMP_RESTRICT n, int delimiter, FILE* __QCMP_RESTRICT stream )
{
	__QCS_FCONTEXT( "getdelim" );

	ssize_t Result = 0;
	__QCS_PROTECT
	{
		Result = _stdio.getdelim( lineptr, n, delimiter, stream );
	}__QCS_ENDPROTECT
	return Result;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) ssize_t getline( char** __QCMP_RESTRICT lineptr, size_t* __QCMP_RESTRICT n, FILE* __QCMP_RESTRICT stream )
{
	__QCS_FCONTEXT( "getline" );

	ssize_t Result = 0;
	__QCS_PROTECT
	{
		Result = _stdio.getline( lineptr, n, stream );
	}__QCS_ENDPROTECT
	return Result;
}

//--------------------------------------------------------------------------------
///gets
__QOR_INTERFACE( __CQOR ) char* gets( char* s )
{
    __QCS_FCONTEXT( "gets" );

    char* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _stdio.gets( s );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
///gets_s
__QOR_INTERFACE( __CQOR ) char* gets_s( char* s, size_t _Size )
{
    __QCS_FCONTEXT( "gets_s" );

    char* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _stdio.gets_s( s, _Size );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) FILE* open_memstream( char** bufp, size_t* sizep )
{
    __QCS_FCONTEXT( "open_memstream" );

    FILE* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _stdio.open_memstream( bufp, sizep );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
///pclose
__QOR_INTERFACE( __CQOR ) int pclose( FILE* pFile )
{
    __QCS_FCONTEXT( "pclose" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.pclose( pFile );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///perror
__QOR_INTERFACE( __CQOR ) void perror( const char* s )
{
    __QCS_FCONTEXT( "perror" );

    __QCS_PROTECT
    {
        _stdio.perror( s );
    }__QCS_ENDPROTECT
}

//--------------------------------------------------------------------------------
///popen
__QOR_INTERFACE( __CQOR ) FILE* popen( const char* szCommand, const char* szMode )
{
    __QCS_FCONTEXT( "popen" );

    FILE* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _stdio.popen( szCommand, szMode );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
///printf
__QOR_INTERFACE( __CQOR ) int printf( const char* format, ... )
{
    __QCS_FCONTEXT( "printf" );

    int iResult = 0;
    __QCS_PROTECT
    {
        va_list args;
        va_start( args, format );
        iResult = _stdio.printf( format, args );
        va_end(args);
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///printf_s
__QOR_INTERFACE( __CQOR ) int printf_s( const char* format, ... )
{
    __QCS_FCONTEXT( "printf_s" );

    int iResult = 0;
    __QCS_PROTECT
    {
        va_list args;
        va_start( args, format );
        iResult = _stdio.printf_s( format, args );
        va_end( args );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///putc
__QOR_INTERFACE( __CQOR ) int putc( int c, FILE* stream )
{
    __QCS_FCONTEXT( "putc" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.putc( c, stream );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///putchar
__QOR_INTERFACE( __CQOR ) int putchar( int c )
{
    __QCS_FCONTEXT( "putchar" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.putchar( c );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///putc_unlocked
__QOR_INTERFACE( __CQOR ) int putc_unlocked( int c, FILE* pFile )
{
    __QCS_FCONTEXT( "putc_unlocked" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.putc_unlocked( c, pFile );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///putchar_unlocked
__QOR_INTERFACE( __CQOR ) int putchar_unlocked( int c )
{
    __QCS_FCONTEXT( "putchar_unlocked" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.putchar_unlocked( c );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///puts
__QOR_INTERFACE( __CQOR ) int puts( const char* s )
{
    __QCS_FCONTEXT( "putchar" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.puts( s );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///remove
__QOR_INTERFACE( __CQOR ) int remove( const char* filename )
{
    __QCS_FCONTEXT( "remove" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.remove( filename );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///rename
#ifndef OS_EXPORTS_STDIO_RENAME
__QOR_INTERFACE( __CQOR ) int rename( const char* old, const char* pnew )
{
    __QCS_FCONTEXT( "rename" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.rename( old, pnew );
    }__QCS_ENDPROTECT
    return iResult;
}
#endif

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int renameat( int ofd, const char* szOld, int newfd, const char* szNew )
{
	__QCS_FCONTEXT( "renameat" );

	int iResult = 0;
	__QCS_PROTECT
	{
		iResult = _stdio.renameat( ofd, szOld, newfd, szNew );
	}__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
///rewind
__QOR_INTERFACE( __CQOR ) void rewind( FILE* stream )
{
    __QCS_FCONTEXT( "rewind" );

    __QCS_PROTECT
    {
        _stdio.rewind( stream );
    }__QCS_ENDPROTECT
}

//--------------------------------------------------------------------------------
///scanf
__QOR_INTERFACE( __CQOR ) int scanf( const char* __QCMP_RESTRICT format, ... )
{
    __QCS_FCONTEXT( "scanf" );

    int iResult = 0;
    __QCS_PROTECT
    {
        va_list args;
        va_start( args, format );
        iResult = _stdio.scanf( format, args );
        va_end(args);
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///scanf_s
__QOR_INTERFACE( __CQOR ) int scanf_s( const char* format, ... )
{
    __QCS_FCONTEXT( "scanf_s" );

    int iResult = 0;
    __QCS_PROTECT
    {
        va_list args;
        va_start( args, format );
        iResult = _stdio.scanf_s( format, args );
        va_end( args );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///setbuf
__QOR_INTERFACE( __CQOR ) void setbuf( FILE* __QCMP_RESTRICT stream, char* __QCMP_RESTRICT buf )
{
    __QCS_FCONTEXT( "setbuf" );

    __QCS_PROTECT
    {
        _stdio.setbuf( stream, buf );
    }__QCS_ENDPROTECT
}

//--------------------------------------------------------------------------------
///setvbuf
__QOR_INTERFACE( __CQOR ) int setvbuf( FILE* __QCMP_RESTRICT stream, char* __QCMP_RESTRICT buf, int mode, size_t size )
{
    __QCS_FCONTEXT( "setvbuf" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.setvbuf( stream, buf, mode, size );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///snprintf
__QOR_INTERFACE( __CQOR ) int snprintf( char* __QCMP_RESTRICT s, size_t n, const char* /*__QCMP_RESTRICT*/ format, ... )
{
    __QCS_FCONTEXT( "snprintf" );

    int iResult = 0;
    __QCS_PROTECT
    {
        va_list args;
        va_start( args, format );
        iResult = _stdio.snprintf( s, n, format, args );
        va_end(args);
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
//sprintf
__QOR_INTERFACE( __CQOR ) int sprintf( char* __QCMP_RESTRICT s, const char* /*__QCMP_RESTRICT*/ format, ... )
{
    __QCS_FCONTEXT( "sprintf" );

    int iResult = 0;
    __QCS_PROTECT
    {
        va_list args;
        va_start( args, format );
        iResult = _stdio.sprintf( s, format, args );
        va_end(args);
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///sprintf_s
__QOR_INTERFACE( __CQOR ) int sprintf_s( char* s, size_t SizeInBytes, const char* format, ... )
{
    __QCS_FCONTEXT( "sprintf_s" );

    int iResult = 0;
    __QCS_PROTECT
    {
        va_list args;
        va_start( args, format );
        iResult = _stdio.sprintf_s( s, SizeInBytes, format, args );
        va_end( args );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///sscanf
__QOR_INTERFACE( __CQOR ) int sscanf( const char* __QCMP_RESTRICT s, const char* /*__QCMP_RESTRICT*/ format, ... )
{
    __QCS_FCONTEXT( "sscanf" );

    int iResult = 0;
    __QCS_PROTECT
    {
        va_list args;
        va_start( args, format );
        iResult = _stdio.sscanf( s, format, args );
        va_end(args);
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///sscanf_s
__QOR_INTERFACE( __CQOR ) int sscanf_s( const char* s, const char* format, ... )
{
    __QCS_FCONTEXT( "sscanf_s" );

    int iResult = 0;
    __QCS_PROTECT
    {
        va_list args;
        va_start( args, format );
        iResult = _stdio.sscanf_s( s, format, args );
        va_end( args );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///tempnam
__QOR_INTERFACE( __CQOR ) char* tempnam( const char* szDir, const char* szPfx )
{
    __QCS_FCONTEXT( "tempnam" );

    char* pResult = 0;
    __QCS_PROTECT
    {
        pResult = _stdio.tempnam( szDir, szPfx );
    }__QCS_ENDPROTECT
    return pResult;
}

//--------------------------------------------------------------------------------
///tmpfile
__QOR_INTERFACE( __CQOR ) FILE* tmpfile( void )
{
    __QCS_FCONTEXT( "tmpfile" );

    FILE* pFile = 0;
    __QCS_PROTECT
    {
        pFile = _stdio.tmpfile();
    }__QCS_ENDPROTECT
    return pFile;
}

//--------------------------------------------------------------------------------
///tmpfile_s
__QOR_INTERFACE( __CQOR ) errno_t tmpfile_s( FILE** ppFile )
{
    __QCS_FCONTEXT( "tmpfile_s" );

    errno_t eResult = 0;
    __QCS_PROTECT
    {
        eResult = _stdio.tmpfile_s( ppFile );
    }__QCS_ENDPROTECT
    return eResult;
}

//--------------------------------------------------------------------------------
///tmpnam
__QOR_INTERFACE( __CQOR ) char* tmpnam( char* s )
{
    __QCS_FCONTEXT( "tmpnam" );

    char* pName = 0;
    __QCS_PROTECT
    {
        pName = _stdio.tmpnam( s );
    }__QCS_ENDPROTECT
    return pName;
}

//--------------------------------------------------------------------------------
///tmpnam_s
__QOR_INTERFACE( __CQOR ) errno_t tmpnam_s( char* s, size_t Size )
{
    __QCS_FCONTEXT( "tmpname_s" );

    errno_t eResult = 0;
    __QCS_PROTECT
    {
        eResult = _stdio.tmpnam_s( s, Size );
    }__QCS_ENDPROTECT
    return eResult;
}

//--------------------------------------------------------------------------------
///ungetc
__QOR_INTERFACE( __CQOR ) int ungetc( int c, FILE* stream )
{
    __QCS_FCONTEXT( "ungetc" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.ungetc( c, stream );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///vfprintf
__QOR_INTERFACE( __CQOR ) int vfprintf( FILE* __QCMP_RESTRICT stream, const char* __QCMP_RESTRICT format, va_list arg )
{
    __QCS_FCONTEXT( "vfprintf" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.vfprintf( stream, format, arg );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///vfprintf_s
__QOR_INTERFACE( __CQOR ) int vfprintf_s( FILE* stream, const char* format, va_list arg )
{
    __QCS_FCONTEXT( "vfprintf_s" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.vfprintf_s( stream, format, arg );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///vfscanf
__QOR_INTERFACE( __CQOR ) int vfscanf( FILE* __QCMP_RESTRICT stream, const char* __QCMP_RESTRICT format, va_list arg )
{
    __QCS_FCONTEXT( "vfscanf" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.vfscanf( stream, format, arg );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///vprintf
__QOR_INTERFACE( __CQOR ) int vprintf( const char* __QCMP_RESTRICT format, va_list arg )
{
    __QCS_FCONTEXT( "vprintf" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.vprintf( format, arg );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///vprintf_s
__QOR_INTERFACE( __CQOR ) int vprintf_s( const char* format, va_list arg )
{
    __QCS_FCONTEXT( "vprintf_s" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.vprintf_s( format, arg );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///vscanf
__QOR_INTERFACE( __CQOR ) int vscanf( const char* __QCMP_RESTRICT format, va_list arg )
{
    __QCS_FCONTEXT( "vscanf" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.vscanf( format, arg );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///vsnprintf
__QOR_INTERFACE( __CQOR ) int vsnprintf( char* __QCMP_RESTRICT s, size_t n, const char* __QCMP_RESTRICT format, va_list arg )
{
    __QCS_FCONTEXT( "vsnprintf" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.vsnprintf( s, n, format, arg );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///vsprintf
__QOR_INTERFACE( __CQOR ) int vsprintf( char* __QCMP_RESTRICT s, const char* __QCMP_RESTRICT format, va_list arg )
{
    __QCS_FCONTEXT( "vsprintf" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.vsprintf( s, format, arg );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///vsprintf_s
__QOR_INTERFACE( __CQOR ) int vsprintf_s( char* s, size_t SizeInBytes, const char* format, va_list arg )
{
    __QCS_FCONTEXT( "vsprintf_s" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.vsprintf_s( s, SizeInBytes, format, arg );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
///vsscanf
__QOR_INTERFACE( __CQOR ) int vsscanf( const char* __QCMP_RESTRICT s, const char* __QCMP_RESTRICT format, va_list arg )
{
    __QCS_FCONTEXT( "vsscanf" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _stdio.vsscanf( s, format, arg );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int sscanf_l( const char* buffer, ::locale_t locale, const char* format, ... ) //int _sscanf_l( const char* buffer, const char* format, ::locale_t locale, ... );
{
	__QCS_FCONTEXT( "sscanf_l" );

	int iResult = 0;
	__QCS_PROTECT
	{
        va_list args;
        va_start(args, format);
		//TODO: iResult = _stdio.sscanf_l( buffer, locale, format, args );
		va_end(args);
	}__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int sprintf_l( char* buffer, ::locale_t locale, const char* format, ... )// _sprintf_l( , __f, __l, __VA_ARGS__ )
{
	__QCS_FCONTEXT( "sprintf_l" );

	int iResult = 0;
	__QCS_PROTECT
	{
		va_list args;
		va_start( args, format );
		//TODO: iResult = _stdio.sprintf_l( buffer, locale, format, args );
		va_end( args );
	}__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int snprintf_l( char* buffer, size_t count, ::locale_t locale, const char* format, ... )
{
	__QCS_FCONTEXT( "snprintf_l" );

	int iResult = 0;
	__QCS_PROTECT
	{
		va_list args;
		va_start( args, format );
		//TODO: iResult= _stdio.snprintf_l( buffer, count, locale, format, args );
		va_end( args );
	}__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int asprintf_l( char **ret, ::locale_t loc, const char* format, ... )
{
	//TODO:
	return 0;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int vasprintf_l( char **ret, ::locale_t loc, const char* format, va_list ap )
{
	//TODO:
	return 0;
}

__QCMP_ENDLINKAGE_C
