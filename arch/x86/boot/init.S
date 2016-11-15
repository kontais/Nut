/**
 * Nut bootstrap prgoram
 * This code is excuted in 8086 real mode,initializing hardware and switching into 
 * protected mode in the end.
 *
 *	Li Fei(C) 2016.11.14
 *
 * Boot protocol:
 *	Bootstrap image is loaded at fixed 0x1000:0x0000
 */
.code16
.global boot
boot:
#	Set up segment registers to 0x1000 and stack pointer to 0x1000:0xffff
	mov	$0x1000, %ax
	mov	%ax, %ss
	mov	%ax, %ds
	mov	%ax, %es
	mov	$0xffff, %sp
	
.global	main16
	jmp	main16
