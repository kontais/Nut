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
void main(int argv, char **args)
{
	int_init();
	mm_init();
	SerialPortInitialize();
	enable_interrupt();
// 	exec("init");
	
	
	while(1)
	{
		sched();
	}
}

void thread1(void)
{
	kprint("This is thread1.\n");
	
}
void thread2(void)
{
	kprint("This is thread2.\n");
}
