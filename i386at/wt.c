
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	wt.c,v $
 * Revision 2.2.1.6  91/07/15  00:17:03  rvb
 * 	Flush micro second timing stuff; this was never working.
 * 	[91/06/27            mg32]
 * 
 * Revision 2.2.1.5  90/08/25  15:44:25  rvb
 * 	Use take_<>_irq() vs direct manipulations of ivect and friends.
 * 	[90/08/20            rvb]
 * 
 * Revision 2.2.1.4  90/07/10  11:45:41  rvb
 * 	New style probe/attach.
 * 	NOTE: the probe test could be made more thorough
 * 	[90/06/15            rvb]
 * 
 * Revision 2.2.1.3  90/01/08  13:29:38  rvb
 * 	Add Intel copyright.
 * 	[90/01/08            rvb]
 * 
 * Revision 2.2.1.2  89/12/21  18:00:09  rvb
 * 	Change WTPRI to make the streamer tape read/write
 * 	interruptible. 		[lin]
 * 
 * Revision 2.2.1.1  89/11/10  09:49:49  rvb
 * 	ORC likes their streamer port at 0x288.
 * 	[89/11/08            rvb]
 * 
 * Revision 2.2  89/09/25  12:33:02  rvb
 * 	Driver was provided by Intel 9/18/89.
 * 	[89/09/23            rvb]
 * 
 */

/*
 *
 *  Copyright 1988, 1989 by Intel Corporation
 *
 *	Support Bell Tech QIC-02 and WANGTEK QIC-36 or QIC-02
 */

#include <wt.h>
#include <sys/errno.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/buf.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/file.h>
#include <sys/proc.h>
#include <i386/ipl.h>
#include <i386at/atbus.h>
#include <i386at/wtreg.h>

unsigned wtport;
struct isa_dev *wtdev[NWT];
unsigned wtchan = 1;		/* DMA channel number		*/
				/* stardard = 1			*/
				/* hardware permits 1, 2 or 3.	*/
		                /* (Avoid DMA 2: used by disks) */

#define	ERROR 		1	/* return from tape routines */
#define	SUCCESS		0	/* return from tape routines */

int	wci = FALSE;
int	exflag = FALSE;
int	bytes = 0;

static	u_char eqdma = 0x8;
static	u_char pagereg = 0x83;
static	u_char dmareg = 2;
static	u_char dma_write = 0x49;
static	u_char dma_read = 0x45;
static	u_char dma_done = 2;
static	u_char mode = 0;
static	u_char mbits;	/* map bits into each other */
static	long bufptr;
static	unsigned numbytes;
/*
_wci		dw	0	; interrupt chain finished normally
_exflag		dw	0	; exception variable
_bytes		dw	0	; current bytes

eqdma		db	8h	; enable dma command: ch1,ch2=8h, ch3=10h
pagereg		db	83h	; ch1=83h, ch2=81h, ch3=82h
dmareg		db	2	; ch1=2, ch2=4, ch3=6
dma_write	db	49h	; write dma command: 48h+_wtchan
dma_read	db	45h	; read dma command: 44h+_wtchan
dma_done	db	2	; dma done flag: 1<<_wtchan
mode		db	0	; dma operation mode
lbufptr		dw	0	; buffer pointer to data buffers, low word
hbufptr		dw	0	; buffer pointer to data buffers, high word
numbytes	dw	0	; number of bytes to read or write (new)
*/

#define PAGESIZ		4096
#define HZ		100

/* tape controller ports */
#define STATPORT	wtport
#define CTLPORT		STATPORT
#define CMDPORT		(wtport+1)
#define DATAPORT	CMDPORT

/* defines for reading out status from wangtek tape controller */
#define READY   	0x01    /* ready bit define        */
#define EXCEP		0x02	/* exception bit define    */
#define STAT		(READY|EXCEP)
#define	RESETMASK	0x7
#define	RESETVAL	(RESETMASK & ~EXCEP)

/* tape controller control bits (CTLPORT) */
#define	ONLINE	0xC1
#define	RESET	0x02
#define	REQUEST	0x04		/* request command */
#define	CMDOFF	0xC0

