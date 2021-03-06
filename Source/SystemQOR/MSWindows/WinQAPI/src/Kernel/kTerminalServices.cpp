//kTerminalServices.cpp

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

#include "WinQAPI/Kernel32.h"
#include "ReturnCheck.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	//--------------------------------------------------------------------------------
	BOOL CKernel32::ProcessIdToSessionId( DWORD dwProcessId, DWORD* pSessionId )
	{
		_WINQ_SFCONTEXT( "CKernel32::ProcessIdToSessionId" );
		CCheckReturn< BOOL, CBoolCheck<> >::TType bResult;
		bResult = ::ProcessIdToSessionId( dwProcessId, pSessionId );
		return bResult;
	}	

	//--------------------------------------------------------------------------------
	BOOL CKernel32::TermsrvAppInstallMode(void)
	{
		_WINQ_SFCONTEXT( "CKernel32::TermsrvAppInstallMode" );
		CCheckReturn< BOOL, CBoolCheck<> >::TType bResult;
#	if ( _WIN32_WINNT >= 0x0502 )
		//::TermsrvAppInstallMode();
#	else
		
#	endif
		return bResult;
	}

	//--------------------------------------------------------------------------------
	DWORD CKernel32::WTSGetActiveConsoleSessionId(void)
	{
		_WINQ_SFCONTEXT( "CKernel32::WTSGetActiveConsoleSessionId" );
		DWORD dwResult = 0;
#	if( _WIN32_WINNT >= 0x0501 )
		dwResult = ::WTSGetActiveConsoleSessionId();
#	else
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T( "WTSGetActiveConsoleSessionId" ), _T( "Windows XP" ), 0 ));
#	endif
		return dwResult;
	}

}//nsWinQAPI

