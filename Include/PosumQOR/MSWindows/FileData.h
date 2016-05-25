//File.h

//WinQL File Data object

#ifndef _WINQL_FILE_H_
#define _WINQL_FILE_H_

#pragma __QCMP_OPTIMIZEINCLUDE

#include "WinQL/WinQL.h"
#include "WinQL/FileSystem/FileManagement.h"
#include "StreamData.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class CFileData
	{
	public:

		//--------------------------------------------------------------------------------
		union FilePos
		{
			Cmp__int64 bigint;
			struct 
			{
				unsigned long lowerhalf;
				long upperhalf;
			} twoints;
		};


		//Escape characters for inline processing
		__QCMP_STATIC_CONSTANT( unsigned char, LF				= 10 );// line feed
		__QCMP_STATIC_CONSTANT( unsigned char, CR				= 13 );// carriage return
		__QCMP_STATIC_CONSTANT( unsigned char, CTRLZ			= 26 );// ctrl-z means eof for text

		//Flags mapped into m_ucFlags
		__QCMP_STATIC_CONSTANT( unsigned char, FOPEN			= 0x01 );// file void* open
		__QCMP_STATIC_CONSTANT( unsigned char, FEOFLAG			= 0x02 );// end of file has been encountered
		__QCMP_STATIC_CONSTANT( unsigned char, FCRLF			= 0x04 );// CR-LF across read buffer (in text mode)
		__QCMP_STATIC_CONSTANT( unsigned char, FPIPE			= 0x08 );// file void* refers to a pipe
		__QCMP_STATIC_CONSTANT( unsigned char, FNOINHERIT		= 0x10 );// file void* opened _O_NOINHERIT
		__QCMP_STATIC_CONSTANT( unsigned char, FAPPEND			= 0x20 );// file void* opened O_APPEND
		__QCMP_STATIC_CONSTANT( unsigned char, FDEV				= 0x40 );// file void* refers to device
		__QCMP_STATIC_CONSTANT( unsigned char, FTEXT			= 0x80 );// file void* is in text mode

		//Text Mode
		__QCMP_STATIC_CONSTANT( unsigned char, __IOINFO_TM_ANSI		= 0 );// Regular Text
		__QCMP_STATIC_CONSTANT( unsigned char, __IOINFO_TM_UTF8		= 1 );// UTF8 Encoded
		__QCMP_STATIC_CONSTANT( unsigned char, __IOINFO_TM_UTF16LE	= 2 );// UTF16 Little Endian Encoded

		__QCMP_STATIC_CONSTANT( unsigned int, TEXT					= 0x4000 );// file mode is text (translated)
		__QCMP_STATIC_CONSTANT( unsigned int, BINARY				= 0x8000  );// file mode is binary (untranslated)
		__QCMP_STATIC_CONSTANT( unsigned int, WTEXT					= 0x10000 );// file mode is UTF16 (translated)
		__QCMP_STATIC_CONSTANT( unsigned int, U16TEXT				= 0x20000 );// file mode is UTF16 no BOM (translated)
		__QCMP_STATIC_CONSTANT( unsigned int, U8TEXT				= 0x40000 );// file mode is UTF8  no BOM (translated)

		__QCMP_STATIC_CONSTANT( int, BUF_SIZE						= 1025 );// size of LF translation buffer

		//Sharing modes
		__QCMP_STATIC_CONSTANT( int, _SH_DENYRW						= 0x10 );// deny read/write mode
		__QCMP_STATIC_CONSTANT( int, _SH_DENYWR						= 0x20 );// deny write mode
		__QCMP_STATIC_CONSTANT( int, _SH_DENYRD						= 0x30 );// deny read mode
		__QCMP_STATIC_CONSTANT( int, _SH_DENYNO						= 0x40 );// deny none mode
		__QCMP_STATIC_CONSTANT( int, _SH_SECURE						= 0x80 );// secure mode

		//BOM modes
		__QCMP_STATIC_CONSTANT( unsigned short, UTF16LE_BOM			= 0xFEFF );      // UTF16 Little Endian Byte Order Mark
		__QCMP_STATIC_CONSTANT( unsigned short, UTF16BE_BOM			= 0xFFFE );      // UTF16 Big Endian Byte Order Mark
		__QCMP_STATIC_CONSTANT( unsigned short, BOM_MASK			= 0xFFFF );      // Mask for testing Byte Order Mark
		__QCMP_STATIC_CONSTANT( unsigned int,   UTF8_BOM			= 0xBFBBEF );    // UTF8 Byte Order Mark
		__QCMP_STATIC_CONSTANT( int, UTF16_BOMLEN					= 2 );           // No of Bytes in a UTF16 BOM
		__QCMP_STATIC_CONSTANT( int, UTF8_BOMLEN					= 3 );           // No of Bytes in a UTF8 BOM

		CFileData(){}
		~CFileData(){}

		CFileData( const CFileData& src )
		{
			m_pOSFileObject = src.m_pOSFileObject;
			m_ucFlags = src.m_ucFlags;
			m_ucTextMode = src.m_ucTextMode;
			memcpy( m_achPipeBuffer, src.m_achPipeBuffer, 3 );
			m_Buffering = src.m_Buffering;
		}

		void ResetFlags( void )
		{
			m_ucFlags = 0;
		}

		bool GetFlagsOpen( void )
		{
			return ( m_ucFlags & FOPEN ) ? true : false;
		}

		void SetFlagsOpen( bool bOpen )
		{
			bOpen ? ( m_ucFlags |= FOPEN ) : ( m_ucFlags &= ~FOPEN );
		}

		bool GetFlagsEOF( void )
		{
			return ( m_ucFlags & FEOFLAG ) ? true : false;
		}

		void SetFlagsEOF( bool bEOF )
		{
			bEOF ? ( m_ucFlags |= FEOFLAG ) : ( m_ucFlags &= ~FEOFLAG );
		}

		bool GetFlagsCRLF( void )
		{
			return ( m_ucFlags & FCRLF ) ? true : false;
		}

		void SetFlagsCRLF( bool bCRLF )
		{
			bCRLF ? ( m_ucFlags |= FCRLF ) : ( m_ucFlags &= ~FCRLF );
		}

		bool GetFlagsFPIPE( void )
		{
			return ( m_ucFlags & FPIPE ) ? true : false;
		}

		void SetFlagsFPIPE( bool bFPIPE )
		{
			bFPIPE ? ( m_ucFlags |= FPIPE ) : ( m_ucFlags &= ~FPIPE );
		}

		bool GetFlagsFNOINHERIT( void )
		{
			return ( m_ucFlags & FNOINHERIT ) ? true : false;
		}

		void SetFlagsFNOINHERIT( bool bFNOINHERIT )
		{
			bFNOINHERIT ? ( m_ucFlags |= FNOINHERIT ) : ( m_ucFlags &= ~FNOINHERIT );
		}

		bool GetFlagsFAPPEND( void )
		{
			return ( m_ucFlags & FAPPEND ) ? true : false;
		}

		void SetFlagsFAPPEND( bool bFAPPEND )
		{
			bFAPPEND ? ( m_ucFlags |= FAPPEND ) : ( m_ucFlags &= ~FAPPEND );
		}

		bool GetFlagsFDEV( void )
		{
			return ( m_ucFlags & FDEV ) ? true : false;
		}

		void SetFlagsFDEV( bool bFDEV )
		{
			bFDEV ? ( m_ucFlags |= FDEV ) : ( m_ucFlags &= ~FDEV );
		}

		bool GetFlagsFTEXT( void )
		{
			return ( m_ucFlags & FTEXT ) ? true : false;
		}

		void SetFlagsFTEXT( bool bFTEXT )
		{
			bFTEXT ? ( m_ucFlags |= FTEXT ) : ( m_ucFlags &= ~FTEXT );
		}

		void Lock( void )
		{
			m_CC.Enter();
		}

		void Unlock( void )
		{
			m_CC.Leave();
		}

		nsWin32::CFile* GetOSFile( void )
		{
			return m_pOSFileObject;
		}

		void SetOSFile( nsWin32::CFile* pFile )
		{
			m_pOSFileObject = pFile;
		}

		unsigned char GetTextMode( void )
		{
			return m_ucTextMode;
		}

		void SetTextMode( unsigned char ucTextMode )
		{
			m_ucTextMode = ucTextMode;
		}

		bool GetOpenedAsUnicode( void )
		{
			return m_ucTextMode & 0x1 ? true : false;
		}

		void SetOpenedAsUnicode( bool bUnicode )
		{
			m_ucTextMode &= ( 0xFE | ( bUnicode ? 0x1 : 0x0 ) );
		}

		unsigned char& GetPipeBuffer( void )
		{
			return m_achPipeBuffer[ 0 ];
		}

		unsigned char* GetUnicodePipeBuffer( void )
		{
			return &m_achPipeBuffer[ 1 ];
		}

		CStreamData& Buffering( void )
		{
			return m_Buffering;
		}

		Cmp__int64 GetStartPos( void )
		{
			return m_i64StartPos;
		}

		void SetStartPos( Cmp__int64 i64Pos )
		{
			m_i64StartPos = i64Pos;
		}

	protected:

		unsigned char m_ucFlags;
		unsigned char m_ucTextMode;
		unsigned char m_achPipeBuffer[ 3 ];	// one char buffer for files opened on pipes plus 2 more peak ahead chars for UNICODE mode
		nsWin32::CFile* m_pOSFileObject;
		nsWin32::CCriticalSection m_CC;
		CStreamData m_Buffering;
		Cmp__int64 m_i64StartPos;		// File position that matches buffer start
	};

};// nsWin32

#endif//_WINQL_FILE_H_
