//DesktopView.h

//View for Desktop

#ifndef _WINQL_GUI_VIEWS_DESKTOP_H_
#define _WINQL_GUI_VIEWS_DESKTOP_H_

#include "MammutQOR/Model.h"
#include "MonkiQOR/View.h"
#include "AppocritaQOR/Controller.h"
#include "WinQL/CodeServices/DataStructures/TMember.h"
#include "WinQL/OSGUI/GUI.h"
#include "WinQL/OSGUI/WindowFactory.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	namespace nsGUI
	{
        class __WINQL_INTERFACE COSWindow;
        class __WINQL_INTERFACE CWindowClass;
        class __WINQL_INTERFACE CWindowFactory;
		class __WINQL_INTERFACE CBaseWindowController;

		using namespace nsWin32;

		//--------------------------------------------------------------------------------
		class __WINQL_INTERFACE CDesktopView : public nsMonki::CView
		{
		public:

			static const nsWin32::GUID IID_IDesktopWindowView;// {4330AFBC-B840-4f46-B013-9BB5A94B494A}

			//--------------------------------------------------------------------------------
			static nsWin32::GUID DefaultInterfaceID()
			{
				return IID_IDesktopWindowView;
			}

			//--------------------------------------------------------------------------------
			CDesktopView()
			{
			}

			//--------------------------------------------------------------------------------
			virtual ~CDesktopView()
			{
			}

			//--------------------------------------------------------------------------------
			virtual long QueryInterface( const nsWin32::GUID& riid, void** ppInterface )
			{
				long hr = nsWin32::E_NoInterface;
				if( riid == IID_IDesktopWindowView )
				{
					*ppInterface = this;
					hr = OK;
				}
				else
				{
					//Try parts and then base
					//hr = OwnerView().QueryInterface( riid, ppInterface );
					if( hr == nsWin32::E_NoInterface )
					{
						//hr = CDataModel::QueryInterface( riid, ppInterface );
					}
				}
				return hr;
			}

            //--------------------------------------------------------------------------------
			virtual bool Animate()
			{
				bool bResult = false;
				return bResult;
			}

            virtual void DestroyWindow( void );
 
            //--------------------------------------------------------------------------------
            virtual void Update( void )
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
            virtual CWindowClass& GetWindowClass()
            {
                return WndClass();
            }

            //--------------------------------------------------------------------------------
            virtual CWindowFactory& GetWindowFactory()
            {
                return Factory();
            }

			//--------------------------------------------------------------------------------
			virtual long OnCreate( WindowHandle hWnd, CreateStruct* pCreateStruct )
			{
				__QCMP_UNREF( pCreateStruct );
				__QCMP_UNREF( hWnd );
				return 0;
			}

			
			virtual long OnDestroy( COSWindow* pWindow, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
			virtual long OnActivate( COSWindow* pWindow, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
			virtual long OnMouseActivate( COSWindow* pWindow, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
			virtual void OnClose( COSWindow* pWindow );
			virtual void OnSystemError( COSWindow* pWindow, WindowHandle hWnd, Cmp_long_ptr& lResult, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
			virtual void OnSysCommand( COSWindow* pWindow, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );

			CTMember< CWindowFactory > Factory;
			CTMember< CWindowClass > WndClass;

		protected:

			COSWindow* m_pWindow;			
	        
		};

	};//namespace nsGUI

};//namespace nsWin32

#endif//_WINQL_GUI_VIEWS_DESKTOP_H_
