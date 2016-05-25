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
/*	Copyright (c) 1984, 1986, 1987, 1988, 1989 AT&T	*/
/*	  All Rights Reserved  	*/


/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */
/*
 * Portions Copyright (c) 2005 Gunnar Ritter, Freiburg i. Br., Germany
 *
 * Sccsid @(#)test.c	1.10 (gritter) 12/25/06
 */
/* from OpenSolaris "test.c	1.15	05/06/08 SMI" */

/*
 *      test expression
 *      [ expression ]
 */

#include	"defs.h"
#include <sys/types.h>
#include <sys/stat.h>

static int	ap, ac;
static unsigned char **av;

/* test.c */
static unsigned char *nxtarg(int);
static int sexp(void);
static int e1(void);
static int e2(void);
static int e3(void);
static int ftype(const unsigned char *, int);
static int filtyp(const unsigned char *, int);
static int fsizep(const unsigned char *);
static void bfailed(const unsigned char *, const unsigned char *,
		const unsigned char *);

int 
test(int argn, unsigned char *com[])
{
	ac = argn;
	av = com;
	ap = 1;
	if (eq(com[0],(const unsigned char*)"["))
	{
		if (!eq(com[--ac], (const unsigned char*)"]"))
			failed((const unsigned char*)"test", (const unsigned char*)"] missing");
	}
	com[ac] = 0;
	if (ac <= 1)
		return(1);
#ifdef	SUS
	if (ac == 2)
		return(eq(nxtarg(0), ""));
	if (ac == 3 || ac == 4)
		return(!e3());
#endif	/* SUS */
	return(sexp() ? 0 : 1);
}

static unsigned char *
nxtarg(int mt)
{
	if (ap >= ac)
	{
		if (mt)
		{
			ap++;
			return(0);
		}
		failed((const unsigned char*)"test", (const unsigned char*)"argument expected");
	}
	return(av[ap++]);
}

static int 
sexp(void)
{
	int	p1;
	unsigned char	*p2;

	p1 = e1();
	p2 = nxtarg(1);
	if (p2 != 0)
	{
		if (eq(p2, (const unsigned char*)"-o"))
			return(p1 | sexp());

		/* if (!eq(p2, ")"))
			failed("test", synmsg); */
	}
	ap--;
	return(p1);
}

static int 
e1(void)
{
	int	p1;
	unsigned char	*p2;

	p1 = e2();
	p2 = nxtarg(1);

	if ((p2 != 0) && eq(p2, (const unsigned char*)"-a"))
		return(p1 & e1());
	ap--;
	return(p1);
}

static int 
e2(void)
{
	if (eq(nxtarg(0), (const unsigned char*)"!"))
		return(!e3());
	ap--;
	return(e3());
}

