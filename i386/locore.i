# 1 "locore.s"









































































# 1 "/usr/include/i386/asm.h" 1






























































# 94 "/usr/include/i386/asm.h"























































# 74 "locore.s" 2

# 1 "/usr/include/mach/vm_param.h" 1
























































# 1 "/usr/include/mach/machine/vm_param.h" 1


















































































































# 57 "/usr/include/mach/vm_param.h" 2

# 1 "/usr/include/mach/machine/vm_types.h" 1










































# 58 "/usr/include/mach/vm_param.h" 2
















# 108 "/usr/include/mach/vm_param.h"


# 75 "locore.s" 2























	

/ these are not needed for iPSC2
	.globl	_cnvmem
	.globl	_extmem
	.globl	_boottype
	.globl	_boothowto




	.globl	_esym

	.globl	_pstart
	.globl	_gdt
	.globl	_idt
	.globl	_kpde
	.globl	_kpte
	.globl	_scall_dscr
	.globl	_sigret_dscr





	.set	GDTLIM, ((8*96)-1)
	.set	IDTLIM, ((8*256)-1)

	.set    GDTSZ,   96
	.set    IDTSZ,   256
	.set	PAGEBIT, 0x80000000
	.set	MASK,	 0x0FFFFFFF	/ mask the top nibble
	.set	KV,	 0xC0000000

	.text
	.globl _intstack; .align 2; _intstack:
	.globl _df_stack; .align 2; _df_stack:
/	.space	(1*4096	)	
	.set .,. + 4096

.globl _pstart; .align 2; _pstart:


	/ Retrieve the parameters passed from boot
	pop	%eax
	mov	$_boottype, %ebx
	and	$MASK, %ebx
	mov	%eax, (%ebx)

	pop	%eax
	mov	$_extmem, %ebx
	and	$MASK, %ebx
	mov	%eax, (%ebx)

	pop	%eax
	mov	$_cnvmem, %ebx
	and	$MASK, %ebx
	mov	%eax, (%ebx)






	pop	%eax

	mov	$_boothowto, %ebx
	and	$MASK, %ebx
	mov	%eax, (%ebx)




	pop	%eax
	orl	$KV, %eax
	mov	$_esym, %ebx
	and	$MASK, %ebx
	mov	%eax, (%ebx)


	/ Turn off clock interrupt.
	/ This is due to a bug in p0init which enables interrupt
	/ before picinit.
	mov	$0x21, %edx		/ XXX - magic number
	inb	%dx, %al
	orb	$1, %al			/ XXX - magic number
	outb	%al, %dx

	/ Rearrange GDT
	mov	$_gdt, %eax
	and	$MASK, %eax

	mov	$GDTLIM, %ecx

	mov	$GDTdscr, %ebx
	and	$MASK, %ebx
	movw	%cx, (%ebx)

	call	munge_table

	/ Rearrange IDT
	mov	$_idt, %eax
	and	$MASK, %eax

	mov	$IDTLIM, %ecx

	call	munge_table

	/ Rearrange call gate for system call (scall_dscr)
	mov	$_scall_dscr, %eax
	and	$MASK, %eax

	mov	$1, %ecx

	call	munge_table

	/ Rearrange call gate for signal return  (sigret_dscr)
	mov	$_sigret_dscr, %eax
	and	$MASK, %eax

	mov	$1, %ecx

	call	munge_table

	/ Fix up the 1st, 3 giga and last entries in the page directory
	mov	$_kpde, %ebx
	and	$MASK, %ebx

	mov	$_kpte, %eax	
	and	$0xffff000, %eax
	or	$0x1, %eax

	mov	%eax, (%ebx)
	mov	%eax, 3072(%ebx)	/ 3 giga -- C0000000

	mov	$_kpde, %edx
	and	$MASK, %edx

	/ Load IDTR
	mov	$IDTdscr, %eax
	and	$MASK, %eax

	lidt	(%eax)

	/ Load GDTR
	mov	$GDTdscr, %eax
	and	$MASK, %eax

	lgdt	(%eax)

	/ flip cr3 before you flip cr0
	mov	%edx, %cr3

	/ turn PG on
	mov	%cr0, %eax
	or	$PAGEBIT, %eax
	mov	%eax, %cr0


	ljmp	$0x150, $0x0

/ *********************************************************************
/	munge_table:
/		This procedure will 'munge' a descriptor table to
/		change it from initialized format to runtime format.
/		Assumes:
/			%eax -- contains the base address of table.
/			%ecx -- contains size of table.
/ *********************************************************************

munge_table:
	mov	%eax, %ebx
	add	%ebx, %ecx
moretable:
	cmp	%ebx, %ecx
	jl	donetable		/ Have we done every descriptor??
	movb	7(%ebx), %al	/ Find the byte containing the type field
	testb	$0x10, %al	/ See if this descriptor is a segment
	jne	notagate
	testb	$0x04, %al	/ See if this destriptor is a gate
	je	notagate
				/ Rearrange a gate descriptor.
	movw	6(%ebx), %eax	/ Type (etc.) lifted out
	movw	4(%ebx), %edx	/ Selector lifted out.
	movw	%eax, 4(%ebx)	/ Type (etc.) put back
	movw	2(%ebx), %eax	/ Grab Offset 16..31
	movw	%edx, 2(%ebx)	/ Put back Selector
	movw	%eax, 6(%ebx)	/ Offset 16..31 now in right place
	jmp	descdone

notagate:			/ Rearrange a non gate descriptor.
	movw	4(%ebx), %edx	/ Limit 0..15 lifted out
	movb	%al, 5(%ebx)	/ type (etc.) put back
	movw	2(%ebx), %eax	/ Grab Base 16..31
	movb	%al, 4(%ebx)	/ put back Base 16..23
	movb	%ah, 7(%ebx)	/ put back Base 24..32
	movw	(%ebx), %eax	/ Get Base 0..15
	movw	%eax, 2(%ebx)	/ Base 0..15 now in right place
	movw	%edx, (%ebx)	/ Limit 0..15 in its proper place

descdone:
	addw	$8, %ebx	/ Go for the next descriptor
	jmp	moretable

donetable:
	ret

	.align	8
GDTdscr:
	.word  GDTLIM
	.long	_gdt

	.align	8
IDTdscr:
	.word	IDTLIM
	.long	_idt

























































































































































# 1 "/usr/include/i386/asm.h" 1






























































# 94 "/usr/include/i386/asm.h"























































# 467 "locore.s" 2




























# 1 "./mach_kdb.h" 1

# 495 "locore.s" 2

# 1 "./mach_emulation.h" 1

# 496 "locore.s" 2

# 1 "./cputypes.h" 1

# 497 "locore.s" 2

# 1 "/usr/include/sys/errno.h" 1











































































# 1 "./mach_nfs.h" 1

# 76 "/usr/include/sys/errno.h" 2





















































	













	













	




















































# 218 "/usr/include/sys/errno.h"










# 498 "locore.s" 2

# 1 "/usr/include/mach/kern_return.h" 1




















































# 1 "/usr/include/mach/machine/kern_return.h" 1






































# 53 "/usr/include/mach/kern_return.h" 2





		



		




		





		




		



		




		




		



		





		







		



		



		



# 499 "locore.s" 2

# 1 "/usr/include/i386/ipl.h" 1

















































































# 500 "locore.s" 2

# 1 "/usr/include/i386/pic.h" 1

























































































































































































 














# 501 "locore.s" 2

# 1 "/usr/include/i386/reg.h" 1





























































































# 502 "locore.s" 2

# 1 "/usr/include/mach/i386/vm_param.h" 1








































# 114 "/usr/include/mach/i386/vm_param.h"

# 503 "locore.s" 2


/
/			 GLOBAL DEFINITIONS
	.data
	.set    CR0_ET,		0x0010            / extension type
	.set    CR0_TS,		0x0008            / task switched
	.set    CR0_EM,		0x0004            / use math emulation
	.set    CR0_MP,		0x0002            / math coprocessor present
	.set    CR0_PE,		0x0001            / protection enable
	.set    FP_SW,		0x0001            / fp emulator is used
	.set    FP_287,		0x0002            / 80287 present
	.set    FP_387,		0x0003            / 80387 present
	.set    F_OFF,		0x0002		/ kernel mode flags, ints off
	.set    F_ON,		0x0202		/ kernel mode flags, ints on
	.set    IS_LDT_SEL,	0x0004		/ GDT/LDT bit in selector
	.set	KSTKSZ,		0x1000
	.set    KVBASE,		0xC0000000	/ base address of the kernel
	.set	MASK,		0x0004
	.set	NBPC,		0x1000		/ Page Size from param.h
	.set	PC,		0x0008
	.set	PROTPORT,	0x00E0
	.set	PROTVAL,	0x0001
	.set	TICS,		0x0010
	.set	UPROF,		0x000C
	.set	USER_CS,	0x0017
	.set	USER_DS,	0x001F
	.set	USIZE,		0x0003		/ No. of pages in U Block
	.set    UVBASE,		0x00000000	/ main store start v_addr
	.set    MAXUVADR,	KVBASE		/ maximum user vaddr.
	.set    MINKVADR,	KVBASE		/ minimum kernel vaddr.
	.set    MINUVADR,	UVBASE		/ minimum user vaddr.
	.set    UVTEXT,		UVBASE		/ beginning addr of user text

/
/			 GLOBAL VARIABLES
	.data
	.globl _loadpt; .align 2; _loadpt:
	.long 	0
	.globl _loadpg; .align 2; _loadpg:
	.long	0 
	.globl _eaxsave; .align 2; _eaxsave:
	.long	0










/
/			 MACROES
	.text
///////////////////////////////////////////////////////////////////////////////
/	EXCEPTION : macro to handle trap where error code is not automatically 
/	pushed on stack by i80386, calls the trap handling routine and passes 
/	parameters on the stack, dummies out the trap name so that we only need
/	to write one trap handler, with common stack image.
///////////////////////////////////////////////////////////////////////////////







///////////////////////////////////////////////////////////////////////////////
/	 EXCEPTERR : macro to handle trap where error code is automatically 
/	 pushed on stack by i80386, calls the trap handling routine and passes
/	 parameters on the stack.
///////////////////////////////////////////////////////////////////////////////
 





///////////////////////////////////////////////////////////////////////////////
/	INTERRUPT : macro to handle interrupt call whether external or software
/	based, calls interrupt handling routine passing parameters on stack.
///////////////////////////////////////////////////////////////////////////////







///////////////////////////////////////////////////////////////////////////////
/	KERNEL_RETURN : procedure to follow to return to kernel routine 
/	for system calls, traps, interrupts etc.
///////////////////////////////////////////////////////////////////////////////










///////////////////////////////////////////////////////////////////////////////
/ 	INTERRUPT_RETURN : this routine is run to return from an interrupt
/ 	handling routine. This is implemented as a macroe for efficiency 
/ 	reasons.
///////////////////////////////////////////////////////////////////////////////











///////////////////////////////////////////////////////////////////////////////
/	SET_PIC_MASK : this routine is run to set the pic masks, it is 
/	implemented as a macroe for efficiency reasons.
///////////////////////////////////////////////////////////////////////////////








/
/			MACRO CALLS 

///////////////////////////////////////////////////////////////////////////////
/	Faults : reported BEFORE execution instruction causing exception.
/ 	Trap   : reported AFTER  execution instruction causing exception.
/	Abort  : reported where error location is not known and program
/		restart impossible.
/ 
/ 	Exceptions 0x0E and (0x11 - 0x1F) are reserved by Intel
/ 	Exception  0x02 is for the Non Maskable Interrupt.
/ 	Exceptions 0x40 - 0xFF are assigned to external interrupts.
///////////////////////////////////////////////////////////////////////////////

