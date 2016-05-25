/* Public Domain Curses */

#include "Qurses/curspriv.h"

RCSID("$Id: touch.c,v 1.29 2008/07/13 16:08:18 wmcbrine Exp $")

/*man-start**************************************************************

  Name:                                                         touch

  Synopsis:
        int touchwin(WINDOW *win);
        int touchline(WINDOW *win, int start, int count);
        int untouchwin(WINDOW *win);
        int wtouchln(WINDOW *win, int y, int n, int changed);
        bool is_linetouched(WINDOW *win, int line);
        bool is_wintouched(WINDOW *win);

  Description:
        touchwin() and touchline() throw away all information about 
        which parts of the window have been touched, pretending that the 
        entire window has been drawn on.  This is sometimes necessary 
        when using overlapping windows, since a change to one window 
        will affect the other window, but the records of which lines 
        have been changed in the other window will not reflect the 
        change.

        untouchwin() marks all lines in the window as unchanged since 
        the last call to wrefresh().

        wtouchln() makes n lines in the window, starting at line y, look 
        as if they have (changed == 1) or have not (changed == 0) been 
        changed since the last call to wrefresh().

        is_linetouched() returns TRUE if the specified line in the 
        specified window has been changed since the last call to 
        wrefresh().

        is_wintouched() returns TRUE if the specified window 
        has been changed since the last call to wrefresh().

  Return Value:
        All functions return OK on success and ERR on error except
        is_wintouched() and is_linetouched().

  Portability                                X/Open    BSD    SYS V
        touchwin                                Y       Y       Y
        touchline                               Y       -      3.0
        untouchwin                              Y       -      4.0
        wtouchln                                Y       Y       Y
        is_linetouched                          Y       -      4.0
        is_wintouched                           Y       -      4.0

**man-end****************************************************************/

//------------------------------------------------------------------------------
int touchwin(WINDOW *win)
{
	__QCS_FCONTEXT( "touchwin" );
    
	int i;

    if( !win )
	{
        return ERR;
	}

    for (i = 0; i < win->_maxy; i++)
    {
        win->_firstch[i] = 0;
        win->_lastch[i] = win->_maxx - 1;
    }

    return 0;
}

//------------------------------------------------------------------------------
int touchline( WINDOW* win, int start, int count )
{
	__QCS_FCONTEXT( "touchline" );

    int i;

    if( !win || start > win->_maxy || start + count > win->_maxy )
	{
        return ERR;
	}

    for (i = start; i < start + count; i++)
    {
        win->_firstch[i] = 0;
        win->_lastch[i] = win->_maxx - 1;
    }

    return 0;
}

//------------------------------------------------------------------------------
int untouchwin( WINDOW* win )
{
	__QCS_FCONTEXT( "untouchwin" );

    int i;

    if( !win )
	{
        return ERR;
	}

    for( i = 0; i < win->_maxy; i++ )
    {
        win->_firstch[i] = _NO_CHANGE;
        win->_lastch[i] = _NO_CHANGE;
    }

    return 0;
}

//------------------------------------------------------------------------------
int wtouchln( WINDOW* win, int y, int n, int changed )
{
	__QCS_FCONTEXT( "wtouchln" );

    int i;

    if( !win || y > win->_maxy || y + n > win->_maxy )
	{
        return ERR;
	}

    for( i = y; i < y + n; i++ )
    {
        if (changed)
        {
            win->_firstch[i] = 0;
            win->_lastch[i] = win->_maxx - 1;
        }
        else 
        {
            win->_firstch[i] = _NO_CHANGE;
            win->_lastch[i] = _NO_CHANGE;
        }
    }

    return 0;
}

//------------------------------------------------------------------------------
bool is_linetouched( WINDOW* win, int line )
{
    __QCS_FCONTEXT( "is_linetouched" );

    if( !win || line > win->_maxy || line < 0 )
	{
        return FALSE;
	}

    return ( win->_firstch[ line ] != _NO_CHANGE ) ? TRUE : FALSE;
}

//------------------------------------------------------------------------------
bool is_wintouched( WINDOW* win )
{
	__QCS_FCONTEXT( "is_wintouched" );

    int i;

    if( win )
	{
        for( i = 0; i < win->_maxy; i++ )
		{
            if( win->_firstch[ i ] != _NO_CHANGE )
			{
                return TRUE;
			}
		}
	}

    return FALSE;
}
