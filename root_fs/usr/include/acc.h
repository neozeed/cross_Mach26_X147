/*
 *  see getacent(3)
 *
 **********************************************************************
 * HISTORY
 * $Log:	acc.h,v $
 * Revision 1.4  90/11/14  16:38:26  bww
 * 	setacent() returns a value.
 * 	[90/11/14  16:37:48  bww]
 * 
 * Revision 1.3  89/12/24  16:52:01  bww
 * 	Corrected __STDC__ usage.
 * 	[89/12/24  16:47:42  bww]
 * 
 * Revision 1.2  89/05/26  12:28:16  bww
 * 	CMU CS as of 89/05/15
 * 	[89/05/26  09:46:50  bww]
 * 
 * Revision 1.2  88/12/14  23:29:04  mja
 * 	Added declarations for __STDC__.
 * 	[88/01/06            jjk]
 * 
 * 11-Oct-85  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Add external declarations for account routines.  Change
 *	ac_passwd to ac_attrs for new accounting file information.
 *
 **********************************************************************
 */

struct	account
{
	char	*ac_name;
	char	**ac_attrs;
	int	 ac_uid;
	int	 ac_aid;
	char	*ac_created;
	char	*ac_expires;
	char	*ac_sponsor;
	time_t	 ac_ctime;
	time_t	 ac_xtime;
};

#if __STDC__
extern struct account *getacent(void);
extern struct account *getacauid(int, int);
extern struct account *getacanam(const char *, int);
extern int setacent(void);
extern void endacent(void);
#else
struct account *getacent(), *getacauid(), *getacanam();
#endif
