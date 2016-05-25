//WinQLDeviceManager.cpp

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

#include "WinQL/CodeServices/WinQLPolicy.h"
#include "WinQL/Application/Threading/WinQLCriticalSection.h"
#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/CodeServices/Text/WinString.h"
#include "WinQL/System/Devices/WinQLDeviceManager.h"
#include "WinQL/System/Devices/USB/WinQLUSBHub.h"
#include "WinQL/Definitions/Constants.h"
#include "WinQL/Definitions/Interfaces.h"
#include "WinQL/GUI/Window.h"
#include "WinQAPI/SetupAPI.h"
#include "WinQAPI/psapi.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	__QOR_IMPLEMENT_OCLASS_LUID( CDeviceManager );

	//1394 and 16883 devices
	nsCodeQOR::mxGUID CDeviceManager::BUS1394_CLASS_GUID					= { 0x6BDD1FC1, 0x810F, 0x11d0, { 0xBE, 0xC7, 0x08, 0x00, 0x2B, 0xE2, 0x09, 0x2F } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_61883_CLASS						= { 0x7EBEFBC0, 0x3200, 0x11d2, { 0xB4, 0xC2, 0x00, 0xA0, 0xC9, 0x69, 0x7D, 0x07 } };

	//Battery and ACPI devices
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVICE_APPLICATIONLAUNCH_BUTTON	= { 0x629758EE, 0x986E, 0x4D9E, { 0x8E, 0x47, 0xDE, 0x27, 0xF8, 0xAB, 0x05, 0x4D } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVICE_BATTERY					= { 0x72631E54, 0x78A4, 0x11D0, { 0xBC, 0xF7, 0x00, 0xAA, 0x00, 0xB7, 0xB3, 0x2A } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVICE_LID						= { 0x4AFA3D52, 0x74A7, 0x11d0, { 0xbe, 0x5e, 0x00, 0xA0, 0xC9, 0x06, 0x28, 0x57 } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVICE_MEMORY					= { 0x3FD0F03D, 0x92E0, 0x45FB, { 0xB7, 0x5C, 0x5E, 0xD8, 0xFF, 0xB0, 0x10, 0x21 } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVICE_MESSAGE_INDICATOR			= { 0xCD48A365, 0xFA94, 0x4CE2, { 0xA2, 0x32, 0xA1, 0xB7, 0x64, 0xE5, 0xD8, 0xB4 } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVICE_PROCESSOR					= { 0x97FADB10, 0x4E33, 0x40AE, { 0x35, 0x9C, 0x8B, 0xEF, 0x02, 0x9D, 0xBD, 0xD0 } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVICE_SYS_BUTTON				= { 0x4AFA3D53, 0x74A7, 0x11d0, { 0xbe, 0x5e, 0x00, 0xA0, 0xC9, 0x06, 0x28, 0x57 } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVICE_THERMAL_ZONE				= { 0x4AFA3D51, 0x74A7, 0x11d0, { 0xbe, 0x5e, 0x00, 0xA0, 0xC9, 0x06, 0x28, 0x57 } };

	//Bluetooth
	nsCodeQOR::mxGUID CDeviceManager::GUID_BTHPORT_DEVICE_INTERFACE			= { 0x0850302A, 0xB344, 0x4fda, { 0x9B, 0xE9, 0x90, 0x57, 0x6B, 0x8D, 0x46, 0xF0 } };

	//Display and Image
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_BRIGHTNESS			= { 0xFDE5BBA4, 0xB3F9, 0x46FB, { 0xBD, 0xAA, 0x07, 0x28, 0xCE, 0x31, 0x00, 0xB4 } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_DISPLAY_ADAPTER		= { 0x5B45201D, 0xF2F2, 0x4F3B, { 0x85, 0xBB, 0x30, 0xFF, 0x1F, 0x95, 0x35, 0x99 } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_I2C					= { 0x2564AA4F, 0xDDDB, 0x4495, { 0xB4, 0x97, 0x6A, 0xD4, 0xA8, 0x41, 0x63, 0xD7 } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_IMAGE				= { 0x6BDD1FC6, 0x810F, 0x11D0, { 0xBE, 0xC7, 0x08, 0x00, 0x2B, 0xE2, 0x09, 0x2F } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_MONITOR				= { 0xE6F07B5F, 0xEE97, 0x4a90, { 0xB0, 0x76, 0x33, 0xF5, 0x7B, 0xF4, 0xEA, 0xA7 } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_OPM					= { 0xBF4672DE, 0x6B4E, 0x4BE4, { 0xA3, 0x25, 0x68, 0xA9, 0x1E, 0xA4, 0x9C, 0x09 } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_VIDEO_OUTPUT_ARRIVAL= { 0x1AD9E4F0, 0xF88D, 0x4360, { 0xBA, 0xB9, 0x4C, 0x2D, 0x55, 0xE5, 0x64, 0xCD } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DISPLAY_DEVICE_ARRIVAL			= { 0x1CA05180, 0xA699, 0x450A, { 0x9A, 0x0C, 0xDE, 0x4F, 0xBE, 0x3D, 0xDD, 0x89 } };

	//Interactive Input
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_HID					= { 0x4D1E55B2, 0xF16F, 0x11CF, { 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_KEYBOARD			= { 0x884b96c3, 0x56ef, 0x11d1, { 0xbc, 0x8c, 0x00, 0xa0, 0xc9, 0x14, 0x05, 0xdd } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_MOUSE				= { 0x378de44c, 0x56ef, 0x11d1, { 0xbc, 0x8c, 0x00, 0xa0, 0xc9, 0x14, 0x05, 0xdd } };

	//Modem
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_MODEM				= { 0x2C7089AA, 0x2E0E, 0x11D1, { 0xB1, 0x14, 0x00, 0xC0, 0x4F, 0xC2, 0xAA, 0xE4 } };

	//Network
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_NET					= { 0xCAC88484, 0x7515, 0x4C03, { 0x82, 0xE6, 0x71, 0xA8, 0x7A, 0xBA, 0xC3, 0x61 } };

	//Serial and Parallel Port
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_COMPORT				= { 0x86E0D1E0, 0x8089, 0x11D0, { 0x9C, 0xE4, 0x08, 0x00, 0x3E, 0x30, 0x1F, 0x73 } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_PARALLEL			= { 0x97F76EF0, 0xF883, 0x11D0, { 0xAF, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x84, 0x5C } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_PARCLASS			= { 0x811FC6A5, 0xF728, 0x11D0, { 0xA5, 0x37, 0x00, 0x00, 0xF8, 0x75, 0x3E, 0xD1 } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_SERENUM_BUS_ENUMERATOR = { 0x4D36E978, 0xE325, 0x11CE, { 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18} };

	//Storage
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_CDCHANGER			= { 0x53F56312, 0xB6BF, 0x11D0, { 0x94, 0xF2, 0x00, 0xA0, 0xC9, 0x1E, 0xFB, 0x8B } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_CDROM				= { 0x53F56308, 0xB6BF, 0x11D0, { 0x94, 0xF2, 0x00, 0xA0, 0xC9, 0x1E, 0xFB, 0x8B } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_DISK				= { 0x53F56307, 0xB6BF, 0x11D0, { 0x94, 0xF2, 0x00, 0xA0, 0xC9, 0x1E, 0xFB, 0x8B } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_FLOPPY				= { 0x53F56311, 0xB6BF, 0x11D0, { 0x94, 0xF2, 0x00, 0xA0, 0xC9, 0x1E, 0xFB, 0x8B } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_MEDIUMCHANGER		= { 0x53F56310, 0xB6BF, 0x11D0, { 0x94, 0xF2, 0x00, 0xA0, 0xC9, 0x1E, 0xFB, 0x8B } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_PARTITION			= { 0x53F5630A, 0xB6BF, 0x11D0, { 0x94, 0xF2, 0x00, 0xA0, 0xC9, 0x1E, 0xFB, 0x8B } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_STORAGEPORT			= { 0x2ACCFE60, 0xC130, 0x11D2, { 0xB0, 0x82, 0x00, 0xA0, 0xC9, 0x1E, 0xFB, 0x8B } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_TAPE				= { 0x53F5630B, 0xB6BF, 0x11D0, { 0x94, 0xF2, 0x00, 0xA0, 0xC9, 0x1E, 0xFB, 0x8B } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_VOLUME				= { 0x53F5630D, 0xB6BF, 0x11D0, { 0x94, 0xF2, 0x00, 0xA0, 0xC9, 0x1E, 0xFB, 0x8B } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_WRITEONCEDISK		= { 0x53F5630C, 0xB6BF, 0x11D0, { 0x94, 0xF2, 0x00, 0xA0, 0xC9, 0x1E, 0xFB, 0x8B } };

	//USB
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_USB_DEVICE			= { 0xA5DCBF10, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_USB_HOST_CONTROLLER = { 0x3ABF6F2D, 0x71C4, 0x462A, { 0x8A, 0x92, 0x1E, 0x68, 0x61, 0xE6, 0xAF, 0x27 } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_USB_HUB				= { 0xF18A0E88, 0xC30C, 0x11D0, { 0x88, 0x15, 0x00, 0xA0, 0xC9, 0x06, 0xBE, 0xD8 } };

	//Windows Portable Devices
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_WPD					= { 0x6AC27878, 0xA6FA, 0x4155, { 0xBA, 0x85, 0xF9, 0x8F, 0x49, 0x1D, 0x4F, 0x33 } };
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_WPD_PRIVATE			= { 0xBA0C718F, 0x4DED, 0x49B7, { 0xBD, 0xD3, 0xFA, 0xBE, 0x28, 0x66, 0x12, 0x11 } };

	//Windows Slideshow
	nsCodeQOR::mxGUID CDeviceManager::GUID_DEVINTERFACE_SLIDESHOW			= { 0x152E5811, 0xFEB9, 0x4B00, { 0x90, 0xF4, 0xD3, 0x29, 0x47, 0xAE, 0x16, 0x81 } };

	//--------------------------------------------------------------------------------
	void CDeviceManager::RegisterKnownInterfaceClasses()
	{
		//1394 and 16883 devices
		RegisterInterfaceClass( CTString( _TXT( "IEEE 1394" ) ), BUS1394_CLASS_GUID );
		RegisterInterfaceClass( CTString( _TXT( "61883" ) ), GUID_61883_CLASS );
		
		//Battery and ACPI devices
		RegisterInterfaceClass( CTString( _TXT( "Application Launch Button" ) ), GUID_DEVICE_APPLICATIONLAUNCH_BUTTON );
		RegisterInterfaceClass( CTString( _TXT( "Battery" ) ), GUID_DEVICE_BATTERY );
		RegisterInterfaceClass( CTString( _TXT( "Lid" ) ), GUID_DEVICE_LID );
		RegisterInterfaceClass( CTString( _TXT( "Memory" ) ), GUID_DEVICE_MEMORY );
		RegisterInterfaceClass( CTString( _TXT( "Message Indicator" ) ), GUID_DEVICE_MESSAGE_INDICATOR );
		RegisterInterfaceClass( CTString( _TXT( "Processor" ) ), GUID_DEVICE_PROCESSOR );
		RegisterInterfaceClass( CTString( _TXT( "System Button" ) ), GUID_DEVICE_SYS_BUTTON );
		RegisterInterfaceClass( CTString( _TXT( "Thermal Zone" ) ), GUID_DEVICE_THERMAL_ZONE );

		//Bluetooth
		RegisterInterfaceClass( CTString( _TXT( "Bluetooth Port" ) ), GUID_BTHPORT_DEVICE_INTERFACE );

		//Display and Image
		RegisterInterfaceClass( CTString( _TXT( "Brightness" ) ), GUID_DEVINTERFACE_BRIGHTNESS );
		RegisterInterfaceClass( CTString( _TXT( "Display Adapter" ) ), GUID_DEVINTERFACE_DISPLAY_ADAPTER );
		RegisterInterfaceClass( CTString( _TXT( "I2C" ) ), GUID_DEVINTERFACE_I2C );
		RegisterInterfaceClass( CTString( _TXT( "Image" ) ), GUID_DEVINTERFACE_IMAGE );
		RegisterInterfaceClass( CTString( _TXT( "Monitor" ) ), GUID_DEVINTERFACE_MONITOR );
		RegisterInterfaceClass( CTString( _TXT( "OPM" ) ), GUID_DEVINTERFACE_OPM );
		RegisterInterfaceClass( CTString( _TXT( "Video Output Arrival" ) ), GUID_DEVINTERFACE_VIDEO_OUTPUT_ARRIVAL );
		RegisterInterfaceClass( CTString( _TXT( "Display Device Arrival" ) ), GUID_DISPLAY_DEVICE_ARRIVAL );

		//Interactive Input
		RegisterInterfaceClass( CTString( _TXT( "Human Interface Device" ) ), GUID_DEVINTERFACE_HID );
		RegisterInterfaceClass( CTString( _TXT( "Keyboard" ) ), GUID_DEVINTERFACE_KEYBOARD );
		RegisterInterfaceClass( CTString( _TXT( "Mouse" ) ), GUID_DEVINTERFACE_MOUSE );

		//Modem
		RegisterInterfaceClass( CTString( _TXT( "Modem" ) ), GUID_DEVINTERFACE_MODEM );

		//Network
		RegisterInterfaceClass( CTString( _TXT( "Network" ) ), GUID_DEVINTERFACE_NET );

		//Serial and Parallel Port
		RegisterInterfaceClass( CTString( _TXT( "COM Port" ) ), GUID_DEVINTERFACE_COMPORT );
		RegisterInterfaceClass( CTString( _TXT( "Parallel Port" ) ), GUID_DEVINTERFACE_PARALLEL );
		RegisterInterfaceClass( CTString( _TXT( "Parallel Class" ) ), GUID_DEVINTERFACE_PARCLASS );
		RegisterInterfaceClass( CTString( _TXT( "Serial Bus Enumerator" ) ), GUID_DEVINTERFACE_SERENUM_BUS_ENUMERATOR );

		//Storage
		RegisterInterfaceClass( CTString( _TXT( "CD Changer" ) ), GUID_DEVINTERFACE_CDCHANGER );
		RegisterInterfaceClass( CTString( _TXT( "CDROM" ) ), GUID_DEVINTERFACE_CDROM );
		RegisterInterfaceClass( CTString( _TXT( "Disk" ) ), GUID_DEVINTERFACE_DISK );
		RegisterInterfaceClass( CTString( _TXT( "Floppy" ) ), GUID_DEVINTERFACE_FLOPPY );
		RegisterInterfaceClass( CTString( _TXT( "Meduim Changer" ) ), GUID_DEVINTERFACE_MEDIUMCHANGER );
		RegisterInterfaceClass( CTString( _TXT( "Partition" ) ), GUID_DEVINTERFACE_PARTITION );
		RegisterInterfaceClass( CTString( _TXT( "Storage Port" ) ), GUID_DEVINTERFACE_STORAGEPORT );
		RegisterInterfaceClass( CTString( _TXT( "Tape" ) ), GUID_DEVINTERFACE_TAPE );
		RegisterInterfaceClass( CTString( _TXT( "Volume" ) ), GUID_DEVINTERFACE_VOLUME );
		RegisterInterfaceClass( CTString( _TXT( "Write Once Disk" ) ), GUID_DEVINTERFACE_WRITEONCEDISK );

		//USB
		RegisterInterfaceClass( CTString( _TXT( "USB Device" ) ), GUID_DEVINTERFACE_USB_DEVICE );
		RegisterInterfaceClass( CTString( _TXT( "USB Host Controller" ) ), GUID_DEVINTERFACE_USB_HOST_CONTROLLER );
		RegisterInterfaceClass( CTString( _TXT( "USB Hub" ) ), GUID_DEVINTERFACE_USB_HUB );

		//Windows Portable Devices
		RegisterInterfaceClass( CTString( _TXT( "Windows Portable Device" ) ), GUID_DEVINTERFACE_WPD );
		RegisterInterfaceClass( CTString( _TXT( "Windows Portable Device Private" ) ), GUID_DEVINTERFACE_WPD_PRIVATE );

		//Windows Slideshow
		RegisterInterfaceClass( CTString( _TXT( "Slideshow" ) ), GUID_DEVINTERFACE_SLIDESHOW );
	}

	//--------------------------------------------------------------------------------
	CDeviceManager::CDeviceManager( CTStringRef refstrMachine ) : m_Library( CSetupAPI::Instance() )
	,	m_pPSAPILibrary( new CPSAPI )
	,	m_strMachine( *refstrMachine )
	,	m_bEnumeratorsEnumerated( false )
	,	m_bInstancesEnumerated( false )
	,	m_bSetupClassesEnumerated( false )
	,	m_bInterfaceClassesEnumerated( false )
	,	m_bDriversEnumerated( false )
	{
		_WINQ_FCONTEXT( "CDeviceManager::CDeviceManager" );

		RegisterKnownInterfaceClasses();
	}
	
	//--------------------------------------------------------------------------------
	CDeviceManager::~CDeviceManager()
	{
		_WINQ_FCONTEXT( "CDeviceManager::~CDeviceManager" );
		delete m_pPSAPILibrary;
	}
	
	//--------------------------------------------------------------------------------
	CDeviceNode::refType CDeviceManager::RootDevice()
	{
		return m_ConfigManagementSession.RootDevice().Ref();
	}

	//--------------------------------------------------------------------------------
	std::map< const CTString, CDeviceEnumerator::refType >& CDeviceManager::Enumerators()
	{
		_WINQ_FCONTEXT( "CDeviceManager::Enumerators" );
		if( !m_bEnumeratorsEnumerated )
		{
			m_EnumeratorEnumerator().Enumerate();
			m_bEnumeratorsEnumerated = true;
		}
		return m_DeviceEnumeratorCollection;
	}

	//--------------------------------------------------------------------------------
	std::map< const CTString, CDeviceInstance::refType >& CDeviceManager::Instances()
	{
		_WINQ_FCONTEXT( "CDeviceManager::Instances" );
		if( !m_bInstancesEnumerated )
		{
			EnumerateInstances();
		}
		return m_DeviceInstanceCollection;
	}

	//--------------------------------------------------------------------------------
	std::map< nsCodeQOR::mxGUID, CDeviceSetupClass::refType >& CDeviceManager::SetupClasses()
	{
		_WINQ_FCONTEXT( "CDeviceManager::SetupClasses" );
		if( !m_bSetupClassesEnumerated )
		{
			EnumerateSetupClasses();
		}
		return m_DeviceSetupClassCollection;
	}
	
	//--------------------------------------------------------------------------------
	std::map< nsCodeQOR::mxGUID, CDeviceInterfaceClass::refType >& CDeviceManager::InterfaceClasses()
	{
		_WINQ_FCONTEXT( "CDeviceManager::InterfaceClasses" );
		if( !m_bInterfaceClassesEnumerated )
		{
			EnumerateInterfaceClasses();
		}
		return m_DeviceInterfaceClassCollection;
	}

	//--------------------------------------------------------------------------------
	std::map< const CTString, CDeviceDriver::refType >& CDeviceManager::Drivers()
	{
		_WINQ_FCONTEXT( "CDeviceManager::Drivers" );
		if( !m_bDriversEnumerated )
		{
			EnumerateDrivers();
		}
		return m_DeviceDriverCollection;
	}

	//--------------------------------------------------------------------------------
	void CDeviceManager::RegisterEnumerator( const CTString strDeivceEnumeratorName, CDeviceEnumerator* pDeviceEnumerator )
	{
		_WINQ_FCONTEXT( "CDeviceManager::RegisterEnumerator" );
		m_DeviceEnumeratorCollection.insert( std::make_pair( strDeivceEnumeratorName, CDeviceEnumerator::refType( pDeviceEnumerator, true ) ) );
	}

	//--------------------------------------------------------------------------------
	void CDeviceManager::RegisterInstance( const CTString strDeviceID, CDeviceInstance* pDeviceInstance )
	{
		_WINQ_FCONTEXT( "CDeviceManager::RegisterInstance" );
		m_DeviceInstanceCollection.insert( std::make_pair( strDeviceID, CDeviceInstance::refType( pDeviceInstance, true ) ) );
	}

	//--------------------------------------------------------------------------------
	void CDeviceManager::RegisterInterfaceClass( const CTString strInterfaceName, nsCodeQOR::mxGUID& InterfaceID )
	{
		_WINQ_FCONTEXT( "CDeviceManager::RegisterInterfaceClass" );
		m_DeviceInterfaceClassCollection.insert( std::make_pair( InterfaceID, CDeviceInterfaceClass::refType( new CDeviceInterfaceClass( InterfaceID, strInterfaceName, m_strMachine.Ref() ), true ) ) );
	}

	//--------------------------------------------------------------------------------
	void CDeviceManager::RegisterUSBHub( const CTString& strHubName, CUSBHub* pUSBHub )
	{
		_WINQ_FCONTEXT( "CDeviceManager::RegisterUSBHub" );
		m_USBHubByNameMap.insert( std::make_pair( strHubName, pUSBHub ) );
	}

	//--------------------------------------------------------------------------------
	CUSBHub* CDeviceManager::USBHubFromName( const CTString& strHubName )
	{
		_WINQ_FCONTEXT( "CDeviceManager::USBHubFromName" );
		CUSBHub* pHub = 0;
		CTString strSearchName = strHubName;
		std::map< const CTString, CUSBHub* >::iterator it = m_USBHubByNameMap.find( strSearchName.toUpper() );
		if( it != m_USBHubByNameMap.end() )
		{
			pHub = it->second;
		}
		return pHub;
	}

	//--------------------------------------------------------------------------------
	CDeviceInterfaceClass::refType CDeviceManager::InterfaceClassFromGUID( nsCodeQOR::mxGUID const& GUID )
	{
		_WINQ_FCONTEXT( "CDeviceManager::InterfaceClassFromGUID" );
		std::map< nsCodeQOR::mxGUID, CDeviceInterfaceClass::refType >::iterator it = m_DeviceInterfaceClassCollection.find( GUID );
		return it == m_DeviceInterfaceClassCollection.end() ? CDeviceInterfaceClass::refType( 0 ) : (*it).second->Ref();
	}

	//--------------------------------------------------------------------------------
	nsCodeQOR::CTLRef< CDeviceInstance > CDeviceManager::DeviceFromID( const mxTCHAR* szDeviceID )
	{
		_WINQ_FCONTEXT( "CDeviceManager::DeviceFromID" );
		std::map< const CTString, nsCodeQOR::CTLRef< CDeviceInstance > >::iterator it = m_DeviceInstanceCollection.find( CTString( szDeviceID ) );
		return it == m_DeviceInstanceCollection.end() ? nsCodeQOR::CTLRef< CDeviceInstance >( 0 ) : (*it).second->Ref();
	}
	
	//--------------------------------------------------------------------------------
	nsCodeQOR::CTLRef< CDeviceInstance > CDeviceManager::DeviceFromName( const mxTCHAR* szDeviceName )
	{
		_WINQ_FCONTEXT( "CDeviceManager::DeviceFromName" );

		CTString strDeviceID = DeviceIDFromName( szDeviceName );
		std::map< const CTString, nsCodeQOR::CTLRef< CDeviceInstance > >::iterator it = m_DeviceInstanceCollection.find( strDeviceID );
		return it == m_DeviceInstanceCollection.end() ? nsCodeQOR::CTLRef< CDeviceInstance >( 0 ) : (*it).second->Ref();
	}
	
	//--------------------------------------------------------------------------------
	CDeviceEnumerator::refType CDeviceManager::EnumeratorFromName( CTStringRef strEnumeratorRef )
	{
		_WINQ_FCONTEXT( "CDeviceManager::EnumeratorFromName" );
		CTString strEnumerator( *strEnumeratorRef );
		m_EnumeratorEnumerator();
		std::map< const CTString, CDeviceEnumerator::refType >::iterator it = m_DeviceEnumeratorCollection.find( strEnumerator );		
		return it == m_DeviceEnumeratorCollection.end() ? CDeviceEnumerator::refType( 0 ) : (*it).second->Ref();
	}

	//--------------------------------------------------------------------------------
	CTString CDeviceManager::DeviceIDFromName( const mxTCHAR* szDeviceName )
	{
		_WINQ_FCONTEXT( "CDeviceManager::DeviceIDFromName" );

		CTString strDeviceID;
		CHandle Handle = m_Library.SetupDiCreateDeviceInfoListEx( 0, 0, 0, 0 );

		if( !Handle.IsInvalid() )
		{
			SP_DevInfo_Data DevInfo;
			DevInfo.cbSize = sizeof( ::SP_DEVINFO_DATA );
			DevInfo.ClassGuid = *(reinterpret_cast< nsCodeQOR::mxGUID* >(&NULL_GUID));
			DevInfo.DevInst = 0;
			DevInfo.Reserved = 0;
			m_Library.SetupDiCreateDeviceInfo(reinterpret_cast< ::HDEVINFO >(Handle.Use()), szDeviceName, reinterpret_cast< const ::GUID* >( &NULL_GUID ), 0, 0, DICD_GENERATE_ID, reinterpret_cast< ::PSP_DEVINFO_DATA >(&DevInfo));

			if( DevInfo.DevInst > 0 && DevInfo.DevInst != ( unsigned long )(-1) )
			{
				
				m_Library.CM_Get_Device_ID_Ex( static_cast< ::DEVINST >( DevInfo.DevInst ), strDeviceID.GetBufferSetLength( MaxDeviceIDLen + 1), MaxDeviceIDLen, 0, 0 );
			}

			m_Library.SetupDiDestroyDeviceInfoList( reinterpret_cast< ::HDEVINFO >( Handle.Use() ) );
		}

		return strDeviceID;
	}

	//------------------------------------------------------------------------------
	void CDeviceManager::WalkInstances( CDeviceNode::refType rootNode, fpDevNodeCallback pNodeCallback )
	{
		bool bContinue = true;
		if( pNodeCallback )
		{
			bContinue = (this->*pNodeCallback)( rootNode );
		}

		if( bContinue )
		{
			std::vector< CDeviceNode* > Nodes = rootNode->GetChildren();
	
			for( std::vector< CDeviceNode* >::iterator it = Nodes.begin(); it != Nodes.end(); ++it )
			{
				CDeviceNode* pNode = *it;
				WalkInstances( pNode->Ref(), pNodeCallback );		
			}
		}
	}

	//--------------------------------------------------------------------------------
	bool CDeviceManager::InstanceFromNodeCallback( CDeviceNode* pDevNode )
	{
		if( pDevNode )
		{
			pDevNode->GetInstance();
		}
		return true;
	}

	//--------------------------------------------------------------------------------
	void CDeviceManager::EnumerateInstances()
	{
		_WINQ_FCONTEXT( "CDeviceManager::EnumerateInstances" );
		WalkInstances( RootDevice(), &CDeviceManager::InstanceFromNodeCallback );
		m_bInstancesEnumerated = true;
	}
	
	//--------------------------------------------------------------------------------
	void CDeviceManager::EnumerateSetupClasses()
	{
		_WINQ_FCONTEXT( "CDeviceManager::EnumerateSetupClasses" );

		unsigned long ulRequiredSize = 0;		
		
		m_Library.SetupDiBuildClassInfoListEx( 0, 0, 0, &ulRequiredSize, m_strMachine, 0 );

		nsCodeQOR::CTArray< nsCodeQOR::__mxGUID, CWinQLPolicy > SetupClassGUIDs( ulRequiredSize );
		unsigned long ulSetupClassCount = 0;
		unsigned long ulFlags = 0;
		m_Library.SetupDiBuildClassInfoListEx( ulFlags, reinterpret_cast< ::LPGUID >( SetupClassGUIDs.GetAddressOfData() ), ulRequiredSize, &ulSetupClassCount, 0/*m_szMachine*/, 0 );
		SetupClassGUIDs.Validate( ulSetupClassCount );

		for( unsigned int ui = 0; ui < ulSetupClassCount; ui++ )
		{
			m_DeviceSetupClassCollection.insert( std::make_pair( SetupClassGUIDs[ ui ], CDeviceSetupClass::refType( new CDeviceSetupClass( SetupClassGUIDs[ ui ], 0/*m_szMachine*/ ), true ) ) );
		}
		m_bSetupClassesEnumerated = true;
	}

	//--------------------------------------------------------------------------------
	void CDeviceManager::EnumerateInterfaceClasses()
	{
		_WINQ_FCONTEXT( "CDeviceManager::EnumerateInterfaceClasses" );
		m_bInterfaceClassesEnumerated = true;
	}
	
	//--------------------------------------------------------------------------------
	void CDeviceManager::EnumerateDrivers()
	{
		_WINQ_FCONTEXT( "CDeviceManager::EnumerateDrivers" );

		unsigned long ulNeeded = 0;
		m_pPSAPILibrary->EnumDeviceDrivers( 0, 0, &ulNeeded );

		nsCodeQOR::CTArray< void*, CWinQLPolicy > DriverAddresses( ulNeeded );
		
		unsigned long ulDriverCount = 0;
		m_pPSAPILibrary->EnumDeviceDrivers( DriverAddresses.GetAddressOfData(), ulNeeded, &ulDriverCount );

		DriverAddresses.Validate( ulDriverCount );

		ulDriverCount /= sizeof( void* );
		for( unsigned int ui = 0; ui< ulDriverCount; ui++ )
		{
			CTString strDriverBaseName;
			strDriverBaseName.ValidateBuffer( static_cast< unsigned short >( m_pPSAPILibrary->GetDeviceDriverBaseName( DriverAddresses[ ui ], strDriverBaseName.GetBufferSetLength( 1024 ), 1024 ) ) );

			m_DeviceDriverCollection.insert( std::make_pair( strDriverBaseName, CDeviceDriver::refType( new CDeviceDriver(), true ) ) );
		}	
		m_bDriversEnumerated = true;
	}
	
}//nsWin32