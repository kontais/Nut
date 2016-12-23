/**
 * This is the routine of the kernel
 * called by bootloader.
 * 
 */

#include <klibc.h>
#include <mm.h>
#include <fat.h>

#include <sched.h>
#include <syscall.h>
#include <int_ctl.h>
#include <queue.h>
#include <GlyphBDF.h>
#include <ProtableGrayMap.h>
#include <pci.h>
#include <paging.h>
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
	modify_chunk_mapping(get_current_plm4e(), 0x80000000, 0x80000000, 0x1000, DEFAULT_PTE_FLAG);
	
	for (int i = 0; i < 5; i ++)
	{
		for (int j = 0; j < 10; j ++)
		{
			printf("%x\n", __pci_read_reg(0, i, 0, j));
		}
		printf("\n");
	}
//	sched_init();
//	syscall_init();
// 	int_init();
	uint32_t *ptr = (uint32_t *)0x80000000;
	for (int i = 0; i < 1024 * 768;i ++)
		*ptr++ = 0;
//	*ptr = 0x80808080;
	/*FATFS_Type fs;
	fatfs_init(&fs);
	unsigned char *buf = malloc(40960);
	unsigned char *stream =buf;
	memset(buf, 0, 40960);
	
	printf("%d\n", read_file(&fs,"unifont-asiic.bdf",buf,40960));
	
	GlyphBDF Glyph_BDF;
	Glyph_BDF_init(&Glyph_BDF);
	GetBitmapFromGlyphBDF(&stream,&Glyph_BDF,'g');
	
	printf("%c\n",Glyph_BDF.ENCODIN);
	for(int i=0;i<16;i++){
		for(int j=0;j<2;j++)
		{
			printf("%c",Glyph_BDF.BITMAP[i][j]);
		}
		printf("\n");
	}
	*/
	Display();
	
// 	
// 	FATDir_Type *dir = fatfs_opendir(&fs, "/MdePkg");
// 	char name[512];
// 	printf("%lx\n", dir);
// 	printf("%lx\n", dir->buf);
// 	printf("%lx\n", dir->size);
// 	printf("%lx\n", dir->offset);
// 	printf("%d\n", read_name(dir->buf, name, 8));
// 	printf("%s\n", name);
// 	printf("%d\n", read_name(dir->buf + 32, name, 8));
// 	printf("%s\n", name);
// 	printf("%d\n", read_name(dir->buf + 64, name, 8));
// 	printf("%s\n", name);
// 	printf("%d\n", read_name(dir->buf + 96, name, 8));
// 	printf("%s\n", name);
// 	printf("%d\n", read_name(dir->buf + 128, name, 8));
// 	printf("%s\n", name);
// 	uint64_t *buf = malloc(65536);
// 	read_cluster(&fs, buf, 2);
// 	printf("%d\n", pio_read_sector(buf, 0));
// 	pio_read_sector(buf, 4144 + 2047);
// 	for (int i = 0; i < 16; i ++)
// 	{
// 		printf("%lx ", *(uint64_t *)(dir->buf + i * 8));
// 		if ((i+1) % 4 == 0)
// 			printf("\n");
// 	}
// 	for (int i = 0; i < 16; i ++)
// 		printf("%x\n", extract_fat_entry(&fs, i));
// 	printf("%x\n", extract_fat_entry(&fs, 0x726B));
// 	printf("%x\n", extract_fat_entry(&fs, 0xB94B));
// 	printf("%x\n", extract_fat_entry(&fs, 0x13869));
// 	printf("%x\n", extract_fat_entry(&fs, 0x16D81));
// 	printf("%d\n", fs.BPB->BPB_SecPerClus);
// 	printf("%d\n", compute_cluster_chain_length(&fs, 2));
// 	char str[128] = {0};
// 	memset(str,'A', 128);
// 	int pos = 0;
// 	for (int i = 0; i < 128; i ++)
// 	{
// 		printf("%d\n", pos += read_lname(buf + pos * 4, str, 128) + 1);
// 		printf("%s\n", str);
// // 		for (int i = 0; i < 128; i++)
// // 			printf("%c",str[i]);
// 		printf("\n");
// 	}
// 	
	
	
//	printf("%lx\n", *(uint64_t *)stu);
//	printf("%lx\n", *(uint64_t *)(stu + 8));
// 	printf("%c%c%c%c\n", 0xe7,0xa7,0x92,0x0A);
// 	proc_init();
// 	ipc_init();
// 	dev_init();
// 	exec("init");
// 	vga_init();
// 	printf("%lx", mm_map);
// 	printf("%lx", cr3);
// 	asm("hlt");
// 	asm("int	$3");
//	void *stack = malloc(4096);
//	thread_t thread;
//	void thread1(void);
//	extern queue_t *ready_queue;
//	thread_init(&thread, NULL, &thread1, stack + 4096);
//	queue_enqueue(ready_queue, &thread);
//	printf("Dead loop.\n");
// 	printf("%s\n", "Hello,world");
	
	
	
	while(1)
	{
// 		extern uint64_t count;
// 		printf("%d\n", count);
	}
// 	asm("hlt");
}

void thread1(void)
{

	while(1)
	{
		asm(
			"mov $0, %rax\r\n"
			"int $0x80"
		);
		printf("This is thread1.\n");
	}
} 
void thread2(void)
{
	while(1)
	{
		printf("This is thread2.\n");
	}
}
