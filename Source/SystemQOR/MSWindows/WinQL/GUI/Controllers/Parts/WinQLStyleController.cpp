//WinQLStyleController.cpp

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
#include "WinQL/GUI/Controllers/Parts/StyleController.h"
#include "WinQL/GUI/Window.h"
__QCMP_WARNING_POP

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_OCLASS_LUID( CStyleController );

	//--------------------------------------------------------------------------------
    CStyleController::CStyleController( nsMammut::CModel* pModelItem, nsQOR::CController::ref_type Parent ) : CBaseWindowPartController( pModelItem, Parent )
	{
		_WINQ_FCONTEXT( "CStyleController::CStyleController" );
	}

	//--------------------------------------------------------------------------------
	CStyleController::~CStyleController()
	{
		_WINQ_FCONTEXT( "CStyleController::~CStyleController" );
	}

	//--------------------------------------------------------------------------------
	bool CStyleController::ProcessMessage( COSWindow& Window, Cmp_long_ptr& lResult, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam )
	{
		_WINQ_FCONTEXT( "CStyleController::ProcessMessage" );

		bool bProcessed = ProcessHook( Window, lResult, uMsg, wParam, lParam );

		switch ( uMsg )
		{
		case COSWindow::wmStyleChanging:
			{
				STYLESTRUCT* pStyle = reinterpret_cast< STYLESTRUCT* >( lParam );
				bool bExtended = ( ( wParam == gwlExStyle ) ? true : false );
				OnStyleChanging( pStyle, bExtended );
				lResult = 0;
				bProcessed = true;
			}
			break;

		case COSWindow::wmStyleChanged:
			{
				STYLESTRUCT* pStyle = reinterpret_cast< STYLESTRUCT* >( lParam );
				bool bExtended = ( ( wParam == gwlExStyle ) ? true : false );
				OnStyleChanged( pStyle, bExtended );
				lResult = 0;
				bProcessed = true;
			}
			break;

		}

		return bProcessed;
	}

	//--------------------------------------------------------------------------------
	void CStyleController::OnStyleChanging( STYLESTRUCT* pStyle, bool bExtended )
	{
		_WINQ_FCONTEXT( "CStyleController::OnStyleChanging" );
		QOR_PP_UNREF2( pStyle, bExtended );
	}

	//--------------------------------------------------------------------------------
	void CStyleController::OnStyleChanged( STYLESTRUCT* pStyle, bool bExtended )
	{
		_WINQ_FCONTEXT( "CStyleController::OnStyleChanged" );
		QOR_PP_UNREF2( pStyle, bExtended );
	}

}//nsWin32
