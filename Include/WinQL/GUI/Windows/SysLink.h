//SysLink.h

// Copyright Querysoft Limited 2013, 2015
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

//SysLink Common Control Window

#ifndef WINQL_GUI_WND_CCTRL_SYSLINK_H_3
#define WINQL_GUI_WND_CCTRL_SYSLINK_H_3

#include "WinQL/GUI/Views/WindowView.h"
#include "WinQL/GUI/WindowFactory.h"
#include "WinQL/GUI/Windows/WinCtrlWindow.h"
#include "MammutQOR/Model.h"
#include "WinQL/Application/Graphics/WinQLRectangle.h"
#include "WinQL/GUI/CommonCtrl.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{

#if		( _WIN32_WINNT >= 0x0501 )
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_GUI ) CSysLinkClass : public CWindowClass
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CSysLinkClass );

		CSysLinkClass();
		virtual ~CSysLinkClass();
		virtual bool Preregistered();
		const TCHAR* Name();

	private:

		CCommonCtrl m_ComCtrl32;

		CSysLinkClass( const CSysLinkClass& );
		CSysLinkClass& operator = ( const CSysLinkClass& );
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_GUI ) CSysLink : public CWinCtrlWindow
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CSysLink );

		CSysLink();
		virtual ~CSysLink();
		virtual long OnNotify( NotificationMessageHeader* pHdr );
		virtual long OnUnknownNotification( NotificationMessageHeader* pHdr );

	private:

		CSysLink( const CSysLink& );
		CSysLink& operator = ( const CSysLink& );
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_GUI ) CSysLinkFactory : public CWindowFactory
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CSysLinkFactory );

		CSysLinkFactory();
		virtual ~CSysLinkFactory();
		CSysLinkFactory( const CSysLinkFactory& );
		CSysLinkFactory& operator = ( const CSysLinkFactory& );

		virtual void* Instance( void );
		//virtual COSWindow* Instance( CWindowModel& srcModel, void* pParam );
		//virtual COSWindow::refType Ref( void* pParam );
		//virtual COSWindow::refType Ref( CWindowModel& srcModel, void* pParam );
		//virtual CSysLink* Instance( CSysLinkModel& srcModel, void* pParam );
		//virtual CSysLink::refType Ref( CSysLinkModel& srcModel, void* pParam );
			
		//--------------------------------------------------------------------------------
/*
		bool GetToolTips()
		{
#if		( _WIN32_IE >= 0x0500 )
			return GetStyleBits( SBARS_TOOLTIPS );
#else//!( _WIN32_IE >= 0x0500 )
#	if		( _WIN32_IE >= 0x0400 )
			return GetStyleBits( SBT_TOOLTIPS );
#	else
			return false;
#	endif// ( _WIN32_IE >= 0x0400 )
#endif//!( _WIN32_IE >= 0x0500 )
		}
*/

	};

#endif//( _WIN32_WINNT >= 0x0501 )

}//nsWin32

#endif//WINQL_GUI_WND_CCTRL_SYSLINK_H_3