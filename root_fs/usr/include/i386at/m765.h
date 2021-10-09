/*
 * HISTORY
 * $Log:	m765.h,v $
 * Revision 1.1  91/05/09  13:43:23  jaap
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
 * $CMU-Log:	m765.h,v $
 * Revision 1.6.1.5  90/11/27  13:44:40  rvb
 * 	Synched 2.5 & 3.0 at I386q (r1.6.1.5) & XMK35 (r2.4)
 * 	[90/11/15            rvb]
 * 
 * Revision 1.6.1.3  90/07/27  11:26:42  rvb
 * 	Fix Intel Copyright as per B. Davies authorization.
 * 	[90/07/27            rvb]
 * 
 * Revision 2.3  90/08/27  22:01:00  dbg
 * 	Flush ushort.
 * 	[90/07/17            dbg]
 * 
 * Revision 2.2  90/05/03  15:45:27  dbg
 * 	Change for pure kernel.
 * 	[90/04/19            dbg]
 * 
 * Revision 1.6.1.2  90/01/08  13:30:22  rvb
 * 	Add Intel copyright.
 * 	[90/01/08            rvb]
 * 
 * Revision 1.6.1.1  89/10/22  11:34:43  rvb
 * 	Received from Intel October 5, 1989.
 * 	[89/10/13            rvb]
 * 
 * Revision 1.6  89/09/25  12:27:00  rvb
 * 	Flush B_VERFIY and B_FORMAT
 * 	[89/09/23            rvb]
 * 
 * Revision 1.5  89/09/20  17:29:17  rvb
 * 	It bothers me that we are changing a constant here so that
 * 	25 Mhz machines will loop for a full 1msec.  There has to be
 * 	a way to set cpuspeed once we find out the kind of machine and
 * 	clock speed.
 * 	[89/09/20            rvb]
 * 
 * Revision 1.4  89/03/09  20:07:10  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/26  12:40:12  gm0w
 * 	Changes for cleanup.
 * 
 */
 
/*
  Copyright 1988, 1989 by Intel Corporation, Santa Clara, California.

		All Rights Reserved

Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appears in all
copies and that both the copyright notice and this permission notice
appear in supporting documentation, and that the name of Intel
not be used in advertising or publicity pertaining to distribution
of the software without specific, written prior permission.

INTEL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
IN NO EVENT SHALL INTEL BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*	Copyright (c) 1987, 1988 TOSHIBA Corp.		*/
/*		All Rights Reserved			*/

#ident  "@(#)m765.h	1.13 - 88/02/17"

/*******************************************************************
 *
 *	 Toshiba Floppy Driver for UNIX System V R3
 *
 *					June 21, 1988
 *
 *	Intended Drive Units:
 *		Worldwide - Model No. ND-356  3.5" unformatted 2MB/1MB
 *		UNIX Media Type Name: 2HD512/2DD512/2D512/1D512.
 *
 *		In Japan Only - Model No. ND-355  3.5" unformatted 1.6MB/1MB
 *		UNIX Media Type Name: 2HC1024/2HC512/2HC256/2DD512/2D512/1D512.
 *
 *		Worldwide - Model No. ND-04DT-A  5.25" unformatted 500 KB
 *		UNIX Media Type Name: 2D512/1D512.
 *
 *		In Japan Only - Model No. ND-08DE  5.25" unformatted 1.6MB/1MB
 *		UNIX Media Type Name: 2HC1024/2HC512/2HC256/2DD512/2D512/1D512.
 *
 *		Use with other devices may require modification.
 *
 *	Notes:
 *		For further detail regarding drive units contact
 *		Toshiba America,Inc. Disk Products Division,
 *		Irvine, CA (714) 583-3000.
 *
 *******************************************************************/


/*
 *	fdcmd.c_rbmtr
 *
 *		 |--+--+--+--+--+--+--+--|
 *		 |  |  |  |  |  |  |  |  |
 *		 |--+--+--+--+--+--+--+--|
 *			^  ^	    ^  ^
 *			|  |	    |  |--- unit0 motor on flag
 *			|  |	    |------ unit1 motor on flag
 *			|  |--------------- unit0 recalibrate flag
 *			|------------------ unit1 recalibrate flag
 */
