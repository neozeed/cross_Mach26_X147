/*
 * Copyright (c) 1990 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND CARNEGIE MELLON UNIVERSITY
 * DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.  IN NO EVENT
 * SHALL CARNEGIE MELLON UNIVERSITY BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF
 * CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Users of this software agree to return to Carnegie Mellon any
 * improvements or extensions that they make and grant Carnegie the
 * rights to redistribute these changes.
 *
 * Export of this software is permitted only after complying with the
 * regulations of the U.S. Deptartment of Commerce relating to the
 * Export of Technical Data.
 */
/*
 * Standard C macros
 *
 **********************************************************************
 * HISTORY
 * $Log:	c.h,v $
 * Revision 1.3  90/12/19  20:03:52  bww
 * 	Add copyright/disclaimer for distribution.
 * 	From "[90/12/12  20:55:27  mja]" ar CMU.
 * 	[90/12/19  20:01:32  bww]
 * 
 * 02-Feb-86  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Added check to allow multiple or recursive inclusion of this
 *	file.  Added bool enum from machine/types.h for regular users
 *	that want a real boolean type.
 *
 * 29-Dec-85  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Also change spacing of MAX and MIN to coincide with that of
 *	sys/param.h.
 *
 * 19-Nov-85  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Changed the number of tabs between TRUE, FALSE and their
 *	respective values to match those in sys/types.h.
 *
 * 17-Dec-84  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Only define TRUE and FALSE if not defined.  Added caseE macro
 *	for using enumerated types in switch statements.
 *
 * 23-Apr-81  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added "sizeofS" and "sizeofA" macros which expand to the size
 *	of a string constant and array respectively.
 *
 **********************************************************************
 */

#ifndef	_C_INCLUDE_
#define	_C_INCLUDE_

#define ABS(x) ((x)>=0?(x):-(x))
#define	MIN(a,b) (((a)<(b))?(a):(b))
#define	MAX(a,b) (((a)>(b))?(a):(b))

#ifndef	FALSE
#define FALSE	0
#endif	FALSE
#ifndef	TRUE
#define TRUE	1
#endif	TRUE

#define	CERROR		(-1)

#ifndef	bool
typedef enum	{ false = 0, true = 1 } bool;
#endif	bool

#define	sizeofS(string)	(sizeof(string) - 1)
#define sizeofA(array)	(sizeof(array)/sizeof(array[0]))

#define caseE(enum_type)	case (int)(enum_type)

#endif	_C_INCLUDE_
