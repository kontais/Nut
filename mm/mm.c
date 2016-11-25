#include <mm.h>
#include <list.h>

struct phy_page_table global_page_table;
void *heap_start = NULL;
/**
 * 
 * 
 */
void vm_page_table_init(void)
{
	
	
}
/**
 * Take all memory pages except those used by kernel
 * into the free list of global_page_table
 */
void page_table_init(void)
{
	kmemset(global_page_table, 0, sizeof(global_page_table));
	list_init(global_page_table.used);
	list_init(global_page_table.free);
	
	struct region *ptr = mm_map->region;
	for (uint64_t index; index < ptr->nums; index++)
	{
		if (*(ptr + index)->virt_addr < kernel_base_address && *(ptr + index)->available)
		{
			uint64_t nums = *(ptr + index)->page_nums;
			for (uint64_t temp = 0; temp < nums; temp ++)
			{
				struct phy_page = kmalloc(sizeof(struct phy_page));
				phy_page->phy_addr= *(ptr + index)->phy_addr;
				phy_page->ref = 0;
				phy_page->flag = page_flag_dirty;
				list_insert_after(global_page_table.free, phy_page->list);
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
	if (list_init(global_page_table.free))
		panic("Out of memory.");
	
	struct list_head *temp = &global_page_table.free;

	temp = temp->next;
	list_del(temp);
	list_add_after(&global_page_table.used, temp);
	Get ptr to the page
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
	list_head *it = proc->mm, *head = proc->mm;
	list_for_each(it, head)
	{
		struct virt_page *ptr = list_entry(it, struct phy_page, list);
		if (ptr->virt_addr == virt_addr)
		{
			if (--ptr->phy_page->ref == 0)
			{
				list_del(ptr->phy_page->list);
				list_add_after(global_page_table.free, ptr->phy_page->list);
			}
			list_del(ptr.list);
			ummap(ptr);
			kfree(ptr);
			break;
		}
	}
}

/**
 * These functions named by k*** is only used in kernel space,rather
 * user space.
 * The buffer pool must be continuous in virtual address space,and
 * can only extended backwards from the origin pool's egde.
 */

#define buffer_head_size sizeof(struct mm_buffer)

/**
 * Init the heap to be used with kmalloc and kfree.
 */
void kmm_init_page(uint64_t virt_addr_start, uint64_t num_of_pages)
{
	((struct mm_buffer *)virt_addr_start)->size = num_of_pages * 4096 - buffer_head_size;
	((struct mm_buffer *)virt_addr_start)->flag = 0;
	list_init(&((struct mm_buffer *)virt_addr_start)->list);
}
void kmm_extended_page(uint64_t virt_addr_start, uint64_t num_of_pages)
{
	struct mm_buffer *heap_end = list_entry(((struct mm_buffer *)virt_addr_start)->list->previous, struct mm_buffer, list);
	
	if (heap_end->flag == 0)
		heap_end->size += num_of_pages * 4096;
	else
	{
		struct mm_buffer *new_end = heap_end + heap->size + buffer_head_size;
		list_init(&new_end->list);
		new_end->flag = 0;
		new_end->size = num_of_pages * 4096 - buffer_head_size;
	}
}
/**
 * This function is automatically called by kfree.
 */
void __kmm_buffer_merge(void *heap)
{
	
}
/**
 * Allocate a buffer of size bytes.
 */
void *kmalloc(size_t size)
{
	struct mm_buffer *it = heap_start;
	list_for_each(it, heap_start)
	{
		if (it->size > size + buffer_head_size && it->flag == 0)	//Split the buffer.
		{
			struct mm_buffer *temp = it + size + buffer_head_size;
			temp->size = it->size - size - buffer_head_size;
			temp->flag = 0;
			it->size = size;
			it->flag = 1;
			list_init(temp->list);
			list_add_after(it->list, temp->list);
			return it + buffer_head_size;
		}
	}
	return NULL;
}

/**
 * Deallocate a buffer.
 */
void kfree(void *ptr)
{
	ptr -= buffer_head_size;
	ptr->size += ((struct mm_buffer *)(ptr + ptr->size + buffer_head_size))->size;
	list_del(((struct mm_buffer *)(ptr + ptr->size + buffer_head_size))->list);
	
	struct mm_buffer *it = heap_start - buffer_head_size;
	it->flag = 0;
	//Join two close blocks
	list_for_each(it, heap_start)
	{
		struct mm_buffer *temp = list_entry(it->list->next, struct mm_buffer, list);
		if (it + it->size == temp)
		{
			it->size += temp->size + buffer_head_size;
			list_del(temp->list);
		}
	}
	
}
/**
 * Initialize kernel memory
 */
void mm_init(void)
{
	page_table_init();
	kmm_init_page(kernel_base_address + kernel_size , );
		
}
