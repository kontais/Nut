#
#Save all registers in the stack.
#Push all registers except RSP,RIP,CS,DS,ES,SS,which are automatically pushed by call
#
systick_handler:

save_context:
	push     %gs
	push     %fs
	
	push     %r15
	push     %r14
	push     %r13
	push     %r12
	push     %r11
	push     %r10
	push     %r9
	push     %r8
	
	push     %rdi
	push     %rsi
	push     %rbp
	
	push     %rbx
	push     %rdx
	push     %rcx
	push     %rax
	
	call     _get_current_thread_pcb	#Get the address of current pcb
	
	pop      0(%rax)			#RAX
	pop      8(%rax)			#RCX
	pop      16(%rax)			#RDX
	pop      24(%rax)			#RBX
	
	pop      32(%rax)			#RBP
	pop      40(%rax)			#RSI
	pop      48(%rax)			#RDI
	
	pop      56(%rax)			#R9
	pop      64(%rax)			#R10
	pop      72(%rax)			#R11
	pop      80(%rax)			#R12
	pop      88(%rax)			#R13
	pop      96(%rax)			#R14
	pop      104(%rax)			#R15
	
	pop      112(%rax)			#FS
	pop      120(%rax)			#GS
	
	
	mov      -8(%rsp), %rcx			#RIP
	mov      %rcx, 128(%rax)	
	
	mov      -16(%rsp), %rcx
	mov      %rcx, 136(%rax)		#CS
	
	mov      -24(%rsp), %rcx
	mov      %rcx, 144(%rax)		#RFLAGS
	
	mov      -32(%rsp), %rcx
	mov      %rcx, 152(%rax)		#RSP
	
	mov      -40(%rsp), %rcx
	mov      %rcx, 160(%rax)		#SS
	
	call     _sched				
#Load address of tcb before jump here.	
load_context:					
        push     160(%rax)			#SS
        push     152(%rax)			#RSP
        push     144(%rax)			#RFLAGS
        push     136(%rax)			#CS
        push     128(%rax)			#RIP
        push     $0				#Error code place holder
        
        push     120(%rax)			#GS
        push     112(%rax)			#FS
        
        push     104(%rax)			#R15
        push     96(%rax)			#R14
        push     88(%rax)			#R13
        push     80(%rax)			#R12
        push     72(%rax)			#R11
        push     64(%rax)			#R10
        push     56(%rax)			#R9
        
        push     48(%rax)			#RDI
        push     40(%rax)			#RSI
        push     32(%rax)			#RBP
        
        push     24(%rax)			#RBX
        push     16(%rax)			#RDX
        push     8(%rax)			#RCX
        push     0(%rax)			#RAX
        
        pop      %rax
        pop      %rcx
        pop      %rdx
        pop      %rbx
        
        pop      %rbp
        pop      %rsi
        pop      %rdi
        
        pop      %r9
        pop      %r10
        pop      %r11
        pop      %r12
        pop      %r13
        pop      %r14
        pop      %r15
        
        pop      %fs
        pop      %gs
#This instruction automatically load the rest registers        
        iret						
        
        
