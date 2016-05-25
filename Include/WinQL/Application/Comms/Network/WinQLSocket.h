//Socket.h
//Win32 Socket

#ifndef WINQL_COMMS_SOCKET_H_3
#define WINQL_COMMS_SOCKET_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/WinQL.h"
#include "WinQL/Definitions/Data.h"
#include "CodeQOR/Macros/CodingMacros.h"
#include "SystemQOR/MSWindows/types/time_types.h"
#include "SystemQOR/MSWindows/types/netdb_types.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	class __QOR_INTERFACE( __WINQAPI ) CWS2_32;
}

//--------------------------------------------------------------------------------
namespace nsWin32
{
	typedef int (__QCMP_STDCALLCONVENTION * fp_AcceptEx )( Cmp_uint_ptr sListenSocket, Cmp_uint_ptr sAcceptSocket,
		void* lpOutputBuffer, unsigned long dwReceiveDataLength, unsigned long dwLocalAddressLength,
		unsigned long dwRemoteAddressLength, unsigned long* lpdwBytesReceived, OVERLAPPED* lpOverlapped );

	//--------------------------------------------------------------------------------
	struct WSABuf
	{
		unsigned long len;  // the length of the buffer
		char* buf;			// the pointer to the buffer
	};

	//--------------------------------------------------------------------------------
	enum WSAEComparator
	{
		CompEqual = 0,
		CompNotLess
	};

	//--------------------------------------------------------------------------------
	struct WSAVersion
	{
		unsigned long       dwVersion;
		WSAEComparator		ecHow;
	};

	//--------------------------------------------------------------------------------
	struct AFProtocols
	{
		int iAddressFamily;
		int iProtocol;
	};

	//--------------------------------------------------------------------------------
	struct FlowSpec 
	{
		unsigned long       TokenRate;
		unsigned long       TokenBucketSize;
		unsigned long       PeakBandwidth;
		unsigned long       Latency;
		unsigned long       DelayVariation;
		unsigned long		ServiceType;
		unsigned long       MaxSduSize;
		unsigned long       MinimumPolicedSize;
	};

	//--------------------------------------------------------------------------------
	struct QualityOfService
	{
		FlowSpec      SendingFlowspec;       // the flow spec for data sending
		FlowSpec      ReceivingFlowspec;     // the flow spec for data receiving
		WSABuf        ProviderSpecific;      // additional provider specific stuff
	};

	__QCMP_STATIC_CONSTANT( int, MaxProtocolChain = 7 );
	__QCMP_STATIC_CONSTANT( int, WSAProtocolLen = 255 );
	__QCMP_STATIC_CONSTANT( int, FDMaxEvents = 10 );

	//--------------------------------------------------------------------------------
	struct WSAProtocolChain
	{
		int ChainLen;										// the length of the chain, length = 0 means layered protocol, length = 1 means base protocol, length > 1 means protocol chain
		unsigned long ChainEntries[ MaxProtocolChain ];   // a list of dwCatalogEntryIds
	};

	//--------------------------------------------------------------------------------
	struct WSAProtocolInfo 
	{
		unsigned long dwServiceFlags1;
		unsigned long dwServiceFlags2;
		unsigned long dwServiceFlags3;
		unsigned long dwServiceFlags4;
		unsigned long dwProviderFlags;
		GUID ProviderId;
		unsigned long dwCatalogEntryId;
		WSAProtocolChain ProtocolChain;
		int iVersion;
		int iAddressFamily;
		int iMaxSockAddr;
		int iMinSockAddr;
		int iSocketType;
		int iProtocol;
		int iProtocolMaxOffset;
		int iNetworkByteOrder;
		int iSecurityScheme;
		unsigned long dwMessageSize;
		unsigned long dwProviderReserved;
		TCHAR szProtocol[ WSAProtocolLen + 1 ];
	};

	typedef int ( __QCMP_STDCALLCONVENTION * fpConditionProc )( WSABuf* lpCallerId, WSABuf* lpCallerData, QualityOfService* lpSQOS, QualityOfService* lpGQOS, WSABuf* lpCalleeId, WSABuf* lpCalleeData, unsigned int* g, Cmp_ulong_ptr dwCallbackData );

