gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/btptes.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/tables.c


@REM cat assym.s ../../machine/start.s  ../../machine/locore.s ../../machine/cswitch.s >locore.tmp
@REM cc -ES -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -DASSEMBLER -DLOCORE -I../machine locore.s >locore.i 
@REM as -o locore.o locore.i
cat assym.s ../../i386/start.s  ../../i386/locore.s ../../i386/cswitch.s >locore.tmp
cpp -nostdinc -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -DASSEMBLER -DLOCORE -I. -I..\.. locore.tmp | sed -e 's/_\ /_/g'| sed -e 's/\ ;/;/g' | sed -e 's/\ :/:/g' |grep -v # > lowlow.i
@REM a386 lowlow.i -o locore.o
a386 ../../i386/locore.i -o locore.o
@REM rm -f locore.i
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/cmu_syscalls.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/init_main.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/init_sysent.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_acct.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_clock.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_descrip.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_exec.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_exit.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_fork.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_mman.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_proc.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_prot.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_resource.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_sig.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_subr.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_synch.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_time.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/kern_xxx.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/mach_process.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/mach_signal.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/quota_sys.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/subr_log.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/subr_prf.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/subr_rmap.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/subr_xxx.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/sys_generic.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/sys_inode.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/sys_socket.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/tty.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/tty_cmupty.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/tty_conf.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/tty_pty.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/tty_subr.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/tty_tty.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_alloc.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_bio.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_bmap.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_disksubr.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_fio.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_inode.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_mount.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_namei.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_physio.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_subr.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_syscalls.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_tables.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/ufs_xxx.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/uipc_domain.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/uipc_mbuf.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/uipc_proto.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/uipc_socket.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/uipc_socket2.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/uipc_syscalls.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../bsd/uipc_usrreq.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../builtin/device_pager.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../builtin/inode_pager.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../builtin/ux_exception.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../conf/param.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ast.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/clock_prim.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/debug.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/exception.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/host.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/iprintf.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/lock.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/mach_factor.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_basics.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_copyin.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_copyout.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_host.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_kport.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_kset.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_pobj.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_port.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_tt.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_globals.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_mports.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_prims.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/ipc_ptraps.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/kalloc.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/mach_net.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/mach_timedev.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/mach_user_internal.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/machine.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/mfs_prim.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/mig_support.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/parallel.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/processor.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/queue.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/sched_prim.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/slave.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/syscall_emulation.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/syscall_subr.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/syscall_sw.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/task.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/thread.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/thread_swap.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/timer.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../kern/zalloc.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse mach/exc_server.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse mach/exc_user.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse mach/mach_host_server.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse mach/mach_server.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse mach/memory_object_default_user.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse mach/memory_object_user.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse mach_debug/mach_debug_server.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../net/af.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../net/dli.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../net/if.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../net/if_loop.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../net/if_sl.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../net/slcompress.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../net/netisr.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../net/raw_cb.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../net/raw_usrreq.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../net/route.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/if_ether.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/igmp.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/in.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/in_pcb.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/in_proto.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/ip_icmp.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/ip_input.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/ip_mroute.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/ip_output.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/raw_ip.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/tcp_debug.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/tcp_input.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/tcp_output.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/tcp_subr.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/tcp_timer.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/tcp_usrreq.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../netinet/udp_usrreq.c
@REM gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../rfs/rfs_control.c
@REM gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../rfs/rfs_descrip.c
@REM gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../rfs/rfs_init.c
@REM gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../rfs/rfs_kern.c
@REM gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../rfs/rfs_socket.c
@REM gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../rfs/rfs_subr.c
@REM gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../rfs/rfs_syscalls.c
@REM gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../rfs/rfs_ticket.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../vm/memory_object.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../vm/vm_fault.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../vm/vm_init.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../vm/vm_kern.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../vm/vm_map.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../vm/vm_object.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../vm/vm_pageout.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../vm/vm_resident.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../vm/vm_unix.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../vm/vm_user.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ioconf.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/access.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/bits.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/command.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/expr.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/format.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/input.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/kdb_main.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/message.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/opset.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/output.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/pcs.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/print.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/runpcs.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/setup.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/stack.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/sym.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/tbls.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb/utls.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/clock.c
@REM cc -ES -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -DASSEMBLER ../../i386/copy_user.s >copy_user.i
@REM as -o copy_user.o copy_user.i
@REM rm -f copy_user.i
uudecode copyuser.txt
a386 copy_user.i -o copy_user.o
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/fpsup.c
@REM cc -ES -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -DASSEMBLER ../../i386/fp/FPU_start.s >FPU_start.i ;  as -o FPU_start.o FPU_start.i;  rm -f FPU_start.i
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
@REM cc -ES -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -DASSEMBLER ../../i386/gcc.s >gcc.i ;  as -o gcc.o gcc.i;  rm -f gcc.i
cpp -nostdinc -I..\.. ../../i386/gcc.s | sed -e 's/_\ /_/g'| sed -e 's/\ ;/;/g' | sed -e 's/\ :/:/g' |grep -v # > gcc.i
a386 -o gcc.o gcc.i
a386 FPU_end.i -o FPU_end.o
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/i386_init.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/pic.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/pit.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/in_cksum.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/kdb.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/machdep.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/mem.c
@REM cc -ES -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -DASSEMBLER ../../i386/ntoh.s >ntoh.i ;  as -o ntoh.o ntoh.i;  rm -f ntoh.i
cpp -nostdinc -I..\.. ../../i386/ntoh.s | sed -e 's/_\ /_/g'| sed -e 's/\ ;/;/g' | sed -e 's/\ :/:/g' |grep -v # > ntoh.i
a386 ntoh.i -o ntoh.o
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/pcb.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/phys.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/pmap.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/sys_machdep.c
@REM cc -ES -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -DASSEMBLER ../../i386/str.s >str.i ;  as -o str.o str.i;  rm -f str.i
cpp -nostdinc -I..\.. ../../i386/str.s | sed -e 's/_\ /_/g'| sed -e 's/\ ;/;/g' | sed -e 's/\ :/:/g' |grep -v # > str.i
a386 str.i -o str.o
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/trap.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/ufs_machdep.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/vm_machdep.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/vx_exception.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/adaptec.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/autoconf.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -D__GNUC__ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/com.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/lpr.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/conf.c
@REM gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/fd.c
gcc -c -nostdinc -E -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/fd.c | sed -e "s/(v)<<8)/('v')<<8)/g"  > fd.i
gcc -c -nostdinc -O fd.i
@REM gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/hd.c
gcc -c -nostdinc -E -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/hd.c | sed -e "s/(v)<<8)/('v')<<8)/g"  > hd.i
gcc -c -nostdinc -O hd.i
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/iopl.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/if_par.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/if_3c501.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/if_pc586.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/if_ns8390.c
@gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/kd.c
gcc -c -nostdinc -E -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/kd.c | sed -e "s/(k)<<8)/('k')<<8)/g"  > kd.i
gcc -c -nostdinc -O kd.i
@REM cc -ES -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -DASSEMBLER ../../i386at/kdasm.s >kdasm.i ;  as -o kdasm.o kdasm.i;  rm -f kdasm.i
cpp -nostdinc -I..\.. ../../i386at/kdasm.s | sed -e 's/_\ /_/g'| sed -e 's/\ ;/;/g' | sed -e 's/\ :/:/g' |grep -v # > kdasm.i
a386 kdasm.i -o kdasm.o
@REM gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/kd_event.c
gcc -c -nostdinc -E -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/kd_event.c | sed -e "s/(K)<<8)/('K')<<8)/g"  > kd_event.i
gcc -O -c kd_event.i
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/kd_mouse.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/kd_queue.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/pic_isa.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/rtc.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386at/wt.c
gcc -c -nostdinc -O -I. -I../../sys -I../.. -I../../root_fs/ -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -fno-function-cse ../../i386/swapgeneric.c -o vmunix.swap
gcc -c vers.c
@REM copy old\fd.o
@REM copy old\hd.o
@REM copy old\kd.o
@REM copy old\kdasm.o
@REM copy old\kd_event.o
@REM copy old\vmunix.swap
call ll.cmd