/*
 * HISTORY
 * $Log:	kd_queue.h,v $
 * Revision 1.1  91/05/09  13:43:04  jaap
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
 * $CMU-Log:	kd_queue.h,v $
 * Revision 1.5.1.3  90/11/27  13:44:23  rvb
 * 	Synched 2.5 & 3.0 at I386q (r1.5.1.3) & XMK35 (r2.3)
 * 	[90/11/15            rvb]
 * 
 * Revision 2.2  90/05/21  13:27:33  dbg
 * 	First checkin.
 * 	[90/05/17  15:43:55  dbg]
 * 
 * Revision 1.5.1.2  90/02/28  15:50:35  rvb
 * 	Fix numerous typo's in Olivetti disclaimer.
 * 	[90/02/28            rvb]
 * 
 * Revision 1.5.1.1  90/01/08  13:30:45  rvb
 * 	Add Olivetti copyright.
 * 	[90/01/08            rvb]
 * 
 * Revision 1.5  89/07/17  10:42:14  rvb
 * 	Olivetti Changes to X79 upto 5/9/89:
 * 	[89/07/11            rvb]
 * 
 * Revision 1.1.1.1  89/04/27  12:36:03  kupfer
 * X79 from CMU.
 * 
 * Revision 1.4  89/03/09  20:06:59  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/26  12:42:52  gm0w
 * 	Changes for cleanup.
 * 
 */
 
/* **********************************************************************
 File:         kd_queue.h
 Description:  definitions for keybd/display Event queue

 $ Header: $

 Copyright Ing. C. Olivetti & C. S.p.A. 1989.
 All rights reserved.
********************************************************************** */
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

/*
 * Definitions for keyboard/mouse events.
 *
 * The keyboard and mouse can be read as a stream of events.  The event
 * definition is the same in both cases, but only keyboard events will
 * be generated by /dev/kbd, and only mouse events will be generated by
 * /dev/mouse.
 */

#include <i386at/kd.h>

#define KDQSIZE	100			/* is this a good size? */

typedef struct {
	kd_event events[KDQSIZE];
	int firstfree, firstout;
} kd_event_queue;

extern void kdq_put(), kdq_reset();
extern boolean_t kdq_empty(), kdq_full();
extern kd_event *kdq_get();