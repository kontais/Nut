#ifndef _PHY_MM_POOL_
#define _PHY_MM_POOL_

#include <uefi.h>

typedef struct
{
	uint64_t _reserved_1:16,
		 phy_addr:48,
		 _reserved_2:11,
		 used:1;
}mm_pool_desc_t;
typedef struct
{
	uint64_t block_size;
	uint64_t ptr;
	struct mm_pool_desc *desc;
}mm_pool_info_block_t;

extern mm_pool_info_block_t *mm_pool_info_block;

void phy_mm_pool_init(efi_memory_descriptor_t *uefi_desc, uint64_t info_block_addr);
uint64_t phy_mm_pool_alloc(void);
void phy_mm_pool_free(uint64_t addr);

#endif
