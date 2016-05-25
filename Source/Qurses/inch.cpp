/* Public Domain Curses */

#include "Qurses/curspriv.h"

RCSID("$Id: inch.c,v 1.33 2008/07/13 16:08:18 wmcbrine Exp $")

/*man-start**************************************************************

  Name:                                                         inch

  Synopsis:
        chtype inch(void);
        chtype winch(WINDOW *win);
        chtype mvinch(int y, int x);
        chtype mvwinch(WINDOW *win, int y, int x);

        int in_wch(cchar_t *wcval);
        int win_wch(WINDOW *win, cchar_t *wcval);
        int mvin_wch(int y, int x, cchar_t *wcval);
        int mvwin_wch(WINDOW *win, int y, int x, cchar_t *wcval);

  Description:
        The inch() functions retrieve the character and attribute from 
        the current or specified window position, in the form of a 
        chtype. If a NULL window is specified, (chtype)ERR is returned.

        The in_wch() functions are the wide-character versions; instead 
        of returning a chtype, they store a cchar_t at the address 
        specified by wcval, and return OK or ERR. (No value is stored 
        when ERR is returned.) Note that in PDCurses, chtype and cchar_t 
        are the same.

  Portability                                X/Open    BSD    SYS V
        inch                                    Y       Y       Y
        winch                                   Y       Y       Y
        mvinch                                  Y       Y       Y
        mvwinch                                 Y       Y       Y
        in_wch                                  Y
        win_wch                                 Y
        mvin_wch                                Y
        mvwin_wch                               Y

**man-end****************************************************************/

//------------------------------------------------------------------------------
chtype winch( WINDOW* win )
{
    __QCS_FCONTEXT( "winch" );

    if( !win )
	{
        return (chtype)ERR;
	}

    return win->_y[ win->_cury ][ win->_curx ];
}

//------------------------------------------------------------------------------
chtype inch( void )
{
    __QCS_FCONTEXT( "inch" );

    return winch( stdscr );
}

//------------------------------------------------------------------------------
chtype mvinch( int y, int x )
{
    __QCS_FCONTEXT( "mvinch" );

    if( move( y, x ) == ERR )
	{
        return (chtype)ERR;
	}

    return stdscr->_y[ stdscr->_cury ][ stdscr->_curx ];
}

//------------------------------------------------------------------------------
chtype mvwinch( WINDOW* win, int y, int x )
{
    __QCS_FCONTEXT( "mvwinch" );

    if( wmove( win, y, x ) == ERR )
	{
        return (chtype)ERR;
	}

    return win->_y[ win->_cury ][ win->_curx ];
}

#if __QOR_UNICODE
//------------------------------------------------------------------------------
int win_wch( WINDOW* win, cchar_t* wcval )
{
    __QCS_FCONTEXT( "win_wch" );

    if( !win || !wcval )
	{
        return ERR;
	}

    *wcval = win->_y[ win->_cury ][ win->_curx ];

    return 0;
}

//------------------------------------------------------------------------------
int in_wch( cchar_t* wcval )
{
    __QCS_FCONTEXT( "in_wch" );

    return win_wch( stdscr, wcval );
}

//------------------------------------------------------------------------------
int mvin_wch( int y, int x, cchar_t* wcval )
{
    __QCS_FCONTEXT( "mvin_wch" );

    if( !wcval || ( move( y, x ) == ERR ) )
	{
        return ERR;
	}

    *wcval = stdscr->_y[ stdscr->_cury ][ stdscr->_curx ];

    return 0;
}

//------------------------------------------------------------------------------
int mvwin_wch( WINDOW* win, int y, int x, cchar_t* wcval )
{
    __QCS_FCONTEXT( "mvwin_wch" );

    if( !wcval || ( wmove( win, y, x ) == ERR ) )
	{
        return ERR;
	}

    *wcval = win->_y[ win->_cury ][ win->_curx ];

    return 0;
}

#endif
