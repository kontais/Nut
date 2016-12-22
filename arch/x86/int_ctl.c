
#include <cpu_intrins.h>
#include <paging.h>
#include <segments.h>
#include <int_ctl.h>
#include <io.h>
uint64_t count = 0;
void handler(void)
{
	count++;
// 	printf("This is in interrupt routine.\n");
// 	asm ("pop %rax");
// 	asm ("iretq");
}
int int_reg(uint8_t vector, void *handle, enum INT_TYPE type);

void systick_handler(void);
void syscall_handler(void);
int int_init(void)
{
	__disable_interrupt__();

	int_reg(0x20, &systick_handler, INT);
	timer_82c54_init(0, 2, 0xffff);
	pic_82c59_init(0x20);
	pic_82c59_unmask_int(0);
	
	int_reg(0x80, &syscall_handler, TRAP);
	
	
	__enable_interrupt__();
}

int int_reg(uint8_t vector, void *handle, enum INT_TYPE type)
{
	struct int_trap_seg_dsc *dsc = (struct int_trap_seg_dsc *)__get_idt_addr__() + vector;
	struct seg_sel seg_dsc = 
	{
		.rpl = 0,
		.ti = 0,
		.index = 2,
	};
	dsc->offset_0_15 = (uint64_t)(handle) & 0xffff;
	dsc->seg_sel = seg_dsc;
	dsc->ist = 0;
	dsc->zero_1 = 0;
	switch(type)
	{
		case 0:
			dsc->type = DSC_TYPE_INIT;
			break;
		case 1:
			dsc->type = DSC_TYPE_TRAP;
			break;
		default:
			bug("Wrong INT_TYPE specified %d\n", type);
			break;
	}
	dsc->zero_2 = 0;
	dsc->dpl = 0;
	dsc->p = 1;
	dsc->offset_16_31 = ((uint64_t)(handle) >> 16) & 0xffff;
	dsc->offset_32_63 = ((uint64_t)(handle) >> 32) & 0xffffffff;
}

int int_unreg(uint8_t vector)
{
	struct int_trap_seg_dsc *dsc = (struct int_trap_seg_dsc *)__get_idt_addr__() + vector;
	dsc->p = 0;
}