/* QIC-02 commands (CMDPORT) */
#define	RDDATA	0x80		/* read data */
#define	READFM	0xA0		/* read file mark */
#define	WRTDATA	0x40		/* write data */
#define	WRITEFM	0x60		/* write file mark */
#define	RDSTAT	0xC0		/* read status command */
#define	REWIND	0x21		/* rewind command (position+bot) */

/* 8237 DMA controller regs */
#define	STATUSREG	0x8
#define MASKREG		0xA
#define MODEREG		0xB
#define CLEARFF		0xC

/* streamer tape block size */
#define BLKSIZE	512

/* Tape characteristics */
#define	NBPS		512	/* 512-byte blocks */
#define	ERROR 		1	/* return from tape routines */
#define	SUCCESS		0	/* return from tape routines */

/* Minor devs */
#define	TPREWCLOSE(d)	(d&04)	/* Rewind tape on close if read or write */
#define TPHOG(d)	0	/* use Hogproc during tape I/O	*/

/* defines for wtflags */
#define	TPINUSE	0x0001		/* tape is already open */
#define	TPREAD	0x0002		/* tape is only open for reading */
#define	TPWRITE	0x0004		/* tape is only open for writing */
#define	TPSTART 0x0008		/* tape must be rewound and reset */
#define	TPDEAD	0x0010		/* tape drive does not work or driver error */
#define	TPSESS	0x0020		/* no more reads or writes allowed in session */
				/* for example, when tape has to be changed */
#define	TPSTOP	0x0040		/* Stop command outstanding */
#define	TPREW	0x0080		/* Rewind command outstanding, see wtdsl2() */
#define	TPVOL	0x0100		/* Read file mark, or hit end of tape */
#define	TPWO	0x0200		/* write command outstanding */
#define	TPRO	0x0400		/* read command outstanding */
#define TPWANY	0x0800		/* write command requested */
#define TPRANY	0x1000		/* read command requested */
#define	TPWP	0x2000		/* write protect error seen */

unsigned int	wtflags = TPSTART;	/* state of tape drive */

struct	buf	rwtbuf;		/* header for raw i/o */
struct  proc	*myproc;	/* process which opened tape driver */

char wtimeron;			/* wtimer() active flag */
char wtio;			/* dma (i/o) active flag */
char isrlock;			/* isr() flag */

struct proc * Hogproc;	/* no Hogproc on Microport */
#define	ftoseg(x)	((unsigned) (x >> 16))
#define	seterror(err)	u.u_error = err

struct	wtstatus {
	ushort	wt_err;		/* code for error encountered */
	ushort	wt_ercnt;	/* number of error blocks */
	ushort	wt_urcnt;	/* number of underruns */
}	wterror;

/* defines for wtstatus.wt_err */
#define	TP_POR		0x100	/* Power on/reset occurred */
#define	TP_RES1		0x200	/* Reserved for end of media */
#define	TP_RES2		0x400	/* Reserved for bus parity */
#define	TP_BOM		0x800	/* Beginning of media */
#define	TP_MBD		0x1000	/* Marginal block detected */
#define	TP_NDT		0x2000	/* No data detected */
#define	TP_ILL		0x4000	/* Illegal command */
#define	TP_ST1		0x8000	/* Status byte 1 bits */
#define	TP_FIL		0x01	/* File mark detected */
#define	TP_BNL		0x02	/* Bad block not located */
#define	TP_UDA		0x04	/* Unrecoverable data error */
#define	TP_EOM		0x08	/* End of media */
#define	TP_WRP		0x10	/* Write protected cartridge */
#define	TP_USL		0x20	/* Unselected drive */
#define	TP_CNI		0x40	/* Cartridge not in place */
#define	TP_ST0		0x80	/* Status byte 0 bits */

/* Grounds for reporting I/O error to user */
#define	TP_ERR0		(TP_BNL|TP_UDA|TP_WRP|TP_CNI|TP_FIL|TP_EOM|TP_USL)
#define	TP_ERR1		(TP_MBD|TP_NDT|TP_ILL)
/* TP_ILL should never happen! */
/*
#define	TP_ERR0		0x7f
#define	TP_ERR1		0x7700
*/

