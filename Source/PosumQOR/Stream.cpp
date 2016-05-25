//Stream.cpp

#include "SystemQOR.h"
#include "PosumQOR/Stream.h"

#if		( QOR_SYS_OS == QOR_SYS_MSW )
#	include "PosumQOR/MSWindows/Posum_Descriptor_Link.h"
#endif//( QOR_SYS_OS == QOR_SYS_MSW )

//--------------------------------------------------------------------------------
namespace nsPosum
{
	//--------------------------------------------------------------------------------
	CStreamInterface::CStreamInterface()
	{
	}

	//--------------------------------------------------------------------------------
	CStreamInterface::CStreamInterface( const CStreamInterface& src )
	{
	}

	//--------------------------------------------------------------------------------
	CStreamInterface& CStreamInterface::operator=( const CStreamInterface& src )
	{
		return *this;
	}

	//--------------------------------------------------------------------------------
	CStreamInterface::~CStreamInterface()
	{
	}

	//--------------------------------------------------------------------------------
	CStream::CStream() : CStreamInterface()
	{
		m_pDescriptorImpl = 0;
		m_pStreamImpl = 0;
	}

	//--------------------------------------------------------------------------------
	CStream::CStream( int nFD ) : CStreamInterface()
	{		
		nsPlatform::nsPosum::CStreamLink Link( nFD );
		m_pDescriptorImpl = Link.Ref();
		m_pStreamImpl = Link.Ref();
	}

	//--------------------------------------------------------------------------------
	CStream::CStream( int nFD, const char* mode )
	{
	}

	//--------------------------------------------------------------------------------
	CStream::CStream( const char* filename, const char* mode )
	{
	}

	//--------------------------------------------------------------------------------
	CStream::CStream( void* buf, size_t size, const char* szMode )
	{
	}

	//--------------------------------------------------------------------------------
	CStream::CStream( FILE* pFILE )
	{
		m_pDescriptorImpl = 0;
		m_pStreamImpl = 0;
		if( pFILE )
		{
			nsPlatform::nsPosum::CStreamLink Link( pFILE->_file );
			m_pDescriptorImpl = Link.Ref();
			m_pStreamImpl = Link.Ref();
		}
	}

	//--------------------------------------------------------------------------------
	CStream::~CStream()
	{
	}

