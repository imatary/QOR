//WinQLProviderChangeNotification.h
//Win32 Provider Change Notification

#ifndef WINQL_COMMS_PROVCHANGENOTIFICATION_H_3
#define WINQL_COMMS_PROVCHANGENOTIFICATION_H_3

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
	class __QOR_INTERFACE( __WINQL ) CProviderChangeNotification
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CProviderChangeNotification );

		CProviderChangeNotification( OVERLAPPED* pOverlapped, fpWSAOverlappedCompletionRoutine pCompletionRoutine );
		~CProviderChangeNotification();

	private:

		int m_iStatus;
		void* m_Handle;
		nsWinQAPI::CWS2_32& m_Library;

		CProviderChangeNotification& operator = ( const CProviderChangeNotification& );
	};

}//nsWin32

#endif//WINQL_COMMS_PROVCHANGENOTIFICATION_H_3
