//ServiceLookup.h
//Win32 Service Lookup

#ifndef WINQL_COMMS_SERVICELOOKUP_H_3
#define WINQL_COMMS_SERVICELOOKUP_H_3

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
	class __QOR_INTERFACE( __WINQL ) CServiceLookup
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CServiceLookup );

		CServiceLookup( WSAQuerySet* pqsRestrictions, unsigned long ulControlFlags );
		~CServiceLookup();
		int Next( unsigned long ulControlFlags, unsigned long* pulBufferLength, WSAQuerySet* pqsResults );
		int NSPIoCtl( unsigned long ulControlCode, void* pvInBuffer, unsigned long cbInBuffer, void* pvOutBuffer, unsigned long ulOutBuffer, unsigned long* pcbBytesReturned, WSACompletion* pCompletion );

	private:

		void* m_pHandle;
		int m_iStatus;
		nsWinQAPI::CWS2_32& m_Library;

		CServiceLookup& operator = ( CServiceLookup& );
	};

}//nsWin32

#endif//WINQL_COMMS_SERVICELOOKUP_H_3
