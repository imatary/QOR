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
		int CPosumStreamDescriptor::GetC( void )
		{
			return m_pObject->getchar();
		}

		//--------------------------------------------------------------------------------
		int CPosumStreamDescriptor::PrintF( const char* format, va_list vargs )
		{
			return m_pObject->printf( format, vargs );
		}

		//--------------------------------------------------------------------------------
		int CPosumStreamDescriptor::PutC( int c )
		{
		    return m_pObject->putc( c );
		}

		//--------------------------------------------------------------------------------
		int CPosumStreamDescriptor::PutS( const char* s )
		{
		    return m_pObject->puts( s );
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
