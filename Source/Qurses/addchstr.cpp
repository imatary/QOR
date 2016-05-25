/* Public Domain Curses */

#include "Qurses/curspriv.h"

RCSID("$Id: addchstr.c,v 1.43 2008/07/13 16:08:17 wmcbrine Exp $")

/*man-start**************************************************************

  Name:                                                         addchstr

  Synopsis:
        int addchstr(const chtype *ch);
        int addchnstr(const chtype *ch, int n);
        int waddchstr(WINDOW *win, const chtype *ch);
        int waddchnstr(WINDOW *win, const chtype *ch, int n);
        int mvaddchstr(int y, int x, const chtype *ch);
        int mvaddchnstr(int y, int x, const chtype *ch, int n);
        int mvwaddchstr(WINDOW *, int y, int x, const chtype *ch);
        int mvwaddchnstr(WINDOW *, int y, int x, const chtype *ch, int n);

        int add_wchstr(const cchar_t *wch);
        int add_wchnstr(const cchar_t *wch, int n);
        int wadd_wchstr(WINDOW *win, const cchar_t *wch);
        int wadd_wchnstr(WINDOW *win, const cchar_t *wch, int n);
        int mvadd_wchstr(int y, int x, const cchar_t *wch);
        int mvadd_wchnstr(int y, int x, const cchar_t *wch, int n);
        int mvwadd_wchstr(WINDOW *win, int y, int x, const cchar_t *wch);
        int mvwadd_wchnstr(WINDOW *win, int y, int x, const cchar_t *wch,
                int n);

  Description:
        These routines write a chtype or cchar_t string directly into 
        the window structure, starting at the current or specified 
        position. The four routines with n as the last argument copy at 
        most n elements, but no more than will fit on the line. If n = 
        -1 then the whole string is copied, up to the maximum number 
        that will fit on the line.

        The cursor position is not advanced. These routines do not check 
        for newline or other special characters, nor does any line 
        wrapping occur.

  Return Value:
        All functions return OK or ERR.

  Portability                                X/Open    BSD    SYS V
        addchstr                                Y       -      4.0
        waddchstr                               Y       -      4.0
        mvaddchstr                              Y       -      4.0
        mvwaddchstr                             Y       -      4.0
        addchnstr                               Y       -      4.0
        waddchnstr                              Y       -      4.0
        mvaddchnstr                             Y       -      4.0
        mvwaddchnstr                            Y       -      4.0
        add_wchstr                              Y
        wadd_wchstr                             Y
        mvadd_wchstr                            Y
        mvwadd_wchstr                           Y
        add_wchnstr                             Y
        wadd_wchnstr                            Y
        mvadd_wchnstr                           Y
        mvwadd_wchnstr                          Y

**man-end****************************************************************/

#include <string.h>

//------------------------------------------------------------------------------
int waddchnstr( WINDOW* win, const chtype* ch, int n )
{
	__QCS_FCONTEXT( "waddchnstr" );

    int y, x, maxx, minx;
    chtype* ptr;

    if( !win || !ch || !n || n < -1 )
	{
        return ERR;
	}

    x = win->_curx;
    y = win->_cury;
    ptr = &( win->_y[ y ][ x ] );

    if( n == -1 || n > win->_maxx - x )
	{
        n = win->_maxx - x;
	}

    minx = win->_firstch[ y ];
    maxx = win->_lastch[ y ];

    for( ; n && *ch; n--, x++, ptr++, ch++ )
    {
        if( *ptr != *ch )
        {
            if( x < minx || minx == _NO_CHANGE )
			{
                minx = x;
			}

            if( x > maxx )
			{
                maxx = x;
			}

            PDC_LOG(("y %d x %d minx %d maxx %d *ptr %x *ch"
                     " %x firstch: %d lastch: %d\n",
                     y, x, minx, maxx, *ptr, *ch, 
                     win->_firstch[y], win->_lastch[y]));

            *ptr = *ch;
        }
    }

    win->_firstch[ y ] = minx;
    win->_lastch[ y ] = maxx;

    return 0;
}

//------------------------------------------------------------------------------
int addchstr( const chtype* ch )
{
    __QCS_FCONTEXT( "addchstr" );

    return waddchnstr( stdscr, ch, -1 );
}

//------------------------------------------------------------------------------
int addchnstr( const chtype* ch, int n )
{
    __QCS_FCONTEXT( "addchnstr" );

    return waddchnstr( stdscr, ch, n );
}

//------------------------------------------------------------------------------
int waddchstr( WINDOW* win, const chtype* ch )
{
    __QCS_FCONTEXT( "waddchstr" );

    return waddchnstr( win, ch, -1 );
}

//------------------------------------------------------------------------------
int mvaddchstr( int y, int x, const chtype* ch )
{
    __QCS_FCONTEXT( "mvaddchstr" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return waddchnstr( stdscr, ch, -1 );
}

//------------------------------------------------------------------------------
int mvaddchnstr( int y, int x, const chtype* ch, int n )
{
    __QCS_FCONTEXT( "mvaddchnstr" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return waddchnstr( stdscr, ch, n );
}

//------------------------------------------------------------------------------
int mvwaddchstr( WINDOW* win, int y, int x, const chtype* ch )
{
    __QCS_FCONTEXT( "mvwaddchstr" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}

    return waddchnstr( win, ch, -1 );
}

//------------------------------------------------------------------------------
int mvwaddchnstr( WINDOW* win, int y, int x, const chtype* ch, int n )
{
    __QCS_FCONTEXT( "mvwaddchnstr" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}

    return waddchnstr( win, ch, n );
}

#if __QOR_UNICODE
//------------------------------------------------------------------------------
int wadd_wchnstr( WINDOW* win, const cchar_t* wch, int n )
{
    __QCS_FCONTEXT( "wadd_wchnstr" );

    return waddchnstr( win, wch, n );
}

//------------------------------------------------------------------------------
int add_wchstr( const cchar_t* wch )
{
    __QCS_FCONTEXT( "add_wchstr" );

    return wadd_wchnstr( stdscr, wch, -1 );
}

//------------------------------------------------------------------------------
int add_wchnstr( const cchar_t* wch, int n )
{
    __QCS_FCONTEXT( "add_wchnstr" );

    return wadd_wchnstr( stdscr, wch, n );
}

//------------------------------------------------------------------------------
int wadd_wchstr( WINDOW* win, const cchar_t* wch )
{
    __QCS_FCONTEXT( "wadd_wchstr" );

    return wadd_wchnstr( win, wch, -1 );
}

//------------------------------------------------------------------------------
int mvadd_wchstr( int y, int x, const cchar_t* wch )
{
    __QCS_FCONTEXT( "mvadd_wchstr" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return wadd_wchnstr( stdscr, wch, -1 );
}

//------------------------------------------------------------------------------
int mvadd_wchnstr( int y, int x, const cchar_t* wch, int n )
{
    __QCS_FCONTEXT( "mvadd_wchnstr" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return wadd_wchnstr( stdscr, wch, n );
}

//------------------------------------------------------------------------------
int mvwadd_wchstr( WINDOW* win, int y, int x, const cchar_t* wch )
{
    __QCS_FCONTEXT( "mvwadd_wchstr" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}

    return wadd_wchnstr( win, wch, -1 );
}

//------------------------------------------------------------------------------
int mvwadd_wchnstr( WINDOW* win, int y, int x, const cchar_t* wch, int n )
{
    __QCS_FCONTEXT( "mvwadd_wchnstr" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}

    return wadd_wchnstr( win, wch, n );
}

#endif
