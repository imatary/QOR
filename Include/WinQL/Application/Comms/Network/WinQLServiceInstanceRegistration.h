//ServiceInstanceRegistration.h
//Win32 Service Instance Registration

#ifndef WINQL_COMMS_SERVICEINSTRREG_H_3
#define WINQL_COMMS_SERVICEINSTRREG_H_3

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
	class __QOR_INTERFACE( __WINQL ) CServiceInstanceRegistration
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CServiceInstanceRegistration );

		CServiceInstanceRegistration( bool bPersistent, WSAQuerySet* pqsRegInfo, unsigned long ulControlFlags );
		~CServiceInstanceRegistration();

	private:

		int m_iStatus;
		bool m_bPersistent;
		nsWinQAPI::CWS2_32& m_Library;
		WSAQuerySet* m_pQuerySet;

		CServiceInstanceRegistration& operator = ( const CServiceInstanceRegistration& );
	};

}//nsWin32

#endif//WINQL_COMMS_SERVICEINSTRREG_H_3
