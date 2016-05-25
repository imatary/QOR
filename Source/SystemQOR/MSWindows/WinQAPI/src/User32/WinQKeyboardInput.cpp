//WinQKeyboardInput.cpp

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

//Keyboard Input functions

#include "WinQAPI/User32.h"
#include "../Source/SystemQOR/MSWindows/WinQAPI/include/ReturnCheck.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	//--------------------------------------------------------------------------------
	HKL CUser32::ActivateKeyboardLayout( HKL hkl, UINT Flags )
	{
		_WINQ_FCONTEXT( "CUser32::ActivateKeyboardLayout" );
		CCheckReturn< HKL, CCheckNonZero< HKL > >::TType Result;
		_WINQ_USESAPI( ActivateKeyboardLayout );
		Result = Call<HKL, HKL, UINT>( pFunc, hkl, Flags );
		return Result;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::BlockInput( BOOL fBlockIt )
	{
		_WINQ_FCONTEXT( "CUser32::BlockInput" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( BlockInput );
		bResult = Call< BOOL, BOOL >( pFunc, fBlockIt );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::EnableWindow( HWND hWnd, BOOL bEnable )
	{
		_WINQ_FCONTEXT( "CUser32::EnableWindow" );
		_WINQ_USESAPI( EnableWindow );
		return Call< BOOL, HWND, BOOL >( pFunc, hWnd, bEnable );
	}

	//--------------------------------------------------------------------------------
	HWND CUser32::GetActiveWindow( void )
	{
		_WINQ_FCONTEXT( "CUser32::GetActiveWindow" );
		_WINQ_USESAPI( GetActiveWindow );
		return Call< HWND >( pFunc );
	}

	//--------------------------------------------------------------------------------
	SHORT CUser32::GetAsyncKeyState( int vKey )
	{
		_WINQ_FCONTEXT( "CUser32::GetAsyncKeyState" );
		_WINQ_USESAPI( GetAsyncKeyState );
		return Call< SHORT, int >( pFunc, vKey );
	}

	//--------------------------------------------------------------------------------
	HWND CUser32::GetFocus(void)
	{
		_WINQ_FCONTEXT( "CUser32::GetFocus" );
		CCheckReturn< HWND, CCheckNonZero< HWND > >::TType Result;
		_WINQ_USESAPI( GetFocus );
		Result = Call< HWND >( pFunc );
		return Result;
	}

	//--------------------------------------------------------------------------------
	UINT CUser32::GetKBCodePage()
	{
		_WINQ_FCONTEXT( "CUser32::GetKBCodePage" );
		_WINQ_USESAPI( GetKBCodePage );
		return Call< UINT >( pFunc );
	}

	//--------------------------------------------------------------------------------
	HKL CUser32::GetKeyboardLayout( DWORD idThread )
	{
		_WINQ_FCONTEXT( "CUser32::GetKeyboardLayout" );
		_WINQ_USESAPI( GetKeyboardLayout );
		return Call< HKL, DWORD >( pFunc, idThread );
	}

	//--------------------------------------------------------------------------------
	UINT CUser32::GetKeyboardLayoutList( int nBuff, HKL* lpList )
	{
		_WINQ_FCONTEXT( "CUser32::GetKeyboardLayoutList" );
		CCheckReturn< UINT, CCheckNonZero< UINT > >::TType uiResult;
		_WINQ_USESAPI( GetKeyboardLayoutList );
		uiResult = Call< UINT, int, HKL* >( pFunc, nBuff, lpList );
		return uiResult;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::GetKeyboardLayoutName( LPTSTR pwszKLID )
	{
		_WINQ_FCONTEXT( "CUser32::GetKeyboardLayoutName" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( GetKeyboardLayoutName );
		bResult = Call< BOOL, LPTSTR >( pFunc, pwszKLID );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::GetKeyboardState( PBYTE lpKeyState )
	{
		_WINQ_FCONTEXT( "CUser32::GetKeyboardState" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( GetKeyboardState );
		bResult = Call< BOOL, PBYTE >( pFunc, lpKeyState );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	int CUser32::GetKeyboardType( int nTypeFlag )
	{
		_WINQ_FCONTEXT( "CUser32::GetKeyboardType" );
		int iResult = 0;
		_WINQ_USESAPI( GetKeyboardType );
		iResult = Call< int, int >( pFunc, nTypeFlag );
		if( iResult == 0 && nTypeFlag != 1 )
		{
			__WINQAPI_CONT_ERROR(( GENERAL_API_ERROR, _T( "GetKeyboardType" ), 0 ));
		}
		return iResult;
	}

	//--------------------------------------------------------------------------------
	int CUser32::GetKeyNameText( LONG lParam, LPTSTR lpString, int nSize )
	{
		_WINQ_FCONTEXT( "CUser32::GetKeyNameText" );
		CCheckReturn< int, CCheckNonZero< int > >::TType iResult;
		_WINQ_USESAPIAW( GetKeyNameText );
		iResult = Call< int, LONG, LPTSTR, int >( pFunc, lParam, lpString, nSize );
		return iResult;
	}

	//--------------------------------------------------------------------------------
	SHORT CUser32::GetKeyState( int nVirtKey )
	{
		_WINQ_FCONTEXT( "CUser32::GetKeyState" );
		_WINQ_USESAPI( GetKeyState );
		return Call< SHORT, int >( pFunc, nVirtKey );
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::GetLastInputInfo( PLASTINPUTINFO plii )
	{
		_WINQ_FCONTEXT( "CUser32::GetLastInputInfo" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( GetLastInputInfo );
		bResult = Call< BOOL, PLASTINPUTINFO >( pFunc, plii );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::IsWindowEnabled( HWND hWnd )
	{
		_WINQ_FCONTEXT( "CUser32::IsWindowEnabled" );
		_WINQ_USESAPI( IsWindowEnabled );
		return Call< BOOL, HWND >( pFunc, hWnd );
	}

	//--------------------------------------------------------------------------------
	VOID CUser32::keybd_event( BYTE bVk, BYTE bScan, DWORD dwFlags, void* dwExtraInfo )
	{
		_WINQ_FCONTEXT( "CUser32::keybd_event" );
		_WINQ_USESAPI( keybd_event );
		voidCall< BYTE, BYTE, DWORD, void* >( pFunc, bVk, bScan, dwFlags, dwExtraInfo );
	}

	//--------------------------------------------------------------------------------
	HKL CUser32::LoadKeyboardLayout( LPCTSTR pwszKLID, UINT Flags )
	{
		_WINQ_FCONTEXT( "CUser32::LoadKeyboardLayout" );
		CCheckReturn< HKL, CCheckNonZero< HKL > >::TType Result;
		_WINQ_USESAPI( LoadKeyboardLayout );
		Result = Call< HKL, LPCTSTR, UINT >( pFunc, pwszKLID, Flags );
		return Result;
	}

	//--------------------------------------------------------------------------------
	UINT CUser32::MapVirtualKey( UINT uCode, UINT uMapType )
	{
		_WINQ_FCONTEXT( "CUser32::MapVirtualKey" );
		/*CCheckReturn< UINT, CCheckNonZero< UINT > >::TType*/ UINT uiResult;
		_WINQ_USESAPI( MapVirtualKey );
		uiResult = Call< UINT, UINT, UINT >( pFunc, uCode, uMapType );
		return uiResult;
	}

	//--------------------------------------------------------------------------------
	UINT CUser32::MapVirtualKeyEx( UINT uCode, UINT uMapType, HKL dwhkl )
	{
		_WINQ_FCONTEXT( "CUser32::MapVirtualKeyEx" );
		CCheckReturn< UINT, CCheckNonZero< UINT > >::TType uiResult;
		_WINQ_USESAPI( MapVirtualKeyEx );
		uiResult = Call< UINT, UINT, UINT, HKL >( pFunc, uCode, uMapType, dwhkl );
		return uiResult;
	}

	//--------------------------------------------------------------------------------
	DWORD CUser32::OemKeyScan( WORD wOemChar )
	{
		_WINQ_FCONTEXT( "CUser32::OemKeyScan" );
		_WINQ_USESAPI( OemKeyScan );
		return Call< DWORD, WORD >( pFunc, wOemChar );
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::RegisterHotKey( HWND hWnd, int id, UINT fsModifiers, UINT vk )
	{
		_WINQ_FCONTEXT( "CUser32::RegisterHotKey" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( RegisterHotKey );
		bResult = Call< BOOL, HWND, int, UINT, UINT >( pFunc, hWnd, id, fsModifiers, vk );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	UINT CUser32::SendInput( UINT nInputs, LPINPUT pInputs, int cbSize )
	{
		_WINQ_FCONTEXT( "CUser32::SendInput" );
		CCheckReturn< UINT, CCheckNonZero< UINT > >::TType uiResult;
		_WINQ_USESAPI( SendInput );
		uiResult = Call< UINT, UINT, LPINPUT, int >( pFunc, nInputs, pInputs, cbSize );
		return uiResult;
	}

	//--------------------------------------------------------------------------------
	HWND CUser32::SetActiveWindow( HWND hWnd )
	{
		_WINQ_FCONTEXT( "CUser32::SetActiveWindow" );
		CCheckReturn< HWND, CCheckNonZero< HWND > >::TType Result;
		_WINQ_USESAPI( SetActiveWindow );
		Result = Call< HWND, HWND >( pFunc, hWnd );
		return Result;
	}

	//--------------------------------------------------------------------------------
	HWND CUser32::SetFocus( HWND hWnd )
	{
		_WINQ_FCONTEXT( "CUser32::SetFocus" );
		CCheckReturn< HWND, CCheckNonZero< HWND > >::TType Result;
		_WINQ_USESAPI( SetFocus );
		Result = Call< HWND, HWND >( pFunc, hWnd );
		return Result;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::SetKeyboardState( LPBYTE lpKeyState )
	{
		_WINQ_FCONTEXT( "CUser32::SetKeyboardState" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( SetKeyboardState );
		bResult = Call< BOOL, LPBYTE >( pFunc, lpKeyState );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	int CUser32::ToAscii( UINT uVirtKey, UINT uScanCode, PBYTE lpKeyState, LPWORD lpChar, UINT uFlags )
	{
		_WINQ_FCONTEXT( "CUser32::ToAscii" );
		CCheckReturn< int, CTCheckNotLess< int, 0 > >::TType iResult;
		_WINQ_USESAPI( ToAscii );
		iResult = Call< int, UINT, UINT, PBYTE, LPWORD, UINT >( pFunc, uVirtKey, uScanCode, lpKeyState, lpChar, uFlags );
		return iResult;
	}

	//--------------------------------------------------------------------------------
	int CUser32::ToAsciiEx( UINT uVirtKey, UINT uScanCode, PBYTE lpKeyState, LPWORD lpChar, UINT uFlags, HKL dwhkl )
	{
		_WINQ_FCONTEXT( "CUser32::ToAsciiEx" );
		CCheckReturn< int, CTCheckNotLess< int, 0 > >::TType iResult;
		_WINQ_USESAPI( ToAsciiEx );
		iResult = Call< int, UINT, UINT, PBYTE, LPWORD, UINT, HKL >( pFunc, uVirtKey, uScanCode, lpKeyState, lpChar, uFlags, dwhkl );
		return iResult;
	}

	//--------------------------------------------------------------------------------
	int CUser32::ToUnicode( UINT wVirtKey, UINT wScanCode, const PBYTE lpKeyState, LPWSTR pwszBuff, int cchBuff, UINT wFlags )
	{
		_WINQ_FCONTEXT( "CUser32::ToUnicode" );
		_WINQ_USESAPI( ToUnicode );
		return Call< int, UINT, UINT, const PBYTE, LPWSTR, int, UINT >( pFunc, wVirtKey, wScanCode, lpKeyState, pwszBuff, cchBuff, wFlags );
	}

	//--------------------------------------------------------------------------------
	int CUser32::ToUnicodeEx( UINT wVirtKey, UINT wScanCode, const PBYTE lpKeyState, LPWSTR pwszBuff, int cchBuff, UINT wFlags, HKL dwhkl )
	{
		_WINQ_FCONTEXT( "CUser32::ToUnicodeEx" );
		_WINQ_USESAPI( ToUnicodeEx );
		return Call< int, UINT, UINT, const PBYTE, LPWSTR, int, UINT >( pFunc, wVirtKey, wScanCode, lpKeyState, pwszBuff, cchBuff, wFlags, dwhkl );
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::UnloadKeyboardLayout( HKL hkl )
	{
		_WINQ_FCONTEXT( "CUser32::UnloadKeyboardLayout" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( UnloadKeyboardLayout );
		bResult = Call< BOOL, HKL >( pFunc, hkl );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::UnregisterHotKey( HWND hWnd, int id )
	{
		_WINQ_FCONTEXT( "CUser32::UnregisterHotKey" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( UnregisterHotKey );
		bResult = Call< BOOL, HWND, int >( pFunc, hWnd, id );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	SHORT CUser32::VkKeyScan( TCHAR ch )
	{
		_WINQ_FCONTEXT( "CUser32::VkKeyScan" );
		CCheckReturn< SHORT, CTCheckFailureValue< SHORT, -32640 > >::TType sResult;
		_WINQ_USESAPIAW( VkKeyScan );
		sResult = Call< SHORT, TCHAR >( pFunc, ch );
		return sResult;
	}

	//--------------------------------------------------------------------------------
	SHORT CUser32::VkKeyScanEx( TCHAR ch, HKL dwhkl )
	{
		_WINQ_FCONTEXT( "CUser32::VkKeyScanEx" );
		CCheckReturn< SHORT, CTCheckFailureValue< SHORT, -32640 > >::TType sResult;
		_WINQ_USESAPI( VkKeyScanEx );
		sResult = Call< SHORT, TCHAR, HKL >( pFunc, ch, dwhkl );
		return sResult;
	}

}//nsWinQAPI
