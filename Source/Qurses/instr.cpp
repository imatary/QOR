/* Public Domain Curses */

#include "Qurses/curspriv.h"

RCSID("$Id: instr.c,v 1.44 2008/07/13 16:08:18 wmcbrine Exp $")

/*man-start**************************************************************

  Name:                                                         instr

  Synopsis:
        int instr(char *str);
        int innstr(char *str, int n);
        int winstr(WINDOW *win, char *str);
        int winnstr(WINDOW *win, char *str, int n);
        int mvinstr(int y, int x, char *str);
        int mvinnstr(int y, int x, char *str, int n);
        int mvwinstr(WINDOW *win, int y, int x, char *str);
        int mvwinnstr(WINDOW *win, int y, int x, char *str, int n);

        int inwstr(wchar_t *wstr);
        int innwstr(wchar_t *wstr, int n);
        int winwstr(WINDOW *win, wchar_t *wstr);
        int winnwstr(WINDOW *win, wchar_t *wstr, int n);
        int mvinwstr(int y, int x, wchar_t *wstr);
        int mvinnwstr(int y, int x, wchar_t *wstr, int n);
        int mvwinwstr(WINDOW *win, int y, int x, wchar_t *wstr);
        int mvwinnwstr(WINDOW *win, int y, int x, wchar_t *wstr, int n);

  Description:
        These functions take characters (or wide characters) from the 
        current or specified position in the window, and return them as 
        a string in str (or wstr). Attributes are ignored. The functions 
        with n as the last argument return a string at most n characters 
        long.

  Return Value:
        Upon successful completion, innstr(), mvinnstr(), mvwinnstr() 
        and winnstr() return the number of characters actually read into
        the string; instr(), mvinstr(), mvwinstr() and winstr() return 
        OK. Otherwise, all these functions return ERR.

  Portability                                X/Open    BSD    SYS V
        instr                                   Y       -      4.0
        winstr                                  Y       -      4.0
        mvinstr                                 Y       -      4.0
        mvwinstr                                Y       -      4.0
        innstr                                  Y       -      4.0
        winnstr                                 Y       -      4.0
        mvinnstr                                Y       -      4.0
        mvwinnstr                               Y       -      4.0
        inwstr                                  Y
        winwstr                                 Y
        mvinwstr                                Y
        mvwinwstr                               Y
        innwstr                                 Y
        winnwstr                                Y
        mvinnwstr                               Y
        mvwinnwstr                              Y

**man-end****************************************************************/

//------------------------------------------------------------------------------
int winnstr( WINDOW* win, char* str, int n )
{
	__QCS_FCONTEXT( "winnstr" );

#if __QOR_UNICODE
    wchar_t wstr[ 513 ];

    if( n < 0 || n > 512 )
	{
        n = 512;
	}

    if( winnwstr( win, wstr, n ) == ERR )
	{
        return ERR;
	}

    return PDC_wcstombs( str, wstr, n );
#else
    chtype* src;
    int i;

    if( !win || !str )
	{
        return ERR;
	}

    if( n < 0 || ( win->_curx + n ) > win->_maxx )
	{
        n = win->_maxx - win->_curx;
	}

    src = win->_y[ win->_cury ] + win->_curx;

    for( i = 0; i < n; i++ )
	{
        str[ i ] = src[ i ] & A_CHARTEXT;
	}

    str[ i ] = '\0';

    return i;
#endif
}

//------------------------------------------------------------------------------
int instr( char* str )
{
    __QCS_FCONTEXT( "instr" );

    return ( ERR == winnstr( stdscr, str, stdscr->_maxx ) ) ? ERR : 0;
}

//------------------------------------------------------------------------------
int winstr( WINDOW* win, char* str )
{
    __QCS_FCONTEXT( "winstr" );

    return ( ERR == winnstr( win, str, win->_maxx ) ) ? ERR : 0;
}

//------------------------------------------------------------------------------
int mvinstr( int y, int x, char* str )
{
    __QCS_FCONTEXT( "mvinstr" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return ( ERR == winnstr( stdscr, str, stdscr->_maxx ) ) ? ERR : 0;
}

//------------------------------------------------------------------------------
int mvwinstr( WINDOW* win, int y, int x, char* str )
{
    __QCS_FCONTEXT( "mvwinstr" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}

    return ( ERR == winnstr( win, str, win->_maxx ) ) ? ERR : 0;
}

//------------------------------------------------------------------------------
int innstr( char* str, int n )
{
    __QCS_FCONTEXT( "innstr" );

    return winnstr( stdscr, str, n );
}

//------------------------------------------------------------------------------
int mvinnstr( int y, int x, char* str, int n )
{
    __QCS_FCONTEXT( "mvinnnstr" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return winnstr( stdscr, str, n );
}

//------------------------------------------------------------------------------
int mvwinnstr( WINDOW* win, int y, int x, char *str, int n )
{
    __QCS_FCONTEXT( "mvwinnstr" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}

    return winnstr( win, str, n );
}

#if __QOR_UNICODE

//------------------------------------------------------------------------------
int winnwstr( WINDOW* win, wchar_t* wstr, int n )
{
	__QCS_FCONTEXT( "winnwstr" );

    chtype* src;
    int i;

    if( !win || !wstr )
	{
        return ERR;
	}

    if( n < 0 || ( win->_curx + n ) > win->_maxx )
	{
        n = win->_maxx - win->_curx;
	}

    src = win->_y[ win->_cury ] + win->_curx;

    for( i = 0; i < n; i++ )
	{
        wstr[ i ] = src[ i ] & A_CHARTEXT;
	}

    wstr[ i ] = L'\0';

    return i;
}

//------------------------------------------------------------------------------
int inwstr( wchar_t* wstr )
{
    __QCS_FCONTEXT( "inwstr" );

    return ( ERR == winnwstr( stdscr, wstr, stdscr->_maxx ) ) ? ERR : 0;
}

//------------------------------------------------------------------------------
int winwstr( WINDOW* win, wchar_t* wstr )
{
    __QCS_FCONTEXT( "winwstr" );

    return ( ERR == winnwstr( win, wstr, win->_maxx ) ) ? ERR : 0;
}

//------------------------------------------------------------------------------
int mvinwstr( int y, int x, wchar_t* wstr )
{
    __QCS_FCONTEXT( "mvinwstr" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return ( ERR == winnwstr( stdscr, wstr, stdscr->_maxx ) ) ? ERR : 0;
}

//------------------------------------------------------------------------------
int mvwinwstr( WINDOW* win, int y, int x, wchar_t* wstr )
{
    __QCS_FCONTEXT( "mvwinwstr" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}

    return ( ERR == winnwstr( win, wstr, win->_maxx ) ) ? ERR : 0;
}

//------------------------------------------------------------------------------
int innwstr( wchar_t* wstr, int n )
{
    __QCS_FCONTEXT( "innwstr" );

    return winnwstr( stdscr, wstr, n );
}

//------------------------------------------------------------------------------
int mvinnwstr( int y, int x, wchar_t* wstr, int n )
{
    __QCS_FCONTEXT( "mvinnwstr" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return winnwstr( stdscr, wstr, n );
}

//------------------------------------------------------------------------------
int mvwinnwstr( WINDOW* win, int y, int x, wchar_t* wstr, int n )
{
    __QCS_FCONTEXT( "mvwinnwstr" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}
    return winnwstr( win, wstr, n );
}

#endif
