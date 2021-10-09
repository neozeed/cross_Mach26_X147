/*
 * HISTORY
 * $Log:	blitvar.h,v $
 * Revision 1.1  91/05/09  13:41:03  jaap
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
 * $CMU-Log:	blitvar.h,v $
 * Revision 1.6.1.3  90/11/27  13:41:12  rvb
 * 	Synched 2.5 & 3.0 at I386q (r1.6.1.3) & XMK35 (r2.3)
 * 	[90/11/15            rvb]
 * 
 * Revision 2.2  90/05/03  15:41:23  dbg
 * 	First checkin.
 * 
 * Revision 1.6.1.2  90/02/28  15:49:08  rvb
 * 	Fix numerous typo's in Olivetti disclaimer.
 * 	[90/02/28            rvb]
 * 
 * Revision 1.6.1.1  90/01/08  13:32:11  rvb
 * 	Add Olivetti copyright.
 * 	[90/01/08            rvb]
 * 
 * Revision 1.6  89/09/20  17:27:22  rvb
 * 	Revision 1.6  89/07/26  22:39:18  kupfer
 * 	tweaks, better support for user code that wants to use the 786.
 * 
 * Revision 1.5  89/07/07  17:56:13  kupfer
 * X79 merge, 2nd attempt.
 * 
 * Revision 1.4  89/03/09  20:05:08  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/26  12:41:37  gm0w
 * 	Changes for cleanup.
 * 
 */
 
/* **********************************************************************
 File:         blitvar.h
 Description:  Definitions used by Blit driver other than h/w definition.

 $ Header: $

 Copyright Ing. C. Olivetti & C. S.p.A. 1988, 1989.
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

#include <i386at/blitreg.h>
#include <sys/types.h>
#include <mach/boolean.h>


/* 
 * This is how we use the Blit's graphics memory.  The frame buffer 
 * goes at the front, and the rest is used for miscellaneous 
 * allocations.  Users can use the "spare" memory, but they should do 
 * an ioctl to find out which part of the memory is really free.
 */

struct blitmem {
	union blitfb {
		u_char mono_fb[BLIT_MONOFBSIZE];
		u_char color_fb[1];	/* place-holder */
	} fb;
	u_char spare[BLIT_MEMSIZE - sizeof(union blitfb)];
};


/*
 * Macro to get from blitdev pointer to monochrome framebuffer.
 */
#define       BLIT_MONOFB(blt, fbptr) \
	{ struct blitmem *mymem = (struct blitmem *)((blt)->graphmem); \
	fbptr = mymem->fb.mono_fb; \
	}


/* 
 * Single-tile description that can be used to describe the entire 
 * screen. 
 */

struct screen_descrip {
	STRIPHEADER strip;
	TILEDESC tile;
};


/* 
 * Number of microseconds we're willing to wait for display processor 
 * to load its command block.
 */

#define DP_RDYTIMEOUT			1000000


/* 
 * Conversion macros.
 */

#define VM_TO_ADDR786(vmaddr, blit_base) \
	((int)(vmaddr) - (int)(blit_base))


extern boolean_t blit_present();
extern void blit_init();
