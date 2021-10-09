 





 





































 
 









 






















 

 
 





 


























































































 











.globl _kd_slmwd; .align 2; _kd_slmwd: 
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi

	movl	0x08(%ebp) , %edi
	movl	0x0c(%ebp) , %ecx
	movw	0x10(%ebp) , %ax
	cld
	rep
	stosw

	popl	%edi
	leave
	ret




 






.globl _kd_slmscu; .align 2; _kd_slmscu: 
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%edi

	movl	 0x08(%ebp) , %esi
	movl	   0x0c(%ebp) , %edi
	movl	0x10(%ebp) , %ecx
	cmpl	%edi, %esi
	cld
	rep
	movsw

	popl	%edi
	popl	%esi
	leave
	ret

 


.globl _kd_slmscd; .align 2; _kd_slmscd: 
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%edi

	movl	 0x08(%ebp) , %esi
	movl	   0x0c(%ebp) , %edi
	movl	0x10(%ebp) , %ecx
	cmpl	%edi, %esi
	std
	rep
	movsw
	cld

	popl	%edi
	popl	%esi
	leave
	ret



