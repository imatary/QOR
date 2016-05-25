/* Public Domain Curses */

#include "Qurses/curspriv.h"

RCSID("$Id: inchstr.c,v 1.34 2008/07/13 16:08:18 wmcbrine Exp $")

/*man-start**************************************************************

  Name:                                                         inchstr

  Synopsis:
        int inchstr(chtype *ch);
        int inchnstr(chtype *ch, int n);
        int winchstr(WINDOW *win, chtype *ch);
        int winchnstr(WINDOW *win, chtype *ch, int n);
        int mvinchstr(int y, int x, chtype *ch);
        int mvinchnstr(int y, int x, chtype *ch, int n);
        int mvwinchstr(WINDOW *, int y, int x, chtype *ch);
        int mvwinchnstr(WINDOW *, int y, int x, chtype *ch, int n);

        int in_wchstr(cchar_t *wch);
        int in_wchnstr(cchar_t *wch, int n);
        int win_wchstr(WINDOW *win, cchar_t *wch);
        int win_wchnstr(WINDOW *win, cchar_t *wch, int n);
        int mvin_wchstr(int y, int x, cchar_t *wch);
        int mvin_wchnstr(int y, int x, cchar_t *wch, int n);
        int mvwin_wchstr(WINDOW *win, int y, int x, cchar_t *wch);
        int mvwin_wchnstr(WINDOW *win, int y, int x, cchar_t *wch, int n);

  Description:
        These routines read a chtype or cchar_t string from the window, 
        starting at the current or specified position, and ending at the 
        right margin, or after n elements, whichever is less.

  Return Value:
        All functions return the number of elements read, or ERR on 
        error.

  Portability                                X/Open    BSD    SYS V
        inchstr                                 Y       -      4.0
        winchstr                                Y       -      4.0
        mvinchstr                               Y       -      4.0
        mvwinchstr                              Y       -      4.0
        inchnstr                                Y       -      4.0
        winchnstr                               Y       -      4.0
        mvinchnstr                              Y       -      4.0
        mvwinchnstr                             Y       -      4.0
        in_wchstr                               Y
        win_wchstr                              Y
        mvin_wchstr                             Y
        mvwin_wchstr                            Y
        in_wchnstr                              Y
        win_wchnstr                             Y
        mvin_wchnstr                            Y
        mvwin_wchnstr                           Y

**man-end****************************************************************/

//------------------------------------------------------------------------------
int winchnstr( WINDOW* win, chtype* ch, int n )
{
	__QCS_FCONTEXT( "winchnstr" );

    chtype *src;
    int i;

    if( !win || !ch || n < 0 )
	{
        return ERR;
	}

    if( ( win->_curx + n ) > win->_maxx )
	{
        n = win->_maxx - win->_curx;
	}

    src = win->_y[ win->_cury ] + win->_curx;

    for( i = 0; i < n; i++ )
	{
        *ch++ = *src++;
	}

    *ch = (chtype)0;

    return 0;
}

//------------------------------------------------------------------------------
int inchstr( chtype* ch )
{
    __QCS_FCONTEXT( "inchstr" );

    return winchnstr( stdscr, ch, stdscr->_maxx - stdscr->_curx );
}

//------------------------------------------------------------------------------
int winchstr( WINDOW* win, chtype* ch )
{
    __QCS_FCONTEXT( "winchstr" );

    return winchnstr( win, ch, win->_maxx - win->_curx );
}

//------------------------------------------------------------------------------
int mvinchstr( int y, int x, chtype* ch )
{
    __QCS_FCONTEXT( "mvinchstr" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return winchnstr( stdscr, ch, stdscr->_maxx - stdscr->_curx );
}

//------------------------------------------------------------------------------
int mvwinchstr( WINDOW* win, int y, int x, chtype* ch )
{
    __QCS_FCONTEXT( "mvwinchstr" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}

    return winchnstr( win, ch, win->_maxx - win->_curx );
}

//------------------------------------------------------------------------------
int inchnstr( chtype* ch, int n )
{
    __QCS_FCONTEXT( "inchnstr" );

    return winchnstr( stdscr, ch, n );
}

//------------------------------------------------------------------------------
int mvinchnstr( int y, int x, chtype* ch, int n )
{
    __QCS_FCONTEXT( "mvinchnstr" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return winchnstr( stdscr, ch, n );
}

//------------------------------------------------------------------------------
int mvwinchnstr( WINDOW* win, int y, int x, chtype* ch, int n )
{
    __QCS_FCONTEXT( "mvwinchnstr" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}

    return winchnstr( win, ch, n );
}

#if __QOR_UNICODE
//------------------------------------------------------------------------------
int win_wchnstr( WINDOW* win, cchar_t* wch, int n )
{
    __QCS_FCONTEXT( "win_wchnstr" );

    return winchnstr( win, wch, n );
}

//------------------------------------------------------------------------------
int in_wchstr( cchar_t* wch )
{
    __QCS_FCONTEXT( "in_wchstr" );

    return win_wchnstr( stdscr, wch, stdscr->_maxx - stdscr->_curx );
}

//------------------------------------------------------------------------------
int win_wchstr( WINDOW* win, cchar_t* wch )
{
    __QCS_FCONTEXT( "win_wchstr" );

    return win_wchnstr( win, wch, win->_maxx - win->_curx );
}

//------------------------------------------------------------------------------
int mvin_wchstr( int y, int x, cchar_t* wch )
{
    __QCS_FCONTEXT( "mvin_wchstr" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return win_wchnstr( stdscr, wch, stdscr->_maxx - stdscr->_curx );
}

//------------------------------------------------------------------------------
int mvwin_wchstr( WINDOW* win, int y, int x, cchar_t* wch )
{
    __QCS_FCONTEXT( "mvwin_wchstr" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}

    return win_wchnstr( win, wch, win->_maxx - win->_curx );
}

//------------------------------------------------------------------------------
int in_wchnstr( cchar_t* wch, int n )
{
    __QCS_FCONTEXT( "in_wchnstr" );

    return win_wchnstr( stdscr, wch, n );
}

//------------------------------------------------------------------------------
int mvin_wchnstr( int y, int x, cchar_t* wch, int n )
{
    __QCS_FCONTEXT( "mvin_wchnstr" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return win_wchnstr( stdscr, wch, n );
}

//------------------------------------------------------------------------------
int mvwin_wchnstr( WINDOW* win, int y, int x, cchar_t* wch, int n )
{ 
    __QCS_FCONTEXT( "mvwin_wchnstr" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}
    return win_wchnstr( win, wch, n );
}

#endif