#define MTRMASK		0x003		/* mask motor_flag for get status */
#define MTRRST		0x0fc		/* reset motor_flag data */
#define RBSHIFT		0x004		/* shift count for recalibrate data */
#define RBRST		0x0cf		/* reset recalibrate data */

/*
 *	fdcmd.c_intr
 *
 *				   |--+--+--+--+--+--+--+--|
 *				   |  |  |  |  |  |  |  |  |
 *				   |--+--+--+--+--+--+--+--|
 *				     ^  ^  ^  ^  ^  ^  ^  ^
 *			 reserved  --+  |  |  |  |  |  |  +--- read/write flag
 *			 reserved  -----+  |  |  |  |  +------ seek flag
 *			 reserved  --------+  |  |  +------ seek flag(for retry)
 * recalibrate/seek flag(for open) -----------+  +--------- recalibrate flag
 */
#define RWFLAG		0x001
#define SKFLAG		0x002
#define SKEFLAG		0x004
#define RBFLAG		0x008
#define WUPFLAG		0x010
#define CMDRST		0x000	

/*
 *	fddrtab.dr_type
 *
 *	+---+---+---+---+---+---+---+---+
 *	|   |   |   |   |   |   |   |   |
 *	+---+---+---+---+---+---+---+---+
 *	  ^   ^   ^   ^   ^
 *	  |   |   |   |   |---------- rapid seek flag
 *	  |---|   |   |			0: normal seek
 *	    |	  |   |			1: rapid seek
 *	    |	  |   |-------------- detect format
 *	    |	  |			0: no detect
 *	    |	  |			1: format type OK
 *	    |	  |------------------ 40 or 80 cylinder(for 2hc/2dd drive)
 *	    |				0: 80 cylinder
 *	    |				1: 40 cylinder
 *	    |------------------------ transfer rate(for read/write/format)
 *					00: 500kbps  10: 250kbps
 *					01: 300kbps  11: reserved
 */
#define OKTYPE		0x10		/* media change flag */
#define DOUBLE		0x20		/* double/single step change */
#define RAPID		0x08		/* rapid seek flag */
#define RPSEEK		0x00		/* rapid seek */
#define NMSEEK		0x80		/* normal seek */
#define RATEMASK	0xc0		/* transfer parameter mask data */

/*
 *	device number
 *
 *	 15		10  9  8  7		       0
 *	+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *	| 0  0  0  0  0  0  0  1| 0|  |  |  |		|
 *	+-----------+-----+-----+--+--+--+--+-----------+
 *	  ^		       ^  ^  ^  ^  ^  ^        ^
 *	  |____________________|  |__|  |__|  |________|
 *		    |		   |	 |	  |
 *		    |		   |	 |	  |-  media type
 *		major number	   |	 |	0:auto type 5:2dd512(9sector)
 *				   |	 |	1:2hd512    6:2dd512(8sector)
 *		unit number -------|	 |	2:2hc256    7:2d512 (9sector)
 *					 |	3:2hc512    8:2d512 (8sector)
 *		partition number --------|	4:2hc1024 [ 9:1d512 (9sector)]
 *							  [10:1d512 (8sector)]
 */
#define UNIT(dev)	(((dev) >> 6) & 3)	/* get unit number */
#define PARTITION(dev)	(((dev) >> 4) & 3)	/* get partition status */
#define MEDIATYPE(dev)	((dev) & 0xf)		/* get media type */


/*****************************************************************************

		wait time / timeout count

 *****************************************************************************/
#define MSEC		0x1000		/* 1 msec loop count */
#define STSCHKCNT	0x2800		/* For check status */
#define ITOUT		HZ*5		/* interrupt timeout count */
#define TOUT		HZ/4		/* media type check timeout count */
#define MTRSTOP		HZ*2		/* motor off time */
#define SEEKWAIT	HZ/100*3	/* head_lock time */

/******************************************************************************

		define for FDC

 ******************************************************************************/
/* FDC register */
#define CTRLREG		0x03f2		/* controle register */
#define STSREG		0x03f4		/* status register */
#define DATAREG		0x03f5		/* data register */
#define VFOREG		0x03f7		/* vfo register */

/* CTRLREG flags */
#define HEADLOAD	0x01
#define FDC_RST		0x04
#define MTR_ON		0x04
#define DMAREQ		0x08

