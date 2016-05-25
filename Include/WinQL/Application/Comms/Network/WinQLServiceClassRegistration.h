//ServiceClassRegistration.h
//Win32 Service Class Registration

#ifndef WINQL_COMMS_SERVICECLASSRREG_H_3
#define WINQL_COMMS_SERVICECLASSRREG_H_3

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
	class __QOR_INTERFACE( __WINQL ) CServiceClassRegistration
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CServiceClassRegistration );

		CServiceClassRegistration( WSAServiceClassInfo* pServiceClassInfo, bool bPersistent );
		~CServiceClassRegistration();

	private:

		int m_iStatus;
		bool m_bPersistent;
		GUID* m_pGUID;
		nsWinQAPI::CWS2_32& m_Library;

		CServiceClassRegistration& operator = ( const CServiceClassRegistration& );
	};

}//nsWin32

#endif//WINQL_COMMS_SERVICECLASSRREG_H_3
