/*
 * HISTORY
 * $Log:	asm.h,v $
 * Revision 1.1  91/05/09  13:35:24  jaap
 * mt XINU initial version MSD 2.6
 * 
 */

/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * CMU-HISTORY
 * $CMU-Log:	asm.h,v $
 * 27-Mar-90  Mary Thompson (mrt) at Carnegie-Mellon University
 *	Made profiling ENTRY conditional under GPROF or PROF
 *
 * Revision 2.1.1.6  90/03/29  20:45:08  rvb
 * 	Typo on ENTRY if gprof
 * 	[90/03/29            rvb]
 * 
 * Revision 2.1.1.5  90/02/28  15:47:31  rvb
 * 	fix SVC for "ifdef wheeze" [kupfer]
 * 
 * Revision 2.1.1.4  90/02/27  08:47:30  rvb
 * 	Fix the GPROF definitions.
 * 	 ENTRY(x) gets profiled iffdef GPROF.
 * 	 Entry(x) (and DATA(x)) is NEVER profiled.
 * 	 MCOUNT can be used by asm that intends to build a frame,
 * 	 after the frame is built.
 * 	[90/02/26            rvb]
 * 
 * Revision 2.1.1.3  90/02/09  17:23:23  rvb
 * 	Add #define addr16 .byte 0x67
 * 	[90/02/09            rvb]
 * 
 * Revision 2.1.1.2  89/11/10  09:51:33  rvb
 * 	Added LBi, SVC and ENTRY
 * 
 * Revision 2.1.1.1  89/10/22  11:29:38  rvb
 * 	New a.out and coff compatible .s files.
 * 	[89/10/16            rvb]
 * 
 */


#define S_ARG0	 4(%esp)
#define S_ARG1	 8(%esp)
#define S_ARG2	12(%esp)
#define S_ARG3	16(%esp)

#define FRAME	pushl %ebp; movl %esp, %ebp
#define EMARF	leave

#define B_ARG0	 8(%ebp)
#define B_ARG1	12(%ebp)
#define B_ARG2	16(%ebp)
#define B_ARG3	20(%ebp)

#ifdef	wheeze

#define ALIGN 4
#define EXT(x) x
#define L_EXT(x) x:
#if	__STDC__
#define LCL(x) .##x

#define LB(x,n) .##x
#define LBb(x,n) .##x
#define LBf(x,n) .##x
#else	/* __STDC__ */
#define LCL(x) ./**/x

#define LB(x,n) ./**/x
#define LBb(x,n) ./**/x
#define LBf(x,n) ./**/x
#endif	/* !__STDC__ */

#define	SVC lcall $7,$0

#define String .string
#define Value  .value
#define Times(a,b) [a\*b]
#define Divide(a,b) [a\\b]

#define INB	inb	(%dx)
#define OUTB	outb	(%dx)
#define INL	inl	(%dx)
#define OUTL	outl	(%dx)

#else	wheeze

#define ALIGN 2
#if	__STDC__
#define L_EXT(x) _##x:
#define EXT(x) _##x
#else
#define L_EXT(x) _/**/x:
#define EXT(x) _/**/x
#endif
#define	LCL(x)	x

#define LB(x,n) n
#if	__STDC__
#define LBb(x,n) n/**/b
#define LBf(x,n) n/**/f
#else
#define LBb(x,n) n/**/b
#define LBf(x,n) n/**/f
#endif

#define SVC .byte 0x9a; .long 0; .word 0x7

#define String	.ascii
#define Value	.word
#define Times(a,b) (a*b)
#define Divide(a,b) (a/b)

#define INB	inb	%dx, %al
#define OUTB	outb	%al, %dx
#define INL	inl	%dx, %eax
#define OUTL	outl	%eax, %dx

#endif	wheeze

#define data16	.byte 0x66
#define addr16	.byte 0x67



#if defined(GPROF) || defined (PROF)
#define MCOUNT		.data; LB(x, 9): .long 0; .text; lea LBb(x, 9),%edx; call mcount
#define	ENTRY(x)	.globl EXT(x); .align ALIGN; L_EXT(x) ; \
			pushl %ebp; movl %esp, %ebp; MCOUNT; popl %ebp;
#define	ASENTRY(x) 	.globl x; .align ALIGN; x: ; \
			pushl %ebp; movl %esp, %ebp; MCOUNT; popl %ebp;
#else /* defined(GPROF) || defined (PROF) */
#define MCOUNT
#define	ENTRY(x)	.globl EXT(x); .align ALIGN; L_EXT(x)
#define	ASENTRY(x)	.globl x; .align ALIGN; x:
#endif /* defined(GPROF) || defined (PROF) */

#define	Entry(x)	.globl EXT(x); .align ALIGN; L_EXT(x)
#define	DATA(x)		.globl EXT(x); .align ALIGN; L_EXT(x)

