// Public Domain Curses

#include "Qurses/Windows/pdcwin.h"
#include "WinQL/Application/Console/WinQLConsoleScreenBuffer.h"
#include "WinQL/Application/WinQLApplication.h"

RCSID("$Id: pdcgetsc.c,v 1.36 2008/07/14 04:24:52 wmcbrine Exp $")

//------------------------------------------------------------------------------
// get the cursor size/shape
int PDC_get_cursor_mode( void )
{
	__QCS_FCONTEXT( "PDC_get_cursor_mode" );

	nsWin32::ConsoleCursorInfo cci;	
    
    if( !nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->GetCursorInfo( cci ) )
	{
        return ERR;
	}

    return cci.dwSize;
}

//------------------------------------------------------------------------------
// return number of screen rows
int PDC_get_rows( void )
{
	__QCS_FCONTEXT( "PDC_get_rows" );

	nsWin32::ConsoleScreenBufferInfoEx scr;
	memset( &scr, 0, sizeof( nsWin32::ConsoleScreenBufferInfoEx ) );
	scr.cbSize = sizeof( nsWin32::ConsoleScreenBufferInfoEx );
	nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->GetInfoEx( scr );

    return scr.srWindow.Bottom - scr.srWindow.Top + 1;
}

//------------------------------------------------------------------------------
// return number of buffer rows
int PDC_get_buffer_rows( void )
{
	__QCS_FCONTEXT( "PDC_get_buffer_rows" );
    nsWin32::ConsoleScreenBufferInfoEx scr;
	memset( &scr, 0, sizeof( nsWin32::ConsoleScreenBufferInfoEx ) );
	scr.cbSize = sizeof( nsWin32::ConsoleScreenBufferInfoEx );
    nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->GetInfoEx( scr );

    return scr.dwSize.Y;
}

//------------------------------------------------------------------------------
// return width of screen/viewport
int PDC_get_columns( void )
{
	__QCS_FCONTEXT( "PDC_get_colomns" );
    nsWin32::ConsoleScreenBufferInfoEx scr;
	memset( &scr, 0, sizeof( nsWin32::ConsoleScreenBufferInfoEx ) );
	scr.cbSize = sizeof( nsWin32::ConsoleScreenBufferInfoEx );
    nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->GetInfoEx( scr );

    return scr.srWindow.Right - scr.srWindow.Left + 1;
}
