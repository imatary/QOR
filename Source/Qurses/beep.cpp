/* Public Domain Curses */

#include "Qurses/curspriv.h"

RCSID("$Id: beep.c,v 1.34 2008/07/13 16:08:17 wmcbrine Exp $")

/*man-start**************************************************************

  Name:                                                         beep

  Synopsis:
        int beep(void);
        int flash(void);

  Description:
        beep() sounds the audible bell on the terminal, if possible;
        if not, it calls flash().

        flash() "flashes" the screen, by inverting the foreground and
        background of every cell, pausing, and then restoring the
        original attributes.

  Return Value:
        These functions return OK.

  Portability                                X/Open    BSD    SYS V
        beep                                    Y       Y       Y
        flash                                   Y       Y       Y

**man-end****************************************************************/

//------------------------------------------------------------------------------
int beep( void )
{
    __QCS_FCONTEXT( "beep" );

    if( SP->audible )
	{
        PDC_beep();
	}
    else
	{
        flash();
	}

    return 0;
}

//------------------------------------------------------------------------------
int flash( void )
{
	__QCS_FCONTEXT( "flash" );

    int z, y, x;

    // Reverse each cell; wait; restore the screen

    for( z = 0; z < 2; z++ )
    {
        for( y = 0; y < LINES; y++ )
		{
            for( x = 0; x < COLS; x++ )
			{
                curscr->_y[ y ][ x ] ^= A_REVERSE;
			}
		}

        wrefresh( curscr );

        if( !z )
		{
            napms( 50 );
		}
    }

    return 0;
}