	//--------------------------------------------------------------------------------
	struct WSANameSpaceInfo
	{
		GUID               NSProviderId;
		unsigned long      dwNameSpace;
		int                fActive;
		unsigned long      dwVersion;
		TCHAR*             lpszIdentifier;
	};

	//--------------------------------------------------------------------------------
	struct WSANameSpaceInfoEx
	{
		GUID                NSProviderId;
		unsigned long       dwNameSpace;
		int                 fActive;
		unsigned long       dwVersion;
		TCHAR*              lpszIdentifier;
		Blob                ProviderSpecific;
	};

	//--------------------------------------------------------------------------------
	struct WSANetworkEvents
	{
       long lNetworkEvents;
       int iErrorCode[ FDMaxEvents ];
	};

	//--------------------------------------------------------------------------------
	struct WSANSClassInfo
	{
		TCHAR*   lpszName;
		unsigned long   dwNameSpace;
		unsigned long   dwValueType;
		unsigned long   dwValueSize;
		void*  lpValue;
	};

	//--------------------------------------------------------------------------------
	struct WSAServiceClassInfo
	{
		GUID*              lpServiceClassId;
		TCHAR*             lpszServiceClassName;
		unsigned long      dwCount;
		WSANSClassInfo*   lpClassInfos;
	};

	typedef void ( __QCMP_STDCALLCONVENTION * fpWSAOverlappedCompletionRoutine )( unsigned long ulError, unsigned long cbTransferred, OVERLAPPED* pOverlapped, unsigned long ulFlags );

	//--------------------------------------------------------------------------------
	enum WSACompletionType
	{
		NSP_Notify_Immediately = 0,
		NSP_Notify_HWND,
		NSP_Notify_Event,
		NSP_Notify_Port,
		NSP_Notify_APC,
	};

	//--------------------------------------------------------------------------------
	struct WSACompletion
	{
		WSACompletionType Type;
		union 
		{
			struct 
			{
				void* hWnd;
				unsigned int uMsg;
				Cmp_uint_ptr context;
			} WindowMessage;

			struct 
			{
				OVERLAPPED* lpOverlapped;
			} Event;

			struct 
			{
				OVERLAPPED* lpOverlapped;
				fpWSAOverlappedCompletionRoutine lpfnCompletionProc;
			} Apc;

			struct 
			{
				OVERLAPPED* lpOverlapped;
				void* hPort;
				Cmp_ulong_ptr Key;
			} Port;
		} Parameters;
	};

	//--------------------------------------------------------------------------------
	struct PollFD
	{
		Cmp_uint_ptr  fd;
		short   events;
		short   revents;
	};

	struct WSAMsg;

	//--------------------------------------------------------------------------------
	enum WSAESetServiceOp
	{
		RNRServiceRegister = 0,
		RNRServiceDeregister,
		RNRServiceDelete
	};

	//--------------------------------------------------------------------------------
	enum WSCProviderInfoType
	{
		//  InfoType is:                  Info points to:
		ProviderInfoLspCategories, // DWORD (LspCategories)
		ProviderInfoAudit,         // struct WSC_PROVIDER_AUDIT_INFO
	};

	__QCMP_STATIC_CONSTANT( int, FD_SetSize = 64 );

	//--------------------------------------------------------------------------------
	struct FDSet
	{
		unsigned int	fd_count;					// how many are SET?
		Cmp_uint_ptr	fd_array[ FD_SetSize ];		// an array of SOCKETs
	};