/* status for command_out */
#define FD_OSTS		0x00		/* For output check */
#define FD_ISTS		0x40		/* For input check */
#define DTOCPU		0x40
#define DATAOK		0x80

/* Command for FDC */
#define SPCCMD		0x03		/* Specify command */
#define SDSCMD		0x04		/* sense device status */
#define RBCMD		0x07		/* Recalibrate command */
#define SISCMD		0x08		/* Sense interrupt status command */
#define SEEKCMD		0x0f		/* seek command */
#define RDM		0xe6		/* FDC READ command */
#define RDMV		0x42e6		/* VERIFY READ command */
#define WTM		0xc5		/* FDC WRITE command */
#define FMTM		0x4d		/* FDC FORMAT command */
#define FMTDATA		0x5e		/* format data */

/* check value */
#define TRACK0		0x10
#define RWLEVEL		0x80		/* interrupt level */
#define OPENBIT		0x80		/* VFO check define */
#define GETFDSTS	0xb4		/* kb ioctl */
#define BYTEMASK	0xff
#define WORDMASK	0xffff
#define SEG1		0x10000

/* FDC error code define */
#define OK		0x00
#define ERROR		0xff
#define EBBHARD		128
#define EBBSOFT		129
#define ST0AT		0x40
#define ST0IC		0x80
#define ST0OK		0xc0
#define ADDRERR		0x01
#define WTPRT		0x02
#define NOREC		0x03
#define OVERRUN		0x04
#define CRCERR		0x05
#define FDCERR		0x06
#define ILLFMT		0x07
#define TIMEOUT		0x08
#define DOORERR		0x09
#define ILLINT		0x0a

/******************************************************************************

		define for DMA

 ******************************************************************************/
/* DMA register */
#define DMACMD1		0x08		/* DMA #1 command register	*/
#define DMAMSK1		0x0f		/* DMA #1 all mask register	*/
#define DMACMD2		0xd0		/* DMA #2 command register	*/
#define DMASMSK		0xd4		/* DMA #2 single mask register	*/
#define DMAMOD2		0xd6		/* DMA #2 mode register		*/
#define DMAMSK2		0xde		/* DMA #2 all mask register	*/
#define DMADATA		0x00		/* DMA #1 command data		*/
#define DMABPFF		0x0c
#define DMAMODE		0x0b
#define DMAADDR		0x04
#define DMAPAGE		0x81
#define DMACNT		0x05
#define DMAMSK		0x0a

#define DMADONE		0
#define DMABUSY		1

/* dma set data */
#define DMARD		0x46		/* DMA read mode		*/
#define DMAWT		0x4a		/* DMA	write mode		*/
#define DMAVRF		0x42		/* DMA verify mode		*/

#define DMADATA0	0x00		/* DMA #2 all mask data		*/
#define DMADATA1	0x0b		/* DMA #1 all mask data		*/
#define DMADATA2	0x00		/* DMA #2 command data		*/
#define DMADATA3	0x00		/* DMA #2 single mask data	*/
#define DMADATA4	0xc0		/* DMA #2 mode data		*/
#define DMADATA5	0x0e		/* DMA #2 all mask data		*/
#define CHANEL2		0x02

/******************************************************************************

		etc. define

 ******************************************************************************/
#define SPL		spl4			/* for driver mutex */
#define MAXUNIT		2			/* Max unit number */

/* dr_cmostype */
#define EXT2D	0x1	/* 5-1/4" Double-Sided */
#define EXT2HD	0x2	/* 5-1/4" High capacity */
#define EXT2DD	0x3	/* 3-1/2" */

/* fdcmd.c_stsflag	*/
#define MTRFLAG	0x01
#define MTROFF	0x02
#define INTROUT	0x04

/* fdcmd.c_devflag (media check flag . etc.) */
#define FDMCHK		0x01
#define FDWAIT		0x02
#define STRCHK		0x04
#define STRWAIT		0x08

/* fdcmd.c_dcount */
#define FDCCNT	9	/* Command table for read/write/format (FDC) */
#define RWCNT	9	/* Read/Write command count */
#define FMTCNT	6	/* format command count */

struct	fdcmd {
	int	c_rbmtr;		/* moter & rcalibrate flag */
	int	c_intr;			/* intr flag */
	int	c_stsflag;		/* moter flag */
	int	c_devflag;		/* device status */
	int	c_dcount;		/* Read/Write/Format data count */
	int	c_rwdata[FDCCNT];	/* Read/Write/Format cmd (FDC) */
	int	c_saddr;		/* cmd seek address */
};

