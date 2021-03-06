//DeviceInterfaceClassModel.h

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

//Win32 Device Interface Class Model

#ifndef WINQL_DEVICEINTERFACECLASSMODEL_H_3
#define WINQL_DEVICEINTERFACECLASSMODEL_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/WinQLPolicy.h"
#include "WinQL/Definitions/Data.h"
#include "WinQL/Definitions/IO.h"
#include "WinQL/Devices/Interfaces/DeviceInterfaceInstanceModel.h"
#include "WinQL/DeviceIO/DeviceHandle.h"
#include "WinQL/CodeServices/WinString.h"
#include "MammutQOR/Models/VectorModel.h"
#include "MammutQOR/Models/MapModel.h"
#include "MammutQOR/Model/MPropertySet.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CDeviceInterfaceClassModel : public nsMammut::CMapModel< CTString, nsMammut::CModel >
	{
	public:

		typedef nsMammut::CMapModel< CTString, nsMammut::CModel > BaseName;

		__QOR_DECLARE_OCLASS_ID( CDeviceInterfaceClassModel );

		CDeviceInterfaceClassModel();
		CDeviceInterfaceClassModel( const CDeviceInterfaceClassModel& );
		CDeviceInterfaceClassModel& operator = ( const CDeviceInterfaceClassModel& );
		~CDeviceInterfaceClassModel();

	private:

		nsMammut::CPropertySet m_Properties;
			nsMammut::CProperty< nsCodeQOR::mxGUID* > m_pGUID;
			nsMammut::CProperty< const mxTCHAR* > m_szMachine;

		nsMammut::CVectorModel< CDeviceInterfaceInstanceModel > m_Instances;

	};
	
}//nsWin32

#endif//WINQL_DEVICEINTERFACECLASSMODEL_H_3
