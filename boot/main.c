/**
 * This is the routine of the kernel
 * called by bootloader.
 * 
 */

#include <serial_port/serial_port.h>
#include <klibc.h>
#include <phy_mm_pool.h>
#include <mm.h>
void main(uint64_t *param_list)
{
	printf("\nStarting kernel...\n");
	for (int i = 0; i < 10; i ++)
		printf("%lx\n", *(param_list + i));

	printf("text_start\t=\t%lx\n", __text_start);
	printf("text_end\t=\t%lx\n", __text_end);
	printf("data_start\t=\t%lx\n", __data_start);
	printf("data_end\t=\t%lx\n", __data_end);
	printf("bss_start\t=\t%lx\n", __bss_start);
	printf("bss_end\t\t=\t%lx\n", __bss_end);
	
// 	page_alloc_init();
	mm_init(param_list[2], param_list[3], param_list[4], param_list[5] + param_list[6] - PHY_MAP_BASE);
// 	printf("%lx\n", out);
// 	proc_init();
// 	ipc_init();
// 	dev_init();
// 	SerialPortInitialize();
// 	enable_interrupt();
// 	exec("init");
// 	vga_init();
// 	printf("%lx", mm_map);
// 	printf("%lx", cr3);
// 	assert(1==2);
	asm("hlt");
	while(1)
	{
// 		__serial_port_print(buf);

// 		for (char *ptr = (char *)0xA0000; (uint64_t)ptr <= 0xBFFFF; ptr ++)
// 			*ptr = 0;
// 		__io_write_8(0X3F8, 'A');
// 		sched();
// 		SerialPortWrite(str, 12);
// 		for (int i = 0; i < 0xfffffff; i ++);
	}
// 	asm("hlt");
}

// void thread1(void)
// {
// 	kprint("This is thread1.\n");
// 	
// } 
// void thread2(void)
// {
// 	kprint("This is thread2.\n");
// }