.globl _trp_divr; .align 2; _trp_divr:				;	pushl	$0x00		;	pushl	$0x00		;	jmp	trap_handler
.globl _trp_debg; .align 2; _trp_debg:				;	pushl	$0x00		;	pushl	$0x01		;	jmp	trap_handler
.globl _int__nmi; .align 2; _int__nmi:				;	pushl	$0x00		;	pushl	$0x02		;	jmp	trap_handler
.globl _trp_brpt; .align 2; _trp_brpt:				;	pushl	$0x00		;	pushl	$0x03		;	jmp	trap_handler
.globl _trp_over; .align 2; _trp_over:				;	pushl	$0x00		;	pushl	$0x04		;	jmp	trap_handler
.globl _flt_bnds; .align 2; _flt_bnds:				;	pushl	$0x00		;	pushl	$0x05		;	jmp	trap_handler
.globl _flt_opcd; .align 2; _flt_opcd:				;	pushl	$0x00		;	pushl	$0x06		;	jmp	trap_handler
.globl _flt_ncpr; .align 2; _flt_ncpr:				;	pushl	$0x00		;	pushl	$0x07		;	jmp	trap_handler
.globl _abt_dblf; .align 2; _abt_dblf:				;	pushl	$0x08		;	jmp	trap_handler
.globl _abt_over; .align 2; _abt_over:				;	pushl	$0x00		;	pushl	$0x09		;	jmp	trap_handler
.globl _flt_btss; .align 2; _flt_btss:				;	pushl	$0x0A		;	jmp	trap_handler
.globl _flt_bseg; .align 2; _flt_bseg:				;	pushl	$0x0B		;	jmp	trap_handler
.globl _flt_bstk; .align 2; _flt_bstk:				;	pushl	$0x0C		;	jmp	trap_handler
.globl _flt_prot; .align 2; _flt_prot:				;	pushl	$0x0D		;	jmp	trap_handler
.globl _flt_page; .align 2; _flt_page:				;	pushl	$0x0E		;	jmp	trap_handler
.globl _trp_0x0F; .align 2; _trp_0x0F:				;	pushl	$0x00		;	pushl	$0x0F		;	jmp	trap_handler
.globl _flt_bcpr; .align 2; _flt_bcpr:				;	pushl	$0x00		;	pushl	$0x10		;	jmp	trap_handler
.globl _trp_0x11; .align 2; _trp_0x11:				;	pushl	$0x00		;	pushl	$0x11		;	jmp	trap_handler
.globl _trp_0x12; .align 2; _trp_0x12:				;	pushl	$0x00		;	pushl	$0x12		;	jmp	trap_handler
.globl _trp_0x13; .align 2; _trp_0x13:				;	pushl	$0x00		;	pushl	$0x13		;	jmp	trap_handler
.globl _trp_0x14; .align 2; _trp_0x14:				;	pushl	$0x00		;	pushl	$0x14		;	jmp	trap_handler
.globl _trp_0x15; .align 2; _trp_0x15:				;	pushl	$0x00		;	pushl	$0x15		;	jmp	trap_handler
.globl _trp_0x16; .align 2; _trp_0x16:				;	pushl	$0x00		;	pushl	$0x16		;	jmp	trap_handler
.globl _trp_0x17; .align 2; _trp_0x17:				;	pushl	$0x00		;	pushl	$0x17		;	jmp	trap_handler
.globl _trp_0x18; .align 2; _trp_0x18:				;	pushl	$0x00		;	pushl	$0x18		;	jmp	trap_handler
.globl _trp_0x19; .align 2; _trp_0x19:				;	pushl	$0x00		;	pushl	$0x19		;	jmp	trap_handler
.globl _trp_0x1A; .align 2; _trp_0x1A:				;	pushl	$0x00		;	pushl	$0x1A		;	jmp	trap_handler
.globl _trp_0x1B; .align 2; _trp_0x1B:				;	pushl	$0x00		;	pushl	$0x1B		;	jmp	trap_handler
.globl _trp_0x1C; .align 2; _trp_0x1C:				;	pushl	$0x00		;	pushl	$0x1C		;	jmp	trap_handler
.globl _trp_0x1D; .align 2; _trp_0x1D:				;	pushl	$0x00		;	pushl	$0x1D		;	jmp	trap_handler
.globl _trp_0x1E; .align 2; _trp_0x1E:				;	pushl	$0x00		;	pushl	$0x1E		;	jmp	trap_handler
.globl _trp_0x1F; .align 2; _trp_0x1F:				;	pushl	$0x00		;	pushl	$0x1F		;	jmp	trap_handler
.globl _trp_0x20; .align 2; _trp_0x20:				;	pushl	$0x00		;	pushl	$0x20		;	jmp	trap_handler
.globl _trp_0x21; .align 2; _trp_0x21:				;	pushl	$0x00		;	pushl	$0x21		;	jmp	trap_handler
.globl _trp_0x22; .align 2; _trp_0x22:				;	pushl	$0x00		;	pushl	$0x22		;	jmp	trap_handler
.globl _trp_0x23; .align 2; _trp_0x23:				;	pushl	$0x00		;	pushl	$0x23		;	jmp	trap_handler
.globl _trp_0x24; .align 2; _trp_0x24:				;	pushl	$0x00		;	pushl	$0x24		;	jmp	trap_handler
.globl _trp_0x25; .align 2; _trp_0x25:				;	pushl	$0x00		;	pushl	$0x25		;	jmp	trap_handler
.globl _trp_0x26; .align 2; _trp_0x26:				;	pushl	$0x00		;	pushl	$0x26		;	jmp	trap_handler
.globl _trp_0x27; .align 2; _trp_0x27:				;	pushl	$0x00		;	pushl	$0x27		;	jmp	trap_handler
.globl _trp_0x28; .align 2; _trp_0x28:				;	pushl	$0x00		;	pushl	$0x28		;	jmp	trap_handler
.globl _trp_0x29; .align 2; _trp_0x29:				;	pushl	$0x00		;	pushl	$0x29		;	jmp	trap_handler
.globl _trp_0x2A; .align 2; _trp_0x2A:				;	pushl	$0x00		;	pushl	$0x2A		;	jmp	trap_handler
.globl _trp_0x2B; .align 2; _trp_0x2B:				;	pushl	$0x00		;	pushl	$0x2B		;	jmp	trap_handler
.globl _trp_0x2C; .align 2; _trp_0x2C:				;	pushl	$0x00		;	pushl	$0x2C		;	jmp	trap_handler
.globl _trp_0x2D; .align 2; _trp_0x2D:				;	pushl	$0x00		;	pushl	$0x2D		;	jmp	trap_handler
.globl _trp_0x2E; .align 2; _trp_0x2E:				;	pushl	$0x00		;	pushl	$0x2E		;	jmp	trap_handler
.globl _trp_0x2F; .align 2; _trp_0x2F:				;	pushl	$0x00		;	pushl	$0x2F		;	jmp	trap_handler
.globl _trp_0x30; .align 2; _trp_0x30:				;	pushl	$0x00		;	pushl	$0x30		;	jmp	trap_handler
.globl _trp_0x31; .align 2; _trp_0x31:				;	pushl	$0x00		;	pushl	$0x31		;	jmp	trap_handler
.globl _trp_0x32; .align 2; _trp_0x32:				;	pushl	$0x00		;	pushl	$0x32		;	jmp	trap_handler
.globl _trp_0x33; .align 2; _trp_0x33:				;	pushl	$0x00		;	pushl	$0x33		;	jmp	trap_handler
.globl _trp_0x34; .align 2; _trp_0x34:				;	pushl	$0x00		;	pushl	$0x34		;	jmp	trap_handler
.globl _trp_0x35; .align 2; _trp_0x35:				;	pushl	$0x00		;	pushl	$0x35		;	jmp	trap_handler
.globl _trp_0x36; .align 2; _trp_0x36:				;	pushl	$0x00		;	pushl	$0x36		;	jmp	trap_handler
.globl _trp_0x37; .align 2; _trp_0x37:				;	pushl	$0x00		;	pushl	$0x37		;	jmp	trap_handler
.globl _trp_0x38; .align 2; _trp_0x38:				;	pushl	$0x00		;	pushl	$0x38		;	jmp	trap_handler
.globl _trp_0x39; .align 2; _trp_0x39:				;	pushl	$0x00		;	pushl	$0x39		;	jmp	trap_handler
.globl _trp_0x3A; .align 2; _trp_0x3A:				;	pushl	$0x00		;	pushl	$0x3A		;	jmp	trap_handler
.globl _trp_0x3B; .align 2; _trp_0x3B:				;	pushl	$0x00		;	pushl	$0x3B		;	jmp	trap_handler
.globl _trp_0x3C; .align 2; _trp_0x3C:				;	pushl	$0x00		;	pushl	$0x3C		;	jmp	trap_handler
.globl _trp_0x3D; .align 2; _trp_0x3D:				;	pushl	$0x00		;	pushl	$0x3D		;	jmp	trap_handler
.globl _trp_0x3E; .align 2; _trp_0x3E:				;	pushl	$0x00		;	pushl	$0x3E		;	jmp	trap_handler
.globl _trp_0x3F; .align 2; _trp_0x3F:				;	pushl	$0x00		;	pushl	$0x3F		;	jmp	trap_handler
/
.globl _int_0x00; .align 2; _int_0x00:				;	pushl	$0x00		;	pushl	$0x00		;	jmp	interrupt
.globl _int_0x01; .align 2; _int_0x01:				;	pushl	$0x00		;	pushl	$0x01		;	jmp	interrupt
.globl _int_0x02; .align 2; _int_0x02:				;	pushl	$0x00		;	pushl	$0x02		;	jmp	interrupt
.globl _int_0x03; .align 2; _int_0x03:				;	pushl	$0x00		;	pushl	$0x03		;	jmp	interrupt
.globl _int_0x04; .align 2; _int_0x04:				;	pushl	$0x00		;	pushl	$0x04		;	jmp	interrupt
.globl _int_0x05; .align 2; _int_0x05:				;	pushl	$0x00		;	pushl	$0x05		;	jmp	interrupt
.globl _int_0x06; .align 2; _int_0x06:				;	pushl	$0x00		;	pushl	$0x06		;	jmp	interrupt
.globl _int_0x07; .align 2; _int_0x07:				;	pushl	$0x00		;	pushl	$0x07		;	jmp	interrupt
.globl _int_0x08; .align 2; _int_0x08:				;	pushl	$0x00		;	pushl	$0x08		;	jmp	interrupt
.globl _int_0x09; .align 2; _int_0x09:				;	pushl	$0x00		;	pushl	$0x09		;	jmp	interrupt
.globl _int_0x0A; .align 2; _int_0x0A:				;	pushl	$0x00		;	pushl	$0x0A		;	jmp	interrupt
.globl _int_0x0B; .align 2; _int_0x0B:				;	pushl	$0x00		;	pushl	$0x0B		;	jmp	interrupt
.globl _int_0x0C; .align 2; _int_0x0C:				;	pushl	$0x00		;	pushl	$0x0C		;	jmp	interrupt
.globl _int_0x0D; .align 2; _int_0x0D:				;	pushl	$0x00		;	pushl	$0x0D		;	jmp	interrupt
.globl _int_0x0E; .align 2; _int_0x0E:				;	pushl	$0x00		;	pushl	$0x0E		;	jmp	interrupt
.globl _int_0x0F; .align 2; _int_0x0F:				;	pushl	$0x00		;	pushl	$0x0F		;	jmp	interrupt
.globl _int_0x10; .align 2; _int_0x10:				;	pushl	$0x00		;	pushl	$0x10		;	jmp	interrupt
.globl _int_0x11; .align 2; _int_0x11:				;	pushl	$0x00		;	pushl	$0x11		;	jmp	interrupt
.globl _int_0x12; .align 2; _int_0x12:				;	pushl	$0x00		;	pushl	$0x12		;	jmp	interrupt
.globl _int_0x13; .align 2; _int_0x13:				;	pushl	$0x00		;	pushl	$0x13		;	jmp	interrupt
.globl _int_0x14; .align 2; _int_0x14:				;	pushl	$0x00		;	pushl	$0x14		;	jmp	interrupt
.globl _int_0x15; .align 2; _int_0x15:				;	pushl	$0x00		;	pushl	$0x15		;	jmp	interrupt
.globl _int_0x16; .align 2; _int_0x16:				;	pushl	$0x00		;	pushl	$0x16		;	jmp	interrupt
.globl _int_0x17; .align 2; _int_0x17:				;	pushl	$0x00		;	pushl	$0x17		;	jmp	interrupt
.globl _int_0x18; .align 2; _int_0x18:				;	pushl	$0x00		;	pushl	$0x18		;	jmp	interrupt
.globl _int_0x19; .align 2; _int_0x19:				;	pushl	$0x00		;	pushl	$0x19		;	jmp	interrupt
.globl _int_0x1A; .align 2; _int_0x1A:				;	pushl	$0x00		;	pushl	$0x1A		;	jmp	interrupt
.globl _int_0x1B; .align 2; _int_0x1B:				;	pushl	$0x00		;	pushl	$0x1B		;	jmp	interrupt
.globl _int_0x1C; .align 2; _int_0x1C:				;	pushl	$0x00		;	pushl	$0x1C		;	jmp	interrupt
.globl _int_0x1D; .align 2; _int_0x1D:				;	pushl	$0x00		;	pushl	$0x1D		;	jmp	interrupt
.globl _int_0x1E; .align 2; _int_0x1E:				;	pushl	$0x00		;	pushl	$0x1E		;	jmp	interrupt
.globl _int_0x1F; .align 2; _int_0x1F:				;	pushl	$0x00		;	pushl	$0x1F		;	jmp	interrupt
.globl _int_0x20; .align 2; _int_0x20:				;	pushl	$0x00		;	pushl	$0x20		;	jmp	interrupt
.globl _int_0x21; .align 2; _int_0x21:				;	pushl	$0x00		;	pushl	$0x21		;	jmp	interrupt
.globl _int_0x22; .align 2; _int_0x22:				;	pushl	$0x00		;	pushl	$0x22		;	jmp	interrupt
.globl _int_0x23; .align 2; _int_0x23:				;	pushl	$0x00		;	pushl	$0x23		;	jmp	interrupt
.globl _int_0x24; .align 2; _int_0x24:				;	pushl	$0x00		;	pushl	$0x24		;	jmp	interrupt
.globl _int_0x25; .align 2; _int_0x25:				;	pushl	$0x00		;	pushl	$0x25		;	jmp	interrupt
.globl _int_0x26; .align 2; _int_0x26:				;	pushl	$0x00		;	pushl	$0x26		;	jmp	interrupt
.globl _int_0x27; .align 2; _int_0x27:				;	pushl	$0x00		;	pushl	$0x27		;	jmp	interrupt
.globl _int_0x28; .align 2; _int_0x28:				;	pushl	$0x00		;	pushl	$0x28		;	jmp	interrupt
.globl _int_0x29; .align 2; _int_0x29:				;	pushl	$0x00		;	pushl	$0x29		;	jmp	interrupt
.globl _int_0x2A; .align 2; _int_0x2A:				;	pushl	$0x00		;	pushl	$0x2A		;	jmp	interrupt
.globl _int_0x2B; .align 2; _int_0x2B:				;	pushl	$0x00		;	pushl	$0x2B		;	jmp	interrupt
.globl _int_0x2C; .align 2; _int_0x2C:				;	pushl	$0x00		;	pushl	$0x2C		;	jmp	interrupt
.globl _int_0x2D; .align 2; _int_0x2D:				;	pushl	$0x00		;	pushl	$0x2D		;	jmp	interrupt
.globl _int_0x2E; .align 2; _int_0x2E:				;	pushl	$0x00		;	pushl	$0x2E		;	jmp	interrupt
.globl _int_0x2F; .align 2; _int_0x2F:				;	pushl	$0x00		;	pushl	$0x2F		;	jmp	interrupt
.globl _int_0x30; .align 2; _int_0x30:				;	pushl	$0x00		;	pushl	$0x30		;	jmp	interrupt
.globl _int_0x31; .align 2; _int_0x31:				;	pushl	$0x00		;	pushl	$0x31		;	jmp	interrupt
.globl _int_0x32; .align 2; _int_0x32:				;	pushl	$0x00		;	pushl	$0x32		;	jmp	interrupt
.globl _int_0x33; .align 2; _int_0x33:				;	pushl	$0x00		;	pushl	$0x33		;	jmp	interrupt
.globl _int_0x34; .align 2; _int_0x34:				;	pushl	$0x00		;	pushl	$0x34		;	jmp	interrupt
.globl _int_0x35; .align 2; _int_0x35:				;	pushl	$0x00		;	pushl	$0x35		;	jmp	interrupt
.globl _int_0x36; .align 2; _int_0x36:				;	pushl	$0x00		;	pushl	$0x36		;	jmp	interrupt
.globl _int_0x37; .align 2; _int_0x37:				;	pushl	$0x00		;	pushl	$0x37		;	jmp	interrupt
.globl _int_0x38; .align 2; _int_0x38:				;	pushl	$0x00		;	pushl	$0x38		;	jmp	interrupt
.globl _int_0x39; .align 2; _int_0x39:				;	pushl	$0x00		;	pushl	$0x39		;	jmp	interrupt
.globl _int_0x3A; .align 2; _int_0x3A:				;	pushl	$0x00		;	pushl	$0x3A		;	jmp	interrupt
.globl _int_0x3B; .align 2; _int_0x3B:				;	pushl	$0x00		;	pushl	$0x3B		;	jmp	interrupt
.globl _int_0x3C; .align 2; _int_0x3C:				;	pushl	$0x00		;	pushl	$0x3C		;	jmp	interrupt
.globl _int_0x3D; .align 2; _int_0x3D:				;	pushl	$0x00		;	pushl	$0x3D		;	jmp	interrupt
.globl _int_0x3E; .align 2; _int_0x3E:				;	pushl	$0x00		;	pushl	$0x3E		;	jmp	interrupt
.globl _int_0x3F; .align 2; _int_0x3F:				;	pushl	$0x00		;	pushl	$0x3F		;	jmp	interrupt
.globl _int_0x40; .align 2; _int_0x40:				;	pushl	$0x00		;	pushl	$0x40		;	jmp	interrupt
.globl _int_0x41; .align 2; _int_0x41:				;	pushl	$0x00		;	pushl	$0x41		;	jmp	interrupt
.globl _int_0x42; .align 2; _int_0x42:				;	pushl	$0x00		;	pushl	$0x42		;	jmp	interrupt
.globl _int_0x43; .align 2; _int_0x43:				;	pushl	$0x00		;	pushl	$0x43		;	jmp	interrupt
.globl _int_0x44; .align 2; _int_0x44:				;	pushl	$0x00		;	pushl	$0x44		;	jmp	interrupt
.globl _int_0x45; .align 2; _int_0x45:				;	pushl	$0x00		;	pushl	$0x45		;	jmp	interrupt
.globl _int_0x46; .align 2; _int_0x46:				;	pushl	$0x00		;	pushl	$0x46		;	jmp	interrupt
.globl _int_0x47; .align 2; _int_0x47:				;	pushl	$0x00		;	pushl	$0x47		;	jmp	interrupt
.globl _int_0x48; .align 2; _int_0x48:				;	pushl	$0x00		;	pushl	$0x48		;	jmp	interrupt
.globl _int_0x49; .align 2; _int_0x49:				;	pushl	$0x00		;	pushl	$0x49		;	jmp	interrupt
.globl _int_0x4A; .align 2; _int_0x4A:				;	pushl	$0x00		;	pushl	$0x4A		;	jmp	interrupt
.globl _int_0x4B; .align 2; _int_0x4B:				;	pushl	$0x00		;	pushl	$0x4B		;	jmp	interrupt
.globl _int_0x4C; .align 2; _int_0x4C:				;	pushl	$0x00		;	pushl	$0x4C		;	jmp	interrupt
.globl _int_0x4D; .align 2; _int_0x4D:				;	pushl	$0x00		;	pushl	$0x4D		;	jmp	interrupt
.globl _int_0x4E; .align 2; _int_0x4E:				;	pushl	$0x00		;	pushl	$0x4E		;	jmp	interrupt
.globl _int_0x4F; .align 2; _int_0x4F:				;	pushl	$0x00		;	pushl	$0x4F		;	jmp	interrupt
.globl _int_0x50; .align 2; _int_0x50:				;	pushl	$0x00		;	pushl	$0x50		;	jmp	interrupt
.globl _int_0x51; .align 2; _int_0x51:				;	pushl	$0x00		;	pushl	$0x51		;	jmp	interrupt
.globl _int_0x52; .align 2; _int_0x52:				;	pushl	$0x00		;	pushl	$0x52		;	jmp	interrupt
.globl _int_0x53; .align 2; _int_0x53:				;	pushl	$0x00		;	pushl	$0x53		;	jmp	interrupt
.globl _int_0x54; .align 2; _int_0x54:				;	pushl	$0x00		;	pushl	$0x54		;	jmp	interrupt
.globl _int_0x55; .align 2; _int_0x55:				;	pushl	$0x00		;	pushl	$0x55		;	jmp	interrupt
.globl _int_0x56; .align 2; _int_0x56:				;	pushl	$0x00		;	pushl	$0x56		;	jmp	interrupt
.globl _int_0x57; .align 2; _int_0x57:				;	pushl	$0x00		;	pushl	$0x57		;	jmp	interrupt
.globl _int_0x58; .align 2; _int_0x58:				;	pushl	$0x00		;	pushl	$0x58		;	jmp	interrupt
.globl _int_0x59; .align 2; _int_0x59:				;	pushl	$0x00		;	pushl	$0x59		;	jmp	interrupt
.globl _int_0x5A; .align 2; _int_0x5A:				;	pushl	$0x00		;	pushl	$0x5A		;	jmp	interrupt
.globl _int_0x5B; .align 2; _int_0x5B:				;	pushl	$0x00		;	pushl	$0x5B		;	jmp	interrupt
.globl _int_0x5C; .align 2; _int_0x5C:				;	pushl	$0x00		;	pushl	$0x5C		;	jmp	interrupt
.globl _int_0x5D; .align 2; _int_0x5D:				;	pushl	$0x00		;	pushl	$0x5D		;	jmp	interrupt
.globl _int_0x5E; .align 2; _int_0x5E:				;	pushl	$0x00		;	pushl	$0x5E		;	jmp	interrupt
.globl _int_0x5F; .align 2; _int_0x5F:				;	pushl	$0x00		;	pushl	$0x5F		;	jmp	interrupt
.globl _int_0x60; .align 2; _int_0x60:				;	pushl	$0x00		;	pushl	$0x60		;	jmp	interrupt
.globl _int_0x61; .align 2; _int_0x61:				;	pushl	$0x00		;	pushl	$0x61		;	jmp	interrupt
.globl _int_0x62; .align 2; _int_0x62:				;	pushl	$0x00		;	pushl	$0x62		;	jmp	interrupt
.globl _int_0x63; .align 2; _int_0x63:				;	pushl	$0x00		;	pushl	$0x63		;	jmp	interrupt
.globl _int_0x64; .align 2; _int_0x64:				;	pushl	$0x00		;	pushl	$0x64		;	jmp	interrupt
.globl _int_0x65; .align 2; _int_0x65:				;	pushl	$0x00		;	pushl	$0x65		;	jmp	interrupt
.globl _int_0x66; .align 2; _int_0x66:				;	pushl	$0x00		;	pushl	$0x66		;	jmp	interrupt
.globl _int_0x67; .align 2; _int_0x67:				;	pushl	$0x00		;	pushl	$0x67		;	jmp	interrupt
.globl _int_0x68; .align 2; _int_0x68:				;	pushl	$0x00		;	pushl	$0x68		;	jmp	interrupt
.globl _int_0x69; .align 2; _int_0x69:				;	pushl	$0x00		;	pushl	$0x69		;	jmp	interrupt
.globl _int_0x6A; .align 2; _int_0x6A:				;	pushl	$0x00		;	pushl	$0x6A		;	jmp	interrupt
.globl _int_0x6B; .align 2; _int_0x6B:				;	pushl	$0x00		;	pushl	$0x6B		;	jmp	interrupt
.globl _int_0x6C; .align 2; _int_0x6C:				;	pushl	$0x00		;	pushl	$0x6C		;	jmp	interrupt
.globl _int_0x6D; .align 2; _int_0x6D:				;	pushl	$0x00		;	pushl	$0x6D		;	jmp	interrupt
.globl _int_0x6E; .align 2; _int_0x6E:				;	pushl	$0x00		;	pushl	$0x6E		;	jmp	interrupt
.globl _int_0x6F; .align 2; _int_0x6F:				;	pushl	$0x00		;	pushl	$0x6F		;	jmp	interrupt
.globl _int_0x70; .align 2; _int_0x70:				;	pushl	$0x00		;	pushl	$0x70		;	jmp	interrupt
.globl _int_0x71; .align 2; _int_0x71:				;	pushl	$0x00		;	pushl	$0x71		;	jmp	interrupt
.globl _int_0x72; .align 2; _int_0x72:				;	pushl	$0x00		;	pushl	$0x72		;	jmp	interrupt
.globl _int_0x73; .align 2; _int_0x73:				;	pushl	$0x00		;	pushl	$0x73		;	jmp	interrupt
.globl _int_0x74; .align 2; _int_0x74:				;	pushl	$0x00		;	pushl	$0x74		;	jmp	interrupt
.globl _int_0x75; .align 2; _int_0x75:				;	pushl	$0x00		;	pushl	$0x75		;	jmp	interrupt
.globl _int_0x76; .align 2; _int_0x76:				;	pushl	$0x00		;	pushl	$0x76		;	jmp	interrupt
.globl _int_0x77; .align 2; _int_0x77:				;	pushl	$0x00		;	pushl	$0x77		;	jmp	interrupt
.globl _int_0x78; .align 2; _int_0x78:				;	pushl	$0x00		;	pushl	$0x78		;	jmp	interrupt
.globl _int_0x79; .align 2; _int_0x79:				;	pushl	$0x00		;	pushl	$0x79		;	jmp	interrupt
.globl _int_0x7A; .align 2; _int_0x7A:				;	pushl	$0x00		;	pushl	$0x7A		;	jmp	interrupt
.globl _int_0x7B; .align 2; _int_0x7B:				;	pushl	$0x00		;	pushl	$0x7B		;	jmp	interrupt
.globl _int_0x7C; .align 2; _int_0x7C:				;	pushl	$0x00		;	pushl	$0x7C		;	jmp	interrupt
.globl _int_0x7D; .align 2; _int_0x7D:				;	pushl	$0x00		;	pushl	$0x7D		;	jmp	interrupt
.globl _int_0x7E; .align 2; _int_0x7E:				;	pushl	$0x00		;	pushl	$0x7E		;	jmp	interrupt
.globl _int_0x7F; .align 2; _int_0x7F:				;	pushl	$0x00		;	pushl	$0x7F		;	jmp	interrupt
.globl _int_0x80; .align 2; _int_0x80:				;	pushl	$0x00		;	pushl	$0x80		;	jmp	interrupt
.globl _int_0x81; .align 2; _int_0x81:				;	pushl	$0x00		;	pushl	$0x81		;	jmp	interrupt
.globl _int_0x82; .align 2; _int_0x82:				;	pushl	$0x00		;	pushl	$0x82		;	jmp	interrupt
.globl _int_0x83; .align 2; _int_0x83:				;	pushl	$0x00		;	pushl	$0x83		;	jmp	interrupt
.globl _int_0x84; .align 2; _int_0x84:				;	pushl	$0x00		;	pushl	$0x84		;	jmp	interrupt
.globl _int_0x85; .align 2; _int_0x85:				;	pushl	$0x00		;	pushl	$0x85		;	jmp	interrupt
.globl _int_0x86; .align 2; _int_0x86:				;	pushl	$0x00		;	pushl	$0x86		;	jmp	interrupt
.globl _int_0x87; .align 2; _int_0x87:				;	pushl	$0x00		;	pushl	$0x87		;	jmp	interrupt
.globl _int_0x88; .align 2; _int_0x88:				;	pushl	$0x00		;	pushl	$0x88		;	jmp	interrupt
.globl _int_0x89; .align 2; _int_0x89:				;	pushl	$0x00		;	pushl	$0x89		;	jmp	interrupt
.globl _int_0x8A; .align 2; _int_0x8A:				;	pushl	$0x00		;	pushl	$0x8A		;	jmp	interrupt
.globl _int_0x8B; .align 2; _int_0x8B:				;	pushl	$0x00		;	pushl	$0x8B		;	jmp	interrupt
.globl _int_0x8C; .align 2; _int_0x8C:				;	pushl	$0x00		;	pushl	$0x8C		;	jmp	interrupt
.globl _int_0x8D; .align 2; _int_0x8D:				;	pushl	$0x00		;	pushl	$0x8D		;	jmp	interrupt
.globl _int_0x8E; .align 2; _int_0x8E:				;	pushl	$0x00		;	pushl	$0x8E		;	jmp	interrupt
.globl _int_0x8F; .align 2; _int_0x8F:				;	pushl	$0x00		;	pushl	$0x8F		;	jmp	interrupt
.globl _int_0x90; .align 2; _int_0x90:				;	pushl	$0x00		;	pushl	$0x90		;	jmp	interrupt
.globl _int_0x91; .align 2; _int_0x91:				;	pushl	$0x00		;	pushl	$0x91		;	jmp	interrupt
.globl _int_0x92; .align 2; _int_0x92:				;	pushl	$0x00		;	pushl	$0x92		;	jmp	interrupt
.globl _int_0x93; .align 2; _int_0x93:				;	pushl	$0x00		;	pushl	$0x93		;	jmp	interrupt
.globl _int_0x94; .align 2; _int_0x94:				;	pushl	$0x00		;	pushl	$0x94		;	jmp	interrupt
.globl _int_0x95; .align 2; _int_0x95:				;	pushl	$0x00		;	pushl	$0x95		;	jmp	interrupt
.globl _int_0x96; .align 2; _int_0x96:				;	pushl	$0x00		;	pushl	$0x96		;	jmp	interrupt
.globl _int_0x97; .align 2; _int_0x97:				;	pushl	$0x00		;	pushl	$0x97		;	jmp	interrupt
.globl _int_0x98; .align 2; _int_0x98:				;	pushl	$0x00		;	pushl	$0x98		;	jmp	interrupt
.globl _int_0x99; .align 2; _int_0x99:				;	pushl	$0x00		;	pushl	$0x99		;	jmp	interrupt
.globl _int_0x9A; .align 2; _int_0x9A:				;	pushl	$0x00		;	pushl	$0x9A		;	jmp	interrupt
.globl _int_0x9B; .align 2; _int_0x9B:				;	pushl	$0x00		;	pushl	$0x9B		;	jmp	interrupt
.globl _int_0x9C; .align 2; _int_0x9C:				;	pushl	$0x00		;	pushl	$0x9C		;	jmp	interrupt
.globl _int_0x9D; .align 2; _int_0x9D:				;	pushl	$0x00		;	pushl	$0x9D		;	jmp	interrupt
.globl _int_0x9E; .align 2; _int_0x9E:				;	pushl	$0x00		;	pushl	$0x9E		;	jmp	interrupt
.globl _int_0x9F; .align 2; _int_0x9F:				;	pushl	$0x00		;	pushl	$0x9F		;	jmp	interrupt
.globl _int_0xA0; .align 2; _int_0xA0:				;	pushl	$0x00		;	pushl	$0xA0		;	jmp	interrupt
.globl _int_0xA1; .align 2; _int_0xA1:				;	pushl	$0x00		;	pushl	$0xA1		;	jmp	interrupt
.globl _int_0xA2; .align 2; _int_0xA2:				;	pushl	$0x00		;	pushl	$0xA2		;	jmp	interrupt
.globl _int_0xA3; .align 2; _int_0xA3:				;	pushl	$0x00		;	pushl	$0xA3		;	jmp	interrupt
.globl _int_0xA4; .align 2; _int_0xA4:				;	pushl	$0x00		;	pushl	$0xA4		;	jmp	interrupt
.globl _int_0xA5; .align 2; _int_0xA5:				;	pushl	$0x00		;	pushl	$0xA5		;	jmp	interrupt
.globl _int_0xA6; .align 2; _int_0xA6:				;	pushl	$0x00		;	pushl	$0xA6		;	jmp	interrupt
.globl _int_0xA7; .align 2; _int_0xA7:				;	pushl	$0x00		;	pushl	$0xA7		;	jmp	interrupt
.globl _int_0xA8; .align 2; _int_0xA8:				;	pushl	$0x00		;	pushl	$0xA8		;	jmp	interrupt
.globl _int_0xA9; .align 2; _int_0xA9:				;	pushl	$0x00		;	pushl	$0xA9		;	jmp	interrupt
.globl _int_0xAA; .align 2; _int_0xAA:				;	pushl	$0x00		;	pushl	$0xAA		;	jmp	interrupt
.globl _int_0xAB; .align 2; _int_0xAB:				;	pushl	$0x00		;	pushl	$0xAB		;	jmp	interrupt
.globl _int_0xAC; .align 2; _int_0xAC:				;	pushl	$0x00		;	pushl	$0xAC		;	jmp	interrupt
.globl _int_0xAD; .align 2; _int_0xAD:				;	pushl	$0x00		;	pushl	$0xAD		;	jmp	interrupt
.globl _int_0xAE; .align 2; _int_0xAE:				;	pushl	$0x00		;	pushl	$0xAE		;	jmp	interrupt
.globl _int_0xAF; .align 2; _int_0xAF:				;	pushl	$0x00		;	pushl	$0xAF		;	jmp	interrupt
.globl _int_0xB0; .align 2; _int_0xB0:				;	pushl	$0x00		;	pushl	$0xB0		;	jmp	interrupt
.globl _int_0xB1; .align 2; _int_0xB1:				;	pushl	$0x00		;	pushl	$0xB1		;	jmp	interrupt
.globl _int_0xB2; .align 2; _int_0xB2:				;	pushl	$0x00		;	pushl	$0xB2		;	jmp	interrupt
.globl _int_0xB3; .align 2; _int_0xB3:				;	pushl	$0x00		;	pushl	$0xB3		;	jmp	interrupt
.globl _int_0xB4; .align 2; _int_0xB4:				;	pushl	$0x00		;	pushl	$0xB4		;	jmp	interrupt
.globl _int_0xB5; .align 2; _int_0xB5:				;	pushl	$0x00		;	pushl	$0xB5		;	jmp	interrupt
.globl _int_0xB6; .align 2; _int_0xB6:				;	pushl	$0x00		;	pushl	$0xB6		;	jmp	interrupt
.globl _int_0xB7; .align 2; _int_0xB7:				;	pushl	$0x00		;	pushl	$0xB7		;	jmp	interrupt
.globl _int_0xB8; .align 2; _int_0xB8:				;	pushl	$0x00		;	pushl	$0xB8		;	jmp	interrupt
.globl _int_0xB9; .align 2; _int_0xB9:				;	pushl	$0x00		;	pushl	$0xB9		;	jmp	interrupt
.globl _int_0xBA; .align 2; _int_0xBA:				;	pushl	$0x00		;	pushl	$0xBA		;	jmp	interrupt
.globl _int_0xBB; .align 2; _int_0xBB:				;	pushl	$0x00		;	pushl	$0xBB		;	jmp	interrupt
.globl _int_0xBC; .align 2; _int_0xBC:				;	pushl	$0x00		;	pushl	$0xBC		;	jmp	interrupt
.globl _int_0xBD; .align 2; _int_0xBD:				;	pushl	$0x00		;	pushl	$0xBD		;	jmp	interrupt
.globl _int_0xBE; .align 2; _int_0xBE:				;	pushl	$0x00		;	pushl	$0xBE		;	jmp	interrupt
.globl _int_0xBF; .align 2; _int_0xBF:				;	pushl	$0x00		;	pushl	$0xBF		;	jmp	interrupt

	.text
