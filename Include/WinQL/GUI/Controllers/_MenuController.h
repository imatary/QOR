//MenuController.h

//WRT GUI Default Controller for Menu handling

#ifndef _WINQRT_GUI_CONTROLLER_MENU_H_
#define _WINQRT_GUI_CONTROLLER_MENU_H_

#include "../Controller.h"
#include "../Models/MenuData.h"
#include "../Menu.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	namespace nsGUI
	{
		//--------------------------------------------------------------------------------
		class CMenuController : public CController
		{
		public:

			//--------------------------------------------------------------------------------
			CMenuController::CMenuController()
			{
			}

			//--------------------------------------------------------------------------------
			CMenuController::CMenuController( CModelItem* pModelItem ) : CController()
			{
				SetModel( pModelItem );
			}

			//--------------------------------------------------------------------------------
			~CMenuController()
			{
			}

			//--------------------------------------------------------------------------------
			virtual bool SetModel( CModelItem* pModelItem )
			{
				m_pMenuData = reinterpret_cast< CMenuData* >( pModelItem );
				return true;
			}

			//--------------------------------------------------------------------------------
			CMenuData* DataPtr()
			{
				return reinterpret_cast< CMenuData* >( m_pModelItem );
			}

			//--------------------------------------------------------------------------------
			virtual bool ProcessMessage( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );			

			virtual void OnInitMenu( CMenu* pMenu );
			virtual void OnInitMenuPopup( CMenu* pMenu, unsigned short wIndex, BOOL bSysMenu );
			virtual void OnMenuSelect( unsigned short wItemID, unsigned short wFlags, CMenu* pMenu );

		protected:

			CMenuData* m_pMenuData;

		};

	};//namespace nsGUI

};//namespace nsWin32

#endif//_WINQRT_GUI_CONTROLLER_MENU_H_
