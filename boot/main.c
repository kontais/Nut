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

#include <pci.h>

#include <fs.h>

#include<fs_generic.h>
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
	id_init();
	sched_init();
	syscall_init();
// 	int_init();
// 	char *ptr = malloc(4096);
// 	for (int i = 0; i < 4096; i ++)
// 		printf("%d ", *(ptr + i));
	exec("/test", NULL);
	
	int_init();
	fs_init();
// 	printf("%d\n", fs_mknode("/home/", FILE_TYPE_DIRCTORY));
// 	printf("%d\n", fs_mknode("/home/dev", FILE_TYPE_DIRCTORY));
// 	printf("%lx\n", fs_getnode("/home"));
// 	printf("%s\n", fs_getnode("/home")->name);
// 	printf("%s\n", fs_getnode("/home/dev")->name);
// 	printf("%d\n", fs_rmnode("/home"));
// 	printf("%s\n", fs_getnode("/home")->name);
// 	printf("%s\n", fs_getnode("/home/dev")->name);
// 	printf("%d\n", fs_rmnode("/home/dev"));
// 	printf("%s\n", fs_getnode("/home")->name);
// 	printf("%s\n", fs_getnode("/home/dev")->name);
// 	asm("mov $0, %rax\r\nint $0x80");
// 	asm("int $3");
// 	FATFS_Type fs;
// 	fatfs_init(&fs);
// 	for (int i = 0; i < 10; i ++)
// 	{
// 		for (int j = 0; j < 10;j ++)
// 			printf("%lx\n", __pci_read_reg(0, i, 0, j));
// 		printf("\n");
// 	}
// 	char *ptr = (char *)0xE0000000;
// 	for (int i = 0; i < 1024 * 768 * 4; i ++)
// 		*(ptr + i) = 0;
// 	char stu[4096]={0};
// 	printf("%d\n", read_file(&fs,"test",stu,4096));
// 	printf("%lx\n", *(uint64_t *)stu);
// 	printf("%lx\n", *(uint64_t *)(stu + 8));

// 	FATDir_Type *fatdir;
// 	FATFile_Type *file_info;
// 	const char *path="/MdePkg/Library/UefiRuntimeLib/UefiRuntimeLib/OUTPUT/";
// 	fatdir = fatfs_opendir(&fs,path);
// 	printf("%d\n", fatdir->size);
// 
// 	for(;;)
// 	{
// 		file_info = fatfs_readdir(&fs,fatdir);
// 		if (file_info == NULL)
// 			break;
// 		printf("%lx\t",file_info);
// 		printf("%s\t%d\t%d\t%d\t",file_info->Name,file_info->First_Cluster,file_info->Creation_Date,file_info->FileSize);
// 		printf("\n");
// 	
// 	
// 	}
// 	fatfs_rewinddir(&fs, fatdir);
// 	for(;;)
// 	{
// 		file_info = fatfs_readdir(&fs,fatdir);
// 		if (file_info == NULL)
// 			break;
// 		printf("%lx\t",file_info);
// 		printf("%s\t%d\t%d\t%d\t",file_info->Name,file_info->First_Cluster,file_info->Creation_Date,file_info->FileSize);
// 		printf("\n");
// 	
// 	
// 	}
// 	fatfs_closedir(&fs, fatdir);
// 	
	
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
// 	void *stack = malloc(4096);
// 	thread_t thread;
// 	void thread1(void);
// 	extern queue_t *ready_queue;
// 	thread_init(&thread, NULL, &thread1, stack + 4096);
// 	queue_enqueue(ready_queue, &thread);
	printf("Dead loop.\n");
// 	printf("%s\n", "Hello,world");
	
	pic_82c59_unmask_int(0);
	
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
