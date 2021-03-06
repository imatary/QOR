//WinQKeyboardAccelerator.cpp

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

//Keyboard Accelerator functions

#include "WinQAPI/User32.h"
#include "../Source/SystemQOR/MSWindows/WinQAPI/include/ReturnCheck.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	//--------------------------------------------------------------------------------
	int CUser32::CopyAcceleratorTable( HACCEL hAccelSrc, LPACCEL lpAccelDst, int cAccelEntries )
	{
		_WINQ_FCONTEXT( "CUser32::CopyAcceleratorTable" );
		_WINQ_USESAPIAW( CopyAcceleratorTable );
		return Call< int, HACCEL, LPACCEL, int >( pFunc, hAccelSrc, lpAccelDst, cAccelEntries );
	}

	//--------------------------------------------------------------------------------
	HACCEL CUser32::CreateAcceleratorTable( LPACCEL lpaccl, int cEntries )
	{
		_WINQ_FCONTEXT( "CUser32::CreateAcceleratorTable" );
		CCheckReturn< HACCEL, CCheckNonZero< HACCEL > >::TType Result;
		_WINQ_USESAPI( CreateAcceleratorTable );
		Result = Call< HACCEL, LPACCEL, int >( pFunc, lpaccl, cEntries );
		return Result;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::DestroyAcceleratorTable( HACCEL hAccel )
	{
		_WINQ_FCONTEXT( "CUser32::DestroyAcceleratorTable" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( DestroyAcceleratorTable );
		bResult = Call< BOOL, HACCEL >( pFunc, hAccel );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	HACCEL CUser32::LoadAccelerators( HINSTANCE hInstance, LPCTSTR lpTableName )
	{
		_WINQ_FCONTEXT( "CUser32::LoadAccelerators" );
		CCheckReturn< HACCEL, CCheckNonZero< HACCEL > >::TType Result;
		_WINQ_USESAPI( LoadAccelerators );
		Result = Call< HACCEL, HINSTANCE, LPCTSTR >( pFunc, hInstance, lpTableName );
		return Result;
	}

	//--------------------------------------------------------------------------------
	int CUser32::TranslateAccelerator( HWND hWnd, HACCEL hAccTable, LPMSG lpMsg )
	{
		_WINQ_FCONTEXT( "CUser32::TranslateAccelerator" );
		CCheckReturn< int, CCheckNonZero< int > >::TType iResult;
		_WINQ_USESAPI( TranslateAccelerator );
		iResult = Call< int, HWND, HACCEL, LPMSG >( pFunc, hWnd, hAccTable, lpMsg );	
		return iResult;
	}

}//nsWinQAPI

