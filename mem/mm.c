#include <mm.h>

/**
 * The fisrt 1GB of address space is preserved for kernel and 
 * the rest is for user space.
 * This function initialize the page table.
 */
struct memory_map
{
	struct
	{
		uint64_t virt_addr;
		uint64_t phy_addr;
		uint32_t size;
	}*region;
	uint64_t nums;
}
struct page
{
	uint64_t addr;
	uint32_t flag;
	uint32_t ref;
	struct list_head list;
};
struct page_table
{
	struct page *used;
	struct page *free;
};

void pagetable_init(void)
{
	for (uint64_t addr = 0; addr < MAX_ADDR; addr += 8)
	{
		if ( addr < 

}
void *kmalloc(size_t bytes)
{
	
	
	
}
void kfree(void *ptr)
{
	
	
	
}
void mm_init(void)
{
	
}
