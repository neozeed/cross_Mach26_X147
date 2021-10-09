/*
 * HISTORY
 * $Log:	setjmp.h,v $
 * Revision 2.8  90/12/12  11:10:42  bww
 * 	Upgraded to Berkeley version 5.2, which includes
 * 	defining the symbol _JBLEN for all architectures.
 * 	[90/12/12  11:07:30  bww]
 * 
 * Revision 2.7  90/08/24  17:01:55  bww
 * 	Added mac2 case (to be the same as the sun3).
 * 	[90/08/24  17:01:10  bww]
 * 
 * Revision 2.6  90/05/03  19:59:41  bww
 * 	Added i386 case.
 * 	[90/05/03  19:58:16  bww]
 * 
 * Revision 2.5  90/04/26  18:10:31  bww
 * 	Added definitions for the Sun4, and
 * 	for sigsetjmp() and siglongjmp().
 * 	[90/04/26  18:09:19  bww]
 * 
 * Revision 2.4  89/08/14  13:44:00  bww
 * 	Add jmp_buf definition for PMAX (mips).
 * 	From "[89/08/03  13:41:22  mja]" at CMU.
 * 	[89/08/14            bww]
 * 
 * Revision 2.3  89/06/30  12:11:58  bww
 * 	Added function prototype declarations and protection for
 * 	recursive includes.
 * 	[89/06/30  12:01:04  bww]
 * 
 * Revision 2.2  89/06/26  20:20:31  bww
 * 	Merged changes for SUN3, IBMRT, Multimax, and Sequent into
 * 	4.3-tahoe version.
 * 	[89/06/26  20:17:09  bww]
 * 
 * Revision 1.2  89/05/26  12:28:43  bww
 * 	CMU CS as of 89/05/15
 * 	[89/06/04  19:14:49  bww]
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
 *	@(#)setjmp.h	5.2 (Berkeley) 5/29/90
 */

#ifndef _SETJMP_H_
#define _SETJMP_H_

#if	defined(multimax)
#define	_JBLEN	10
#endif
#if	defined(balance)
#define	_JBLEN	11		/* 4 regs, ... */
#endif
#if	defined(sun3)
#define	_JBLEN	15		/* pc, sigmask, onsstack, d2-7, a2-7 */
#endif
#if	defined(mac2)
#define	_JBLEN	14		/* pc, sigmask, d2-7, a2-7 */
#endif
#if	defined(ibmrt)
#define	_JBLEN	16
#endif
#if	defined(vax)
#define	_JBLEN	10
#endif
#if	defined(i386)
#define	_JBLEN	21
#endif
#if	defined(mips)
/*
 * onstack, sigmask, pc, r0-r31,
 * 40 padding words to match length of sigcontext structure
 */
#define	_JBLEN	(3+32+40)
#endif
#if	defined(sun4)
/*
 * onsstack,sigmask,sp,pc,npc,psr,g1,o0,wbcnt (sigcontext).
 * All else recovered by under/over(flow) handling.
 */
#define	_JBLEN	9
#endif

typedef int jmp_buf[_JBLEN];

/*
 * sigsetjmp/siglongjmp use the last int to decide if the
 * signal mask was saved or not.
 */
typedef	int sigjmp_buf[_JBLEN + 1];

#if __STDC__
extern int setjmp(jmp_buf);
extern void longjmp(jmp_buf, int);
extern int _setjmp(jmp_buf);
extern void _longjmp(jmp_buf, int);
extern int sigsetjmp(sigjmp_buf, int);
extern void siglongjmp(sigjmp_buf, int);
#else
extern int setjmp();
extern void longjmp();
extern int _setjmp();
extern void _longjmp();
extern int sigsetjmp();
extern void siglongjmp();
#endif

#if	defined(sun4)
/*
 * Routines that call setjmp have strange control flow graphs,
 * since a call to a routine that calls resume/longjmp will eventually
 * return at the setjmp site, not the original call site.  This
 * utterly wrecks control flow analysis.
 */
#pragma unknown_control_flow(sigsetjmp, setjmp, _setjmp)
#endif

#endif /* _SETJMP_H_ */
