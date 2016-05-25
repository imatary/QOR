//RowContainer.cpp

//#include "stdafx.h"
#include "WinQL/GUI/Controllers/RowContainer.h"
#include "WinQL/GUI/Window.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	namespace nsGUI
	{
        /*
		//--------------------------------------------------------------------------------
		bool CRowContainer::ProcessMessage( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam )
		{
			bool bProcessed = ProcessHook( pWindow, hWnd, lResult, uMsg, wParam, lParam );

			switch ( uMsg )
			{
				default:
				{
					unsigned int uiLoop;
					for( uiLoop = 0; uiLoop < m_apControllers.Size(); uiLoop ++ )
					{
						bProcessed |= m_apControllers[ uiLoop ]->ProcessMessage( pWindow, hWnd, lResult, uMsg, wParam, lParam );
					}
				}
			}			

			return bProcessed;		
		}
*/
	};//namespace nsGUI

};//namespace nsWin32
