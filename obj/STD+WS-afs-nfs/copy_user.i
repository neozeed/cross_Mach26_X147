# 1 "../../i386/copy_user.s"



































# 1 "./mach_kdb.h" 1

# 36 "../../i386/copy_user.s" 2

# 1 "/usr/include/machine/asm.h" 1






























































# 94 "/usr/include/machine/asm.h"























































# 37 "../../i386/copy_user.s" 2

# 1 "/usr/include/sys/errno.h" 1











































































# 1 "./mach_nfs.h" 1

# 76 "/usr/include/sys/errno.h" 2





















































	













	













	




















































# 218 "/usr/include/sys/errno.h"










# 38 "../../i386/copy_user.s" 2













/ FAULT_ERROR is called if copyin() or copyout() generate a page fault
/ that can't be satisfied.  Through some stack magic FAULT_ERROR
/ returns 	14		 to the caller of copyin/copyout.
/ ALLOW_FAULT_START and ALLOW_FAULT_END bracket other code that can
/ use FAULT_ERROR.  See trap() for more details.

.globl _FAULT_ERROR; .align 2; _FAULT_ERROR:

	cmpl	$1, _kdbtrapok
	je	0f

	movl	-4(%ebp),%esi
	movl	-8(%ebp),%edi
0:
	movl	-12(%ebp),%eax
	movl	%ebp,%esp
	popl 	%ebp
	ret

.globl _ALLOW_FAULT_START; .align 2; _ALLOW_FAULT_START:

	





# 89 "../../i386/copy_user.s"







.globl _copyin; .align 2; _copyin:
	pushl	%ebp; movl %esp, %ebp; pushl %esi; pushl %edi; pushl $	14		; 
	movl	 8(%ebp), %esi
	movl	12(%ebp), %edi
	movl	16(%ebp), %ecx

	movl	$(0xc0000000), %edx;	cmpl	%edx, %esi;	ja	9f;	leal	(%esi, %ecx), %eax;	cmpl	%esi, %eax;	jb	9f;	cmpl	%edx, %eax;	jbe	8f;9:	movl	$	14		, %eax;	jmp	3f;8:

	cld
	movl	%ecx, %edx
	sarl	$2, %ecx
	rep; movsl

	leal	3, %ecx
	andl	%edx, %ecx
	rep; movsb

	movl	%ecx, %eax
3:	leal 4(%esp), %esp; popl %edi; popl %esi; popl %ebp
	ret










.globl _careful_bcopy; .align 2; _careful_bcopy:
	pushl	%ebp; movl %esp, %ebp; pushl %esi; pushl %edi; pushl $	14		; 
	movl	 8(%ebp), %esi
	movl	12(%ebp), %edi
	movl	16(%ebp), %ecx

	cld
	movl	%ecx, %edx
	sarl	$2, %ecx
	rep; movsl

	leal	3, %ecx
	andl	%edx, %ecx
	rep; movsb

	movl	%ecx, %eax
3:	leal 4(%esp), %esp; popl %edi; popl %esi; popl %ebp
	ret






.globl _copyout; .align 2; _copyout:
	pushl	%ebp; movl %esp, %ebp; pushl %esi; pushl %edi; pushl $	14		; 
	movl	 8(%ebp), %esi
	movl	12(%ebp), %edi
	movl	16(%ebp), %ecx


	movl	$(0xc0000000), %edx;	cmpl	%edx, %edi;	ja	9f;	leal	(%edi, %ecx), %eax;	cmpl	%edi, %eax;	jb	9f;	cmpl	%edx, %eax;	jbe	8f;9:	movl	$	14		, %eax;	jmp	3f;8:
	pushl	%ecx
	pushl	%edi
	call	_userwrite
	leal	8(%esp), %esp
	orl	%eax, %eax
	jnz	3f

	cld
	movl	16(%ebp), %ecx
	movl	%ecx, %edx
	sarl	$2, %ecx
	rep; movsl

	leal	3, %ecx
	andl	%edx, %ecx
	rep; movsb

	movl	%ecx, %eax