/
///////////////////////////////////////////////////////////////////////////////
/	TRAP_HANDLER	: routine to handle exceptions, args passed
/	via stack, some exceptions cause an error code to be pushed
/	onto the stack by the processor prior to calling the relevant
/	exception handler, (most dont), in each case the exception
/	handling routine pads the stack image out as required and
/	calls this trap handler with a trap number.This routine
/	basically determines whether or not we were running as kernel
/	at the time of the exception and calls the routine "trap()"
/	with the correct parameters.
///////////////////////////////////////////////////////////////////////////////

/	1. As this is a trap handler and so was called (for some
/	reason) during execution of some routine, we save the state of
/	the running program.  
/	// See 80386 System Software Writers Guide , pp (3-4) for
/	stack layout.

.globl _TRAP; .align 2; _TRAP:
trap_handler:
	pusha				/ 18 /
	pushl	%ds			/  2 /
	pushl	%es			/  2 /
	pushl	%fs			/  2 /
	pushl	%gs			/  2 /

/	2. Now we need to establish ourselves as running in Kernel
/	mode by selecting the Kernel's data space.

	movw	$0x160,%ax		/  4 / %ds can't be affected directly.
	movw	%ax,%ds			/  2 /
	movw	%ax,%es			/  2 /
	movl	%esp, %ebp		/  2 / save a copy of stack pointer.

