#ifndef _MM_
#define _MM_

#define SYSCALL_BASE		0xffffffffff000000
#define KERNEL_IMAGE_BASE	0xffffffff80000000
#define KERNEL_HEAP_BASE	0xfffff80000000000
#define VIRTUAL_MAP_BASE	0xfffff40000000000
#define KERNEL_STACK_TOP	0xfffff0ffffffffff
#define PHY_MAP_BASE		0xffff800000000000

#define GDT_BASE		0x0000000000000000UL
#define GDT_SIZE		0x0000000000010000UL
#define IDT_BASE		0x0000000000010000UL
#define IDT_SIZE		0x0000000000001000UL
#define TSS_BASE		0x0000000000011000UL
#define TSS_SIZE		0x0000000000000068UL

extern char __text_start[];
extern char __text_end[];
extern char __data_start[];
extern char __data_end[];
extern char __bss_start[];
extern char __bss_end[];

#endif
