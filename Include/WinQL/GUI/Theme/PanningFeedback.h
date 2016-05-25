//PanningFeedback.h

#ifndef _QSYS_MSWINDOWS_WIN32_OSGUI_THEME_PANNINGFEEDBACK_H_
#define _QSYS_MSWINDOWS_WIN32_OSGUI_THEME_PANNINGFEEDBACK_H_

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/Definitions/Data.h"
#include "WinQL/GUI/Window.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	class __QOR_INTERFACE( __WINQAPI ) CUXTheme;
}

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_GUI ) CPanningFeedback
	{
	public:

		CPanningFeedback( COSWindow::refType Wnd );
		~CPanningFeedback();

		CPanningFeedback& operator = ( const CPanningFeedback& src );

		void AnimateBack( bool bAnimate );
		bool Update( long lTotalOverpanOffsetX, long lTotalOverpanOffsetY, bool bInInertia );

	protected:

		nsWinQAPI::CUXTheme& m_UXTheme;
		bool m_bStatus;
		COSWindow::refType m_Wnd;
		bool m_bAnimateBack;

	};

}//nsWin32

#endif//_QSYS_MSWINDOWS_WIN32_OSGUI_THEME_PANNINGFEEDBACK_H_
