//Posum_File.cpp
//Windows specific implementation of the Posum CFileBase class

#include "SystemQOR.h"
#include "PosumQOR/MSWindows/Posum_File.h"
#include "WinQL/CodeServices/Handle.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	namespace nsPosum
	{
		//--------------------------------------------------------------------------------
		CPosumFileDescriptor::CPosumFileDescriptor( const char* szPath, int iFlags, va_list vargs )
		{
			m_pObject = new nsWin32::nsPosum::CPosumFile( szPath, iFlags, vargs );
		}

		//--------------------------------------------------------------------------------
		CPosumFileDescriptor::CPosumFileDescriptor( nsWin32::CFile* pOSFile )
		{
			m_pObject = new nsWin32::nsPosum::CPosumFile( pOSFile );
		}

		//--------------------------------------------------------------------------------
		CPosumFileDescriptor::~CPosumFileDescriptor()
		{
			delete m_pObject;
		}

		//--------------------------------------------------------------------------------
		int CPosumFileDescriptor::Control( int cmd, va_list vargs )
		{
			return 0;//m_pObject->fcntl( cmd, vargs );
		}


		//--------------------------------------------------------------------------------
		CPosumFile::CPosumFile( const char* szPath, int iFlags, va_list vargs ) : CPosumDescriptor()
		{
			//
		}

		//--------------------------------------------------------------------------------
		CPosumFile::CPosumFile( nsWin32::CFile* pOSFile )
		{
			m_FileData.SetOSFile( pOSFile );
		}

		//--------------------------------------------------------------------------------
		CPosumFile::~CPosumFile()
		{
			m_pFileSystem->Close( m_FileData );
		}

		//--------------------------------------------------------------------------------
		int CPosumFile::fadvise( off_t offset, off_t len, int advice )
		{
			int iResult = -1;
			return iResult;
		}

	};//namespace nsPosum

};//namespace nsWin32
