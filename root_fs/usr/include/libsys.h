/*
 ****************************************************************************
 * HISTORY
 * $Log:	libsys.h,v $
 * Revision 1.2  90/02/02  09:42:50  bww
 * 	CMU CS as of 90/02/01
 * 	[90/02/02  09:42:45  bww]
 * 
 * Revision 2.2  90/02/01  16:13:42  mja
 * 	Created.
 * 	[90/02/01  11:31:01  mja]
 * 
 ****************************************************************************
 */

#ifndef	_LIBSYS_H_
#define	_LIBSYS_H_	1



/*
 *  System/environment dependent subroutines
 */

extern int   chkopr();
extern int   getmodes();
extern char *hardcrypt();
extern int   isopr();
extern int   logaccess();
extern int   okaccess();
extern int   oklogin();
extern char *okpasswd();
extern char *okpassword();
extern int   setmodes();
extern char *ttyloc();
extern char *ttywhere();
extern int   warnlogin();


/* okpasswd() option flags */
#define	OKPSWD_ALL	0x0	/* apply all password checks */
#define	OKPSWD_NOVERS	0x1	/* omit encryption version check */




/*
 *  Non-standard system calls
 */

extern int   icreate();
extern int   idec();
extern int   iinc();
extern int   iopen();
extern int   iread();
extern int   iwrite();
extern int   pioctl();
extern int   rpause();
extern int   setpag();
extern int   table();



#endif	/* not _LIBSYS_H_ */
