#
#Save all registers in the stack.
#Push all registers except RSP,RIP,CS,DS,ES,SS,which are automatically pushed by call
#
.globl context_switch
context_switch:
	push	%gs
	push	%fs
	
	push	%r15
	push	%r14
	push	%r13
	push	%r12
	push	%r11
	push	%r10
	push	%r9
	push	%r8
	
	push	%rdi
	push	%rsi
	push	%rbp
	
	push	%rbx
	push	%rdx
	push	%rcx
	push	%rax
	
	mov	%rsp, %rdi		#Passed As an argument
	call	context_save		#Save context in the stack
	
	call	sched			#Schedule routine
	
	mov	%rsp, %rdi		#Passed As an argument
	call	context_load		#Get the address of current pcb
	
	pop	%rax
	pop	%rcx
	pop	%rdx
	pop	%rbx
		
	pop	%rbp
	pop	%rsi
	pop	%rdi
	
	pop	%r8
	pop	%r9
	pop	%r10
	pop	%r11
	pop	%r12
	pop	%r13
	pop	%r14
	pop	%r15
	
	pop	%fs
	pop	%gs
	
#This instruction automatically load the rest registers        
	iretq

