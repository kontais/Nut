
.globl systick_handler
systick_handler:
	call handler
	iretq
	
.globl syscall_handler, syscall_table
syscall_handler:
	push	%rbp
	lea	syscall_table, %rbp
	call	*(%rbp, %rax, 8)
	pop	%rbp
	iretq
