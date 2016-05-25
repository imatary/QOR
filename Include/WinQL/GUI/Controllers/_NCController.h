//NCController.h

//WRT GUI Default Controller for Non Client handling

#ifndef _WINQRT_GUI_CONTROLLER_NC_H_
#define _WINQRT_GUI_CONTROLLER_NC_H_

#include "../Controller.h"
#include "../Models/GUIModel.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	namespace nsGUI
	{
		//--------------------------------------------------------------------------------
		class CNCController : public CController
		{
		public:

			//--------------------------------------------------------------------------------
			CNCController::CNCController()
			{
			}

			//--------------------------------------------------------------------------------
			CNCController::CNCController( CModelItem* pModelItem ) : CController( pModelItem )
			{
			}

			//--------------------------------------------------------------------------------
			~CNCController()
			{
			}

			//--------------------------------------------------------------------------------
			CGUIModel* DataPtr()
			{
				return reinterpret_cast< CGUIModel* >( m_pModelItem );
			}

			//--------------------------------------------------------------------------------
			virtual bool ProcessMessage( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );

			virtual void OnNCCreate( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
			virtual void OnNCActivate( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
			virtual void OnNCDestroy( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
			virtual void OnNCCalcSize( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
			virtual void OnNCPaint( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
			virtual void OnNCHitTest( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
			virtual void OnNCMouseMove( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
			virtual void OnNCLButtonDown( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
			virtual void OnNCLButtonUp( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
			virtual void OnNCLButtonDblClk( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
			virtual void OnNCRButtonDown( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
			virtual void OnNCRButtonUp( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
			virtual void OnNCRButtonDblClk( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
			virtual void OnNCMButtonDown( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
			virtual void OnNCMButtonUp( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
			virtual void OnNCMButtonDblClk( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
			virtual void OnNCSize( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
		};

	};//namespace nsGUI

};//namespace nsWin32

#endif//_WINQRT_GUI_CONTROLLER_NC_H_
