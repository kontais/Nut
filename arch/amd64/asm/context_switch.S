#
#Save all registers in the stack.
#
save_context:
    push     %rax
    push     %rcx
    push     %rdx
    push     %rbx
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
    jump     
load_context:
    pop      
