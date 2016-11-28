#include <segments.h>
#include <klibc.h>
#include <mm.h>



extern void exception_handler(void);

static void __gdt_init(void)
{
	memset((void *)GDT_BASE, 0, GDT_SIZE);
	//First descriptor is not used
	struct seg_dsc *seg = (struct seg_dsc *)GDT_BASE + 1;
	//Two segement initialize, data,
	seg->p = 1;
	seg->s = 1;
	seg->type = SEG_T_D_RW_A;
	seg ++;
// 	*((uint64_t *)seg) = 0x00AF9B000000FFFF;
	seg->p = 1;
	seg->l = 1;
	seg->s = 1;
	seg->type = SEG_T_C_EX_R_A;
	seg ++;
	struct tss_ldt_dsc *tss_ldt = (struct tss_ldt_dsc *)seg;
	tss_ldt->type = DSC_TYPE_TSS;
	tss_ldt->base_0_15 = (TSS_BASE + PHY_MAP_BASE) & 0xffff;
	tss_ldt->base_16_23 = (TSS_BASE + PHY_MAP_BASE) >> 16 & 0xff;
	tss_ldt->base_24_31 = (TSS_BASE + PHY_MAP_BASE) >> 24 & 0xff;
	tss_ldt->base_32_63 = (TSS_BASE + PHY_MAP_BASE) >> 32 & 0xffffffff;
	tss_ldt->p = 1;
	tss_ldt->seg_limit_0_15 = TSS_SIZE - 1;
	tss_ldt->avl = 1;
}
static void __idt_init(void)
{
	struct int_trap_seg_dsc exception_handler_dsc;
	struct seg_sel seg_sel_dsc;
	uint64_t handler_addr;
	asm (
		"lea	exception_handler, %%rax\r\n"
		"mov	%%rax, %0\r\n"
		: "=m" (handler_addr)
		:
	);
	handler_addr += KERNEL_IMAGE_BASE;
	printf("Exception Handler locates at %lx\n", handler_addr);
	seg_sel_dsc.rpl = 0;
	seg_sel_dsc.ti = 0;
	seg_sel_dsc.index = 2;
	exception_handler_dsc.p = 1;
	exception_handler_dsc.dpl = 0;
	exception_handler_dsc.zero_1 = 0;
	exception_handler_dsc.type = DSC_TYPE_INIT;
	exception_handler_dsc.zero_2 = 0;
	exception_handler_dsc.ist = 0;
	exception_handler_dsc.seg_sel = seg_sel_dsc;
	exception_handler_dsc.offset_0_15 = handler_addr;
	exception_handler_dsc.offset_16_31 = handler_addr >> 16;
	exception_handler_dsc.offset_32_63 = handler_addr >> 32;
	
	memset((void *)IDT_BASE, 0, IDT_SIZE);
	struct int_trap_seg_dsc *int_trap = (void *)IDT_BASE;
	for (int i = 0; i < 16; i ++)
	{
		*(int_trap + i) = exception_handler_dsc;
	}
}
static void __tss_init(void)
{
	memset((void *)TSS_BASE, 0, TSS_SIZE);
	struct tss_seg *tss= (void *)TSS_BASE;
	tss->RSP0_lower = 0xffffffff;
	tss->RSP0_upper = 0xffffffff;
	tss->RSP1_lower = 0xffffffff;
	tss->RSP1_upper = 0xffffffff;
	tss->RSP2_lower = 0xffffffff;
	tss->RSP2_upper = 0xffffffff;
	tss->IST1_lower = 0xffffffff;
	tss->IST1_upper = 0xffffffff;
	tss->IST2_lower = 0xffffffff;
	tss->IST2_upper = 0xffffffff;
	tss->IST3_lower = 0xffffffff;
	tss->IST3_upper = 0xffffffff;
	tss->IST4_lower = 0xffffffff;
	tss->IST4_upper = 0xffffffff;
	tss->IST5_lower = 0xffffffff;
	tss->IST5_upper = 0xffffffff;
	tss->IST6_lower = 0xffffffff;
	tss->IST6_upper = 0xffffffff;
	tss->IST7_lower = 0xffffffff;
	tss->IST7_upper = 0xffffffff;
	tss->IO_base = 0x0000;
}
void init_dsc_tables(void)
{
	__gdt_init();
	__idt_init();
	__tss_init();
}
void load_dsc_tables_and_seg_sels(void)
{
	//Load global descriptor table and task-state-segment
	struct {
		uint32_t _reserve_1;
		uint16_t _reserve_2;
		uint16_t limit;
		uint64_t base;
	} pseudo_dsc __attribute__ ((aligned (8)));
	memset(&pseudo_dsc, 0 ,sizeof(pseudo_dsc));
	pseudo_dsc.limit = GDT_SIZE - 1;
	pseudo_dsc.base = GDT_BASE + PHY_MAP_BASE;
	asm (
		"lea	%0, %%rax\r\n"
		"lgdt	(%%rax)\r\n"
		"mov	$0x8, %%rax\r\n"
		"mov	%%rax, %%ds\r\n"
		"mov	%%rax, %%es\r\n"
		"mov	%%rax, %%ss\r\n"
		"mov	%%rax, %%fs\r\n"
		"mov	%%rax, %%gs\r\n"
		"mov	$0x18, %%ax\r\n"
		"ltr	%%ax\r\n"
		:
		: "m" (pseudo_dsc.limit)
	);
	pseudo_dsc.limit = IDT_SIZE - 1;
	pseudo_dsc.base = IDT_BASE + PHY_MAP_BASE;
	//Load interrupt table
	asm (
		"lea	%0, %%rax\r\n"
		"lidt	(%%rax)\r\n"
		:
		: "m" (pseudo_dsc.limit)
	);
	//Load code segment
	struct {
		uint32_t _reserve_1;
		uint16_t _reserve_2;
		uint16_t seg_sel;
		uint64_t addr;
	} far_ptr __attribute__ ((aligned (8)));
	far_ptr.seg_sel = 0x10;
	far_ptr.addr = 0;
	asm (
		"lea	%0, %%rax\r\n"
		"mov	$jump, %%rbx\r\n"
		"add	$0xffffffff80000000, %%rbx\r\n"
		"mov	%%rbx, 2(%%rax)\r\n"
// 		"int	$3\r\n"
		"ljmp	*(%%rax)\r\n"
		"jump:\r\n"
		:
		: "m" (far_ptr.seg_sel)
	);
	printf("%lx %lx\n", far_ptr.seg_sel, far_ptr.addr);
	printf("GDTR = %lx %lx\n", pseudo_dsc.base, pseudo_dsc.limit);
	printf("GDT:\n");
	for (uint64_t i = 0; i < 0x10; i ++)
// 		printf("%lx\n", *(uint64_t *)(i * 8));
		printf("%lx\n", *(uint64_t *)(0x00000000DF7A8018 + i * 8));
	for (uint64_t i = 0; i < 0x10; i ++)
// 		printf("%lx\n", *(uint64_t *)(i * 8));
		printf("%lx\n", *(uint64_t *)(0x00000000DFF2DF98 + i * 8));	
	
	
}
void dump_reg(uint64_t addr)
{
	printf("Exception:\n");
	
}
