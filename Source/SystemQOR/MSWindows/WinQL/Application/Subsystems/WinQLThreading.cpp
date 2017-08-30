//WinQLThreading.cpp

// Copyright Querysoft Limited 2013, 2016
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
#include "WinQL/Application/SubSystems/WinQLThreading.h"
#include "WinQL/Application/Threading/WinQLThread.h"
#include "WinQAPI/Kernel32.h"
#include "WinQAPI/User32.h"

//------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	__QOR_IMPLEMENT_EXTERNAL_FACTORY( CThreading, 0x9394b8ba, 0xcc95, 0x4215, 0x84, 0x7d, 0xcf, 0xf7, 0x5f, 0x62, 0xb4, 0xce );

	//--------------------------------------------------------------------------------
	CThreading::CThreading()
	{
		_WINQ_FCONTEXT( "CThreading::CThreading" );
	}

	//--------------------------------------------------------------------------------
	CThreading::CThreading( const CThreading& src )
	{
		_WINQ_FCONTEXT( "CThreading::CThreading" );
		*this = src;
	}

	//--------------------------------------------------------------------------------
	CThreading& CThreading::operator = ( const CThreading& )
	{
		_WINQ_FCONTEXT( "CThreading::operator =" );
		return *this;
	}

	//--------------------------------------------------------------------------------
	CThreading::~CThreading()
	{
		_WINQ_FCONTEXT( "CThreading::~CThreading" );
	}

	//--------------------------------------------------------------------------------
	void CThreading::Setup( nsQOR::IApplication& Applicaton )
	{
		_WINQ_FCONTEXT( "CThreading::Setup" );
	}

	//--------------------------------------------------------------------------------
	void CThreading::Shutdown( nsQOR::IApplication& Application )
	{
		_WINQ_FCONTEXT( "CThreading::Shutdown" );
	}

	//--------------------------------------------------------------------------------
	bool CThreading::SetStackGuarantee( unsigned long ulStackSizeInBytes )
	{
		_WINQ_FCONTEXT( "CThreading::SetStackGuarantee" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = CKernel32::SetThreadStackGuarantee( &ulStackSizeInBytes ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//------------------------------------------------------------------------------
	unsigned long CThreading::Sleep( unsigned long dwMilliseconds, bool bAlertable )
	{
		_WINQ_FCONTEXT( "CThreading::Sleep" );
		unsigned long dwResult = 0;
		__QOR_PROTECT
		{
			if( bAlertable )
			{
				dwResult = CKernel32::SleepEx( dwMilliseconds, bAlertable ? TRUE : FALSE );
			}
			else
			{
				CKernel32::Sleep( dwMilliseconds );
			}
		}__QOR_ENDPROTECT
		return dwResult;
	}

	//--------------------------------------------------------------------------------
	void CThreading::SwitchToFiber( void* lpFiber )
	{
		_WINQ_FCONTEXT( "CThreading::SwitchToFiber" );
		__QOR_PROTECT
		{
			CKernel32::SwitchToFiber( lpFiber );
		}__QOR_ENDPROTECT
	}

	//------------------------------------------------------------------------------
	bool CThreading::SwitchToThread()
	{
		_WINQ_FCONTEXT( "CThreading::SwitchToThread" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = CKernel32::SwitchToThread() ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	unsigned long CThreading::GetCurrentProcessorNumber()
	{
		_WINQ_FCONTEXT( "CThreading::GetCurrentProcessorNumber" );
		DWORD dwResult = 0;
		__QOR_PROTECT
		{
			dwResult = CKernel32::GetCurrentProcessorNumber();
		}__QOR_ENDPROTECT
		return dwResult;
	}

	//--------------------------------------------------------------------------------
	nsQOR::IThread::ref_type CThreading::GetCurrent( void )
	{
		return t_pCurrentWin32Thread->Ref();
	}

	//--------------------------------------------------------------------------------
	unsigned long CThreading::GetCurrentId( void )
	{
		_WINQ_SFCONTEXT( "CThreading::GetCurrentId" );
		return CKernel32::GetCurrentThreadId();
	}

	//--------------------------------------------------------------------------------
	nsQOR::IThread::ref_type CThreading::Create( Cmp_ulong_ptr ulStackSize )
	{
		_WINQ_FCONTEXT( "CThreading::Create" );
		unsigned long ulThreadId = 0;

		unsigned long ulCreationFlags = 0;
		nsWin32::LPSECURITY_ATTRIBUTES pSecurityAttributes = nullptr;
		CThread* pNewThread = new CThread( pSecurityAttributes, ulStackSize, &CThread::StartRoutine, (void*)( &pNewThread ), ulCreationFlags | CREATE_SUSPENDED, &ulThreadId );

		nsQOR::IThread::ref_type Ref( pNewThread );

		if( ( ulCreationFlags & CREATE_SUSPENDED ) == 0 )
		{
			pNewThread->Resume();
		}
		return Ref;
	}

}//nsWin32