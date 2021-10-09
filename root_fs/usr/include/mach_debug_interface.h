#ifndef	_mach_debug
#define	_mach_debug

/* Module mach_debug */

#include <mach/kern_return.h>
#if	(defined(__STDC__) || defined(c_plusplus)) || defined(LINTLIBRARY)
#include <mach/port.h>
#include <mach/message.h>
#endif

#ifndef	mig_external
#define mig_external extern
#endif

mig_external void init_mach_debug
#if	(defined(__STDC__) || defined(c_plusplus))
    (port_t rep_port);
#else
    ();
#endif
#include <mach/std_types.h>
#include <mach/mach_types.h>
#include <mach_debug/mach_debug_types.h>

/* Routine host_ipc_statistics */
mig_external kern_return_t host_ipc_statistics
#if	defined(LINTLIBRARY)
    (task, statistics)
	task_t task;
	ipc_statistics_t *statistics;
{ return host_ipc_statistics(task, statistics); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	task_t task,
	ipc_statistics_t *statistics
);
#else
    ();
#endif
#endif

/* Routine host_ipc_statistics_reset */
mig_external kern_return_t host_ipc_statistics_reset
#if	defined(LINTLIBRARY)
    (task)
	task_t task;
{ return host_ipc_statistics_reset(task); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	task_t task
);
#else
    ();
#endif
#endif

/* Routine host_callout_info */
mig_external kern_return_t host_callout_info
#if	defined(LINTLIBRARY)
    (task, info, infoCnt)
	task_t task;
	callout_info_array_t *info;
	unsigned int *infoCnt;
{ return host_callout_info(task, info, infoCnt); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	task_t task,
	callout_info_array_t *info,
	unsigned int *infoCnt
);
#else
    ();
#endif
#endif

/* Routine host_callout_statistics */
mig_external kern_return_t host_callout_statistics
#if	defined(LINTLIBRARY)
    (task, statistics)
	task_t task;
	callout_statistics_t *statistics;
{ return host_callout_statistics(task, statistics); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	task_t task,
	callout_statistics_t *statistics
);
#else
    ();
#endif
#endif

/* Routine host_callout_statistics_reset */
mig_external kern_return_t host_callout_statistics_reset
#if	defined(LINTLIBRARY)
    (task)
	task_t task;
{ return host_callout_statistics_reset(task); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	task_t task
);
#else
    ();
#endif
#endif

/* Routine host_zone_info */
mig_external kern_return_t host_zone_info
#if	defined(LINTLIBRARY)
    (task, names, namesCnt, info, infoCnt)
	task_t task;
	zone_name_array_t *names;
	unsigned int *namesCnt;
	zone_info_array_t *info;
	unsigned int *infoCnt;
{ return host_zone_info(task, names, namesCnt, info, infoCnt); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	task_t task,
	zone_name_array_t *names,
	unsigned int *namesCnt,
	zone_info_array_t *info,
	unsigned int *infoCnt
);
#else
    ();
#endif
#endif

/* Routine host_ipc_bucket_info */
mig_external kern_return_t host_ipc_bucket_info
#if	defined(LINTLIBRARY)
    (task, TLinfo, TLinfoCnt, TPinfo, TPinfoCnt)
	task_t task;
	ipc_bucket_info_array_t *TLinfo;
	unsigned int *TLinfoCnt;
	ipc_bucket_info_array_t *TPinfo;
	unsigned int *TPinfoCnt;
{ return host_ipc_bucket_info(task, TLinfo, TLinfoCnt, TPinfo, TPinfoCnt); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	task_t task,
	ipc_bucket_info_array_t *TLinfo,
	unsigned int *TLinfoCnt,
	ipc_bucket_info_array_t *TPinfo,
	unsigned int *TPinfoCnt
);
#else
    ();
#endif
#endif

#endif	_mach_debug
