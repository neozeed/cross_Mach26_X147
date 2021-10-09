/*	grp.h	4.1	83/05/03	*/
/*
 **********************************************************************
 * HISTORY
 * $Log:	grp.h,v $
 * Revision 2.2  89/06/30  12:10:48  bww
 * 	Added function prototype declarations.
 * 	[89/06/30  11:56:43  bww]
 * 
 * Revision 1.2  89/05/26  12:26:48  bww
 * 	CMU CS as of 89/05/15
 * 	[89/05/26  09:46:50  bww]
 * 
 **********************************************************************
 */

struct	group { /* see getgrent(3) */
	char	*gr_name;
	char	*gr_passwd;
	int	gr_gid;
	char	**gr_mem;
};

#if __STDC__
extern struct group *getgrent(void);
extern struct group *getgrgid(int);
extern struct group *getgrnam(const char*);
extern void setgrent(void);
extern void endgrent(void);
#else
struct group *getgrent(), *getgrgid(), *getgrnam();
#endif
