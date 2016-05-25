//DescriptorItem.h

#ifndef _WINQL_FILESYSTEM_DESCRIPTORITEM_H_
#define _WINQL_FILESYSTEM_DESCRIPTORITEM_H_

#pragma __QCMP_OPTIMIZEINCLUDE

#include "WinQL/WinQL.h"
//#include "WinQL/WinQLPolicy.h"
#include "WinQL/CodeServices/Synchronization.h"
#include "PosumQOR/MSWindows/DescriptorItemBase.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	template< class TObject, class TInterface >
	class CDescriptorItem : public CDescriptorItemBase, public TInterface
	{
	public:

		//--------------------------------------------------------------------------------
		CDescriptorItem( TObject* pObject ) : m_pObject( pObject ), CDescriptorItemBase()
		{
		}

		//--------------------------------------------------------------------------------
		virtual ~CDescriptorItem()
		{
		}


		//--------------------------------------------------------------------------------
		virtual ssize_t Read( void* pBuffer, size_t nBytes )
		{
			return this->read( pBuffer, nBytes );
		}

		//--------------------------------------------------------------------------------
		virtual long read( void* p, size_t size )
		{
			return m_pObject->read( p, size );
		}

		//--------------------------------------------------------------------------------
		virtual ssize_t Write( const void* pBuffer, size_t nBytes )
		{
			return write( pBuffer, nBytes );
		}

		//--------------------------------------------------------------------------------
		virtual ssize_t write( const void* pBuffer, size_t nBytes )
		{
			return m_pObject->write( pBuffer, nBytes );
		}

		//--------------------------------------------------------------------------------
		virtual int Close( void )
		{
			return this->close();
		}

		//--------------------------------------------------------------------------------
		virtual int close( void )
		{
			int iResult = m_pObject->close();
			m_pObject = 0;
			return iResult;
		}

	protected:

		CDescriptorItem()
		{			
		}

		TObject* m_pObject;
	};

};// nsWin32

#endif//_WINQL_FILESYSTEM_DESCRIPTORITEM_H_