/* defines for reading out status from wangtek tape controller */
#define READY   	0x01    /* ready bit define        */
#define EXCEP		0x02	/* exception bit define    */

/* sleep priority */
#define WTPRI	(PZERO-5)

char	pagebuf[NBPS];		/* buffer of size NBPS */
unsigned long	pageaddr;	/* physical addr of pagebuf */
				/* pageaddr is used with DMA controller */
time_t Hogtime;			/* lbolt when Hog timer started */
extern time_t	lbolt;

#define	debug	printf

extern int wtintr(), wtprobe(), wtattach();

int	(*wtintrs[])() = {	wtintr, 0};

struct	isa_driver	wtdriver = 
	{wtprobe, 0, wtattach, "wt", 0, 0, 0};

int
wtprobe(dev)
struct isa_dev	*dev;
{
	caddr_t	spot = dev->dev_addr;
	unsigned wtport_save;

	if (wtchan < 1 || wtchan > 3) {
		sterr("Bad DMA channel, cannot init driver");
		return 0;
	}

	wtport_save = wtport;
	wtport = (unsigned)spot;
	if (t_reset() == SUCCESS) {
		return(1);
	} else {
		wtport = wtport_save;
		return(0);
	}
}

int
wtattach(dev)
struct isa_dev *dev;
{
	struct	tty	*tp;
	u_char		unit = dev->dev_unit;

	take_dev_irq(dev);
	printf("wt%d:  port = %x, spl = %d, pic = %d.\n",
		unit, dev->dev_addr, dev->dev_spl, dev->dev_pic);
	wtdev[unit] = dev;

	switch (wtchan) {
	case 1:
		break;
	case 2:
		dma_write = wtchan+0x48;
		dma_read = wtchan+0x44;
		dmareg = wtchan+wtchan;
		pagereg = 0x81;
		dma_done = 4;
		break;
	case 3:
		dma_write = wtchan+0x48;
		dma_read = wtchan+0x44;
		dmareg = wtchan+wtchan;
		eqdma = 0x10;
		pagereg = 0x82;
		dma_done = 8;
		break;
	}
	pageaddr = kvtophys((unsigned long) pagebuf);

#ifdef DEBUG
	debug("wt%d:  pageset: addr %lx\n", pageaddr);
#endif

	return;
}
/*
 * Strategy routine.
 *
 * Arguments:
 *  Pointer to buffer structure
 * Function:
 *  Start transfer.
 *
 * It would be nice to have this multiple-threaded.
 * There is a version of dump from Berkeley that works with multiple processes
 * trading off with disk & tape I/O.
 */

