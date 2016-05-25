/* Public Domain Curses */

#include "Qurses/curspriv.h"

RCSID("$Id: addstr.c,v 1.44 2008/07/13 16:08:17 wmcbrine Exp $")

/*man-start**************************************************************

  Name:                                                         addstr

  Synopsis:
        int addstr(const char *str);
        int addnstr(const char *str, int n);
        int waddstr(WINDOW *win, const char *str);
        int waddnstr(WINDOW *win, const char *str, int n);
        int mvaddstr(int y, int x, const char *str);
        int mvaddnstr(int y, int x, const char *str, int n);
        int mvwaddstr(WINDOW *win, int y, int x, const char *str);
        int mvwaddnstr(WINDOW *win, int y, int x, const char *str, int n);

        int addwstr(const wchar_t *wstr);
        int addnwstr(const wchar_t *wstr, int n);
        int waddwstr(WINDOW *win, const wchar_t *wstr);
        int waddnwstr(WINDOW *win, const wchar_t *wstr, int n);
        int mvaddwstr(int y, int x, const wchar_t *wstr);
        int mvaddnwstr(int y, int x, const wchar_t *wstr, int n);
        int mvwaddwstr(WINDOW *win, int y, int x, const wchar_t *wstr);
        int mvwaddnwstr(WINDOW *win, int y, int x, const wchar_t *wstr, int n);

  Description:
        These routines write all the characters of the null-terminated
        string str or wide-character string wstr to the given window.
        The functionality is similar to calling waddch() once for each
        character in the string; except that, when PDCurses is built
        with wide-character support enabled, the narrow-character
        functions treat the string as a multibyte string in the current
        locale, and convert it. The routines with n as the last
        argument write at most n characters; if n is negative, then the
        entire string will be added.

  Return Value:
        All functions return OK or ERR.

  Portability                                X/Open    BSD    SYS V
        addstr                                  Y       Y       Y
        waddstr                                 Y       Y       Y
        mvaddstr                                Y       Y       Y
        mvwaddstr                               Y       Y       Y
        addnstr                                 Y       -      4.0
        waddnstr                                Y       -      4.0
        mvaddnstr                               Y       -      4.0
        mvwaddnstr                              Y       -      4.0
        addwstr                                 Y
        waddwstr                                Y
        mvaddwstr                               Y
        mvwaddwstr                              Y
        addnwstr                                Y
        waddnwstr                               Y
        mvaddnwstr                              Y
        mvwaddnwstr                             Y

**man-end****************************************************************/

//------------------------------------------------------------------------------
int waddnstr( WINDOW* win, const char* str, int n )
{
	__QCS_FCONTEXT( "waddnstr" );

    int i = 0;

    if( !win || !str )
	{
        return ERR;
	}

    while( str[ i ] && ( i < n || n < 0 ) )
    {
#if __QOR_UNICODE
        wchar_t wch;
        int retval = PDC_mbtowc( &wch, str + i, n >= 0 ? n - i : 6 );

        if( retval <= 0 )
		{
            return 0;
		}

        i += retval;
#else
        chtype wch = (unsigned char)( str[ i++ ] );
#endif
        if( waddch( win, wch ) == ERR )
		{
            return ERR;
		}
    }

    return 0;
}

//------------------------------------------------------------------------------
int addstr( const char* str )
{
    __QCS_FCONTEXT( "addstr" );

    return waddnstr( stdscr, str, -1 );
}

//------------------------------------------------------------------------------
int addnstr( const char* str, int n )
{
    __QCS_FCONTEXT( "addnstr" );

    return waddnstr( stdscr, str, n );
}

//------------------------------------------------------------------------------
int waddstr( WINDOW* win, const char* str )
{
    __QCS_FCONTEXT( "waddstr" );

    return waddnstr( win, str, -1 );
}

//------------------------------------------------------------------------------
int mvaddstr( int y, int x, const char* str )
{
    __QCS_FCONTEXT( "mvaddstr" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return waddnstr( stdscr, str, -1 );
}

//------------------------------------------------------------------------------
int mvaddnstr( int y, int x, const char* str, int n )
{
    __QCS_FCONTEXT( "mvaddnstr" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return waddnstr( stdscr, str, n );
}

//------------------------------------------------------------------------------
int mvwaddstr( WINDOW* win, int y, int x, const char* str )
{
    __QCS_FCONTEXT( "mvwaddstr" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}

    return waddnstr( win, str, -1 );
}

//------------------------------------------------------------------------------
int mvwaddnstr( WINDOW* win, int y, int x, const char* str, int n )
{
	__QCS_FCONTEXT( "mvwaddnstr" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}

    return waddnstr( win, str, n );
}

#if __QOR_UNICODE
//------------------------------------------------------------------------------
int waddnwstr( WINDOW* win, const wchar_t* wstr, int n )
{
	__QCS_FCONTEXT( "waddnwstr" );

    int i = 0;

    if( !win || !wstr )
	{
        return ERR;
	}

    while( wstr[ i ] && ( i < n || n < 0 ) )
    {
        chtype wch = wstr[ i++ ];

        if( waddch( win, wch ) == ERR )
		{
            return ERR;
		}
    }

    return 0;
}

//------------------------------------------------------------------------------
int addwstr( const wchar_t* wstr )
{
    __QCS_FCONTEXT( "addwstr" );

    return waddnwstr( stdscr, wstr, -1 );
}

//------------------------------------------------------------------------------
int addnwstr( const wchar_t* wstr, int n )
{
    __QCS_FCONTEXT( "addnwstr" );

    return waddnwstr( stdscr, wstr, n );
}

//------------------------------------------------------------------------------
int waddwstr( WINDOW* win, const wchar_t* wstr )
{
    __QCS_FCONTEXT( "waddwstr" );

    return waddnwstr( win, wstr, -1 );
}

//------------------------------------------------------------------------------
int mvaddwstr( int y, int x, const wchar_t* wstr )
{
    __QCS_FCONTEXT( "mvaddwstr" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return waddnwstr( stdscr, wstr, -1 );
}

//------------------------------------------------------------------------------
int mvaddnwstr( int y, int x, const wchar_t* wstr, int n )
{
    __QCS_FCONTEXT( "mvaddnwstr" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}
    return waddnwstr( stdscr, wstr, n );
}

//------------------------------------------------------------------------------
int mvwaddwstr( WINDOW* win, int y, int x, const wchar_t* wstr )
{
    __QCS_FCONTEXT( "mvwaddwstr" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}
    return waddnwstr( win, wstr, -1 );
}

//------------------------------------------------------------------------------
int mvwaddnwstr( WINDOW* win, int y, int x, const wchar_t* wstr, int n )
{
	__QCS_FCONTEXT( "mvwaddnwstr" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}
    return waddnwstr( win, wstr, n );
}

#endif
