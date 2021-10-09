
/*
 * Copyright (c) 1983, 1987 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)resolv.h	5.5 (Berkeley) 5/12/87
 */

/*
 * Global defines and variables for resolver stub.
 **********************************************************************
 * HISTORY
 * $Log:	resolv.h,v $
 * Revision 2.4  90/11/16  19:43:07  bww
 * 	Protected against multiple includes, and
 * 	corrected return type of res_init().
 * 	[90/11/16  19:42:26  bww]
 * 
 * Revision 2.3  90/02/11  16:04:25  bww
 * 	Restored unconditional definition of RES_DEFAULT.
 * 	[90/02/11  16:04:03  bww]
 * 
 * Revision 2.2  89/06/30  12:11:51  bww
 * 	Added function prototype declarations and CMU specific
 * 	definitions.
 * 	[89/06/30  12:00:36  bww]
 * 
 * Revision 1.2  89/05/26  12:27:55  bww
 * 	CMU CS as of 89/05/15
 * 	[89/05/26  09:46:50  bww]
 * 
 **********************************************************************
 */

#ifndef	_RESOLV_H_
#define	_RESOLV_H_

#define	MAXNS		3		/* max # name servers we'll track */
#define	MAXDNSRCH	3		/* max # default domain levels to try */
#define	LOCALDOMAINPARTS 2		/* min levels in name that is "local" */

#define	RES_TIMEOUT	4		/* seconds between retries */

struct state {
	int	retrans;	 	/* retransmition time interval */
	int	retry;			/* number of times to retransmit */
	long	options;		/* option flags - see below. */
	int	nscount;		/* number of name servers */
	struct	sockaddr_in nsaddr_list[MAXNS];	/* address of name server */
#define	nsaddr	nsaddr_list[0]		/* for backward compatibility */
	u_short	id;			/* current packet id */
	char	defdname[MAXDNAME];	/* default domain */
	char	*dnsrch[MAXDNSRCH+1];	/* components of domain to search */
};

/*
 * Resolver options
 */
#define RES_INIT	0x0001		/* address initialized */
#define RES_DEBUG	0x0002		/* print debug messages */
#define RES_AAONLY	0x0004		/* authoritative answers only */
#define RES_USEVC	0x0008		/* use virtual circuit */
#define RES_PRIMARY	0x0010		/* query primary server only */
#define RES_IGNTC	0x0020		/* ignore trucation errors */
#define RES_RECURSE	0x0040		/* recursion desired */
#define RES_DEFNAMES	0x0080		/* use default domain name */
#define RES_STAYOPEN	0x0100		/* Keep TCP socket open */
#define RES_DNSRCH	0x0200		/* search up local domain tree */
#if	CMU
#define RES_RESPORT	0x010000	/* Use resolver port for query */
#endif	/* CMU */

#define RES_DEFAULT	(RES_RECURSE | RES_DEFNAMES | RES_DNSRCH)

extern struct state _res;
#if __STDC__
#include <stdio.h>
#include <arpa/nameser.h>
extern char *p_cdname(char *, char *, FILE *);
extern char *p_rr(char *, char *, FILE *);
extern char *p_type(int);
extern char *p_class(int);
extern int res_mkquery(int, char *, int, int, char *, int,
			struct rrec *, char *, int);
extern int res_send(char *, int, char *, int);
extern int res_init(void);
extern int dn_comp(char *, char *, int, char **, char **);
extern int dn_expand(char *, char *, char *, char *, int);
#else
extern char *p_cdname(), *p_rr(), *p_type(), *p_class();
#endif

#endif	/* _RESOLV_H_ */
