#include "phy_mm_pool.h"
#include <types.h>

mm_pool_info_block_t *mm_pool_info_block;
/**
 * Convert UEFI format memory map into internal format
 * for the convenience of allocating and deallocating
 * physical pages.
 * @uefi_desc pointer to UEFI memory map structure
 * @info_block_addr address of global mm_pool_info_block
 */
void phy_mm_pool_init(efi_memory_descriptor_t *uefi_desc, uint64_t info_block_addr)
{
	mm_pool_info_block = (mm_pool_info_block_t *)info_block_addr;
	mm_pool_info_block->size = 0;
	mm_pool_info_block->ptr = 0;
	mm_pool_info_block->desc = mm_pool_info_block + 1;
	mm_pool_desc_t *ptr = mm_pool_info_block->desc;
	for (efi_memory_descriptor_t it = uefi_desc; *it != 0; it ++)
	{
		if (it->type == EfiConventionalMemory)
		{
			for (int i = 0; i < it->number_of_pages; i ++)
			{
				*ptr++ = (it->physical_start + (i << 12)) & 0x0000fffffffff000;
			}
		}
	}
}

uint64_t phy_mm_pool_alloc(void)
{
	mm_pool_desc_t *mm_pool_desc;
	while (*(mm_pool_desc = mm_pool_info_block->desc + mm_pool_info_block->ptr)->used != 0)
	{
		mm_pool_info_block->ptr = ++mm_pool_info_block->ptr % mm_pool_info_block->block_size;
	}
	mm_pool_desc->used = 1;
	mm_pool_info_block->ptr = ++mm_pool_info_block->ptr % mm_pool_info_block->block_size;
	return mm_pool_desc & 0x0000fffffffff000;
}

void phy_mm_pool_free(uint64_t addr)
{
	for (uint64_t i = 0; i < mm_pool_info_block->block_size; i ++)
	{
		if (addr == *(mm_pool_info_block->desc + i) & 0x0000fffffffff000)
		{
			*(mm_pool_info_block->desc + i)->used = 0;
			return;
		}
	}
}
