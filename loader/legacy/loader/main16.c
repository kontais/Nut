/**
 * main16:
 * 	C routine in the 8086 real mode,called by init.S
 * 
 * 		Li Fei(C) 2016.11.14
 */
#include <e820.h>
//#include <early_print.k>
#include <BIOS_interrupt.h>

void main16(void)
{
 	char *string = "Hello,world.";
	char *string2 = "Yes.";
// 	print_str16(string);
// 	print_str16("Yes,Sir.");
// 	print_str16(string2);
//  	char *ptr = string;
 	reg16 reg;
	reg.ax = 0x1301;
	reg.bx = 0X000C;
	reg.cx = 12;
	reg.es = 0x1000;
	reg.bp = string;
	bios_int16(&reg, 0x10);
	
// 	reg.ax = 0x1301;
// 	reg.bx = 0x000C;
// 	reg.cx = 4;
// // 	reg.dx = 0x0100;
// 	reg.es = 0x1000;
// 	reg.bp = string2;
// 	bios_int16(&reg, 0x10);
	
	while(1);
}