int
wtstrategy(bp)
register struct buf *bp;
{
	unsigned ucnt1, ucnt2, finished;
	unsigned long adr1, adr2;

	adr1 = kvtophys(bp->b_un.b_addr);
#ifdef DEBUG
	debug("bpaddr %x\n", adr1);
#endif
	ucnt1 = bp->b_bcount;
	ucnt2 = 0;
	adr2 = 0;
#ifdef DEBUG
	debug("WTstart: adr1 %lx cnt %x\n", adr1, ucnt1);
#endif
	if (ftoseg(adr1) != ftoseg(adr1 + (unsigned) ucnt1 - 1))
	{
		adr2 = (adr1 & 0xffff0000L) + 0x10000L;
		ucnt2 = (adr1 + ucnt1) - adr2;
		ucnt1 -= ucnt2;
	}
	/* at file marks and end of tape, we just return '0 bytes available' */
	if (wtflags & TPVOL) {
		bp->b_resid = bp->b_bcount;
		goto xit;
	}
	if ((Hogproc == (struct proc *) 0) && TPHOG(bp->b_dev))
	{
#ifdef DEBUG
		printf("setting Hogproc\n");
#endif
		Hogtime = 0;
		Hogproc = myproc;
	}
	if (bp->b_flags & B_READ) {
		int	bad = 0;

		/* For now, we assume that all data will be copied out */
		/* If read command outstanding, just skip down */
		if (!(wtflags & TPRO)) {
			if (ERROR == wtsense(TP_WRP))	/* clear status */
				goto errxit;
#ifdef DEBUG
			debug("WTread: Start read\n");
#endif
			if (!(wtflags & TPREAD) || (wtflags & TPWANY) ||
			    (rstart() == ERROR))  {
#ifdef DEBUG
				debug("Tpstart: read init error\n"); /* */
#endif
				goto errxit;
			}
			wtflags |= TPRO|TPRANY;
		}

		finished = 0;
		/* Take a deep breath */
		if (ucnt1) {
			if ((rtape(adr1, ucnt1) == ERROR) &&
					(wtsense(TP_WRP) == ERROR))
				goto endio;
			/* wait for it */
			bad = pollrdy();
			finished = bytes;
			if (bad)
				goto endio;
		}
		/* if a second I/O region, start it */
		if (ucnt2) {
			if ((rtape(adr2, ucnt2) == ERROR) &&
					(wtsense(TP_WRP) == ERROR))
				ucnt2 = 0;	/* don't poll for me */
			}

		/* if second i/o pending wait for it */
		if (ucnt2) {
			pollrdy();
			/* whether pollrdy is ok or not */
			finished += bytes;
		}
	} else {
		if (wtflags & TPWP)	/* write protected */
			goto errxit;

		/* If write command outstanding, just skip down */
		if (!(wtflags & TPWO)) {
			if (ERROR == wtsense(0))	/* clear status */
			{
#ifdef DEBUG
				debug("TPstart: sense 0\n");
#endif
				goto errxit;
			}
			if (!(wtflags & TPWRITE) || (wtflags & TPRANY) ||
			    (wstart() == ERROR))  {
#ifdef DEBUG
				debug("Tpstart: write init error\n"); /* */
#endif
				wtsense(0);

errxit:				bp->b_flags |= B_ERROR;
				bp->b_resid = bp->b_bcount;
				goto xit;
			}
			wtflags |= TPWO|TPWANY;
		} 

		/* and hold your nose */
		if (ucnt1 && ((wtape(adr1, ucnt1) == ERROR)
				&& (wtsense(0) == ERROR)))
			finished = bytes;

		else if (ucnt2 &&
			(((ucnt1 && pollrdy()) ||
				(wtape(adr2, ucnt2) == ERROR)) &&
				(wtsense(0) == ERROR)))
			finished = ucnt1 + NBPS + bytes;
		/* All writes and/or copyins were fine! */
		else
			finished = bp->b_bcount;
		pollrdy();
	}

	endio:
	wterror.wt_err = 0;
	if (exflag && wtsense((bp->b_flags & B_READ) ? TP_WRP : 0)) {
		if ((wterror.wt_err & TP_ST0) 
			&& (wterror.wt_err & (TP_FIL|TP_EOM))) {
#ifdef DEBUG
			debug("WTsta: Hit end of tape\n"); /* */
#endif
			wtflags |= TPVOL;
			if (wterror.wt_err & TP_FIL) {
				if (wtflags & TPRO)
					/* interrupter is bogus */
					rstart();  /* restart read command */
				else
					wtflags &= ~TPWO;
				finished += NBPS; 
			}
		/* Reading file marks or writing end of tape return 0 bytes */
		} else	{
			bp->b_flags |= B_ERROR;
			wtflags &= ~(TPWO|TPRO);
		}
	}

	bp->b_resid = bp->b_bcount - finished;
xit:
	biodone(bp);
	if (wtimeron)
		Hogtime = lbolt;
	else if (Hogproc == myproc)
		Hogproc = (struct proc *) 0;
}

/*
 * simulate an interrupt periodically while I/O is going
 * this is necessary in case interrupts get eaten due to
 * multiple devices on a single IRQ line
 */
wtimer()
{
	/* If I/O going and not in isr(), simulate interrupt
	 * If no I/O for at least 1 second, stop being a Hog
	 * If I/O done and not a Hog, turn off wtimer()
	 */
	if (wtio && !isrlock)
		isr();

	if ((Hogproc == myproc) && Hogtime && (lbolt-Hogtime > HZ))
		Hogproc = (struct proc *) 0;

	if (wtio || (Hogproc == myproc))
		timeout(wtimer, (caddr_t) 0, HZ);
	else
		wtimeron = 0;
}


