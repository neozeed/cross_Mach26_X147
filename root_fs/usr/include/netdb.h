/*
 * Copyright (c) 1980, 1983, 1988 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	@(#)netdb.h	5.10 (Berkeley) 6/27/88
 *
 **********************************************************************
 * HISTORY
 * $Log:	netdb.h,v $
 * Revision 2.4  90/10/30  11:55:02  bww
 * 	Protect whole file and definition of "struct rpcent".
 * 	[90/10/30  11:54:50  bww]
 * 
 * Revision 2.3  89/10/03  16:11:15  bww
 * 	Added declarations for getrpcent() routines.
 * 	[89/10/03  16:11:02  bww]
 * 
 * Revision 2.2  89/06/30  12:11:22  bww
 * 	Added function prototype declarations.
 * 	[89/06/30  11:58:54  bww]
 * 
 * Revision 1.2  89/05/26  12:29:29  bww
 * 	CMU CS as of 89/05/15
 * 	[89/05/26  09:46:50  bww]
 * 
 **********************************************************************
 */

#ifndef	_NETDB_H_
#define	_NETDB_H_

/*
 * Structures returned by network
 * data base library.  All addresses
 * are supplied in host order, and
 * returned in network order (suitable
 * for use in system calls).
 */
struct	hostent {
	char	*h_name;	/* official name of host */
	char	**h_aliases;	/* alias list */
	int	h_addrtype;	/* host address type */
	int	h_length;	/* length of address */
	char	**h_addr_list;	/* list of addresses from name server */
#define	h_addr	h_addr_list[0]	/* address, for backward compatiblity */
};

/*
 * Assumption here is that a network number
 * fits in 32 bits -- probably a poor one.
 */
struct	netent {
	char		*n_name;	/* official name of net */
	char		**n_aliases;	/* alias list */
	int		n_addrtype;	/* net address type */
	unsigned long	n_net;		/* network # */
};

struct	servent {
	char	*s_name;	/* official service name */
	char	**s_aliases;	/* alias list */
	int	s_port;		/* port # */
	char	*s_proto;	/* protocol to use */
};

struct	protoent {
	char	*p_name;	/* official protocol name */
	char	**p_aliases;	/* alias list */
	int	p_proto;	/* protocol # */
};

#ifndef	_RPCENT_DEFINED_
#define	_RPCENT_DEFINED_
struct rpcent {
	char	*r_name;	/* name of server for this rpc program */
	char	**r_aliases;	/* alias list */
	int	r_number;	/* rpc program number */
};
#endif	/* _RPCENT_DEFINED_ */

#if __STDC__
extern struct hostent  *gethostbyname(const char*);
extern struct hostent  *gethostbyaddr(const char*, int, int);
extern struct hostent  *gethostent(void);
extern struct netent   *getnetbyname(const char*);
extern struct netent   *getnetbyaddr(long, int);
extern struct netent   *getnetent(void);
extern struct servent  *getservbyname(const char*, const char*);
extern struct servent  *getservbyport(int, const char*);
extern struct servent  *getservent(void);
extern struct protoent *getprotobyname(const char*);
extern struct protoent *getprotobynumber(int);
extern struct protoent *getprotoent(void);
extern struct rpcent   *getrpcbyname(const char*);
extern struct rpcent   *getrpcbynumber(int);
extern struct rpcent   *getrpcent(void);
extern void sethostent(int);
extern void endhostent(void);
#else
struct hostent	*gethostbyname(), *gethostbyaddr(), *gethostent();
struct netent	*getnetbyname(), *getnetbyaddr(), *getnetent();
struct servent	*getservbyname(), *getservbyport(), *getservent();
struct protoent	*getprotobyname(), *getprotobynumber(), *getprotoent();
struct rpcent	*getrpcbyname(), *getrpcbynumber(), *getrpcent();
#endif

/*
 * Error return codes from gethostbyname() and gethostbyaddr()
 * (left in extern int h_errno).
 */

#define	HOST_NOT_FOUND	1 /* Authoritative Answer Host not found */
#define	TRY_AGAIN	2 /* Non-Authoritive Host not found, or SERVERFAIL */
#define	NO_RECOVERY	3 /* Non recoverable errors, FORMERR, REFUSED, NOTIMP */
#define	NO_DATA		4 /* Valid name, no data record of requested type */
#define	NO_ADDRESS	NO_DATA		/* no address, look for MX record */

#endif	/* _NETDB_H_ */
