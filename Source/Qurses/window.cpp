/* Public Domain Curses */

#include "Qurses/curspriv.h"

RCSID("$Id: window.c,v 1.62 2008/07/13 16:08:18 wmcbrine Exp $")

/*man-start**************************************************************

  Name:                                                         window

  Synopsis:
        WINDOW *newwin(int nlines, int ncols, int begy, int begx);
        WINDOW *derwin(WINDOW* orig, int nlines, int ncols,
                int begy, int begx);
        WINDOW *subwin(WINDOW* orig, int nlines, int ncols,
                int begy, int begx);
        WINDOW *dupwin(WINDOW *win);
        int delwin(WINDOW *win);
        int mvwin(WINDOW *win, int y, int x);
        int mvderwin(WINDOW *win, int pary, int parx);
        int syncok(WINDOW *win, bool bf);
        void wsyncup(WINDOW *win);
        void wcursyncup(WINDOW *win);
        void wsyncdown(WINDOW *win);

        WINDOW *resize_window(WINDOW *win, int nlines, int ncols);
        int wresize(WINDOW *win, int nlines, int ncols);
        WINDOW *PDC_makelines(WINDOW *win);
        WINDOW *PDC_makenew(int nlines, int ncols, int begy, int begx);
        void PDC_sync(WINDOW *win);

  Description:
        newwin() creates a new window with the given number of lines,
        nlines and columns, ncols. The upper left corner of the window
        is at line begy, column begx. If nlines is zero, it defaults to
        LINES - begy; ncols to COLS - begx. Create a new full-screen
        window by calling newwin(0, 0, 0, 0).

        delwin() deletes the named window, freeing all associated 
        memory. In the case of overlapping windows, subwindows should be 
        deleted before the main window.

        mvwin() moves the window so that the upper left-hand corner is
        at position (y,x). If the move would cause the window to be off
        the screen, it is an error and the window is not moved. Moving
        subwindows is allowed.

        subwin() creates a new subwindow within a window.  The
        dimensions of the subwindow are nlines lines and ncols columns.
        The subwindow is at position (begy, begx) on the screen.  This
        position is relative to the screen, and not to the window orig.
        Changes made to either window will affect both.  When using this
        routine, you will often need to call touchwin() before calling
        wrefresh().

        derwin() is the same as subwin(), except that begy and begx are
        relative to the origin of the window orig rather than the
        screen.  There is no difference between subwindows and derived
        windows.

        mvderwin() moves a derived window (or subwindow) inside its
        parent window.  The screen-relative parameters of the window are
        not changed.  This routine is used to display different parts of
        the parent window at the same physical position on the screen.

        dupwin() creates an exact duplicate of the window win.

        wsyncup() causes a touchwin() of all of the window's parents.

        If wsyncok() is called with a second argument of TRUE, this
        causes a wsyncup() to be called every time the window is
        changed.

        wcursyncup() causes the current cursor position of all of a
        window's ancestors to reflect the current cursor position of the
        current window.

        wsyncdown() causes a touchwin() of the current window if any of
        its parent's windows have been touched.

        resize_window() allows the user to resize an existing window. It 
        returns the pointer to the new window, or NULL on failure.

        wresize() is an ncurses-compatible wrapper for resize_window().
        Note that, unlike ncurses, it will NOT process any subwindows of
        the window. (However, you still can call it _on_ subwindows.) It 
        returns OK or ERR.

        PDC_makenew() allocates all data for a new WINDOW * except the
        actual lines themselves. If it's unable to allocate memory for
        the window structure, it will free all allocated memory and
        return a NULL pointer.

        PDC_makelines() allocates the memory for the lines.

        PDC_sync() handles wrefresh() and wsyncup() calls when a window
        is changed.

  Return Value:
        newwin(), subwin(), derwin() and dupwin() return a pointer
        to the new window, or NULL on failure. delwin(), mvwin(),
        mvderwin() and syncok() return OK or ERR. wsyncup(),
        wcursyncup() and wsyncdown() return nothing.

  Errors:
        It is an error to call resize_window() before calling initscr().
        Also, an error will be generated if we fail to create a newly
        sized replacement window for curscr, or stdscr. This could
        happen when increasing the window size. NOTE: If this happens,
        the previously successfully allocated windows are left alone;
        i.e., the resize is NOT cancelled for those windows.

  Portability                                X/Open    BSD    SYS V
        newwin                                  Y       Y       Y
        delwin                                  Y       Y       Y
        mvwin                                   Y       Y       Y
        subwin                                  Y       Y       Y
        derwin                                  Y       -       Y
        mvderwin                                Y       -       Y
        dupwin                                  Y       -      4.0
        wsyncup                                 Y       -      4.0
        syncok                                  Y       -      4.0
        wcursyncup                              Y       -      4.0
        wsyncdown                               Y       -      4.0
        resize_window                           -       -       -
        wresize                                 -       -       -
        PDC_makelines                           -       -       -
        PDC_makenew                             -       -       -
        PDC_sync                                -       -       -

**man-end****************************************************************/