wtrawio(bp)
struct buf	*bp;
{
	wtstrategy(bp);
	biowait(bp);
	return(0);
}

wt_minphys(bp)
struct buf	*bp;
{
	if (bp->b_bcount > PAGESIZ)
		bp->b_bcount = PAGESIZ;
}

/*
 * raw read routine
 */
wtread(dev, uio)
struct uio	*uio;
{
	if (wtflags & TPSESS) {
		seterror(EIO);
		return(EIO);
	}
	physio(wtrawio, &rwtbuf, dev, B_READ, wt_minphys, uio);
	return(0);
}

/*
 * raw write routine
 */
wtwrite(dev, uio)
struct uio	*uio;
{
	if (wtflags & TPSESS) {
		seterror(EIO);
		return(EIO);
	}
	physio(wtrawio, &rwtbuf, dev, B_WRITE, wt_minphys, uio);
	return(0);
}



/*
 * ioctl routine
 *  for user level QIC commands only
 */
wtioctl(dev, cmd, arg, mode)
int dev, cmd;
unsigned long arg;
int mode;
{
	if (cmd == WTQICMD)
	{
		if ((qicmd((int)arg) == ERROR) || (rdyexc(HZ) == ERROR))
		{
			wtsense(0);
			seterror(EIO);
		}
		return;
	}
	seterror(EINVAL);
}

/*
 * open routine
 * called on every device open
 */
wtopen(dev, flag)
int	dev, flag;
{
	int unit = minor(dev) >> 3;

#ifdef DEBUG
	printf("wtopen ...\n");
#endif
	if (unit > NWT || !wtdev[unit] || !wtdev[unit]->dev_alive)
		return ENXIO;

	if (!pageaddr) {
		nodev();
		return(ENXIO);
	}
	if (wtflags & (TPINUSE)) {
		seterror(ENXIO);
		return(ENXIO);
	}
	if (wtflags & (TPDEAD)) {
		seterror(EIO);
		return(EIO);
	}
	/* If a rewind from the last session is going on, wait */
	while(wtflags & TPREW) {
#ifdef DEBUG
		debug("Waiting for rew to finish\n");
#endif
		delay(1000000);	/* delay one second */
	}
	/* Only do reset and select when tape light is off, and tape is rewound.
	 * This allows multiple volumes. */
	if (wtflags & TPSTART) { 
		if (t_reset() != SUCCESS) {
			nodev();
			return(ENXIO);
		}
#ifdef DEBUG
		debug("reset done. calling wtsense\n");
#endif
		if (wtsense(TP_WRP) == ERROR) {
			seterror(EIO);
			return (EIO);
		}
#ifdef DEBUG
		debug("wtsense done\n");
#endif
		wtflags &= ~TPSTART;	
	}

	wtflags = TPINUSE;
	if (flag & FREAD)
		wtflags |= TPREAD;
	if (flag & FWRITE)
		wtflags |= TPWRITE;
	rwtbuf.b_flags = 0;
	myproc = u.u_procp;		/* for comparison */
	return(0);
}

/*
 * close routine
 * called on last device close
 * If not rewind-on-close, leave read or write command intact.
 */
