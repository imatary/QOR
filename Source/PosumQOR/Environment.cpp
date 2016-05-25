//Environment.cpp

#include "SystemQOR.h"
#include "PosumQOR/Environment.h"

//--------------------------------------------------------------------------------
namespace nsPosum
{
	__QOR_IMPLEMENT_OCLASS_LUID( CEnvironment );

	//--------------------------------------------------------------------------------
	CEnvironment::CEnvironment( CEnvironment* pImpl )
	{
		m_pEnvironmentImpl = pImpl;
	}

	//--------------------------------------------------------------------------------
	CEnvironment::CEnvironment()
	{
		nsCodeQOR::CClassInstanceFactory* pFactory = ThisModule().ClassReg().GetFactory( ClassID() );
		m_pEnvironmentImpl = reinterpret_cast< CEnvironment* >( pFactory->Instance() );
	}

	//--------------------------------------------------------------------------------
	CEnvironment::~CEnvironment()
	{
	}

	//--------------------------------------------------------------------------------
	CEnvironment& CEnvironment::operator = ( CEnvironment& src )
	{
		if( &src != this )
		{
			*m_pEnvironmentImpl = *src.m_pEnvironmentImpl;
		}
		return *this;
	}

	//--------------------------------------------------------------------------------
	char* CEnvironment::Get( const char* szName )
	{
		return m_pEnvironmentImpl->Get( szName );
	}

	//--------------------------------------------------------------------------------
	int CEnvironment::Put( const char* szEnvString )
	{
		return m_pEnvironmentImpl->Put( szEnvString );
	}

}//nsPosum
