/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)stab.h	5.1 (Berkeley) 5/30/85
 */

/* IF YOU ADD DEFINITIONS, ADD THEM TO nm.c as well */
/*
 * This file gives definitions supplementing <a.out.h>
 * for permanent symbol table entries.
 * These must have one of the N_STAB bits on,
 * and are subject to relocation according to the masks in <a.out.h>.
 */
/*
 **********************************************************************
 * HISTORY
 * $Log:	stab.h,v $
 * Revision 2.3  90/08/26  13:38:00  bww
 * 	Added support for mac2.
 * 	[90/08/26  13:37:28  bww]
 * 
 * Revision 2.2  89/06/26  20:20:37  bww
 * 	Merged SUN3 and Sequent changes into 4.3-tahoe version.
 * 	[89/06/26  20:17:54  bww]
 * 
 * 29-May-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Added sequent shared symbols.
 *
 * 15-Dec-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Created from Sun's version of stab.h.
 *
 **********************************************************************
 */
/*
 * for symbolic debugger, sdb(1):
 */
#define	N_GSYM	0x20		/* global symbol: name,,0,type,0 */
#define	N_FNAME	0x22		/* procedure name (f77 kludge): name,,0 */
#define	N_FUN	0x24		/* procedure: name,,0,linenumber,address */
#define	N_STSYM	0x26		/* static symbol: name,,0,type,address */
#define	N_LCSYM	0x28		/* .lcomm symbol: name,,0,type,address */
#ifdef	balance
#define	N_SSTSYM 0x36		/* shared static symbol: name,,0,type,address */
#define	N_SLCSYM 0x38		/* shared .lcomm symbol: name,,0,type,address */
#endif	/* balance */
#define	N_RSYM	0x40		/* register sym: name,,0,type,register */
#define	N_SLINE	0x44		/* src line: 0,,0,linenumber,address */
#define	N_SSYM	0x60		/* structure elt: name,,0,type,struct_offset */
#define	N_SO	0x64		/* source file name: name,,0,0,address */
#define	N_LSYM	0x80		/* local sym: name,,0,type,offset */
#define	N_SOL	0x84		/* #included file name: name,,0,0,address */
#define	N_PSYM	0xa0		/* parameter: name,,0,type,offset */
#define	N_ENTRY	0xa4		/* alternate entry: name,linenumber,address */
#define	N_LBRAC	0xc0		/* left bracket: 0,,0,nesting level,address */
#define	N_RBRAC	0xe0		/* right bracket: 0,,0,nesting level,address */
#define	N_BCOMM	0xe2		/* begin common: name,, */
#define	N_ECOMM	0xe4		/* end common: name,, */
#define	N_ECOML	0xe8		/* end common (local name): ,,address */
#define	N_LENG	0xfe		/* second stab entry with length information */

/*
 * for the berkeley pascal compiler, pc(1):
 */
#define	N_PC	0x30		/* global pascal symbol: name,,0,subtype,line */

#if defined(sun) || defined(mac2)
#define	N_MAIN	0x2a		/* name of main routine : name,,0,0,0 */
#define	N_BINCL	0x82		/* header file: name,,0,0,0 */
#define	N_EINCL	0xa2		/* end of include file */
#define	N_EXCL	0xc2		/* excluded include file */
#endif	/* sun || mac2 */
