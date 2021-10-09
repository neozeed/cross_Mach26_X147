/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	map.h,v $
 * Revision 2.7  92/02/04  21:18:35  mja
 * 	Changed some conditionals from sun4c to sun4 to ease porting of
 * 	some drivers.
 * 	[92/02/02            berman]
 * 
 * Revision 2.6  90/12/17  17:21:34  berman
 * 	Added some SPARCstation definitions.
 * 	[90/11/09            berman]
 * 
 * Revision 2.5  89/03/09  22:05:30  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  17:54:36  gm0w
 * 	Got rid of MACH conditionals and the non-MACH code.
 * 	[89/02/13            mrt]
 * 
 * Revision 2.3  88/08/24  02:34:31  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:16:39  mwyoung]
 * 
 * 17-Aug-87  David Golub (dbg) at Carnegie-Mellon University
 *	MACH: Replaced user_pt_map by kernel_pageable_map.
 *	Removed swapmap, nswapmap, argmap (not used).
 *
 * 25-Feb-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Installed VM changes.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)map.h	7.1 (Berkeley) 6/4/86
 */

/*
 * Resource Allocation Maps.
 *
 * Associated routines manage sub-allocation of an address space using
 * an array of segment descriptors.  The first element of this array
 * is a map structure, describing the arrays extent and the name
 * of the controlled object.  Each additional structure represents
 * a free segment of the address space.
 *
 * A call to rminit initializes a resource map and may also be used
 * to free some address space for the map.  Subsequent calls to rmalloc
 * and rmfree allocate and free space in the resource map.  If the resource
 * map becomes too fragmented to be described in the available space,
 * then some of the resource is discarded.  This may lead to critical
 * shortages, but is better than not checking (as the previous versions
 * of these routines did) or giving up and calling panic().  The routines
 * could use linked lists and call a memory allocator when they run
 * out of space, but that would not solve the out of space problem when
 * called at interrupt time.
 *
 * N.B.: The address 0 in the resource address space is not available
 * as it is used internally by the resource map routines.
 */

#ifndef	_SYS_MAP_H_
#define _SYS_MAP_H_

struct map {
	struct	mapent *m_limit;	/* address of last slot in map */
	char	*m_name;		/* name of resource */
/* we use m_name when the map overflows, in warning messages */
#ifdef	sun4
        unsigned int m_free;            /* number of free slots in map */
        unsigned int m_want;            /* # of processes sleeping on map */
#endif	sun4
};
struct mapent
{
	int	m_size;		/* size of this segment of the map */
	int	m_addr;		/* resource-space addr of start of segment */
};

#ifdef	KERNEL
#include <vm/vm_map.h>

extern vm_map_t	kernel_pageable_map;
extern vm_map_t	mb_map;
#endif	KERNEL
#ifdef	sun4
#define mapstart(X)     (struct mapent *)((X)+1)
#define mapfree(X)      (X)->m_free
#define mapwant(X)      (X)->m_want
#endif	sun4
#endif	_SYS_MAP_H_
