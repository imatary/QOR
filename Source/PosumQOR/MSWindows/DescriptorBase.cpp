//DescriptorBase.cpp

#include "SystemQOR.h"
#include "WinQL/CodeServices/ErrorSystem/Error.h"
#include "PosumQOR/MSWindows/DescriptorBase.h"
#include "PosumQOR/MSWindows/DescriptorPool.h"
#include "PosumQOR/MSWindows/DescriptorItemBase.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	CDescriptor::CDescriptor()
	{
		m_i = -1;
		m_pPool = nsCodeQOR::CTSingleton< CDescriptorPool >::Instance();
		m_pItem = 0;
	}

	//--------------------------------------------------------------------------------
	CDescriptor::CDescriptor( int i )
	{
		m_i = i;
		m_pPool = nsCodeQOR::CTSingleton< CDescriptorPool >::Instance();
		if( !AcquireItem() )
		{
			m_i = -1;
		}
	}

	//--------------------------------------------------------------------------------
	CDescriptor::~CDescriptor()
	{
	}

	//--------------------------------------------------------------------------------
	CDescriptor::operator int( void )
	{
		return m_i;
	}

	//--------------------------------------------------------------------------------
	bool CDescriptor::AcquireItem( void )
	{
		if( m_pItem == 0 )
		{
			if( m_pPool == 0 )
			{
				m_pPool = nsCodeQOR::CTSingleton< CDescriptorPool >::Instance();
			}
			if( m_pPool )
			{
				m_pItem = m_pPool->GetItem( m_i );
			}
		}

		return ( m_pItem != 0 ) ? true : false;
	}

};//nsWin32
