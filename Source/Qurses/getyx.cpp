/* Public Domain Curses */

#include "Qurses/curspriv.h"

RCSID("$Id: getyx.c,v 1.29 2008/07/15 17:13:26 wmcbrine Exp $")

/*man-start**************************************************************

  Name:                                                         getyx

  Synopsis:
        void getyx(WINDOW *win, int y, int x);
        void getparyx(WINDOW *win, int y, int x);
        void getbegyx(WINDOW *win, int y, int x);
        void getmaxyx(WINDOW *win, int y, int x);

        void getsyx(int y, int x);
        int setsyx(int y, int x);

        int getbegy(WINDOW *win);
        int getbegx(WINDOW *win);
        int getcury(WINDOW *win);
        int getcurx(WINDOW *win);
        int getpary(WINDOW *win);
        int getparx(WINDOW *win);
        int getmaxy(WINDOW *win);
        int getmaxx(WINDOW *win);

  Description:
        The getyx() macro (defined in curses.h -- the prototypes here 
        are merely illustrative) puts the current cursor position of the 
        specified window into y and x. getbegyx() and getmaxyx() return 
        the starting coordinates and size of the specified window, 
        respectively. getparyx() returns the starting coordinates of the 
        parent's window, if the specified window is a subwindow; 
        otherwise it sets y and x to -1. These are all macros.

        getsyx() gets the coordinates of the virtual screen cursor, and
        stores them in y and x. If leaveok() is TRUE, it returns -1, -1.
        If lines have been removed with ripoffline(), then getsyx()
        includes these lines in its count; so, the returned y and x
        values should only be used with setsyx().

        setsyx() sets the virtual screen cursor to the y, x coordinates.
        If y, x are -1, -1, leaveok() is set TRUE.

        getsyx() and setsyx() are meant to be used by a library routine
        that manipulates curses windows without altering the position of
        the cursor. Note that getsyx() is defined only as a macro.

        getbegy(), getbegx(), getcurx(), getcury(), getmaxy(),
        getmaxx(), getpary(), and getparx() return the appropriate
        coordinate or size values, or ERR in the case of a NULL window.

  Portability                                X/Open    BSD    SYS V
        getyx                                   Y       Y       Y
        getparyx                                -       -      4.0
        getbegyx                                -       -      3.0
        getmaxyx                                -       -      3.0
        getsyx                                  -       -      3.0
        setsyx                                  -       -      3.0
        getbegy                                 -       -       -
        getbegx                                 -       -       -
        getcury                                 -       -       -
        getcurx                                 -       -       -
        getpary                                 -       -       -
        getparx                                 -       -       -
        getmaxy                                 -       -       -
        getmaxx                                 -       -       -

**man-end****************************************************************/

//------------------------------------------------------------------------------
int getbegy( WINDOW* win )
{
    __QCS_FCONTEXT( "getbegy" );

    return win ? win->_begy : ERR;
}

//------------------------------------------------------------------------------
int getbegx( WINDOW* win )
{
    __QCS_FCONTEXT( "getbegx" );

    return win ? win->_begx : ERR;
}

//------------------------------------------------------------------------------
int getcury( WINDOW* win )
{
    __QCS_FCONTEXT( "getcury" );

    return win ? win->_cury : ERR;
}

//------------------------------------------------------------------------------
int getcurx( WINDOW* win )
{
    __QCS_FCONTEXT( "getcurx" );

    return win ? win->_curx : ERR;
}

//------------------------------------------------------------------------------
int getpary( WINDOW* win )
{
    __QCS_FCONTEXT( "getpary" );

    return win ? win->_pary : ERR;
}

//------------------------------------------------------------------------------
int getparx( WINDOW* win )
{
    __QCS_FCONTEXT( "getparx" );

    return win ? win->_parx : ERR;
}

//------------------------------------------------------------------------------
int getmaxy( WINDOW* win )
{
    __QCS_FCONTEXT( "getmaxy" );

    return win ? win->_maxy : ERR;
}

//------------------------------------------------------------------------------
int getmaxx( WINDOW* win )
{
    __QCS_FCONTEXT( "getmaxx" );

    return win ? win->_maxx : ERR;
}

//------------------------------------------------------------------------------
int setsyx( int y, int x )
{
	__QCS_FCONTEXT( "setsyx" );

    if( y == -1 && x == -1 )
    {
        curscr->_leaveit = TRUE;
        return 0;
    }
    else
    {
        curscr->_leaveit = FALSE;
        return wmove( curscr, y, x );
    }
}
