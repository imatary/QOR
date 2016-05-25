//ColumnContainer.h

//GUI Column Container

#ifndef _WINQL_GUI_CONTROLLER_COLCONTAINER_H_
#define _WINQL_GUI_CONTROLLER_COLCONTAINER_H_

#include "ContainerController.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	namespace nsGUI
	{
		//--------------------------------------------------------------------------------
		class __WINQL_INTERFACE CColumnContainer : public CContainerController
		{
		public:

			//--------------------------------------------------------------------------------
			CColumnContainer::CColumnContainer()
			{
			}

			//--------------------------------------------------------------------------------
			CColumnContainer::CColumnContainer( nsMammut::CModel* pModelItem ) : CContainerController( pModelItem )
			{
			}

			//--------------------------------------------------------------------------------
			~CColumnContainer()
			{
			}

			//--------------------------------------------------------------------------------
			CListModel* DataPtr()
			{
				return reinterpret_cast< CListModel* >( m_pModel );
			}

			//--------------------------------------------------------------------------------
			virtual bool Layout( COSWindow* pWindow, nsWin32::nsGraphics::CRegion& ContainerRgn )
			{
				return true;
			}

			//--------------------------------------------------------------------------------
			void Paint( COSWindow* pWindow, WindowHandle hWnd, CDeviceContext& DC )
			{
			}

			//--------------------------------------------------------------------------------
			//virtual bool ProcessMessage( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );

			//virtual Cmp_long_ptr OnNotify( Cmp_uint_ptr idCtrl, NMHDR* pHdr );

		};

	};//namespace nsGUI

};//namespace nsWin32

#endif//_WINQL_GUI_CONTROLLER_COLCONTAINER_H_
