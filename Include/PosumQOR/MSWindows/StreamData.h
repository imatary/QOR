//Stream.h

//WinQL File Stream Data object

#ifndef _WINQL_STREAM_H_
#define _WINQL_STREAM_H_

#pragma __QCMP_OPTIMIZEINCLUDE

#include "SystemQOR/MSWindows/types/stdio_types.h"
#include "WinQL/WinQL.h"
#include "WinQL/FileSystem/FileManagement.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class CStreamData
	{
	public:

		//Read/Write mode
		__QCMP_STATIC_CONSTANT( unsigned char, IOREAD		= 0x0001 );// line feed
		__QCMP_STATIC_CONSTANT( unsigned char, IOWRT		= 0x0002 );// carriage return

		//Buffer sizes
		__QCMP_STATIC_CONSTANT( unsigned int, _SMALL_BUFSIZ		= 512 );
		__QCMP_STATIC_CONSTANT( unsigned int, _INTERNAL_BUFSIZ	= 4096 );

		//Buffer flags
		__QCMP_STATIC_CONSTANT( unsigned short, m_scusIONoBuffering		= 0x0004 );//_IONBF
/*#define _IOMYBUF        0x0008
#define _IOEOF          0x0010
#define _IOERR          0x0020
#define _IOSTRG         0x0040
#define _IORW           0x0080*/
		__QCMP_STATIC_CONSTANT( unsigned short, _IOYOURBUF				= 0x0100 );
		__QCMP_STATIC_CONSTANT( unsigned short, _IOSETVBUF				= 0x0400 );
		__QCMP_STATIC_CONSTANT( unsigned short, _IOFEOF					= 0x0800 );
		__QCMP_STATIC_CONSTANT( unsigned short, _IOFLRTN				= 0x1000 );
		__QCMP_STATIC_CONSTANT( unsigned short, _IOCTRLZ				= 0x2000 );
		__QCMP_STATIC_CONSTANT( unsigned short, _IOCOMMIT				= 0x4000 );
		__QCMP_STATIC_CONSTANT( unsigned short, _IOLOCKED				= 0x8000 );

		__QCMP_STATIC_CONSTANT( unsigned short, _S_IFMT					= 0xF000 );// file type mask
		__QCMP_STATIC_CONSTANT( unsigned short, _S_IFDIR				= 0x4000 );//directory
		__QCMP_STATIC_CONSTANT( unsigned short, _S_IFCHR				= 0x2000 );//character special
		__QCMP_STATIC_CONSTANT( unsigned short, _S_IFIFO				= 0x1000 );//pipe
		__QCMP_STATIC_CONSTANT( unsigned short, _S_IFREG				= 0x8000 );//regular
		__QCMP_STATIC_CONSTANT( unsigned short, _S_IREAD				= 0x0100 );//read permission, owner
		__QCMP_STATIC_CONSTANT( unsigned short, _S_IWRITE				= 0x0080 );//write permission, owner
		__QCMP_STATIC_CONSTANT( unsigned short, _S_IEXEC				= 0x0040 );//execute/search permission, owner

		CStreamData()
		{
		}

		~CStreamData()
		{
		}

		char* GetPointer( void )
		{
			return m_Buffer._ptr;
		}

		void ResetPointer( void )
		{
			m_Buffer._ptr = 0;
		}

		int GetCount( void )
		{
			return m_Buffer._cnt;
		}

		void SetCount( int iCount )
		{
			m_Buffer._cnt = iCount;
		}

		char* GetBase( void )
		{
			return m_Buffer._base;
		}

		void ResetBase( void )
		{
			m_Buffer._base = 0;
		}

		int GetFlags( void )
		{
			return m_Buffer._flag;
		}

		void SetFlags( int iFlags )
		{
			m_Buffer._flag = iFlags;
		}

		bool GetFlagRead( void )
		{
			return ( m_Buffer._flag & IOREAD ) ? true : false;
		}

		bool GetFlagWrite( void )
		{
			return ( m_Buffer._flag & IOWRT ) ? true : false;
		}

		bool GetFlagNoBuffering( void )
		{
			return ( m_Buffer._flag & m_scusIONoBuffering ) ? true : false;
		}

		bool GetFlagMyBuffering( void )
		{
			return ( m_Buffer._flag & _IOMYBUF ) ? true : false;
		}

		bool GetFlagEOF( void )
		{
			return ( m_Buffer._flag & _IOEOF ) ? true : false;
		}

		bool GetFlagErr( void )
		{
			return ( m_Buffer._flag & _IOERR ) ? true : false;
		}

		bool GetFlagString( void )
		{
			return ( m_Buffer._flag & _IOSTRG ) ? true : false;
		}

		bool GetFlagRW( void )
		{
			return ( m_Buffer._flag & _IORW ) ? true : false;
		}

		bool GetFlagYourBuffer( void )
		{
			return ( m_Buffer._flag & _IOYOURBUF ) ? true : false;
		}

		bool GetFlagSetVBuffer( void )
		{
			return ( m_Buffer._flag & _IOSETVBUF ) ? true : false;
		}

		bool GetFlagFEOF( void )
		{
			return ( m_Buffer._flag & _IOFEOF ) ? true : false;
		}

		bool GetFlagFLRTN( void )
		{
			return ( m_Buffer._flag & _IOFLRTN ) ? true : false;
		}

		bool GetFlagCtrlZ( void )
		{
			return ( m_Buffer._flag & _IOCTRLZ ) ? true : false;
		}

		bool GetFlagCommit( void )
		{
			return ( m_Buffer._flag & _IOCOMMIT ) ? true : false;
		}

		bool GetFlagLocked( void )
		{
			return ( m_Buffer._flag & _IOLOCKED ) ? true : false;
		}

		int GetFile( void )
		{
			return m_Buffer._file;
		}

		int GetCharBuffer( void )
		{
			return m_Buffer._charbuf;
		}

		int GetBufferSize( void )
		{
			return m_Buffer._bufsiz;
		}

		char* GetTempFileName( void )
		{
			return m_Buffer._tmpfname;
		}

		void SetTempFileName( char* szTmpFileName )
		{
			m_Buffer._tmpfname = szTmpFileName;
		}

		int GetOffset( void )
		{
			return m_Buffer._ptr - m_Buffer._base;
		}

		bool GetUTF8Translations( void )
		{
			return m_bUTF8Translations;
		}

		void SetUTF8Translations( bool bTranslations )
		{
			m_bUTF8Translations = bTranslations;
		}

		//--------------------------------------------------------------------------------
		bool UseBigBuffer( void )
		{
			return( ( m_Buffer._flag & ( _IOMYBUF | _IOYOURBUF ) ) ? true : false );
		}

	private:

		_iobuf m_Buffer;
		bool m_bUTF8Translations;	// Buffer contains translations other than CRLF
	};


}//nsWin32

#endif//_WINQL_STREAM_H_
