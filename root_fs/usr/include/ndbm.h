/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)ndbm.h	5.1 (Berkeley) 5/30/85
 *
 **********************************************************************
 * HISTORY
 * $Log:	ndbm.h,v $
 * Revision 2.2  89/06/30  12:11:16  bww
 * 	Added function prototype declarations and protection for
 * 	recursive includes.
 * 	[89/06/30  11:58:40  bww]
 * 
 * Revision 1.2  89/05/26  12:27:22  bww
 * 	CMU CS as of 89/05/15
 * 	[89/05/26  09:46:50  bww]
 * 
 **********************************************************************
 */

/*
 * Hashed key data base library.
 */
#ifndef _NDBM_H_
#define _NDBM_H_ 1

#define PBLKSIZ 1024
#define DBLKSIZ 4096

typedef struct {
	int	dbm_dirf;		/* open directory file */
	int	dbm_pagf;		/* open page file */
	int	dbm_flags;		/* flags, see below */
	long	dbm_maxbno;		/* last ``bit'' in dir file */
	long	dbm_bitno;		/* current bit number */
	long	dbm_hmask;		/* hash mask */
	long	dbm_blkptr;		/* current block for dbm_nextkey */
	int	dbm_keyptr;		/* current key for dbm_nextkey */
	long	dbm_blkno;		/* current page to read/write */
	long	dbm_pagbno;		/* current page in pagbuf */
	char	dbm_pagbuf[PBLKSIZ];	/* page file block buffer */
	long	dbm_dirbno;		/* current block in dirbuf */
	char	dbm_dirbuf[DBLKSIZ];	/* directory file block buffer */
} DBM;

#define _DBM_RDONLY	0x1	/* data base open read-only */
#define _DBM_IOERR	0x2	/* data base I/O error */

#define dbm_rdonly(db)	((db)->dbm_flags & _DBM_RDONLY)

#define dbm_error(db)	((db)->dbm_flags & _DBM_IOERR)
	/* use this one at your own risk! */
#define dbm_clearerr(db)	((db)->dbm_flags &= ~_DBM_IOERR)

/* for flock(2) and fstat(2) */
#define dbm_dirfno(db)	((db)->dbm_dirf)
#define dbm_pagfno(db)	((db)->dbm_pagf)

typedef struct {
	char	*dptr;
	int	dsize;
} datum;

/*
 * flags to dbm_store()
 */
#define DBM_INSERT	0
#define DBM_REPLACE	1

#if __STDC__
extern DBM	*dbm_open(char*, int, int);
extern void	dbm_close(DBM*);
extern datum	dbm_fetch(DBM*, datum);
extern datum	dbm_firstkey(DBM*);
extern datum	dbm_nextkey(DBM*);
extern long	dbm_forder(DBM*, datum);
extern int	dbm_delete(DBM*, datum);
extern int	dbm_store(DBM*, datum, datum, int);
#else
DBM	*dbm_open();
void	dbm_close();
datum	dbm_fetch();
datum	dbm_firstkey();
datum	dbm_nextkey();
long	dbm_forder();
int	dbm_delete();
int	dbm_store();
#endif
#endif /* _NDBM_H_ */
