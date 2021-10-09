/*
 * HISTORY
 * $Log:	hdreg.h,v $
 * Revision 1.1  91/05/09  13:41:34  jaap
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
 * $CMU-Log:	hdreg.h,v $
 * Revision 1.5.1.5  90/11/27  13:42:14  rvb
 * 	Synched 2.5 & 3.0 at I386q (r1.5.1.5) & XMK35 (r2.4)
 * 	[90/11/15            rvb]
 * 
 * Revision 1.5.1.4  90/07/27  11:25:57  rvb
 * 	Fix Intel Copyright as per B. Davies authorization.
 * 	[90/07/27            rvb]
 * 
 * Revision 2.2  90/05/03  15:42:24  dbg
 * 	First checkin.
 * 
 * Revision 1.5.1.3  90/03/29  18:59:52  rvb
 * 	Added some more ERROR_ codes.
 * 	[90/03/28            rvb]
 * 
 * Revision 1.5.1.2  90/01/08  13:31:35  rvb
 * 	Add Intel copyright.
 * 	[90/01/08            rvb]
 * 
 * Revision 1.5.1.1  89/12/21  18:00:06  rvb
 * 	Changes from Eugene:
 * 	  1) ERROR_BBD, ERROR_ECC, MAX_RETRIES, MAX_ALTBUFS
 * 	  2) field rename in hh:
 * 		controller_busy, retry_count, restore_request
 * 	[89/12/07            rvb]
 * 
 * Revision 1.5  89/09/09  15:22:00  rvb
 * 	hd.h -> hdreg.h; hd.h is now use for configuration.
 * 	[89/09/09            rvb]
 * 
 * Revision 1.4  89/07/17  10:40:31  rvb
 * 	Olivetti Changes to X79 upto 5/9/89:
 * 	[89/07/11            rvb]
 * 
 * Revision 1.3  89/02/26  12:36:47  gm0w
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

#define FIXED_DISK_REG			0x3f6
#define MORETHAN8HEADS			0x008
#define EIGHTHEADSORLESS		0x000
#define FIXEDBITS			0x0a0

#define PORT_DATA			0x1f0
#define PORT_ERROR			0x1f1
#define PORT_PRECOMP			0x1f1
#define PORT_NSECTOR			0x1f2
#define PORT_SECTOR			0x1f3
#define PORT_CYLINDERLOWBYTE		0x1f4
#define PORT_CYLINDERHIBYTE		0x1f5
#define PORT_DRIVE_HEADREGISTER		0x1f6
#define PORT_STATUS			0x1f7
#define PORT_COMMAND			0x1f7

#define STAT_BUSY			0x080
#define STAT_READY			0x040
#define STAT_WRITEFAULT			0x020
#define STAT_SEEKDONE			0x010
#define STAT_DATAREQUEST		0x008
#define STAT_ECC			0x004
#define STAT_INDEX			0x002
#define STAT_ERROR			0x001

#define CMD_RESTORE			0x010
#define CMD_SEEK			0x070
#define CMD_READ			0x020
#define CMD_WRITE			0x030
#define CMD_FORMAT			0x050
#define CMD_READVERIFY			0x040
#define CMD_DIAGNOSE			0x090
#define CMD_SETPARAMETERS		0x091

#define	ERROR_BBD			0x80
#define ERROR_ECC			0x40
#define ERROR_ID			0x10
#define ERROR_ABRT			0x04
#define ERROR_TRK0			0x02
#define ERROR_MARK			0x01

#define	MAX_RETRIES	5
#define	MAX_ALTBUFS	4

#define PATIENCE	3000000		/* how long to wait for controller */
#define PARTITION(z)	(minor(z) & 0x0f)
#define UNIT(z)		(minor(z) >> 4)
#define GOINGUP		1
#define GOINGDOWN	0

#define GETALTTBL	(('H' << 8) | 1)
#define FMTBAD		(('H' << 8) | 2)
#define BAD_BLK		0x80			/* needed for V_VERIFY */

/*
 * the state of the one and only (stupid board) current block I/O request:
 */
struct hd_ctlr_info {
	u_short	curdrive;		/* drive the controller is using */
	u_char	controller_busy;	/* controller can't take cmd now */
	u_char	retry_count;		/* # of times cmd has been tried */

	u_short	status;			/* stat read from controller port */
	u_char	restore_request;	/* restore command */
	u_char	format_request;		/* let's do some formatting */

	u_int	format_track;		/* used by V_FORMAT in hdioctl() */

	daddr_t	physblock;		/* block # relative to partition 0 */
	u_int	substituteblock;	/* replacement for bad hh.physblock */
	u_int	substitutetrack;	/* used during format, see hdioctl() */
	caddr_t	rw_addr;		/* ram addr to read/write sector */
	u_short	cylinder;		/* cylinder # rel. to part. 0 */
	u_short	head;			/* as it looks */
	u_short	sector;			/* as it looks */
	u_char	single_mode;		/* 1 = transfer one block each time */
	u_char	block_is_bad;		/* 1 = current block is remapped */

	u_int	blockcount;		/* blocks done so far */
	u_int	blocktotal;		/* total blocks this request */

	u_char	interleave_tab[DEV_BSIZE];/* used to format sector interleave */
};

/*
 * the boot record partition table is documented in IBM AT Tech. Ref p. 9-6
 * THIS IS HERE FOR COMPATIBILITY REASONS ONLY.
 * The Mach kernel uses the ipart structure in disk.h instead.
 */
struct boot_record {
	u_char	boot_ind;	/* if it == 0x80, this partition is active */
	u_char	head;		/* driver does not look at this field */
	u_char	sector;		/* driver does not look at this field */
	u_char	cylinder;	/* driver does not look at this field */

	u_char	sys_ind;	/* driver does not look at this field */
	u_char	end_head;	/* driver does not look at this field */
	u_char	end_sector;	/* driver does not look at this field */
	u_char	end_cylinder;	/* driver does not look at this field */

	u_int	rel_sect;	/* where unix starts if boot_ind == 0x80 */
	u_int	num_sects;	/* driver does not look at this field */
};
