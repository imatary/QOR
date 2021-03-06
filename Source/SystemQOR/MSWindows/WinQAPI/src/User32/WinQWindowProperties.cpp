//WinQWindowProperties.cpp

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

//Window Properties functions

#include "WinQAPI/User32.h"
#include "../Source/SystemQOR/MSWindows/WinQAPI/include/ReturnCheck.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	//--------------------------------------------------------------------------------
	int CUser32::EnumProps( HWND hWnd, PROPENUMPROC lpEnumFunc )
	{
		_WINQ_FCONTEXT( "CUser32::EnumProps" );
		int iResult = 0;
		_WINQ_USESAPIAW( EnumProps );
		iResult = Call< int, HWND, PROPENUMPROC >( pFunc, hWnd, lpEnumFunc );
		return iResult;
	}

	//--------------------------------------------------------------------------------
	int CUser32::EnumPropsEx( HWND hWnd, PROPENUMPROCEX lpEnumFunc, LPARAM lParam )
	{
		_WINQ_FCONTEXT( "CUser32::EnumPropsEx" );
		int iResult = 0;
		_WINQ_USESAPIAW( EnumPropsEx );
		iResult = Call< int, HWND, PROPENUMPROCEX, LPARAM >( pFunc, hWnd, lpEnumFunc, lParam );
		return iResult;
	}

	//--------------------------------------------------------------------------------
	HANDLE CUser32::GetProp( HWND hWnd, LPCTSTR lpString )
	{
		_WINQ_FCONTEXT( "CUser32::GetProp" );
		CCheckReturn< HANDLE, CHandleNullCheck< > >::TType Result;
		_WINQ_USESAPIAW( GetProp );
		Result = Call< HANDLE, HWND, LPCTSTR >( pFunc, hWnd, lpString );
		return Result;
	}

	//--------------------------------------------------------------------------------
	HANDLE CUser32::RemoveProp( HWND hWnd, LPCTSTR lpString )
	{
		_WINQ_FCONTEXT( "CUser32::RemoveProp" );
		CCheckReturn< HANDLE, CHandleNullCheck< > >::TType Result;
		_WINQ_USESAPI( RemoveProp );
		Result = Call< HANDLE, HWND, LPCTSTR >( pFunc, hWnd, lpString );
		return Result;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::SetProp( HWND hWnd, LPCTSTR lpString, HANDLE hData )
	{
		_WINQ_FCONTEXT( "CUser32::SetProp" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( SetProp );
		bResult = Call< BOOL, HWND, LPCTSTR, HANDLE >( pFunc, hWnd, lpString, hData );
		return bResult;
	}

}//nsWinQAPI
