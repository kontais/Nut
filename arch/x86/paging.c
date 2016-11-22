#include <paging.h>

/**
 * Modify the page tables.
 * @plm4 top entry of the page table
 * @virt_addr virtual address to be mapped
 * @phy_addr physical address to be mapped to
 * @flag extra function flags to set
 * @retval 0 : succeed
 * 	  -1 : error
 */

 
static inline uint64_t get_virt_addr_of_page_entry(uint64_t entry)
{
	
}
static inline uint64_t 
int modify_mapping(struct pml4e_table *plm4e, uint64_t virt_addr, uint64_t phy_addr, uint64_t flag)
{
	uint64_t plm4e_entry = *(plm4e + (virt_addr >> 39 & PAGING_MASK_ENTRY_OFFSET);
	if (!(plm4e_entry & PAGING_MASK_P))
	{
		make a new pdpte entry;
	}
	uint64_t pdpte_entry = *(get_virt_addr_of_page_entry(plm4e_entry)  + (virt_addr >> 30 & PAGING_MASK_ENTRY_OFFSET));
	if (!(pdpte_entry & PAGING_MASK_P))
	{
		make a new pde entry;
	}
	uint64_t pde_entry = *(get_virt_addr_of_page_entry(pdpte_entry)  + (virt_addr >> 21 & PAGING_MASK_ENTRY_OFFSET));
	if (!(pde_entry & PAGING_MASK_P))
	{
		uint64_t pte_entry = *(get_virt_addr_of_page_entry(pde_entry) + (virt_addr >> 12 & PAGING_MASK_ENTRY_OFFSET));
		pte_entry = (phy_addr & PAGING_MASK_ADDR) | flag;
	}
	return 0;
}
