//WinQLAppWindowController.cpp

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

#include "SystemQOR.h"
__QCMP_WARNING_PUSH
__QCMP_WARNING_DISABLE( __QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST, "Safe usage: saved in member for later use" );
#include "WinQL/GUI/Controllers/AppWindowController.h"
#include "WinQL/GUI/Window.h"
#include "WinQL/Application/Graphics/WinQLRectangle.h"
#include "WinQL/Application/Graphics/WinQLRegion.h"
__QCMP_WARNING_POP

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_OCLASS_LUID( CAppWindowController );

	//--------------------------------------------------------------------------------
	CAppWindowController::CAppWindowController()
	{
		_WINQ_FCONTEXT( "CAppWindowController::CAppWindowController" );
	}

	//--------------------------------------------------------------------------------
	CAppWindowController::CAppWindowController( nsMammut::CModel* pModelItem ) : CBaseWindowController( pModelItem )
	{
		_WINQ_FCONTEXT( "CAppWindowController::CAppWindowController" );
	}

	//--------------------------------------------------------------------------------
	CAppWindowController::~CAppWindowController()
	{
		_WINQ_FCONTEXT( "CAppWindowController::~CAppWindowController" );
	}

	//--------------------------------------------------------------------------------
	bool CAppWindowController::ProcessMessage( COSWindow& Window, Cmp_long_ptr& lResult, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam )
	{
		_WINQ_FCONTEXT( "CAppWindowController::ProcessMessage" );

		bool bProcessed = ProcessHook( Window, lResult, uMsg, wParam, lParam );

		if( !bProcessed )
		{
			switch ( uMsg )
			{

			case COSWindow::wmEnterIdle:
				{
					lResult = Window.DefProc( uMsg, wParam, lParam );
					COSWindow::refType refWnd = COSWindow::FromHandle( CWindowHandle( 0, (void*)( lParam ) ).Ref() );
					OnEnterIdle( wParam, refWnd );
					bProcessed = true;					
				}
				break;

			case COSWindow::wmSysCommand:
				{
					Window.DefProc( uMsg, wParam, lParam );
					unsigned short wYPos = 0;
					unsigned short wXPos = LoWord( lParam );
					unsigned short wData = HiWord( lParam );
					bool bAcceleratorUsed = ( wData == -1 ) ? true : false;
					bool bMnemonic = ( wData == 0 ) ? true : false;
					if( !bAcceleratorUsed && !bMnemonic )
					{
						wYPos = wData;
					}
					OnSysCommand( wParam , wYPos, wXPos, bAcceleratorUsed, bMnemonic );
					lResult = 0;
					bProcessed = true;
				}
				break;

			case COSWindow::wmDropFiles:
				{
					void* hDropInfo = reinterpret_cast< void* >( wParam );
					OnDropFiles( hDropInfo );
					lResult = 0;
					bProcessed = true;					
				}
				break;

			case COSWindow::wmQueryEndSession:
				{
					bool bLoggingOff = ( lParam & COSWindow::EndSessionLogOff ) > 0 ? true : false;
					lResult = OnQueryEndSession( bLoggingOff ) ? true : false;
					bProcessed = true;
				}
				break;

			case COSWindow::wmEndSession:
				{
					bool bEnd = wParam ? true : false;
					bool bLoggingOff = ( lParam & COSWindow::EndSessionLogOff ) > 0 ? true : false;
					OnEndSession( bEnd, bLoggingOff );
					lResult = 0;
					bProcessed = true;
				}
				break;

			case COSWindow::wmQueryNewPalette:
				{
					lResult = OnQueryNewPalette() ? true : false;
					Window.DefProc( uMsg, wParam, lParam );
					bProcessed = true;
				}
				break;

			case COSWindow::wmPaletteChanged:
				{
					Window.DefProc( uMsg, wParam, lParam );
					COSWindow::refType refWnd = COSWindow::FromHandle( CWindowHandle( 0, (void*)( wParam ) ).Ref() );
					OnPaletteChanged( refWnd );
					bProcessed = true;
				}
				break;
/*
			case WM_COMMAND:
				{
					WindowHandle hWnd = reinterpret_cast< WindowHandle >( lParam );
					unsigned short wNotify = HIWORD( wParam );
					unsigned short wID = LOWORD( wParam );
					nsCodeQOR::CTLRef< COSWindow > rpWindow( COSWindow::FromHandle( hWnd ) );
					OnCommand( rpWindow, wNotify, wID );
					lResult = 0;
					bProcessed = true;
				}
				break;
*/
			case COSWindow::wmActivateApp:
				{
					bool bActivate = wParam ? true : false;
					unsigned long dwThreadID = lParam;
					OnActivateApp( bActivate, dwThreadID );
					lResult = 0;
					bProcessed = true;
				}
				break;

			case COSWindow::wmDeviceChange:
				{
					lResult = Window.DefProc( uMsg, wParam, lParam );
					bProcessed = true;
				}
				break;

			default:
				bProcessed = CBaseWindowController::ProcessMessage( Window, lResult, uMsg, wParam, lParam );
			}
		}

		return bProcessed;		
	}


	//--------------------------------------------------------------------------------
	void CAppWindowController::OnEnterIdle( unsigned short wWhy, COSWindow::refType Who )
	{
		_WINQ_FCONTEXT( "CAppWindowController::OnEnterIdle" );
	}

	//--------------------------------------------------------------------------------
	void CAppWindowController::OnSysCommand( Cmp_uint_ptr nID, unsigned short wYPos, unsigned short wXPos, bool bAcceleratorUsed, bool bMnemonic )
	{
		_WINQ_FCONTEXT( "CAppWindowController::OnSysCommand" );
	}

	//--------------------------------------------------------------------------------
	void CAppWindowController::OnDropFiles( void* hDropInfo )
	{
		_WINQ_FCONTEXT( "CAppWindowController::OnDropFiles" );
	}

	//--------------------------------------------------------------------------------
	bool CAppWindowController::OnQueryEndSession( bool bLoggingOff )
	{
		_WINQ_FCONTEXT( "CAppWindowController::OnQueryEndSession" );
		return true;
	}

	//--------------------------------------------------------------------------------
	void CAppWindowController::OnEndSession( bool bEnd, bool bLoggingOff )
	{
		_WINQ_FCONTEXT( "CAppWindowController::OnEndSession" );
	}

	//--------------------------------------------------------------------------------
	bool CAppWindowController::OnQueryNewPalette()
	{
		_WINQ_FCONTEXT( "CAppWindowController::OnQueryNewPalette" );
		return false;
	}

	//--------------------------------------------------------------------------------
	void CAppWindowController::OnPaletteChanged( COSWindow::refType ChangeSource )
	{
		_WINQ_FCONTEXT( "CAppWindowController::OnPaletteChanged" );
	}
/*
	//--------------------------------------------------------------------------------
	void CAppWindowController::OnCommand( COSWindow* pWindow, unsigned short wNotify, unsigned short wID )
	{
	}
*/

	//--------------------------------------------------------------------------------
	void CAppWindowController::OnActivateApp( bool bActivate, unsigned long dwThreadID )
	{
		_WINQ_FCONTEXT( "CAppWindowController::OnActivateApp" );
		if( bActivate == true )
		{
		}
		else
		{
		}
	}

}//nsWin32
