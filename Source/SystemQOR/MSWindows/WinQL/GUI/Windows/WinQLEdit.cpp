//WinQLEdit.cpp

// Copyright Querysoft Limited 2013
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

#include "CompilerQOR.h"
__QCMP_WARNING_PUSH
__QCMP_WARNING_DISABLE( __QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST, "Safe usage: stored in member for later use" )
#include "WinQL/GUI/Windows/Edit.h"
__QCMP_WARNING_POP

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_OCLASS_LUID( CEditClass );

	//--------------------------------------------------------------------------------
	CEditClass::CEditClass()
	{ 
		_WINQ_FCONTEXT( "CEditClass::CEditClass" );
	}

	//--------------------------------------------------------------------------------
	CEditClass::~CEditClass()
	{ 
		_WINQ_FCONTEXT( "CEditClass::~CEditClass" );
	}

	//--------------------------------------------------------------------------------
	bool CEditClass::Preregistered()
	{ 
		_WINQ_FCONTEXT( "CEditClass::Preregistered" );
		return true; 
	}

	//--------------------------------------------------------------------------------
	const TCHAR* CEditClass::Name()
	{ 
		_WINQ_FCONTEXT( "CEditClass::Name" );
		return _TXT( "EDIT" ); 
	}



	//--------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID( CEditFactory );

	//--------------------------------------------------------------------------------
	CEditFactory::CEditFactory() : CWindowFactory()
	{
		_WINQ_FCONTEXT( "CEditFactory::CEditFactory" );
	}

	//--------------------------------------------------------------------------------
	CEditFactory::~CEditFactory()
	{				
		_WINQ_FCONTEXT( "CEditFactory::~CEditFactory" );
	}

	//--------------------------------------------------------------------------------
	CEdit* CEditFactory::Create()
	{
		_WINQ_FCONTEXT( "CEditFactory::Instance" );
		return new CEdit;//PreCreateWindow< CEdit, CEditClass >();
	}

	//--------------------------------------------------------------------------------
	bool CEditFactory::GetLeft()
	{
		_WINQ_FCONTEXT( "CEditFactory::GetLeft" );
		return !GetStyleBits( ES_RIGHT );
	}

	//--------------------------------------------------------------------------------
	void CEditFactory::SetLeft( bool bFlag )
	{
		_WINQ_FCONTEXT( "CEditFactory::SetLeft" );
		SetStyleBits( ES_RIGHT, !bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CEditFactory::GetCenter()
	{
		_WINQ_FCONTEXT( "CEditFactory::GetCenter" );
		return GetStyleBits( ES_CENTER );
	}

	//--------------------------------------------------------------------------------
	void CEditFactory::SetCenter( bool bFlag )
	{
		_WINQ_FCONTEXT( "CEditFactory::SetCenter" );
		SetStyleBits( ES_CENTER, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CEditFactory::GetRight()
	{
		_WINQ_FCONTEXT( "CEditFactory::GetRight" );
		return GetStyleBits( ES_RIGHT );
	}

	//--------------------------------------------------------------------------------
	void CEditFactory::SetRight( bool bFlag )
	{
		_WINQ_FCONTEXT( "CEditFactory::SetRight" );
		SetStyleBits( ES_RIGHT, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CEditFactory::GetMultiLine()
	{
		_WINQ_FCONTEXT( "CEditFactory::GetMultiLine" );
		return GetStyleBits( ES_MULTILINE );
	}

	//--------------------------------------------------------------------------------
	void CEditFactory::SetMultiLine( bool bFlag )
	{
		_WINQ_FCONTEXT( "CEditFactory::SetMultiLine" );
		SetStyleBits( ES_MULTILINE, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CEditFactory::GetUpperCase()
	{
		_WINQ_FCONTEXT( "CEditFactory::GetUpperCase" );
		return GetStyleBits( ES_UPPERCASE );
	}

	//--------------------------------------------------------------------------------
	void CEditFactory::SetUpperCase( bool bFlag )
	{
		_WINQ_FCONTEXT( "CEditFactory::SetUpperCase" );
		SetStyleBits( ES_UPPERCASE, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CEditFactory::GetLowerCase()
	{
		_WINQ_FCONTEXT( "CEditFactory::GetLowerCase" );
		return GetStyleBits( ES_LOWERCASE );
	}

	//--------------------------------------------------------------------------------
	void CEditFactory::SetLowerCase( bool bFlag )
	{
		_WINQ_FCONTEXT( "CEditFactory::SetLowerCase" );
		SetStyleBits( ES_LOWERCASE, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CEditFactory::GetPassword()
	{
		_WINQ_FCONTEXT( "CEditFactory::GetPassword" );
		return GetStyleBits( ES_PASSWORD );
	}

	//--------------------------------------------------------------------------------
	void CEditFactory::SetPassword( bool bFlag )
	{
		_WINQ_FCONTEXT( "CEditFactory::SetPassword" );
		SetStyleBits( ES_PASSWORD, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CEditFactory::GetAutoVScroll()
	{
		_WINQ_FCONTEXT( "CEditFactory::GetAutoVScroll" );
		return GetStyleBits( ES_AUTOVSCROLL );
	}

	//--------------------------------------------------------------------------------
	void CEditFactory::SetAutoVScroll( bool bFlag )
	{
		_WINQ_FCONTEXT( "CEditFactory::SetAutoVScroll" );
		SetStyleBits( ES_AUTOVSCROLL, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CEditFactory::GetAutoHScroll()
	{
		_WINQ_FCONTEXT( "CEditFactory::GetAutoHScroll" );
		return GetStyleBits( ES_AUTOHSCROLL );
	}

	//--------------------------------------------------------------------------------
	void CEditFactory::SetAutoHScroll( bool bFlag )
	{
		_WINQ_FCONTEXT( "CEditFactory::SetAutoHScroll" );
		SetStyleBits( ES_AUTOHSCROLL, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CEditFactory::GetNoHideSel()
	{
		_WINQ_FCONTEXT( "CEditFactory::GetNoHideSel" );
		return GetStyleBits( ES_NOHIDESEL );
	}

	//--------------------------------------------------------------------------------
	void CEditFactory::SetNoHideSel( bool bFlag )
	{
		_WINQ_FCONTEXT( "CEditFactory::SetNoHideSel" );
		SetStyleBits( ES_NOHIDESEL, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CEditFactory::GetOEMConvert()
	{
		_WINQ_FCONTEXT( "CEditFactory::GetOEMConvert" );
		return GetStyleBits( ES_OEMCONVERT );
	}

	//--------------------------------------------------------------------------------
	void CEditFactory::SetOEMConvert( bool bFlag )
	{
		_WINQ_FCONTEXT( "CEditFactory::SetOEMConvert" );
		SetStyleBits( ES_OEMCONVERT, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CEditFactory::GetReadOnly()
	{
		_WINQ_FCONTEXT( "CEditFactory::GetReadOnly" );
		return GetStyleBits( ES_READONLY );
	}

	//--------------------------------------------------------------------------------
	void CEditFactory::SetReadOnly( bool bFlag )
	{
		_WINQ_FCONTEXT( "CEditFactory::SetReadOnly" );
		SetStyleBits( ES_READONLY, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CEditFactory::GetWantReturn()
	{
		_WINQ_FCONTEXT( "CEditFactory::GetWantReturn" );
		return GetStyleBits( ES_WANTRETURN );
	}

	//--------------------------------------------------------------------------------
	void CEditFactory::SetWantReturn( bool bFlag )
	{
		_WINQ_FCONTEXT( "CEditFactory::SetWantReturn" );
		SetStyleBits( ES_WANTRETURN, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CEditFactory::GetNumber()
	{
		_WINQ_FCONTEXT( "CEditFactory::GetNumber" );
		return GetStyleBits( ES_NUMBER );
	}

	//--------------------------------------------------------------------------------
	void CEditFactory::SetNumber( bool bFlag )
	{
		_WINQ_FCONTEXT( "CEditFactory::SetNumber" );
		SetStyleBits( ES_NUMBER, bFlag );
	}
	
	
	
	
	__QOR_IMPLEMENT_OCLASS_LUID( CEdit );

	//--------------------------------------------------------------------------------
	CEdit::CEdit() : CWinCtrlWindow()
	{
		_WINQ_FCONTEXT( "CEdit::CEdit" );
	}

	//--------------------------------------------------------------------------------
	CEdit::~CEdit()
	{
		_WINQ_FCONTEXT( "CEdit::~CEdit" );
	}

	//--------------------------------------------------------------------------------
	void CEdit::OnCommand( unsigned short wCtrlID, unsigned short wCode )
	{
		_WINQ_FCONTEXT( "CEdit::OnCommand" );
		switch ( wCode )
		{
		case EN_SETFOCUS:
			{
				OnSetFocus();
			}
			break;
		case EN_KILLFOCUS:
			{
				OnKillFocus();
			}
			break;
		case EN_CHANGE:
			{
				OnChange();
			}
			break;
		case EN_UPDATE:
			{
				OnUpdate();
			}
			break;
		case EN_ERRSPACE:
			{
				OnErrSpace();
			}
			break;
		case EN_MAXTEXT:
			{
				OnMaxText();
			}
			break;
		case EN_HSCROLL:
			{
				OnHScroll();
			}
			break;
		case EN_VSCROLL:
			{
				OnVScroll();
			}
			break;
#if		( _WIN32_WINNT >= 0x0500 )
		case EN_ALIGN_LTR_EC:
			{
				OnAlignLTR();
			}
			break;
		case EN_ALIGN_RTL_EC:
			{
				OnAlignRTL();
			}
			break;
#endif//( _WIN32_WINNT >= 0x0500 )
		}
	}

	//--------------------------------------------------------------------------------
	void CEdit::OnSetFocus()
	{
		_WINQ_FCONTEXT( "CEdit::OnSetFocus" );
	}

	//--------------------------------------------------------------------------------
	void CEdit::OnKillFocus()
	{
		_WINQ_FCONTEXT( "CEdit::OnKillFocus" );
	}

	//--------------------------------------------------------------------------------
	void CEdit::OnChange()
	{
		_WINQ_FCONTEXT( "CEdit::OnChange" );
	}

	//--------------------------------------------------------------------------------
	void CEdit::OnUpdate()
	{
		_WINQ_FCONTEXT( "CEdit::OnUpdate" );
	}

	//--------------------------------------------------------------------------------
	void CEdit::OnErrSpace()
	{
		_WINQ_FCONTEXT( "CEdit::OnErrSpace" );
	}

	//--------------------------------------------------------------------------------
	void CEdit::OnMaxText()
	{
		_WINQ_FCONTEXT( "CEdit::OnMaxText" );
	}

	//--------------------------------------------------------------------------------
	void CEdit::OnHScroll()
	{
		_WINQ_FCONTEXT( "CEdit::OnHScroll" );
	}

	//--------------------------------------------------------------------------------
	void CEdit::OnVScroll()
	{
		_WINQ_FCONTEXT( "CEdit::OnVScroll" );
	}

	//--------------------------------------------------------------------------------
	void CEdit::OnAlignLTR()
	{
		_WINQ_FCONTEXT( "CEdit::OnAlignLTR" );
	}

	//--------------------------------------------------------------------------------
	void CEdit::OnAlignRTL()
	{
		_WINQ_FCONTEXT( "CEdit::OnAlignRTL" );
	}

	//--------------------------------------------------------------------------------
	bool CEdit::CanUndo()
	{
		_WINQ_FCONTEXT( "CEdit::CanUndo" );
		bool bResult = ( m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_CANUNDO, 0, 0 ) ? true : false );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	long CEdit::CharFromPos( unsigned short wXPos, unsigned short wYPos )
	{
		_WINQ_FCONTEXT( "CEdit::CharFromPos" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_CHARFROMPOS, 0, MakeLParam( wXPos, wYPos ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	void CEdit::EmptyUndoBuffer()
	{
		_WINQ_FCONTEXT( "CEdit::EmptyUndoBuffer" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_EMPTYUNDOBUFFER, 0, 0 );
	}

	//--------------------------------------------------------------------------------
	void CEdit::SetLineFormat( bool bSoftLineBreaks )
	{
		_WINQ_FCONTEXT( "CEdit::SetLineFormat" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_FMTLINES, static_cast< Cmp_uint_ptr >( bSoftLineBreaks ? 1 : 0 ), 0 );
	}

	//--------------------------------------------------------------------------------
	bool CEdit::GetCueBanner( wchar_t* wstrBuffer, long lBufferCount )
	{
		_WINQ_FCONTEXT( "CEdit::GetCueBanner" );
		bool bResult = false;//( m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_GETCUEBANNER, reinterpret_cast< Cmp_uint_ptr >( wstrBuffer ), static_cast< Cmp_long_ptr >( lBufferCount ) ) ? true : false );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	long CEdit::GetFirstVisibleLine()
	{
		_WINQ_FCONTEXT( "CEdit::GetFirstVisibleLine" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_GETFIRSTVISIBLELINE, 0, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CEdit::GetHandle()
	{
		_WINQ_FCONTEXT( "CEdit::GetHandle" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_GETHANDLE, 0, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	//EM_GETHILITE ??TODO:

	//--------------------------------------------------------------------------------
	long CEdit::GetIMEStatus( Cmp_uint_ptr TypeOfStatus )
	{
		_WINQ_FCONTEXT( "CEdit::GetIMEStatus" );
		long lResult = 0;// m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_GETIMESTATUS, TypeOfStatus, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CEdit::GetLimitText()
	{
		_WINQ_FCONTEXT( "CEdit::GetLimitText" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_GETLIMITTEXT, 0, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CEdit::GetLine( Cmp_uint_ptr LineIndex, TCHAR* strBuffer, unsigned short wBufferCount )
	{
		_WINQ_FCONTEXT( "CEdit::GetLine" );
		*( reinterpret_cast< unsigned short* >( strBuffer ) ) = wBufferCount;
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_GETLINE, LineIndex, reinterpret_cast< Cmp_long_ptr >( strBuffer ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CEdit::GetLineCount()
	{
		_WINQ_FCONTEXT( "CEdit::GetLineCount" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_GETLINECOUNT, 0, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CEdit::GetMargins()
	{
		_WINQ_FCONTEXT( "CEdit::GetMargins" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_GETMARGINS, 0, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	bool CEdit::GetModified()
	{
		_WINQ_FCONTEXT( "CEdit::GetModified" );
		bool bResult = ( m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_GETMODIFY, 0, 0 ) ? true : false );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	long CEdit::GetPasswordChar()
	{
		_WINQ_FCONTEXT( "CEdit::GetPasswordChar" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_GETPASSWORDCHAR, 0, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	void CEdit::GetFormatRect( CRectangle& rcFormat )
	{
		_WINQ_FCONTEXT( "CEdit::GetFormatRect" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_GETRECT, 0, reinterpret_cast< Cmp_long_ptr >( &rcFormat ) );				
	}

	//--------------------------------------------------------------------------------
	long CEdit::GetSel( unsigned long& dwSelBegin, unsigned long& dwSelEnd )
	{
		_WINQ_FCONTEXT( "CEdit::GetSel" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_GETSEL, reinterpret_cast< Cmp_uint_ptr >( &dwSelBegin ), reinterpret_cast< Cmp_long_ptr >( &dwSelEnd ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CEdit::GetThumb()
	{
		_WINQ_FCONTEXT( "CEdit::GetThumb" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_GETTHUMB, 0, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CEdit::GetWordBreakProc()
	{
		_WINQ_FCONTEXT( "CEdit::GetWordBreakProc" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_GETWORDBREAKPROC, 0, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	bool CEdit::HideBaloonTip()
	{
		_WINQ_FCONTEXT( "CEdit::HideBaloonTip" );
		bool bResult = false;//( m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_HIDEBALLOONTIP, 0, 0 ) ? true : false );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	void CEdit::LimitText( Cmp_uint_ptr CharCount )
	{
		_WINQ_FCONTEXT( "CEdit::LimitText" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_LIMITTEXT, CharCount, 0 );
	}

	//--------------------------------------------------------------------------------
	long CEdit::LineFromChar( Cmp_uint_ptr CharIndex )
	{
		_WINQ_FCONTEXT( "CEdit::LineFromChar" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_LINEFROMCHAR, CharIndex, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CEdit::GetLineStartIndex( Cmp_uint_ptr Line )
	{
		_WINQ_FCONTEXT( "CEdit::GetLineStartIndex" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_LINEINDEX, Line, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CEdit::GetLineLength( Cmp_uint_ptr CharIndex )
	{
		_WINQ_FCONTEXT( "CEdit::GetLineLength" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_LINELENGTH, CharIndex, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CEdit::Scroll( Cmp_uint_ptr HScrollChars, Cmp_long_ptr VScrollLines )
	{
		_WINQ_FCONTEXT( "CEdit::Scroll" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_LINESCROLL, HScrollChars, VScrollLines );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CEdit::PosFromChar( Cmp_uint_ptr CharIndex )
	{
		_WINQ_FCONTEXT( "CEdit::PosFromChar" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_POSFROMCHAR, CharIndex, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	void CEdit::ReplaceSel( bool bCanUndo, const TCHAR* strText )
	{
		_WINQ_FCONTEXT( "CEdit::ReplaceSel" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_REPLACESEL, static_cast< Cmp_uint_ptr >( bCanUndo ? 1 : 0 ), reinterpret_cast< Cmp_long_ptr >( strText ) );
	}

	//--------------------------------------------------------------------------------
	long CEdit::Scroll( Cmp_uint_ptr Action )
	{
		_WINQ_FCONTEXT( "CEdit::Scroll" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_SCROLL, Action, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	void CEdit::ScrollCaret()
	{
		_WINQ_FCONTEXT( "CEdit::ScrollCaret" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_SCROLLCARET, 0, 0 );
	}

	//--------------------------------------------------------------------------------
	bool CEdit::SetCueBanner( bool bShowPersist, const wchar_t* wstrCue )
	{
		_WINQ_FCONTEXT( "CEdit::SetCueBanner" );
		bool bResult = false;//( m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_SETCUEBANNER, static_cast< Cmp_uint_ptr >( bShowPersist ? 1 : 0 ), reinterpret_cast< Cmp_long_ptr >( wstrCue ) ) ? true : false );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	void CEdit::SetHandle( Cmp_uint_ptr MemHandle )
	{
		_WINQ_FCONTEXT( "CEdit::SetHandle" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_SETHANDLE, MemHandle, 0 );
	}

	//--------------------------------------------------------------------------------
	//EM_SETHILITE ??TODO:

	//--------------------------------------------------------------------------------
	long CEdit::SetIMEStatus( Cmp_uint_ptr StatusType, Cmp_long_ptr lStatus )
	{
		_WINQ_FCONTEXT( "CEdit::SetIMEStatus" );
		long lResult = 0;//m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_SETIMESTATUS, StatusType, lStatus );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	void CEdit::SetLimitText( Cmp_uint_ptr Limit )
	{
		_WINQ_FCONTEXT( "CEdit::SetLimitText" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_SETLIMITTEXT, Limit, 0 );
	}

	//--------------------------------------------------------------------------------
	void CEdit::SetMargins( Cmp_uint_ptr Margins, unsigned short wLeftMargin, unsigned short wRightMargin )
	{
		_WINQ_FCONTEXT( "CEdit::SetMargins" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_SETMARGINS, Margins, MakeLParam( wLeftMargin, wRightMargin ) );
	}

	//--------------------------------------------------------------------------------
	void CEdit::SetModified( bool bModified )
	{
		_WINQ_FCONTEXT( "CEdit::SetModified" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_SETMODIFY, static_cast< Cmp_uint_ptr >( bModified ? 1 : 0 ), 0 );
	}

	//--------------------------------------------------------------------------------
	void CEdit::SetPasswordChar( Cmp_uint_ptr PasswordChar )
	{
		_WINQ_FCONTEXT( "CEdit::SetPasswordChar" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_SETPASSWORDCHAR, PasswordChar, 0 );
	}

	//--------------------------------------------------------------------------------
	bool CEdit::SetReadOnly( bool bReadOnly )
	{
		_WINQ_FCONTEXT( "CEdit::SetReadOnly" );
		bool bResult = ( m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_SETREADONLY, static_cast< Cmp_uint_ptr >( bReadOnly ? 1 : 0 ), 0 ) ? true : false );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	void CEdit::SetFormatRect( CRectangle& rcFormat )
	{
		_WINQ_FCONTEXT( "CEdit::SetFormatRect" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_SETRECT, 0, reinterpret_cast< Cmp_long_ptr >( &rcFormat ) );
	}

	//--------------------------------------------------------------------------------
	void CEdit::SetFormatRectNP( CRectangle& rcFormat )
	{
		_WINQ_FCONTEXT( "CEdit::SetFormatRectNP" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_SETRECTNP, 0, reinterpret_cast< Cmp_long_ptr >( &rcFormat ) );
	}

	//--------------------------------------------------------------------------------
	void CEdit::SetSel( Cmp_uint_ptr SelBegin, Cmp_long_ptr SelEnd )
	{
		_WINQ_FCONTEXT( "CEdit::SetSel" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_SETSEL, SelBegin, SelEnd );
	}

	//--------------------------------------------------------------------------------
	bool CEdit::SetTabStops( Cmp_uint_ptr TabCount, unsigned int* pStops )
	{
		_WINQ_FCONTEXT( "CEdit::SetTabStops" );
		bool bResult = ( m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_SETTABSTOPS, TabCount, reinterpret_cast< Cmp_long_ptr >( pStops ) ) ? true : false );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	void CEdit::SetWordBreakProc( fpEditWordBreakCallBack pFunc )
	{
		_WINQ_FCONTEXT( "CEdit::SetWordBreakProc" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_SETWORDBREAKPROC, 0, reinterpret_cast< Cmp_long_ptr >( pFunc ) );
	}

	//--------------------------------------------------------------------------------
	/*TODO:
	bool ShowBaloonTip( EDITBALLOONTIP* pTip )
	{
		bool bResult = ( m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_SHOWBALLOONTIP, 0, reinterpret_cast< Cmp_long_ptr >( pTip ) ) ? true : false );
		return bResult;
	}
	*/

	//--------------------------------------------------------------------------------
	bool CEdit::UndoR()
	{
		_WINQ_FCONTEXT( "CEdit::UndoR" );
		bool bResult = ( m_Win32MsgHandler.Send( Ref(), (unsigned int) EM_UNDO, 0, 0 ) ? true : false );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CEdit::Undo()
	{
		_WINQ_FCONTEXT( "CEdit::Undo" );
		bool bResult = ( m_Win32MsgHandler.Send( Ref(), (unsigned int) COSWindow::wmUndo, 0, 0 ) ? true : false );
		return bResult;
	}

}//nsWin32

