/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)a.out.h	5.2 (Berkeley) 4/7/87
 **********************************************************************
 * HISTORY
 * $Log:	a.out.h,v $
 * Revision 2.5  90/08/24  18:46:24  ed
 * 	Added mac2 to sun case less extra testing for sun2 binaries.
 * 	[90/08/24  18:44:51  ed]
 * 
 * Revision 2.4  90/05/03  19:59:25  bww
 * 	Added definition of N_TXTOFF for i386.
 * 	[90/05/03  19:57:49  bww]
 * 
 * Revision 2.3  90/01/17  13:00:35  bww
 * 	Included sysV/{aouthdr.h,filehdr.h,scnhdr.h} for mips.
 * 	Included all the multimax files from sysV.
 * 	From "[90/01/09            mrt]" at CMU.
 * 	[90/01/17            bww]
 * 
 * Revision 2.2  89/06/26  20:20:00  bww
 * 	Merged SUN3, IBMRT, and COFF changes into 4.3-tahoe version.
 * 	[89/06/26  20:12:27  bww]
 * 
 * 02-Nov-87  Jonathan Chew (jjc) at Carnegie-Mellon University
 *	Added N_DATADDR and N_BSSADDR for Sun.
 *
 * 21-Oct-87  Michael Jones (mbj) at Carnegie-Mellon University
 *	Included COFF definitions for Multimax.  Sigh.
 *
 * 29-May-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Added sequent changes
 *
 * 17-Nov-86  Jonathan Chew (jjc) at Carnegie-Mellon University
 *	Added changes for Sun.
 *
 * 22-Sep-86  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Added changes for IBM RT.
 *
 **********************************************************************
 */

#if defined(multimax) || defined(mips)

/*	5.2 SID a.out.h	2.4	*/


 /*		COMMON OBJECT FILE FORMAT



 	File Organization:

 	_______________________________________________    INCLUDE FILE
 	|_______________HEADER_DATA___________________|
 	|					      |
 	|	File Header			      |    "filehdr.h"
 	|.............................................|
 	|					      |
 	|	Auxilliary Header Information	      |	   "aouthdr.h"
 	|					      |
 	|_____________________________________________|
 	|					      |
 	|	".text" section header		      |	   "scnhdr.h"
 	|					      |
 	|.............................................|
 	|					      |
 	|	".data" section header		      |	      ''
 	|					      |
 	|.............................................|
 	|					      |
 	|	".bss" section header		      |	      ''
 	|					      |
 	|_____________________________________________|
 	|______________RAW_DATA_______________________|
 	|					      |
 	|	".text" section data (rounded to 4    |
 	|				bytes)	      |
 	|.............................................|
 	|					      |
 	|	".data" section data (rounded to 4    |
 	|				bytes)	      |
 	|_____________________________________________|
 	|____________RELOCATION_DATA__________________|
 	|					      |
 	|	".text" section relocation data	      |    "reloc.h"
 	|					      |
 	|.............................................|
 	|					      |
 	|	".data" section relocation data	      |       ''
 	|					      |
 	|_____________________________________________|
 	|__________LINE_NUMBER_DATA_(SDB)_____________|
 	|					      |
 	|	".text" section line numbers	      |    "linenum.h"
 	|					      |
 	|.............................................|
 	|					      |
 	|	".data" section line numbers	      |	      ''
 	|					      |
 	|_____________________________________________|
 	|________________SYMBOL_TABLE_________________|
 	|					      |
 	|	".text", ".data" and ".bss" section   |    "syms.h"
 	|	symbols				      |	   "storclass.h"
 	|					      |
 	|_____________________________________________|
	|________________STRING_TABLE_________________|
	|					      |
	|	    long symbol names		      |
	|_____________________________________________|



 		OBJECT FILE COMPONENTS

 	HEADER FILES:
 			/usr/include/filehdr.h
			/usr/include/aouthdr.h
			/usr/include/scnhdr.h
			/usr/include/reloc.h
			/usr/include/linenum.h
			/usr/include/syms.h
			/usr/include/storclass.h

	STANDARD FILE:
			/usr/include/a.out.h    "object file" 
   */