/	3. The first argument for the trap handler (trap()) is the
/	location of the stack image that we have just created, so we
/	push the current value of %esp.

	pushl	%esp			/  2 /

/	4. Now we need to know whether the process that was running
/	when the exception was detected was part of the Kernel or
/	running in User space.  This we can tell from the %cs stored
/	on the stack. In either case we call trap() but in the user
/	space case we must do some extra checking when done with
/	trap() to see if a context switch is warranted or not.

	movl	(0x0010*4)(%ebp), %eax
	btl	$17,%eax
	jc	v86_trap_handler
	movl	(0x000F*4)(%ebp), %eax	/  2 /	
	testw	$IS_LDT_SEL,%ax		/  2 /
	jnz	user_trap_handler	/ ** /

///////////////////////////////////////////////////////////////////////////////
/ 	5. Kernel mode case : call trap(), then remove stack image created 
/	earlier, and return from whence we came.
///////////////////////////////////////////////////////////////////////////////

kernel_trap_handler:
	call 	_trap		/ ** /
	addl	$0x04,%esp		/  2 / gets us to bottom of stack image
					/      created above.
short_user_ret:
kernel_return:
popl	%gs		;	popl	%fs		;	popl	%es		;	popl	%ds		;	popa			;	addl	$0x08, %esp	;	iret

