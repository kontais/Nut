#include "vga.h"
#include <io.h>


int vga_init(void)
{
	__io_write_8(MISC_OUTPUT_REG_W, 0x02);
}
