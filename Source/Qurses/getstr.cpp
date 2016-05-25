/* Public Domain Curses */

#include "Qurses/curspriv.h"

RCSID("$Id: getstr.c,v 1.51 2008/07/14 04:24:51 wmcbrine Exp $")

/*man-start**************************************************************

  Name:                                                         getstr

  Synopsis:
        int getstr(char *str);
        int wgetstr(WINDOW *win, char *str);
        int mvgetstr(int y, int x, char *str);
        int mvwgetstr(WINDOW *win, int y, int x, char *str);
        int getnstr(char *str, int n);
        int wgetnstr(WINDOW *win, char *str, int n);
        int mvgetnstr(int y, int x, char *str, int n);
        int mvwgetnstr(WINDOW *win, int y, int x, char *str, int n);

        int get_wstr(wint_t *wstr);
        int wget_wstr(WINDOW *win, wint_t *wstr);
        int mvget_wstr(int y, int x, wint_t *wstr);
        int mvwget_wstr(WINDOW *win, int, int, wint_t *wstr);
        int getn_wstr(wint_t *wstr, int n);
        int wgetn_wstr(WINDOW *win, wint_t *wstr, int n);
        int mvgetn_wstr(int y, int x, wint_t *wstr, int n);
        int mvwgetn_wstr(WINDOW *win, int y, int x, wint_t *wstr, int n);

  Description:
        These routines call wgetch() repeatedly to build a string, 
        interpreting erase and kill characters along the way, until a 
        newline or carriage return is received. When PDCurses is built 
        with wide-character support enabled, the narrow-character 
        functions convert the wgetch()'d values into a multibyte string 
        in the current locale before returning it. The resulting string 
        is placed in the area pointed to by *str. The routines with n as 
        the last argument read at most n characters.

        Note that there's no way to know how long the buffer passed to 
        wgetstr() is, so use wgetnstr() to avoid buffer overflows.

  Return Value:
        This functions return ERR on failure or any other value on 
        success.

  Portability                                X/Open    BSD    SYS V
        getstr                                  Y       Y       Y
        wgetstr                                 Y       Y       Y
        mvgetstr                                Y       Y       Y
        mvwgetstr                               Y       Y       Y
        getnstr                                 Y       -      4.0
        wgetnstr                                Y       -      4.0
        mvgetnstr                               Y       -       -
        mvwgetnstr                              Y       -       -
        get_wstr                                Y
        wget_wstr                               Y
        mvget_wstr                              Y
        mvwget_wstr                             Y
        getn_wstr                               Y
        wgetn_wstr                              Y
        mvgetn_wstr                             Y
        mvwgetn_wstr                            Y

**man-end****************************************************************/

#define MAXLINE 255

