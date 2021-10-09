/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)dbm.h	5.1 (Berkeley) 3/27/86
 *
 **********************************************************************
 * HISTORY
 * $Log:	dbm.h,v $
 * Revision 2.2  89/06/30  12:10:28  bww
 * 	Added function prototype declarations.
 * 	[89/06/30  11:55:50  bww]
 * 
 * Revision 1.2  89/05/26  12:29:17  bww
 * 	CMU CS as of 89/05/15
 * 	[89/05/26  09:46:50  bww]
 * 
 **********************************************************************
 */

#ifndef NULL
/*
 * this is lunacy, we no longer use it (and never should have
 * unconditionally defined it), but, this whole file is for
 * backwards compatability - someone may rely on this.
 */
#define	NULL	((char *) 0)
#endif

#include <ndbm.h>

#if __STDC__
extern datum	fetch(datum);
extern datum	firstkey(void);
extern datum	nextkey(datum);
#else
datum	fetch();
datum	firstkey();
datum	nextkey();
#endif
#if 0
datum	makdatum();
datum	firsthash();
long	calchash();
long	hashinc();
#endif
