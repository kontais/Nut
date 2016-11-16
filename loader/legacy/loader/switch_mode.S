#	Nut bootstrap prgoram
#	This code is excuted in 8086 real mode,initializing hardware and switching into 
#	protected mode in the end.
#
#		Li Fei(C) 2016.11.14
#
switch_16_to_32:
#	Initialize gdt descriptor
	lea	gdt_desc, %ax
	add	$0x10, %ax
	mov	%ax, %si
	
	lea	gdt, %dx
	mov	%dx, (%si)
	
	
#	Disable interrupt
	cli
#	Load gdt register
	lgdt	gdt_desc
#	Set PE flag to enable segment,entering protected mode
	mov	%cr0, %eax
	or	$1, %eax
	mov	%eax, %cr0

.code32
	jmp	$0x0001,$jump
	
jump:	mov	$0x0002, %ax
	mov	%ax, %ds
	mov	%ax, %ss
	mov	%ax, %es
	mov	%ax, %gs
	mov	%ax, %fs
	mov	$0xffffffff,%esp
	
	.global _main
	jmp	*_main

.align 32
gdt_desc:
.hword 0x0010
.word 0

.align 32
gdt:
.quad 0x0000000000000000
#code_segment
.quad 0x0067cf000000ffff
#data_segment
.quad 0x0067c7000000ffff

	 
