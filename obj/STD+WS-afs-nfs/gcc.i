 





 













 





 



































































































.globl ___divsi3; .align 2; ___divsi3: 
	movl	4(%esp), %eax



	cdq

	idivl	 8(%esp), %eax 
	ret

.globl ___udivsi3; .align 2; ___udivsi3: 
	movl	4(%esp), %eax
	xorl	%edx, %edx
	divl	 8(%esp), %eax 
	ret

