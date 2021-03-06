//WinQLFrameWindow.cpp

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
__QCMP_WARNING_DISABLE( __QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST, "Safe usafe: stored in member for later use" );
#include "WinQL/GUI/VisualModels/FrameWindowModel.h"
#include "WinQL/GUI/Windows/FrameWindow.h"
#include "WinQL/GUI/VisualModels/FrameWindowClassModel.h"
#include "WinQL/GUI/VisualModels/FrameWindowStyleModel.h"
#include "WinQL/GUI/Views/FrameWindowClassFactory.h"
__QCMP_WARNING_POP

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_OCLASS_LUID( CFrameWindowClass );

	//--------------------------------------------------------------------------------
	CFrameWindowClass::CFrameWindowClass()
	{ 
		_WINQ_FCONTEXT( "CFrameWindowClass::CFrameWindowClass" );
	}

	//--------------------------------------------------------------------------------
	CFrameWindowClass::~CFrameWindowClass()
	{ 
		_WINQ_FCONTEXT( "CFrameWindowClass::~CFrameWindowClass" );
	}

	//--------------------------------------------------------------------------------
	const mxTCHAR* CFrameWindowClass::Name()
	{ 
		_WINQ_FCONTEXT( "CFrameWindowClass::Name" );
		return _TXT( "WinQLFrameWindow" ); 
	}

	//--------------------------------------------------------------------------------
	bool CFrameWindowClass::Registered( bool bRegister )
	{
		_WINQ_FCONTEXT( "CFrameWindowClass::Registered" );
		static bool sbRegistered = false;
		if( bRegister == true )
		{
			sbRegistered = true;
		}
		return sbRegistered;
	}





	__QOR_IMPLEMENT_OCLASS_LUID( CFrameWindowFactory );

	//--------------------------------------------------------------------------------
	CFrameWindowFactory::CFrameWindowFactory() : CTWindowFactory< class CFrameWindowModel, class CFrameWindow >()
	{
		_WINQ_FCONTEXT( "CFrameWindowFactory::CFrameWindowFactory" );
	}

	//--------------------------------------------------------------------------------
	CFrameWindowFactory::~CFrameWindowFactory()
	{	
		_WINQ_FCONTEXT( "CFrameWindowFactory::~CFrameWindowFactory" );
	}

	//--------------------------------------------------------------------------------
	CFrameWindow* CFrameWindowFactory::Create( CWindowClass* pWndClass, CMenu* pMenu )
	{
		_WINQ_FCONTEXT( "CFrameWindowFactory::Create" );

		return new CFrameWindow( pWndClass, m_StyleEx, m_Model().m_Name.Value(), m_Style, m_Model().m_Layout.Value().m_XPos, m_Model().m_Layout.Value().m_YPos,
			m_Model().m_Layout.Value().m_Width.Value(), m_Model().m_Layout.Value().m_Height.Value(), 
			m_Model().m_Parent.Value() ? m_Model().m_Parent.Value()->Handle() : CWindowHandle::refType(), 
			pMenu ? pMenu->Handle() : CMenuHandle::refType(), m_Model().m_Module.Value(), m_pUserParam );
	}




	//--------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID( CFrameWindow );

	//--------------------------------------------------------------------------------
	CFrameWindow::CFrameWindow()
	{
		_WINQ_FCONTEXT( "CFrameWindow::CFrameWindow" );
	}

	//--------------------------------------------------------------------------------
	CFrameWindow::CFrameWindow( CWindowClass* pClass, unsigned long dwExStyle, const TCHAR* lpWindowName, unsigned long dwStyle, int x, int y, int nWidth, int nHeight, CWindowHandle::refType hWndParent, CMenuHandle::refType hMenu, CWinModule* pModule, void* lpParam ) : 
		COSWindow( pClass, dwExStyle, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, pModule, lpParam )
	{
		_WINQ_FCONTEXT( "CFrameWindow::CFrameWindow" );
	}

	//--------------------------------------------------------------------------------
	CFrameWindow::~CFrameWindow()
	{
		_WINQ_FCONTEXT( "CFrameWindow::~CFrameWindow" );
	}


}//nsWin32