3:	leal 4(%esp), %esp; popl %edi; popl %esi; popl %ebp
	ret

	





# 199 "../../i386/copy_user.s"






.globl _copystr; .align 2; _copystr:
	pushl	%ebp; movl %esp, %ebp; pushl %esi; pushl %edi; pushl $	14		; 

	movl	 8(%ebp), %esi
	movl	12(%ebp), %edi
	movl	16(%ebp), %ecx

	cld
0:	lodsb	
	stosb
	orb	%al, %al
	loopne	0b
	je	1f
	movl	$	2		, %eax
	jmp	3f

1:	movl	20(%ebp), %eax
	orl	%eax, %eax
	je	2f

	subl	 8(%ebp), %esi
	movl	%esi, (%eax)

2:	xorl	%eax, %eax

3:	leal 4(%esp), %esp; popl %edi; popl %esi; popl %ebp
	ret







.globl _copyinstr; .align 2; _copyinstr:
	pushl	%ebp; movl %esp, %ebp; pushl %esi; pushl %edi; pushl $	14		; 

	movl	 8(%ebp), %esi
	movl	12(%ebp), %edi
	movl	16(%ebp), %ecx

	movl	$(0xc0000000), %edx;	cmpl	%edx, %esi;	ja	9f;	leal	(%esi, %ecx), %eax;	cmpl	%esi, %eax;	jb	9f;	cmpl	%edx, %eax;	jbe	8f;	movl	%edx, %ecx;	subl	%esi, %ecx;	jmp	8f;9:	movl	$	14		, %eax;	jmp	3f;8:

	cld
0:	lodsb	
	stosb
	orb	%al, %al
	loopne	0b
	je	1f
	movl	$	2		, %eax
	jmp	3f

1:	movl	20(%ebp), %eax
	orl	%eax, %eax
	je	2f

	subl	 8(%ebp), %esi
	movl	%esi, (%eax)

2:	xorl	%eax, %eax

3:	leal 4(%esp), %esp; popl %edi; popl %esi; popl %ebp
	ret






.globl _copyoutstr; .align 2; _copyoutstr:
	pushl	%ebp; movl %esp, %ebp; pushl %esi; pushl %edi; pushl $	14		; 

	movl	 8(%ebp), %esi
	movl	12(%ebp), %edi
	movl	16(%ebp), %ecx

	movl	$(0xc0000000), %edx;	cmpl	%edx, %edi;	ja	9f;	leal	(%edi, %ecx), %eax;	cmpl	%edi, %eax;	jb	9f;	cmpl	%edx, %eax;	jbe	8f;	movl	%edx, %ecx;	subl	%edi, %ecx;	jmp	8f;9:	movl	$	14		, %eax;	jmp	3f;8:
	pushl	%ecx
	pushl	%edi
	call	_userwrite
	leal	8(%esp), %esp
	orl	%eax, %eax
	jnz	3f

	cld
	movl	16(%ebp), %ecx
0:	lodsb	
	stosb
	orb	%al, %al
	loopne	0b
	je	1f
	movl	$	2		, %eax
	jmp	3f

1:	movl	20(%ebp), %eax
	orl	%eax, %eax
	je	2f

	subl	 8(%ebp), %esi
	movl	%esi, (%eax)

2:	xorl	%eax, %eax

3:	leal 4(%esp), %esp; popl %edi; popl %esi; popl %ebp
	ret


	




# 326 "../../i386/copy_user.s"

.globl _fuword; .align 2; _fuword:
	pushl	%ebp; movl %esp, %ebp; pushl %esi; pushl %edi; pushl $-1; 
	movl	 8(%ebp), %esi
	leal	4, %ecx
	movl	$(0xc0000000), %edx;	cmpl	%edx, %esi;	ja	9f;	leal	(%esi, %ecx), %eax;	cmpl	%edx, %eax;	jbe	8f;9:	movl	$-1, %eax;	jmp	3f;8:
	movl	(%esi), %eax	