#include <sysV/aouthdr.h>
#include <sysV/filehdr.h>
#include <sysV/scnhdr.h>
#endif	/* defined(multimax) || defined(mips) */

#ifdef	multimax 
#include <nlist.h>	/* included for mmax */

#include <sysV/reloc.h>
#include <sysV/linenum.h>
#include <sysV/syms.h>	/* includes storclass.h */

#else	/* multimax */

/*
 * Definitions of the a.out header
 * and magic numbers are shared with
 * the kernel.
 */
#ifdef	balance
#include <sys/param.h>
#include <sys/vmparam.h>
#endif	/* balance */
#include <sys/exec.h>

/*
 * Macros which take exec structures as arguments and tell whether
 * the file has a reasonable magic number or offsets to text|symbols|strings.
 */
#ifdef	balance
/* defined later */
#else	/* balance */
#define	N_BADMAG(x) \
    (((x).a_magic)!=OMAGIC && ((x).a_magic)!=NMAGIC && ((x).a_magic)!=ZMAGIC)
#endif	/* balance */

#ifdef ibmrt
#define	N_TXTOFF(x) \
	((x).a_magic==ZMAGIC ? 2048 : sizeof (struct exec))
#endif
#if defined(sun) || defined(mac2)
#define	PAGSIZ		0x2000
#define	SEGSIZ		0x20000
#ifdef sun
#define	OLD_PAGSIZ	0x800	/* THIS DISAPPEARS IN RELEASE 4.0 */
#define	OLD_SEGSIZ	0x8000	/* THIS DISAPPEARS IN RELEASE 4.0 */

#define	N_PAGSIZ(x) \
	((x).a_machtype == M_OLDSUN2? OLD_PAGSIZ : PAGSIZ)
#define	N_SEGSIZ(x) \
	((x).a_machtype == M_OLDSUN2? OLD_SEGSIZ : SEGSIZ)

#define	N_TXTOFF(x) \
	/* text segment */ \
	( (x).a_machtype == M_OLDSUN2 \
	? ((x).a_magic==ZMAGIC ? N_PAGSIZ(x) : sizeof (struct exec)) \
	: ((x).a_magic==ZMAGIC ? 0 : sizeof (struct exec)) )
#define N_TXTADDR(x) \
	((x).a_machtype == M_OLDSUN2? N_SEGSIZ(x) : N_PAGSIZ(x))
#else	/* sun */
#define N_PAGSIZ(x)	(PAGSIZ)
#define N_SEGSIZ(x)	(SEGSIZ)

#define	N_TXTOFF(x) \
	((x).a_magic==ZMAGIC ? 0 : sizeof (struct exec))
#define N_TXTADDR(x)	N_PAGSIZ(x)
#endif	/* sun */
#define N_DATADDR(x) \
	(((x).a_magic==OMAGIC)? (N_TXTADDR(x)+(x).a_text) \
	: (N_SEGSIZ(x)+((N_TXTADDR(x)+(x).a_text-1) & ~(N_SEGSIZ(x)-1))))

#define N_BSSADDR(x)  (N_DATADDR(x)+(x).a_data)
#endif	/* sun || mac2 */
#ifdef	i386
#define	N_TXTOFF(x)	(sizeof (struct exec))
#endif	/* i386 */
#ifdef vax
#define	N_TXTOFF(x) \
	((x).a_magic==ZMAGIC ? 1024 : sizeof (struct exec))
#endif
#ifdef	balance
/*
 * Macros to determine validity of object file and offsets in a file.
 *
 * In an executable a.out, a_magic determines how position in the file
 * relates to execution address: ZMAGIC and XMAGIC place position 0 in the
 * file at address EXECPGRND in memory; SMAGIC uses same file and execution
 * addresses.  a_text encodes the virtual (execution) size of the text,
 * not necessarily the size in the file.  Header is included in the
 * text.  N_ADDRADJ() encodes this.
 *
 * In a non-executable a.out (OMAGIC), text starts after header.
 *
 * N_MINSIZ(x) gives minimum size for legal executable.
 */

#define	EXECPGRND	(LOWPAGES*NBPG)