#include <stdlib.h>

//------------------------------------------------------------------------------
WINDOW* PDC_makenew( int nlines, int ncols, int begy, int begx )
{
	__QCS_FCONTEXT( "PDC_makenew" );

    WINDOW* win;

    // allocate the window structure itself

    if( ( win = (WINDOW*)calloc( 1, sizeof( WINDOW ) ) ) == (WINDOW*)NULL )
	{
        return win;
	}

    // allocate the line pointer array

    if( ( win->_y = (chtype**)malloc( nlines * sizeof( chtype* ) ) ) == NULL )
    {
        free( win );
        return (WINDOW*)NULL;
    }

    // allocate the minchng and maxchng arrays
    if( ( win->_firstch = (int*)malloc( nlines * sizeof( int ) ) ) == NULL )
    {
        free( win->_y );
        free( win );
        return (WINDOW*)NULL;
    }

    if( ( win->_lastch = (int*)malloc( nlines * sizeof( int ) ) ) == NULL )
    {
        free( win->_firstch );
        free( win->_y );
        free( win );
        return (WINDOW*)NULL;
    }

    // initialize window variables

    win->_maxy = nlines;  // real max screen size 
    win->_maxx = ncols;   // real max screen size 
    win->_begy = begy;
    win->_begx = begx;
    win->_bkgd = ' ';     // wrs 4/10/93 -- initialize background to blank
    win->_clear = (bool) ( ( nlines == LINES ) && ( ncols == COLS ) );
    win->_bmarg = nlines - 1;
    win->_parx = win->_pary = -1;

    // init to say window all changed

    touchwin( win );

    return win;
}

//------------------------------------------------------------------------------
WINDOW* PDC_makelines( WINDOW* win )
{
	__QCS_FCONTEXT( "PDC_makelines" );

    int i, j, nlines, ncols;

    if( !win )
	{
        return (WINDOW*)NULL;
	}

    nlines = win->_maxy;
    ncols = win->_maxx;

    for( i = 0; i < nlines; i++ )
    {
        if( ( win->_y[ i ] = (chtype*)malloc( ncols * sizeof( chtype ) ) ) == NULL )
        {
            // if error, free all the data

            for( j = 0; j < i; j++ )
			{
                free( win->_y[ j ] );
			}

            free( win->_firstch );
            free( win->_lastch );
            free( win->_y );
            free( win );

            return (WINDOW*)NULL;
        }
    }

    return win;
}

//------------------------------------------------------------------------------
void PDC_sync( WINDOW* win )
{
    __QCS_FCONTEXT( "PDC_sync" );

    if( win->_immed )
	{
        wrefresh( win );
	}
    if( win->_sync )
	{
        wsyncup( win );
	}
}

//------------------------------------------------------------------------------
WINDOW* newwin( int nlines, int ncols, int begy, int begx )
{
	__QCS_FCONTEXT( "newwin" );

    WINDOW* win;

    PDC_LOG( ( "newwin() - called:lines=%d cols=%d begy=%d begx=%d\n", nlines, ncols, begy, begx ) );

    if( !nlines )
	{
        nlines = LINES - begy;
	}
    if( !ncols )
	{
        ncols  = COLS  - begx;
	}

    if( ( begy + nlines > SP->lines || begx + ncols > SP->cols ) || !( win = PDC_makenew( nlines, ncols, begy, begx ) ) || !( win = PDC_makelines( win ) ) )
	{
        return (WINDOW*)NULL;
	}

    werase( win );

    return win;
}

//------------------------------------------------------------------------------
int delwin(WINDOW *win)
{
	__QCS_FCONTEXT( "delwin" );

    int i;

    if( !win )
	{
        return ERR;
	}

    // subwindows use parents' lines

    if( !( win->_flags & ( _SUBWIN | _SUBPAD ) ) )
	{
        for( i = 0; i < win->_maxy && win->_y[ i ]; i++ )
		{
            if( win->_y[ i ] )
			{
                free( win->_y[ i ] );
			}
		}
	}

    free( win->_firstch );
    free( win->_lastch );
    free( win->_y );
    free( win );

    return 0;
}

