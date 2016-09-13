
/**
 * Enable ACPI timer.
 * @timer_mode one of the macros below
 * @vector     routine in the interrupt table 16-255
 */
#define acpi_timer_mode_one_shot      0x00
#define acpi_timer_mode_oPeriodic     0x01
#define acpi_timer_mode_tsc_deadline  0x02

void enable_cpu_acpi_timer(uint8_t timer_mode, uint8_t vector)
{
	uint32_t *reg = (uint32_t *)(uint8_t *)0xffe00320;
	*reg = (timer_mode & 0x03) << 17 | vector;
}
/**
 * Configure ACPI timer.
 * @initial_count Auto reload value,32-bit unsigned integer is okay.
 * @divide        Frequency divider,0-7,indicating 2,4,8,16,32,64,128,1.
 */
void set_cpu_acpi_timer(uint32_t initial_count, uint8_t divide)
{
	uint32_t *reg = (uint32_t *)(uint8_t *)0xfee00380;
	*reg = initial_count;
	reg = (uint32_t *)(uint8_t *)0xfee003E0;
	*reg = (divide & 0x04) << 3 | (divide & 0x03);
}


	
