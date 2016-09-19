#ifndef _MM_H_
#define _MM_H_

#include <ktypes.h>
#include <list.h>
#include <proc.h>

/**
 * The fisrt 1GB of address space is preserved for kernel and 
 * the rest is for user space.
 * This function initialize the page table.
 */
struct memory_map
{
	struct region
	{
		uint64_t virt_addr;
		uint64_t phy_addr;
		uint64_t page_nums;
		uint64_t available;
	}*region;
	uint64_t nums;
};
/**
 * Physical address page definition.
 * Flag definition:
 */

struct phy_page
{
	struct   list_head list;
	uint64_t phy_addr;
	uint64_t ref;
};
#define page_flag_read	0x01
#define page_flag_write	0x02
#define page_flag_exec  0x04
struct virt_page
{
	struct   list_head list;
	struct   phy_page  *phy_page;
	uint64_t virt_addr;
	uint64_t flag;
};
struct phy_page_table
{
	struct list_head used;
	struct list_head free;
};
struct mm_buffer
{
	uint64_t size;		//Continuous size of this buffer in bytes.
	uint64_t flag;		//Indicating whether this buffer is available,0 means avalable.
	struct list_head list;	//List to the following buffer.
};

void page_table_init(void);
void alloc_page(uint64_t virt_addr,struct proc *proc);
void free_page(uint64_t virt_addr,struct proc *proc);
void kmm_init_page(uint64_t virt_addr_start, uint64_t num_of_pages);
void kmm_extended_page(uint64_t virt_addr_start, uint64_t num_of_pages);
void *kmalloc(size_t size);
void kfree(void *ptr);
void mm_init(void);
#endif
