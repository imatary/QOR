//WinQLTerminalServices.h

// Copyright Querysoft Limited 2015
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

#ifndef WINQL_TERMINALSERVICES_H_3
#define WINQL_TERMINALSERVICES_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/WinQL.h"
#include "WinQL/CodeServices/WinQLPolicy.h"
#include "WinQL/CodeServices/WinQLSharedRef.h"
#include "WinQL/CodeServices/Text/WinString.h"
#include "WinQL/System/Security/WinQLSecurityDescriptor.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	class __QOR_INTERFACE( __WINQAPI ) CWTSAPI32;
}

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CTermServHelper
	{

	public:
		__QOR_DECLARE_OCLASS_ID( CTermServHelper );

		CTermServHelper();
		CTermServHelper( const CTermServHelper& );
		CTermServHelper& operator = ( const CTermServHelper& );
		~CTermServHelper();
		bool ProcessIdToSessionId( unsigned long dwProcessId, unsigned long* pSessionId );
		bool AppInstallMode( void );
		unsigned long GetActiveConsoleSessionId( void );

	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CTerminalServer
	{
	public:

		//--------------------------------------------------------------------------------
		enum eINFOCLASS
		{
			WTSInitialProgram,
			WTSApplicationName,
			WTSWorkingDirectory,
			WTSOEMId,
			WTSSessionId,
			WTSUserName,
			WTSWinStationName,
			WTSDomainName,
			WTSConnectState,
			WTSClientBuildNumber,
			WTSClientName,
			WTSClientDirectory,
			WTSClientProductId,
			WTSClientHardwareId,
			WTSClientAddress,
			WTSClientDisplay,
			WTSClientProtocolType,
			WTSIdleTime,
			WTSLogonTime,
			WTSIncomingBytes,
			WTSOutgoingBytes,
			WTSIncomingFrames,
			WTSOutgoingFrames,
			WTSClientInfo,
			WTSSessionInfo,
			WTSSessionInfoEx,
			WTSConfigInfo,
			WTSValidationInfo,   // Info Class value used to fetch Validation Information through the WTSQuerySessionInformation
			WTSSessionAddressV4,
			WTSIsRemoteSession
		};

		//--------------------------------------------------------------------------------
		enum eCONFIGCLASS
		{
			WTSUserConfigInitialProgram,
			WTSUserConfigWorkingDirectory,
			WTSUserConfigfInheritInitialProgram,
			WTSUserConfigfAllowLogonTerminalServer,
			WTSUserConfigTimeoutSettingsConnections,
			WTSUserConfigTimeoutSettingsDisconnections,
			WTSUserConfigTimeoutSettingsIdle,
			WTSUserConfigfDeviceClientDrives,
			WTSUserConfigfDeviceClientPrinters,
			WTSUserConfigfDeviceClientDefaultPrinter,
			WTSUserConfigBrokenTimeoutSettings,
			WTSUserConfigReconnectSettings,
			WTSUserConfigModemCallbackSettings,
			WTSUserConfigModemCallbackPhoneNumber,
			WTSUserConfigShadowingSettings,
			WTSUserConfigTerminalServerProfilePath,
			WTSUserConfigTerminalServerHomeDir,
			WTSUserConfigTerminalServerHomeDirDrive,
			WTSUserConfigfTerminalServerRemoteHomeDir,
			WTSUserConfigUser
		};

		//--------------------------------------------------------------------------------
		class __QOR_INTERFACE( __WINQL ) CSession
		{
		public:

			typedef nsCodeQOR::CTLRef< CSession > refType;

			__QOR_DECLARE_OCLASS_ID( CSession );

			CSession( CTerminalServer& Server, unsigned long ulId );
			CSession( const CSession& );
			~CSession();

			//--------------------------------------------------------------------------------
			refType Ref( void )
			{
				return refType( this, false );
			}

			bool SendMessageT( CTString strTitle, CTString strMessage, unsigned long Style, unsigned long Timeout, unsigned long* pResponse, bool bWait );		
			bool QueryInformation( eINFOCLASS WTSInfoClass, TCHAR** ppBuffer, unsigned long* pBytesReturned );
			bool Disconnect( bool bWait );
			bool Logoff( bool bWait );		
			bool QueryUserToken( CRAIISessionHandle::refType& refHandle );

			//--------------------------------------------------------------------------------
			unsigned long ID( void )
			{
				return m_ulID;
			}

		private:

			CSession& operator = ( const CSession& );

			CTerminalServer& m_Server;
			unsigned long m_ulID;

		};

		//--------------------------------------------------------------------------------
		class __QOR_INTERFACE( __WINQL ) CSessionNotification
		{
		public:

			typedef nsCodeQOR::CTLRef< CSessionNotification > refType;

			__QOR_DECLARE_OCLASS_ID( CSessionNotification );

			CSessionNotification( CTerminalServer& Server, COSWindow& Window, bool bAllSessions = false );
			~CSessionNotification();

			//--------------------------------------------------------------------------------
			refType Ref( void )
			{
				return refType( this, false );
			}

			//--------------------------------------------------------------------------------
			bool Status( void )
			{
				return m_bStatus;
			}

		private:

			CSessionNotification();
			CSessionNotification( const CSessionNotification& );
			CSessionNotification& operator = ( const CSessionNotification& );

			COSWindow& m_Window;
			CTerminalServer& m_Server;
			bool m_bStatus;
		};

		//--------------------------------------------------------------------------------
		class __QOR_INTERFACE( __WINQL ) CVirtualChannel
		{
		public:

			//--------------------------------------------------------------------------------
			enum eVIRTUALCLASS 
			{
				WTSVirtualClientData,  // Virtual channel client module data (C2H data)
				WTSVirtualFileHandle
			};

			typedef nsCodeQOR::CTLRef< CVirtualChannel > refType;

			__QOR_DECLARE_OCLASS_ID( CVirtualChannel );

			CVirtualChannel( CTerminalServer& Server, CSession& Session, CAString& strName );
			CVirtualChannel( CTerminalServer& Server, CSession& Session, CAString& strName, unsigned long ulFlags );
			~CVirtualChannel();

			//--------------------------------------------------------------------------------
			refType Ref( void )
			{
				return refType( this, false );
			}

			bool PurgeInput();
			bool PurgeOutput();
			bool Query( eVIRTUALCLASS WtsVirtualClass, void** ppBuffer, unsigned long* pBytesReturned );
			bool Read( unsigned long TimeOut, char* Buffer, unsigned long BufferSize, unsigned long* pBytesRead );
			bool Write( char* Buffer, unsigned long Length, unsigned long* pBytesWritten );

		private:

			CVirtualChannel();
			CVirtualChannel( const CVirtualChannel& );
			CVirtualChannel& operator = ( const CVirtualChannel& );

			CTerminalServer& m_Server;
			void* m_hChannelHandle;
			CAString m_strName;
		};

		//--------------------------------------------------------------------------------
		enum eConnectStateClass
		{
			WTSActive,              // User logged on to WinStation
			WTSConnected,           // WinStation connected to client
			WTSConnectQuery,        // In the process of connecting to client
			WTSShadow,              // Shadowing another WinStation
			WTSDisconnected,        // WinStation logged on without client
			WTSIdle,                // Waiting for client to connect
			WTSListen,              // WinStation is listening for connection
			WTSReset,               // WinStation is being reset
			WTSDown,                // WinStation is down due to error
			WTSInit,                // WinStation in initialization
		};

		//--------------------------------------------------------------------------------
		struct SessionInfo
		{
			unsigned long SessionId;		// session id
			CTString strWinStationName;		// name of WinStation this session is connected to
			eConnectStateClass State;		// connection state (see enum)
		};

		//--------------------------------------------------------------------------------
		struct ProcessInfo
		{
			unsigned long SessionId;
			unsigned long ProcessId;
			CTString strProcessName;
			//CSID UserSID;
		};

		CTerminalServer( const CTString& strName );
		virtual ~CTerminalServer();

		__QOR_DECLARE_OCLASS_ID( CTerminalServer );
		
		CSessionNotification::refType CreateSessionNotification( COSWindow& Window, bool bAllSessions = false );
		bool EnumerateSessions( nsCodeQOR::CTArray< SessionInfo >& Sessions );
		bool TerminateProcess( unsigned long ulProcessId, unsigned long ulExitCode );
		bool EnumerateProcesses( nsCodeQOR::CTArray< ProcessInfo >& Processes );
		bool ShutdownSystem( unsigned long ShutdownFlag );	
		bool SetUserConfig( CTString& strUserName, eCONFIGCLASS ConfigClass, CTString& strBuffer, unsigned long ulDataLength );
		bool QueryUserConfig( CTString& strUserName, eCONFIGCLASS ConfigClass, nsCodeQOR::CTLRef< byte >& refData );
		bool WaitSystemEvent( unsigned long EventMask, unsigned long* pEventFlags );

	protected:

		CTString m_strName;
		nsWinQAPI::CWTSAPI32* m_pWTSAPI;
		void* m_Handle;

	private:

		CTerminalServer();
		CTerminalServer( const CTerminalServer& );
		CTerminalServer& operator = ( const CTerminalServer& );
	};


	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CTSRemoteServer : public CTerminalServer
	{
	public:

		typedef nsCodeQOR::CTLRef< CTSRemoteServer > refType;

		__QOR_DECLARE_OCLASS_ID( CTSRemoteServer );

		CTSRemoteServer( const CTString& strName );
		~CTSRemoteServer();
		
		//--------------------------------------------------------------------------------
		refType Ref( void )
		{
			return refType( this );
		}

	private:

		CTSRemoteServer();
		CTSRemoteServer( const CTSRemoteServer& );
		CTSRemoteServer& operator = ( const CTSRemoteServer& );

	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CTSLocalServer : public CTerminalServer
	{
		QOR_PP_WINQL_SHARED;

	public:

		//--------------------------------------------------------------------------------
		struct __QOR_INTERFACE( __WINQL ) CListenerConfig
		{
			unsigned long version;
			unsigned long fEnableListener;
			unsigned long MaxConnectionCount;
			unsigned long fPromptForPassword;
			unsigned long fInheritColorDepth;
			unsigned long ColorDepth;
			unsigned long fInheritBrokenTimeoutSettings;
			unsigned long BrokenTimeoutSettings;

			unsigned long fDisablePrinterRedirection;
			unsigned long fDisableDriveRedirection;
			unsigned long fDisableComPortRedirection;
			unsigned long fDisableLPTPortRedirection;
			unsigned long fDisableClipboardRedirection;
			unsigned long fDisableAudioRedirection;
			unsigned long fDisablePNPRedirection;
			unsigned long fDisableDefaultMainClientPrinter;

			unsigned long LanAdapter;
			unsigned long PortNumber;

			unsigned long fInheritShadowSettings;
			unsigned long ShadowSettings;

			unsigned long TimeoutSettingsConnection;
			unsigned long TimeoutSettingsDisconnection;
			unsigned long TimeoutSettingsIdle;
   
			unsigned long SecurityLayer;
			unsigned long MinEncryptionLevel;   
			unsigned long UserAuthentication;

			CTString m_strComment;
			CTString m_strLogonUserName;
			CTString m_strLogonDomain;
			CTString m_strWorkDirectory;
			CTString m_strInitialProgram;
		};

		//--------------------------------------------------------------------------------
		class __QOR_INTERFACE( __WINQL ) CListener : public CListenerConfig
		{

		public:

			typedef nsCodeQOR::CTLRef< CListener > refType;

			__QOR_DECLARE_OCLASS_ID( CListener );

			CListener( CTSLocalServer& Server, CTString& strName );
			CListener( const CListener& );
			CListener( CTSLocalServer& Server, const CListenerConfig& );
			CListener& operator = ( const CListenerConfig& );
			~CListener();

			bool GetSecurity( unsigned long ulSecurityInformation, CSecurityDescriptor** ppDescriptor );
			bool SetSecurity( unsigned long ulSecurityInformation, CSecurityDescriptor& SecurityDescriptor );
			bool QueryConfig();
			bool Create( void );
			bool Update( void );

			CTString m_strName;

		private:

			CListener();
			CListener& operator = ( const CListener& );

			CTSLocalServer& m_Server;

			void AssignFromConfig( void* pConfig );
			void AssignToConfig( void* pConfig );

		};

		typedef CSharedRef< CTSLocalServer > refType;

		__QOR_DECLARE_OCLASS_ID( CTSlocalServer );

		CTSLocalServer();
		~CTSLocalServer();
		
		//Local only
		bool EnumerateListeners( nsCodeQOR::CTArray< CListener::refType >& Listeners );
		bool GetChildSessionId( unsigned long& ulSessionId );

		//--------------------------------------------------------------------------------
		refType Ref( void )
		{
			return refType( this );
		}

	private:

		CTSLocalServer( const CTSLocalServer& );
		CTSLocalServer& operator = ( const CTSLocalServer& );
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CTerminalServices : public CTermServHelper
	{
		QOR_PP_WINQL_SHARED;

	public:

		//--------------------------------------------------------------------------------
		class CRemoteControlSession
		{
		public:

			typedef nsCodeQOR::CTLRef< CRemoteControlSession > refType;

			__QOR_DECLARE_OCLASS_ID( CRemoteControlSession );

			CRemoteControlSession( CTString& strTargetServerName, unsigned long ulTargetLogonId, unsigned char HotkeyVk, unsigned short usHotkeyModifiers );
			~CRemoteControlSession();

			//--------------------------------------------------------------------------------
			bool Status( void )
			{
				return m_bStatus;
			}

			//--------------------------------------------------------------------------------
			refType Ref( void )
			{
				return refType( this, false );
			}

		private:

			CRemoteControlSession( const CRemoteControlSession& );
			CRemoteControlSession& operator = ( const CRemoteControlSession& );

			nsWinQAPI::CWTSAPI32* m_pWTSAPI;
			bool m_bStatus;
			unsigned long m_ulLogonId;
		};

		typedef CSharedRef< CTerminalServices > refType;

		__QOR_DECLARE_OCLASS_ID( CTerminalServices );

		CTerminalServices();
		~CTerminalServices();

		bool EnumerateServers( CTString& strDomain, nsCodeQOR::CTArray< CTString >& ServerNames );
		bool ConnectSession( unsigned long LogonId, unsigned long TargetLogonId, CTString strPassword, bool bWait );
		bool EnableChildSessions( bool bEnable );
		bool IsChildSessionsEnabled( void );
		CTSLocalServer::refType LocalServer( void );
		CRemoteControlSession::refType CreateRemoteControlSession( CTString& strTargetServer, unsigned long ulTargetLogonId, unsigned char HotkeyVk, unsigned short ushotkeyModifiers );
		CTSRemoteServer::refType RemoteServer( const CTString& strName );

	private:

		CTerminalServices( const CTerminalServices& );
		CTerminalServices& operator = ( const CTerminalServices& );

		nsWinQAPI::CWTSAPI32* m_pWTSAPI;
		CTSLocalServer m_LocalServer;
		
	};

}//nsWin32

#endif//WINQL_TERMINALSERVICES_H_3