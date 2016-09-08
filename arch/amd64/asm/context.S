#
#
#
save_context:
    pop      %rsp    #First set tcb to be stack
    push     %rax
    push     %rcx
    push     %rdx
    push     %rbx
    
    mov      %ts, %rax
    push     20(%rax)
    
    push     %rsi
    push     %sdi
    push     %r8
    push     %r9
    push     %r10
    push     %r11
    push     %r12
    push     %r13
    push     %r14
    push     %r15

    push     %fs
    push     %gs

    push     %flags
    push     %rip
    
    

    ret

load_context:
	
