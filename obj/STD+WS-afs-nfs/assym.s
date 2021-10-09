#ifdef LOCORE
#define	P_LINK 0
#define	P_RLINK 4
#define	P_PRI 17
#define	P_STAT 19
#define	P_CURSIG 23
#define	P_SIG 24
#define	P_FLAG 40
#define	SSLEEP 1
#define	SRUN 3
#define	UPAGES 16
#define	U_PROCP 0
#define	U_RU 688
#define	RU_MINFLT 32
#define	PR_BASE 4
#define	PR_SIZE 8
#define	PR_OFF 12
#define	PR_SCALE 16
#define	U_ERROR 104
#define	U_AR0 0
#define	pcb_fpvalid 264
#define	pcb_fps 268
#define	USER_FP 0x2f
#define	KDSSEL 0x160
#define	KTSSSEL 0x150
#define	JTSSSEL 0x170
#define	THREAD_PCB 36
#define	THREAD_RECOVER 104
#define	THREAD_TASK 12
#define	UTHREAD 120
#define	UTASK 124
#else
asm(".set	U_ARG,4");
asm(".set	U_QSAVE,40");
#endif
