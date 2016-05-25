//WinQLActCtx.cpp

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

#include "WinQAPI/Kernel32.h"
#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/Application/WinQLActCtx.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	__QOR_IMPLEMENT_OCLASS_LUID( CActCtx );

	//--------------------------------------------------------------------------------
	CActCtx::CActCtx()
	{
		_WINQ_FCONTEXT( "CActCtx::CActCtx" );
		__QOR_PROTECT
		{
			m_hActCtx = CKernel32::CreateActCtx( reinterpret_cast< ::PACTCTX >( this ) );
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	CActCtx::~CActCtx()
	{
		_WINQ_FCONTEXT( "CActCtx::~CActCtx" );
		Release();
	}

	//--------------------------------------------------------------------------------
	bool CActCtx::Activate( Cmp_ulong_ptr* lpCookie )
	{
		_WINQ_FCONTEXT( "CActCtx::Activate" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = CKernel32::ActivateActCtx( m_hActCtx, lpCookie ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CActCtx::Deactivate( unsigned long dwFlags, Cmp_ulong_ptr ulCookie )
	{
		_WINQ_FCONTEXT( "CActCtx::Deactivate" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = CKernel32::DeactivateActCtx( dwFlags, ulCookie ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	void CActCtx::AddRef()
	{
		_WINQ_FCONTEXT( "CActCtx::AddRef" );
		__QOR_PROTECT
		{
			CKernel32::AddRefActCtx( m_hActCtx );
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	void CActCtx::Release()
	{
		_WINQ_FCONTEXT( "CActCtx::Release" );
		__QOR_PROTECT
		{
			CKernel32::ReleaseActCtx( m_hActCtx );
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	bool CActCtx::Zombify()
	{
		_WINQ_FCONTEXT( "CActCtx::Zombify" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = CKernel32::ZombifyActCtx( m_hActCtx ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CActCtx::FindSectionGuid( unsigned long dwFlags, const nsWin32::GUID* lpExtensionGuid, unsigned long ulSectionId, const nsWin32::GUID* lpGuidToFind, nsWin32::PACTCTX_SECTION_KEYED_DATA ReturnedData )
	{
		_WINQ_SFCONTEXT( "CActCtx::FindSectionGuid" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = CKernel32::FindActCtxSectionGuid( dwFlags, reinterpret_cast< const ::GUID* >( lpExtensionGuid ), ulSectionId, reinterpret_cast< const ::GUID* >( lpGuidToFind ), reinterpret_cast< ::PACTCTX_SECTION_KEYED_DATA >( ReturnedData ) ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CActCtx::FindSectionString( unsigned long dwFlags, const nsWin32::GUID* lpExtensionGuid, unsigned long ulSectionId, const TCHAR* lpStringToFind, nsWin32::PACTCTX_SECTION_KEYED_DATA ReturnedData )
	{
		_WINQ_SFCONTEXT( "CActCtx::FindSectionString" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = CKernel32::FindActCtxSectionString( dwFlags, reinterpret_cast< const ::GUID* >( lpExtensionGuid ), ulSectionId, lpStringToFind, reinterpret_cast< ::PACTCTX_SECTION_KEYED_DATA >( ReturnedData ) ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CActCtx::GetCurrent( void** lphActCtx )
	{
		_WINQ_SFCONTEXT( "CActCtx::GetCurrent" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = CKernel32::GetCurrentActCtx( lphActCtx ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CActCtx::QueryW( unsigned long dwFlags, void* pvSubInstance, unsigned long ulInfoClass, void* pvBuffer, Cmp_ulong_ptr cbBuffer, Cmp_ulong_ptr* pcbWrittenOrRequired )
	{
		_WINQ_FCONTEXT( "CActCtx::QueryW" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = CKernel32::QueryActCtxW( dwFlags, m_hActCtx, pvSubInstance, ulInfoClass, pvBuffer, cbBuffer, pcbWrittenOrRequired ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CActCtx::QuerySettingsW( unsigned long dwFlags, const wchar_t* settingsNameSpace, const wchar_t* settingName, wchar_t* pvBuffer, Cmp_ulong_ptr dwBuffer, Cmp_ulong_ptr* pdwWrittenOrRequired )
	{
		_WINQ_FCONTEXT( "CActCtx::QuerySettingsW" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = CKernel32::QueryActCtxSettingsW( dwFlags, m_hActCtx, settingsNameSpace, settingName, pvBuffer, dwBuffer, pdwWrittenOrRequired ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

}//nsWin32