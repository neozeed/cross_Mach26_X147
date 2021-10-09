#ifndef	_env_mgr
#define	_env_mgr

/* Module env_mgr */

#include <mach/kern_return.h>
#if	(defined(__STDC__) || defined(c_plusplus)) || defined(LINTLIBRARY)
#include <mach/port.h>
#include <mach/message.h>
#endif

#ifndef	mig_external
#define mig_external extern
#endif

mig_external void init_env_mgr
#if	(defined(__STDC__) || defined(c_plusplus))
    (port_t rep_port);
#else
    ();
#endif
#include <mach/std_types.h>
#include <servers/emdefs.h>

/* Routine env_set_string */
mig_external kern_return_t env_set_string
#if	defined(LINTLIBRARY)
    (port, env_name, env_val)
	port_t port;
	env_name_t env_name;
	env_str_val_t env_val;
{ return env_set_string(port, env_name, env_val); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	port_t port,
	env_name_t env_name,
	env_str_val_t env_val
);
#else
    ();
#endif
#endif

/* Routine env_get_string */
mig_external kern_return_t env_get_string
#if	defined(LINTLIBRARY)
    (port, env_name, env_val)
	port_t port;
	env_name_t env_name;
	env_str_val_t env_val;
{ return env_get_string(port, env_name, env_val); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	port_t port,
	env_name_t env_name,
	env_str_val_t env_val
);
#else
    ();
#endif
#endif

/* Routine env_del_string */
mig_external kern_return_t env_del_string
#if	defined(LINTLIBRARY)
    (port, env_name)
	port_t port;
	env_name_t env_name;
{ return env_del_string(port, env_name); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	port_t port,
	env_name_t env_name
);
#else
    ();
#endif
#endif

/* Routine env_set_port */
mig_external kern_return_t env_set_port
#if	defined(LINTLIBRARY)
    (port, env_name, env_val)
	port_t port;
	env_name_t env_name;
	port_t env_val;
{ return env_set_port(port, env_name, env_val); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	port_t port,
	env_name_t env_name,
	port_t env_val
);
#else
    ();
#endif
#endif

/* Routine env_get_port */
mig_external kern_return_t env_get_port
#if	defined(LINTLIBRARY)
    (port, env_name, env_val)
	port_t port;
	env_name_t env_name;
	port_t *env_val;
{ return env_get_port(port, env_name, env_val); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	port_t port,
	env_name_t env_name,
	port_t *env_val
);
#else
    ();
#endif
#endif

/* Routine env_del_port */
mig_external kern_return_t env_del_port
#if	defined(LINTLIBRARY)
    (port, env_name)
	port_t port;
	env_name_t env_name;
{ return env_del_port(port, env_name); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	port_t port,
	env_name_t env_name
);
#else
    ();
#endif
#endif

/* Routine env_list_strings */
mig_external kern_return_t env_list_strings
#if	defined(LINTLIBRARY)
    (port, env_names, env_namesCnt, env_string_vals, env_string_valsCnt)
	port_t port;
	env_name_list *env_names;
	unsigned int *env_namesCnt;
	env_str_list *env_string_vals;
	unsigned int *env_string_valsCnt;
{ return env_list_strings(port, env_names, env_namesCnt, env_string_vals, env_string_valsCnt); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	port_t port,
	env_name_list *env_names,
	unsigned int *env_namesCnt,
	env_str_list *env_string_vals,
	unsigned int *env_string_valsCnt
);
#else
    ();
#endif
#endif

/* Routine env_list_ports */
mig_external kern_return_t env_list_ports
#if	defined(LINTLIBRARY)
    (port, env_names, env_namesCnt, env_ports_vals, env_ports_valsCnt)
	port_t port;
	env_name_list *env_names;
	unsigned int *env_namesCnt;
	port_array_t *env_ports_vals;
	unsigned int *env_ports_valsCnt;
{ return env_list_ports(port, env_names, env_namesCnt, env_ports_vals, env_ports_valsCnt); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	port_t port,
	env_name_list *env_names,
	unsigned int *env_namesCnt,
	port_array_t *env_ports_vals,
	unsigned int *env_ports_valsCnt
);
#else
    ();
#endif
#endif

/* Routine env_set_stlist */
mig_external kern_return_t env_set_stlist
#if	defined(LINTLIBRARY)
    (port, env_names, env_namesCnt, env_string_vals, env_string_valsCnt)
	port_t port;
	env_name_list env_names;
	unsigned int env_namesCnt;
	env_str_list env_string_vals;
	unsigned int env_string_valsCnt;
{ return env_set_stlist(port, env_names, env_namesCnt, env_string_vals, env_string_valsCnt); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	port_t port,
	env_name_list env_names,
	unsigned int env_namesCnt,
	env_str_list env_string_vals,
	unsigned int env_string_valsCnt
);
#else
    ();
#endif
#endif

/* Routine env_set_ptlist */
mig_external kern_return_t env_set_ptlist
#if	defined(LINTLIBRARY)
    (port, env_names, env_namesCnt, env_ports_vals, env_ports_valsCnt)
	port_t port;
	env_name_list env_names;
	unsigned int env_namesCnt;
	port_array_t env_ports_vals;
	unsigned int env_ports_valsCnt;
{ return env_set_ptlist(port, env_names, env_namesCnt, env_ports_vals, env_ports_valsCnt); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	port_t port,
	env_name_list env_names,
	unsigned int env_namesCnt,
	port_array_t env_ports_vals,
	unsigned int env_ports_valsCnt
);
#else
    ();
#endif
#endif

/* Routine env_copy_conn */
mig_external kern_return_t env_copy_conn
#if	defined(LINTLIBRARY)
    (port, new_env_port)
	port_t port;
	port_t *new_env_port;
{ return env_copy_conn(port, new_env_port); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	port_t port,
	port_t *new_env_port
);
#else
    ();
#endif
#endif

/* Routine env_new_conn */
mig_external kern_return_t env_new_conn
#if	defined(LINTLIBRARY)
    (port, new_env_port)
	port_t port;
	port_t *new_env_port;
{ return env_new_conn(port, new_env_port); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	port_t port,
	port_t *new_env_port
);
#else
    ();
#endif
#endif

/* Routine env_restrict_conn */
mig_external kern_return_t env_restrict_conn
#if	defined(LINTLIBRARY)
    (port, new_env_port)
	port_t port;
	port_t *new_env_port;
{ return env_restrict_conn(port, new_env_port); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	port_t port,
	port_t *new_env_port
);
#else
    ();
#endif
#endif

/* Routine env_disconnect */
mig_external kern_return_t env_disconnect
#if	defined(LINTLIBRARY)
    (port)
	port_t port;
{ return env_disconnect(port); }
#else
#if	(defined(__STDC__) || defined(c_plusplus))
(
	port_t port
);
#else
    ();
#endif
#endif

#endif	_env_mgr
