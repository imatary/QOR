//File.cpp

#include "SystemQOR.h"
#include "PosumQOR/File.h"

#if		( QOR_SYS_OS == QOR_SYS_MSW )
#	include "PosumQOR/MSWindows/Posum_Descriptor_Link.h"
#endif//( QOR_SYS_OS == QOR_SYS_MSW )

//--------------------------------------------------------------------------------
namespace nsPosum
{
	//--------------------------------------------------------------------------------
	CFileInterface::CFileInterface()
	{
	}

	//--------------------------------------------------------------------------------
	CFileInterface::CFileInterface( const CFileInterface& src )
	{
	}

	//--------------------------------------------------------------------------------
	CFileInterface& CFileInterface::operator=( const CFileInterface& src )
	{
		return *this;
	}

	//--------------------------------------------------------------------------------
	CFileInterface::~CFileInterface()
	{
	}

	//--------------------------------------------------------------------------------
	CFile::CFile() : CFileInterface()
	{
	}

	//--------------------------------------------------------------------------------
	CFile::CFile( int nFD ) : CFileInterface()
	{		
		nsPlatform::nsPosum::CFileLink Link( nFD );
		m_pDescriptorImpl = Link.Ref();
		m_pFileImpl = Link.Ref();
	}

	//--------------------------------------------------------------------------------
	CFile::CFile( const char* szPath, int iFlags, va_list vargs )
	{
		nsPlatform::nsPosum::CFileLink Link( szPath, iFlags, vargs );
		m_pDescriptorImpl = Link.Ref();
		m_pFileImpl = Link.Ref();
	}

	//--------------------------------------------------------------------------------
	CFile::CFile( const CFile& src )
	{
		nsPlatform::nsPosum::CFileLink Link( src.m_iDescriptor );
		m_pDescriptorImpl = Link.Ref();
		m_pFileImpl = Link.Ref();
	}

	//--------------------------------------------------------------------------------
	CFile::~CFile()
	{
	}

	//--------------------------------------------------------------------------------
	int CFile::Control( int cmd, va_list vargs )
	{
		return m_pFileImpl->Control( cmd, vargs );
	}


};//namespace nsPosum