struct	fdubuf {
	struct buf *buf_queue;		/* head of I/O queue (b_forw) */
	int	buf_seekaddr;		/* cylinder address */
};
/* fdmbuf.b_rberr/fdmbuf.b_seekerr/fdmbuf.b_rwerr */
#define MEDIARD		0x01
#define MEDIASEEK	0x01
#define SRETRY		0x03
#define MRETRY		0x30
#define LRETRY		0x300
#define SRMASK		0x0f
#define MRMASK		0xf0
#define RMRMASK		0xff0
#define LRMASK		0xf00
#define MINC		0x10
#define LINC		0x100

/* fdmbuf.b_active[] Values of buffer-header b_active,
 * used for mutual-exclusion of opens and other I/O requests. */
#define FD_IO_IDLE	0		/* idle -- anything goes */
#define FD_IO_BUSY	0x01		/* something going on */
#define FD_IO_WAIT	0x02		/* waiting for controller to be idle */

struct	fdmbuf {
	char	b_active[MAXUNIT];	/* busy flag			*/
	char	b_unit;			/* for change unit		*/
	char	b_dmabuf;		/* using buffer for DMA		*/
	short	b_rberr;		/* rb error count (for recovery) */
	short	b_seekerr;		/* seek error count (for recovery) */
	short	b_rwerr;		/* r/w error count (for recovery) */
	short	b_status;		/* error status			*/
	struct buf	*b_buf;		/* set bp address		*/
	caddr_t b_xferaddr;		/* trasfer address		*/
	u_int	b_xfercount;		/* total transfer count		*/
	u_int	b_xferdma;		/* dma transfer count		*/
	daddr_t	b_sector;		/* read/write sector		*/
	struct fdcmd b_cmd;		/* set command table address	*/
};

#define FMTID	4
struct fmttbl {
	u_char cyl;
	u_char head;
	u_char sector;
	u_char s_type;
};

struct	fdpart {
	u_short p_fsec;		/* start sector number		*/
	u_short p_nsec;		/* disk length (sector count)	*/
};

#define FORMMAX	0x0e	/* support mediatype count */
struct	fddrtab {
	u_short	dr_ncyl;	/* cylinder count		*/
	char	dr_nrhead;	/* removable heads		*/
	char	dr_nsec;	/* sector per track		*/
	u_short	dr_secsiz;	/* sector_size (byte)		*/
	u_short	dr_spc;		/* actual sectors/cylinder	*/
	struct fdpart *dr_part;	/* start sector, disk length	*/
	char	dr_type;	/* media type			*/
	char	dr_rwgpl;	/* Read / Write Gap length	*/
	char	dr_fgpl;	/* Format Gap length		*/
	char	dr_cmostype;	/* media type from CMOS		*/
};

struct	fdcmn {
	char	f_srthut;	/* Step rate, Head unload time	*/
	char	f_hltnd;	/* Head load time, Non DMA mode */
	char	f_hst;		/* Head Setting time		*/
	char	f_dtl;		/* Data length			*/
};

struct	fdtree {
	struct fddrtab *fd_parm; /* parameter address	*/
	int	cylno;		/* read cylnder number	*/
	short	headno;		/*	head number	*/
	short	secno;		/*	sector number	*/
	struct	fdtree *fd_yes; /* next tree		*/
	struct	fdtree *fd_no;	/* next tree		*/
};


#define HZ		100		/* 100 ticks/second of the clock */

#if	__STDC__
#define V_SETPARMS	_IOW('v',14,long)	/* Set drive type */
#else
#define V_SETPARMS	_IOW(v,14,long)		/* Set drive type */
#endif

#ifdef	MACH_KERNEL
#define	PZERO		25
#define	PRIBIO		20

#define	B_VERIFY	IO_SPARE_START
#define	B_FORMAT	(IO_SPARE_START << 1)

#define	b_pfcent	io_mode

#else	MACH_KERNEL
#define B_VERIFY	B_MD1		/* Special "struct buf" flags for */
#define B_FORMAT	B_MD2		/*	format and verify operations */
#endif	MACH_KERNEL
