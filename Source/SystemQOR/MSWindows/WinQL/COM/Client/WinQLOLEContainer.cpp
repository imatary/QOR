//WinQLOLEContainer.cpp

// Copyright Querysoft Limited 2013, 2015
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include "WinQL/CodeServices/WinQLPolicy.h"
#include "WinQL/Application/Threading/WinQLCriticalSection.h"
#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/COM/OLEContainer.h"
#include "WinQAPI/OLE32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_OCLASS_LUID( COLEContainer );

__QCMP_WARNING_PUSH
__QCMP_WARNING_DISABLE( __QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST )
	//--------------------------------------------------------------------------------
	COLEContainer::COLEContainer() : 
		m_OleClientSitePtr( this )
	, m_AdviseSinkPtr( this )
	, m_MessageFilterPtr( this )
	, m_OleItemContainerPtr( this )
	, m_PersistFilePtr( this )
	, m_ClassFactoryPtr( this )
	, m_OleInPlaceSitePtr( this )
	, m_OleInPlaceFramePtr( this )
	, m_OleInPlaceObjectPtr( this )
	, m_DropSourcePtr( this )
	, m_DropTargetPtr( this )
	, m_DataObjectPtr( this )
	{
		_WINQ_FCONTEXT( "COLEContainer::COLEContainer" );
	}
__QCMP_WARNING_POP

	//--------------------------------------------------------------------------------
	COLEContainer::~COLEContainer()
	{
		_WINQ_FCONTEXT( "COLEContainer::~COLEContainer" );
	}

	//--------------------------------------------------------------------------------
	//Guarantee availaility of required interfaces
	void COLEContainer::Initialize()
	{
		_WINQ_FCONTEXT( "COLEContainer::Initialize" );
		IOleClientSite* pClientSite = m_OleClientSitePtr;
		IAdviseSink* pAdviseSink = m_AdviseSinkPtr;
	}

	//--------------------------------------------------------------------------------
	long COLEContainer::OleCreateDefaultHandler( const GUID& clsid, IUnknown* pUnkOuter, const GUID& riid, void** lplpObj )
	{
		_WINQ_FCONTEXT( "COLEContainer::OleCreateDefaultHandler" );
		long lResult = -1;
		__QOR_PROTECT
		{
			lResult = m_Library.OleCreateDefaultHandler( reinterpret_cast< REFCLSID >( clsid ), 
				reinterpret_cast< ::LPUNKNOWN >( pUnkOuter ),
				reinterpret_cast< REFIID >( riid ), lplpObj );
		}__QOR_ENDPROTECT
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long COLEContainer::OleCreateEmbeddingHelper( const GUID& clsid, IUnknown* pUnkOuter, unsigned long flags, IClassFactory* pCF, const GUID& riid, void** lplpObj )
	{
		_WINQ_FCONTEXT( "COLEContainer::OleCreateEmbeddingHelper" );
		long lResult = -1;
		__QOR_PROTECT
		{
			lResult = m_Library.OleCreateEmbeddingHelper( reinterpret_cast< REFCLSID >( clsid ),
				reinterpret_cast< ::LPUNKNOWN >( pUnkOuter ), flags, 
				reinterpret_cast< ::LPCLASSFACTORY >( pCF ), 
				reinterpret_cast< REFIID >( riid ), lplpObj );
		}__QOR_ENDPROTECT
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long COLEContainer::OleCreate( const GUID& rclsid, const GUID& riid, unsigned long renderopt, FormatEtc* pFormatEtc, IStorage* pStg )
	{
		_WINQ_FCONTEXT( "COLEContainer::OleCreate" );
		long lResult = -1;
		__QOR_PROTECT
		{
			lResult = m_Library.OleCreate( reinterpret_cast< REFCLSID >( rclsid ),
				reinterpret_cast< REFIID >( riid ), renderopt,
				reinterpret_cast< ::LPFORMATETC >( pFormatEtc ), 
				reinterpret_cast< ::LPOLECLIENTSITE >( Internal_Interface< IOleClientSite >() ),
				reinterpret_cast< ::LPSTORAGE >( pStg ), 
				reinterpret_cast< void** >( &m_pContained ) );
		}__QOR_ENDPROTECT
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long COLEContainer::OleCreateEx( const GUID& rclsid, const GUID& riid, unsigned long dwFlags, unsigned long renderopt, unsigned long cFormats, unsigned long* rgAdvf, FormatEtc* rgFormatEtc, unsigned long* rgdwConnection, IStorage* pStg )
	{
		_WINQ_FCONTEXT( "COLEContainer::OleCreateEx" );
		long lResult = -1;
		__QOR_PROTECT
		{
			lResult = m_Library.OleCreateEx( reinterpret_cast< REFCLSID >( rclsid ),
				reinterpret_cast< REFIID >( riid ), dwFlags, renderopt, cFormats, rgAdvf, 
				reinterpret_cast< ::LPFORMATETC >( rgFormatEtc ), 
				reinterpret_cast< ::IAdviseSink* >( Internal_Interface< IAdviseSink >() ), rgdwConnection, 
				reinterpret_cast< ::LPOLECLIENTSITE >( Internal_Interface< IOleClientSite >() ), 
				reinterpret_cast< ::LPSTORAGE >( pStg ), 
				reinterpret_cast< void** >( &m_pContained ) );
		}__QOR_ENDPROTECT
		return lResult;
	}

	//--------------------------------------------------------------------------------
	bool COLEContainer::OleIsRunning()
	{
		_WINQ_FCONTEXT( "COLEContainer::OleIsRunning" );
		bool bResult = false;
		__QOR_PROTECT
		{
			IOleObject* pObject;
			if( m_pContained )
			{
				long lResult = m_pContained->QueryInterface( IOleObject_IID, reinterpret_cast< void** >( &pObject ) );
				if( lResult == S_OK )
				{
					lResult = m_Library.OleIsRunning( reinterpret_cast< ::LPOLEOBJECT >( pObject ) ) ? true : false;
					pObject->Release();
				}
			}
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	long COLEContainer::OleNoteObjectVisible( bool bVisible )
	{
		_WINQ_FCONTEXT( "COLEContainer::OleNoteObjectVisible" );
		long lResult = -1;
		__QOR_PROTECT
		{
			if( m_pContained )
			{
				lResult = m_Library.OleNoteObjectVisible( reinterpret_cast< ::LPUNKNOWN >( m_pContained ), bVisible ? 1 : 0 );
			}
		}__QOR_ENDPROTECT
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long COLEContainer::TellObjectItsContained( bool bContained )
	{
		_WINQ_FCONTEXT( "COLEContainer::TellObjectItsContained" );
		long lResult = -1;
		__QOR_PROTECT
		{
			if( m_pContained )
			{
				lResult = m_Library.OleSetContainedObject( reinterpret_cast< ::LPUNKNOWN >( m_pContained ), bContained );
			}
		}__QOR_ENDPROTECT
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long COLEContainer::OleRun()
	{
		_WINQ_FCONTEXT( "COLEContainer::OleRun" );
		long lResult = -1;
		__QOR_PROTECT
		{
			if( m_pContained )
			{
				lResult = m_Library.OleRun( reinterpret_cast< ::LPUNKNOWN >( m_pContained ) );
			}
		}__QOR_ENDPROTECT
		return lResult;
	}

}//nsWin32