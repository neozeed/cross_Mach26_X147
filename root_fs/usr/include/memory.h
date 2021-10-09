/*
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)memory.h	5.1 (Berkeley) 85/08/05
 *
 **********************************************************************
 * HISTORY
 * $Log:	memory.h,v $
 * Revision 2.2  89/06/30  12:11:10  bww
 * 	Added function prototype declarations.
 * 	[89/06/30  11:57:46  bww]
 * 
 * Revision 1.2  89/05/26  12:26:23  bww
 * 	CMU CS as of 89/05/15
 * 	[89/05/26  09:46:50  bww]
 * 
 **********************************************************************
 */

/*
 * Definitions of the Sys5 compat memory manipulation routines
 */

#if __STDC__
extern char *memccpy(char*, const char*, int, int);
extern char *memchr(const char*, int, int);
extern int memcmp(const char*, const char*, int);
extern char *memcpy(char*, const char*, int);
extern char *memset(char*, int, int);
#else
extern char *memccpy();
extern char *memchr();
extern int memcmp();
extern char *memcpy();
extern char *memset();
#endif
