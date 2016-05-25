//Descriptor.cpp

#include "SystemQOR.h"
#include "PosumQOR/Descriptor.h"

#if		( QOR_SYS_OS == QOR_SYS_MSW )
#	include "PosumQOR/MSWindows/Posum_Descriptor_Link.h"
#endif//( QOR_SYS_OS == QOR_SYS_MSW )

//--------------------------------------------------------------------------------
namespace nsPosum
{
	//--------------------------------------------------------------------------------
	CDescriptor::CDescriptor() : m_iDescriptor( -1 ), m_pDescriptorImpl( 0 )
	{
	}

	//--------------------------------------------------------------------------------
	CDescriptor::CDescriptor( int nFD ) : m_iDescriptor( nFD ), m_pDescriptorImpl( 0 )
	{
		nsPlatform::nsPosum::CDescriptorLink Link( nFD );
		m_pDescriptorImpl = Link.Ref();
	}

	//--------------------------------------------------------------------------------
	CDescriptor::CDescriptor( int nFD, CDescriptorInterface* pImpl ): m_iDescriptor( nFD ), m_pDescriptorImpl( pImpl )
	{
	}

	//--------------------------------------------------------------------------------
	CDescriptor::~CDescriptor()
	{
	}

	//--------------------------------------------------------------------------------
	CDescriptor& CDescriptor::operator = ( const CDescriptor& src )
	{
		if( &src != this )
		{
		}
		return *this;
	}
	/*
	//--------------------------------------------------------------------------------
	int CDescriptor::Close( void )
	{
		return 0;
	}
	
	//--------------------------------------------------------------------------------
	//dup
	//--------------------------------------------------------------------------------
	//dup2
	
	//--------------------------------------------------------------------------------
	int CDescriptor::AIOCancel( aiocb* paiocb )
	{
		return 0;
	}

	//--------------------------------------------------------------------------------
	int CDescriptor::AIOError( const aiocb* )
	{
		return 0;
	}

	//--------------------------------------------------------------------------------
	int CDescriptor::AIOFSync( int, aiocb* )
	{
		return 0;
	}

	//--------------------------------------------------------------------------------
	int	CDescriptor::AIORead( aiocb* )
	{
		return 0;
	}

	//--------------------------------------------------------------------------------
	ssize_t CDescriptor::AIOReturn( aiocb* )
	{
		return 0;
	}

	//--------------------------------------------------------------------------------
	int CDescriptor::AIOSuspend( const aiocb* const[], int, const timespec* )
	{
		return 0;
	}

	//--------------------------------------------------------------------------------
	int CDescriptor::AIOWrite( aiocb* )
	{
		return 0;
	}

	//--------------------------------------------------------------------------------
	int	CDescriptor::LIOListIO( int, aiocb* __QCMP_RESTRICT const[], int, sigevent* __QCMP_RESTRICT )
	{
		return 0;
	}
	
	//--------------------------------------------------------------------------------
	int CDescriptor::FSync( void )
	{
		return 0;
	}

	//--------------------------------------------------------------------------------
	int CDescriptor::IsATTY( void )
	{
		return 0;
	}

	//--------------------------------------------------------------------------------
	ssize_t CDescriptor::Read( void* pBuffer, size_t nBytes )
	{
		return 0;
	}

	//--------------------------------------------------------------------------------
	ssize_t CDescriptor::Write( const void* pBuffer, size_t nBytes )
	{
		return 0;
	}
	*/

}//nsPosum