//------------------------------------------------------------------------------
int mvwin( WINDOW* win, int y, int x )
{
    __QCS_FCONTEXT( "mvwin" );

    if( !win || ( y + win->_maxy > LINES || y < 0 ) || ( x + win->_maxx > COLS || x < 0 ) )
	{
        return ERR;
	}

    win->_begy = y;
    win->_begx = x;
    touchwin( win );

    return 0;
}

//------------------------------------------------------------------------------
WINDOW* subwin( WINDOW* orig, int nlines, int ncols, int begy, int begx )
{
	__QCS_FCONTEXT( "subwin" );
    WINDOW* win;
    int i;
    int j = begy - orig->_begy;
    int k = begx - orig->_begx;

    // make sure window fits inside the original one

    if( !orig || ( begy < orig->_begy ) || ( begx < orig->_begx ) || ( begy + nlines ) > ( orig->_begy + orig->_maxy ) || ( begx + ncols ) > ( orig->_begx + orig->_maxx ) )
	{
        return (WINDOW*)NULL;
	}

    if( !nlines )
	{
        nlines = orig->_maxy - 1 - j;
	}

    if( !ncols )
	{
        ncols  = orig->_maxx - 1 - k;
	}

    if( !( win = PDC_makenew( nlines, ncols, begy, begx ) ) )
	{
        return (WINDOW*)NULL;
	}

    // initialize window variables

    win->_attrs = orig->_attrs;
    win->_bkgd = orig->_bkgd;
    win->_leaveit = orig->_leaveit;
    win->_scroll = orig->_scroll;
    win->_nodelay = orig->_nodelay;
    win->_use_keypad = orig->_use_keypad;
    win->_immed = orig->_immed;
    win->_sync = orig->_sync;
    win->_pary = j;
    win->_parx = k;
    win->_parent = orig;

    for( i = 0; i < nlines; i++, j++ )
	{
        win->_y[ i ] = orig->_y[ j ] + k;
	}

    win->_flags |= _SUBWIN;

    return win;
}

//------------------------------------------------------------------------------
WINDOW* derwin( WINDOW* orig, int nlines, int ncols, int begy, int begx )
{
	__QCS_FCONTEXT( "derwin" );
    return subwin( orig, nlines, ncols, begy + orig->_begy, begx + orig->_begx );
}

//------------------------------------------------------------------------------
int mvderwin( WINDOW* win, int pary, int parx )
{
	__QCS_FCONTEXT( "mvderwin" );

    int i, j;
    WINDOW* mypar;

    if( !win || !( win->_parent ) )
	{
        return ERR;
	}

    mypar = win->_parent;

    if( pary < 0 || parx < 0 || ( pary + win->_maxy ) > mypar->_maxy || ( parx + win->_maxx ) > mypar->_maxx )
	{
        return ERR;
	}

    j = pary;

    for( i = 0; i < win->_maxy; i++ )
	{
        win->_y[ i ] = ( mypar->_y[ j++ ]) + parx;
	}

    win->_pary = pary;
    win->_parx = parx;

    return 0;
}

//------------------------------------------------------------------------------
WINDOW* dupwin( WINDOW* win )
{
	__QCS_FCONTEXT( "dupwin" );

    WINDOW* pnew;
    chtype* ptr, *ptr1;
    int nlines, ncols, begy, begx, i;

    if( !win )
	{
        return (WINDOW*)NULL;
	}

    nlines = win->_maxy;
    ncols = win->_maxx;
    begy = win->_begy;
    begx = win->_begx;

    if( !( pnew = PDC_makenew( nlines, ncols, begy, begx ) ) || !( pnew = PDC_makelines( pnew ) ) )
	{
        return (WINDOW *)NULL;
	}

    // copy the contents of win into new

    for( i = 0; i < nlines; i++ )
    {
        for( ptr = pnew->_y[ i ], ptr1 = win->_y[ i ]; ptr < pnew->_y[ i ] + ncols; ptr++, ptr1++ )
		{
            *ptr = *ptr1;
		}

        pnew->_firstch[ i ] = 0;
        pnew->_lastch[ i ] = ncols - 1;
    }

    pnew->_curx = win->_curx;
    pnew->_cury = win->_cury;
    pnew->_maxy = win->_maxy;
    pnew->_maxx = win->_maxx;
    pnew->_begy = win->_begy;
    pnew->_begx = win->_begx;
    pnew->_flags = win->_flags;
    pnew->_attrs = win->_attrs;
    pnew->_clear = win->_clear;
    pnew->_leaveit = win->_leaveit;
    pnew->_scroll = win->_scroll;
    pnew->_nodelay = win->_nodelay;
    pnew->_use_keypad = win->_use_keypad;
    pnew->_tmarg = win->_tmarg;
    pnew->_bmarg = win->_bmarg;
    pnew->_parx = win->_parx;
    pnew->_pary = win->_pary;
    pnew->_parent = win->_parent;
    pnew->_bkgd = win->_bkgd;
    pnew->_flags = win->_flags;

    return pnew;
}

