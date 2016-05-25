//AddressInfo.h
//Win32 Address Info

#ifndef WINQ_COMMS_ADDRINFO_H_3
#define WINQ_COMMS_ADDRINFO_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/WinQL.h"
#include "WinQLSocket.h"
#include "SystemQOR/MSWindows/types/time_types.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	class __QOR_INTERFACE( __WINQAPI ) CWS2_32;
}

//--------------------------------------------------------------------------------
namespace nsWin32
{

	//--------------------------------------------------------------------------------
	struct AddrInfo 
	{
		int              ai_flags;
		int              ai_family;
		int              ai_socktype;
		int              ai_protocol;
		size_t           ai_addrlen;
		TCHAR*           ai_canonname;
		CSocket::Address* ai_addr;
		AddrInfo*		 ai_next;
	};

	//--------------------------------------------------------------------------------
	struct AddrInfoEx
	{
		int                 ai_flags;       // AI_PASSIVE, AI_CANONNAME, AI_NUMERICHOST
		int                 ai_family;      // PF_xxx
		int                 ai_socktype;    // SOCK_xxx
		int                 ai_protocol;    // 0 or IPPROTO_xxx for IPv4 and IPv6
		size_t              ai_addrlen;     // Length of ai_addr
		TCHAR*				ai_canonname;   // Canonical name for nodename
		CSocket::Address*	ai_addr;        // Binary address
		void*				ai_blob;
		size_t              ai_bloblen;
		GUID*               ai_provider;
		AddrInfoEx*			ai_next;        // Next structure in linked list
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CAddressInfo
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CAddressInfo );

		CAddressInfo( const TCHAR* pName, const TCHAR* pServiceName, unsigned long ulNameSpace, GUID* pNSpId, const AddrInfoEx* pHints, timeval* pTimeout );
		CAddressInfo( const TCHAR* pNodeName, const TCHAR* pServiceName, const AddrInfo* pHints );
		~CAddressInfo();

		AddrInfo* Info( void );
		AddrInfoEx* InfoEx( void );

	private:

		AddrInfoEx* m_pInfoEx;
		AddrInfo* m_pInfo;
		int m_iStatus;
		nsWinQAPI::CWS2_32& m_Library;

		CAddressInfo& operator = ( const CAddressInfo& );
	};

}//nsWin32

#endif//WINQ_COMMS_ADDRINFO_H_3
