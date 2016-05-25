//DesktopView.h

//A view class responsible for integrating with the system desktop or desktops on a desktop OS, Windows, KDE, Gnome, OSX
//This is a top level and potentially no-render invisible view designed to parent other views and provide them with the containment properties necessary
//to integrate correctly with the host desktop.
//Multiple monitor desktops, paging and potentially zooming virtual desktops will also need to be handled here.

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#ifndef _MONKIQOR_DESKTOPVIEW_H_
#define _MONKIQOR_DESKTOPVIEW_H_

#include "../View.h"
#include "Impl/DesktopViewImpl.h"

//------------------------------------------------------------------------------
namespace nsMonki
{
	//------------------------------------------------------------------------------
	class __MONKI_INTERFACE CDesktopView : public CDesktopViewImpl< nsPlatform::CPolicy::GUIPolicy::DesktopViewClass >
	{
	public:

	protected:
		//An implementation based in nsPlatform will be used based on what the nsPlatform::CPolicy class recommends as a desktop view implementation
	};

}//nsMonki

#endif//_MONKIQOR_DESKTOPVIEW_H_