//------------------------------------------------------------------------------
WINDOW* resize_window( WINDOW* win, int nlines, int ncols )
{
	__QCS_FCONTEXT( "resize_window" );

    WINDOW* pnew;
    int i, save_cury, save_curx, new_begy, new_begx;

    if( !win )
	{
        return (WINDOW*)NULL;
	}

    if( win->_flags & _SUBPAD )
    {
        if( !( pnew = subpad( win->_parent, nlines, ncols, win->_begy, win->_begx ) ) )
		{
            return (WINDOW*)NULL;
		}
    }
    else if( win->_flags & _SUBWIN )
    {
        if( !( pnew = subwin( win->_parent, nlines, ncols, win->_begy, win->_begx ) ) )
		{
            return (WINDOW*)NULL;
		}
    }
    else
    {
        if( win == SP->slk_winptr )
        {
            new_begy = SP->lines - SP->slklines;
            new_begx = 0;
        }
        else
        {
            new_begy = win->_begy;
            new_begx = win->_begx;
        }

        if( !( pnew = PDC_makenew( nlines, ncols, new_begy, new_begx ) ) )
		{
            return (WINDOW*)NULL;
		}
    }

    save_curx = min( win->_curx, pnew->_maxx );
    save_cury = min( win->_cury, pnew->_maxy );

    if( !( win->_flags & ( _SUBPAD | _SUBWIN ) ) )
    {
        if( !( pnew = PDC_makelines( pnew ) ) )
		{
            return (WINDOW*)NULL;
		}

        werase( pnew );

        copywin( win, pnew, 0, 0, 0, 0, min( win->_maxy, pnew->_maxy ) - 1, min( win->_maxx, pnew->_maxx ) - 1, FALSE );

        for( i = 0; i < win->_maxy && win->_y[ i ]; i++ )
		{
            if( win->_y[ i ] )
			{
                free( win->_y[ i ] );
			}
		}
    }

    pnew->_flags = win->_flags;
    pnew->_attrs = win->_attrs;
    pnew->_clear = win->_clear;
    pnew->_leaveit = win->_leaveit;
    pnew->_scroll = win->_scroll;
    pnew->_nodelay = win->_nodelay;
    pnew->_use_keypad = win->_use_keypad;
    pnew->_tmarg = ( win->_tmarg > pnew->_maxy - 1 ) ? 0 : win->_tmarg;
    pnew->_bmarg = ( win->_bmarg == win->_maxy - 1 ) ? pnew->_maxy - 1 : min( win->_bmarg, ( pnew->_maxy - 1 ) );
    pnew->_parent = win->_parent;
    pnew->_immed = win->_immed;
    pnew->_sync = win->_sync;
    pnew->_bkgd = win->_bkgd;
    pnew->_curx = save_curx;
    pnew->_cury = save_cury;

    free( win->_firstch );
    free( win->_lastch );
    free( win->_y );

    *win = *pnew;
    free( pnew );

    return win;
}

//------------------------------------------------------------------------------
int wresize( WINDOW* win, int nlines, int ncols )
{
	__QCS_FCONTEXT( "wresize" );

    return ( resize_window( win, nlines, ncols ) ? 0 : ERR );
}

//------------------------------------------------------------------------------
void wsyncup( WINDOW* win )
{
	__QCS_FCONTEXT( "wsyncup" );

    WINDOW* tmp;

    for( tmp = win; tmp; tmp = tmp->_parent )
	{
        touchwin( tmp );
	}
}

//------------------------------------------------------------------------------
int syncok( WINDOW* win, bool bf )
{
	__QCS_FCONTEXT( "syncok" );

    if( !win )
	{
        return ERR;
	}

    win->_sync = bf;

    return 0;
}

//------------------------------------------------------------------------------
void wcursyncup( WINDOW* win )
{
	__QCS_FCONTEXT( "wcursyncup" );

    WINDOW* tmp;

    for( tmp = win; tmp && tmp->_parent; tmp = tmp->_parent )
	{
        wmove( tmp->_parent, tmp->_pary + tmp->_cury, tmp->_parx + tmp->_curx );
	}
}

//------------------------------------------------------------------------------
void wsyncdown( WINDOW* win )
{
	__QCS_FCONTEXT( "wsyncdown" );
    WINDOW* tmp;

    for( tmp = win; tmp; tmp = tmp->_parent )
    {
        if( is_wintouched( tmp ) )
        {
            touchwin( win );
            break;
        }
    }
}
