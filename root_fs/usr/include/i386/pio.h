/*
 * HISTORY
 * $Log:	pio.h,v $
 * Revision 1.1  91/05/09  13:39:21  jaap
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
 * $CMU-Log:	pio.h,v $
 * Revision 2.1.1.1  90/08/25  15:42:54  rvb
 * 	[90/08/14            mg32]
 * 
 * 	Now we know how types are factor in.
 * 	Cleaned up a bunch: eliminated ({ for output and flushed unused
 * 	output variables.
 * 	[90/08/14            rvb]
 * 
 * 	This is how its done in gcc:
 * 		Created.
 * 	[90/03/26            rvb]
 * 
 */

#ifdef	__GNUC__
#ifdef	__STDC__

#define inl(y) \
({ unsigned long _tmp__; \
	asm volatile("inl %1, %0" : "=a" (_tmp__) : "d" ((unsigned short)(y))); \
	_tmp__; })

#define inw(y) \
({ unsigned short _tmp__; \
	asm volatile(".byte 0x66; inl %1, %0" : "=a" (_tmp__) : "d" ((unsigned short)(y))); \
	_tmp__; })

#define inb(y) \
({ unsigned char _tmp__; \
	asm volatile("inb %1, %0" : "=a" (_tmp__) : "d" ((unsigned short)(y))); \
	_tmp__; })


#define outl(x, y) \
{ asm volatile("outl %0, %1" : : "a" (y) , "d" ((unsigned short)(x))); }


#define outw(x, y) \
{asm volatile(".byte 0x66; outl %0, %1" : : "a" ((unsigned short)(y)) , "d" ((unsigned short)(x))); }


#define outb(x, y) \
{ asm volatile("outb %0, %1" : : "a" ((unsigned char)(y)) , "d" ((unsigned short)(x))); }

#endif	/* __STDC__ */
#endif	/* __GNUC__ */
