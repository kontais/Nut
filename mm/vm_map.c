#include <mm.h>
#include <paging.h>
#include <vm.h>

int vm_map_init(vm_map_t *vm_map)
{
	list_init(&vm_map->vm_map_list);
	vm_map->map_entry = NULL;
}
int vm_map_add(vm_map_t *vm_map, vm_map_entry_t *entry)
{
	vm_map_t *new_map;
	if ((new_map = malloc(sizeof(vm_map_t))) == NULL)
		return -1;
	list_init(&new_map->vm_map_list);
	list_add_before(&vm_map->vm_map_list, &new_map->vm_map_list);
	new_map->map_entry = entry;
	return 0;
}

void vm_map_do_mapping(vm_map_t *vm_map)
{
	list_head_t *it;
// 	printf("%lx\n", vm_map);
	list_for_each(it, &vm_map->vm_map_list)
	{
		vm_map_t *vm_map = list_entry(it, vm_map_t, vm_map_list);
// 		printf("%lx\n", vm_map);
		vm_map_entry_t *entry = vm_map->map_entry;
// 		printf("%lx\n", entry);
		assert(vm_map != NULL);
// 		printf("%lx\n", entry->flags);
		assert((entry->flags & PAGING_MASK_ADDR) == 0);
		assert(entry->virt_addr + (entry->page_nums << 12) <= 0x0000800000000000);
// 		printf("%lx %lx %lx %lx\n",entry->virt_addr, entry->phy_addr, entry->page_nums, entry->flags);
		modify_chunk_mapping(get_current_plm4e(), entry->virt_addr, entry->phy_addr, entry->page_nums, entry->flags);
	}
}
void vm_map_undo_mapping(vm_map_t *vm_map)
{
	
	
}
