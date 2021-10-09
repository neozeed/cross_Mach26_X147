/*
 * HISTORY
 * $Log:	if_par.h,v $
 * Revision 1.2  91/12/03  17:16:14  slatteng
 * 	update from CMU
 * 	[91/12/03  17:09:42  slatteng]
 * 
 * Revision 1.1  91/05/09  13:42:09  jaap
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
 * $CMU-Log:	if_par.h,v $
 * Revision 2.1.1.1  90/08/25  15:43:59  rvb
 * 	Created 08/05/90.
 * 		Parallel port network driver.
 * 	[90/08/14            mg32]
 * 
 */
 
/* 
 *	Parallel port network driver v1.0
 *	All rights reserved.
 */ 
#define OUTPUT(addr) (addr + 0)
#define INPUT(addr)  (addr + 1)
#define INTR(addr)   (addr + 2)

#define SPLNET		spl6
#define PARMTU		8192
#define MAXSPIN		10000
