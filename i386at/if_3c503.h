/* 
 * Mach Operating System
 * Copyright (c) 1991 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	if_3c503.h,v $
 * Revision 2.1.1.1  91/01/11  08:39:48  rvb
 * 	Created.
 * 
 * Revision 2.1.1.1  91/01/04  12:19:07  rvb
 * 	Etherlink II device specific info.
 * 
 */

/* Gate Array Description */

#define	PSTR	0x400
#define	PSPR	0x401
#define	DQTR	0x402
#define	BCFR	0x403
#define	PCFR	0x404
#define	GACFR	0x405
#define	CTLR	0x406
#define	STREG	0x407
#define	IDCFR	0x408
#define	DAMSB	0x409
#define	DALSB	0x40A
#define	VPTR2	0x40B
#define	VPTR1	0x40C
#define	VPTR0	0x40D
#define	RFMSB	0x40E
#define	RFLSB	0x40F

		/*	PSTR	400	*/
/* int */
		/*	PSPR	401	*/
/* int */
		/*	DQTR	402	*/
/* dma only */
		/*	BCFR	403	*/
#define	B7_300	0x300
#define	B6_310	0x310
#define	B5_330	0x330
#define	B4_350	0x350
#define	B3_250	0x250
#define	B2_280	0x280
#define	B1_2A0	0x2a0
#define	B0_2E0	0x2e0
		/*	PCFR	404	*/

		/*	GACFR	405	*/
#define	GACFR_NIM	0x80
#define	GACFR_TCM	0x40
#define	GACFR_OWS	0x20
#define	GACFR_TEST	0x10
#define	GACFR_RSEL	0x08
#define	GACFR_MBS2	0x04
#define	GACFR_MBS1	0x02
#define	GACFR_MBS0	0x01
	/*
	 * This definition is only for the std 8k window on an 8k board.
	 * It is incorrect for a 32K board.  But they do not exists yet
	 * and I don't even know how to tell I am looking at one.
	 */
#define	GACFR_8K	(GACFR_RSEL|0x1)
		/*	CTLR	406	*/
#define	CTLR_START	0x80
#define	CTLR_DDIR	0x40
#define	CTLR_DBSEL	0x20
#define	CTLR_SHARE	0x10
#define	CTLR_EAHI	0x08
#define	CTLR_EALO	0x04
#define	CTLR_XSEL	0x02
#define	CTLR_RST	0x01
#define	CTLR_EA		0x0c
#define CTLR_STA_ADDR	0x04
#define CTLR_THIN	0x02
#define CTLR_THICK	0x00
		/*	STREG	407	*/
/* DMA */
		/*	IDCFR	408	*/
#define	IDCFR_IRQ5	0x80
#define	IDCFR_IRQ4	0x40
#define	IDCFR_IRQ3	0x20
#define	IDCFR_IRQ2	0x10
#define	IDCFR_DRQ3	0x04
#define	IDCFR_DRQ2	0x02
#define	IDCFR_DRQ1	0x01
		/*	DAMSB	409	*/
/* int & dma */
		/*	DALSB	40A	*/
/* int & dma */
		/*	VPTR2	40B	*/
		/*	VPTR1	40C	*/
		/*	VPTR0	40D	*/
		/*	RFMSB	40E	*/
/* what's a register file */
		/*	RFLSB	40F	*/
