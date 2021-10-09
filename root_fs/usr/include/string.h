/*
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)string.h	5.1 (Berkeley) 85/08/05
 *
 **********************************************************************
 * HISTORY
 * $Log:	string.h,v $
 * Revision 2.2  89/06/30  12:12:11  bww
 * 	Added function prototype declarations.  Sys5 declarations
 * 	are now only contained in <strings.h>.
 * 	[89/06/30  12:02:23  bww]
 * 
 * Revision 1.2  89/05/26  12:26:16  bww
 * 	CMU CS as of 89/05/15
 * 	[89/05/26  09:46:50  bww]
 * 
 **********************************************************************
 */

#include <strings.h>

/*
 * these next few are obsolete trash
 */

#if __STDC__
extern char *strcpyn(char*, const char*, int);
extern char *strcatn(char*, const char*, int);
extern int strcmpn(const char*, const char*, int);
#else
extern char *strcpyn();
extern char *strcatn();
extern int strcmpn();
#endif
