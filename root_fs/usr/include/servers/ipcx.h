#ifndef	_ipcx
#define	_ipcx

/* Module ipcx */

#include <mach/kern_return.h>
#if	(defined(__STDC__) || defined(c_plusplus)) || defined(LINTLIBRARY)
#include <mach/port.h>
#include <mach/message.h>
#endif

#ifndef	mig_external
#define mig_external extern
#endif

mig_external void init_ipcx
#if	(defined(__STDC__) || defined(c_plusplus))
    (port_t rep_port);
#else
    ();
#endif
#include <servers/ipcx_types.h>

/* Routine startserver */
mig_external kern_return_t startserver
#if	defined(LINTLIBRARY)
    (mPort, userid, password, commandline, serverkport, serverdport)
	port_t mPort;
	a_string userid;
	a_string password;
	a_string commandline;
	port_t *serverkport;
	port_t *serverdport;
{ return startserver(mPort, userid, password, commandline, serverkport, serverdport); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	port_t mPort,
	a_string userid,
	a_string password,
	a_string commandline,
	port_t *serverkport,
	port_t *serverdport
);
#else
    ();
#endif
#endif

#endif	_ipcx
