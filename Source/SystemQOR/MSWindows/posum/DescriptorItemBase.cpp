//DescriptorItemBase.cpp

#include "SystemQOR.h"
#include "WinQL/CodeServices/ErrorSystem/Error.h"
#include "PosumQOR/MSWindows/DescriptorItemBase.h"
#include "PosumQOR/MSWindows/DescriptorPool.h"
#include "PosumQOR/MSWindows/FileSystem.h"
#include "WinQL/CodeServices/Process.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	CDescriptorItemBase::CDescriptorItemBase( int iDescriptor ) : m_iDescriptor( iDescriptor )
	{
		m_lRefCount = 0;
	}

	//--------------------------------------------------------------------------------
	CDescriptorItemBase::~CDescriptorItemBase()
	{
		FileSystem().DescriptorPool().FreeDescriptor( this );
	}

	//--------------------------------------------------------------------------------
	int CDescriptorItemBase::Descriptor( void )
	{
		return m_iDescriptor;
	}

	//--------------------------------------------------------------------------------
	CDescriptorItemBase::CDescriptorItemBase() : m_iDescriptor( -1 )
	{
		FileSystem().DescriptorPool().AssignDescriptor( this );
	}

	//--------------------------------------------------------------------------------
	void CDescriptorItemBase::AssignDescriptor( int iDescriptor )
	{
		if( m_iDescriptor == -1 )
		{
			m_iDescriptor = iDescriptor;
		}
	}

	//--------------------------------------------------------------------------------
	void CDescriptorItemBase::FreeDescriptor( void )
	{
		m_iDescriptor = -1;
	}

	//--------------------------------------------------------------------------------
	void CDescriptorItemBase::AddRef()
	{
		m_lRefCount++;
	}

	//--------------------------------------------------------------------------------
	void CDescriptorItemBase::Release()
	{
		m_lRefCount--;
	}

};// nsWin32
