/**
 * This is the routine of the kernel
 * called by bootloader.
 * This main function allows passing
 * boot parameters through the kernel
 * command line.
 * 
 * Parameters:(with * is necessary)
 * 
 * 1.Kernel Memory Base*	: "base=ADDRESS"
 * 2.Kernel Size*		: "size=SIZE"
 * 3.Memory Map Table Base*	: "map=ADDRESS"
 * 4.Memory Map Size*		: "mapsize=SIE"
 */

#include <serial_port/serial_port.h>
#include <io.h>
#include <vga.h>
#include <klibc.h>
// void main(int argv, char **args) asm("_main");
void main(int argv, char **args)
{
	char *str = "Hello,world\n";
	char buf[1024] = {0};
	
	early_print_init();
//  	mm_init();
// 	proc_init();
// 	ipc_init();
// 	dev_init();
// 	SerialPortInitialize();
// 	enable_interrupt();
// 	exec("init");
// 	vga_init();
// 	__print_str(buf, str);
	__serial_port_print("Debug:\n");
// 	__print_deci(buf, 1234567890);
// 	__print_hex(buf,str,16);
// 	__serial_port_print(buf);
	assert(1==2);
	printf("ABCD%sABCD%d%c %x", str,1234567890,'B', 0xff);
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