	//--------------------------------------------------------------------------------
	/*
	CStream& CStream::operator = ( const CStream& src )
	{
		if( &src != this )
		{
		}
		return *this;
	}
	*/
	/*
	//--------------------------------------------------------------------------------
	errno_t CStream::ClearError()
	{
		errno_t Result = 0;
		if( m_pStreamImpl )
		{
			Result = m_pStreamImpl->ClearError();
		}
		return Result;
	}

	//--------------------------------------------------------------------------------
	FILE* CStream::GetFILE( void )
	{
		FILE* pResult = 0;
		if( m_pStreamImpl )
		{
			pResult = m_pStreamImpl->GetFILE();
		}
		return pResult;
	}

	//--------------------------------------------------------------------------------
	int CStream::EoF( void )
	{
		int iResult = 0;
		if( m_pStreamImpl )
		{
			iResult = m_pStreamImpl->EoF();
		}
		return iResult;
	}

	//--------------------------------------------------------------------------------
	int CStream::Error( void )
	{
		int iResult = 0;
		if( m_pStreamImpl )
		{
			iResult = m_pStreamImpl->Error();
		}
		return iResult;
	}

	//--------------------------------------------------------------------------------
	int CStream::Flush( void )
	{
		int iResult = 0;
		if( m_pStreamImpl )
		{
			iResult = m_pStreamImpl->Flush();
		}
		return iResult;
	}
	*/
	//--------------------------------------------------------------------------------
	int CStream::GetC( void )
	{
		int iResult = 0;
		if( m_pStreamImpl )
		{
			iResult = m_pStreamImpl->GetC();
		}
		return iResult;
	}
	/*
	//--------------------------------------------------------------------------------
	int CStream::GetCUnlocked( void )
	{
		int iResult = 0;
		if( m_pStreamImpl )
		{
			iResult = m_pStreamImpl->GetCUnlocked();
		}
		return iResult;
	}

	//--------------------------------------------------------------------------------
	int CStream::GetPos( fpos_t* pos )
	{
		int iResult = 0;
		if( m_pStreamImpl )
		{
			iResult = m_pStreamImpl->GetPos( pos );
		}
		return iResult;
	}

	//--------------------------------------------------------------------------------
	char* CStream::GetS( char* s, int n )
	{
		char* pResult = 0;
		if( m_pStreamImpl )
		{
			pResult = m_pStreamImpl->GetS( s, n );
		}
		return pResult;
	}

	//--------------------------------------------------------------------------------
	int CStream::FileNumber( void )
	{
		int iResult = -1;
		if( m_pStreamImpl )
		{
			iResult = m_pStreamImpl->FileNumber();
		}
		return iResult;
	}

	//--------------------------------------------------------------------------------
	void CStream::Lock( void )
	{
		if( m_pStreamImpl )
		{
			m_pStreamImpl->Lock();
		}
	}
	*/
	//--------------------------------------------------------------------------------
	int CStream::PrintF( const char* format, va_list vargs )
	{
		int iResult = 0;
		if( m_pStreamImpl )
		{
			iResult = m_pStreamImpl->PrintF( format, vargs );
		}
		return iResult;
	}
	/*
	//--------------------------------------------------------------------------------
	int CStream::Wprintf( const wchar_t* format, va_list vargs )
	{
		int iResult = 0;
		if( m_pStreamImpl )
		{
			iResult = m_pStreamImpl->Wprintf( format, vargs );
		}
		return iResult;
	}
	*/
	//--------------------------------------------------------------------------------
	int CStream::PutC( int c )
	{
		int iResult = 0;
		if( m_pStreamImpl )
		{
			iResult = m_pStreamImpl->PutC( c );
		}
		return iResult;
	}
	/*
	//--------------------------------------------------------------------------------
	int CStream::PutCUnlocked( int c )
	{
		int iResult = 0;
		if( m_pStreamImpl )
		{
			iResult = m_pStreamImpl->PutCUnlocked( c );
		}
		return iResult;
	}
	*/
	//--------------------------------------------------------------------------------
	int CStream::PutS( const char* s )
	{
		int iResult = 0;
		if( m_pStreamImpl )
		{
			iResult = m_pStreamImpl->PutS( s );
		}
		return iResult;
	}
	/*
	//--------------------------------------------------------------------------------
	size_t CStream::Read( void* ptr, size_t size, size_t nmemb )
	{
		size_t Result = 0;
		if( m_pStreamImpl )
		{
			Result = m_pStreamImpl->Read( ptr, size, nmemb );
		}
		return Result;
	}

	//--------------------------------------------------------------------------------
	FILE* CStream::Reopen( const char* filename, const char* mode )
	{
		FILE* pResult = 0;
		if( m_pStreamImpl )
		{
			pResult = m_pStreamImpl->Reopen( filename, mode );
		}
		return pResult;
	}

	//--------------------------------------------------------------------------------
	void CStream::Rewind( void )
	{
		if( m_pStreamImpl )
		{
			m_pStreamImpl->Rewind();
		}
	}

	//--------------------------------------------------------------------------------
	int CStream::ScanF( const char* format, va_list vargs )
	{
		int iResult = 0;
		if( m_pStreamImpl )
		{
			iResult = m_pStreamImpl->ScanF( format, vargs );
		}
		return iResult;
	}

	//--------------------------------------------------------------------------------
	off_t CStream::Seek( off_t offset, int whence )
	{
		off_t iResult = 0;
		if( m_pStreamImpl )
		{
			iResult = m_pStreamImpl->Seek( offset, whence );
		}
		return iResult;
	}

	//--------------------------------------------------------------------------------
	int CStream::SeekO( off_t offset, int whence )
	{
		int iResult = 0;
		if( m_pStreamImpl )
		{
			iResult = m_pStreamImpl->SeekO( offset, whence );
		}
		return iResult;
	}

	//--------------------------------------------------------------------------------
	void CStream::SetBuffer( char* buf )
	{
		if( m_pStreamImpl )
		{
			m_pStreamImpl->SetBuffer( buf );
		}
	}

	//--------------------------------------------------------------------------------
	int CStream::SetVBuffer( char* buf, int mode, size_t size )
	{
		int iResult = 0;
		if( m_pStreamImpl )
		{
			iResult = m_pStreamImpl->SetVBuffer( buf, mode, size );
		}
		return iResult;
	}

	//--------------------------------------------------------------------------------
	int CStream::SetPos( const fpos_t* pos )
	{
		int iResult = 0;
		if( m_pStreamImpl )
		{
			iResult = m_pStreamImpl->SetPos( pos );
		}
		return iResult;
	}

	//--------------------------------------------------------------------------------
	long int CStream::Tell( void )
	{
		long int liResult = 0;
		if( m_pStreamImpl )
		{
			liResult = m_pStreamImpl->Tell();
		}
		return liResult;
	}

	//--------------------------------------------------------------------------------
	off_t CStream::TellO( void )
	{
		off_t Result = 0;
		if( m_pStreamImpl )
		{
			Result = m_pStreamImpl->TellO();
		}
		return Result;
	}

	//--------------------------------------------------------------------------------
	int CStream::TryLock( void )
	{
		int iResult = 0;
		if( m_pStreamImpl )
		{
			iResult = m_pStreamImpl->TryLock();
		}
		return iResult;
	}

	//--------------------------------------------------------------------------------
	int CStream::UnGetC( int c )
	{
		int iResult = 0;
		if( m_pStreamImpl )
		{
			iResult = m_pStreamImpl->UnGetC( c );
		}
		return iResult;
	}

	//--------------------------------------------------------------------------------
	void CStream::Unlock( void )
	{
		if( m_pStreamImpl )
		{
			m_pStreamImpl->Unlock();
		}
	}

	//--------------------------------------------------------------------------------
	size_t CStream::Write( const void* ptr, size_t size, size_t nmemb )
	{
		size_t Result = 0;
		if( m_pStreamImpl )
		{
			Result = m_pStreamImpl->Write( ptr, size, nmemb );
		}
		return Result;
	}
	*/
};//namespace nsPosum
