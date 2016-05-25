//WindowClassFactory.h

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

//Factory for Window Registration Classes

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#ifndef WINQL_VIEWS_WNDCLSFACTORY_H_3
#define WINQL_VIEWS_WNDCLSFACTORY_H_3

#include "CompilerQOR.h"
#include "CodeQOR/ClassReg/ClassRegEntry.h"
#include "WinQL/GUI/WindowClass.h"
#include "WinQL/GUI/VisualModels/WindowClassModel.h"
#include "WinQL/GUI/Views/IconFactory.h"
#include "WinQL/GUI/Views/CursorFactory.h"
#include "WinQL/GUI/Views/BrushFactory.h"
#include "WinQL/GUI/GUIFactory.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	template< class TWindowClass >
	class CTWindowClassFactory : public CTGUIClassFactory< CWindowClassModel, TWindowClass >
	{
	public:

		//--------------------------------------------------------------------------------
		CTWindowClassFactory()
		{
		}

		//--------------------------------------------------------------------------------
		virtual ~CTWindowClassFactory()
		{
		}

		//--------------------------------------------------------------------------------
		virtual void* Instance( void )
		{
			return Create();
		}

		//--------------------------------------------------------------------------------
		virtual TWindowClass* Instance( CWindowClassModel& srcModel )
		{
			m_Model() = srcModel;
			return reinterpret_cast< TWindowClass* >( Instance() );
		}

		virtual TWindowClass* Create( void ) = 0;

		//--------------------------------------------------------------------------------
		virtual void SetupWndClass( TWindowClass* pResult )
		{
			pResult->SetByteAlignClient( m_Model().m_ByteAlignClient.Value() );
			pResult->SetByteAlignWindow( m_Model().m_ByteAlignWindow.Value() );
			pResult->SetDoubleClicks( m_Model().m_DblClicks.Value() );
			pResult->SetDropShadow( m_Model().m_DropShadow.Value() );
			pResult->SetGlobalClass( m_Model().m_GlobalClass.Value() );
			pResult->SetHRedrawTrigger( m_Model().m_HRedraw.Value() );
			pResult->SetNoClose( m_Model().m_NoClose.Value() );
			pResult->SetOwnDC( m_Model().m_OwnDC.Value() );
			pResult->SetSaveBits( m_Model().m_SaveBits.Value() );
			pResult->SetUseClassDC( m_Model().m_ClassDC.Value() );
			pResult->SetUsesParentDC( m_Model().m_ParentDC.Value() );
			pResult->SetVRedrawTrigger( m_Model().m_VRedraw.Value() );

			pResult->m_cbClsExtra = ( m_Model().m_ClassExtra );
			pResult->m_cbWndExtra = ( m_Model().m_WindowExtra );

			pResult->m_pIcon = m_Model().m_pIcon.Value() ? m_Model().m_pIcon.Value()->Handle()->Use() : 0;
			pResult->m_pIconSm = m_Model().m_pSmallIcon.Value() ? m_Model().m_pSmallIcon.Value()->Handle()->Use() : 0;
			pResult->m_pCursor = m_Model().m_pCursor.Value() ? m_Model().m_pCursor.Value()->Handle()->Use() : 0;
			pResult->m_pbrBackground = m_Model().m_pBackgroundBrush.Value() ? m_Model().m_pBackgroundBrush.Value()->Handle()->Use() : 0;

			pResult->m_lpszMenuName = m_Model().m_MenuName;
			pResult->m_lpszClassName = m_Model().m_ClassName;
			pResult->m_hInstance = m_Model().m_pModule.Value() ? m_Model().m_pModule.Value()->ModuleHandle().Use() : 0;
		}

	protected:

		CIconFactory m_IconFactory;
		CCursorFactory m_CursorFactory;
		CBrushFactory m_BrushFactory;
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_GUI ) CWindowClassFactory : public CTWindowClassFactory< CWindowClass >
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CWindowClassFactory );

		CWindowClassFactory();
		virtual ~CWindowClassFactory();

		virtual CWindowClass* Create( void );
		virtual CWindowClass* Instance( CWindowClassModel& srcModel );
	};

}//nsWin32

#endif//WINQL_VIEWS_WNDCLSFACTORY_H_3