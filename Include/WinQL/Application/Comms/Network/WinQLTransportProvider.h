//TransprtProvider.h
//Win32 Transport Provider

#ifndef WINQL_COMMS_TRANSPORTPROVIDER_H_3
#define WINQL_COMMS_TRANSPORTPROVIDER_H_3

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
	class __QOR_INTERFACE( __WINQL ) CTransportProvider
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CTransportProvider );

		CTransportProvider( GUID* pProviderId, wchar_t* szProviderDllPath, WSAProtocolInfo* pProtocolInfoList, unsigned long ulNumberOfEntries, int* pErrNo );
		CTransportProvider( GUID* pProviderId, wchar_t* szProviderDllPath, wchar_t* szLSPName, unsigned long ulServiceFlags, WSAProtocolInfo* pProtocolInfoList, unsigned long ulNumberOfEntries, unsigned long* pulCatalogEntryId, int* pErrNo );
		~CTransportProvider();

	private:

		int m_iStatus;
		bool m_bPersistent;
		GUID* m_pProviderId;
		nsWinQAPI::CWS2_32& m_Library;

		CTransportProvider& operator = ( const CTransportProvider& );

	};

}//nsWin32

#endif//WINQL_COMMS_TRANSPORTPROVIDER_H_3
