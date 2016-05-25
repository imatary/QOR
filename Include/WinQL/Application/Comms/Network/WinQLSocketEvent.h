//WinQLSocketEvent.h
//Win32 Socket Event

#ifndef WINQL_COMMS_SOCKEVENT_H_3
#define WINQL_COMMS_SOCKEVENT_H_3

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
	class __QOR_INTERFACE( __WINQL ) CSocketEvent
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CSocketEvent );

		CSocketEvent();
		~CSocketEvent();

		unsigned long Handle( void );
		bool Reset( void );
		bool Set( void );

	private:

		unsigned long m_Handle;
		nsWinQAPI::CWS2_32& m_Library;

		CSocketEvent& operator = ( const CSocketEvent& );
	};

}//nsWin32

#endif//WINQL_COMMS_SOCKEVENT_H_3
