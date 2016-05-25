//WinQDeviceContext.cpp

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

//DC functions

#include "WinQAPI/User32.h"
#include "../Source/SystemQOR/MSWindows/WinQAPI/include/ReturnCheck.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	//--------------------------------------------------------------------------------
	LONG CUser32::ChangeDisplaySettings( ::LPDEVMODE lpDevMode, DWORD dwflags )
	{
		_WINQ_FCONTEXT( "CUser32::ChangeDisplaySettings" );
		CCheckReturn< LONG, CSuccessCheck< > >::TType lResult;
		_WINQ_USESAPI( ChangeDisplaySettings );	
		lResult = Call< LONG, ::LPDEVMODE, DWORD >( pFunc, lpDevMode, dwflags );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	LONG CUser32::ChangeDisplaySettingsEx( LPCTSTR lpszDeviceName, ::LPDEVMODE lpDevMode, HWND hwnd, DWORD dwflags, LPVOID lParam )
	{
		_WINQ_FCONTEXT( "CUser32::ChangeDisplaySettingsEx" );
		CCheckReturn< LONG, CSuccessCheck< > >::TType lResult;
		_WINQ_USESAPI( ChangeDisplaySettingsEx );
		lResult = Call< LONG, LPCTSTR, ::LPDEVMODE, HWND, DWORD, LPVOID >( pFunc, lpszDeviceName, lpDevMode, hwnd, dwflags, lParam );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::EnumDisplayDevices( LPCTSTR lpDevice, DWORD iDevNum, ::PDISPLAY_DEVICE lpDisplayDevice, DWORD dwFlags )
	{
		_WINQ_FCONTEXT( "CUser32::EnumDisplayDevices" );
		BOOL bResult;
		_WINQ_USESAPI( EnumDisplayDevices );
		bResult = Call< BOOL, LPCTSTR, DWORD, ::PDISPLAY_DEVICE, DWORD >( pFunc, lpDevice, iDevNum, lpDisplayDevice, dwFlags );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::EnumDisplaySettings( LPCTSTR lpszDeviceName, DWORD iModeNum, ::LPDEVMODE lpDevMode )
	{
		_WINQ_FCONTEXT( "CUser32::EnumDisplaySettings" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( EnumDisplaySettings );
		bResult = Call< BOOL, LPCTSTR, DWORD, ::LPDEVMODE >( pFunc, lpszDeviceName, iModeNum, lpDevMode );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::EnumDisplaySettingsEx( LPCTSTR lpszDeviceName, DWORD iModeNum, ::LPDEVMODE lpDevMode, DWORD dwFlags )
	{
		_WINQ_FCONTEXT( "CUser32::EnumDisplaySettingsEx" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( EnumDisplaySettingsEx );
		bResult = Call< BOOL, LPCTSTR, DWORD, ::LPDEVMODE, DWORD >( pFunc, lpszDeviceName, iModeNum, lpDevMode, dwFlags );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	HDC CUser32::GetDC( HWND hWnd )
	{
		_WINQ_FCONTEXT( "CUser32::GetDC" );
		CCheckReturn< HDC, CCheckNonZero< HDC > >::TType Result;
		_WINQ_USESAPI( GetDC );
		Result = Call< HDC, HWND >( pFunc, hWnd );
		return Result;
	}

	//--------------------------------------------------------------------------------
	HDC CUser32::GetDCEx( HWND hWnd, HRGN hrgnClip, DWORD flags )
	{
		_WINQ_FCONTEXT( "CUser32::GetDCEx" );
		CCheckReturn< HDC, CCheckNonZero< HDC > >::TType Result;
		_WINQ_USESAPI( GetDCEx );
		Result = Call< HDC, HWND, HRGN, DWORD >( pFunc, hWnd, hrgnClip, flags );
		return Result;
	}

	//--------------------------------------------------------------------------------
	int CUser32::ReleaseDC( HWND hWnd, HDC hDC )
	{
		_WINQ_FCONTEXT( "CUser32::ReleaseDC" );
		CCheckReturn< int, CCheckNonZero< int > >::TType iResult;
		_WINQ_USESAPI( ReleaseDC );
		iResult = Call< int, HWND, HDC >( pFunc, hWnd, hDC );
		return iResult;
	}

}//nsWinQAPI