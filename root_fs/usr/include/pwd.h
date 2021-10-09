/*	pwd.h	4.1	83/05/03	*/
/*
 **********************************************************************
 * HISTORY
 * $Log:	pwd.h,v $
 * Revision 2.2  89/06/30  12:11:45  bww
 * 	Added function prototype declarations.
 * 	[89/06/30  11:59:59  bww]
 * 
 * Revision 1.2  89/05/26  12:27:29  bww
 * 	CMU CS as of 89/05/15
 * 	[89/05/26  09:46:50  bww]
 * 
 **********************************************************************
 */

struct	passwd { /* see getpwent(3) */
	char	*pw_name;
	char	*pw_passwd;
	int	pw_uid;
	int	pw_gid;
	int	pw_quota;
	char	*pw_comment;
	char	*pw_gecos;
	char	*pw_dir;
	char	*pw_shell;
};

#if __STDC__
extern struct passwd *getpwent (void);
extern struct passwd *getpwuid (int);
extern struct passwd *getpwnam (const char*);

extern void setpwent (void);
extern void endpwent (void);
extern void setpwfile (const char*);
#else
struct passwd *getpwent(), *getpwuid(), *getpwnam();
#endif
