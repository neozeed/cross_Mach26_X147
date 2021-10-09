/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)nlist.h	5.2 (Berkeley) 4/7/87
 *
 **********************************************************************
 * HISTORY
 * $Log:	nlist.h,v $
 * Revision 2.3  89/06/30  12:11:30  bww
 * 	Added function prototype declaration.
 * 	[89/06/30  11:59:13  bww]
 * 
 * Revision 2.2  89/06/26  20:20:23  bww
 * 	Merged COFF changes into 4.3-tahoe version.
 * 	[89/06/26  20:15:59  bww]
 * 
 * Revision 1.2  89/05/26  12:27:36  bww
 * 	CMU CS as of 89/05/15
 * 	[89/05/26  09:46:50  bww]
 * 
 **********************************************************************
 */

#ifdef multimax

/*
*	"5.2 SID  nlist.h: 1.2 3/19/83"
*/

/* symbol table entry structure */

struct nlist
{
	char		*n_name;	/* symbol name */
	long		n_value;	/* value of symbol */
	short		n_scnum;	/* section number */
	unsigned short	n_type;		/* type and derived type */
	char		n_sclass;	/* storage class */
	char		n_numaux;	/* number of aux. entries */
	char		n_env;		/* Symbol interpretation environ */
	char 		n_dummy;	/* Currently unused */
};

#else /* multimax */

/*
 * Format of a symbol table entry; this file is included by <a.out.h>
 * and should be used if you aren't interested the a.out header
 * or relocation information.
 */
struct	nlist {
	char	*n_name;	/* for use when in-core */
	unsigned char n_type;	/* type flag, i.e. N_TEXT etc; see below */
	char	n_other;	/* unused */
	short	n_desc;		/* see <stab.h> */
	unsigned long n_value;	/* value of this symbol (or sdb offset) */
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

#endif /* multimax */
#if __STDC__
extern int nlist(const char*, struct nlist[]);
#endif