	class CSocketEvent;

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CSocket
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CSocket );

		//--------------------------------------------------------------------------------
		enum eType
		{
			Sock_Stream		 = 1,
			Sock_DGram,
			Sock_Raw,
			Sock_ReliablyDeliveredMessage,
			Sock_SeqPacket,
		};

		//--------------------------------------------------------------------------------
		enum eAddressFamily
		{
			AF_Unspecified		= 0,               // unspecified
			AF_Unix				= 1,               // local to host (pipes, portals)
			AF_INet				= 2,               // internetwork: UDP, TCP, etc.
			AF_ImpLink			= 3,               // arpanet imp addresses
			AF_Pup				= 4,               // pup protocols: e.g. BSP
			AF_Chaos			= 5,               // mit CHAOS protocols
			AF_NS				= 6,               // XEROX NS protocols
			AF_IPX				= AF_NS,           // IPX protocols: IPX, SPX, etc.
			AF_ISO				= 7,               // ISO protocols
			AF_OSI				= AF_ISO,          // OSI is ISO
			AF_ECMA				= 8,               // european computer manufacturers
			AF_DataKit			= 9,               // datakit protocols
			AF_CCITT			= 10,              // CCITT protocols, X.25 etc
			AF_SNA				= 11,              // IBM SNA
			AF_DECnet			= 12,              // DECnet
			AF_DLI				= 13,              // Direct data link interface
			AF_LAT				= 14,              // LAT
			AF_HYLink			= 15,              // NSC Hyperchannel
			AF_AppleTalk		= 16,              // AppleTalk
			AF_NetBIOS			= 17,              // NetBios-style addresses
			AF_VoiceView		= 18,              // VoiceView
			AF_FireFox			= 19,              // Protocols from Firefox
			AF_Unknown1			= 20,              // Somebody is using this!
			AF_Ban				= 21,              // Banyan
			AF_ATM				= 22,              // Native ATM Services
			AF_INet6			= 23,              // Internetwork Version 6
			AF_Cluster			= 24,              // Microsoft Wolfpack
			AF_12844			= 25,              // IEEE 1284.4 WG AF
			AF_IRDA				= 26,              // IrDA
			AF_NetDes			= 28,              // Network Designers OSI & gateway
			AF_TCNPROCESS		= 29,
			AF_TCNMESSAGE		= 30,
			AF_ICLFXBM			= 31,
			AF_BTH				= 32,              // Bluetooth RFCOMM/L2CAP protocols
			AF_Link				= 33,
			AF_Max				= 34,
		};

		//--------------------------------------------------------------------------------
		enum eProtocol
		{
			IPProto_IP			= 0,				// dummy for IP 
			IPProto_ICMP		= 1,				// control message protocol 
			IPProto_IGMP		= 2,				// group management protocol
			IPProto_GGP			= 3,				// gateway^2 (deprecated) 
			IPProto_TCP			= 6,				// tcp 
			IPProto_PUP			= 12,				// pup 
			IPProto_UDP			= 17,				// user datagram protocol 
			IPProto_IDP			= 22,				// xns idp 
			IPProto_ND			= 77,				// UNOFFICIAL net disk proto 
			IPProto_RAW			= 255,				// raw IP packet 
			IPProto_MAX			= 256,
		};

		//--------------------------------------------------------------------------------
		enum eFlag
		{
			Flag_Overlapped				= 0x01,
			Flag_MultiPoint_C_Root		= 0x02,
			Flag_MultiPoint_C_Leaf		= 0x04,
			Flag_MultiPoint_D_root		= 0x08,
			Flag_Multipoint_S_Leaf		= 0x10,
			Flag_Access_System_Security	= 0x40,
			Flag_No_Handle_Inherit		= 0x80,
			Flag_Registered_IO			= 0x100,
		};

		//--------------------------------------------------------------------------------
		struct Address
		{
			unsigned short sa_family;
			char sa_data[ 60 ];
		};

		//--------------------------------------------------------------------------------
		struct CSAddrInfo
		{
			Address LocalAddr;
			Address RemoteAddr;
			int iSocketType;
			int iProtocol;
		};

		//--------------------------------------------------------------------------------
		struct SocketAddress
		{
			Address* lpSockaddr;
			int iSockaddrLength;
		};

		//--------------------------------------------------------------------------------
		struct SocketAddressList
		{
			int             iAddressCount;
			SocketAddress   Address[ 1 ];
		};

		//--------------------------------------------------------------------------------
		struct IrDA_SocketAddress
		{
			unsigned short irdaAddressFamily;
			unsigned char  irdaDeviceID[4];
			char	irdaServiceName[25];
		};

		//--------------------------------------------------------------------------------
		// IPv4 Socket address, Internet style
		struct __QOR_INTERFACE( __WINQL ) Internet_SocketAddress
		{
			Internet_SocketAddress( unsigned char ucA, unsigned char ucB, unsigned char ucC, unsigned char ucD, unsigned short usPort = 0 );

			unsigned short sin_family;
			unsigned short sin_port;
			in_addr sin_addr;
			char sin_zero[8];
		};

		static nsCodeQOR::mxGUID WSAID_AcceptEx;

		CSocket();
		CSocket( Cmp_uint_ptr Socket );
		virtual ~CSocket();

		void Create( int iAF, int iType, int iProtocol );
		void Create( int iAF, int iType, int iProtocol, WSAProtocolInfo* pProtocolInfo, unsigned int Group, unsigned long ulFlags );
		int Bind( const Address* pName, int iNamelen );
		int Listen( int iBacklog );
		CSocket Accept( Address* pAddr, int* pAddrlen );
		CSocket Accept( CSocket::Address* pAddr, int* pAddrlen, fpConditionProc pfnCondition, Cmp_ulong_ptr CallbackData );
		int Connect( const Address* name, int iNamelen );
		int Connect( const Address* pName, int iNamelen, WSABuf* pCallerData, WSABuf* pCalleeData, QualityOfService* pSQOS, QualityOfService* pGQOS );
		bool ConnectByList( SocketAddressList* pSocketAddressList, unsigned long* pLocalAddressLength, Address* pLocalAddress, unsigned long* pulRemoteAdressLength, Address* pRemoteAddress, const timeval* pTimeout );
		bool ConnectByName( TCHAR* pNodeName, TCHAR* pServiceName, unsigned long* pulLocalAddressLength, CSocket::Address* pLocalAddress, unsigned long* pulRemoteAddresLength, CSocket::Address* pRemoteAddress, const timeval* pTimeout );
		int Duplicate( unsigned long ulProcessId, WSAProtocolInfo* pProtocolInfo );
		int GetPeerName( Address* pName, int* piNameLen );
		int GetSockName( Address* pName, int* piNameLen );
		int GetSockOpt( int iLevel, int iOptName, char* pOptVal, int* pOptLen );
		int HToNL( unsigned long ulHost, unsigned long* pulNet );
		int HToNS( unsigned short usHost, unsigned short* pusNet );
		int IOCtl( long lCmd, unsigned long* pArg );
		int IOCtl( unsigned long ulIoControlCode, void* pvInBuffer, unsigned long cbInBuffer, void* pvOutBuffer, unsigned long cbOutBuffer, unsigned long* pcbBytesReturned, OVERLAPPED* lpOverlapped, fpWSAOverlappedCompletionRoutine lpCompletionRoutine );
		CSocket JoinLeaf( const CSocket::Address* pName, int iNamelen, WSABuf* pCallerData, WSABuf* pCalleeData, QualityOfService* pSQOS, QualityOfService* pGQOS, unsigned long ulFlags );
		int NToHL( unsigned long ulNet, unsigned long* pulHost );
		int NToHS( unsigned short usNet, unsigned short* pusHost );
		int Receive( char* buf, int len, int flags );
		int Receive( WSABuf* pBuffers, unsigned long ulBufferCount, unsigned long* pulNumberOfBytesRecvd, unsigned long* pulFlags, OVERLAPPED* pOverlapped, fpWSAOverlappedCompletionRoutine pCompletionRoutine );
		int RecvDisconnect( WSABuf* pInboundDisconnectData );
		int ReceiveFrom( char* Buffer, int iLen, int iFlags, Address* pFrom, int* pFromLen );
		int ReceiveFrom( WSABuf* pBuffers, unsigned long ulBufferCount, unsigned long* pulNumberOfBytesRecvd, unsigned long* pulFlags, Address* pFrom, int* pFromLen, OVERLAPPED* pOverlapped, fpWSAOverlappedCompletionRoutine pCompletionRoutine );
		int Send( const char* Buffer, int iLen, int iFlags );
		int Send( WSABuf* pBuffers, unsigned long ulBufferCount, unsigned long* pulNumberOfBytesSent, unsigned long ulFlags, OVERLAPPED* pOverlapped, fpWSAOverlappedCompletionRoutine pCompletionRoutine );
		int SendDisconnect( WSABuf* pOutboundDisconnectData );
		int SendMsg( WSAMsg* pMsg, unsigned long ulFlags, unsigned long* pulNumberOfBytesSent, OVERLAPPED* pOverlapped, fpWSAOverlappedCompletionRoutine pCompletionRoutine );
		int SendTo( const char* Buffer, int iLen, int iFlags, const Address* pTo, int iToLen );
		int SendTo( WSABuf* pBuffers, unsigned long ulBufferCount, unsigned long* pulNumberOfBytesSent, unsigned long ulFlags, const CSocket::Address* pTo, int iToLen, OVERLAPPED* pOverlapped, fpWSAOverlappedCompletionRoutine pCompletionRoutine );
		int SetSockOpt( int iLevel, int iOptName, const char* pOptVal, int iOptLen );
		int Shutdown( int iHow );
		int EnumNetworkEvents( CSocketEvent& EventObject, WSANetworkEvents* pNetworkEvent );
		int EventSelect( CSocketEvent& EventObject, long lNetworkEvents );
		bool GetOverlappedResult( OVERLAPPED* pOverlapped, unsigned long* pcbTransfer, int fWait, unsigned long* pulFlags );
		bool GetQOSByName( WSABuf* pQOSName, QualityOfService* pQOS );
		int AsyncSelect( CWindowHandle& hWnd, unsigned int uiMsg, long lEvent );
		int IsInSet( FDSet* pSet );
		Cmp_uint_ptr ID( void );
		int GetLastError( void );

	protected:

		Cmp_uint_ptr m_Socket;

	private:

		nsWinQAPI::CWS2_32& m_Library;

		__QCS_DECLARE_NONASSIGNABLE( CSocket );
	};

	//--------------------------------------------------------------------------------
	struct WSAQuerySet
	{
		unsigned long	dwSize;
		TCHAR*          lpszServiceInstanceName;
		GUID*			lpServiceClassId;
		WSAVersion*		lpVersion;
		TCHAR*          lpszComment;
		unsigned long   dwNameSpace;
		GUID*			lpNSProviderId;
		TCHAR*          lpszContext;
		unsigned long   dwNumberOfProtocols;
		AFProtocols*	lpafpProtocols;
		TCHAR*          lpszQueryString;
		unsigned long   dwNumberOfCsAddrs;
		CSocket::CSAddrInfo*		lpcsaBuffer;
		unsigned long   dwOutputFlags;
		Blob*			lpBlob;
	};

	//--------------------------------------------------------------------------------
	struct WSAMsg 
	{
		CSocket::Address*       name;              // Remote address 
		int              namelen;           // Remote address length
		WSABuf*          lpBuffers;         // Data buffer array 

#if		(_WIN32_WINNT >= 0x0600)
		unsigned long    dwBufferCount;     // Number of elements in the array
#else
		unsigned long    dwBufferCount;     // Number of elements in the array
#endif//(_WIN32_WINNT>=0x0600)

		WSABuf*          Control;           // Control buffer

#if		(_WIN32_WINNT >= 0x0600)
		unsigned long    dwFlags;           // Flags
#else
		unsigned long    dwFlags;           // Flags 
#endif//(_WIN32_WINNT>=0x0600)

	};

#ifndef __WINQL

	__QOR_INTERFACE( __WINQL ) nsCodeQOR::mxGUID __QCMP_DECLARE_MERGE_INITIALIZERS CSocket::WSAID_AcceptEx		= { 0xb5367df1, 0xcbac, 0x11cf, { 0x95, 0xca, 0x00, 0x80, 0x5f, 0x48, 0xa1, 0x92 } };

#endif//__WINQL

}//nsWin32

#endif//WINQL_COMMS_SOCKET_H_3