///////////////////////////////////////////////////////////////////////////////
/ 	5. User mode case : call trap(), check to see if a context switch is 
/	warranted then remove stack image created earlier, and return from 
/	whence we came.
///////////////////////////////////////////////////////////////////////////////

v86_trap_handler:
	call 	_trapv86		/ ** /
	addl	$0x04,%esp		/  2 / gets us to bottom of stack image
	jmp	user_return

user_trap_handler:
	call 	_trap		/ ** /
	addl	$0x04,%esp		/  2 / gets us to bottom of stack image
					/      created above.

user_return:
	cmpl	$0x01, _need_ast	/  4 / See if context switch flag is set
	jne	check_curr_ipl		/ ** /

user_cswitch_check:
	movl	$0x00, _need_ast	/  4 / reset context switch flag.
	pushl	%esp			/  2 / save stack ptr for return
	call	_astintr		/ ** / call context switch routine.
	addl	$0x04, %esp		/  2 / clear stack ptr.
	
check_curr_ipl:
	cmpl	$0x00,_curr_ipl	/  4 / check current ipl
	jz 	final_return		/ ** / see if it is zero.
	jmp	ipl0panic

final_return:
	popl	%gs			/  2 / pop stack structure created
	popl	%fs			/  2 /
	popl	%es			/  2 /
	popl	%ds			/  2 /
	popa				/ 18 /
	
	addl	$0x08,%esp		/  2 / remove hardware structure 
	iret				/275 /
/
///////////////////////////////////////////////////////////////////////////////
/ 	SYSTEM_CALL : a routine to handle system calls which arrive
/	via call gates. The hardware places the same stack image as
/	for a trap EXCEPT that the flags register (EFLAGS) is not
/	pushed, INSTEAD the trap gate is set up such that 1 longword
/	on the stack is set aside for parameters to be passed, also
/	there are no trap #'s or error codes passed, so we set aside
/	space for them such that we maintain a consistant stack image
/	and can take advantage of stack offsets used by various pieces
/	of code.  Basically when done we call syscall() with the same
/	stack image format that exception() above uses to call trap().
/	Basically system calls are treated the same as exceptions, in
/	that we figure out whether we have a regular or a 1
/	specific system call, and, if regular we call syscall(),
/	otherwise we call MACH_sys_call(), which basically forms the
/	address of the system_call handler and invokes it.
///////////////////////////////////////////////////////////////////////////////

.globl _system_call; .align 2; _system_call:

/	1. Form stack image as above, and pad out hardware defined
/	fields.  There are 3 fields that are different here, call
/	gates do not cause the flags register to be pushed as do trap
/	gates, so the call gate is defined such that space is
/	allocated for 1 parameter to be passed from the user stack to
/	the kernel/system call stack. This paramater happens to be
/	placed where the flags register would be put in a trap call,
/	in fact the last pushed entity is copied from the user stack
/	to the kernel stack, so we just rewrite it with the flags
/	register. The other 2 fields that are different are the trap
/	number and error code fields, which are easy to dummy out as
/	they are the last things that would be pushed by the processor
/	had this been a trap call anyway.

	pushf				/  4 / pad out trap number field.
	pushf				/  4 / dummy out error code field.
	pusha				/ 18 /
	pushl	%ds			/  2 /
	pushl	%es			/  2 /
	pushl	%fs			/  2 /
	pushl	%gs			/  2 /

/	2. Now we wish to push the flags register onto the stack so as
/	to make it consistant with #defines used elsewhere. The flags
/	register is not directly accessable, so we push it onto the
/	stack ( already done to dummy out trap# and error code
/	fields), and then simply copy it from where it is to where we
/	want it to be.

	movl	(0x000D*4)(%esp), %eax /  4 /
	movl	%eax,(0x0010*4)(%esp)	/  4 /

/	3. Now we change to the kernel data space, as we are now in
/	kernel mod and copy the current stack pointer.

	movw	$0x160,%ax		/  2 /
	movw	%ax,%ds			/  2 /
	movw	%ax,%es			/  2 /
	movl	%esp,%ebp		/  2 /

/	4. Now we must determine whether this is a common system call
/	or whether this is a special 1 system call demanding quick
/	attention.  We do this by examining the sys_call number passed
/	via %eax (now on the stack). If the number is less then -0x09
/	then this is a special 1 system call.

	movl	(0x000B*4)(%esp),%eax	/  4 /
	cmpl	$-0x09,%eax		/  2 /
	jnl	user_sys_call		/ ** / 

///////////////////////////////////////////////////////////////////////////////
/ 	MACH_SYS_CALL : a quick subroutine, which instead of calling
/ 	syscall(), calculates the sys_call handling routine address
/ 	and invokes same. This of course only works for a small subset
/ 	of the possible range of system calls.
///////////////////////////////////////////////////////////////////////////////

/	1. Firstly the system call number passed is less than -0x09,
/	so negate it making it positive so that it can be used as an
/	array index. Then we check it aginst boundary limits and call
/	the routine which actually does the real work.

MACH_sys_call:
	negl	%eax			/  2 /
	cmpl	%eax,_mach_trap_count /  2 /
	jge	call_MACH_trap		/ ** / this is a -ve number inverted

mach_failure:
	movl	$		5,%eax	/  2 /
	jmp	user_return		/ ** /


/	CALL_MACH_TRAP : %eax is used as an index into a trap handler
/	table, where we can get the trap handler address and the
/	number of parameters to pass to it. Then we use copyin() to
/	get the parameters from user stack into kernel stack.

call_MACH_trap:
	shl	$0x03, %eax		/  3 / adapt index to array element size
	movswl	_mach_trap_table(%eax),%ecx	/ arg. count
					/  4 / 
	movl	_mach_trap_table+0x04(%eax), %ebx	/ call handler
					/  4 /
	subl	$0x04,%ecx		/  2 / argv[0] is routine name
					/      so we modify arg. count