3:	leal 4(%esp), %esp; popl %edi; popl %esi; popl %ebp
	ret

.globl _suiword; .align 2; _suiword:
.globl _suword; .align 2; _suword:
	pushl	%ebp; movl %esp, %ebp; pushl %esi; pushl %edi; pushl $-1; 
	movl	 8(%ebp), %esi
	leal	4, %ecx
	movl	$(0xc0000000), %edx;	cmpl	%edx, %esi;	ja	9f;	leal	(%esi, %ecx), %eax;	cmpl	%edx, %eax;	jbe	8f;9:	movl	$-1, %eax;	jmp	3f;8:
	pushl	%ecx
	pushl	%esi
	call	_userwrite
	leal	8(%esp), %esp
	orl	%eax, %eax
	jnz	3f
	movl	12(%ebp), %eax
	movl	%eax, (%esi)
3:	leal 4(%esp), %esp; popl %edi; popl %esi; popl %ebp
	ret

.globl _fuibyte; .align 2; _fuibyte:
.globl _fubyte; .align 2; _fubyte:
	pushl	%ebp; movl %esp, %ebp; pushl %esi; pushl %edi; pushl $-1; 
	movl	 8(%ebp), %esi
	leal	1, %ecx
	movl	$(0xc0000000), %edx;	cmpl	%edx, %esi;	ja	9f;	leal	(%esi, %ecx), %eax;	cmpl	%edx, %eax;	jbe	8f;9:	movl	$-1, %eax;	jmp	3f;8:
	xorl	%eax, %eax
	movb	(%esi), %al
3:	leal 4(%esp), %esp; popl %edi; popl %esi; popl %ebp
	ret

.globl _suibyte; .align 2; _suibyte:
.globl _subyte; .align 2; _subyte:
	pushl	%ebp; movl %esp, %ebp; pushl %esi; pushl %edi; pushl $-1; 
	movl	 8(%ebp), %esi
	leal	1, %ecx
	movl	$(0xc0000000), %edx;	cmpl	%edx, %esi;	ja	9f;	leal	(%esi, %ecx), %eax;	cmpl	%edx, %eax;	jbe	8f;9:	movl	$-1, %eax;	jmp	3f;8:
	pushl	%ecx
	pushl	%esi
	call	_userwrite
	leal	8(%esp), %esp
	orl	%eax, %eax
	jnz	3f
	movb	12(%ebp), %al
	movb	%al, (%esi)
3:	leal 4(%esp), %esp; popl %edi; popl %esi; popl %ebp
	ret








.globl _kdbwlong; .align 2; _kdbwlong:
	pushl	%ebp; movl %esp, %ebp; pushl %esi; pushl %edi; pushl $	14		; 
	incl	_kdbtrapok
	
	movl	 8(%ebp), %eax
	movl	12(%ebp), %edx
	movl	(%edx), %ecx
	movl	%ecx, (%eax)
	xorl	%eax, %eax

	decl	_kdbtrapok
	leal 4(%esp), %esp; popl %edi; popl %esi; popl %ebp
	ret







.globl _kdbrlong; .align 2; _kdbrlong:
	pushl	%ebp; movl %esp, %ebp; pushl %esi; pushl %edi; pushl $	14		; 
	incl	_kdbtrapok

	movl	 8(%ebp), %eax
	movl	12(%ebp), %edx
	movl	(%eax), %ecx
	movl	%ecx, (%edx)
	xorl	%eax, %eax

	decl	_kdbtrapok
	leal 4(%esp), %esp; popl %edi; popl %esi; popl %ebp
	ret


.globl _ALLOW_FAULT_END; .align 2; _ALLOW_FAULT_END:
