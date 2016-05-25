//DescriptorPool.cpp

#include "SystemQOR.h"
#include "WinQL/CodeServices/ErrorSystem/Error.h"
#include "PosumQOR/MSWindows/DescriptorPool.h"
#include "PosumQOR/MSWindows/DescriptorBase.h"
#include "PosumQOR/MSWindows/DescriptorItemBase.h"
#include "PosumQOR/MSWindows/Posum_File.h"

__QOR_IMPLEMENT_SINGLETON( nsWin32::CDescriptorPool );

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	CDescriptorPool::CDescriptorPool()
	{
		m_lNextToGen = -1;
		GenerateDescriptor( 20 );
	}

	//--------------------------------------------------------------------------------
	CDescriptorPool::~CDescriptorPool()
	{
	}

	//--------------------------------------------------------------------------------
	nsCodeQOR::CTCRef< CDescriptorItemBase > CDescriptorPool::GetItem( int iDescriptor )
	{
		nsCodeQOR::CTCRef< CDescriptorItemBase > Ref( m_InUseMap.Find( iDescriptor ) );
		return Ref;
	}

	//--------------------------------------------------------------------------------
	//Generate a new descriptor into the free list
	void CDescriptorPool::GenerateDescriptor( unsigned int uiCount )
	{
		for( unsigned int uiLoop = 0; uiLoop < uiCount; uiLoop++ )
		{
			long lResult = CInterlockedHelper::Increment( &m_lNextToGen );
			int iResult = static_cast< int >( lResult );
			m_FreeList.Append( iResult );
		}
	}

	//--------------------------------------------------------------------------------
	void CDescriptorPool::AssignDescriptor( CDescriptorItemBase* pItem )
	{
		if( m_FreeList.Size() < 5 )
		{
			GenerateDescriptor( 15 );
		}
			
		int iDescriptor = m_FreeList[ 0 ];
		m_FreeList.RemoveAt( 0, 1 );
		pItem->AssignDescriptor( iDescriptor );
		m_InUseMap.Insert( iDescriptor, pItem );
	}

	//--------------------------------------------------------------------------------
	void CDescriptorPool::FreeDescriptor( CDescriptorItemBase* pItem )
	{
		int i = pItem->Descriptor();
		pItem->FreeDescriptor();
		m_InUseMap.Remove( i );
		m_FreeList.Append( i );
	}

};// nsWin32
