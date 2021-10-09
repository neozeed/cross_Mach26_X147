/*	varargs.h	4.1	83/05/03	*/
/*
 **********************************************************************
 * HISTORY
 * $Log:	varargs.h,v $
 * Revision 2.4  90/03/01  15:54:56  bww
 * 	Defined va_alist to be __builtin_va_alist on SPARC.
 * 	From "[90/02/01            jjc]" at CMU.
 * 	[90/03/01            bww]
 * 
 * Revision 2.3  89/08/14  13:44:08  bww
 * 	Add definitions for PMAX (mips BYTE_LSF).
 * 	From "[89/07/03            mja]" at CMU.
 * 	[89/08/14            bww]
 * 
 * Revision 2.2  89/06/26  20:20:43  bww
 * 	Merged IBMRT and "BYTE_MSF" changes into 4.3-tahoe version.
 * 	[89/06/26  20:18:38  bww]
 * 
 * 03-Dec-86  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Changed conditional to BYTE_MSF.
 *
 * 20-Nov-86  Jonathan Chew (jjc) at Carnegie-Mellon University
 *	Added definitions for Sun.
 *
 * 22-Sep-86  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Added changes for IBM RT.
 *
 **********************************************************************
 */

typedef char *va_list;
#if	ibmrt
# define va_alist va_alist1, va_alist2, va_alist3, va_alist4
# define va_dcl int va_alist1, va_alist2, va_alist3, va_alist4;
# define va_start(list) list = (char *) &va_alist1
#else	/* ibmrt */
#if	sparc
# define va_alist __builtin_va_alist
#endif	/* sparc */
# define va_dcl int va_alist;
# define va_start(list) list = (char *) &va_alist
#endif	/* ibmrt */
# define va_end(list)
#if	BYTE_MSF
# define va_arg(list,mode) ((mode *)((list += (sizeof(mode)+3)&(-4))\
		-((sizeof(mode)<4)?sizeof(mode):(sizeof(mode)+3)&(-4))))[0]
#else	/* BYTE_MSF */
#if	mips
/* PMAX pushes floats on the stack only on double longword boundaries */
#define va_arg(list, mode) ((mode *)((list = \
        (char *) (sizeof(mode) > 4 ? ((int)list + 2*8 - 1) & -8 \
                                   : ((int)list + 2*4 - 1) & -4))\
		-((sizeof(mode)+3)&(-4))))[0]
#else	/* mips */
# define va_arg(list,mode) ((mode *)((list += (sizeof(mode)+3)&(-4))\
		-((sizeof(mode)+3)&(-4))))[0]
#endif	/* mips */
#endif	/* BYTE_MSF */
