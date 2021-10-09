/*
 * Copyright (c) 1983, 1987 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)time.h	1.2 (Berkeley) 3/4/87
 *
 **********************************************************************
 * HISTORY
 * $Log:	time.h,v $
 * Revision 2.4  90/11/15  18:39:47  bww
 * 	Corrected declaration for mktime().
 * 	[90/11/15  18:39:12  bww]
 * 
 * Revision 2.3  89/12/11  11:00:05  bww
 * 	Added defines for TM_GMTOFF and TM_ZONE to indicate the
 * 	presence of the respective fields.  Added declarations
 * 	for ANSIish difftime(), mktime(), and strftime().
 * 	[89/12/11  10:59:44  bww]
 * 
 * Revision 2.2  89/06/30  12:12:25  bww
 * 	Added function prototype declarations and protection for
 * 	recursive includes.
 * 	[89/06/30  12:03:07  bww]
 * 
 * Revision 1.2  89/05/26  12:28:50  bww
 * 	CMU CS as of 89/05/15
 * 	[89/05/26  09:46:50  bww]
 * 
 **********************************************************************
 */

#ifndef	_TIME_H_
#define	_TIME_H_ 1
/*
 * Structure returned by gmtime and localtime calls (see ctime(3)).
 */
struct tm {
	int	tm_sec;
	int	tm_min;
	int	tm_hour;
	int	tm_mday;
	int	tm_mon;
	int	tm_year;
	int	tm_wday;
	int	tm_yday;
	int	tm_isdst;
	long	tm_gmtoff;
	char	*tm_zone;
};

#define	TM_GMTOFF	tm_gmtoff
#define	TM_ZONE		tm_zone

#if __STDC__
extern long time(long*);
extern char *ctime(long*);
extern char *asctime(struct tm*);
extern struct tm *gmtime(long*);
extern struct tm *localtime(long*);
extern double difftime(long, long);
extern long mktime(struct tm*);
extern long strftime(char*, long, char*, struct tm*);
#else
extern	struct tm *gmtime(), *localtime();
extern	char *asctime(), *ctime();
extern	long time(), mktime(), strftime();
extern	double difftime();
#endif
#endif /* _TIME_H_ */
