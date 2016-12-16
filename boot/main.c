/**
 * This is the routine of the kernel
 * called by bootloader.
 * 
 */

#include <klibc.h>
#include <mm.h>
#include <fat.h>
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
	
	fatfs fs;
	fatfs_init(&fs);
	printf("%d\n", fs.BPB->ExtBPB.Ext_BPB_32.BPB_RootClus);
	printf("%d\n", fs.RootDirSecs);
	printf("%d\n", fs.FATSecs);
	printf("%d\n", fs.DataSecs);
	printf("%d\n", fs.TotSecs);
	printf("%d\n", fs.CountOfClus);
	printf("%d\n", fs.FirstRootSec);
	printf("%d\n", fs.FirstFATSec);
	printf("%d\n", fs.FirstDataSec);
	uint64_t *buf = malloc(65536);
	read_cluster(&fs, buf, 2);
// 	pio_read_sector(buf, 4144 + 2047);
	for (int i = 0; i < 8 << 3; i ++)
	{
		printf("%lx ", *(buf + i));
		if ((i+1) % 4 == 0)
			printf("\n");
	}
// 	for (int i = 0; i < 16; i ++)
// 		printf("%x\n", extract_fat_entry(&fs, i));
// 	printf("%x\n", extract_fat_entry(&fs, 0x726B));
// 	printf("%x\n", extract_fat_entry(&fs, 0xB94B));
// 	printf("%x\n", extract_fat_entry(&fs, 0x13869));
// 	printf("%x\n", extract_fat_entry(&fs, 0x16D81));
// 	printf("%d\n", fs.BPB->BPB_SecPerClus);
	char str[128] = {0xd2,0x79,0xe3,0x89,0x68,0x51,0xfd,0x56,0xcc,0x53,0xbf,0x7e};
// 	printf("%d\n", read_lname(buf + 96, str, 128));
// 	for (int i = 0; i < 128; i++)
// 		printf("%c",str[i]);
// 	printf("\n");
// 	printf("%x\n", str[0]);
// 	printf("%x\n", str[1]);
	char utf8[64] = {0xe7,0xa7,0x92,0x0A,0x00};
	int pos = 0;
	for (int i = 0; i < 64; i ++)
	{
		pos += unicode_into_utf8(*(uint16_t*)(str + i * 2), utf8 + pos);
	}
	for (int i = 0; i < 64; i ++)
	{
		printf("%c", *(utf8 + i));
	}
// 	printf("\n");
	printf("\n");
// 	printf("%c%c%c%c\n", 0xe7,0xa7,0x92,0x0A);
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
