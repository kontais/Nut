/**
 * This is the routine of the kernel
 * called by bootloader.
 * 
 */

#include <klibc.h>
#include <mm.h>
#include <mbr.h>
void main(uint64_t *param_list)
{
	printf("\nStarting kernel...\n");
	for (int i = 0; i < 10; i ++)
		printf("%lx\n", *(param_list + i));

	printf("text_start\t=\t%lx\n", __text_start);
	printf("text_end\t=\t%lx\n", __text_end);
	printf("data_start\t=\t%lx\n", __data_start);
	printf("data_end\t=\t%lx\n", __data_end);
	printf("bss_start\t=\t%lx\n", __bss_start);
	printf("bss_end\t\t=\t%lx\n", __bss_end);
	
	mm_init(param_list[2], param_list[3], param_list[4], param_list[5] + param_list[6] - PHY_MAP_BASE);
	vm_init();
	int_init();
	MBR_Record record;
	MBR_Init(&record);
	uint32_t LBA, size;
	Get_Partition(&record, 0, &LBA, &size);
	printf("%x %x\n", LBA, size);
	printf("%x %x\n", record.BootSig[0], record.BootSig[1]);
// 	proc_init();	
// 	ipc_init();
// 	dev_init();
// 	exec("init");
// 	vga_init();
// 	printf("%lx", mm_map);
// 	printf("%lx", cr3);
// 	asm("hlt");
	while(1)
	{
// 		extern uint64_t count;
// 		printf("%d\n", count);
	}
// 	asm("hlt");
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
