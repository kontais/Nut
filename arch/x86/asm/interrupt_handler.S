
.globl systick_handler
systick_handler:
	jmp	context_switch
	
.globl syscall_handler, syscall_table
syscall_handler:
	push	%rbp
	lea	syscall_table, %rbp
	call	*(%rbp, %rax, 8)
	pop	%rbp
	iretq
