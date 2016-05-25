//Dialog.h

//Dialog

#ifndef _WINQL_WND_DIALOG_H_
#define _WINQL_WND_DIALOG_H_

#pragma __QCMP_OPTIMIZEINCLUDE

#include "WinQL/OSGUI/Window.h"
#include "MammutQOR/Model.h"
#include "WinQL/OSGUI/MessageHandler.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	namespace nsGUI
	{
		//--------------------------------------------------------------------------------
		class __QOR_INTERFACE( __WINQL ) CDialog : public COSWindow
		{
		public:

			//Messages

			__QCMP_STATIC_CONSTANT( int, DM_GETDEFID         = ( COSWindow::wmUser + 0 ) );
			__QCMP_STATIC_CONSTANT( int, DM_SETDEFID         = ( COSWindow::wmUser + 1 ) );

#if		(WINVER >= 0x0400)
			__QCMP_STATIC_CONSTANT( int, DM_REPOSITION       = ( COSWindow::wmUser + 2 ) );
#endif//(WINVER >= 0x0400)

			//--------------------------------------------------------------------------------
			CDialog( void* pParam ) : COSWindow( 0, pParam )
			{				
			}

			//--------------------------------------------------------------------------------
			virtual ~CDialog()
			{
			}

			//--------------------------------------------------------------------------------
			void Create( const TCHAR* lpWindowName, InstanceHandle hInstance, unsigned long dwStyle = nsWin32::nsGUI::COSWindow::eWSOverlappedWindow, unsigned long dwExStyle = COSWindow::eWSExAppWindow, int x = CW_UseDefault, int y = CW_UseDefault, int nWidth = CW_UseDefault, int nHeight = CW_UseDefault, WindowHandle hWndParent = 0, MenuHandle hMenu = 0 )
			{
				//p_tWndHandleMap->PendingAdd( this );				
				m_pWin32Dialog = new nsWin32::nsGUI::CDialog( hInstance, m_pTemplate, hWndParent, &CDialog::StaticCallback, reinterpret_cast< Cmp_long_ptr >( this ) );
				//m_pOSWindow = new nsWin32::nsGUI::COSWindow( m_pWin32Dialog->Handle() );
				//p_tWndHandleMap->Add( m_pOSWindow->Handle(), this );
			}

			//--------------------------------------------------------------------------------
			static Cmp_int_ptr __QCMP_STDCALLCONVENTION StaticCallback( WindowHandle hwndDlg, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam )
			{
				//_WINQRT_FCONTEXT( "CDialog::StaticCallback" );
				Cmp_int_ptr iResult = 0;
				CDialog* pDialog = reinterpret_cast< CDialog* >( lParam );
				if( pDialog != NULL )
				{
					iResult = pDialog->InstanceCallback( hwndDlg, uMsg, wParam );
				}
				return iResult;
			}

			//--------------------------------------------------------------------------------
			virtual Cmp_int_ptr InstanceCallback( WindowHandle hwndDlg, unsigned int uMsg, Cmp_uint_ptr wParam )
			{
				//_WINQRT_FCONTEXT( "CDialog::InstanceCallback" );
				Cmp_int_ptr iResult = 0;
				/*
				if( m_pDialogFunc != NULL )
				{
					iResult = (m_pDialogFunc)( hwndDlg, uMsg, wParam, m_dwInitParam );
				}
				else
				{
					iResult = DefaultProc( uMsg, wParam, m_dwInitParam );
				}
				*/
				return iResult;
			}

			//--------------------------------------------------------------------------------
			long GetDefaultID()
			{
				long lResult = m_Win32MsgHandler.Send( Handle(), (unsigned int) DM_GETDEFID, 0, 0 );
				return lResult;
			}

			//--------------------------------------------------------------------------------
			void Reposition()
			{
				m_Win32MsgHandler.Send( Handle(), (unsigned int) DM_REPOSITION, 0, 0 );				
			}

			//--------------------------------------------------------------------------------
			void SetDefaultID( Cmp_uint_ptr DefID )
			{
				m_Win32MsgHandler.Send( Handle(), (unsigned int) DM_SETDEFID, DefID, 0 );
			}

		protected:

			DLGTEMPLATE* m_pTemplate;
			nsWin32::nsGUI::CDialog* m_pWin32Dialog;
			nsWin32::nsGUI::CMessageHandler m_Win32MsgHandler;

		};

	};//namespace nsGUI

};//namespace nsWin32

#endif//_WINQL_WND_DIALOG_H_


