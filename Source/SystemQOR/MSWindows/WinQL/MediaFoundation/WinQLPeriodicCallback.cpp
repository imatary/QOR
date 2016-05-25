//WinQLPeriodicCallback.cpp

// Copyright Querysoft Limited 2013, 2015
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
#include "WinQL/MediaFoundation/PeriodicCallback.h"
#include "WinQAPI/MedFoundAPI.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	const GUID IMFPeriodicCallback::_IID = { 0xad4c100b, 0x422f, 0x9175, 0x4b, 0xf7, 0x0d, 0x66, 0x93, 0xd9, 0x13, 0x75 };

	//--------------------------------------------------------------------------------
	namespace nsMediaFoundation
	{

		__QOR_IMPLEMENT_OCLASS_LUID( CPeriodicCallback );

		//--------------------------------------------------------------------------------
		CPeriodicCallback::CPeriodicCallback() : m_MFLibrary( *( new nsWinQAPI::CMFAPI ) )
		{
			_WINQ_FCONTEXT( "CPeriodicCallback::CPeriodicCallback" );
			m_ulKey = 0;
			IUnknown* pThis = Internal_Interface< IUnknown >();
			m_ulStatus = m_MFLibrary.MFAddPeriodicCallback( &StaticCallback, reinterpret_cast< ::IUnknown* >( pThis ), &m_ulKey );
		}

		//--------------------------------------------------------------------------------
		CPeriodicCallback::~CPeriodicCallback()
		{
			_WINQ_FCONTEXT( "CPeriodicCallback::~CPeriodicCallback" );
			delete &m_MFLibrary;
		}

		//--------------------------------------------------------------------------------
		unsigned long __QCMP_STDCALLCONVENTION CPeriodicCallback::Callback( void )
		{
			_WINQ_FCONTEXT( "CPeriodicCallback::Callback" );
			return S_OK;
		}

		//--------------------------------------------------------------------------------
		unsigned long CPeriodicCallback::Cancel()
		{
			_WINQ_FCONTEXT( "CPeriodicCallback::Cancel" );
			unsigned long ulResult = m_MFLibrary.MFRemovePeriodicCallback( m_ulKey );
			return ulResult;
		}

		//--------------------------------------------------------------------------------
		void CPeriodicCallback::StaticCallback( ::IUnknown* pContext )
		{
			_WINQ_SFCONTEXT( "CPeriodicCallback::StaticCallback" );
			IMFPeriodicCallback* pPeriodicCallbackObject = 0;			
			pContext->QueryInterface( *( reinterpret_cast< const IID* >( &IMFPeriodicCallback::_IID ) ), reinterpret_cast< void** >( &pPeriodicCallbackObject ) );
			if( pPeriodicCallbackObject != 0 )
			{
				pPeriodicCallbackObject->Callback();
				pPeriodicCallbackObject->Release();
			}
		}

	}//nsMediaFoundation

}//nsWin32