static int 
e3(void)
{
	int	p1;
	register unsigned char	*a;
	unsigned char	*p2;
	long long	ll_1, ll_2;

	a = nxtarg(0);
	if (eq(a, (const unsigned char*)"("))
	{
		p1 = sexp();
		if (!eq(nxtarg(0), (const unsigned char*)")"))
			failed((const unsigned char*)"test",(const unsigned char*)") expected");
		return(p1);
	}
	p2 = nxtarg(1);
	ap--;
	if ((p2 == 0) || (!eq(p2, (const unsigned char*)"=") && !eq(p2, (const unsigned char*)"!=")))
	{
		if (eq(a,(const unsigned char*) "-r"))
			return(chk_access(nxtarg(0), S_IREAD, 0) == 0);
		if (eq(a, (const unsigned char*)"-w"))
			return(chk_access(nxtarg(0), S_IWRITE, 0) == 0);
		if (eq(a, (const unsigned char*)"-x"))
			return(chk_access(nxtarg(0), S_IEXEC, 0) == 0);
#ifdef	SUS
		if (eq(a, (const unsigned char*)"-e"))
			return(access(nxtarg(0), F_OK) == 0);
		if (eq(a, (const unsigned char*)"-S"))
			return(filtyp(nxtarg(0), S_IFSOCK));
		if (eq(a,(const unsigned char*) "!"))
			return(!e3());
#endif	/* SUS */
		if (eq(a, (const unsigned char*)"-d"))
			return(filtyp(nxtarg(0), S_IFDIR));
		if (eq(a, (const unsigned char*)"-c"))
			return(filtyp(nxtarg(0), S_IFCHR));
		if (eq(a, (const unsigned char*)"-b"))
			return(filtyp(nxtarg(0), S_IFBLK));
		if (eq(a, (const unsigned char*)"-f"))
			if (ucb_builtins) {
				sstat statb;
			
				return(stat((char *)nxtarg(0), &statb) >= 0 &&
					(statb.st_mode & S_IFMT) != S_IFDIR);
			}
			else
				return(filtyp(nxtarg(0), S_IFREG));
		if (eq(a, (const unsigned char*)"-u"))
			return(ftype(nxtarg(0), S_ISUID));
		if (eq(a, (const unsigned char*)"-g"))
			return(ftype(nxtarg(0), S_ISGID));
		if (eq(a, (const unsigned char*)"-k"))
			return(ftype(nxtarg(0), S_ISVTX));
		if (eq(a, (const unsigned char*)"-p"))
			return(filtyp(nxtarg(0), S_IFIFO));
		if (eq(a, (const unsigned char*)"-h") || eq(a, (const unsigned char*)"-L"))
			return(filtyp(nxtarg(0), S_IFLNK));
   		if (eq(a, (const unsigned char*)"-s"))
			return(fsizep(nxtarg(0)));
		if (eq(a, (const unsigned char*)"-t"))
		{
			if (ap >= ac)		/* no args */
				return(isatty(1));
			else if (eq((a = nxtarg(0)), (const unsigned char*)"-a") || eq(a, (const unsigned char*)"-o"))
			{
				ap--;
				return(isatty(1));
			}
			else
				return(isatty(atoi((char *)a)));
		}
		if (eq(a, (const unsigned char*)"-n"))
			return(!eq(nxtarg(0), (const unsigned char*)""));
		if (eq(a, (const unsigned char*)"-z"))
			return(eq(nxtarg(0), (const unsigned char*)""));
	}

	p2 = nxtarg(1);
	if (p2 == 0)
		return(!eq(a, (const unsigned char*)""));
	if (eq(p2, (const unsigned char*)"-a") || eq(p2, (const unsigned char*)"-o"))
	{
		ap--;
		return(!eq(a, (const unsigned char*)""));
	}
	if (eq(p2, (const unsigned char*)"="))
		return(eq(nxtarg(0), a));
	if (eq(p2, (const unsigned char*)"!="))
		return(!eq(nxtarg(0), a));
	ll_1 = stoifll(a);
	ll_2 = stoifll(nxtarg(0));
	if (eq(p2, (const unsigned char*)"-eq"))
		return (ll_1 == ll_2);
	if (eq(p2, (const unsigned char*)"-ne"))
		return (ll_1 != ll_2);
	if (eq(p2, (const unsigned char*)"-gt"))
		return (ll_1 > ll_2);
	if (eq(p2, (const unsigned char*)"-lt"))
		return (ll_1 < ll_2);
	if (eq(p2, (const unsigned char*)"-ge"))
		return (ll_1 >= ll_2);
	if (eq(p2, (const unsigned char*)"-le"))
		return (ll_1 <= ll_2);

	bfailed((const unsigned char*)btest, (const unsigned char*)badop, p2);
/* NOTREACHED */
	return 0;
}


static int 
ftype(const unsigned char *f, int field)
{
	sstat statb;

	if (stat((char *)f, &statb) < 0)
		return(0);
	if ((statb.st_mode & field) == field)
		return(1);
	return(0);
}

static int 
filtyp(const unsigned char *f, int field)
{
	sstat statb;
	typedef int(*fstat)( const char*, sstat*);
	fstat statf = (field == S_IFLNK) ? lstat : stat;

	if ((*statf)((const char*)f, &statb) < 0)
		return(0);
	if ((statb.st_mode & S_IFMT) == field)
		return(1);
	else
		return(0);
}



static int 
fsizep(const unsigned char *f)
{
	sstat statb;

	if (stat((char *)f, &statb) < 0)
		return(0);
	return(statb.st_size > 0);
}

/*
 * fake diagnostics to continue to look like original
 * test(1) diagnostics
 */
static void
bfailed(const unsigned char *s1, const unsigned char *s2,
		const unsigned char *s3)
{
	prp();
	prs(s1);
	if (s2)
	{
		prs((const unsigned char*)colon);
		prs(s2);
		prs(s3);
	}
	newline();
	exitsh(ERROR);
}
