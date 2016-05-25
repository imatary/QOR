//RowContainer.h

//WRT GUI Row Container

#ifndef _WINQRT_GUI_CONTROLLER_ROWCONTAINER_H_
#define _WINQRT_GUI_CONTROLLER_ROWCONTAINER_H_

#include "ContainerController.h"
//#include "GUIQOR/Models/ListModel.h"
#include "WinQL/Application/Graphics/WinQLRegion.h"

/*
//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	namespace nsGUI
	{
		//--------------------------------------------------------------------------------
		class CRowContainer : public CContainerController
		{
		public:

			//--------------------------------------------------------------------------------
			CRowContainer::CRowContainer()
			{
			}

			//--------------------------------------------------------------------------------
			CRowContainer::CRowContainer( CDataModel* pModelItem ) : CContainerController( pModelItem )
			{
			}

			//--------------------------------------------------------------------------------
			~CRowContainer()
			{
			}

			//--------------------------------------------------------------------------------
			virtual bool SetModel( CDataModel* pModelItem )
			{
				bool bResult = CContainerController::SetModel( pModelItem );

				unsigned int uiLoop;
				for( uiLoop = 0; uiLoop < m_apControllers.Size(); uiLoop ++ )
				{
					//bResult &= m_apControllers[ uiLoop ]->SetModel( Item( uiLoop ) );
				}

				return bResult;
			}


			//--------------------------------------------------------------------------------
			CLayoutModel* Item( unsigned int uiItem )
			{
				CLayoutModel* pItem = reinterpret_cast< CLayoutModel* >( DataPtr()->operator []( uiItem ) );
				return pItem;
			}

			//--------------------------------------------------------------------------------
			virtual unsigned int CalcMaxRowWidth( COSWindow* pWindow, nsGraphics::CRegion& ContainerRgn )
			{
				unsigned int uiResult = 0;
				unsigned int uiLoop;
				for( uiLoop = 0; uiLoop < DataPtr()->Size(); uiLoop++ )
				{
					uiResult += Item( uiLoop )->GetMaxWidth();
				}
				return uiResult;
			}

			//--------------------------------------------------------------------------------
			virtual unsigned int CalcNaturalRowWidth( COSWindow* pWindow, nsGraphics::CRegion& ContainerRgn )
			{
				unsigned int uiResult = 0;
				unsigned int uiLoop;
				for( uiLoop = 0; uiLoop < DataPtr()->Size(); uiLoop++ )
				{
					uiResult += Item( uiLoop )->GetNaturalWidth();
				}
				return uiResult;
			}

			//--------------------------------------------------------------------------------
			virtual unsigned int CalcMinRowWidth( COSWindow* pWindow, nsGraphics::CRegion& ContainerRgn )
			{
				unsigned int uiResult = 0;
				unsigned int uiLoop;
				for( uiLoop = 0; uiLoop < DataPtr()->Size(); uiLoop++ )
				{
					uiResult += Item( uiLoop )->GetMinWidth();
				}
				return uiResult;
			}

			//--------------------------------------------------------------------------------
			virtual unsigned int CalcMinRowHeight( COSWindow* pWindow, nsGraphics::CRegion& ContainerRgn )
			{
				unsigned int uiResult = 0;
				unsigned int uiLoop;
				for( uiLoop = 0; uiLoop < DataPtr()->Size(); uiLoop++ )
				{
					unsigned int uiMinHeight = Item( uiLoop )->GetMinHeight();
					if( uiMinHeight > uiResult )
					{
						uiResult = uiMinHeight;
					}
				}
				return uiResult;
			}

			//--------------------------------------------------------------------------------
			//default natural Row height will be largest component natural height
			virtual unsigned int CalcNaturalRowHeight( COSWindow* pWindow, nsGraphics::CRegion& ContainerRgn )
			{
				unsigned int uiResult = 0;
				unsigned int uiLoop;
				for( uiLoop = 0; uiLoop < DataPtr()->Size(); uiLoop++ )
				{
					unsigned int uiMinHeight = Item( uiLoop )->GetNaturalHeight();
					if( uiMinHeight > uiResult )
					{
						uiResult = uiMinHeight;
					}
				}
				return uiResult;
			}

			//--------------------------------------------------------------------------------
			virtual unsigned int CalcRowHeight( COSWindow* pWindow, nsGraphics::CRegion& ContainerRgn )
			{
				unsigned int uiResult = 0;
				unsigned int uiMinHeight = CalcMinRowHeight( pWindow, ContainerRgn );
				unsigned int uiNaturalHeight = CalcNaturalRowHeight( pWindow, ContainerRgn );

				nsGraphics::CRectangle rcContBox;
				ContainerRgn.GetBox( rcContBox );

				if( rcContBox.Height() > uiNaturalHeight )
				{
					uiResult = uiNaturalHeight;
				}
				else if( rcContBox.Height() > uiMinHeight )
				{
					uiResult = rcContBox.Height();
				}
				else
				{
					uiResult = uiMinHeight;
				}

				return uiResult;
			}

			//--------------------------------------------------------------------------------
			virtual bool Layout( COSWindow* pWindow, nsGraphics::CRegion& ContainerRgn )
			{
				//Establish Height of row
				unsigned int uiRowHeight = CalcRowHeight( pWindow, ContainerRgn );
				//Establish Row Left and Right outer limits from Container Rgn
				nsGraphics::CRectangle rcContainer;
				ContainerRgn.GetBox( rcContainer );
				nsGraphics::CRegion rgnWidestLayout( rcContainer.Left(), rcContainer.Top(), rcContainer.Right(), rcContainer.Bottom() );
				int iResult = 0;
				nsGraphics::CRegion rgnClip( ContainerRgn, rgnWidestLayout, RGN_AND, iResult );
				nsGraphics::CRectangle rcLayout;
				rgnClip.GetBox( rcLayout );

				//TODO: iResult can be used to establish if we have a complex actual container region.

				unsigned int uiRowMinWidth = CalcMinRowWidth( pWindow, ContainerRgn );
				unsigned int uiRowMaxWidth = CalcMaxRowWidth( pWindow, ContainerRgn );
				unsigned int uiMaxRowFlex = uiRowMaxWidth - uiRowMinWidth;

				if( rcLayout.Width() > uiRowMaxWidth )
				{
					//We don't have enough content to fill the row
					//Could pad according to alignment L, C or R
					//Could ignore and leave the container to manage the slack
				}

				if( uiRowMinWidth < rcLayout.Width() )
				{
					unsigned int uiRowNaturalWidth = CalcNaturalRowWidth( pWindow, ContainerRgn );

					if( uiRowNaturalWidth <= rcLayout.Width() )
					{	//items will be stretched
						
						unsigned int uiRowSlack = rcLayout.Width() - uiRowNaturalWidth;
						nsGraphics::CRectangle rcItem( rcLayout.Left(), rcLayout.Top(), rcLayout.Left(), rcLayout.Bottom() );

						//Each component gets a proportion of the row slack according to the proportion of
						//uiMaxRowFlex it's Flex represents;
						unsigned int uiLoop;
						for( uiLoop = 0; uiLoop < DataPtr()->Size(); uiLoop++ )
						{
							unsigned int uiFlex = Item( uiLoop )->GetMaxWidth() - Item( uiLoop )->GetMinWidth();
							double dFactor = ( static_cast< double >( uiFlex ) ) / ( static_cast< double >( uiMaxRowFlex ) );
							double dStretch = dFactor * ( static_cast< double >( uiRowSlack ) );
							nsGraphics::CSize ItemSize( Item( uiLoop )->GetMinWidth() + static_cast< unsigned int >( dStretch ), 0 );
							rcItem += ItemSize;

							nsGraphics::CRegion rgnItem( rcItem.Left(), rcItem.Top(), rcItem.Right(), rcItem.Bottom() );
							rgnItem.Combine( rgnClip, RGN_AND );							
							bool bSuccess = m_apControllers[ uiLoop ]->Layout( pWindow, rgnItem );
							rcItem -= ItemSize;
							rcItem.Offset( ItemSize.cx, 0 );
						}
					}
					else
					{	//items will be squeezed
					}					
				}
				else
				{
					//TODO: Either we hide/overlap something or we have a layout error, width is too small
				}

				//Establish layout direction from model
				//Loop through contained items placing them in the row
				//	Establish the minimum and maximum sizes for each contained item
				//	Establish the h-aligment LorR and the v-alignment TorB or each item
				//Calculate the minimum and maximum Row height
				//Establish the Row Left and Right real limits from Container Rgn
				//Place and Layout each item
				return true;
			}

			//--------------------------------------------------------------------------------
			void Paint( COSWindow* pWindow, WindowHandle hWnd, CDeviceContext& DC )
			{
				unsigned int uiLoop;
				for( uiLoop = 0; uiLoop < m_apControllers.Size(); uiLoop++ )
				{
					m_apControllers[ uiLoop ]->Paint( pWindow, hWnd, DC );
				}
			}

			//--------------------------------------------------------------------------------
			virtual bool ProcessMessage( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );

			//virtual Cmp_long_ptr OnNotify( Cmp_uint_ptr idCtrl, NMHDR* pHdr );

			//--------------------------------------------------------------------------------
			virtual void Append( CLayoutController* pController )
			{
				m_apControllers.Append( pController );
			}

		protected:

			//Contained Controllers
			CTArray< CLayoutController*, nsCodeQOR::mem_traits< CLayoutController* >::CTAllocator > m_apControllers;

		};

	};//namespace nsGUI

};//namespace nsWin32
*/
#endif//_WINQRT_GUI_CONTROLLER_ROWCONTAINER_H_