wtclose(dev)
{
	int wtdsl2();

#ifdef DEBUG
	debug("WTclose:\n");
#endif
	if (Hogproc == myproc)
		Hogproc = (struct proc *) 0;
	if (!exflag && (wtflags & TPWANY) && !(wtflags & (TPSESS|TPDEAD))) {
		if (!(wtflags & TPWO))
			wstart();
#ifdef DEBUG
		debug("WT: Writing file mark\n");
#endif
		wmark();	/* write file mark */
#ifdef DEBUG
		debug("WT: Wrote file mark, going to wait\n");
#endif
		if (rdyexc(HZ/10) == ERROR) {
			wtsense(0);
			}
		}
	if (TPREWCLOSE(dev) || (wtflags & (TPSESS|TPDEAD))) {
	/* rewind tape to beginning of tape, deselect tape, and make a note */
	/* don't wait until rewind, though */
		/* Ending read or write causes rewind to happen, if no error,
		 * and READY and EXCEPTION stay up until it finishes */
		if (wtflags & (TPRO|TPWO))
		{
#ifdef DEBUG
			debug("End read or write\n");
#endif
			rdyexc(HZ/10);
			ioend();
			wtflags &= ~(TPRO|TPWO);
		}
		else	wtwind();
		wtflags |= TPSTART | TPREW;
		timeout(wtdsl2, 0, HZ);
	}
	else if (!(wtflags & (TPVOL|TPWANY)))
	{
		/* space forward to after next file mark no writing done */
		/* This allows skipping data without reading it.*/
#ifdef DEBUG
		debug("Reading past file mark\n");
#endif
		if (!(wtflags & TPRO))
			rstart();
		rmark();
		if (rdyexc(HZ/10))
		{
			wtsense(TP_WRP);
		}
	}
	wtflags &= TPREW|TPDEAD|TPSTART|TPRO|TPWO;
	return(0);
}

/* return ERROR if user I/O request should receive an I/O error code */

wtsense(ignor)
{
	wtflags &= ~(TPRO|TPWO);
#ifdef DEBUG
	debug("WTsense: start ");
#endif
	if (rdstatus(&wterror) == ERROR)
	{
#ifdef DEBUG
		debug("WTsense: Can't read status\n");
#endif
		return(ERROR);
	}
#ifdef DEBUG
	if (wterror.wt_err & (TP_ST0|TP_ST1))
	{
		debug("Tperror: status %x error %d underruns %d\n",
			wterror.wt_err, wterror.wt_ercnt, wterror.wt_urcnt);
	}
	else
		debug("done. no error\n");
#endif
	wterror.wt_err &= ~ignor;	/* ignore certain errors */
	reperr(wterror.wt_err);
	if (((wterror.wt_err & TP_ST0) && (wterror.wt_err & TP_ERR0)) ||
		    ((wterror.wt_err & TP_ST1) && (wterror.wt_err & TP_ERR1)))
			return	ERROR;

	return SUCCESS;
}

/* lifted from tdriver.c from Wangtek */
reperr(srb0)
int srb0;
{
	int s0 = srb0 & (TP_ERR0|TP_ERR1);	/* find out which exception to report */
 
	if (s0) {
		if (s0 & TP_USL) 
			sterr("Drive not online");
		else if (s0 & TP_CNI) 
			sterr("No cartridge");
		else if ((s0 & TP_WRP) && !(wtflags & TPWP))
		{
			sterr("Tape is write protected");
			wtflags |= TPWP;
		}
		/*
		if (s0 & TP_FIL)
			sterr("Filemark detected");
		*/
		else if (s0 & TP_BNL)
			sterr("Block in error not located");
		else if (s0 & TP_UDA)
			sterr("Unrecoverable data error");
		/*
		else if (s0 & TP_EOM)
			sterr("End of tape");
		*/
		else if (s0 & TP_NDT)
			sterr("No data detected");
		/*
		if (s0 & TP_POR)
			sterr("Reset occured");
		*/
		else if (s0 & TP_BOM)
			sterr("Beginning of tape");
		else if (s0 & TP_ILL)
			sterr("Illegal command");
	}
}
	
sterr(errstr)
char	*errstr;
{
	printf("Streamer: %s\n", errstr);
}

/* Wait until rewind finishes, and deselect drive */
wtdsl2() {
	int	stat;

	stat = inb(wtport) & (READY|EXCEP);
#ifdef DEBUG
	debug("Timeout: Waiting for rewind to finish: stat %x\n", stat);
#endif
	switch (stat) {
		/* They're active low, ya'know */
		case READY|EXCEP:
			timeout(wtdsl2, (caddr_t) 0, HZ);
			return;
		case EXCEP: 
			wtflags &= ~TPREW;
			return;
		case READY:
		case	0:
			wtflags &= ~TPREW;
			sterr("Rewind failed");
			wtsense(TP_WRP);
			return;
			}
	}

