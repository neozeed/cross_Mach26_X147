/*
 * HISTORY
 * $Log:	paths.h,v $
 * Revision 2.4  90/10/04  13:31:27  bww
 * 	Added entries for MAILDIR, MAN, NOLOGIN, UTMP, and VARTMP.
 * 	[90/10/04  13:31:00  bww]
 * 
 */
/*
 * Copyright (c) 1989 The Regents of the University of California.
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	@(#)paths.h	5.2 (Berkeley) 6/4/89
 */

#define	_PATH_BSHELL	"/bin/sh"
#define	_PATH_CONSOLE	"/dev/console"
#define	_PATH_CSHELL	"/bin/csh"
#define	_PATH_DEV	"/dev/"
#define	_PATH_DEVNULL	"/dev/null"
#define	_PATH_DRUM	"/dev/drum"
#define	_PATH_KMEM	"/dev/kmem"
#define	_PATH_MAILDIR	"/usr/spool/mail"
#define	_PATH_MAN	"/usr/man"
#define	_PATH_MEM	"/dev/mem"
#define	_PATH_NOLOGIN	"/etc/nologin"
#define	_PATH_SENDMAIL	"/usr/lib/sendmail"
#define	_PATH_TMP	"/tmp/"
#define	_PATH_TTY	"/dev/tty"
#define	_PATH_UNIX	"/vmunix"
#define	_PATH_UTMP	"/etc/utmp"
#define	_PATH_VARTMP	"/usr/tmp"
#define	_PATH_VI	"/usr/ucb/vi"
