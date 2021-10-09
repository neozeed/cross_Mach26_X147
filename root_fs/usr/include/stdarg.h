/*
 **********************************************************************
 * HISTORY
 * $Log:	stdarg.h,v $
 * Revision 1.3  89/12/24  16:52:20  bww
 * 	Corrected definition of va_start().  Enabled support
 * 	for BYTE_MSF machines, and included support for PMAX.
 * 	Removed declaration for _doprnt().  Utilized #error.
 * 	[89/12/24  16:51:32  bww]
 * 
 * Revision 1.2  89/05/26  12:29:53  bww
 * 	CMU CS as of 89/05/15
 * 	[89/05/26  09:46:50  bww]
 * 
 * Revision 2.3  89/01/20  15:43:52  gm0w
 * 	Cleaned up module a bit.
 * 	[88/12/27            gm0w]
 * 
 * Revision 2.2  88/12/14  23:34:32  mja
 * 	Created.
 * 	[88/01/06            jjk]
 * 
 **********************************************************************
 */

/*
 *  This is the ANSI C version of varargs.h.  If you are using
 *  a non-ANSI compiler you should include <varargs.h> instead.
 */
#if !__STDC__
#error You MUST have an ANSI compatible compiler to use stdarg.h
#endif

#ifndef _STDARG_H_
#define _STDARG_H_ 1

/*
 * USAGE:
 *	f( arg-declarations, ... ) {
 *		va_list ap;
 *		va_start(ap, parmN);	// parmN == last named arg
 *		// ...
 *		type arg = va_arg(ap, type);
 *		// ...
 *		va_end(ap);
 *	}
 */

typedef char *va_list;
#if	mips
/* PMAX pushes floats on the stack only on double longword boundaries */
# define va_start(list,parmN) list = ((char *)(&parmN) +\
				(sizeof(parmN) > 4 ? (2*8 - 1) & -8 \
						   : (2*4 - 1) & -4))
#else
# define va_start(list,parmN) list = ((char *)(&parmN) +\
				(sizeof(parmN)+3)&(-4))
#endif
# define va_end(list)
#if	BYTE_MSF
# define va_arg(list,mode) ((mode *)((list += (sizeof(mode)+3)&(-4))\
		-((sizeof(mode)<4)?sizeof(mode):(sizeof(mode)+3)&(-4))))[0]
#else	/* BYTE_MSF */
#if	mips
/* PMAX pushes floats on the stack only on double longword boundaries */
# define va_arg(list,mode) ((mode *)((list = \
        (char *) (sizeof(mode) > 4 ? ((int)list + 2*8 - 1) & -8 \
                                   : ((int)list + 2*4 - 1) & -4))\
		-((sizeof(mode)+3)&(-4))))[0]
#else
# define va_arg(list,mode) ((mode *)((list += (sizeof(mode)+3)&(-4))\
		-((sizeof(mode)+3)&(-4))))[0]
#endif
#endif	/* BYTE_MSF */

#include <stdio.h>
extern int vprintf(const char *, va_list);
extern int vfprintf(FILE *, const char *, va_list);
extern int vsprintf(char *, const char *, va_list);
#endif	/* not _STDARG_H_ */
