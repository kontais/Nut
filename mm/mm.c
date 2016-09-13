#include <mm.h>


struct phy_page_table global_page_table;

/**
 * Take all memory pages except those used by kernel
 * into the free list of global_page_table
 */
void page_table_init(void)
{
	kmemset(global_page_table, 0, sizeof(global_page_table));
	global_page_table->used = NULL;
	global_page_table->free = NULL;
	
	struct region *ptr = mm_map->region;
	for (uint64_t index; index < ptr->nums; index++)
	{
		if (*(ptr + index)->virt_addr < KERNEL_ADDRESS)
		{
			uint64_t nums = *(ptr + index)->page_nums;
			for (uint64_t temp = 0; temp < nums; temp ++)
			{
				struct phy_page = kmalloc(sizeof(struct phy_page));
				phy_page->phy_addr= *(ptr + index)->phy_addr;
				phy_page->ref = 0;
				phy_page->flag = page_flag_dirty;
				list_insert_after(global_page_table->free, phy_page->list);
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
	if (global_page_table->free == NULL)
		panic("Out of memory.");
	
	struct list_head *temp = global_page_table->free;
	if (temp->next != temp)
	{
		temp = temp->next;
		list_del(temp);
	}
	else
	{
		global_page_table->free = NULL;
		kprint("No more free page.");
	}
	list_add_after(global_page_table->used, temp);
	//Get ptr to the page
	struct phy_page *entry = list_entry(temp, struct phy_page, list);
	entry->ref++;
	entry->flag &= ~page_flag_dirty;//Clean dirty bit
	
	struct virt_page *new = kmalloc(sizeof(struct virt_page));
	list_init(new->list);
	
	if (proc->mm == NULL)
		proc->mm = new->list;
	else
		list_insert_after(proc->mm, new->list);
	
	new->phy_page = entry;
	new->virt_addr = virt_addr;
	new->flag = page_flag_read | page_flag_write | page_flag_exec;
	
	
	do_map(virt_page);
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
