
.globl systick_handler
systick_handler:
	call handler
	iretq
	
.globl syscall_handler
syscall_handler:
/* 	call	__syscall_handler */
	iretq
