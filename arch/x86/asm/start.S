/**
  * Parameter passing by stack:
  * [         Image loading address          ]
  * [     UEFI memory map desc array size    ]
  * [       UEFI memory map desc address     ]
  */
.globl _start
_start:
/* 	.globl	__relocate,mm_init,early_print_init */
/* 	mov	%rsp, %rbp */
/* 	mov	(%rbp), %rdi */
/* 	mov	8(%rbp), %rsi */
/* 	mov	16(%rbp), %rdx */
/* 	call	early_print_init */
/* 	call	mm_init */
/* 	hlt */
/*	mov	$0x400000, %rax
	or	$0x18, %rax
	mov	%rax, %cr3*/
/*	pop	(mm_map_addr)
	pop	(mm_map_size)*/
	
/*  	mov	kernel_image_base_addr, %rax */
/* 	mov	(%rax), %rax */
/* 	mov	kernel_image_base_addr, %rax */
/* 	pop	(mm_map) */
/* 	mov	$0xffffffff80000000, %rax */
/* 	add	$0x0400, %rax */
/* 	hlt */
/* 	jmp	*%rax */
/*	add	$main, %rax*/
/*  	jmp	*%rax  */
	jmp	main
/* .globl mm_map_size,mm_map_addr */
/* mm_map_size:.quad 0 */
/* mm_map_addr:.quad 0 */

