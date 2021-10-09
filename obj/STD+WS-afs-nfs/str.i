 





 
































 





 



























































































 


.globl _ffs; .align 2; _ffs: 
	bsfl	 4(%esp) , %eax
	jz	0f
	incl	%eax
	ret
0:	xorl	%eax, %eax
	ret

 





.globl _bcmp; .align 2; _bcmp: 
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

 




.globl _strlen; .align 2; _strlen: 
	movl	 4(%esp) , %edx		 
	orl	%edx, %edx
	jne	1f
	leal	3f, %eax
	pushl	%eax
	call	_panic 
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

 





.globl _strcpy; .align 2; _strcpy: 
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

 





.globl _strncpy; .align 2; _strncpy: 
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

 



.globl _strcmp; .align 2; _strcmp: 
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
.globl _memcpy; .align 2; _memcpy: 
	pushl	%edi
	pushl	%esi
	movl	8+12(%esp),%edx		/  8 for the two pushes above
	movl	8+ 4(%esp),%edi
	movl	8+ 8(%esp),%esi
	jmp	0f

/ bcopy(from, to, bcount)

.globl _bcopy; .align 2; _bcopy: 
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

.globl _bcopy16; .align 2; _bcopy16: 
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

 








/ bzero(adr, bcnt)

.globl _blkclr; .align 2; _blkclr: 
.globl _bzero; .align 2; _bzero: 
.globl _bclear; .align 2; _bclear: 
	pushl	%ebp
	movl	%esp,%ebp
	 

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
