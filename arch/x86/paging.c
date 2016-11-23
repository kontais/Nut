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

int query_mapping(struct plm4_entry *plm4, uint64_t virt_addr, uint64_t *phy_addr, int *flag)
{
//change the method ,for example:high 16 000
	int i,k;
	uint64_t py,vir;
	vir_addr=vir_addr&0x0000ffffffffffff;   //remove high 16 bits
//get the begain phy_addr of pdpte_entry
//plm4.p is the flag which judges weather the paging is present
	if(plm4.p==0){
		printf("false to query!\n");
		return 0;
	}
	else{
		vir=vir_addr>>39;
		py=vir&0x1ff;
		plm4=plm4+py;
	}
//get the begain phy_addr of pde_entry
	if(plm4.p==0){
		printf("false to query!\n");
		return 0;
	}
	else{
		vir=vir_addr>>30;
		py=vir&0x1ff;
		plm4=plm4+py;
	}
//get the begain phy_addr of pte_entry
	if(plm4.p==0){
		printf("false to query!\n");
		return 0;
	}
	else{
		vir=vir_addr>>21;
		py=vir&0x1ff;
		plm4=plm4+py;
	}
//get the begain phy_addr of pte4k_entry
	if(plm4.p==0){
		printf("false to query!\n");
		return 0;
	}
	else{
		vir=vir_addr>>12;
		py=vir&0x1ff;
		plm4=plm4+py;
	}
//get phy_addr 
	if((plm4.p)==0){
		printf("false to query!\n");
		return 0;
	}
	else{
		py=vir_addr&0xfff;
		plm4=plm4+py;	
	}
//get the final flag and phy_addr
	*phy_addr=*plm4;
	return 0;
}





















