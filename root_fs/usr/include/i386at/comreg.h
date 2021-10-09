/*
 * HISTORY
 * $Log:	comreg.h,v $
 * Revision 1.5  92/03/05  16:35:46  slatteng
 * 	declare new minor device bits for DCD & CTS signal use flags
 * 	> 
 * 	[92/03/05  16:35:19  slatteng]
 * 
 * Revision 1.4  91/09/10  13:47:34  slatteng
 * 	#defined "NOi" for new interrupt service function
 * 	[91/09/10  13:41:57  slatteng]
 * 
 * Revision 1.3  91/05/23  15:13:38  slatteng
 * 	added FIFO port definitions
 * 	[91/05/23  15:12:45  slatteng]
 * 
 * Revision 1.2  91/05/14  16:22:24  slatteng
 * 	cleanup
 * 	[91/05/14  14:59:16  slatteng]
 * 
 * Revision 1.1  91/05/09  13:41:13  jaap
 * mt XINU initial version MSD 2.6
 * 
 */

/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * CMU-HISTORY
 * $CMU-Log:	comreg.h,v $
 * Revision 2.3.1.5  90/11/27  13:41:32  rvb
 * 	Synched 2.5 & 3.0 at I386q (r2.3.1.5) & XMK35 (r2.1)
 * 	[90/11/15            rvb]
 * 
 * Revision 2.3.1.4  90/08/25  15:44:03  rvb
 * 	Flush New Ioctls.
 * 	[90/08/14            rvb]
 * 
 * Revision 2.3.1.3  90/07/10  11:43:13  rvb
 * 	Merge csr offsets macros into this file.
 * 	[90/07/06            rvb]
 * 
 * Revision 2.3.1.2  90/02/28  15:49:16  rvb
 * 	Fix numerous typo's in Olivetti disclaimer.
 * 	[90/02/28            rvb]
 * 
 * Revision 2.3.1.1  90/01/08  13:30:02  rvb
 * 	Add Olivetti copyright.
 * 	[90/01/08            rvb]
 * 
 * Revision 2.3  89/09/09  15:21:09  rvb
 * 	com.h -> comreg.h; com.h is now used vs pccom.h for
 * 	configuration.
 * 	[89/09/09            rvb]
 * 
 * Revision 2.2  89/07/17  10:39:48  rvb
 * 	New from Oilvetti.
 * 
 */

/* 
 *	Olivetti serial port driver v1.0
 *	Copyright Ing. C. Olivetti & C. S.p.A. 1988, 1989
 *	All rights reserved.
 *
 */ 
/*
  Copyright 1988, 1989 by Olivetti Advanced Technology Center, Inc.,
Cupertino, California.

		All Rights Reserved

  Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appears in all
copies and that both the copyright notice and this permission notice
appear in supporting documentation, and that the name of Olivetti
not be used in advertising or publicity pertaining to distribution
of the software without specific, written prior permission.

  OLIVETTI DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
IN NO EVENT SHALL OLIVETTI BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUR OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#define	COM_IGNORE_DCD	0x40
#define	COM_IGNORE_CTS	0x80
#define	COMUNIT(dev)	(minor(dev) & 0x3f)

#define	TXRX(addr)	(addr + 0)
#define	BAUD_LSB(addr)	(addr + 0)
#define	BAUD_MSB(addr)	(addr + 1)
#define	INTR_ENAB(addr)	(addr + 1)
#define	INTR_ID(addr)	(addr + 2)
#define	FIFO_CTL(addr)	(addr + 2)
#define	LINE_CTL(addr)	(addr + 3)
#define	MODEM_CTL(addr)	(addr + 4)
#define	LINE_STAT(addr)	(addr + 5)
#define	MODEM_STAT(addr) (addr + 6)

/* interrupt id regisger */
#define	COMBITSi	7
#define	NOi		1
#define	MODi		0
#define	TRAi		2
#define	RECi		4
#define	LINi		6
#define	FIFOon		0x80

/* FIFO control register */
#define	FIFO_TRIG_1	0x00
#define	FIFO_TRIG_4	0x40
#define	FIFO_TRIG_8	0x80
#define	FIFO_TRIG_14	0xc0
#define	FIFO_XMIT_RESET	0x04
#define	FIFO_RECV_RESET	0x02
#define	FIFO_RESET	(FIFO_XMIT_RESET | FIFO_RECV_RESET)
#define	FIFO_ENABLE	0x01
#define	FIFO_OFF	0

#define	FIFO_SIZE	16

/* line control register */
#define		iWLS0	0x01		/*word length select bit 0 */	
#define		iWLS1	0x02		/*word length select bit 2 */	
#define		iSTB	0x04		/* number of stop bits */
#define		iPEN	0x08		/* parity enable */
#define		iEPS	0x10		/* even parity select */
#define		iSP	0x20		/* stick parity */
#define		iSETBREAK 0x40		/* break key */
#define		iDLAB	0x80		/* divisor latch access bit */
#define		i5BITS	0x00		/* 5 bits per char */
#define		i6BITS	0x01		/* 6 bits per char */
#define		i7BITS	0x02		/* 7 bits per char */
#define		i8BITS	0x03		/* 8 bits per char */

/* line status register */
#define		iDR	0x01		/* data ready */
#define		iOR	0x02		/* overrun error */
#define		iPE	0x04		/* parity error */
#define		iFE	0x08		/* framing error */
#define		iBRKINTR 0x10		/* a break has arrived */
#define		iTHRE	0x20		/* tx hold reg is now empty */
#define		iTSRE	0x40		/* tx shift reg is now empty */

/* interrupt enable register */
#define		iRX_ENAB	0x01
#define		iTX_ENAB	0x02
#define		iERROR_ENAB	0x04
#define		iMODEM_ENAB	0x08

/* modem control register */
#define		iDTR		0x01	/* data terminal ready */
#define		iRTS		0x02	/* request to send */
#define		iOUT1		0x04	/* COM aux line -not used */
#define		iOUT2		0x08	/* turns intr to 386 on/off */	
#define		iLOOP		0x10	/* loopback for diagnostics */

/* modem status register */
#define		iDCTS		0x01	/* delta clear to send */
#define		iDDSR		0x02	/* delta data set ready */
#define		iTERI		0x04	/* trail edge ring indicator */
#define		iDRLSD		0x08	/* delta rx line sig detect */
#define		iCTS		0x10	/* clear to send */
#define		iDSR		0x20	/* data set ready */
#define		iRI		0x40	/* ring indicator */
#define		iRLSD		0x80	/* rx line sig detect */