#define	N_BADMAG(x) \
    (((x).a_magic)!=OMAGIC && ((x).a_magic)!=ZMAGIC && \
     ((x).a_magic)!=XMAGIC && ((x).a_magic)!=SMAGIC)

#define N_ADDRADJ(x) \
	(((x).a_magic == ZMAGIC || (x).a_magic == XMAGIC) ? EXECPGRND : 0)

#define	N_TXTOFF(x)	((x).a_magic == OMAGIC ? sizeof (struct exec) : 0)
#define N_DATAOFF(x)	(N_TXTOFF(x) + (x).a_text - N_ADDRADJ(x))
#define N_SHDATAOFF(x)	(N_DATAOFF(x) + (x).a_data)
#define N_TROFF(x)	(N_SHDATAOFF(x) + (x).a_shdata)
#define N_DROFF(x)	(N_TROFF(x) + (x).a_trsize)
#define N_SHDROFF(x)	(N_DROFF(x) + (x).a_drsize)
#define N_SYMOFF(x)	(N_SHDROFF(x) + (x).a_shdrsize)
#define N_MINSIZ(x)	N_TROFF(x)
#else	/* balance */
#define N_SYMOFF(x) \
	(N_TXTOFF(x) + (x).a_text+(x).a_data + (x).a_trsize+(x).a_drsize)
#endif	/* balance */
#define	N_STROFF(x) \
	(N_SYMOFF(x) + (x).a_syms)

/*
 * Format of a relocation datum.
 */
struct relocation_info {
	int	r_address;	/* address which is relocated */
unsigned int	r_symbolnum:24,	/* local symbol ordinal */
		r_pcrel:1, 	/* was relocated pc relative already */
		r_length:2,	/* 0=byte, 1=word, 2=long */
		r_extern:1,	/* does not include value of sym referenced */
#ifdef	balance
		r_bsr:1,	 	/* this is an entry for a bsr dest. */
		r_disp:1,	 	/* the value is a displacemnt */
		:2;		/* nothing, yet */
#else	/* balance */
		:4;		/* nothing, yet */
#endif	/* balance */
};

/*
 * Format of a symbol table entry; this file is included by <a.out.h>
 * and should be used if you aren't interested the a.out header
 * or relocation information.
 */
struct	nlist {
	union {
		char	*n_name;	/* for use when in-core */
		long	n_strx;		/* index into file string table */
	} n_un;
unsigned char	n_type;		/* type flag, i.e. N_TEXT etc; see below */
	char	n_other;	/* unused */
	short	n_desc;		/* see <stab.h> */
unsigned long	n_value;	/* value of this symbol (or sdb offset) */
};
#define	n_hash	n_desc		/* used internally by ld */

/*
 * Simple values for n_type.
 */
#define	N_UNDF	0x0		/* undefined */
#define	N_ABS	0x2		/* absolute */
#define	N_TEXT	0x4		/* text */
#define	N_DATA	0x6		/* data */
#define	N_BSS	0x8		/* bss */
#ifdef	balance
#define	N_COMM		0x0a		/* common (internal to ld) */
#define	N_FN		0x0c		/* file-name */

/*
 * Be careful if you change these definitions; N_SHARED is used
 * as an "attribute" for efficiency in some tools (eg, ld).
 */
#define	N_SHARED	0x10		/* shared N_UNDF, N_DATA, N_BSS */
#define	N_SHUNDF	(N_SHARED|N_UNDF)
#define	N_SHDATA	(N_SHARED|N_DATA)
#define	N_SHBSS		(N_SHARED|N_BSS)
#define	N_SHCOMM	(N_SHARED|N_COMM)
#else	/* balance */
#define	N_COMM	0x12		/* common (internal to ld) */
#define	N_FN	0x1e		/* file name symbol */
#endif	/* balance */

#define	N_EXT	01		/* external bit, or'ed in */
#define	N_TYPE	0x1e		/* mask for all the type bits */

/*
 * Sdb entries have some of the N_STAB bits set.
 * These are given in <stab.h>
 */
#define	N_STAB	0xe0		/* if any of these bits set, a SDB entry */

/*
 * Format for namelist values.
 */
#define	N_FORMAT	"%08x"

#endif	/* multimax */