//------------------------------------------------------------------------------
int wgetnstr( WINDOW* win, char* str, int n )
{
	__QCS_FCONTEXT( "wgetnstr" );

#if __QOR_UNICODE
    wchar_t wstr[ MAXLINE + 1 ];

    if( n < 0 || n > MAXLINE )
	{
        n = MAXLINE;
	}

    if( wgetn_wstr( win, (wint_t *)wstr, n ) == ERR )
	{
        return ERR;
	}

    return PDC_wcstombs( str, wstr, n );
#else
    int ch, i, num, x, chars;
    char *p;
    bool stop, oldecho, oldcbreak, oldnodelay;

    if( !win || !str )
	{
        return ERR;
	}

    chars = 0;
    p = str;
    stop = FALSE;

    x = win->_curx;

    oldcbreak = SP->cbreak;		// remember states
    oldecho = SP->echo;
    oldnodelay = win->_nodelay;

    SP->echo = FALSE;			// we do echo ourselves
    cbreak();					// ensure each key is returned immediately
    win->_nodelay = FALSE;		// don't return -1

    wrefresh( win );

    while( !stop )
    {
        ch = wgetch( win );

        switch( ch )
        {

        case '\t':
            ch = ' ';
            num = TABSIZE - (win->_curx - x) % TABSIZE;
            for( i = 0; i < num; i++ )
            {
                if( chars < n )
                {
                    if( oldecho ) 
					{
                        waddch( win, ch );
					}
                    *p++ = ch;
                    ++chars;
                }
                else
				{
                    beep();
				}
            }
            break;

        case _ECHAR:        // CTRL-H -- Delete character
            if( p > str )
            {
                if( oldecho ) 
				{
                    waddstr( win, "\b \b" );
				}
                ch = (unsigned char)(*--p);
                if( ( ch < ' ' ) && ( oldecho ) )
				{
                    waddstr( win, "\b \b" );
				}
                chars--;
            }
            break;

        case _DLCHAR:       // CTRL-U -- Delete line
            while( p > str )
            {
                if( oldecho ) 
				{
                    waddstr( win, "\b \b" );
				}
                ch = (unsigned char)(*--p);
                if( ( ch < ' ' ) && ( oldecho ) )
				{
                    waddstr( win, "\b \b" );
				}
            }
            chars = 0;
            break;

        case _DWCHAR:       // CTRL-W -- Delete word

            while( ( p > str ) && ( *( p - 1 ) == ' ' ) )
            {
                if( oldecho ) 
				{
                    waddstr( win, "\b \b" );
				}

                --p;        // remove space 
                chars--;
            }

            while( ( p > str ) && ( *( p - 1 ) != ' ' ) )
            {
                if( oldecho ) 
				{
                    waddstr( win, "\b \b" );
				}

                ch = (unsigned char)(*--p);
                if( ( ch < ' ' ) && ( oldecho ) )
				{
                    waddstr( win, "\b \b" );
				}
                chars--;
            }
            break;

        case '\n':
        case '\r':
            stop = TRUE;
            if( oldecho )
			{
                waddch( win, '\n' );
			}
            break;

        default:
            if( chars < n )
            {
                if( !SP->key_code && ch < 0x100 )
                {
                    *p++ = ch;
                    if( oldecho ) 
					{
                        waddch( win, ch );
					}
                    chars++;
                }
            }
            else
			{
                beep();
			}

            break;      
        }

        wrefresh( win );
    }

    *p = '\0';

    SP->echo = oldecho;     /* restore old settings */
    SP->cbreak = oldcbreak;
    win->_nodelay = oldnodelay;

    return 0;
#endif
}

//------------------------------------------------------------------------------
int getstr( char* str )
{
    __QCS_FCONTEXT( "getstr" );

    return wgetnstr( stdscr, str, MAXLINE );
}

//------------------------------------------------------------------------------
int wgetstr( WINDOW* win, char* str )
{
    __QCS_FCONTEXT( "wgetstr" );

    return wgetnstr( win, str, MAXLINE );
}

