/* Public Domain Curses */

#include "Qurses/Windows/pdcwin.h"
#include "WinQL/Application/Process/WinQLProcess.h"

RCSID("$Id: pdcutil.c,v 1.14 2008/07/14 04:24:52 wmcbrine Exp $")

//------------------------------------------------------------------------------
void PDC_beep( void )
{
    __QCS_FCONTEXT( "PDC_beep" );

	//TODO:nsWin32::CProcess::ThisProcess()->ErrorSystem().MessageBeep( 0xFFFFFFFF );
}

//------------------------------------------------------------------------------
void PDC_napms( int ms )
{
    __QCS_FCONTEXT( "PDC_napms" );

	nsWin32::CThreadHelper ThreadHelper;
    ThreadHelper.Sleep( ms );
}

//------------------------------------------------------------------------------
const char* PDC_sysname( void )
{
	__QCS_FCONTEXT( "PDC_sysname" );
    return "Win32";
}
