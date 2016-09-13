#include <mm.h>

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
	}*region;
	uint64_t nums;
}
struct page
{
	struct   list_head list;
	uint64_t phy_addr;
	uint32_t flag;
	uint32_t ref;
};
struct page_table
{
	struct list_head used;
	struct list_head free;
	struct list_head swaped;
}global_page_table;

/**
 * Take all memory pages except those used by kernel
 * into the free list of global_page_table
 */
void page_table_init(void)
{
	kmemset(global_page_table, 0, sizeof(global_page_table));
	list_head_init(page_table->used);
	list_head_init(page_table->free);
	
	struct region *ptr = mm_map->region;
	for (uint64_t index; index < ptr->nums; index++)
	{
		if (*(ptr + index)->virt_addr < KERNEL_ADDRESS)
		{
			uint64_t nums = *(ptr + index)->page_nums;
			for (uint64_t temp = 0; temp < nums; temp ++)
			{
				struct page_table = kmalloc(sizeof(struct page_table));
				page_table->phy_addr= *(ptr + index)->phy_addr;
				page_table->ref = 0;
				page_table->flag = 0;
				list_insert_after(global_page_table.free, page_table->list);
			}
		}
	}
}
/**
 * These two functions is used to allocate 
 * and deallocate pages in user space.
 */
void alloc_page(uint64_t virt_addr,struct proc *proc)
{
	list_head_add_after(proc->mm, global_page_table);
	
	
}
void free_page(uint64_t virt_addr,struct proc *proc)
{
	
	
}
void kmem_init(void)
{
	
}
void *kmalloc(size_t size)
{
	
}
void kfree(void *ptr)
{
	
}
void mm_init(void)
{
	
}
