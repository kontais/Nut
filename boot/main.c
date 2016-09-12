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
void main(int argv, char **args)
{
	mm_init();
	
	exec("init");
	while(1)
	{
		sched();
	}
}
