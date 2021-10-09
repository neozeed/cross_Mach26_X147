/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)mp.h	5.1 (Berkeley) 5/30/85
 */

/*
 **********************************************************************
 * HISTORY
 * $Log:	mp.h,v $
 * Revision 2.2  89/06/26  20:20:17  bww
 * 	Merged vax -> BYTE_MSF change into 4.3-tahoe version.
 * 	[89/06/26  20:15:20  bww]
 * 
 * 04-Nov-87  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Changed vax test to BYTE_MSF test.
 *
 **********************************************************************
 */
#define MINT struct mint
MINT
{	int len;
	short *val;
};
#define FREE(x) {if(x.len!=0) {free((char *)x.val); x.len=0;}}
#ifndef DBG
#define shfree(u) free((char *)u)
#else
#include <stdio.h>
#define shfree(u) { if(dbg) fprintf(stderr, "free %o\n", u); free((char *)u);}
extern int dbg;
#endif
#if	BYTE_MSF
struct half
{	short high;
	short low;
};
#else
struct half
{	short low;
	short high;
};
#endif
extern MINT *itom();
extern short *xalloc();

#ifdef lint
extern xv_oid;
#define VOID xv_oid =
#else
#define VOID
#endif
