/*
 **********************************************************************
 * HISTORY
 * $Log:	sysent.h,v $
 * Revision 1.4  90/11/17  16:33:59  bww
 * 	Removed AFS i*() declarations.
 * 	[90/11/17  16:33:23  bww]
 * 
 * Revision 1.3  89/12/07  11:19:37  bww
 * 	Removed include of sys/features.h as it is no longer
 * 	exported or needed.  From "[89/12/05            mrt]" at CMU.
 * 	[89/12/07            bww]
 * 
 * Revision 1.2  89/05/26  12:26:40  bww
 * 	CMU CS as of 89/05/15
 * 	[89/05/26  09:46:50  bww]
 * 
 * Revision 2.3  89/01/20  15:44:24  gm0w
 * 	Added externs to the non-STDC case for functions that do not
 * 	have int return values.
 * 	[88/12/17            gm0w]
 * 
 * Revision 2.2  88/12/14  23:35:52  mja
 * 	Created.
 * 	[88/01/06            jjk]
 * 
 **********************************************************************
 */

#ifndef _SYSENT_H_
#define _SYSENT_H_ 1

#if __STDC__
#include <sys/types.h>
#include <sys/time.h>

extern int access(const char *, int);
extern int acct(const char *);
extern int brk(void *);
extern int sbrk(int);
extern int chdir(const char *);
extern int chmod(const char *, int);
extern int fchmod(int, int);
extern int chown(const char *, int, int);
extern int fchown(int, int, int);
extern int chroot(const char *);
extern int close(int);
extern int creat(const char *, int);
extern int dup(int);
extern int dup2(int, int);
extern int execve(const char *, const char **, const char **);
extern void _exit(int);
extern int fcntl(int, int, int);
extern int flock(int, int);
extern int fork(void);
extern int fsync(int);
extern int getdtablesize(void);
extern gid_t getgid(void);
extern gid_t getegid(void);
extern int getgroups(int, int *);
extern long gethostid(void);
extern int sethostid(long);
extern int gethostname(char *, int);
extern int sethostname(const char *, int);
extern int getpagesize(void);
extern int getpgrp(int);
extern int getpid(void);
extern int getppid(void);
extern uid_t getuid(void);
extern uid_t geteuid(void);
extern int ioctl(int, unsigned long, void *);
extern int kill(int, int);
extern int killpg(int, int);
extern int link(const char *, const char *);
extern off_t lseek(int, off_t, int);
extern int mkdir(const char *, int);
extern int mknod(const char *, int, int);
extern int mount(const char *, const char *, int);
extern int umount(const char *);
extern int open(const char *, int, int);  /* char *, int, ... ?? */
extern int pipe(int *);
extern int profil(void *, int, int, int);
extern int ptrace(int, int, int *, int);
extern int quota(int, int, int, void *);
extern int read(int, void *, int);
extern int readlink(const char *, void *, int);
extern int reboot(int);
extern int rename(const char *, const char *);
extern int rmdir(const char *);
extern int select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
extern int setgroups(int, int *);
extern int setpgrp(int, int);
extern int setquota(const char *, const char *);
extern int setregid(gid_t, gid_t);
extern int setreuid(uid_t, uid_t);
extern int swapon(const char *);
extern int symlink(const char *, const char *);
extern void sync(void);
extern int syscall(int, ...);
extern int truncate(const char *, off_t);
extern int ftruncate(int, off_t);
extern int umask(int);
extern int unlink(const char *);
extern int vfork(void);
extern void vhangup(void);
extern int write(int, void *, int);

#ifndef	_VICEIOCTL
#include <sys/viceioctl.h>
#endif	/* not _VICEIOCTL */
extern int pioctl(const char *, unsigned long, struct ViceIoctl *, int);
extern int setpag(void);
#else /* __STDC__ */
extern gid_t getgid();
extern gid_t getegid();
extern long gethostid();
extern uid_t getuid();
extern uid_t geteuid();
extern off_t lseek();
#endif	/* __STDC__ */
#endif	/* not _SYSENT_H_ */
