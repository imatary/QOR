//SocketHelper.h
//Win32 Socket Helper

#ifndef WINQL_COMMS_SOCKETHELPER_H_3
#define WINQL_COMMS_SOCKETHELPER_H_3

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
	class __QOR_INTERFACE( __WINQL ) CSocketHelper
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CSocketHelper );

		//--------------------------------------------------------------------------------
		struct In_Addr 
		{
			//--------------------------------------------------------------------------------
			union 
			{
				//--------------------------------------------------------------------------------
				struct 
				{ 
					unsigned char s_b1,s_b2,s_b3,s_b4; 
				} S_un_b;
					
				//--------------------------------------------------------------------------------
				struct 
				{ 
					unsigned short s_w1,s_w2; 
				} S_un_w;
					
				unsigned long S_addr;
			} S_un;

//#define s_addr  S_un.S_addr			// can be used for most tcp & ip code
//#define s_host  S_un.S_un_b.s_b2    // host on imp
//#define s_net   S_un.S_un_b.s_b1    // network
//#define s_imp   S_un.S_un_w.s_w2    // imp
//#define s_impno S_un.S_un_b.s_b4    // imp #
//#define s_lh    S_un.S_un_b.s_b3    // logical host
		};

		CSocketHelper();
		~CSocketHelper();

		CSocketHelper& operator = ( const CSocketHelper& src );

		hostent* GetHostByAddr( const char* pAddr, int iLen, int iType );
		hostent* GetHostByName( const char* pName );
		protoent* GetProtoByName( const char* pName );
		protoent* GetProtoByNumber( int iNumber );
		servent* GetServByName( const char* pName, const char* pProto );
		servent* GetServByPort( int iPort, const char* pProto );
		int GetHostName( char* pName, int iNamelen );

		unsigned long HToNL( unsigned long ulHost );
		unsigned short HToNS( unsigned short usHost );
		unsigned long Inet_Addr( const char* cp );
		char* Inet_NToA( In_Addr in );
		unsigned long NToHL( unsigned long ulNet );
		unsigned short NToHS( unsigned short usNet );
		int Select( int iNFDs, FDSet* pReadFDs, FDSet* pWriteFDs, FDSet* pExceptFDs, const timeval* pTimeout );
		const TCHAR* InetNToP( int iFamily, void* pAddr, TCHAR* pStringBuf, size_t StringBufSize );
		int InetPToN( int iFamily, const TCHAR* pszAddrString, void* pAddrBuf );
		int AddressToString( CSocket::Address* pAddress, unsigned long ulAddressLength, WSAProtocolInfo* lpProtocolInfo, TCHAR* szAddressString, unsigned long* pulAddressStringLength );
		int EnumNameSpaceProviders( unsigned long* pulBufferLength, WSANameSpaceInfo* pNSPBuffer );
		int EnumNameSpaceProvidersEx( unsigned long* pulBufferLength, WSANameSpaceInfoEx* pNSPBuffer );
		int EnumProtocols( int* piProtocols, WSAProtocolInfo* pProtocolBuffer, unsigned long* pulBufferLength );
		int EnumProtocols( int* piProtocols, WSAProtocolInfo* pProtocolBuffer, unsigned long* pulBufferLength, int* pErrNo );
		int GetServiceClassInfo( GUID* pProviderId, GUID* pServiceClassId, unsigned long* pulBufferLength, WSAServiceClassInfo* pServiceClassInfo );
		int GetServiceClssNameByClassId( GUID* pServiceClassId, TCHAR* szServiceClassName, unsigned long* pulBufferLength );
		int Poll( PollFD* fdarray, unsigned long nfds, int iTimeout );
		void* AsyncGetHostByAddr( CWindowHandle& hWnd, unsigned int uiMsg, const char* Addr, int iLen, int iType, char* pBuffer, int iBufLen );
		void* AsyncGetHostByName( CWindowHandle& hWnd, unsigned int uiMsg, const char* pName, char* pBuffer, int iBufLen );
		void* AsyncGetProtoByNumber( CWindowHandle& hWnd, unsigned int uiMsg, int iNumber, char* pBuffer, int iBufLen );
		void* AsyncGetProtoByName( CWindowHandle& hWnd, unsigned int uiMsg, const char* pName, char* pBuffer, int iBufLen );
		void* AsyncGetServByPort( CWindowHandle& hWnd, unsigned int uiMsg, int iPort, const char* pProto, char* pBuffer, int iBufLen );
		void* AsyncGetServByName( CWindowHandle& hWnd, unsigned int uiMsg, const char* pName, const char* pProto, char* pBuffer, int iBufLen );
		int CancelAsyncRequest( void* hAsyncTaskHandle );
		int GetLastError( void );
		void SetLastError( int iError );
		int StringToAddress( TCHAR* AddressString, int iAddressFamily, WSAProtocolInfo* pProtocolInfo, CSocket::Address* pAddress, int* pAddressLength );
		unsigned long WaitForMultipleEvents( unsigned long cEvents, void* const* lphEvents, int fWaitAll, unsigned long ulTimeout, int fAlertable );
		int EnableNameSpaceProvider( GUID* pProviderId, int fEnable );
		int GetApplicationCategory( const wchar_t* Path, unsigned long PathLength, const wchar_t* Extra, unsigned long ExtraLength, unsigned long* pPermittedLSPCategories, int* pErrNo );
		int GetProviderInfo( GUID* pProviderId, WSCProviderInfoType InfoType, unsigned char* Info, size_t* InfoSize, unsigned long ulFlags, int* pErrNo );
		int GetProviderPath( GUID* pProviderId, wchar_t* szProviderDllPath, int* pProviderDllPathLen, int* pErrNo );
		int SetApplicationCategory( const wchar_t* Path, unsigned long PathLength, const wchar_t* Extra, unsigned long ExtraLength, unsigned long ulPermittedLSPCategories, unsigned long* pPrevParmLSPCat, int* pErrNo );
		int SetProviderInfo( GUID* pProviderId, WSCProviderInfoType InfoType, unsigned char* Info, size_t InfoSize, unsigned long ulFlags, int* pErrNo );
		int UpdateProvider( GUID* pProviderId, wchar_t* szProviderDllPath, WSAProtocolInfo* pProtocolInfoList, unsigned long ulNumberOfEntries, int* pErrNo );
		int WriteNameSpaceOrder( GUID* pProviderId, unsigned long ulNumberOfEntries );
		int WriteProviderOrder( unsigned long* pulCatalogEntryId, unsigned long ulNumberOfEntries );

	private:

		nsWinQAPI::CWS2_32& m_Library;
	};

}//nsWin32

#endif//WINQL_COMMS_SOCKETHELPER_H_3
