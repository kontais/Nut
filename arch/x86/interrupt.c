#include <cpu_configure.h>

void int_init(void)
{
	enable_cpu_acpi_timer(acpi_timer_mode_Periodic, 255);
	set_cpu_acpi_timer(1234567, 6);
	
}
	
