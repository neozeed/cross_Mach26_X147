/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)vfont.h	5.1 (Berkeley) 5/30/85
 */
#if     CMU
/*
 **********************************************************************
 * HISTORY
 * $Log:	vfont.h,v $
 * Revision 2.2  89/06/26  20:20:51  bww
 * 	Merged SUN3 changes into 4.3-tahoe version.
 * 	[89/06/26  20:19:10  bww]
 * 
 * 14-Dec-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *      Created from Sun's version of vfont.h.
 *
 **********************************************************************
 */
#endif	CMU

/*
 * The structures header and dispatch define the format of a font file.
 *
 * See vfont(5) for more details.
 */
struct header {
	short magic;
	unsigned short size;
	short maxx;
	short maxy;
	short xtend;
}; 

struct dispatch {
	unsigned short addr;
	short nbytes;
	char up,down,left,right;
	short width;
};

#if     sun
#define VFONT_MAGIC     0436
#define NUM_DISPATCH    256
#endif  sun