wtwind() {
#ifdef DEBUG
	debug("WT: About to rewind\n");
#endif
	rwind();	/* actually start rewind */
}

wtintr(unit) {
	if (wtflags & (TPWO|TPRO))
	{
		isrlock = 1;
		if (wtio) isr();
		isrlock = 0;
	}
}

rdyexc(ticks)
{
	int s;
#ifdef DEBUG
	int os = 0xffff;		/* force printout first time */
#endif
	for (;;) {			/* loop until ready or exception */
		s=(inb(wtport) & 0xff);	/* read the status register */
#ifdef DEBUG
		if (os != s) {
			debug("Status reg = %x\n", s); /* */
			os = s;
			}
#endif
		if (!(s & EXCEP))	/* check if exception have occured */
			break;
		if (!(s & READY))	/* check if controller is ready */
			break;
		s = spl5();
		delay((ticks/HZ)*1000000); /* */
		splx(s);
	}
#ifdef DEBUG
	debug("Status reg = %x on return\n", s); /* */
#endif
	return((s & EXCEP)?SUCCESS:ERROR);  /* return exception if it occured */
}

pollrdy()
{
	int	 sps;
#ifdef DEBUG
	debug("Pollrdy\n");
#endif
	sps = spl5();
	while (wtio)
		sleep(&wci, WTPRI);
	splx(sps);
#ifdef DEBUG
	debug("Finish poll, wci %d exflag %d\n", wci, exflag);
#endif
	return exflag;
}

wtdma()		/* start up i/o operation, called from dma() in wtlib1.s */
{
	wtio = 1;
	if (!wtimeron)
	{
		wtimeron = 1;
		timeout(wtimer, (caddr_t) 0, HZ/2);
	}
}

wtwake()	/* end i/o operation, called from isr() in wtlib1.s */
{
	wtio = 0;
	wakeup(&wci);
}


#define near

static near
sendcmd()
{
	/* desired command in global mbits */

	outb(CTLPORT, mbits | REQUEST);		/* set request */
	while (inb(STATPORT) & READY);		/* wait for ready */
	outb(CTLPORT, mbits & ~REQUEST);	/* reset request */
	while ((inb(STATPORT) & READY) == 0);	/* wait for not ready */
}

static near		/* execute command */
cmds(cmd)
{
	register s;

	do s = inb(STATPORT);
	while ((s & STAT) == STAT);	/* wait for ready */

	if ((s & EXCEP) == 0)		/* if exception */
		return ERROR;		/* error */
	
	outb(CMDPORT, cmd);		/* output the command	*/

	outb(CTLPORT, mbits=ONLINE);	/* set & send ONLINE	*/
	sendcmd();

	return SUCCESS;
}

qicmd(cmd)
{
	return cmds(cmd);
}

rstart()
{
	return cmds(RDDATA);
}

rmark()
{
	return cmds(READFM);
}

wstart()
{
	return cmds(WRTDATA);
}

ioend()
{
	register s;
	register rval = SUCCESS;

	do s = inb(STATPORT);
	while ((s & STAT) == STAT);	/* wait for ready */

	if ((s & EXCEP) == 0)		/* if exception */
		rval = ERROR;		/* error */
	
	outb(CTLPORT, CMDOFF);		/* reset ONLINE */
	outb(MASKREG, wtchan+4);	/* turn off dma */
	outb(CLEARFF, 0);		/* reset direction flag */

	return rval;
}

wmark()
{
	register s;

	if (cmds(WRITEFM) == ERROR)
		return ERROR;

	do s = inb(STATPORT);
	while ((s & STAT) == STAT);	/* wait for ready */

	if ((s & EXCEP) == 0)		/* if exception */
		return ERROR;		/* error */

	return SUCCESS;
}

rwind()
{
	register s;

	mbits = CMDOFF;

	do s = inb(STATPORT);
	while ((s & STAT) == STAT);	/* wait for ready */

	outb(CMDPORT, REWIND);
	sendcmd();

	return SUCCESS;
}

