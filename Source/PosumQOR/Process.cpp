//Process.cpp

#include "SystemQOR.h"
#include "PosumQOR/Process.h"

#if		( QOR_SYS_OS == QOR_SYS_MSW )
#	include "PosumQOR/MSWindows/Posum_Descriptor_Link.h"
#endif//( QOR_SYS_OS == QOR_SYS_MSW )

//--------------------------------------------------------------------------------
namespace nsPosum
{
	//--------------------------------------------------------------------------------
	CProcessInterface::CProcessInterface()
	{
	}

	//--------------------------------------------------------------------------------
	CProcessInterface::~CProcessInterface()
	{
	}

	//--------------------------------------------------------------------------------
	CProcessInterface::CProcessInterface( const CProcessInterface& src )
	{
	}

	//--------------------------------------------------------------------------------
	CProcessInterface& CProcessInterface::operator = ( const CProcessInterface& src )
	{
		return *this;
	}

	//--------------------------------------------------------------------------------
	CProcess::CProcess( int pid ) : CProcessInterface()
	{
		nsPlatform::nsPosum::CProcessLink Link( pid );
		m_pProcessImpl = Link.Ref();
	}

	//--------------------------------------------------------------------------------
	CProcess::~CProcess()
	{
	}

};//namespace nsPosum
