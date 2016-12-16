#ifndef _MM_
#define _MM_

#define SYSCALL_BASE		0xffffffffff000000
#define KERNEL_IMAGE_BASE	0xffffffff80000000
#define KERNEL_HEAP_BASE	0xfffff80000000000
#define VIRTUAL_MAP_BASE	0xfffff40000000000
#define KERNEL_STACK_TOP	0xfffff10000000000
#define PHY_MAP_BASE		0xffff800000000000

#define INVALID_ADDR		0xffffffffffffffff

#define GDT_BASE		0x0000000000000000
#define GDT_SIZE		0x0000000000010000
#define IDT_BASE		0x0000000000010000
#define IDT_SIZE		0x0000000000001000
#define TSS_BASE		0x0000000000011000
#define TSS_SIZE		0x0000000000000068

extern char __text_start[];
extern char __text_end[];
extern char __data_start[];
extern char __data_end[];
extern char __bss_start[];
extern char __bss_end[];

#endif
