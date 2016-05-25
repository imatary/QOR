//Posum_Stream.h

#ifndef _WINQL_POSUM_STREAM_H_
#define _WINQL_POSUM_STREAM_H_

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include <errno.h>
#include "CodeQOR/DataStructures/TLRef.h"
#include "SystemQOR/MSWindows/types/stdio_types.h"
#include "PosumQOR/Stream.h"
#include "PosumQOR/MSWindows/DescriptorItem.h"
#include "PosumQOR/MSWindows/Posum_File.h"
#include "PosumQOR/MSWindows/StreamData.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	namespace nsPosum
	{
		//--------------------------------------------------------------------------------
		class CPosumStream : public CPosumFile
		{
		public:

			CPosumStream( const char* szPath, int iFlags, va_list vargs ) : CPosumFile( szPath, iFlags, vargs ){};
			CPosumStream( nsWin32::CFile* pOSFile ) : CPosumFile( pOSFile ){};
			virtual ~CPosumStream(){};

			int getchar( void );
			int printf( const char* format, va_list vargs );
			int putc( int c );
			int puts( const char* s );

		private:

			nsWin32::CStreamData m_StreamData;
		};

		//--------------------------------------------------------------------------------
		class CPosumStreamDescriptor : public CDescriptorItem< CPosumStream, ::nsPosum::CStreamInterface >
		{
		public:

			CPosumStreamDescriptor( const char* szPath, int iFlags, va_list vargs );
			CPosumStreamDescriptor( nsWin32::CFile* pOSFile );
			virtual ~CPosumStreamDescriptor(){}
			
			virtual errno_t ClearError();
			virtual FILE* GetFILE( void );
			virtual int EoF( void );
			virtual int Error( void );
			virtual int Flush( void );
			virtual int GetC( void );
			virtual int GetCUnlocked( void );
			virtual int GetPos( fpos_t* pos );
			virtual char* GetS( char* s, int n );
			virtual int FileNumber( void );
			virtual void Lock( void );
			virtual int PrintF( const char* format, va_list vargs );
			virtual int Wprintf( const wchar_t* format, va_list vargs );
			virtual int PutC( int c );
			virtual int PutCUnlocked( int c );
			virtual int PutS( const char* s );
			virtual size_t Read( void* ptr, size_t size, size_t nmemb );
			virtual FILE* Reopen( const char* filename, const char* mode );
			virtual void Rewind( void );
			virtual int ScanF( const char* format, va_list vargs );
			virtual off_t Seek( off_t offset, int whence );
			virtual int SeekO( off_t offset, int whence );
			virtual void SetBuffer( char* buf );
			virtual int SetVBuffer( char* buf, int mode, size_t size );
			virtual int SetPos( const fpos_t* pos );
			virtual long int Tell( void );
			virtual off_t TellO( void );
			virtual int TryLock( void );
			virtual int UnGetC( int c );
			virtual void Unlock( void );
			virtual size_t Write( const void* ptr, size_t size, size_t nmemb );
		};

	}//nsPosum

}//nsWin32

#endif//_WINQL_POSUM_STREAM_H_
