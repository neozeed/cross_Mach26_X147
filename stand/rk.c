/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 **********************************************************************
 * HISTORY
 * $Log:	rk.c,v $
 * Revision 2.3  89/03/09  21:16:34  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  14:35:14  gm0w
 * 	Changes for cleanup.
 * 
 **********************************************************************
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)rk.c	7.1 (Berkeley) 6/5/86
 */

/*
 * RK611/RK07
 */
#include <machine/pte.h>

#include <sys/param.h>
#include <sys/inode.h>
#include <sys/fs.h>

#include <vaxuba/ubareg.h>
#include <vaxuba/rkreg.h>

#include "saio.h"
#include "savax.h"

u_short	rkstd[] = { 0777440 };
short	rk_off[] = { 0, 241, 0, -1, -1, -1, 393, -1 };

rkopen(io)
	register struct iob *io;
{
	register struct rkdevice *rkaddr = (struct rkdevice *)ubamem(io->i_unit, rkstd[0]);

	if (rk_off[io->i_boff] == -1 ||
	    io->i_boff < 0 || io->i_boff > 7)
		_stop("rk bad unit");
	io->i_boff = rk_off[io->i_boff] * NRKSECT*NRKTRK;
	rkaddr->rkcs2 = RKCS2_SCLR;
	rkwait(rkaddr);
}

rkstrategy(io, func)
	register struct iob *io;
{
	register struct rkdevice *rkaddr = (struct rkdevice *)ubamem(io->i_unit, rkstd[0]);
	int com;
	daddr_t bn;
	short dn, cn, sn, tn;
	int ubinfo, errcnt = 0;

retry:
	ubinfo = ubasetup(io, 1);
	bn = io->i_bn;
	dn = io->i_unit;
	cn = bn/(NRKSECT*NRKTRK);
	sn = bn%NRKSECT;
	tn = (bn / NRKSECT) % NRKTRK;
	rkaddr->rkcs2 = dn;
	rkaddr->rkcs1 = RK_CDT|RK_PACK|RK_GO;
	rkwait(rkaddr);
	rkaddr->rkcs1 = RK_CDT|RK_DCLR|RK_GO;
	rkwait(rkaddr);
	rkaddr->rkda = sn | (tn << 8);
	rkaddr->rkcyl = cn;
	rkaddr->rkba = ubinfo;
	rkaddr->rkwc = -(io->i_cc >> 1);
	com = RK_CDT|((ubinfo>>8)&0x300)|RK_GO;
	if (func == READ)
		com |= RK_READ;
	else
		com |= RK_WRITE;
	rkaddr->rkcs1 = com;
	rkwait(rkaddr);
	while ((rkaddr->rkds & RKDS_SVAL) == 0)
		;
	ubafree(io, ubinfo);
	if (rkaddr->rkcs1 & RK_CERR) {
		printf("rk error: (cyl,trk,sec)=(%d,%d,%d) cs2=%b er=%b\n",
		    cn, tn, sn, rkaddr->rkcs2, RKCS2_BITS,
		    rkaddr->rker, RKER_BITS);
		rkaddr->rkcs1 = RK_CDT|RK_DCLR|RK_GO;
		rkwait(rkaddr);
		if (errcnt == 10) {
			printf("rk: unrecovered error\n");
			return (-1);
		}
		errcnt++;
		goto retry;
	}
	if (errcnt)
		printf("rk: recovered by retry\n");
	return (io->i_cc);
}

rkwait(rkaddr)
	register struct rkdevice *rkaddr;
{

	while ((rkaddr->rkcs1 & RK_CRDY) == 0)
		;
}

/*ARGSUSED*/
rkioctl(io, cmd, arg)
	struct iob *io;
	int cmd;
	caddr_t arg;
{

	return (ECMD);
}