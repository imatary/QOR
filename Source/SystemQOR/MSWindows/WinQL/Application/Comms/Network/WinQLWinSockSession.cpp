//WinQLWinSockSession.cpp

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
#include "WinQL/Application/Comms/Network/WinQLWinSockSession.h"
#include "WinQAPI/WS2_32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	__QOR_IMPLEMENT_OCLASS_LUID( CWinSockSession );

	//--------------------------------------------------------------------------------
	CWinSockSession::CWinSockSession( unsigned short usVersionRequested ) : m_Library( CWS2_32::Instance() )
	,	m_iStatus( -1 )
	{
		_WINQ_FCONTEXT( "CWinSockSession::CWinSockSession" );
		__QOR_PROTECT
		{
			m_iStatus = m_Library.WSAStartup( usVersionRequested, reinterpret_cast< LPWSADATA >( &m_Data ) );
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	CWinSockSession::~CWinSockSession()
	{
		_WINQ_FCONTEXT( "CWinSockSession::~CWinSockSession" );
		m_iStatus = m_Library.WSACleanup();
	}

	//--------------------------------------------------------------------------------
	bool CWinSockSession::IsValid()
	{
		_WINQ_FCONTEXT( "CWinSockSession::IsValid" );
		return m_iStatus == 0 ? true : false;
	}

	//--------------------------------------------------------------------------------
	WinSockSessionData CWinSockSession::GetData()
	{
		return m_Data;
	}

}//nsWin32
