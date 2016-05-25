/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License, Version 1.0 only
 * (the "License").  You may not use this file except in compliance
 * with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright (c) 2001 by Sun Microsystems, Inc.
 * All rights reserved.
 */

/*	Copyright (c) 1984, 1986, 1987, 1988, 1989 AT&T	*/
/*	  All Rights Reserved  	*/

/*
 * Portions Copyright (c) 2005 Gunnar Ritter, Freiburg i. Br., Germany
 *
 * Sccsid @(#)blok.c	1.7 (gritter) 6/16/05
 */

/* from OpenSolaris "blok.c	1.19	05/06/08 SMI" */
/*
 *	UNIX shell
 */

#include	"defs.h"


// storage allocator (circular first fit strategy)

#define	BUSY 01
#define	busy(x)	(Rcheat((x)->word) & BUSY)

unsigned	brkincr = BRKINCR;
blk* blokp;			// current search pointer
blk* bloktop;		// top of arena (last blok)
unsigned char		*brkbegin;

//-------------------------------------------------------------------------------
void* alloc( size_t nbytes )
{
	register unsigned rbytes = round( nbytes + BYTESPERWORD, BYTESPERWORD );

	if( stakbot == 0 ) 
	{
		addblok( (unsigned)0 );
	}

	for (;;)
	{
		int	c = 0;
		register blk* p = blokp;
		register blk* q;

		do
		{
			if (!busy(p))
			{
				while (!busy(q = p->word))
				{
					p->word = q->word;
				}

				if( (char*)q - (char*)p >= rbytes )
				{
					blokp = (blk*) ( (char*)p + rbytes);

					if (q > blokp)
					{
						blokp->word = p->word;
					}

					p->word = (blk*) ( Rcheat( blokp ) | BUSY );
					return ((char *)(p + 1));
				}
			}
			q = p;
			p = (blk*)( Rcheat( p->word ) & ~BUSY );
		} while( p > q || ( c++ ) == 0 );

		addblok( rbytes );
	}
}

//-------------------------------------------------------------------------------
void addblok( unsigned reqd )
{
	if (stakbot == 0)
	{
		brkbegin = setbrk(3 * BRKINCR);
		bloktop = (blk*)brkbegin;
	}

	if (stakbas != staktop)
	{
		register unsigned char* rndstak;
		register blk* blokstak;

		if( staktop >= brkend )
		{
			growstak( staktop );
		}
		pushstak( 0 );
		rndstak = (unsigned char *)round( staktop, BYTESPERWORD );
		blokstak = (blk*)(stakbas) - 1;
		blokstak->word = stakbsy;
		stakbsy = blokstak;
		bloktop->word = (blk*)( Rcheat( rndstak ) | BUSY );
		bloktop = (blk*)( rndstak );
	}
	reqd += brkincr;
	reqd &= ~(brkincr - 1);
	blokp = bloktop;
	/*
	 * brkend points to the first invalid address.
	 * make sure bloktop is valid.
	 */
	if( (unsigned char*)&bloktop->word >= brkend )
	{
		if( setbrk( (unsigned)((unsigned char *) (&bloktop->word) - brkend + sizeof(blk) ) ) == (unsigned char*)-1 )
		{
			error( (const unsigned char*)nospace );
		}
	}
	bloktop = bloktop->word = (blk*)( Rcheat( bloktop ) + reqd );
	if( (unsigned char*)&bloktop->word >= brkend )
	{
		if( setbrk( (unsigned)((unsigned char *)(&bloktop->word) - brkend + sizeof(blk) ) ) == (unsigned char *)-1 )
		{
			error( (const unsigned char*)nospace );
		}
	}
	bloktop->word = (blk*)( brkbegin + 1 );
	{
		register unsigned char* stakadr = (unsigned char *)( bloktop + 2 );
		register unsigned char* sp = stakadr;
		if( reqd = ( staktop - stakbot ) )
		{
			if( stakadr + reqd >= brkend )
			{
				growstak( stakadr + reqd );
			}
			while( reqd-- > 0 )
			{
				*sp++ = *stakbot++;
			}
			sp--;
		}
		staktop = sp;
		if( staktop >= brkend )
		{
			growstak( staktop );
		}
		stakbas = stakbot = stakadr;
	}
}

//-------------------------------------------------------------------------------
void free( void* ap )
{
	register struct blk *p;

	if( ( p = (blk*)ap ) && p < bloktop && p > (blk*)brkbegin )
	{
#ifdef DEBUG
		chkbptr(p);
#endif
		--p;
		p->word = (blk*)( Rcheat( p->word ) & ~BUSY );
	}


}


#ifdef DEBUG
//-------------------------------------------------------------------------------
int chkbptr( blk* ptr )
{
	int	exf = 0;
	register blk* p = (blk*)brkbegin;
	register blk* q;
	int	us = 0, un = 0;

	for( ;; )
	{
		q = (blk*)( Rcheat( p->word ) & ~BUSY );

		if( p + 1 == ptr )
		{
			exf++;
		}

		if( q < (blk*)brkbegin || q > bloktop )
		{
			abort(3);
		}

		if( p == bloktop )
		{
			break;
		}

		if( busy( p ) )
		{
			us += q - p;
		}
		else
		{
			un += q - p;
		}

		if( p >= q )
		{
			abort( 4 );
		}

		p = q;
	}
	if( exf == 0 )
	{
		abort( 1 );
	}
}

//-------------------------------------------------------------------------------
int chkmem( void )
{
	register blk* p = (blk*)brkbegin;
	register blk* q;
	int	us = 0, un = 0;

	for (;;) 
	{
		q = (blk*)( Rcheat( p->word ) & ~BUSY );

		if( q < (blk*)brkbegin || q > bloktop )
		{
			abort( 3 );
		}

		if( p == bloktop )
		{
			break;
		}

		if( busy( p ) )
		{
			us += q - p;
		}
		else
		{
			un += q - p;
		}

		if( p >= q )
		{
			abort( 4 );
		}

		p = q;
	}

	prs("un/used/avail ");
	prn( un );
	blank();
	prn( us );
	blank();
	prn( (char*)bloktop - brkbegin - ( un + us ) );
	newline();
}

#endif

//-------------------------------------------------------------------------------
size_t blklen( char* q )
{
	register blk* pp = (blk*)q;
	register blk* p;

	--pp;
	p = (blk*)( Rcheat( pp->word ) & ~BUSY );

	return ( (size_t)( (long)p - (long)q ) );
}
