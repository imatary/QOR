//WinQLDDE.h

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

//Win32 Dynamic Data Exchange

//These classes are actually wrapping the DDEML API. Before we get there we need basic Windows Message driven DDE

#ifndef WINQL_IPC_DDE_H_3
#define WINQL_IPC_DDE_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "CodeQOR/Macros/codingmacros.h"
#include "WinQL/Definitions/Handles.h"
#include "WinQL/Definitions/Security.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	class __QOR_INTERFACE( __WINQAPI ) CUser32;
}

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	typedef unsigned char SECURITY_CONTEXT_TRACKING_MODE, *PSECURITY_CONTEXT_TRACKING_MODE;

	//--------------------------------------------------------------------------------
	typedef struct _SECURITY_QUALITY_OF_SERVICE 
	{
		unsigned long Length;
		SECURITY_IMPERSONATION_LEVEL ImpersonationLevel;
		SECURITY_CONTEXT_TRACKING_MODE ContextTrackingMode;
		unsigned char EffectiveOnly;
	} SECURITY_QUALITY_OF_SERVICE, * PSECURITY_QUALITY_OF_SERVICE;

	//--------------------------------------------------------------------------------
	typedef struct tagCONVCONTEXT 
	{
		unsigned int cb;             /* set to sizeof(CONVCONTEXT) */
		unsigned int wFlags;         /* none currently defined. */
		unsigned int wCountryID;     /* country/region code for topic/item strings used. */
		int iCodePage;      /* codepage used for topic/item strings. */
		unsigned long dwLangID;       /* language ID for topic/item strings. */
		unsigned long dwSecurity;     /* Private security code. */
		SECURITY_QUALITY_OF_SERVICE qos;  /* client side's quality of service */
	} CONVCONTEXT, *PCONVCONTEXT;

	//--------------------------------------------------------------------------------
	typedef struct tagCONVINFO 
	{
		unsigned long cb;           /* sizeof(CONVINFO)  */
		Cmp_ulong_ptr hUser;		/* user specified field  */
		void* hConvPartner;			/* hConv on other end or 0 if non-ddemgr partner  */
		void* hszSvcPartner;		/* app name of partner if obtainable  */
		void* hszServiceReq;		/* AppName requested for connection  */
		void* hszTopic;				/* Topic name for conversation  */
		void* hszItem;				/* transaction item name or NULL if quiescent  */
		unsigned int wFmt;          /* transaction format or NULL if quiescent  */
		unsigned int wType;         /* XTYP_ for current transaction  */
		unsigned int wStatus;       /* ST_ constant for current conversation  */
		unsigned int wConvst;       /* XST_ constant for current transaction  */
		unsigned int wLastError;    /* last transaction error.  */
		void*		 hConvList;		/* parent hConvList if this conversation is in a list */
		nsWin32::CONVCONTEXT ConvCtxt;  /* conversation context */
		void*		 hwnd;          /* window handle for this conversation */
		void*		 hwndPartner;   /* partner window handle for this conversation */
	} CONVINFO, *PCONVINFO;

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CDDEAppInstance
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CDDEAppInstance );

		CDDEAppInstance( unsigned long afCmd, int* pbResult = 0 );
		virtual ~CDDEAppInstance();
		unsigned long ID( void );
		static void* __QCMP_STDCALLCONVENTION CallBack( unsigned int/*wType*/, unsigned int/*wFmt*/, void* /*hConv*/, void* /*hsz1*/, void* /*hsz2*/, void* /*hData*/, Cmp_ulong_ptr /*dwData1*/, Cmp_ulong_ptr /*dwData2*/ );
		unsigned int GetLastError( void );

	protected:

		int* m_pbResult;
		unsigned long m_idInst;
		unsigned int m_uiInitResult;

	private:

		nsWinQAPI::CUser32& m_User32Library;

		CDDEAppInstance();
		__QCS_DECLARE_NONCOPYABLE( CDDEAppInstance );
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CDDEStringItem
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CDDEStringItem );

		CDDEStringItem( CDDEAppInstance& Inst, TCHAR* psz, int iCodePage, int* pbResult = 0 );
		virtual ~CDDEStringItem();
		void* operator()( void );
		bool operator == ( CDDEStringItem& Cmp2 );
		unsigned long Query( TCHAR* psz, unsigned long cchMax, int iCodePage );
		bool Keep( void );

	protected:

		int* m_pbResult;
		CDDEAppInstance& m_Inst;
		void* m_hItem;

	private:

		nsWinQAPI::CUser32& m_User32Library;

		CDDEStringItem();
		__QCS_DECLARE_NONCOPYABLE( CDDEStringItem );
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CDDEDataItem
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CDDEDataItem );

		CDDEDataItem( CDDEAppInstance& Inst, unsigned char* pSrc, unsigned long cb, unsigned long cbOff, void* hszItem, unsigned int wFmt, unsigned int afCmd, int* pbResult = 0 );
		virtual ~CDDEDataItem();
		void* operator()( void );
		unsigned long Get( unsigned char* pDst, unsigned long cbMax, unsigned long cbOff );

	protected:
			
		CDDEAppInstance& m_Inst;
		int* m_pbResult;
		void* m_hData;
		bool m_bOwned;

	private:

		nsWinQAPI::CUser32& m_User32Library;

		CDDEDataItem();
		__QCS_DECLARE_NONCOPYABLE( CDDEDataItem );
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CDDEDataAccess
	{
	public:
			
		__QOR_DECLARE_OCLASS_ID( CDDEDataAccess );

		CDDEDataAccess( CDDEAppInstance& Inst, void* hData, int* pbResult = 0 );
		virtual ~CDDEDataAccess();
		unsigned char* Data( void );
		unsigned long Size( void );

	protected:

		CDDEAppInstance& m_Inst;
		int* m_pbResult;
		unsigned char* m_pData;
		unsigned long m_cbDataSize;
		void* m_hData;

	private:

		nsWinQAPI::CUser32& m_User32Library;

		CDDEDataAccess();
		__QCS_DECLARE_NONCOPYABLE( CDDEDataAccess );
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CDDEClient
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CDDEClient );

		//--------------------------------------------------------------------------------
		class __QOR_INTERFACE( __WINQL ) CConversation
		{
		public:

			__QOR_DECLARE_OCLASS_ID( CConversation );
				
			CConversation( CDDEAppInstance& Inst, void* hszService, void* hszTopic, nsWin32::CONVCONTEXT* pContext = 0, int* pbResult = 0 );
			void Reconnect( void );
			virtual ~CConversation();
			void* operator()( void );
			bool EnableCallback( CDDEAppInstance& Inst, unsigned int wCmd );
			bool ImpersonateClient( void );
			unsigned int QueryInfo( unsigned long idTransaction, nsWin32::PCONVINFO pConvInfo );
			bool SetUserHandle( unsigned long idTransaction, Cmp_ulong_ptr hUser );

		protected:

			CDDEAppInstance& m_Inst;
			int* m_pbResult;
			void* m_hConv;
			nsWin32::CONVCONTEXT m_Context;

		private:

			nsWinQAPI::CUser32& m_User32Library;

			CConversation();
			__QCS_DECLARE_NONCOPYABLE( CConversation );

		};

		//--------------------------------------------------------------------------------
		class __QOR_INTERFACE( __WINQL ) CConversationList
		{
		public:

			__QOR_DECLARE_OCLASS_ID( CConversationList );

			CConversationList( CDDEAppInstance& Inst, void* hszService, void* hszTopic, nsWin32::CONVCONTEXT* pContext = 0, int* pbResult = 0 );
			virtual ~CConversationList();
			void* operator()( void );
			void* QueryNextServer( void* hConvPrev );

		protected:

			CDDEAppInstance& m_Inst;
			int* m_pbResult;
			void* m_hConvList;
			nsWin32::CONVCONTEXT m_Context;

		private:

			nsWinQAPI::CUser32& m_User32Library;

			CConversationList();
			__QCS_DECLARE_NONCOPYABLE( CConversationList );
		};

		//--------------------------------------------------------------------------------
		class __QOR_INTERFACE( __WINQL ) CTransaction
		{
		public:

			__QOR_DECLARE_OCLASS_ID( CTransaction );

			CTransaction( CDDEAppInstance& Inst, unsigned char* pData, unsigned long cbData, void* hConv, void* hszItem, unsigned int wFmt, unsigned int wType, unsigned long dwTimeout, int* pResult = 0 );
			virtual ~CTransaction();

		protected:

			bool m_bCompleted;
			void* m_hConv;
			void* m_hData;
			unsigned long m_dwResult;
			unsigned long m_dwTransaction;
			int* m_pResult;
			CDDEAppInstance& m_Inst;

		private:

			nsWinQAPI::CUser32& m_User32Library;

			CTransaction();
			__QCS_DECLARE_NONCOPYABLE( CTransaction );
			
		};
			
		CDDEClient();
		virtual ~CDDEClient();

	private:

		__QCS_DECLARE_NONCOPYABLE( CDDEClient );
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CDDEServer
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CDDEServer );

		CDDEServer();
		virtual ~CDDEServer();
		bool NameService( CDDEAppInstance& Inst, unsigned int hsz1, unsigned int hsz2, unsigned int afCmd );
		bool PostAdvise( CDDEAppInstance& Inst, void* hszTopic, void* hszItem );

	private:

		nsWinQAPI::CUser32& m_User32Library;

		__QCS_DECLARE_NONCOPYABLE( CDDEServer );

	};

}//nsWin32

#endif//WINQL_IPC_DDE_H_3
