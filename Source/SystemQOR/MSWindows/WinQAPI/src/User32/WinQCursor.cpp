//WinQCursor.cpp

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

//Cursor functions

#include "WinQAPI/User32.h"
#include "../Source/SystemQOR/MSWindows/WinQAPI/include/ReturnCheck.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	//--------------------------------------------------------------------------------
	BOOL CUser32::ClipCursor( const RECT* lpRect )
	{
		_WINQ_FCONTEXT( "CUser32::ClipCursor" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( ClipCursor );
		bResult = Call< BOOL, const RECT* >( pFunc, lpRect );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	HCURSOR CUser32::mxCopyCursor( HCURSOR pcur )
	{
		_WINQ_FCONTEXT( "CUser32::mxCopyCursor" );
		CCheckReturn< HCURSOR, CCheckNonZero< HCURSOR > >::TType Result;
		_WINQ_USESAPI( CopyIcon );
		Result = Call< HCURSOR, HCURSOR >( pFunc, pcur );
		return Result;
	}

	//--------------------------------------------------------------------------------
	HCURSOR CUser32::CreateCursor( HINSTANCE hInst, int xHotSpot, int yHotSpot, int nWidth, int nHeight, const VOID* pvANDPlane, const VOID* pvXORPlane )
	{
		_WINQ_FCONTEXT( "CUser32::CreateCursor" );
		CCheckReturn< HCURSOR, CCheckNonZero< HCURSOR > >::TType Result;
		_WINQ_USESAPI( CreateCursor );
		Result = Call< HCURSOR, HINSTANCE, int, int, int, int, const void*, const void* >( pFunc, hInst, xHotSpot, yHotSpot, nWidth, nHeight, pvANDPlane, pvXORPlane );
		return Result;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::DestroyCursor( HCURSOR hCursor )
	{
		_WINQ_FCONTEXT( "CUser32::DestroyCursor" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( DestroyCursor );
		bResult = Call< BOOL, HCURSOR >( pFunc, hCursor );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::GetClipCursor( LPRECT lpRect )
	{
		_WINQ_FCONTEXT( "CUser32::GetClipCursor" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( GetClipCursor );
		bResult = Call< BOOL, LPRECT >( pFunc, lpRect );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	HCURSOR CUser32::GetCursor(void)
	{
		_WINQ_FCONTEXT( "CUser32::GetCursor" );
		CCheckReturn< HCURSOR, CCheckNonZero< HCURSOR, nsCodeQOR::CError::ERR_LVL_WARNING, API_RETURNED_NO_DATA > >::TType Result;
		_WINQ_USESAPI( GetCursor );
		Result = Call< HCURSOR >( pFunc );
		return Result;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::GetCursorInfo( PCURSORINFO pci )
	{
		_WINQ_FCONTEXT( "CUser32::GetCursorInfo" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( GetCursorInfo );
		bResult = Call< BOOL, PCURSORINFO >( pFunc, pci );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::GetCursorPos( LPPOINT lpPoint )
	{
		_WINQ_FCONTEXT( "CUser32::GetCursorPos" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( GetCursorPos );
		bResult = Call< BOOL, LPPOINT >( pFunc, lpPoint );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::GetPhysicalCursorPos( LPPOINT lpPoint )
	{
		_WINQ_FCONTEXT( "CUser32::GetPhysicalCursorPos" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( GetPhysicalCursorPos );
		bResult = Call< BOOL, LPPOINT >( pFunc, lpPoint );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	HCURSOR CUser32::LoadCursor( HINSTANCE hInstance, LPCTSTR lpCursorName )
	{
		_WINQ_FCONTEXT( "CUser32::LoadCursor" );
		CCheckReturn< HCURSOR, CCheckNonZero< HCURSOR > >::TType Result;
		_WINQ_USESAPI( LoadCursor );
		Result = Call< HCURSOR, HINSTANCE, LPCTSTR >( pFunc, hInstance, lpCursorName );
		return Result;
	}

	//--------------------------------------------------------------------------------
	HCURSOR CUser32::LoadCursorFromFile( LPCTSTR lpFileName )
	{
		_WINQ_FCONTEXT( "CUser32::LoadCursorFromFile" );
		CCheckReturn< HCURSOR, CCheckNonZero< HCURSOR > >::TType Result;
		_WINQ_USESAPI( LoadCursorFromFile );
		Result = Call< HCURSOR, LPCTSTR >( pFunc, lpFileName );
		return Result;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::SetCursorPos( int X, int Y )
	{
		_WINQ_FCONTEXT( "CUser32::SetCursorPos" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( SetCursorPos );
		bResult = Call< BOOL, int, int >( pFunc, X, Y );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::SetPhysicalCursorPos( int X, int Y )
	{
		_WINQ_FCONTEXT( "CUser32::SetPhysicalCursorPos" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( SetPhysicalCursorPos );
		bResult = Call< BOOL, int, int >( pFunc, X, Y );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	int CUser32::ShowCursor( BOOL bShow )
	{
		_WINQ_FCONTEXT( "CUser32::ShowCursor" );
		_WINQ_USESAPI( ShowCursor );
		return Call< int, BOOL >( pFunc, bShow );
	}

	//--------------------------------------------------------------------------------
	HCURSOR CUser32::SetCursor( HCURSOR hCursor )
	{
		_WINQ_FCONTEXT( "CUser32::SetCursor" );
		_WINQ_USESAPI( SetCursor );
		return Call< HCURSOR, HCURSOR >( pFunc, hCursor );
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::SetSystemCursor( HCURSOR hcur, DWORD id )
	{
		_WINQ_FCONTEXT( "CUser32::SetSystemCursor" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( SetSystemCursor );
		bResult = Call< BOOL, HCURSOR, DWORD >( pFunc, hcur, id );
		return bResult;
	}

}//nsWinQAPI