rdstatus(stp)
char *stp;		/* pointer to 6 byte buffer */
{
	register s;
	int n;

	do s = inb(STATPORT);
	while ((s & STAT) == STAT);	/* wait for ready or exception */

	outb(CMDPORT, RDSTAT);
	sendcmd();			/* send read status command */

	for (n=0; n<6; n++)
	{
#ifdef DEBUG
		debug("rdstatus: waiting, byte %d\n", n);
#endif
		do s = inb(STATPORT);
		while ((s & STAT) == STAT);	/* wait for ready */
#ifdef DEBUG
		debug("rdstatus: done\n");
#endif
		if ((s & EXCEP) == 0)		/* if exception */
			return ERROR;		/* error */

		*stp++ = inb(DATAPORT);		/* read status byte */

		outb(CTLPORT, mbits | REQUEST);	/* set request */
#ifdef DEBUG
		debug("rdstatus: waiting after request, byte %d\n", n);
#endif
		while ((inb(STATPORT)&READY) == 0);	/* wait for not ready */
		for (s=100; s>0; s--);		/* wait an additional time */

		outb(CTLPORT, mbits & ~REQUEST);/* unset request */
#ifdef DEBUG
		debug("rdstatus: done\n");
#endif
	}
	return SUCCESS;
}

t_reset()
{
	register i;
	outb(CTLPORT, RESET);		/* send reset */
	delay(20);
	outb(CTLPORT, CMDOFF);		/* turn off reset */
	if ((inb(STATPORT) & RESETMASK) == RESETVAL)
		return SUCCESS;
	return ERROR;
}

static
dma()
{
	int x=spl5();
	wtdma();
	outb(CLEARFF, 0);
	outb(MODEREG, mode);	/* set dma mode */
	outb(dmareg, bufptr & 0xFF);
	outb(dmareg, (bufptr>>8) & 0xFF);
	outb(pagereg, (bufptr>>16) & 0xFF);                         
	outb(dmareg+1, (BLKSIZE-1) & 0xFF);
	outb(dmareg+1, (BLKSIZE-1) >> 8);
	outb(wtport, eqdma+ONLINE);
	outb(MASKREG, wtchan);	/* enable command to 8237, start dma */
	splx(x);
}

static near
wtstart(buf, cnt)
long buf;
int cnt;
{
	register s;

	bufptr = buf;		/* init statics */
	numbytes = cnt;
	wci = FALSE;		/* init flags */
	exflag = FALSE;
	bytes = 0;		/* init counter */

	do s = inb(STATPORT) & STAT;
	while (s == STAT);	/* wait for ready or error */

	if (s & EXCEP)		/* no error */
	{
		dma();
		return SUCCESS;
	}
	return ERROR;		/* error */
}

rtape(buf, cnt)
long buf;			/* physical address */
int cnt;			/* number of bytes */
{
	mode = dma_read;
	return wtstart(buf,cnt);
}

wtape(buf, cnt)
long buf;			/* physical address */
int cnt;			/* number of bytes */
{
	mode = dma_write;
	return wtstart(buf,cnt);
}

isr()
{
	int stat = inb(wtport);
	if (!(stat & EXCEP))	/* exception during I/O */
	{
		if (bytes + BLKSIZE >= numbytes) wci = TRUE;
		exflag = TRUE;
		goto isrwake;
	}
	if ((stat & READY) || !(inb(STATUSREG) & dma_done))
		return;
	exflag = FALSE;
	outb(wtport, ONLINE);
	bytes += BLKSIZE;
	if (bytes >= numbytes)	/* normal completion of I/O */
	{
		wci = TRUE;
isrwake:
		outb(MASKREG, 4+wtchan);	/* turn off dma */
		wtwake();			/* wake up user level */
	}
	else
	{			/* continue I/O */
		bufptr += BLKSIZE;
		dma();
	}
}

/*
 * delay i ten-microseconds
 */
delay(i)
int i;
{
  register int j;
  for (j=i*20; j>0; j--)
    inb(0x377);
}

wtsize()
{
}

wtdump()
{
}
