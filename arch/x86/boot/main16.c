/**
 * main16:
 * 	C routine in the 8086 real mode,called by init.S
 * 
 * 		Li Fei(C) 2016.11.14
 */
#include <BIOS_interrupt.h>

void main16(void)
{
 	char *string = "Hello,world.";
 	char *ptr = string;
	reg16 reg;
	reg.ax = 0x1301;
	reg.bx = 0X000C;
	reg.cx = 100;
	reg.es = 0x1000;
 	reg.bp = string;
	bios16_int(reg, 0x10);
	while(1);
}
