//WinQLAddressRegistration.h
//Win32 Address Registration

#ifndef WINQL_COMMS_ADDRREG_H_3
#define WINQL_COMMS_ADDRREG_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQLSocket.h"
#include "SystemQOR/MSWindows/types/time_types.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	class __QOR_INTERFACE( __WINQAPI ) CWS2_32;
}

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CAddressRegistration
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CAddressRegistration );

		CAddressRegistration( const TCHAR* pName, const TCHAR* pServiceName, CSocket::Address* pAddresses, unsigned long ulAddressCount, Blob* pBlob, unsigned long ulFlags, unsigned long ulNameSpace, GUID* pNspId, bool bPersistent = false );
		~CAddressRegistration();

	private:

		int m_iStatus;
		bool m_bPersistent;
		nsWinQAPI::CWS2_32& m_Library;
		const TCHAR* m_pName;
		const TCHAR* m_pServiceName;
		unsigned long m_ulFlags;
		unsigned long m_ulNameSpace;
		GUID* m_pNspId;

		CAddressRegistration& operator = ( const CAddressRegistration& );
	};

}//nsWin32

#endif//WINQL_COMMS_ADDRREG_H_3
