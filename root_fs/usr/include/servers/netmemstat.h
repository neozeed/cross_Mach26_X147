#ifndef	_netmemstat
#define	_netmemstat

/* Module netmemstat */

#include <mach/kern_return.h>
#if	(defined(__STDC__) || defined(c_plusplus)) || defined(LINTLIBRARY)
#include <mach/port.h>
#include <mach/message.h>
#endif

#ifndef	mig_external
#define mig_external extern
#endif

mig_external void init_netmemstat
#if	(defined(__STDC__) || defined(c_plusplus))
    (port_t rep_port);
#else
    ();
#endif
#include "mach/mach_types.h"
#include "netmemory_defs.h"

/* Routine paging_object_statistics */
mig_external kern_return_t paging_object_statistics
#if	defined(LINTLIBRARY)
    (paging_object, faults_per_page, faults_per_pageCnt, faults_total, faults_totalCnt)
	port_t paging_object;
	pointer_t *faults_per_page;
	unsigned int *faults_per_pageCnt;
	pointer_t *faults_total;
	unsigned int *faults_totalCnt;
{ return paging_object_statistics(paging_object, faults_per_page, faults_per_pageCnt, faults_total, faults_totalCnt); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	port_t paging_object,
	pointer_t *faults_per_page,
	unsigned int *faults_per_pageCnt,
	pointer_t *faults_total,
	unsigned int *faults_totalCnt
);
#else
    ();
#endif
#endif

#endif	_netmemstat
