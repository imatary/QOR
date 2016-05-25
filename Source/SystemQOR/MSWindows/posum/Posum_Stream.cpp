//Posum_Stream.cpp
//Windows specific implementation of the Posum CStream class

#include "SystemQOR.h"
#include "PosumQOR/MSWindows/Posum_Stream.h"
#include "WinQL/FileSystem/Formatter.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	namespace nsPosum
	{
		//--------------------------------------------------------------------------------
		CPosumStreamDescriptor::CPosumStreamDescriptor( const char* szPath, int iFlags, va_list vargs )
		{
			m_pObject = new nsWin32::nsPosum::CPosumStream( szPath, iFlags, vargs );
		}

		//--------------------------------------------------------------------------------
		CPosumStreamDescriptor::CPosumStreamDescriptor( nsWin32::CFile* pOSFile )
		{
			m_pObject = new nsWin32::nsPosum::CPosumStream( pOSFile );
		}

		//--------------------------------------------------------------------------------
		errno_t CPosumStreamDescriptor::ClearError()
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		FILE* CPosumStreamDescriptor::GetFILE( void )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		int CPosumStreamDescriptor::EoF( void )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		int CPosumStreamDescriptor::Error( void )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		int CPosumStreamDescriptor::Flush( void )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		int CPosumStreamDescriptor::GetC( void )
		{
			return m_pObject->getchar();
		}

		//--------------------------------------------------------------------------------
		int CPosumStreamDescriptor::GetCUnlocked( void )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		int CPosumStreamDescriptor::GetPos( fpos_t* pos )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		char* CPosumStreamDescriptor::GetS( char* s, int n )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		int CPosumStreamDescriptor::FileNumber( void )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		void CPosumStreamDescriptor::Lock( void )
		{
		}

		//--------------------------------------------------------------------------------
		int CPosumStreamDescriptor::PrintF( const char* format, va_list vargs )
		{
			return m_pObject->printf( format, vargs );
		}

		//--------------------------------------------------------------------------------
		int CPosumStreamDescriptor::Wprintf( const wchar_t* format, va_list vargs )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		int CPosumStreamDescriptor::PutC( int c )
		{
		    return m_pObject->putc( c );
		}

		//--------------------------------------------------------------------------------
		int CPosumStreamDescriptor::PutCUnlocked( int c )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		int CPosumStreamDescriptor::PutS( const char* s )
		{
		    return m_pObject->puts( s );
		}

		//--------------------------------------------------------------------------------
		size_t CPosumStreamDescriptor::Read( void* ptr, size_t size, size_t nmemb )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		FILE* CPosumStreamDescriptor::Reopen( const char* filename, const char* mode )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		void CPosumStreamDescriptor::Rewind( void )
		{
		}

		//--------------------------------------------------------------------------------
		int CPosumStreamDescriptor::ScanF( const char* format, va_list vargs )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		off_t CPosumStreamDescriptor::Seek( off_t offset, int whence )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		int CPosumStreamDescriptor::SeekO( off_t offset, int whence )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		void CPosumStreamDescriptor::SetBuffer( char* buf )
		{

		}

		//--------------------------------------------------------------------------------
		int CPosumStreamDescriptor::SetVBuffer( char* buf, int mode, size_t size )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		int CPosumStreamDescriptor::SetPos( const fpos_t* pos )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		long int CPosumStreamDescriptor::Tell( void )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		off_t CPosumStreamDescriptor::TellO( void )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		int CPosumStreamDescriptor::TryLock( void )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		int CPosumStreamDescriptor::UnGetC( int c )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		void CPosumStreamDescriptor::Unlock( void )
		{
			
		}

		//--------------------------------------------------------------------------------
		size_t CPosumStreamDescriptor::Write( const void* ptr, size_t size, size_t nmemb )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		int CPosumStream::getchar( void )
		{
			nsWin32::CCRTFile* pCRTFile = dynamic_cast< nsWin32::CCRTFile* >( m_FileData.GetOSFile() );
			if( pCRTFile )
			{
				return pCRTFile->GetC();
			}
			return 0;
		}

		//--------------------------------------------------------------------------------
		int CPosumStream::printf( const char* format, va_list vargs )
		{
			nsWin32::CCRTFile* pCRTFile= dynamic_cast< nsWin32::CCRTFile* >( m_FileData.GetOSFile() );
			if( pCRTFile )
			{
				return pCRTFile->PrintF( format, vargs );
			}
			return 0;
		}

		//--------------------------------------------------------------------------------
		int CPosumStream::putc( int c )
		{
			nsWin32::CCRTFile* pCRTFile= dynamic_cast< nsWin32::CCRTFile* >( m_FileData.GetOSFile() );
			if( pCRTFile )
			{
				return pCRTFile->PutC( c );
			}
			return 0;
		}

		//--------------------------------------------------------------------------------
		int CPosumStream::puts( const char* s )
		{
			nsWin32::CCRTFile* pCRTFile= dynamic_cast< nsWin32::CCRTFile* >( m_FileData.GetOSFile() );
			if( pCRTFile )
			{
				return pCRTFile->PutS( s );
			}
			return 0;
		}

	};//nsPosum

};//nsWin32
