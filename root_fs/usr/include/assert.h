/*
 * HISTORY
 * $Log:	assert.h,v $
 * Revision 3.2  90/11/10  14:37:27  bww
 * 	Added __STDC__ support.
 * 	[90/11/10  14:34:27  bww]
 * 
 */
/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that: (1) source distributions retain this entire copyright
 * notice and comment, and (2) distributions including binaries display
 * the following acknowledgement:  ``This product includes software
 * developed by the University of California, Berkeley and its contributors''
 * in the documentation or other materials provided with the distribution
 * and in all advertising materials mentioning features or use of this
 * software. Neither the name of the University nor the names of its
 * contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	@(#)assert.h	4.3 (Berkeley) 5/6/90
 */

#ifdef NDEBUG
#define	assert
#define	_assert
#else
#if __STDC__
#define	assert(expression) { \
	if (!(expression)) { \
		(void)fprintf(stderr, \
		    "assertion \"%s\" failed: file \"%s\", line %d\n", \
		    # expression, __FILE__, __LINE__); \
		exit(2); \
	} \
}
#else
#define	assert(expression) { \
	if (!(expression)) { \
		(void)fprintf(stderr, \
		    "assertion \"%s\" failed: file \"%s\", line %d\n", \
		    "expression", __FILE__, __LINE__); \
		exit(2); \
	} \
}
#endif
#define	_assert(expression)	assert(expression)
#endif
