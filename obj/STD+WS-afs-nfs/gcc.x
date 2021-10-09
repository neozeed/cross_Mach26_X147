# 1 "<stdin>"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "<stdin>"
# 21 "<stdin>"
# 1 "../../machine/asm.h" 1
# 22 "<stdin>" 2
# 31 "<stdin>"
.globl __divsi3; .align 2; __divsi3:
 movl 4(%esp), %eax



 cdq

 idivl 8(%esp), %eax
 ret

.globl __udivsi3; .align 2; __udivsi3:
 movl 4(%esp), %eax
 xorl %edx, %edx
 divl 8(%esp), %eax
 ret
