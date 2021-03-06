//WinQLCOSessionEx.cpp

// Copyright Querysoft Limited 2013, 2015, 2017
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
#include "WinQL/COM/RunTime/Sessions/WinQLCOSessionEx.h"
#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQAPI/OLE32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	CCOSessionEx::CCOSessionEx( CCOSession::dont_initialize* pIgnore ) : CCOSession( pIgnore )
	{
		_WINQ_FCONTEXT( "CCOSessionEx::CCOSessionEx" );
		m_bUninitEx = false;
		//Derived class will init/cleanup the COM library
	}

	//--------------------------------------------------------------------------------
	CCOSessionEx::CCOSessionEx( unsigned long ulCoInit ) : CCOSession( (CCOSession::dont_initialize*)(0) )
	{
		_WINQ_FCONTEXT( "CCOSessionEx::CCOSessionEx" );
		if( ulCoInit == 0 )
		{
			m_lStatus = m_Library.CoInitialize( 0 );
		}
		else
		{
			m_lStatus = m_Library.CoInitializeEx( 0, ulCoInit );
		}
		m_bUninitEx = true;
	}

	//--------------------------------------------------------------------------------
	CCOSessionEx::~CCOSessionEx()
	{
		_WINQ_FCONTEXT( "CCOSessionEx::~CCOSessionEx" );
		if( m_bUninitEx )
		{
			m_Library.CoUninitialize();
		}
	}

	//--------------------------------------------------------------------------------
	long CCOSessionEx::AllowSetForegroundWindow( void* pUnk )
	{
		_WINQ_FCONTEXT( "CCOSessionEx::AllowSetForegroundWindow" );
		return m_Library.CoAllowSetForegroundWindow( reinterpret_cast< ::IUnknown* >( pUnk ), 0 );
	}

	//--------------------------------------------------------------------------------
	//Cancel outbound DCOM call on current thread
	long CCOSessionEx::CancelCall( unsigned long ulTimeout )
	{
		_WINQ_FCONTEXT( "CCOSessionEx::CancelCall" );
		return m_Library.CoCancelCall( 0, ulTimeout );
	}

	//--------------------------------------------------------------------------------
	void CCOSessionEx::FreeAllLibraries()
	{
		_WINQ_FCONTEXT( "CCOSessionEx::FreeAllLibraries" );
		m_Library.CoFreeAllLibraries();
	}

	//--------------------------------------------------------------------------------
	void CCOSessionEx::FreeUnusedLibraries()
	{
		_WINQ_FCONTEXT( "CCOSessionEx::FreeUnusedLibraries" );
		m_Library.CoFreeUnusedLibraries( );
	}

	//--------------------------------------------------------------------------------
	void CCOSessionEx::FreeUnusedLibrariesEx( unsigned long ulUnloadDelay )
	{
		_WINQ_FCONTEXT( "CCOSessionEx::FreeUnusedLibrariesEx" );
		m_Library.CoFreeUnusedLibrariesEx( ulUnloadDelay, 0 );
	}

	//--------------------------------------------------------------------------------
	long CCOSessionEx::GetApartmentType( AptType* pAptType, AptTypeQualifier* pAptQualifier )
	{
		_WINQ_FCONTEXT( "CCOSessionEx::GetApartmentType" );
		return m_Library.CoGetApartmentType( reinterpret_cast< APTTYPE* >( pAptType ), reinterpret_cast< APTTYPEQUALIFIER* >( pAptQualifier ) );
	}

	//--------------------------------------------------------------------------------
	long CCOSessionEx::GetCallContext( const GUID& riid, void** ppInterface )
	{
		_WINQ_FCONTEXT( "CCOSessionEx::GetCallContext" );
		return m_Library.CoGetCallContext( reinterpret_cast< REFIID >( riid ), ppInterface );
	}

	//--------------------------------------------------------------------------------
	long CCOSessionEx::GetCallerTID( unsigned long* pTID )
	{
		_WINQ_FCONTEXT( "CCOSessionEx::GetCallerTID" );
		return m_Library.CoGetCallerTID( pTID );
	}

	//--------------------------------------------------------------------------------
	long CCOSessionEx::GetCurrentLogicalThreadId( GUID* pGuid )
	{
		_WINQ_FCONTEXT( "CCOSessionEx::GetCurrentLogicalThreadId" );
		return m_Library.CoGetCurrentLogicalThreadId( reinterpret_cast< ::GUID* >( pGuid ) );
	}

	//--------------------------------------------------------------------------------
	unsigned long CCOSessionEx::GetCurrentUniqueThreadId()
	{
		_WINQ_FCONTEXT( "CCOSessionEx::GetCurrentUniqueThreadId" );
		return m_Library.CoGetCurrentProcess();
	}

	//--------------------------------------------------------------------------------
	long CCOSessionEx::GetMalloc( unsigned long ulMemContext, void** ppMalloc )
	{
		_WINQ_FCONTEXT( "CCOSessionEx::GetMalloc" );
		return m_Library.CoGetMalloc( ulMemContext, reinterpret_cast< LPMALLOC* >( ppMalloc ) );
	}

	//--------------------------------------------------------------------------------
	COLESessionEx::COLESessionEx() : CCOSessionEx( (CCOSession::dont_initialize*)(0) )
	{
		_WINQ_FCONTEXT( "CCOSessionEx::COLESessionEx" );
		m_lStatus = m_Library.OleInitialize( 0 );
		m_bOLEUninitEx = true;
	}

	//--------------------------------------------------------------------------------
	COLESessionEx::~COLESessionEx()
	{
		_WINQ_FCONTEXT( "CCOSessionEx::~COLESessionEx" );
		if( m_bOLEUninitEx )
		{
			m_Library.OleUninitialize();
		}
	}
		
}//nsWin32
