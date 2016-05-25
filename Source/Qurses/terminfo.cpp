/* Public Domain Curses */

#include "Qurses/curspriv.h"

RCSID("$Id: terminfo.c,v 1.37 2008/07/21 12:29:20 wmcbrine Exp $")

/*man-start**************************************************************

  Name:                                                         terminfo

  Synopsis:
        int mvcur(int oldrow, int oldcol, int newrow, int newcol);
        int vidattr(chtype attr);
        int vid_attr(attr_t attr, short color_pair, void *opt);
        int vidputs(chtype attr, int (*putfunc)(int));
        int vid_puts(attr_t attr, short color_pair, void *opt,
                int (*putfunc)(int));

        int del_curterm(TERMINAL *);
        int putp(const char *);
        int restartterm(const char *, int, int *);
        TERMINAL *set_curterm(TERMINAL *);
        int setterm(const char *term);
        int setupterm(const char *, int, int *);
        int tgetent(char *, const char *);
        int tgetflag(const char *);
        int tgetnum(const char *);
        char *tgetstr(const char *, char **);
        char *tgoto(const char *, int, int);
        int tigetflag(const char *);
        int tigetnum(const char *);
        char *tigetstr(const char *);
        char *tparm(const char *,long, long, long, long, long, long,
                long, long, long);
        int tputs(const char *, int, int (*)(int));

  Description:
        mvcur() lets you move the physical cursor without updating any 
        window cursor positions. It returns OK or ERR.

        The rest of these functions are currently implemented as stubs, 
        returning the appropriate errors and doing nothing else.

  Portability                                X/Open    BSD    SYS V
        mvcur                                   Y       Y       Y

**man-end****************************************************************/

#include "Qurses/term.h"

TERMINAL* cur_term = NULL;

//------------------------------------------------------------------------------
int mvcur(int oldrow, int oldcol, int newrow, int newcol)
{
	__QCS_FCONTEXT( "mvcur" );

    if( ( newrow >= LINES ) || ( newcol >= COLS ) || ( newrow < 0 ) || ( newcol < 0 ) )
	{
        return ERR;
	}

    PDC_gotoyx( newrow, newcol );
    SP->cursrow = newrow;
    SP->curscol = newcol;

    return 0;
}

//------------------------------------------------------------------------------
int vidattr( chtype attr )
{
	__QCS_FCONTEXT( "vidattr" );
    return ERR;
}

//------------------------------------------------------------------------------
int vid_attr( attr_t attr, short color_pair, void* opt )
{
    __QCS_FCONTEXT( "vid_attr" );
    return ERR;
}

//------------------------------------------------------------------------------
int vidputs( chtype attr, int (*putfunc)( int ) )
{
    __QCS_FCONTEXT( "vidputs" );
    return ERR;
}

//------------------------------------------------------------------------------
int vid_puts( attr_t attr, short color_pair, void* opt, int (*putfunc)( int ) )
{
    __QCS_FCONTEXT( "vid_puts" );
    return ERR;
}

//------------------------------------------------------------------------------
int del_curterm( TERMINAL* oterm )
{
    __QCS_FCONTEXT( "del_curterm" );
    return ERR;
}

//------------------------------------------------------------------------------
int putp( const char* str )
{
    __QCS_FCONTEXT( "putp" );
    return ERR;
}

//------------------------------------------------------------------------------
int restartterm( const char* term, int filedes, int* errret )
{
    __QCS_FCONTEXT( "restartterm" );

    if( errret )
	{
        *errret = -1;
	}

    return ERR;
}

//------------------------------------------------------------------------------
TERMINAL* set_curterm( TERMINAL* nterm )
{
	__QCS_FCONTEXT( "set_curterm" );

    return (TERMINAL *)NULL;
}

//------------------------------------------------------------------------------
int setterm( const char* term )
{
    __QCS_FCONTEXT( "setterm" );
    return ERR;
}

//------------------------------------------------------------------------------
int setupterm( const char* term, int filedes, int* errret )
{
    __QCS_FCONTEXT( "setupterm" );

    if( errret )
	{
        *errret = -1;
	}
    else
	{
        fprintf(stderr, "There is no terminfo database\n");
	}

    return ERR;
}

//------------------------------------------------------------------------------
int tgetent( char* bp, const char* name )
{
	__QCS_FCONTEXT( "tgetent" );
    return ERR;
}

//------------------------------------------------------------------------------
int tgetflag( const char* id )
{
	__QCS_FCONTEXT( "tgetflag" );
    return ERR;
}

//------------------------------------------------------------------------------
int tgetnum( const char* id )
{
	__QCS_FCONTEXT( "tgetnum" );
    return ERR;
}

//------------------------------------------------------------------------------
char* tgetstr( const char* id, char** area )
{
	__QCS_FCONTEXT( "tgetstr" );
    return (char*)NULL;
}

//------------------------------------------------------------------------------
char* tgoto( const char* cap, int col, int row )
{
    __QCS_FCONTEXT( "tgoto" );
    return (char*)NULL;
}

//------------------------------------------------------------------------------
int tigetflag( const char* capname )
{
    __QCS_FCONTEXT( "tigetflag" );
    return -1;
}

//------------------------------------------------------------------------------
int tigetnum( const char* capname )
{
    __QCS_FCONTEXT( "tigetnum" );
    return -2;
}

//------------------------------------------------------------------------------
char* tigetstr( const char* capname )
{
    __QCS_FCONTEXT( "tigetstr" );
    return (char*)(-1);
}

//------------------------------------------------------------------------------
char* tparm( const char* cap, long p1, long p2, long p3, long p4, long p5, long p6, long p7, long p8, long p9 )
{
    __QCS_FCONTEXT( "tparm" );
    return (char*)NULL;
}

//------------------------------------------------------------------------------
int tputs( const char* str, int affcnt, int (*putfunc)( int ) )
{
    __QCS_FCONTEXT( "tputs" );
    return ERR;
}
