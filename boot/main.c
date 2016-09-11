/**
 * This is the routine of the kernel
 * called by bootloader.
 * This main function allows passing
 * boot parameters through the kernel
 * command line.
 * 
 * Parameters:(with * is necessary)
 * 
 * 1.Kernel Memory Base* : "kmb=ADDRESS"
 * 2.Kernel Memory Limit*: "kml=SIZE"
 * 3.
 * 
 */
void main(int argv, char **args)
{
	mm_init();
	
	
	
	
}
