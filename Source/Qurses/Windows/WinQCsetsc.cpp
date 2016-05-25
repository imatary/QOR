/* Public Domain Curses */

#include "Qurses/Windows/pdcwin.h"
#include "WinQL/Application/Console/WinQLConsoleScreenBuffer.h"
#include "WinQL/Application/WinQLApplication.h"

RCSID("$Id: pdcsetsc.c,v 1.40 2008/07/14 04:24:52 wmcbrine Exp $")

/*man-start**************************************************************

  Name:                                                         pdcsetsc

  Synopsis:
        int PDC_set_blink(bool blinkon);
        void PDC_set_title(const char *title);

  Description:
        PDC_set_blink() toggles whether the A_BLINK attribute sets an
        actual blink mode (TRUE), or sets the background color to high
        intensity (FALSE). The default is platform-dependent (FALSE in
        most cases). It returns OK if it could set the state to match 
        the given parameter, ERR otherwise. Current platforms also 
        adjust the value of COLORS according to this function -- 16 for 
        FALSE, and 8 for TRUE.

        PDC_set_title() sets the title of the window in which the curses
        program is running. This function may not do anything on some
        platforms. (Currently it only works in Win32 and X11.)

  Portability                                X/Open    BSD    SYS V
        PDC_set_blink                           -       -       -
        PDC_set_title                           -       -       -

**man-end****************************************************************/

//------------------------------------------------------------------------------
int PDC_curs_set( int visibility )
{
	__QCS_FCONTEXT( "PDC_curs_set" );

	nsWin32::ConsoleCursorInfo cci;
    
    int ret_vis;

    ret_vis = SP->visibility;
	
    if( !nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->GetCursorInfo( cci ) )
	{
        return ERR;
	}

    switch(visibility)
    {
    case 0:             /* invisible */
        cci.bVisible = FALSE;
        break;
    case 2:             /* highly visible */
        cci.bVisible = TRUE;
        cci.dwSize = 95;
        break;
    default:            /* normal visibility */
        cci.bVisible = TRUE;
        cci.dwSize = SP->orig_cursor;
        break;
    }

	if( !nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->SetCursorInfo( cci ) )
	{
		return ERR;
	}

    SP->visibility = visibility;
    return ret_vis;
}

//------------------------------------------------------------------------------
void PDC_set_title( const char* title )
{
	__QCS_FCONTEXT( "PDC_set_title" );

	nsWin32::CAString strTitle( title );
#if __QOR_UNICODE
    wchar_t wtitle[512];
#endif
    PDC_LOG(("PDC_set_title() - called:<%s>\n", title));

#if __QOR_UNICODE
    PDC_mbstowcs(wtitle, title, 511);
	nsWin32::CConsole::TheWin32Console()->Title.Set( strTitle.toWString() );
#else
	nsWin32::CConsole::TheWin32Console()->Title.Set( strTitle.toTString() );
#endif
}

//------------------------------------------------------------------------------
int PDC_set_blink( bool blinkon )
{
	__QCS_FCONTEXT( "PDC_set_blink" );

    if( pdc_color_started )
	{
        COLORS = 16;
	}

    return blinkon ? ERR : nsWin32::OK;
}
