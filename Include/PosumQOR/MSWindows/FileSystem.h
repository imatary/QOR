//FileSystem.h
//win32 FileSystem class

#ifndef _QSYS_MSWINDOWS_WIN32_FILESYSTEM_H_
#define _QSYS_MSWINDOWS_WIN32_FILESYSTEM_H_

#include <fcntl.h>
#include "WinQL/OSServices/Console.h"
#include "WinQL/CodeServices/String.h"
#include "WinQL/FileSystem/FolderManagement.h"
#include "WinQL/CodeServices/ErrorHandling.h"
#include "PosumQOR/MSWindows/FileData.h"
#include "PosumQOR/MSWindows/DescriptorPool.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	class CFileSystem;

	CFileSystem& FileSystem( void );

	//--------------------------------------------------------------------------------
	class CFileSystem : public CFileHelper, CDirectoryHelper
	{
	public:

		CFileSystem();
		~CFileSystem();

		static nsWin32::CConsoleHelper m_sConsoleHelper;
		static nsWin32::CErrorHelper m_sErrorHelper;
		static nsWin32::CStringHelper m_sStringHelper;
		static nsWin32::CInterlockedHelper m_sInterlockedHelper;

		static char sachLookupTrailBytes[ 256 ];

		//--------------------------------------------------------------------------------
		template< typename t > __QCMP_ALWAYSINLINE char UTF8TrailBytes( t& c )
		{
			return sachLookupTrailBytes[ (unsigned char)c ];
		}

		//--------------------------------------------------------------------------------
		__QCMP_ALWAYSINLINE char MSB( char& c )
		{
			return ( (c) & 0x80 );
		}

		//--------------------------------------------------------------------------------
		__QCMP_ALWAYSINLINE bool UTF8IsIndependent( char& c )// Independent byte has most significant bit set to 0
		{
			return ( MSB( c ) == 0 );
		}

		//--------------------------------------------------------------------------------
		__QCMP_ALWAYSINLINE bool UTF8IsLeadByte( char&c )// Any leadbyte will have the patterns 11000xxx 11100xxx or 11110xxx
		{
			return ( sachLookupTrailBytes[ (unsigned char)c ] != 0 );
		}

		//--------------------------------------------------------------------------------
		__QCMP_ALWAYSINLINE int _isatty( CFileData& FileData )
		{
			return (int)( FileData.GetFlagsFDEV() );
		}

		int GetFMode( void )
		{
			return m_fmode;
		}

		void SetFMode( int fmode )
		{
			m_fmode = fmode;
		}

		int GetComMode( void )
		{
			return m_commode;
		}

		void SetComMode( int cmode )
		{
			m_commode = cmode;
		}

		int GetUMaskVal( void )
		{
			return m_umaskval;
		}

		void SetUMaskVal( int umask )
		{
			m_umaskval = umask;
		}

		CDescriptorPool& DescriptorPool( void )
		{
			return *m_pDescriptorPool;
		}

		void Open ( CFileData& FileData, const char* szFilename, const char* szMode, int iSHFlag );
		int Commit( CFileData& FileData );
		int Duplicate( CFileData& srcFileData, CFileData** ppDupFileData );
		Cmp__int64 Seek( CFileData& FileData, Cmp__int64 i64Pos, int iMethod );
		Cmp__int64 Tell( CFileData& FileData );
		int Read( CFileData& FileData, void* pvInputBuffer, unsigned uCount );
		errno_t ChangeSize( CFileData& FileData, Cmp__int64 i64Size );
		int SetMode( CFileData& FileData, int iMode );
		int Write( CFileData& FileData, const void* buf, unsigned cnt );
		int Close( CFileData& FileData );

	private:

		int InitRead( CFileData& FileData, void*& pvInputBuffer, unsigned& uCount, void*& pRawBuffer );
		void InitReadPipe( CFileData& FileData, char*& pchBuffer, int& iBytesRead, unsigned& uCount );
		void OnReadError( int& iResult, unsigned long& ulDOSResult );
		void PostReadText( CFileData& FileData, int& iOSBytesRead, void*& pRawBuffer, unsigned long& ulDOSResult, int& iBytesRead, int& iResult, void*& pvInputBuffer, unsigned& uInputSize );
		void PostReadTextUTF16LE( CFileData& FileData, int& iOSBytesRead, void*& pRawBuffer, unsigned long& ulDOSResult, int& iBytesRead, int& iResult, void*& pvInputBuffer, unsigned& uInputSize );
		void WriteUConsole( CFileData& FileData, const void*& pvBuffer, char& chTMode, unsigned int& uiCount, int& iLFCount, int& iCharCount, unsigned long& ulDOSResult );
		int WriteText( CFileData& FileData, const void*& pvBuffer, unsigned long& ulDOSResult, unsigned int& uiCount, char& chTMode, int& iLFCount, int& iWritten, int& iCharCount );
		wint_t PutWCh( wchar_t ch );
		template< typename _tchar > errno_t OpenSHelper( CFileData& FileData, const _tchar* tszPath, int iOFlag, int iSHFlag, int iPMode, int bSecure );
		template< typename _tchar > errno_t OpenNoLockS( CFileData& FileData, const _tchar* tszPath, int oflag, int shflag, int pmode, int bSecure );
		template< typename _tchar > bool OnOpenError( CFileData& FileData, unsigned long& dwFileAccess, int& iOFlag, const _tchar* tszPath, unsigned long& dwFileShare, unsigned long& dwFileCreate, SECURITY_ATTRIBUTES& SecurityAttributes, unsigned long& dwFileAttributes, errno_t& Result );
		template< typename _tchar > errno_t PostOpen( CFileData& FileData, int& iOFlag, char& chFileFlags, int& fmode, unsigned long& dwFileAccess, unsigned long& dwFileCreate, unsigned long& dwFileAttribute, const _tchar* tszPath, unsigned long& dwFileShare, SECURITY_ATTRIBUTES& SecurityAttributes );
		char DecodeOpenFlags( CFileData& FileData, int& iOFlag, SECURITY_ATTRIBUTES& SecurityAttributes, int& iFMode, unsigned long& dwFileAccess, int& iSHFlag, unsigned long& dwFileShare, unsigned long& dwFileCreate );
		unsigned long DecodeOpenAttributes( CFileData& FileData, int& iOFlag, unsigned long& dwFileAccess, unsigned long& dwFileShare, int& iPMode, unsigned int& uiOSPlatform );
		bool PostOpenTextMode( CFileData& FileData, int& iOFlag, char& chFileFlags, int& fmode, errno_t& Result, char& tmode, unsigned long& dwFileAccess, unsigned long& dwFileCreate );

		int m_fmode;
		int m_commode;
		int m_umaskval;

		CDescriptorPool* m_pDescriptorPool;
	};

};// nsWin32

#endif//_QSYS_MSWINDOWS_WIN32_FILESYSTEM_H_
