/**
 * This is the routine of the kernel
 * called by bootloader.
 * 
 */

#include <serial_port/serial_port.h>
#include <klibc.h>
#include <phy_mm_pool.h>
#include <mm.h>
char *str = "Hello,world\n";
void main(void)
{

// 	char buf[1024] = {0};
// 	uint64_t cr3;
// 	asm (
// 		"mov %%cr0, %%rax\r\n"
// 		"mov %%rax, %0\r\n"
// 		: "=m" (cr3)
// 		:
// 	);
	early_print_init();
	__serial_port_print("Debug:\n");
	printf("text_start=%lx\n", __text_start);
	printf("text_end=%lx\n", __text_end);
	printf("data_start=%lx\n", __data_start);
	printf("data_end=%lx\n", __data_end);
	printf("bss_start=%lx\n", __bss_start);
	printf("bss_end=%lx\n", __bss_end);
// 	printf("data_load=%lx\n", data_load_start);
	
	uint64_t out;
	asm (
		"call read\r\n"
		"read:\r\n"
		"pop %0\r\n"
		: "=m" (out)
		: 
	);
	printf("%lx\n", out);
// 	asm (
// 		"lea kernel_image_base_addr, %%rax\r\n"
// 		"mov %%rax, %0\r\n"
// 		: "=m"(out)
// 		:
// 	);
// 	printf("%lx\n", out);
// 	proc_init();
// 	ipc_init();
// 	dev_init();
// 	SerialPortInitialize();
// 	enable_interrupt();
// 	exec("init");
// 	vga_init();
// 	__print_str(buf, str);
	
// 	__print_deci(buf, 1234567890);
// 	__print_hex(buf,str,16);
// 	__serial_port_print(buf);
// 	printf("%lx", mm_map);
	printf("%s", str);
// 	printf("%lx", cr3);
// 	assert(1==2);
// 	printf("ABCD%sABCD%d%c %x", str,1234567890,'B', 0xff);
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
