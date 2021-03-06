//WinQLSyncHandle.cpp

// Copyright Querysoft Limited 2013
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

#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/Application/ErrorSystem/WinQLErrDomain.h"
#include "WinQL/CodeServices/Handles/WinQLSyncHandle.h"
#include "WinQAPI/Kernel32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_OCLASS_LUID( CSyncHandle );

	//--------------------------------------------------------------------------------
	CSyncHandle::CSyncHandle() : CHandle( 0 ), 
		m_SourceProcess( nsWinQAPI::CKernel32::Instance().GetCurrentProcess() )
	,	m_ulRefCount( 0 )
	,	m_bCanBeSignaled( false )
	{
		_WINQ_FCONTEXT( "CSyncHandle::CSyncHandle" );
	}

	//--------------------------------------------------------------------------------
	CSyncHandle::CSyncHandle( void* h, bool bCanBeSignaled ) : CHandle( h ), 
		m_SourceProcess( nsWinQAPI::CKernel32::Instance().GetCurrentProcess() )
	,	m_ulRefCount( 0 )
	,	m_bCanBeSignaled( bCanBeSignaled )
	{
		_WINQ_FCONTEXT( "CSyncHandle::CSyncHandle" );
	}

	//--------------------------------------------------------------------------------
	CSyncHandle::~CSyncHandle()
	{
		_WINQ_FCONTEXT( "CSyncHandle::~CSyncHandle" );
		if( m_h != 0 )
		{
			Close();
		}
	}

	//--------------------------------------------------------------------------------
	CSyncHandle::CSyncHandle( const CSyncHandle& src ) : CHandle( 0 ), 
		m_SourceProcess( nsWinQAPI::CKernel32::Instance().GetCurrentProcess() )
	,	m_ulRefCount( 0 )
	,	m_bCanBeSignaled( false )
	{
		_WINQ_FCONTEXT( "CSyncHandle::CSyncHandle" );
		*this = src;
	}

	//--------------------------------------------------------------------------------
	CSyncHandle& CSyncHandle::operator = ( const CSyncHandle& src )
	{
		_WINQ_FCONTEXT( "CSyncHandle::operator =" );
		if( &src != this )
		{
			__QOR_PROTECT
			{
				if( m_h != 0 )
				{
					Close();
				}
				unsigned long ulFlags = 0;
				GetInformation( &ulFlags );
				bool bResult = Duplicate( src.m_SourceProcess.ptr(), nsWinQAPI::CKernel32::Instance().GetCurrentProcess(), &m_h, 0, ( ulFlags & HANDLE_FLAG_INHERIT ) != 0 ? true : false, DUPLICATE_SAME_ACCESS );
				if( !bResult )
				{
					_QSYS_MSW_WWL_RAISE( ( nsWinQAPI::GENERAL_API_ERROR, _TXT( "CSyncHandle::operator =" ).c_str(), 0 ), nsCodeQOR::CError::ERR_LVL_SERIOUS );
				}
				else
				{
					m_bCanBeSignaled = src.m_bCanBeSignaled;
				}
			}__QOR_ENDPROTECT
		}
		return *this;
	}

	//--------------------------------------------------------------------------------
	//Assign a Windows handle to this object
	CSyncHandle& CSyncHandle::operator = ( void* pOSHandle )
	{
		_WINQ_FCONTEXT( "CSyncHandle::operator =" );
		__QOR_PROTECT
		{
			if( m_h != 0 )
			{
				Close();
			}
			m_h = pOSHandle;
		}__QOR_ENDPROTECT
		return *this;
	}

	//--------------------------------------------------------------------------------
	void* CSyncHandle::Use( void )
	{
		_WINQ_FCONTEXT( "CSyncHandle::Use" );
		return ptr();
	}

	//--------------------------------------------------------------------------------
	unsigned long CSyncHandle::AddRef( void )
	{
		_WINQ_FCONTEXT( "CSyncHandle::AddRef" );
		return ++m_ulRefCount;
	}

	//--------------------------------------------------------------------------------
	unsigned long CSyncHandle::Release( void )
	{
		_WINQ_FCONTEXT( "CSyncHandle::Release" );
		return --m_ulRefCount;
	}

	//--------------------------------------------------------------------------------
	bool CSyncHandle::CanBeSignaled( void )
	{
		_WINQ_FCONTEXT( "CSyncHandle::CanBeSignaled" );
		return m_bCanBeSignaled;
	}

	//--------------------------------------------------------------------------------
	void CSyncHandle::SetCanBeSignaled( bool bSignalable )
	{
		_WINQ_FCONTEXT( "CSyncHandle::SetCanBeSignaled" );
		m_bCanBeSignaled = bSignalable;
	}


	//--------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID( CThreadHandle );

	//--------------------------------------------------------------------------------
	CThreadHandle::CThreadHandle() : CSyncHandle( nsWinQAPI::CKernel32::GetCurrentThread(), true )
	{
	}

	//--------------------------------------------------------------------------------
	CThreadHandle::CThreadHandle( void* h ) : CSyncHandle( h, true )
	{
	}

	//--------------------------------------------------------------------------------
	CThreadHandle::~CThreadHandle()
	{
	}

	//--------------------------------------------------------------------------------
	CThreadHandle::CThreadHandle( const CThreadHandle& src ) : CSyncHandle( src )
	{
		if( &src != this )
		{
			*this = src;
		}
	}

	//--------------------------------------------------------------------------------
	CThreadHandle& CThreadHandle::operator = ( const CThreadHandle& src )
	{
		_WINQ_FCONTEXT( "CThreadHandle::operator =" );
		__QOR_PROTECT
		{
			m_h = src.m_h;
		}__QOR_ENDPROTECT
		return *this;
	}

	//--------------------------------------------------------------------------------
	CThreadHandle& CThreadHandle::operator = ( void* pOSHandle )
	{
		_WINQ_FCONTEXT( "CThreadHandle::operator =" );
		__QOR_PROTECT
		{
			m_h = pOSHandle;
		}__QOR_ENDPROTECT
		return *this;
	}


	//--------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID( CSyncHandleSet );

	//--------------------------------------------------------------------------------
	CSyncHandleSet::CSyncHandleSet()
	{
		_WINQ_FCONTEXT( "CSyncHandleSet::CSyncHandleSet" );
	}

	//--------------------------------------------------------------------------------
	CSyncHandleSet::CSyncHandleSet( const CSyncHandleSet& src )
	{
		_WINQ_FCONTEXT( "CSyncHandleSet::CSyncHandleSet" );
		*this = src;
	}

	//--------------------------------------------------------------------------------
	CSyncHandleSet::~CSyncHandleSet()
	{
		_WINQ_FCONTEXT( "CSyncHandleSet::~CSyncHandleSet" );
	}

	//--------------------------------------------------------------------------------
	CSyncHandleSet& CSyncHandleSet::operator = ( const CSyncHandleSet& src)
	{
		_WINQ_FCONTEXT( "CSyncHandleSet::operator =" );

		if( &src != this )
		{
		}

		return *this;
	}

	//--------------------------------------------------------------------------------
	unsigned long CSyncHandleSet::Add( CSyncHandle& Handle )
	{
		_WINQ_FCONTEXT( "CSyncHandleSet::Add" );
		CSyncHandle* pSyncHandle = &Handle;
		m_ArraySyncHandles.Append( pSyncHandle );
		void* pHandle = Handle.ptr();
		m_UseArray.Append( pHandle );
		return m_ArraySyncHandles.Size();
	}

	//--------------------------------------------------------------------------------
	unsigned long CSyncHandleSet::Remove( CSyncHandle& Handle )
	{
		_WINQ_FCONTEXT( "CSyncHandleSet::Remove" );
		void* pHandle = Handle.ptr();
		unsigned long ulIndex = 0;
		while( ulIndex < m_UseArray.Size() )
		{
			if( m_UseArray[ ulIndex ] == pHandle )
			{
				m_UseArray.RemoveAt( ulIndex );
				m_ArraySyncHandles.RemoveAt( ulIndex );
				return m_UseArray.Size();
			}
		}

		_QSYS_MSW_WWL_RAISE( ( nsWinQAPI::GENERAL_API_ERROR, _TXT( "CSyncHandleSet::Remove" ), 0 ), nsCodeQOR::CError::ERR_LVL_CONTINUE );
		return (unsigned long)(-1);	
	}

	//--------------------------------------------------------------------------------
	unsigned long CSyncHandleSet::Count( void )
	{
		_WINQ_FCONTEXT( "CSyncHandleSet::Count" );
		return m_UseArray.Size();
	}

	//--------------------------------------------------------------------------------
	void** CSyncHandleSet::Use( void )
	{
		_WINQ_FCONTEXT( "CSyncHandleSet::Use" );
		return m_UseArray.GetAddressOfData();
	}

}//nsWin32
