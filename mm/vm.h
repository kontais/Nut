#ifndef _VM_H_
#define _VM_H_

#include <ktypes.h>
#include <list.h>
#include <proc.h>

#define VM_MAP_READ	0x0000000000000001
#define VM_MAP_WRITE 	0x0000000000000002
#define VM_MAP_EXEC	0x0000000000000004
typedef struct vm_map
{
	struct list_head vm_map_list;
	uint64_t virt_addr;
	uint64_t phy_addr;
	uint64_t page_nums;
	uint64_t flag;
	uint64_t refs;
}vm_map_t;


void *malloc(size_t size);
void free(void *ptr);
void vm_init(void);

#endif
