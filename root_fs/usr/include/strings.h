/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)strings.h	5.3 (Berkeley) 11/18/87
 *
 **********************************************************************
 * HISTORY
 * $Log:	strings.h,v $
 * Revision 2.5  90/12/12  11:10:54  bww
 * 	Corrected erroneous use of "const" for strtok().
 * 	[90/12/12  11:08:22  bww]
 * 
 * Revision 2.4  90/10/22  12:14:55  bww
 * 	Corrected second parameter type (char -> int)
 * 	for index(), rindex(), strchr(), and strrchr().
 * 	[90/10/22  12:14:25  bww]
 * 
 * Revision 2.3  90/10/21  14:15:49  bww
 * 	Added definition for strerror().
 * 	[90/10/21  14:15:17  bww]
 * 
 * Revision 2.2  89/06/30  12:12:19  bww
 * 	Added function prototype declarations.
 * 	[89/06/30  12:02:40  bww]
 * 
 * Revision 1.2  89/05/26  12:28:08  bww
 * 	CMU CS as of 89/05/15
 * 	[89/05/26  09:46:50  bww]
 * 
 **********************************************************************
 */

/*
 * External function definitions
 * for routines described in string(3).
 */
#ifndef _STRINGS_H_
#define _STRINGS_H_ 1

#if __STDC__
extern char *strcat(char*, const char*);
extern char *strncat(char*, const char*, int);
extern int  strcmp(const char*, const char*);
extern int  strncmp(const char*, const char*, int);
extern int  strcasecmp(const char*, const char*);
extern int  strncasecmp(const char*, const char*, int);
extern char *strcpy(char*, const char*);
extern char *strncpy(char*, const char*, int);
extern int  strlen(const char*);
extern char *strerror(int);
extern char *index(const char*, int);
extern char *rindex(const char*, int);
#else
char	*strcat();
char	*strncat();
int	strcmp();
int	strncmp();
int	strcasecmp();
int	strncasecmp();
char	*strcpy();
char	*strncpy();
int	strlen();
char	*strerror();
char	*index();
char	*rindex();
#endif

/* S5 compatibility */
#if __STDC__
extern char *strchr(const char*, int);
extern char *strrchr(const char*, int);
extern char *strpbrk(const char*, const char*);
extern int  strspn(const char*, const char*);
extern int  strcspn(const char*, const char*);
extern char *strtok(char*, const char*);
#else
char	*strchr();
char	*strrchr();
char	*strpbrk();
int	strspn();
int	strcspn();
char	*strtok();
#endif
#endif /* _STRINGS_H_ */
