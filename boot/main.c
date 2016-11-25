/**
 * This is the routine of the kernel
 * called by bootloader.
 * 
 */

#include <serial_port/serial_port.h>
#include <klibc.h>
#include <phy_mm_pool.h>
extern efi_memory_descriptor_t mm_map;
extern char text_start[];
extern char text_end[];
extern char data_start[];
extern char data_end[];
extern char bss_start[];
extern char bss_end[];
void main(void)
{
	char *str = "Hello,world\n";
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
	printf("text_start=%lx\n", text_start);
	printf("text_end=%lx\n", text_end);
	printf("data_start=%lx\n", data_start);
	printf("data_end=%lx\n", data_end);
	printf("bss_start=%lx\n", bss_start);
	printf("bss_end=%lx\n", bss_end);
// 	printf("data_load=%lx\n", data_load_start);
	
   	mm_init();
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
	printf("%lx", mm_map);
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
