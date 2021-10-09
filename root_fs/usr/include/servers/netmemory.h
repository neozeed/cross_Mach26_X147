#ifndef	_netmemory
#define	_netmemory

/* Module netmemory */

#include <mach/kern_return.h>
#if	(defined(__STDC__) || defined(c_plusplus)) || defined(LINTLIBRARY)
#include <mach/port.h>
#include <mach/message.h>
#endif

#ifndef	mig_external
#define mig_external extern
#endif

mig_external void init_netmemory
#if	(defined(__STDC__) || defined(c_plusplus))
    (port_t rep_port);
#else
    ();
#endif
#include <mach/mach_types.h>
#include "netmemory_defs.h"

/* Routine netmemory_create */
mig_external kern_return_t netmemory_create
#if	defined(LINTLIBRARY)
    (server_port, object_size, paging_object, control_port)
	port_t server_port;
	vm_size_t object_size;
	port_t *paging_object;
	port_t *control_port;
{ return netmemory_create(server_port, object_size, paging_object, control_port); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	port_t server_port,
	vm_size_t object_size,
	port_t *paging_object,
	port_t *control_port
);
#else
    ();
#endif
#endif

/* Routine netmemory_destroy */
mig_external kern_return_t netmemory_destroy
#if	defined(LINTLIBRARY)
    (control_port)
	port_t control_port;
{ return netmemory_destroy(control_port); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	port_t control_port
);
#else
    ();
#endif
#endif

/* Routine netmemory_cache */
mig_external kern_return_t netmemory_cache
#if	defined(LINTLIBRARY)
    (server_port, paging_object, local_paging_object)
	port_t server_port;
	port_t paging_object;
	port_t *local_paging_object;
{ return netmemory_cache(server_port, paging_object, local_paging_object); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	port_t server_port,
	port_t paging_object,
	port_t *local_paging_object
);
#else
    ();
#endif
#endif

/* Routine paging_object_server_statistics */
mig_external kern_return_t paging_object_server_statistics
#if	defined(LINTLIBRARY)
    (object_server, rusage, rusageCnt, faults_total, faults_totalCnt)
	port_t object_server;
	pointer_t *rusage;
	unsigned int *rusageCnt;
	pointer_t *faults_total;
	unsigned int *faults_totalCnt;
{ return paging_object_server_statistics(object_server, rusage, rusageCnt, faults_total, faults_totalCnt); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	port_t object_server,
	pointer_t *rusage,
	unsigned int *rusageCnt,
	pointer_t *faults_total,
	unsigned int *faults_totalCnt
);
#else
    ();
#endif
#endif

/* Routine netmemory_cover */
mig_external kern_return_t netmemory_cover
#if	defined(LINTLIBRARY)
    (server_port, object_data, object_dataCnt, paging_object, control_port)
	port_t server_port;
	pointer_t object_data;
	unsigned int object_dataCnt;
	port_t *paging_object;
	port_t *control_port;
{ return netmemory_cover(server_port, object_data, object_dataCnt, paging_object, control_port); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	port_t server_port,
	pointer_t object_data,
	unsigned int object_dataCnt,
	port_t *paging_object,
	port_t *control_port
);
#else
    ();
#endif
#endif

#endif	_netmemory