/	3. Now take stack pointer and modify it to allow room for the
/	syscall parameters, call copyin() to get the paramaters from
/	user space stack

	subl	%ecx,%esp		/   2 / adjust stack pointer
	movl	%esp,%eax		/   2 / save this stack pointer
		
 	pushl	%ecx			/  2 / push arg count for copyin()
	pushl	%eax			/  2 / push stack pointer for copyin()
	movl	(0x0011*4)(%ebp), %eax /  4 / get user stk pointer (user args)
	addl	$0x04,%eax		/  2 / adjust to point to parameters
	push	%eax			/  2 / push this for copyin()
	call	_copyin		/ ** / copyin(arg#,*kern_stk,*user_stk)
	
	addl	$0x0C,%esp		/  2 / get copyin() parameters off stack
	
	call	*%ebx			/ ** / call MACH_system_call handler.

	movl	%ebp,%esp		/  2 / pop system call parameters
	movl	%eax,(0x000B*4)(%esp)	/  4 / set return value
	movl	%edx,(0x0009*4)(%esp)	/  4 / 
	
	




	call	_current_thread			/ get the thread




	movl	124(%eax),%eax	/ point to task U-area
	movl	0(%eax),%eax	/ then to proc table slot
	orl	%eax, %eax
	jz	alt_call_restore_state	/ skip if no proc table

	movzbl	23(%eax),%edx
	orl	24(%eax),%edx
	jz	alt_call_restore_state





alt_call_restore_state:
	
	jmp	user_return		/ ** / 

/ 	5. If a common system call, push stack pointer, and call syscall(), on 
/	return remove stack pointer from stack, and return to the user space 
/	routine.

user_sys_call:
# 1214 "locore.s"

	pushl	%esp			/  2 /
	call	_syscall		/ ** /
	addl	$0x04,%esp		/  2 /
	jmp	user_return		/ ** /
/
///////////////////////////////////////////////////////////////////////////////
/ 	interrupt :  routine to handle interrupts from external events, this 
/	often requires a change of interrupt priority level, and a call of the 
/	relevant interrupt routine. This routine disables and enable interrupt 
/	as necessary and handles the hardware handshaking with the interrupt 
/	controller hardware.
///////////////////////////////////////////////////////////////////////////////
.globl _INTERRUPT; .align 2; _INTERRUPT:
interrupt:
	pusha				/ 18 /
	pushl	%ds			/  2 /
	pushl	%es			/  2 /
	pushl	%fs			/  2 /
	pushl	%gs			/  2 /

/ 	1. Now that we are in Kernel mode we must select the Kernel data area, 
/	and save a copy of the current stack pointer.

	movw	$0x160,%ax		/  2 /
	movw	%ax,%ds			/  2 /
	movw	%ax,%es			/  2 /
	movl	%esp,%ebp		/  2 /










/ 	1a. Now we must acknowledge the interrupt and issue an EOI command to 
/	the pics, we send a NON-SPECIFIC EOI, as we assume that the pic 
/	automatically interrupts us with only the highest priority interrupt.

	movl	_master_icw,%edx	/  2 / EOI for master.
	movw	_PICM_OCW2,%ax	/  2 /
	outb	%al, %dx				/  4 /

	movw	_PICS_OCW2,%ax	/  2 / EOI for slave.
	addw	$	0x80,%dx		/  2 /
	outb	%al, %dx				/  4 /

/ 	2. Now we must change the interrupt priority level, with interrupts 
/	turned off. First we get the interrupt number off the stack and get the
/	interrupt level associated with it, then we call set_spl().

	movl	(0x000C*4)(%ebp), %edi	/  2 /

/	check for spurious interrupt
	movl	_master_icw, %edx
/	AT's slave the second pic on IRQ2
	cmpl	$2, %edi			/ IRQ2
	je	int_check
	cmpl	$15, %edi			/ IRQ15
	jne	int_ok
	addw	$	0x80,%dx			/  2 /
int_check:
	inb	%dx, %al					/ read ISR
	testb	$0x80, %al			/ return if IS7 is off
	jz	interrupt_return

int_ok:
	movzbl	_intpri(%edi), %eax	/  4 / intpri[int#]  
	cmpl	$                    8, %eax		/  2 /
	je	clock_int_handler	/ ** / 
	cmpl	_curr_ipl, %eax	/  2 / 
	je	no_spl			/ ** /

	call	set_spl			/ ** /

/	3. If the new priority is                     8 this is a special case and means that 
/	this is a clock interrupt, in which case we call a special clock 
/	interrupt handler.

/ 	4. Otherwise, re-enable interrupts and call the relevant interrupt 
/	handler as per the ivect[] array set up in pic_init().

no_spl:
	movl	%eax, %esi		/  2 /

	sti
/	pushl	%edi			/  2 / push int# as int handler arg
	pushl	_iunit(,%edi,4)	/  2 / push unit# as int handler arg
	movl	$_ivect, %ebx	/  2 / get base of ivect[] array
	call	*(%ebx, %edi, 4)	/  4 / *ivect[int#]()
	addl	$0x04, %esp		/  2 / on return remove int# from stack
	cli				/  3 / disable interrupts

/	 5. Having dealt with the interrupt now we must return to the previous 
/	 interrupt priority level, this is done with interrupts turned off.

	movl	_curr_ipl, %eax
	cmp	%esi, %eax	/  2 / check to see if splx needed
	je	no_splx
	movl	%esi, %eax
	call	iret_spl
no_splx:

/	6. Check to see if interrupt occurred in Kernel or user mode
/	and use the appropriate return algorithm.

interrupt_return:
movl	(0x000F*4)(%ebp), %eax	;	testw	$IS_LDT_SEL,%ax		;	jnz	user_return		;	movl	(0x0010*4)(%ebp), %eax;	btl	$17,%eax		;	jc	user_return		;	popl	%gs		;	popl	%fs		;	popl	%es		;	popl	%ds		;	popa			;	addl	$0x08, %esp	;	iret			

///////////////////////////////////////////////////////////////////////////////
/	CLOCK_INT_HANDLER : whereas for any other interrupt, newly
/	arriving interrupts are suppressed only while the interrupt
/	priority level is being changed, this interrupt warrants
/	having new interrupts disabled completely. Here we push the
/	old 0x000F:IP and call hardclock(), in addition if we were
/	interrupted during a user level function AND if the flag
/	dotimein is set, then we call softclock(), on return we reset
/	the interrupt priority level back to what it was before.
///////////////////////////////////////////////////////////////////////////////

clock_int_handler:

	movl	(0x0010*4)(%ebp), %eax
	btl	$17,%eax
	jnc	1f
	pushl	$USER_CS
	jmp	2f
1:	movl	(0x000F*4)(%ebp),%eax	/  4 /
	pushl	%eax			/  2 /
2:	movl	(0x000E*4)(%ebp),%eax	/  4 /
	pushl	%eax			/  2 /
	call	_hardclock		/ ** / hardclock(int#,cs,ip)
	addl	$0x08, %esp		/  2 /
	cmpl	$0x00,_curr_ipl	/  2 / see if softclock() should
	jnz	int_return		/ ** / be run, if not return.
	cmpl	$0x00,_dotimein	/  2 /
	jz	int_return
	
	movl	$0x00,_dotimein	/  2 /
	call	_spl1		/ ** /	 this piece at spl1
	sti
	movl	(0x0010*4)(%ebp), %eax
	btl	$17,%eax
	jnc	1f
	pushl	$USER_CS
	jmp	2f
1:	movl	(0x000F*4)(%ebp),%eax	/  4 /
	pushl	%eax			/  2 /
2:	movl	(0x000E*4)(%ebp),%eax	/  4 /
	pushl	%eax			/  2 /
	call 	_softclock		/ ** / softclock(int#,cs,ip)
	addl	$0x08,%esp		/  2 /
	cli				/  3 /
	call	_spl0		/ ** /
int_return:
movl	(0x000F*4)(%ebp), %eax	;	testw	$IS_LDT_SEL,%ax		;	jnz	user_return		;	movl	(0x0010*4)(%ebp), %eax;	btl	$17,%eax		;	jc	user_return		;	popl	%gs		;	popl	%fs		;	popl	%es		;	popl	%ds		;	popa			;	addl	$0x08, %esp	;	iret			

.globl _Bpt; .align 2; _Bpt:
.globl _bpt; .align 2; _bpt:
	pushl	%ebp
	movl	%esp, %ebp
	.byte	0xcc
	leave
	ret
/
///////////////////////////////////////////////////////////////////////////////
/	SPLn : change interrupt priority level to that in %eax
/	SPLOFF : disable all interrupts, saving interrupt flag
/	SPLON: re-enable interrupt flag, undoes sploff()
/	Warning: SPLn and SPLOFF aren't nestable.  That is,
/		a = sploff();
/		...
/		b = splmumble();
/		...
/		splx(b);
/		...
/		splon(a);
/	is going to do the wrong thing.
///////////////////////////////////////////////////////////////////////////////
# 1413 "locore.s"



		.text

.globl _spl0; .align 2; _spl0:

	movl    $           0, %eax
	jmp	set_spl

.globl _splsoftclock; .align 2; _splsoftclock:
.globl _spl1; .align 2; _spl1:

	movl    $           1, %eax
	jmp	set_spl

.globl _spl2; .align 2; _spl2:

	movl    $           2, %eax
	jmp	set_spl

.globl _spl3; .align 2; _spl3:

	movl    $           3, %eax
	jmp	set_spl

.globl _splnet; .align 2; _splnet:
.globl _splhdw; .align 2; _splhdw:
.globl _spl4; .align 2; _spl4:

	movl    $           4, %eax
	jmp	set_spl

.globl _splbio; .align 2; _splbio:
.globl _spl5; .align 2; _spl5:

	movl    $           5, %eax
	jmp	set_spl

.globl _spltty; .align 2; _spltty:
.globl _spl6; .align 2; _spl6:

	movl    $           6, %eax
	jmp	set_spl

.globl _splimp; .align 2; _splimp:
.globl _splclock; .align 2; _splclock:
.globl _splvm; .align 2; _splvm:
.globl _splsched; .align 2; _splsched:
.globl _splhigh; .align 2; _splhigh:
.globl _splhi; .align 2; _splhi:
.globl _spl7; .align 2; _spl7:

	cli				/  3 / disable interrupts
	movl	_curr_ipl,%eax	/  4 /
	movl	$          8, _curr_ipl	/  2 /
	ret				/ 10 /
/					------
/					  19

.globl _sploff; .align 2; _sploff:				/  7 /
	pushf				/  2 / Flags reg NOT accessable
	popl	%eax			/  2 / push onto stk, pop it into reg.
	cli				/  3 / DISABLE ALL INTERRUPTS
	ret				/  7 /
/					------
/					  21

.globl _splon; .align 2; _splon:				/  7 /
	pushl	MASK(%esp)		/  4 / Flags regs not directly settable.
	popf				/  4 / push value, pop into flags reg.
					/      IF ints were enabled before 
					/	then they are re-enabled now.
	ret				/  7 /
/					------
/					  22

///////////////////////////////////////////////////////////////////////////////
/	SPL : this routine sets the interrupt priority level, it is
/	called from one of the above spln subroutines ONLY, NO-ONE
/	should EVER call set_spl directly as it assumes that the
/	parameters passed in are gospel.  
/	SPLX	: This routine is used to set the ipl BACK to a level
/	it was at before spln() was called, which in turn calls
/	set_spl(), which returns (via %eax) the value of the curr_ipl
/	prior to spln() being called, this routine is passed this
/	level and so must check that it makes sense and if so then
/	simply calls set_spl() with the appropriate interrupt level.
///////////////////////////////////////////////////////////////////////////////

.globl _splx; .align 2; _splx:

	movl	0x04(%esp),%eax		/  4 / get interrupt level from stack

	cmpl	$0x00,%eax		/  2 / check if  < 0
	jl	splxpanic		/  3 /

	cmpl	$                    8,%eax		/  2 / check if too high
	ja	splxpanic		/  3 /
/					------
/					  14

///////////////////////////////////////////////////////////////////////////////
/	SET_SPL : This routine sets curr_spl, ipl, and the pic_mask as
/	appropriate, basically given an spl# to adopt, see if it is
/	the same as the old spl#, if so return. If the numbers are
/	different, then set curr_spl, now check the corresponding ipl
/	for the spl requested, if they are the same then return
/	otherwise set the new ipl and set the pic masks accordingly.
///////////////////////////////////////////////////////////////////////////////

set_spl:				

	pushl	%ebp			/ 2 /
	movl	%esp,%ebp		/ 2 /
	cli				/ 3 / disable interrupts
	movl	_curr_ipl, %edx	/ 4 / get OLD ipl level
	pushl	%edx			/ 2 / save old level for return
	movl	%eax,_curr_ipl	/ 4 / set NEW ipl level
	cmpl	$                    8, %eax		/  2 / if                     8
	je	spl_intoff		/  3 / return with interrupt off
	movw	_pic_mask(,%eax,2), %ax / 5 /
	cmpw	_curr_pic_mask,%ax 	/ 5 /
	je	spl_return		/ 7 /
	movw	%ax, _curr_pic_mask
	
movl	_master_ocw,%edx	;	outb	%al, %dx				;	addw	$	0x80,%dx		;	movb	%ah,%al			;	outb	%al, %dx				/16 /
spl_return:
	sti				/ 3 /
spl_intoff:
	popl	%eax			/ 2 / return old level
	pop	%ebp			/ 2 /
	ret				/10 /
/					-----
/				         79

iret_spl:				
	cli				/ 3 / disable interrupts
	movl	%eax,_curr_ipl	/ 4 / set NEW ipl level
/                     8 is not possible, for we can not be returning to splhi since
/ we'd never be interrupted.
/	cmpl	$                    8, %eax		/  2 / if                     8
/	je	1f
	movw	_pic_mask(,%eax,2), %ax / 5 /
	cmpw	_curr_pic_mask,%ax 	/ 5 /
	je	1f
	movw	%ax, _curr_pic_mask
	
movl	_master_ocw,%edx	;	outb	%al, %dx				;	addw	$	0x80,%dx		;	movb	%ah,%al			;	outb	%al, %dx				/16 /
1:
	ret				/10 /
/					-----
/				         79

/


///////////////////////////////////////////////////////////////////////////////
/	These routine get/set various registers that are not directly
/	accessable by NORMAL user level routines.
///////////////////////////////////////////////////////////////////////////////





.globl __clts; .align 2; __clts:
	clts
	ret





.globl __fnclex; .align 2; __fnclex:
	fnclex
	ret





.globl __fninit; .align 2; __fninit:
	fninit
	ret






.globl __fldcw; .align 2; __fldcw:
	fldcw	4(%esp)
	ret






.globl __fstcw; .align 2; __fstcw:
	pushl	%eax
	fstcw	(%esp)
	popl	%eax
	ret






.globl __fnstsw; .align 2; __fnstsw:
	pushl	%eax
	fnstsw	(%esp)
	popl	%eax
	ret











.globl _savefp; .align 2; _savefp:
	clts
	movl	4(%esp), %eax
	fnsave	(%eax)
	fnclex
	fwait
	ret






.globl _restorefp; .align 2; _restorefp:
	clts
	movl    4(%esp), %eax
	frstor  (%eax)
	ret

.globl _setts; .align 2; _setts:
	movl    %cr0, %eax
	orl     $0x08, %eax
	movl    %eax, %cr0
	ret

.globl _flushtlb; .align 2; _flushtlb:				/  7 /
	movl	%cr3, %eax		/  2 /
	movl	%eax, %cr3		/  2 /
	ret				/  7 /
/					------
/					  18

.globl __cr2; .align 2; __cr2:				/  7 /
	movl	%cr2, %eax		/  2 /
	ret				/  7 /
/					------
/					  16

.globl __cr3; .align 2; __cr3:				/  7 /
	movl	%cr3, %eax		/  2 /
	andl	$0x7FFFFFFF,%eax	/  2 /
	ret 				/  7 /
/					------
/					  18

.globl __dr0; .align 2; __dr0:				/  7 /
	movl    %db0, %eax		/  2 /
	ret				/  7 /
/					------
/					  16

.globl __dr1; .align 2; __dr1:				/  7 /
	movl    %db1, %eax		/  2 /
	ret				/  7 /
/					------
/					  16 

.globl __dr2; .align 2; __dr2:				/  7 /
	movl    %db2, %eax		/  2 /
	ret				/  7 /
/					------
/					  16

.globl __dr3; .align 2; __dr3:				/  7 /
	movl    %db3, %eax		/  2 /
	ret				/  7 /
/					------
/					  16

.globl __dr6; .align 2; __dr6:				/  7 /
	movl    %db6, %eax		/  2 /
	ret				/  7 /
/					------
/					  16

.globl __dr7; .align 2; __dr7:				/  7 /
	movl    %db7, %eax		/  2 /
	ret				/  7 /
/					------
/					  16

.globl __wdr0; .align 2; __wdr0:				/  7 /
	movl    0x04(%esp), %eax	/  2 /
	movl    %eax, %db0		/  2 /
	ret				/  7 /
/					------
/					  18

.globl __wdr1; .align 2; __wdr1:				/  7 /
	movl    0x04(%esp), %eax	/  2 /
	movl    %eax, %db1		/  2 /
	ret				/  7 /
/					------
/					  18

.globl __wdr2; .align 2; __wdr2:				/  7 /
	movl    0x04(%esp), %eax	/  2 /
	movl    %eax, %db2		/  2 /
	ret				/  7 /
/					------
/					  18

.globl __wdr3; .align 2; __wdr3:				/  7 /
	movl    0x04(%esp), %eax	/  2 /
	movl    %eax, %db3		/  2 /
	ret				/  7 /

.globl __wdr6; .align 2; __wdr6:				/  7 /
	movl    0x04(%esp), %eax	/  2 /
	movl    %eax, %db6		/  2 /
	ret				/  7 /

.globl __wdr7; .align 2; __wdr7:				/  7 /
	movl    0x04(%esp), %eax	/  2 /
	movl    %eax, %db7		/  2 /
	ret				/  7 /

.globl _get_tr; .align 2; _get_tr:				/  7 /
	xorl	%eax, %eax		/  2 /
	str	%ax			/  2 /
	ret				/  7 /

.globl _loadtr; .align 2; _loadtr:				/  7 /
	movw	0x04(%esp), %ax		/  2 /
	ltr	%ax			/ 23 /
	ret				/  7 /

.globl _get_ldt; .align 2; _get_ldt:				/  7 /
	pushl	%ebp			/  2 /
	movl	%esp,%ebp		/  2 /
	
	movl	0x08(%ebp),%eax		/  4 /
	sldt	%eax			/  2 /
	popl	%ebp			/  2 /
	ret				/  7 /

.globl _set_ldt; .align 2; _set_ldt:
	pushl	%ebp			/  7 /
	movl	%esp,%ebp		/  2 /
	
	movl	0x08(%ebp),%eax		/  4 /
	lldt	%eax			/ 20 /
	popl	%ebp			/  2 /
	ret				/  7 /

.globl _get_gdt; .align 2; _get_gdt:				/  7 /
	pushl	%ebp			/  2 /
	movl	%esp,%ebp		/  2 /
	
	movl	0x08(%ebp),%ebx		/  4 /
	sgdt	(%ebx)			/  9 /
	popl	%ebp			/  2 /
	ret				/  7 /

.globl _get_cr3; .align 2; _get_cr3:				/  7 /
	pushl	%ebp			/  2 /
	movl	%esp,%ebp		/  2 /
	
	movl	%cr3,%eax		/  2 /
	popl	%ebp			/  2 /
	ret				/  7 /

	.data
	.align 2
cr3_kludge:



	.long	0


	.text
.globl _set_cr3; .align 2; _set_cr3:				/  7 /
	pushl	%ebp			/  2 /
	movl	%esp,%ebp		/  2 /
	
	movl	0x08(%ebp),%eax		/  4 /

/ Setting the high order bit of the page directory base is a workaround
/ for 386 B-step errata #21. It works on Olivetti, Intel, and Prime
/ machines, but it is not guaranteed to work on all systems.

	orl     cr3_kludge, %eax
	movl	%eax,%cr3		/  2 /
	popl	%ebp			/  2 /
	ret				/  7 /
/
# 1846 "locore.s"

/////////////////////////////////////////////////////////////////////////////
/	THREAD_BOOTSTRAP : tbd
/////////////////////////////////////////////////////////////////////////////

.globl _thread_bootstrap; .align 2; _thread_bootstrap:
	call	_spl0
/	incl	cnt+V_SYSCALL
	jmp     user_return	/ jump to common return to user code

/
/			PANIC CALLS
ipl0panic:
	pushl	_curr_ipl
	pushl	$ipl0panic1
	call	_printf
	jmp	panic_hlt

splpanic:
	pushl	%edx		/ current level
	pushl	%eax		/ new level
	pushl	$splpanic2
	call	_printf
	jmp	panic_hlt

spl7panic:
	pushl	$0
	pushl	%eax
	pushl	$spl7panic2
	call	_printf
	jmp	panic_hlt

splxpanic:
	pushl	_curr_ipl	/ current level
	pushl	%eax		/ new level
	pushl	$splxpanic2
	call	_printf
	jmp	panic_hlt

splintpanic:
	pushl	%edx		/ current level
	pushl	%eax		/ new level
	pushl	$splintpanic2
	call	_printf
	jmp	panic_hlt

splxintpanic:
	cli
	pushl	%edx		/ current level
	pushl	%eax		/ new level
	pushl	$splxintpanic2
	call	_printf

panic_hlt:
	


	pushl	$splpanicstr
	call	_panic
	hlt
	.data
splpanicstr:
	.ascii	"splpanic"
	.byte	0
ipl0panic1:
	.ascii	"ret_user(%x): IPL not zero at return to user mode\n"
	.byte	0
splpanic2:
	.ascii	"spl(%x, %x): logic error in locore.s\n"
	.byte	0
spl7panic2:
	.ascii	"spl7(%x, %x): logic error in locore.s\n"
	.byte	0
splxpanic2:
	.ascii	"splx(old %x, new %x): logic error in locore.s\n"
	.byte	0
splintpanic2:
	.ascii	"splint(%x, %x): logic error in locore.s\n"
	.byte	0
splxintpanic2:
	.ascii	"splxint(%x, %x): logic error in locore.s\n"
	.byte	0
	.text
/

.globl _vstart; .align 2; _vstart:				/  7 /
	call	_i386_init

/ Set up for floating point.  Check for any chip at all by trying to
/ do a reset.  if that succeeds, differentiate via cr0.

	clts                            / clear task switched bit in CR0
	fninit                          / initialize chip
	fstsw	%ax			/ get status
	orb	%al,%al			/ status zero? 0 = chip present
	jnz     mathemul                / no, use emulator

/ at this point we know we have a chip of some sort; 
/ use cr0 to differentiate.

	movl    %cr0,%edx               / check for 387 present flag
	testl	$CR0_ET,%edx            / ...
	jz      is287                   / z -> 387 not present
	movb    $FP_387,_fp_kind	/ we have a 387 chip
	jmp     mathchip

/ No 387; determine whether we have a 80287.
is287:
/	fsetpm				/ set the 80287 into protected mode
	.byte	0xe4, 0xdb, 0x9b
	movb	$FP_287,_fp_kind	/ we have a 287 chip

/ We have either a 287 or a 387.
mathchip:



	andl    $-1^(CR0_TS|CR0_EM),%edx / clear emulate math chip bit

	orl     $CR0_MP,%edx            / set math chip present bit
	movl    %edx,%cr0               / in machine status word
	jmp	cont

mathemul:
/ Assume we have an emulator
	movl	%cr0,%edx



	andl	$-1^CR0_MP,%edx

	orl     $CR0_EM,%edx            / set math emulation
	movl	%edx,%cr0
	movb	$FP_SW,_fp_kind	/ signify that we are emulating
cont:
/ BIOS/DOS hack				/ this says don't test memory
	movl	$0xc0000000, %edx
	addl	$0x472, %edx		/ on reboot/reset
	movw	$0x1234, %ax		/ pretty obscure
	movw	%ax, (%edx)
/ BIOS/DOS hack
	call	_setup_main

/ Task switch to the first thread.
/	This is a 16 bit long jump.
	.byte	0xEA
	.long	0
	.word	0x170

	pushl	$panic_msg1
	jmp	setup_hlt

.globl _system_bootstrap; .align 2; _system_bootstrap:
	call	_main
/	Should never get here
	pushl	$panic_msg
setup_hlt:
	call	_panic
	jmp	setup_hlt

.globl _start_init; .align 2; _start_init:
	addl	$8,%esp			/ return addresses
	pushl	%esp
	call	_init_regs
	popl	%eax





	jmp	user_return

panic_msg:
	.ascii	"First thread returned\n"
	.byte	0
panic_msg1:
	.ascii	"Jump to tss failed\n"
	.byte	0



/////////////////////////////////////////////////////////////////////////////
/	The following routines read and write I/O adress space
/		outb (port_addr, val)
/		outw (port_addr, val)
/		outl (port_addr, val)
/		loutw(port_addr, mem_addr, cnt)
/	unchar	inb  (port_addr     )
/	ushort	inw  (port_addr     )
/	long	inl  (port_addr     )
/	ushort	linw (port_addr, mem_addr, cnt)
/////////////////////////////////////////////////////////////////////////////






.globl _outb; .align 2; _outb:				/  7 / 
	movw	 4(%esp), %dx		/  4 /
	movb	 8(%esp), %al		/  4 /
	outb	%al, %dx				/  4 /




	ret				/  7 /
/					------
/					  26
.globl _outw; .align 2; _outw:				/  7 /	outw ( port#, data )
	movw	 4(%esp), %dx		/  4 /
	movw	 8(%esp), %ax		/  4 /
	.byte 0x66				
	outl	%eax, %dx				/  4 /
	ret				/  7 /
/					------
/					  26
.globl _outl; .align 2; _outl:				/  7 /	outl ( port#, data)
	movw	 4(%esp), %dx		/  4 /
	movl	 8(%esp), %eax		/  4 /
	outl	%eax, %dx				/  4 /
	ret				/  7 /
/					------
/					  26
.globl _loutw; .align 2; _loutw:				/  7 /	loutw( port#, addr, cnt)
	movl	%esi, %eax		/  ? /

	movl	 4(%esp),%edx		/  4 /
	movl	 8(%esp),%esi		/  4 /
	movl	12(%esp),%ecx	/  4 /
					/  6 /
	cld
	rep				/  5 /
	.byte 0x66
	outsl				/  8 /

	movl	%eax, %esi		/  ? /
	ret				/  7 /
/					------
/					  ??
.globl _loutb; .align 2; _loutb:				/  7 /	loutw( port#, addr, cnt)
	movl	%esi, %eax		/  ? /

	movl	 4(%esp),%edx		/  4 /
	movl	 8(%esp),%esi		/  4 /
	movl	12(%esp),%ecx	/  4 /
					/  6 /
	cld
	rep				/  5 /
	.byte 0x66
	outsb				/  8 /

	movl	%eax, %esi		/  ? /
	ret				/  7 /
/					------
/					  50 + (0x000A * 11)

.globl _inb; .align 2; _inb:				/  7 /
	subl    %eax, %eax		/  2 /	clear 0x000B
	movw	 4(%esp), %dx		/  4 /
	inb	%dx, %al				/  4 /







	ret				/  7 /
/					------
/					  24

.globl _inw; .align 2; _inw:				/  7 /
	subl    %eax, %eax		/  2 /
	movw	 4(%esp), %dx		/  4 /
	.byte 0x66
	inl	%dx, %eax				/  4 /
	ret				/  7 /
/					------
/					  24

.globl _inl; .align 2; _inl:				/  7 /
	movw	 4(%esp), %dx		/  4 /
	inl	%dx, %eax				/  4 /
	ret				/  7 /
/					------
/					  22

.globl _linw; .align 2; _linw:				/  7 /
	movl	%edi, %eax		/  ? /

	movl	 4(%esp),%edx		/  4 /
	movl	 8(%esp),%edi		/  4 /
	movl	12(%esp),%ecx	/  4 /
					/  6 /
	cld
	rep				/  5 /
	.byte 0x66
	insl				/  6 /

	movl	%eax, %edi		/  ? /
	ret				/  7 /
/					------
/					  ??

.globl _linb; .align 2; _linb:				/  7 /
	movl	%edi, %eax		/  2 /

	movl	 4(%esp),%edx		/  4 /
	movl	 8(%esp),%edi		/  4 /
	movl	12(%esp),%ecx	/  4 /
					/  6 /
	cld
	rep				/  5 /
	.byte 0x66
	insb				/  6 /

	movl	%eax, %edi		/  2 /
	ret				/  7 /
/					------
/					  50 + (0x000A * 11)

///////////////////////////////////////////////////////////////////////////////
/	addupc(pc, &u.u_prof, tics)
///////////////////////////////////////////////////////////////////////////////

/ offset relative to u.u_prof.

.globl _addupc; .align 2; _addupc:
	pushl	%ebp
	movl	%esp, %ebp		/ set up frame
	
	pushl	%edi

	movl	UPROF(%ebp), %ecx	/ &u.u_prof
	movl	PC(%ebp), %eax		/ pc
	subl	12(%ecx), %eax	/ corrected pc
	jl	addret1
	mull	16(%ecx)		/ Multiply by fractional result
	shrdl	$16,%edx,%eax
	andl	$0xFFFFFFFE, %eax
	cmpl	8(%ecx), %eax	/ length
	jg	addret1
	addl	4(%ecx), %eax	/ base
	movl	%eax, %edi		/ Save during userwrite call
	pushl	$4			/ 12
	pushl	%edi			/ ADDRESS
	call	_userwrite
	addl	$8, %esp
	orl	%eax,%eax
	jnz	adderr
	call	_current_thread
	movl	$adderr,104(%eax)
	movswl	(%edi), %ecx
	addl	TICS(%ebp), %ecx
	movw	%ecx, (%edi)
addret1:
	movl	$0,104(%eax)
	popl	%edi
	popl	%ebp
	ret
adderr:
	movl	$0, 16(%ebx)
	jmp	addret1
/
///////////////////////////////////////////////////////////////////////////////
/	ISUSERDATA : This function returns with ZF set if its arg is in user 
/	space, else with ZF cleared. For the sake of performance, the argument 
/	is in 0x000B, not on the stack. This is NOT a public function.  
/	Mainly used in fubyte(), etc.
///////////////////////////////////////////////////////////////////////////////

isuserdata:			/  7 /
	cmpl    $MINUVADR, %eax		/  2 /
	jb	notuser			/ ** /
	cmpl    $MAXUVADR-1, %eax	/  2 /
	ja      notuser			/ ** /
userok:
	xorl	%ebx, %ebx		/  2 / set zero flag
notuser:
	ret				/  7 /
/					------
/		is usersata		  26
/		is NOT userdata		  16/28

///////////////////////////////////////////////////////////////////////////////
/	ISUSERSTRING : Same as isuser, but tests for an entire string in user 
/	space. On entry, start of string is in eax, end in edx. On return, 
/	ZF ==> string is OK.  This is NOT a public function.  
///////////////////////////////////////////////////////////////////////////////

isuserstring:				/  7 /
	cmpl    $MINUVADR, %eax		/  2 /
	jb	notuser			/ ** /
	cmpl    $MAXUVADR-1, %eax	/  2 /
	ja      notuser			/ ** /

	cmpl    $MINUVADR, %edx		/  2 /
	jb      notuser			/ ** /
	cmpl    $MAXUVADR-1, %edx	/  2 /
	ja      notuser			/ ** /

	jmp	userok			/  7 /
/					------
/	is     userstring		  41
/	is NOT userstring		21/28/33/38


///////////////////////////////////////////////////////////////////////////////
/	CURRENT_THREAD : returns number of CURRENTLY active threads
///////////////////////////////////////////////////////////////////////////////

.globl _current_thread; .align 2; _current_thread:			/  7 /
	movl	_active_threads,%eax /  4 / only because cpu_number()==0
	ret				/  7 /
/					------
/					  18

///////////////////////////////////////////////////////////////////////////////
/	TENMICROSEC : The following code is used to waste 10 microseconds.
/	It is initialized in pit.c.
///////////////////////////////////////////////////////////////////////////////

.globl _tenmicrosec; .align 2; _tenmicrosec:			/  7 /
	movl	_microdata, %ecx	/  4 / Loop uses ecx.

microloop:
	loop	microloop		/ 11 /
	ret				/  7 /
/					------
/					18 + (0x000A * 11)

///////////////////////////////////////////////////////////////////////////////
/	PRF_ACCESS : tbd
///////////////////////////////////////////////////////////////////////////////

.globl _prf_access; .align 2; _prf_access:			/  7 /
	pushl	%ebp			/  2 /
	movl	%esp,%ebp		/  2 /
	
	pushl	%es			/  2 /

	movl	8(%ebp),%eax		/  4 /
	movw	%ax,%es			/  2 /
	xorl	%eax,%eax		/  2 /
	movb	%es:12(%ebp),%al	/  4 /

	popl	%es			/  2 /
	popl	%ebp			/  2 /
	ret				/  7 /
/					------
/					  36

///////////////////////////////////////////////////////////////////////////////
/	SIG_CLEAN : tbd
///////////////////////////////////////////////////////////////////////////////

.globl _sig_clean; .align 2; _sig_clean:
	/ set up the stack to look as in reg.h
	subl    $8, %esp        	/  2 / pad stk with ERRCODE and 0x000C
	pusha				/ 18 / save user registers
	pushl	%ds			/  2 /
	pushl	%es			/  2 /
	pushl	%fs			/  2 /
	pushl	%gs			/  2 /

	pushfl				/  2 /
	popl	%eax			/  2 /
	movl    %eax, (0x0010*4)(%esp) /  4 /
	movw	$0x160, %ax		/  2 /
	movw	%ax, %ds		/  2 /
	movw	%ax, %es		/  2 /
	movl	%esp, %ebp		/  2 /
	pushl   $F_ON			/  2 /
	popfl				/  2 /

	pushl	%esp			/  2 / argument to sigclean
	call    _osigreturn		/ restore pre-signal state
	addl    $4, %esp        	/  2 / pop arg


	jmp	short_user_ret
/	jmp     do_ret          / Can't do regular return-to-user processing



///////////////////////////////////////////////////////////////////////////////
/	check for kernel access
/	assume segment descr. allows access
/	check page dir and page table entries
/	check for VALID page or page with USER protection
///////////////////////////////////////////////////////////////////////////////

/.globl _kernacc; .align 2; _kernacc:				/  7 /
/	pushl	%ebp			/  2 /  set up stack image
/	movl	%esp,%ebp		/  2 /
/	pushl	%esi			/  2 /
/	pushl	%ebx			/  2 /
/	movl	%cr3,%esi		/  4 /
/	addl	$KVBASE,%esi		/  2 / kpde
/	movl	8(%ebp),%eax		/  4 / first address
/	movl	12(%ebp),%ebx		/  4 / length
/	addl	%eax,%ebx		/  2 /
/	decl	%ebx			/  2 / last adr
/	shrl	$12	,%eax		/  2 / first chunk/page
/	shrl	$12	,%ebx		/  2 / last chunk/page
/kacc1:
/	movl	%eax,%ecx
/	shrl	$22	-12	,%ecx	/  2 / dxr index
/	movl	(%esi,%ecx,4),%edx	/  4 / pd entry
/	testb	$1,%dl			/  2 / VALID
/	jz	kaccerr			/ ** /
/	addl	$KVBASE,%edx		/  2 /
/	andl	$-1!0xfff	,%edx	/  4 /
/	movl	%eax,%ecx		/  2 /
/	andl	$	0x3ff	,%ecx		/  2 /
/	movl	(%edx,%ecx,4),%edx	/  4 / pt entry
/	testb	$5,%dl			/  2 / VALID or USER page
/	jz	kaccerr			/ ** /
/	incl	%eax			/  2 /
/	cmpl	%ebx,%eax		/  2 /
/	jle	kacc1			/ ** /
/	movl	$1,%eax			/  2 /
/kaccout:
/	popl	%ebx			/  2 /
/	popl	%esi			/  2 /
/	popl	%ebp			/  2 /
/	ret				/  7 /
/kaccerr:
/	subl	%eax,%eax		/  2 /
/	jmp	kaccout			/  7 /











































 
 



# 1 "/usr/include/i386/asm.h" 1






























































# 94 "/usr/include/i386/asm.h"























































# 2425 "locore.s" 2


	.text









.globl _save_context; .align 2; _save_context:
	





	call	_get_pcb_context
	movl	%eax,%edx		/ address of save area
	movl	_curr_ipl, %eax
	movl	%eax, 24(%edx)	/ save ipl level for longjmp
	call	_splhi
	movl	%edi, 0(%edx)
	movl	%esi, 4(%edx)
	movl	%ebx, 8(%edx)
	movl	%ebp, 12(%edx)
	movl	%esp, 16(%edx)
	movl	(%esp), %ecx		/ %eip (return address)
	movl	%ecx, 20(%edx)
	subl	%eax, %eax		/ retval <- 0
	ret

.globl _setjmp; .align 2; _setjmp:
	movl	4(%esp), %edx		/ address of save area
	movl	_curr_ipl, %eax
	movl	%eax, 24(%edx)	/ save ipl level for longjmp
	movl	%edi, 0(%edx)
	movl	%esi, 4(%edx)
	movl	%ebx, 8(%edx)
	movl	%ebp, 12(%edx)
	movl	%esp, 16(%edx)
	movl	(%esp), %ecx		/ %eip (return address)
	movl	%ecx, 20(%edx)
	subl	%eax, %eax		/ retval <- 0
	ret

.globl _longjmp; .align 2; _longjmp:
	call	_splhi
	movl	4(%esp), %edx		/ address of save area
	movl	0(%edx), %edi
	movl	4(%edx), %esi
	movl	8(%edx), %ebx
	movl	12(%edx), %ebp
	movl	16(%edx), %esp
	movl	20(%edx), %eax	/ %eip (return address)
	movl	%eax, 0(%esp)
	pushl	24(%edx)
	call	_splx		/ restore ipl level
	popl	%edx
	popl	%eax			/ ret addr != 0
	jmp	*%eax			/ indirect

.globl _kdbsetjmp; .align 2; _kdbsetjmp:
	movl	4(%esp), %edx		/ address of save area
	movl	%edi, 0(%edx)
	movl	%esi, 4(%edx)
	movl	%ebx, 8(%edx)
	movl	%ebp, 12(%edx)
	movl	%esp, 16(%edx)
	movl	(%esp), %ecx		/ %eip (return address)
	movl	%ecx, 20(%edx)
	subl	%eax, %eax		/ retval <- 0
	ret

.globl _kdblongjmp; .align 2; _kdblongjmp:
	movl	8(%esp), %eax		/ return value
	movl	4(%esp), %edx		/ address of save area
	movl	0(%edx), %edi
	movl	4(%edx), %esi
	movl	8(%edx), %ebx
	movl	12(%edx), %ebp
	movl	16(%edx), %esp
	movl	20(%edx), %ecx		/ %eip (return address)
	addl	$4, %esp		/ pop ret adr
	jmp	*%ecx			/ indirect

