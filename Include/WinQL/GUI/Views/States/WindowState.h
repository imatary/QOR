//WindowState.h

//State for Window View

#ifndef _WINQL_GUI_VIEWS_STATES_WINDOW_H_
#define _WINQL_GUI_VIEWS_STATES_WINDOW_H_

#include "MammutQOR/Model.h"
#include "MonkiQOR/View/State.h"
#include "WinQL/OSGUI/GUI.h"
#include "WinQL/OSGUI/WindowFactory.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	namespace nsGUI
	{
		class __WINQL_INTERFACE CWindowView;

		//--------------------------------------------------------------------------------
		class __WINQL_INTERFACE CWindowState : public nsMonki::CState
		{
		public:

			//TODO: Add maximization state, on top state, activation state, enable state, visible state

			//--------------------------------------------------------------------------------
			CWindowState( nsMonki::CView* pView ) : nsMonki::CState( pView )// : m_pWindow( 0 ), m_pController( 0 )
			{
			}

			//--------------------------------------------------------------------------------
			virtual ~CWindowState()
			{
			}

			//--------------------------------------------------------------------------------
			virtual void Enable( bool bEnable )
			{
				__QCMP_UNREF( bEnable );
			}

			//--------------------------------------------------------------------------------
			COSWindow& Window()
			{
				return *m_pWindow;
			}

            //--------------------------------------------------------------------------------
			bool RegisterOwnedWindow( COSWindow* pWindow )
			{
				m_apOwnedWindows.Append( pWindow );
				return true;
			}

			//--------------------------------------------------------------------------------
			COSWindow* OwnedWindow( unsigned int uiIndex )
			{
				return m_apOwnedWindows[ uiIndex ];
			}

			//--------------------------------------------------------------------------------
			unsigned int OwnedWindowCount()
			{
				return m_apOwnedWindows.Size();
			}

			//--------------------------------------------------------------------------------
			bool RegisterChildWindow( COSWindow* pWindow )
			{
				m_apChildWindows.Append( pWindow );
				return true;
			}

			//--------------------------------------------------------------------------------
			COSWindow* ChildWindow( unsigned int uiIndex )
			{
				return m_apChildWindows[ uiIndex ];
			}

			//--------------------------------------------------------------------------------
			unsigned int ChildWindowCount()
			{
				return m_apChildWindows.Size();
			}

		protected:

			nsCodeQOR::CTArray< COSWindow*, nsWin32::CPolicy > m_apChildWindows;
			nsCodeQOR::CTArray< COSWindow*, nsWin32::CPolicy > m_apOwnedWindows;

			COSWindow* m_pWindow;			

		};

	};//namespace nsGUI

};//namespace nsWin32

#endif//_WINQL_GUI_VIEWS_STATES_WINDOW_H_
