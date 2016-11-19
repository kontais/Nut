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

#include <SerialPortLib.h>
#include <io.h>
// void main(int argv, char **args) asm("_main");
void main(int argv, char **args)
{
	char *str = "Hello,world\n";
// 	mm_init();
// 	proc_init();
// 	ipc_init();
// 	dev_init();
// 	SerialPortInitialize();
// 	enable_interrupt();
// 	exec("init");
	
	
	while(1)
	{
// 		IoWrite8(0X3F8, 'A');
// 		sched();
		SerialPortWrite(str, 12);
// 		for (int i = 0; i < 0xfffffff; i ++);
	}
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
