#include <mm.h>
#include <paging.h>

int vm_map_init(vm_map_t *vm_map)
{
	list_init(&vm_map->vm_map_list);
	vm_map->map_entry = NULL;
}
int vm_map_add(vm_map_t *vm_map, vm_map_entry *entry)
{
	vm_map_t *new_map;
	if ((new_map = malloc(sizeof(vm_map_t))) == NULL)
		return -1;
	list_init(&new_map->vm_map_list);
	list_add_before(&vm_map_list, &new_map->vm_map_list);
	new_map->map_entry = entry;
	return 0;
}

void vm_map_do_mapping(vm_map_t *vm_map)
{
	list_head_t *it;
	list_for_each(it, &vm_map->vm_map_list)
	{
		vm_map_entry_t *map_entry = list_entry(it, vm_map_entry_t, vm_map_list);
		assert(map_entry->flags & PAGING_MASK_ADDR == 0);
		modify_chunk_mapping(get_current_plm4e(), map_entry->virt_addr, map_entry->phy_addr, map_entry->page_nums, map_entry->flags);
	}
}
