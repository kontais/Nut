//	Nut bootloader
//	This file is the routine of the bootloader
//
//		Written by Li Fei(C) 2016.11.14
//	After switching into protected mode,it runs to main.
//
//

#include <../paging.h>

void main(void)
{
	init_page_tables();
	switch_to_64();
	init_interrupt();
	init_bios_calls();
	run_to_kernel();
}
