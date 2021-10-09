gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/btptes.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/tables.c


@REM cat assym.s ../../machine/start.s  ../../machine/locore.s ../../machine/cswitch.s >locore.tmp
@REM cc -ES -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -DASSEMBLER -DLOCORE -I../machine locore.s >locore.i 
@REM as -O2 locore.o locore.i
cat assym.s ../../i386/start.s  ../../i386/locore.s ../../i386/cswitch.s >locore.tmp
cpp -nostdinc -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -DASSEMBLER -DLOCORE -I. -I..\.. locore.tmp | sed -e 's/_\ /_/g'| sed -e 's/\ ;/;/g' | sed -e 's/\ :/:/g' |grep -v # > lowlow.i
@REM a386 lowlow.i -o locore.o
a386 locore.i -o locore.o
@REM rm -f locore.i
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/cmu_syscalls.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/init_main.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/init_sysent.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_acct.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_clock.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_descrip.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_exec.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_exit.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_fork.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_mman.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_proc.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_prot.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_resource.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_sig.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_subr.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_synch.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_time.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_xxx.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/mach_process.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/mach_signal.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/quota_sys.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/subr_log.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/subr_prf.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/subr_rmap.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/subr_xxx.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/sys_generic.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/sys_inode.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/sys_socket.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/tty.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/tty_cmupty.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/tty_conf.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/tty_pty.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/tty_subr.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/tty_tty.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_alloc.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_bio.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_bmap.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_disksubr.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_fio.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_inode.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_mount.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_namei.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_physio.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_subr.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_syscalls.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_tables.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_xxx.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/uipc_domain.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/uipc_mbuf.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/uipc_proto.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/uipc_socket.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/uipc_socket2.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/uipc_syscalls.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/uipc_usrreq.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../builtin/device_pager.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../builtin/inode_pager.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../builtin/ux_exception.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../conf/param.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ast.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/clock_prim.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/debug.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/exception.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/host.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/iprintf.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/lock.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/mach_factor.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_basics.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_copyin.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_copyout.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_host.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_kport.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_kset.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_pobj.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_port.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_tt.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_globals.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_mports.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_prims.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_ptraps.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/kalloc.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/mach_net.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/mach_timedev.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/mach_user_internal.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/machine.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/mfs_prim.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/mig_support.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/parallel.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/processor.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/queue.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/sched_prim.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/slave.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/syscall_emulation.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/syscall_subr.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/syscall_sw.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/task.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/thread.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/thread_swap.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/timer.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/zalloc.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse mach/exc_server.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse mach/exc_user.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse mach/mach_host_server.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse mach/mach_server.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse mach/memory_object_default_user.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse mach/memory_object_user.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse mach_debug/mach_debug_server.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../net/af.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../net/dli.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../net/if.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../net/if_loop.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../net/if_sl.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../net/slcompress.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../net/netisr.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../net/raw_cb.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../net/raw_usrreq.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../net/route.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/if_ether.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/igmp.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/in.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/in_pcb.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/in_proto.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/ip_icmp.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/ip_input.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/ip_mroute.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/ip_output.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/raw_ip.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/tcp_debug.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/tcp_input.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/tcp_output.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/tcp_subr.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/tcp_timer.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/tcp_usrreq.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/udp_usrreq.c
@REM gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../rfs/rfs_control.c
@REM gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../rfs/rfs_descrip.c
@REM gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../rfs/rfs_init.c
@REM gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../rfs/rfs_kern.c
@REM gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../rfs/rfs_socket.c
@REM gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../rfs/rfs_subr.c
@REM gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../rfs/rfs_syscalls.c
@REM gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../rfs/rfs_ticket.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../vm/memory_object.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../vm/vm_fault.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../vm/vm_init.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../vm/vm_kern.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../vm/vm_map.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../vm/vm_object.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../vm/vm_pageout.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../vm/vm_resident.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../vm/vm_unix.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../vm/vm_user.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ioconf.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/access.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/bits.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/command.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/expr.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/format.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/input.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/kdb_main.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/message.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/opset.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/output.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/pcs.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/print.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/runpcs.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/setup.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/stack.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/sym.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/tbls.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/utls.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/clock.c
@REM cc -ES -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -DASSEMBLER ../../i386/copy_user.s >copy_user.i
@REM as -O2 copy_user.o copy_user.i
@REM rm -f copy_user.i
uudecode copyuser.txt
a386 copy_user.i -o copy_user.o
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/fpsup.c
@REM cc -ES -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -DASSEMBLER ../../i386/fp/FPU_start.s >FPU_start.i ;  as -O2 FPU_start.o FPU_start.i;  rm -f FPU_start.i
cpp -nostdinc -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -DASSEMBLER -DLOCORE -I. -I..\.. ../../i386/fp/FPU_start.s | sed -e 's/_\ /_/g'| sed -e 's/\ ;/;/g' | sed -e 's/\ :/:/g' |grep -v # > FPU_start.i
a386 FPU_start.i -o FPU_start.o
rm -f arith.o
uudecode ../../i386/fp/arith.b
rm -f dcode.o
uudecode ../../i386/fp/dcode.b
rm -f divmul.o
uudecode ../../i386/fp/divmul.b
rm -f lipsq.o
uudecode ../../i386/fp/lipsq.b
rm -f reg.o
uudecode ../../i386/fp/reg.b
rm -f remsc.o
uudecode ../../i386/fp/remsc.b
rm -f round.o
uudecode ../../i386/fp/round.b
rm -f status.o
uudecode ../../i386/fp/status.b
rm -f store.o
uudecode ../../i386/fp/store.b
rm -f subadd.o
uudecode ../../i386/fp/subadd.b
rm -f trans.o
uudecode ../../i386/fp/trans.b
@REM cc -ES -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -DASSEMBLER ../../i386/fp/FPU_end.s >FPU_end.i ;  as -o FPU_end.o FPU_end.i;  rm -f FPU_end.i
cpp -nostdinc -I..\.. ../../i386/fp/FPU_end.s | sed -e 's/_\ /_/g'| sed -e 's/\ ;/;/g' | sed -e 's/\ :/:/g' |grep -v # > FPU_end.i
a386 -o FPU_end.o FPU_end.i
@REM cc -ES -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -DASSEMBLER ../../i386/gcc.s >gcc.i ;  as -O2 gcc.o gcc.i;  rm -f gcc.i
cpp -nostdinc -I..\.. ../../i386/gcc.s | sed -e 's/_\ /_/g'| sed -e 's/\ ;/;/g' | sed -e 's/\ :/:/g' |grep -v # > gcc.i
a386 -o gcc.o gcc.i
a386 FPU_end.i -O2 FPU_end.o
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/i386_init.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/pic.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/pit.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/in_cksum.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/machdep.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/mem.c
@REM cc -ES -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -DASSEMBLER ../../i386/ntoh.s >ntoh.i ;  as -O2 ntoh.o ntoh.i;  rm -f ntoh.i
cpp -nostdinc -I..\.. ../../i386/ntoh.s | sed -e 's/_\ /_/g'| sed -e 's/\ ;/;/g' | sed -e 's/\ :/:/g' |grep -v # > ntoh.i
a386 ntoh.i -o ntoh.o
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/pcb.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/phys.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/pmap.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/sys_machdep.c
@REM cc -ES -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -DASSEMBLER ../../i386/str.s >str.i ;  as -O2 str.o str.i;  rm -f str.i
cpp -nostdinc -I..\.. ../../i386/str.s | sed -e 's/_\ /_/g'| sed -e 's/\ ;/;/g' | sed -e 's/\ :/:/g' |grep -v # > str.i
a386 str.i -o str.o
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/trap.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/ufs_machdep.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/vm_machdep.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/vx_exception.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/adaptec.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/autoconf.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -D__GNUC__ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/com.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/lpr.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/conf.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/fd.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/hd.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/iopl.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/if_par.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/if_3c501.c
gcc2 -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/if_pc586.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/if_ns8390.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/kd.c
@REM cc -ES -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -DASSEMBLER ../../i386at/kdasm.s >kdasm.i ;  as -O2 kdasm.o kdasm.i;  rm -f kdasm.i
cpp -nostdinc -I..\.. ../../i386at/kdasm.s | sed -e 's/_\ /_/g'| sed -e 's/\ ;/;/g' | sed -e 's/\ :/:/g' |grep -v # > kdasm.i
a386 kdasm.i -o kdasm.o
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/kd_event.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/kd_mouse.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/kd_queue.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/pic_isa.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/rtc.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/wt.c
gcc-258_old -c -nostdinc -O2 -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/swapgeneric.c -o vmunix.swap
gcc-258_old -c vers.c
copy old\fd.o
copy old\hd.o
copy old\kd.o
copy old\kdasm.o
copy old\kd_event.o
call ll.cmd