//WinQLBluetooth.cpp

// Copyright Querysoft Limited 2016
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

//WinQL Bluetooth Subsystem

#include "WinQL/WinQL.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "SystemQOR/System.h"
#include "WinQL/Application/WinQLApplication.h"
#include "WinQL/Application/Subsystems/WinQLBluetooth.h"
#include "WinQL/System/Devices/Interfaces/WinQLDeviceInterfaceClass.h"
#include "WinQL/System/WinQLSystem.h"

#include "WinQAPI/Kernel32.h"
#include "WinQAPI/BthProps.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_EXTERNAL_FACTORY( CBluetooth, 0x38f0f25a, 0xcf5, 0x4103, 0x8f, 0x80, 0xc6, 0xd0, 0x2a, 0x16, 0x23, 0x8a );

	__QOR_IMPLEMENT_OCLASS_LUID( CBluetooth::CHostWindowClass );

	CBluetooth::CHostWindowClass CBluetooth::s_WindowClass;

	//--------------------------------------------------------------------------------
	CBluetooth::CHostWindowClass::CHostWindowClass()
	{
		Preinitialise();
		SetOwnDC( true );
		SetHRedrawTrigger( true );
		SetVRedrawTrigger( true );
		m_hInstance = const_cast< ImageDOSHeader* >( &__ImageBase );
		Register();
	}

	//--------------------------------------------------------------------------------
	const TCHAR* CBluetooth::CHostWindowClass::Name()
	{
		_WINQ_FCONTEXT( "CBluetooth::CHostWindowClass::Name" );
		return _TXT( "WinQLBluetoothHostWindowClass" );
	};

	//--------------------------------------------------------------------------------
	CBluetooth::CHostWindowClass::~CHostWindowClass()
	{
	}





	//--------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID( CBluetooth::CDeviceChange );

	//--------------------------------------------------------------------------------
	CBluetooth::CDeviceChange::CDeviceChange( CBluetooth& Host, nsMammut::CModel* pModelItem, nsQOR::CController::ref_type Parent ) : CDeviceChangeController( pModelItem, Parent ), m_Host( Host )
	{
		_WINQ_FCONTEXT( "CBluetoothDeviceChangeController::CBluetoothDeviceChangeController" );
	}

	//--------------------------------------------------------------------------------
	CBluetooth::CDeviceChange::~CDeviceChange()
	{
		_WINQ_FCONTEXT( "CBluetoothDeviceChangeController::~CBluetoothDeviceChangeController" );
	}

	//--------------------------------------------------------------------------------
	long CBluetooth::CDeviceChange::OnDBTCustomEvent( sDeviceBroadcastHeader* pDeviceBroadcastHeader )
	{
		_WINQ_FCONTEXT( "CBluetoothDeviceChangeController::OnDBTCustomEvent" );
		long lResult = 0;
		if( pDeviceBroadcastHeader && pDeviceBroadcastHeader->ulDeviceType == CNotificationFilter::eNotifyHandle )
		{
			sDeviceBroadcastHandle* pDeviceBroadcastHandle = reinterpret_cast< sDeviceBroadcastHandle* >( pDeviceBroadcastHeader );

			if( pDeviceBroadcastHandle )
			{
				void* pRadioHandle = pDeviceBroadcastHandle->DeviceHandle;

				if( memcmp( &pDeviceBroadcastHandle->EventGUID, &CBluetoothRadio::GUID_BLUETOOTH_HCI_EVENT, sizeof( nsCodeQOR::mxGUID ) ) == 0 )
				{
					//HCI Event
					BluetoothHCIEventInfo* pData = reinterpret_cast< BluetoothHCIEventInfo* >( pDeviceBroadcastHandle->data );
					lResult = m_Host.OnHCIEvent( pData, pRadioHandle );
				}
				else if( memcmp( &pDeviceBroadcastHandle->EventGUID, &CBluetoothRadio::GUID_BLUETOOTH_L2CAP_EVENT, sizeof( nsCodeQOR::mxGUID ) ) == 0 )
				{
					//L2CAP Event
					BluetoothL2CAPEventInfo* pData = reinterpret_cast< BluetoothL2CAPEventInfo* >( pDeviceBroadcastHandle->data );
					lResult = m_Host.OnL2CAPEvent( pData, pRadioHandle );
				}
				else if( memcmp( &pDeviceBroadcastHandle->EventGUID, &CBluetoothRadio::GUID_BLUETOOTH_RADIO_IN_RANGE, sizeof( nsCodeQOR::mxGUID ) ) == 0 )
				{
					//In Range
					BluetoothRadioInRange* pData = reinterpret_cast< BluetoothRadioInRange* >( pDeviceBroadcastHandle->data );
					lResult = m_Host.OnDeviceInRange( pData, pRadioHandle );
				}
				else if( memcmp( &pDeviceBroadcastHandle->EventGUID, &CBluetoothRadio::GUID_BLUETOOTH_RADIO_OUT_OF_RANGE, sizeof( nsCodeQOR::mxGUID ) ) == 0 )
				{
					//Out of Range
					BluetoothAddress* pData = reinterpret_cast< BluetoothAddress* >( pDeviceBroadcastHandle->data );
					lResult = m_Host.OnDeviceOutOfRange( pData, pRadioHandle );
				}
			}
		}
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CBluetooth::CDeviceChange::OnDeviceChange( COSWindow& Window, Cmp_uint_ptr wParam, Cmp_long_ptr lParam )
	{
		_WINQ_FCONTEXT( "CDeviceChange::OnDeviceChange" );

		switch( wParam )
		{
		case 0x0019://DBT_CONFIGCHANGECANCELLED
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		case 0x0018://DBT_CONFIGCHANGED
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		case 0x8006://DBT_CUSTOMEVENT
			return OnDBTCustomEvent( reinterpret_cast< sDeviceBroadcastHeader* >( lParam ) );
			break;
		case 0x8000://DBT_DEVICEARRIVAL
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		case 0x8001://DBT_DEVICEQUERYREMOVE
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		case 0x8002://DBT_DEVICEQUERYREMOVEFAILED
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		case 0x8004://DBT_DEVICEREMOVECOMPLETE
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		case 0x8003://DBT_DEVICEMOVEPENDING
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		case 0x8005://DBT_DEVICETYPESPECIFIC
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		case 0x0007://DBT_DEVNODES_CHANGED
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		case 0x0017://DBT_QUERYCHANGECONFIG
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		case 0xFFFF://DBT_USERDEFINED
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		}
		return 0;
	}






	//--------------------------------------------------------------------------------
	CBluetooth::CBluetooth() : nsQOR::CSubSystem(), m_Library( nsWinQAPI::CBthProps::Instance() ), m_pHostWindow( 0 ), m_DeviceChangeController( *this, 0, 0 ), m_ScanState( eInitial )
	{
	}

	//--------------------------------------------------------------------------------
	CBluetooth::~CBluetooth()
	{
	}

	//--------------------------------------------------------------------------------
	void CBluetooth::Setup( nsQOR::IApplication& Application )
	{
		//CWin32Application& WindowsApp = dynamic_cast<CWin32Application&>( Application );

		unsigned long StyleEx = COSWindow::eWSExAppWindow;
		unsigned long Style = COSWindow::eWSOverlapped;
		m_pHostWindow = new COSWindow( &s_WindowClass, StyleEx, _TXT( "WinQLBluetoothHostWindow" ), Style, 0, 0, 640, 480, 0, 0, ThisProcess(), 0 );

		if( m_pHostWindow )
		{
			m_BaseWindowController.DeviceChange.Configure( &m_DeviceChangeController );
			m_pHostWindow->Controller( &m_BaseWindowController );
		}

		if( m_VecRadios.size() == 0 )
		{
			EnumerateRadios();
		}

		for( VecRadiosType::iterator it = m_VecRadios.begin(); it != m_VecRadios.end(); it++ )
		{
			( *it )->EnableNotifications( m_pHostWindow->Handle()->AsHandle(), true );
		}

		//CBluetoothHostMessageHandler MessageHandler( *this );
		//MessageHandler.MessageLoop();
	}

	//--------------------------------------------------------------------------------
	void CBluetooth::Shutdown( nsQOR::IApplication& Application )
	{
		//CWin32Application& WindowsApp = dynamic_cast<CWin32Application&>( Application );
		delete m_pHostWindow;
		m_pHostWindow = 0;
	}

	//--------------------------------------------------------------------------------
	void CBluetooth::EnumerateRadios( void )
	{
		_WINQ_FCONTEXT( "CBluetooth::EnumerateRadios" );
		CDeviceInterfaceClass::refType BluetoothRadios = TheSystem().As< nsWin32::CSystem >()->Devices( QOR_PP_SHARED_OBJECT_ACCESS ).InterfaceClassFromGUID( CDeviceManager::GUID_BTHPORT_DEVICE_INTERFACE );

		if( !BluetoothRadios.IsNull() )
		{
			CDeviceInterfaceClass::interface_iterator it = BluetoothRadios->Interfaces().begin();
			while( it != BluetoothRadios->Interfaces().end() )
			{
				CBluetoothRadio::refType BluetoothRadio = ( *it ).As< CBluetoothRadio >();

				if( !BluetoothRadio.IsNull() )
				{
					m_VecRadios.push_back( BluetoothRadio );

					if( BluetoothRadio->GetDeviceFile() )
					{
						m_MapRadioHandles.insert( std::make_pair( BluetoothRadio->GetDeviceFile()->Handle()->Use(), BluetoothRadio.operator CBluetoothRadio*( ) ) );
					}
				}
				it++;
			}
		}
	}

	//--------------------------------------------------------------------------------
	CBluetoothRadio::refType CBluetooth::RadioFromHandle( void* pRadioHandle )
	{
		CBluetoothRadio::refType Radio;

		HandleRadioMapType::const_iterator it = m_MapRadioHandles.find( pRadioHandle );
		if( it != m_MapRadioHandles.end() )
		{
			Radio = ( *it ).second->Ref();
		}
		return Radio;
	}

	//--------------------------------------------------------------------------------
	long CBluetooth::OnHCIEvent( BluetoothHCIEventInfo* pEventInfo, void* pRadioHandle )
	{
		if( pEventInfo )
		{
			AddrDeviceMapType::iterator it = m_MapRemoteDevices.find( pEventInfo->bthAddress );
			if( it != m_MapRemoteDevices.end() )
			{
				CBluetoothRemoteDevice::refType RemoteDevice = ( *it ).second->Ref();

				if( !RemoteDevice.IsNull() )
				{
					switch( pEventInfo->connected )
					{
					case 0:		//Disconnect
						RemoteDevice->OnDisconnect();
						break;
					case 1:		//Connect
						RemoteDevice->OnConnect( static_cast< CBluetoothRemoteDevice::eConnectionType >( pEventInfo->connectionType ) );	//Connection type 1 == ACL, 2 == SCO
						break;
					}
				}
			}
		}
		return 1;
	}

	//--------------------------------------------------------------------------------
	long CBluetooth::OnL2CAPEvent( BluetoothL2CAPEventInfo* pEventInfo, void* pRadioHandle )
	{
		if( pEventInfo )
		{
			AddrDeviceMapType::iterator it = m_MapRemoteDevices.find( pEventInfo->bthAddress );
			if( it != m_MapRemoteDevices.end() )
			{
				CBluetoothRemoteDevice::refType RemoteDevice = ( *it ).second->Ref();

				RemoteDevice->OnL2CAPEvent( pEventInfo, RadioFromHandle( pRadioHandle ) );
			}
		}
		return 1;
	}

	//--------------------------------------------------------------------------------
	long CBluetooth::OnDeviceInRange( BluetoothRadioInRange* pEventInfo, void* pRadioHandle )
	{
		if( pEventInfo )
		{
			AddrDeviceMapType::iterator it = m_MapRemoteDevices.find( pEventInfo->deviceInfo.address );
			if( it != m_MapRemoteDevices.end() )
			{
				CBluetoothRemoteDevice::refType RemoteDevice = ( *it ).second->Ref();

				RemoteDevice->OnInRange( pEventInfo->deviceInfo, pEventInfo->previousDeviceFlags, RadioFromHandle( pRadioHandle ) );
			}
			else
			{
				CBluetoothRemoteDevice::refType RemoteDevice( new CBluetoothRemoteDevice, true );

				m_MapRemoteDevices.insert( std::make_pair( pEventInfo->deviceInfo.address, RemoteDevice ) );
				RemoteDevice->OnInRange( pEventInfo->deviceInfo, pEventInfo->previousDeviceFlags, RadioFromHandle( pRadioHandle ) );
			}
		}
		return 1;
	}

	//--------------------------------------------------------------------------------
	long CBluetooth::OnDeviceOutOfRange( BluetoothAddress* pEventInfo, void* pRadioHandle )
	{
		if( pEventInfo )
		{
			AddrDeviceMapType::iterator it = m_MapRemoteDevices.find( pEventInfo->ullLong );
			if( it != m_MapRemoteDevices.end() )
			{
				CBluetoothRemoteDevice::refType RemoteDevice = ( *it ).second->Ref();

				RemoteDevice->OnOutOfRange();
			}
		}
		return 1;
	}

}//nsWin32