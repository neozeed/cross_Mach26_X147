/*
 * HISTORY
 * $Log:	machparam.h,v $
 * Revision 1.1  91/05/09  13:38:54  jaap
 * mt XINU initial version MSD 2.6
 * 
 */

/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * CMU-HISTORY
 * 02-06-90 Mary Thompson (mrt)
 *	Added more machine constants ala Tahoe.
 *
 * $CMU-Log:	machparam.h,v $
 * Revision 1.5  89/09/09  15:20:13  rvb
 * 	CLSIZE ====== 1 not 2
 * 	[89/09/07            rvb]
 * 
 * Revision 1.4  89/03/09  20:03:11  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/26  12:32:34  gm0w
 * 	Changes for cleanup.
 * 
 * 31-Dec-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Derived from MACH2.0 vax release.
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3
 *
 * 19-Jun-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Expanded UPAGES to 12 since with the extended
 *	number of file descriptors, the old size only allowed for one
 *	kernel stack page before reaching the red-zone.
 *	[V1(1)]
 */
 
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)machparam.h	7.1 (Berkeley) 6/5/86
 */
/*
 * Machine dependent constants for i386
 */
#define MACHINE "i386"

#include <machine/endian.h>

#define	CHAR_BIT	NBBY
#define	CHAR_MAX	0x7f
#define	CHAR_MIN	0x80
#define	CLK_TCK		60			/* for times() */
#define	INT_MAX		0x7fffffff
#define	INT_MIN		0x80000000
#define	LONG_MAX	0x7fffffff
#define	LONG_MIN	0x80000000
#define	SCHAR_MAX	0x7f
#define	SCHAR_MIN	0x80
#define	SHRT_MAX	0x7fff
#define	SHRT_MIN	0x8000
#define	UCHAR_MAX	0xff
#define	UINT_MAX	0xffffffff
#define	ULONG_MAX	0xffffffff
#define	USHRT_MAX	0xffff

/*
 * Machine dependent constants for 80386.
 */
#define NBPG	4096		/* bytes/page */
#define PGOFSET	(NBPG-1)	/* byte offset into page */
#define PGSHIFT	12		/* LOG2(NBPG) */

#define CLSIZE		1
#define CLSIZELOG2	0

#define SSIZE	1		/* initial stack size/NBPG */
#define SINCR	1		/* increment of stack/NBPG */

#define UPAGES	16		/* pages of u-area */

#define KERNBASE 0xc0000000

/*
 * Some macros for units conversion
 */
/* Core clicks (512 bytes) to segments and vice versa */
#define ctos(x)	(x)
#define stoc(x)	(x)

/* Core clicks (512 bytes) to disk blocks */
#define ctod(x)	(x)
#define dtoc(x)	(x)
#define dtob(x)	((x)<<9)

/* clicks to bytes */
#define ctob(x)	((x)<<9)

/* bytes to clicks */
#define btoc(x)	((((unsigned)(x)+511)>>9))

/*
 * Macros to decode processor status word.
 */
#define USMODE	3		/* current Xlevel == user */
#define SEL_RPL		0x03
#define USERMODE(cs)	(((cs) & SEL_RPL) == USMODE)
#define BASEPRI(x)  ((x) != 0)

#ifdef	KERNEL
#ifndef	LOCORE
int	cpuspeed;
#endif
#define DELAY(n)	{ register int N = cpuspeed * (n); while (--N > 0); }

#else	KERNEL
#define DELAY(n)	{ register int N = (n); while (--N > 0); }
#endif	KERNEL
