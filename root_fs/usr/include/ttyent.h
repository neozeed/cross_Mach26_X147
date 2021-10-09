/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)ttyent.h	5.1 (Berkeley) 5/30/85
 *
 **********************************************************************
 * HISTORY
 * $Log:	ttyent.h,v $
 * Revision 2.2  89/06/30  12:12:32  bww
 * 	Added function prototype declarations.
 * 	[89/06/30  12:03:21  bww]
 * 
 * Revision 1.2  89/05/26  12:27:48  bww
 * 	CMU CS as of 89/05/15
 * 	[89/05/26  09:46:50  bww]
 * 
 **********************************************************************
 */

struct	ttyent { /* see getttyent(3) */
	char	*ty_name;	/* terminal device name */
	char	*ty_getty;	/* command to execute, usually getty */
	char	*ty_type;	/* terminal type for termcap (3X) */
	int	ty_status;	/* status flags (see below for defines) */
	char 	*ty_window;	/* command to start up window manager */
	char	*ty_comment;	/* usually the location of the terminal */
};

#define TTY_ON		0x1	/* enable logins (startup getty) */
#define TTY_SECURE	0x2	/* allow root to login */

#if __STDC__
extern struct ttyent *getttyent(void);
extern struct ttyent *getttynam(const char*);
extern void setttyent(void);
extern void endttyent(void);
#else
extern struct ttyent *getttyent();
extern struct ttyent *getttynam();
#endif
