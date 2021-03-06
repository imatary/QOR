//Tab.h

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

//Tab Common Control Window

#ifndef WINQL_GUI_WND_CCTRL_TAB_H_3
#define WINQL_GUI_WND_CCTRL_TAB_H_3

#include "WinQL/GUI/Views/WindowView.h"
#include "WinQL/GUI/Windows/WinCtrlWindow.h"
#include "CommonCtrlClass.h"
#include "MammutQOR/Model.h"
#include "WinQL/Application/Graphics/WinQLRectangle.h"
#include "WinQL/GUI/Windows/CommonCtrlFactory.h"
#include "WinQL/GUI/ImageList.h"

#if		( _WIN32_IE < 0x0400 )

	typedef struct tagNMOBJECTNOTIFY : public NotificationMessageHeader
	{
		//NMHDR   hdr;
		int     iItem;
#	ifdef __IID_DEFINED__
		const IID *piid;
#	else
		const void *piid;
#	endif
		void *pObject;
		long hResult;
		unsigned long dwFlags;    // control specific flags (hints as to where in iItem it hit)
	} NMOBJECTNOTIFY, *LPNMOBJECTNOTIFY;

#endif//( _WIN32_IE < 0x0400 )

//--------------------------------------------------------------------------------
namespace nsWin32
{
	class __QOR_INTERFACE( __WINQL_GUI ) CTabFactory;

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_GUI ) CTabClass : public CCommonCtrlClass
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CTabClass );

		CTabClass();
		virtual ~CTabClass();

	private:

		CTabClass( const CTabClass& );
		CTabClass& operator = ( const CTabClass& );
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_GUI ) CTab : public CWinCtrlWindow
	{
	public:

		typedef CTabClass TWndClass;
		typedef CTabFactory TFactory;

		//--------------------------------------------------------------------------------
		typedef struct tagTCHITTESTINFO
		{
			POINT pt;
			unsigned int flags;
		} TCHITTESTINFO, *LPTCHITTESTINFO;

		//--------------------------------------------------------------------------------
		typedef struct tagTCKEYDOWN : public NotificationMessageHeader
		{
			//NMHDR hdr;
			unsigned short wVKey;
			unsigned int flags;
		} NMTCKEYDOWN;

		//--------------------------------------------------------------------------------
		struct TCITEM
		{
			unsigned int mask;
#if (_WIN32_IE >= 0x0300)
			unsigned int dwState;
			unsigned int dwStateMask;
#else
			unsigned int lpReserved1;
			unsigned int lpReserved2;
#endif
			TCHAR* pszText;
			int cchTextMax;
			int iImage;

			Cmp_long_ptr lParam;
		};

		__QCMP_STATIC_CONSTANT( int, TCN_FIRST               = (0U-550U) ); 
		__QCMP_STATIC_CONSTANT( int, TCN_LAST                = (0U-580U) );

		//Notifications
		__QCMP_STATIC_CONSTANT( int, TCN_KEYDOWN             = (TCN_FIRST - 0) );
		__QCMP_STATIC_CONSTANT( int, TCN_SELCHANGE           = (TCN_FIRST - 1) );
		__QCMP_STATIC_CONSTANT( int, TCN_SELCHANGING         = (TCN_FIRST - 2) );
#if (_WIN32_IE >= 0x0400)
		__QCMP_STATIC_CONSTANT( int, TCN_GETOBJECT           = (TCN_FIRST - 3) );
#endif      // _WIN32_IE >= 0x0400
#if (_WIN32_IE >= 0x0500)
		__QCMP_STATIC_CONSTANT( int, TCN_FOCUSCHANGE         = (TCN_FIRST - 4) );
#endif      // _WIN32_IE >= 0x0500

		//Messages
		__QCMP_STATIC_CONSTANT( int, TCM_FIRST               = 0x1300 );
		__QCMP_STATIC_CONSTANT( int, TCM_GETIMAGELIST        = ( TCM_FIRST + 2 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_SETIMAGELIST        = ( TCM_FIRST + 3 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_GETITEMCOUNT        = ( TCM_FIRST + 4 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_GETITEMA            = ( TCM_FIRST + 5 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_GETITEMW            = ( TCM_FIRST + 60 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_SETITEMA            = ( TCM_FIRST + 6 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_SETITEMW            = ( TCM_FIRST + 61 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_INSERTITEMA         = ( TCM_FIRST + 7 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_INSERTITEMW         = ( TCM_FIRST + 62 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_DELETEITEM          = ( TCM_FIRST + 8 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_DELETEALLITEMS      = ( TCM_FIRST + 9 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_GETITEMRECT         = ( TCM_FIRST + 10 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_GETCURSEL           = ( TCM_FIRST + 11 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_SETCURSEL           = ( TCM_FIRST + 12 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_HITTEST             = ( TCM_FIRST + 13 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_SETITEMEXTRA        = ( TCM_FIRST + 14 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_ADJUSTRECT          = ( TCM_FIRST + 40 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_SETITEMSIZE         = ( TCM_FIRST + 41 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_REMOVEIMAGE         = ( TCM_FIRST + 42 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_SETPADDING          = ( TCM_FIRST + 43 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_GETROWCOUNT         = ( TCM_FIRST + 44 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_GETTOOLTIPS         = ( TCM_FIRST + 45 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_SETTOOLTIPS         = ( TCM_FIRST + 46 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_GETCURFOCUS         = ( TCM_FIRST + 47 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_SETCURFOCUS         = ( TCM_FIRST + 48 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_SETMINTABWIDTH      = ( TCM_FIRST + 49 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_DESELECTALL         = ( TCM_FIRST + 50 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_HIGHLIGHTITEM       = ( TCM_FIRST + 51 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_SETEXTENDEDSTYLE    = ( TCM_FIRST + 52 ) );
		__QCMP_STATIC_CONSTANT( int, TCM_GETEXTENDEDSTYLE    = ( TCM_FIRST + 53 ) );

#ifdef UNICODE
#	define TCM_SETITEM             TCM_SETITEMW
#	define TCM_INSERTITEM          TCM_INSERTITEMW
#	define TCM_GETITEM             TCM_GETITEMW
#else
#	define TCM_SETITEM             TCM_SETITEMA
#	define TCM_INSERTITEM          TCM_INSERTITEMA
#	define TCM_GETITEM             TCM_GETITEMA
#endif

#define TCM_GETUNICODEFORMAT     CCM_GETUNICODEFORMAT
#define TCM_SETUNICODEFORMAT     CCM_SETUNICODEFORMAT

		__QOR_DECLARE_OCLASS_ID( CTab );

		CTab();
		virtual ~CTab();

		virtual long OnNotify( NotificationMessageHeader* pHdr );			
		virtual void OnClick( NotificationMessageHeader* pHdr );
		virtual bool OnDblClick( NotificationMessageHeader* pHdr );
		virtual bool OnRClick( NotificationMessageHeader* pHdr );
		virtual bool OnRDblClick( NotificationMessageHeader* pHdr );
		virtual void OnReleasedCapture( NotificationMessageHeader* pHdr );
		virtual void OnFocusChange( NotificationMessageHeader* pHdr );
		virtual void OnGetObject( NMOBJECTNOTIFY* pHdr );
		virtual void OnKeyDown( NMTCKEYDOWN* pHdr );
		virtual void OnSelChange( NotificationMessageHeader* pHdr );
		virtual bool OnSelChanging( NotificationMessageHeader* pHdr );
		virtual long OnUnknownNotification( NotificationMessageHeader* pHdr );

		void AdjustRect( bool bLarger, CRectangle& rcAdjust );
		bool DeleteAllItems();
		bool DeleteItem( int iItem );
		void DeselectAll( bool bExcludeFocus );
		long GetCurFocus();
		long GetCurSel();
		long GetExtendedStyle();
		long GetImageList();
		bool GetItem( int iItem, TCITEM& tcItem );
		long GetItemCount();
		bool GetItemRect( int iItem, CRectangle& rcItem );
		long GetRowCount();
		long GetToolTips();
		bool GetUnicodeFormat();
		bool HighlightItem( int iItem, bool bHighlight );
		long HitTest( TCHITTESTINFO& HitTestInfo );
		long InsertItem( int iItem, TCITEM& tcItem );
		void RemoveImage( int iImage );
		void SetCurFocus( int iItem );
		long SetCurSel( int iItem );
		long SetExtendedStyle( unsigned long dwExMask, unsigned long dwExStyle );
		CImageList::refType SetImageList( CImageList::refType hImageList );
		bool SetItem( int iItem, TCITEM& tcItem );
		bool SetItemExtraBytes( int nBytes );
		long SetItemSize( unsigned short wWidth, unsigned short wHeight );
		long SetMinTabWidth( int cx );
		void SetPadding( unsigned short wWidth, unsigned short wHeight );
		void SetToolTips( COSWindow::refType hToolTipWnd );
		bool SetUnicodeFormat( bool bUnicode );

	};

	//--------------------------------------------------------------------------------		
	class __QOR_INTERFACE( __WINQL_GUI ) CTabFactory : public CCommonCtrlFactory< CTab >
	{
	public:

#if (_WIN32_IE >= 0x0300)
		__QCMP_STATIC_CONSTANT( int, TCS_SCROLLOPPOSITE      = 0x0001 );   // assumes multiline tab
		__QCMP_STATIC_CONSTANT( int, TCS_BOTTOM              = 0x0002 );
		__QCMP_STATIC_CONSTANT( int, TCS_RIGHT               = 0x0002 );
		__QCMP_STATIC_CONSTANT( int, TCS_MULTISELECT         = 0x0004 );  // allow multi-select in button mode
#endif
#if (_WIN32_IE >= 0x0400)
		__QCMP_STATIC_CONSTANT( int, TCS_FLATBUTTONS         = 0x0008 );
#endif
		__QCMP_STATIC_CONSTANT( int, TCS_FORCEICONLEFT       = 0x0010 );
		__QCMP_STATIC_CONSTANT( int, TCS_FORCELABELLEFT      = 0x0020 );
#if (_WIN32_IE >= 0x0300)
		__QCMP_STATIC_CONSTANT( int, TCS_HOTTRACK            = 0x0040 );
		__QCMP_STATIC_CONSTANT( int, TCS_VERTICAL            = 0x0080 );
#endif
		__QCMP_STATIC_CONSTANT( int, TCS_TABS                = 0x0000 );
		__QCMP_STATIC_CONSTANT( int, TCS_BUTTONS             = 0x0100 );
		__QCMP_STATIC_CONSTANT( int, TCS_SINGLELINE          = 0x0000 );
		__QCMP_STATIC_CONSTANT( int, TCS_MULTILINE           = 0x0200 );
		__QCMP_STATIC_CONSTANT( int, TCS_RIGHTJUSTIFY        = 0x0000 );
		__QCMP_STATIC_CONSTANT( int, TCS_FIXEDWIDTH          = 0x0400 );
		__QCMP_STATIC_CONSTANT( int, TCS_RAGGEDRIGHT         = 0x0800 );
		__QCMP_STATIC_CONSTANT( int, TCS_FOCUSONBUTTONDOWN   = 0x1000 );
		__QCMP_STATIC_CONSTANT( int, TCS_OWNERDRAWFIXED      = 0x2000 );
		__QCMP_STATIC_CONSTANT( int, TCS_TOOLTIPS            = 0x4000 );
		__QCMP_STATIC_CONSTANT( int, TCS_FOCUSNEVER          = 0x8000 );

		__QOR_DECLARE_OCLASS_ID( CTabFactory );

		CTabFactory( CTab::TWndClass* pClass, unsigned long dwStyle, unsigned long dwStyleEx );
		bool GetScrollOpposite();
		void SetScrollOpposite( bool bFlag );
		bool GetBottom();
		void SetBottom( bool bFlag );
		bool GetRight();
		void SetRight( bool bFlag );
		bool GetMultiSelect();
		void SetMultiSelect( bool bFlag );
		bool GetFlatButtons();
		void SetFlatButtons( bool bFlag );
		bool GetForceIconLeft();
		void SetForceIconLeft( bool bFlag );
		bool GetForceLabelLeft();
		void SetForceLabelLeft( bool bFlag );
		bool GetHotTrack();
		void SetHotTrack( bool bFlag );
		bool GetVertical();
		void SetVertical( bool bFlag );
		bool GetTabs();
		void SetTabs( bool bFlag );
		bool GetButtons();
		void SetButtons( bool bFlag );
		bool GetSingleLine();
		void SetSingleLine( bool bFlag );
		bool GetMultiLine();
		void SetMultiLine( bool bFlag );
		bool GetRightJustify();
		void SetRightJustify( bool bFlag );
		bool GetFixedWidth();
		void SetFixedWidth( bool bFlag );
		bool GetRaggedRight();
		void SetRaggedRight( bool bFlag );
		bool GetFocusOnButtonDown();
		void SetFocusOnButtonDown( bool bFlag );
		bool GetOwnerDrawFixed();
		void SetOwnerDrawFixed( bool bFlag );
		bool GetToolTips();
		void SetToolTips( bool bFlag );
		bool GetFocusNever();
		void SetFocusNever( bool bFlag );

	private:

		CTabFactory();
		CTabFactory( const CTabFactory& );
		CTabFactory& operator = ( const CTabFactory& );
	};

}//nsWin32

#endif//WINQL_GUI_WND_CCTRL_TAB_H_3