//------------------------------------------------------------------------------
int mvgetstr( int y, int x, char* str )
{
    __QCS_FCONTEXT( "mvgetstr" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return wgetnstr( stdscr, str, MAXLINE );
}

//------------------------------------------------------------------------------
int mvwgetstr( WINDOW* win, int y, int x, char* str )
{
    __QCS_FCONTEXT( "mvwgetstr" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}

    return wgetnstr( win, str, MAXLINE );
}

//------------------------------------------------------------------------------
int getnstr( char* str, int n )
{
    __QCS_FCONTEXT( "getnstr" );

    return wgetnstr( stdscr, str, n );
}

//------------------------------------------------------------------------------
int mvgetnstr( int y, int x, char* str, int n )
{
    __QCS_FCONTEXT( "mvgetnstr" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return wgetnstr( stdscr, str, n );
}

//------------------------------------------------------------------------------
int mvwgetnstr( WINDOW* win, int y, int x, char* str, int n )
{
    __QCS_FCONTEXT( "mvwgetnstr" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}

    return wgetnstr( win, str, n );
}

#if __QOR_UNICODE
//------------------------------------------------------------------------------
int wgetn_wstr( WINDOW* win, wint_t* wstr, int n )
{
	__QCS_FCONTEXT( "wgetn_wstr" );

    int ch, i, num, x, chars;
    wint_t *p;
    bool stop, oldecho, oldcbreak, oldnodelay;

    if( !win || !wstr )
	{
        return ERR;
	}

    chars = 0;
    p = wstr;
    stop = FALSE;

    x = win->_curx;

    oldcbreak = SP->cbreak; /* remember states */
    oldecho = SP->echo;
    oldnodelay = win->_nodelay;

    SP->echo = FALSE;       /* we do echo ourselves */
    cbreak();               /* ensure each key is returned immediately */
    win->_nodelay = FALSE;  /* don't return -1 */

    wrefresh( win );

    while( !stop )
    {
        ch = wgetch( win );

        switch( ch )
        {

        case '\t':
            ch = ' ';
            num = TABSIZE - (win->_curx - x) % TABSIZE;
            for( i = 0; i < num; i++ )
            {
                if( chars < n )
                {
                    if( oldecho ) 
					{
                        waddch( win, ch );
					}
                    *p++ = ch;
                    ++chars;
                }
                else
				{
                    beep();
				}
            }
            break;

        case _ECHAR:        // CTRL-H -- Delete character
            if( p > wstr )
            {
                if( oldecho ) 
				{
                    waddstr( win, "\b \b" );
				}
                ch = *--p;
                if( ( ch < ' ' ) && ( oldecho ) )
				{
                    waddstr( win, "\b \b" );
				}
                chars--;
            }
            break;

        case _DLCHAR:       /* CTRL-U -- Delete line */
            while( p > wstr )
            {
                if( oldecho ) 
				{
                    waddstr( win, "\b \b" );
				}
                ch = *--p;
                if( ( ch < ' ') && ( oldecho ) )
				{
                    waddstr( win, "\b \b" );
				}
            }
            chars = 0;
            break;

        case _DWCHAR:       // CTRL-W -- Delete word

            while( ( p > wstr) && ( *( p - 1 ) == ' ' ) )
            {
                if( oldecho ) 
				{
                    waddstr(win, "\b \b");
				}
                --p;        // remove space
                chars--;
            }

            while( ( p > wstr) && ( *( p - 1 ) != ' ' ) )
            {
                if( oldecho ) 
				{
                    waddstr( win, "\b \b" );
				}

                ch = *--p;
                if( ( ch < ' ' ) && ( oldecho ) )
				{
                    waddstr( win, "\b \b" );
				}
                chars--;
            }
            break;

        case '\n':
        case '\r':
            stop = TRUE;
            if( oldecho ) 
			{
                waddch( win, '\n' );
			}
            break;

        default:
            if( chars < n )
            {
                if( !SP->key_code )
                {
                    *p++ = ch;
                    if( oldecho )
					{
                        waddch( win, ch );
					}
                    chars++;
                }
            }
            else
			{
                beep();
			}

            break;
      
        }

        wrefresh( win );
    }

    *p = '\0';

    SP->echo = oldecho;     // restore old settings
    SP->cbreak = oldcbreak;
    win->_nodelay = oldnodelay;

    return 0;
}

//------------------------------------------------------------------------------
int get_wstr( wint_t* wstr )
{
    __QCS_FCONTEXT( "get_wstr" );

    return wgetn_wstr( stdscr, wstr, MAXLINE );
}

//------------------------------------------------------------------------------
int wget_wstr( WINDOW* win, wint_t* wstr )
{
    __QCS_FCONTEXT( "wget_wstr" );

    return wgetn_wstr( win, wstr, MAXLINE );
}

//------------------------------------------------------------------------------
int mvget_wstr( int y, int x, wint_t* wstr )
{
    __QCS_FCONTEXT( "mvget_wstr" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return wgetn_wstr( stdscr, wstr, MAXLINE );
}

//------------------------------------------------------------------------------
int mvwget_wstr( WINDOW* win, int y, int x, wint_t* wstr )
{
    __QCS_FCONTEXT( "mvwget_wstr" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}

    return wgetn_wstr( win, wstr, MAXLINE );
}

//------------------------------------------------------------------------------
int getn_wstr( wint_t* wstr, int n )
{
    __QCS_FCONTEXT( "getn_wstr" );

    return wgetn_wstr( stdscr, wstr, n );
}

//------------------------------------------------------------------------------
int mvgetn_wstr( int y, int x, wint_t* wstr, int n )
{
    __QCS_FCONTEXT( "mvgetn_wstr" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return wgetn_wstr( stdscr, wstr, n );
}

//------------------------------------------------------------------------------
int mvwgetn_wstr( WINDOW* win, int y, int x, wint_t* wstr, int n )
{
    __QCS_FCONTEXT( "mvwgetn_wstr" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}

    return wgetn_wstr( win, wstr, n );
}

#endif
