
.globl systick_handler
systick_handler:
	call	context_save
	call	sched			#Schedule routine
	call	context_load
	iretq				#Automatically load the registers
	
	
.globl syscall_handler, syscall_table
syscall_handler:
	push	%rbp
	mov	syscall_table, %rbp
	call	*(%rbp, %rax, 8)
	pop	%rbp
	iretq
