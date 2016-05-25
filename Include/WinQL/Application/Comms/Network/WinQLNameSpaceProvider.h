//WinQLNameSpaceProvider.h
//Win32 NameSpace V2 Provider

#ifndef WINQL_COMMS_NSPV2PROVIDER_H_3
#define WINQL_COMMS_NSPV2PROVIDER_H_3

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
	struct WSAQuerySet2
	{
		unsigned long    dwSize;
		TCHAR*           lpszServiceInstanceName;
		WSAVersion*      lpVersion;
		TCHAR*           lpszComment;
		unsigned long    dwNameSpace;
		GUID*            lpNSProviderId;
		TCHAR*           lpszContext;
		unsigned long    dwNumberOfProtocols;
		AFProtocols*     lpafpProtocols;
		TCHAR*           lpszQueryString;
		unsigned long    dwNumberOfCsAddrs;
		CSocket::CSAddrInfo*	     lpcsaBuffer;
		unsigned long    dwOutputFlags;
		Blob*            lpBlob;   
	};

	//--------------------------------------------------------------------------------
	typedef int ( *fpNSPv2Startup )( GUID* lpProviderId, void* ppvClientSessionArg );
	typedef int ( *fpNSPv2Cleanup )( GUID* lpProviderId, void* pvClientSessionArg );
	typedef int ( *fpNSPv2LookupServiceBegin )( GUID* lpProviderId, WSAQuerySet2* lpqsRestrictions, unsigned long dwControlFlags, void* lpvClientSessionArg, void** phLookup );
	typedef void ( *fpNSPv2LookupServiceNextEx )( void* hAsyncCall, void* hLookup, unsigned long dwControlFlags, unsigned long* lpdwBufferLength, WSAQuerySet2* lpqsResults );
	typedef int ( *fpNSPv2LookupServiceEnd )( void* hLookup );
	typedef void ( *fpNSPv2SetServiceEx )( void* hAsyncCall, GUID* lpProviderId, WSAQuerySet2* lpqsRegInfo, WSAESetServiceOp essOperation, unsigned long dwControlFlags, void* lpvClientSessionArg );
	typedef void ( *fpNSPv2ClientSessionRunDown )( GUID* lpProviderId, void* pvClientSessionArg );

	//--------------------------------------------------------------------------------
	struct NSPv2Routine 
	{  
		unsigned long cbSize;
		unsigned long dwMajorVersion;
		unsigned long dwMinorVersion;
		fpNSPv2Startup NSPv2Startup;
		fpNSPv2Cleanup NSPv2Cleanup;
		fpNSPv2LookupServiceBegin NSPv2LookupServiceBegin;  
		fpNSPv2LookupServiceNextEx NSPv2LookupServiceNextEx;
		fpNSPv2LookupServiceEnd NSPv2LookupServiceEnd;  
		fpNSPv2SetServiceEx NSPv2SetServiceEx;
		fpNSPv2ClientSessionRunDown NSPv2ClientSessionRundown;
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CNameSpaceProvider
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CNameSpaceProvider );

		CNameSpaceProvider();
		~CNameSpaceProvider();

		int Advertise( const GUID* puuidProviderId, const NSPv2Routine* pNSPv2Routine );
		int CompleteAsyncCall( void* hAsyncCall, int iRetCode );
		int Unadvertise( const GUID* puuidProviderId );
		int Install( wchar_t* szIdentifier, wchar_t* szPathName, unsigned long ulNameSpace, unsigned long ulVersion, GUID* pProviderId );
		int InstallEx( wchar_t* szIdentifier, wchar_t* szPathName, unsigned long ulNameSpace, unsigned long ulVersion, GUID* pProviderId, Blob* pProviderInfo );

	private:

		nsWinQAPI::CWS2_32& m_Library;

		CNameSpaceProvider& operator = ( const CNameSpaceProvider& );
	};

}//nsWin32

#endif//WINQL_COMMS_NSPV2PROVIDER_H_3
