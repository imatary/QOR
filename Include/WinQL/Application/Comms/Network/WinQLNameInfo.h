//NameInfo.h
//Win32 Name Info

#ifndef WINQL_COMMS_NAMEINFO_H_3
#define WINQL_COMMS_NAMEINFO_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQLSocket.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	class __QOR_INTERFACE( __WINQAPI ) CWS2_32;
}

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CNameInfo
	{

	public:

		__QOR_DECLARE_OCLASS_ID( CNameInfo );

		CNameInfo( const CSocket::Address* pSockAddr, int SockaddrLength, TCHAR* pNodeBuffer, unsigned long NodeBufferSize, TCHAR* pServiceBuffer, unsigned long ulServiceBufferSize, int iFlags );
		~CNameInfo();

	private:

		nsWinQAPI::CWS2_32& m_Library;
		int m_iStatus;

		CNameInfo& operator = ( const CNameInfo& );
	};

}//nsWin32

#endif//WINQL_COMMS_NAMEINFO_H_3
