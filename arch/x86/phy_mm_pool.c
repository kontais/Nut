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
void mm_pool_init(efi_memory_descriptor_t *uefi_desc, uint64_t info_block_addr)
{
	mm_pool_info_block = (mm_pool_info_block_t *)info_block_addr;
	mm_pool_info_block->size = 0;
	mm_pool_info_block->desc = mm_pool_info_block + 1;
	mm_pool_desc_t *ptr = mm_pool_info_block->desc;
	for (efi_memory_descriptor_t it = uefi_desc; *it != 0; it ++)
	{
		if (it->type == EfiConventionalMemory)
		{
			for (int i = 0; i < it->number_of_pages; i ++)
			{
				*ptr++ = (it->physical_start + (i << 12)) & 0xffffffffffff0000;
			}
		}
	}
}

uint64_t mm_pool_alloc(void)
{
	
}
void mm_pool_free(uint64_t addr)
{
	
}
