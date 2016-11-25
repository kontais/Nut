.globl _start
_start:
	.globl	main
	mov	%rbx, (mm_map)
	jmp	main
.globl mm_map
mm_map:.quad 0
