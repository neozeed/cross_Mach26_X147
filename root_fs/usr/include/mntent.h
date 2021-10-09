/*	@(#)mntent.h	3.4	89/02/07	mt Xinu
 *
 * File system table, see mntent (5)
 *
 * Used by dump, mount, umount, swapon, fsck, df, ...
 *
 * Quota files are always named "quotas", so if type is "rq",
 * then use concatenation of mnt_dir and "quotas" to locate
 * quota file.
 **********************************************************************
 * HISTORY
 * $Log:	mntent.h,v $
 * Revision 1.2  89/09/27  12:31:03  bww
 * 	Added function prototype declarations.
 * 	[89/09/27  12:30:46  bww]
 * 
 */

#define	MNTTAB		"/etc/fstab"
#define	MOUNTED		"/etc/mtab"

#define	MNTMAXSTR	128

#define	MNTTYPE_UFS	"ufs"	/* disk file system */
#define	MNTTYPE_43	"4.3"	/* (for NFS 4.0 compatibility) */
#define	MNTTYPE_42	"4.2"	/* (for NFS 3.x compatibility) */
#define	MNTTYPE_NFS	"nfs"	/* network file system */
#define	MNTTYPE_PC	"pc"	/* IBM PC (MSDOS) file system */
#define	MNTTYPE_SWAP	"swap"	/* swap file system */
#define	MNTTYPE_IGNORE	"ignore"/* No type specified, ignore this entry */
#define	MNTTYPE_LO	"lo"	/* Loop back File system */

#define	MNTOPT_RO	"ro"	/* read only */
#define	MNTOPT_RW	"rw"	/* read/write */
#define	MNTOPT_QUOTA	"quota"	/* quotas */
#define	MNTOPT_NOQUOTA	"noquota"	/* no quotas */
#define	MNTOPT_SOFT	"soft"	/* soft mount */
#define	MNTOPT_HARD	"hard"	/* hard mount */
#define	MNTOPT_NOSUID	"nosuid"/* no set uid allowed */
#define	MNTOPT_NOAUTO	"hide"	/* hide entry from mount -a */
#define	MNTOPT_INTR	"intr"	/* allow interrupts on hard mount */
#define	MNTOPT_SECURE	"secure"/* use secure RPC for NFS */
#define	MNTOPT_GRPID	"grpsvid"/* BSD-compatible group-id on create */
#define	MNTOPT_REMOUNT	"remount"/* change options on previous mount */
#define	MNTOPT_NOSUB	"nosub"	/* disallow mounts beneath this one */
#define	MNTOPT_MULTI	"multi"	/* Do multi-component lookup */

struct	mntent{
	char	*mnt_fsname;		/* name of mounted file system */
	char	*mnt_dir;		/* file system path prefix */
	char	*mnt_type;		/* MNTTYPE_* */
	char	*mnt_opts;		/* MNTOPT* */
	int	mnt_freq;		/* dump frequency, in days */
	int	mnt_passno;		/* pass number on parallel fsck */
};

#if __STDC__
extern struct	mntent *getmntent(FILE*);
extern char	*hasmntopt(struct mntent*, char*);
extern FILE	*setmntent(char*, char*);
extern int	endmntent(FILE*);
#else
struct	mntent *getmntent();
char	*hasmntopt();
FILE	*setmntent();
int	endmntent();
#endif
