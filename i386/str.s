/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	str.s,v $
 * Revision 2.1.1.6  91/05/03  10:57:58  rvb
 * 	Always leave the "direction bit" clear
 * 	[91/05/03            rvb]
 * 
 * Revision 2.1.1.5  90/07/27  11:23:30  rvb
 * 	Add in 16bit bcopy, bcopy16, from rweiss
 * 	[90/07/26            rvb]
 * 
 * Revision 2.1.1.4  90/05/22  08:19:33  rvb
 * 	Leave ovbcopy in C.
 * 	[90/05/21            rvb]
 * 
 * Revision 2.1.1.3  90/05/18  07:35:02  rvb
 * 	ffs was dependent on the interpretation of what "UNDEFINED" meant on the 
 * 	hardware. Fixed [lance]
 * 
 * Revision 2.1.1.2  90/05/15  11:13:47  rvb
 * 	Add strcmp, strcpy, strncpy, ovbcopy, memcpy
 * 	move in bcopy, bclear from locore.s
 * 	[90/04/23            rvb]
 * 
 * Revision 2.1.1.1  90/03/07  13:28:17  rvb
 * 	All the asm str stuff will live in this file.
 * 	[90/03/07            rvb]
 * 
 * 	Created.
 * 	[90/03/06            rvb]
 * 
 */

#include <machine/asm.h>

/*
 * ffs(mask)
 */
ENTRY(ffs)
	bsfl	S_ARG0, %eax
	jz	0f
	incl	%eax
	ret
0:	xorl	%eax, %eax
	ret

/*
 * bcmp(s1, s2, len)
 * char *s1, *s2;
 * int len
 */

ENTRY(bcmp)
	pushl	%esi
	pushl	%edi

	xorl	%eax, %eax
	movl	12(%esp), %esi
	movl	16(%esp), %edi
	movl	20(%esp), %ecx

	cld
	 repe; cmpsb
	je	0f
	incl	%eax
	
0:	popl	%edi
	popl	%esi
	ret

/*
 * strlen(cp)
 * char *cp;
 */

ENTRY(strlen)
	movl	S_ARG0, %edx		/* ptr */
	orl	%edx, %edx
	jne	1f
	leal	3f, %eax
	pushl	%eax
	call	EXT(panic)
1:	xorl	%eax, %eax
	testb	$0xff,(%edx,%eax,1)
	je	2f
0:	incl	%eax
	testb	$0xff,(%edx,%eax,1)
	je	2f
	incl	%eax
	testb	$0xff,(%edx,%eax,1)
	je	2f
	incl	%eax
	testb	$0xff,(%edx,%eax,1)
	jne	0b
2:	ret
	.data
3:	.asciz	"strlen(NULL)"
	.text

/*
 * Copy string s2 to s1.  s1 must be large enough.
 * return s1
	char *strcpy(s1, s2)
	char *s1, *s2;
*/
ENTRY(strcpy)
	pushl	%esi
	pushl	%edi

	movl	12(%esp), %edi
	movl	16(%esp), %esi
	cld
0:	lodsb
	stosb
	orb	%al, %al		/ zerop
	jne	0b
	movl	12(%esp), %eax
	popl	%edi
	popl	%esi
	ret

/*
 * Copy s2 to s1, truncating or null-padding to always copy n bytes
 * return s1
	char *strncpy(s1, s2, n)
	char *s1, *s2;
 */
ENTRY(strncpy)
	pushl	%esi
	pushl	%edi

	movl	12(%esp), %edi
	movl	16(%esp), %esi
	movl	20(%esp), %ecx
	orl	%ecx, %ecx
	jle	1f

	cld
0:	lodsb
	stosb
	orb	%al, %al		/ zerop
	loopne	0b
	jne	1f			/ n exhausted
	jecxz	1f

	xorl	%al, %al
0:	stosb
	loop	0b			/ zero fill

1:	movl	12(%esp), %eax
	popl	%edi
	popl	%esi
	ret

/*
	strcmp(s1, s2)
	char *s1, *s2;
 */
ENTRY(strcmp)
	xorl	%eax, %eax
	movl	4(%esp), %edx
	movl	8(%esp), %ecx

0:	movb	(%edx), %al
	subb	(%ecx), %al
	jne	8f
	testb	$0xff, (%edx)
	je	8f
	incl	%edx
	incl	%ecx
	jmp	0b
	
8:	cbw; cwde
	ret



/ memcopy(to, from, count)
ENTRY(memcpy)
	pushl	%edi
	pushl	%esi
	movl	8+12(%esp),%edx		/  8 for the two pushes above
	movl	8+ 4(%esp),%edi
	movl	8+ 8(%esp),%esi
	jmp	0f

/ bcopy(from, to, bcount)

ENTRY(bcopy)
	pushl	%edi
	pushl	%esi
	movl	8+12(%esp),%edx		/  8 for the two pushes above
	movl	8+ 8(%esp),%edi
	movl	8+ 4(%esp),%esi
/ move longs
0:	cld
	movl	%edx,%ecx
	sarl	$2,%ecx
	js	bcout
	rep
	movsl
/ move bytes
	movl	%edx,%ecx
	andl	$3,%ecx
	rep
	movsb
bcout:
	popl	%esi
	popl	%edi
	ret	

/ bcopy16(from, to, bcount) using word moves

ENTRY(bcopy16)
	pushl	%edi
	pushl	%esi
	movl	8+12(%esp),%edx		/  8 for the two pushes above
	movl	8+ 8(%esp),%edi
	movl	8+ 4(%esp),%esi
/ move words
0:	cld
	movl	%edx,%ecx
	sarl	$1,%ecx
	js	bcout
	rep
	movsw
/ move bytes
	movl	%edx,%ecx
	andl	$1,%ecx
	rep
	movsb
	popl	%esi
	popl	%edi
	ret	

/* 
 * ovbcopy - like bcopy, but recognizes overlapping ranges and handles 
 *           them correctly.
	ovbcopy(from, to, bytes)
		char *from, *to;
		int bytes;
 */
#if	0
ENTRY(ovbcopy)
	pushl	%edi
	pushl	%esi
	cld
	movl	8+12(%esp),%edx		/  8 for the two pushes above
	movl	8+ 8(%esp),%edi
	movl	8+ 4(%esp),%esi
	leal	(%esi,%edx), %eax	/ from + bytes
	cmpl	%eax, %edi		/ <= to
	jae	0b
	leal	(%edi,%edx), %eax	/ to + bytes
	cmpl	%eax, %esi		/ <= from
	jae	0b
	cmpl	%esi, %edi		/ from > to
	jb	0b
	je 	1f

	addl	%edx, %esi; decl %esi
	addl	%edx, %edi; decl %edi
	std
	movl	%edx,%ecx
/ move bytes
	rep
	cld
	movsb
1:
	popl	%esi
	popl	%edi
	ret	
#endif	0

/ bzero(adr, bcnt)

Entry(blkclr)
Entry(bzero)
Entry(bclear)
	pushl	%ebp
	movl	%esp,%ebp
	MCOUNT

	pushl	%edi
	movl	8(%ebp),%edi
	movl	12(%ebp),%edx
	cld
	subl	%eax,%eax
/ clear longs
	movl	%edx,%ecx
	sarl	$2,%ecx
	js	bzout
	rep
	stosl
/ clear bytes
	movl	%edx,%ecx
	andl	$3,%ecx
	rep
	stosb

bzout:
	popl	%edi
	popl	%ebp
	ret	
