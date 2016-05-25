//CtrlViewController.h

//WRT Control View Controller

#ifndef _WINQRT_CTRLR_CONTROLVIEW_H_
#define _WINQRT_CTRLR_CONTROLVIEW_H_

#include "InteractiveWindowController.h"
#include "../../OSGraphics/Rectangle.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	namespace nsGUI
	{
		//--------------------------------------------------------------------------------
		class __WINQL_INTERFACE CCtrlViewRenderingController : public CRenderingController
		{
		public:

			//--------------------------------------------------------------------------------
			CCtrlViewRenderingController(){}
			~CCtrlViewRenderingController(){}

			//--------------------------------------------------------------------------------			
			virtual void OnSize( COSWindow* pWindow, Cmp_uint_ptr wParam, Cmp_long_ptr lParam )
			{
				if( pWindow != 0 )
				{
					COSWindow* pImediateFrameParent = pWindow->GetParent();
					if( pImediateFrameParent != 0 )
					{
						nsGraphics::CRectangle rcFrameClient = pImediateFrameParent->GetClientRect();
						pWindow->SetPos( 0, rcFrameClient.Left(), rcFrameClient.Top(), rcFrameClient.Width(), rcFrameClient.Height(), nsWin32::nsGUI::COSWindow::swpNoZOrder | nsWin32::nsGUI::COSWindow::swpNoActivate | nsWin32::nsGUI::COSWindow::swpNoSize );
						pWindow->BringToTop();

						COSWindow* pChild = pWindow->Get( nsWin32::nsGUI::COSWindow::gwChild );
						if( pChild != 0 )
						{
							pChild->SetPos( 0, rcFrameClient.Left(), rcFrameClient.Top(), rcFrameClient.Width(), rcFrameClient.Height(), nsWin32::nsGUI::COSWindow::swpNoZOrder | nsWin32::nsGUI::COSWindow::swpNoActivate );
							pChild->BringToTop();
						}
					}

				}

			}

		};

		//--------------------------------------------------------------------------------
		class __WINQL_INTERFACE CCtrlViewController : public CInteractiveWindowController
		{
		public:

			//--------------------------------------------------------------------------------
			CCtrlViewController(){}
			~CCtrlViewController(){}

			//--------------------------------------------------------------------------------
			bool SetModel( nsMammut::CModel* pModelItem )
			{
				Rendering.Configure( &CtrlViewRenderingController() );
				return CInteractiveWindowController::SetModel( pModelItem );
			}

			nsCodeQOR::CSTMember< CCtrlViewRenderingController > CtrlViewRenderingController;

		};

	};//namespace nsGUI

};//namespace nsWin32

#endif//_WINQRT_CTRLR_CONTROLVIEW_H_
