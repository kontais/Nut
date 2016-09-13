#include <mm.h>
struct pte_entry *find_page_table_entry(uint64_t virt_addr)
{
	if (virt_addr >= kernel_memory_base)
		panic("Illigal virt_addr to find.");
	
	struct pml4e_table *pml4e_table_ptr = (struct pml4e_table *)(cr3->phy_addr + kernel_memory_base);
	struct pdpte_table *pdpte_table_ptr = (struct pdpte_table *)(pml4e_table_ptr[virt_addr >> 38]->phy_addr + kernel_memory_base);
	struct pde_table *pde_table_ptr = (struct pde_table *)(pdpte_table_ptr[(virt_addr >> 29) & 0x1ff]->phy_addr + kernel_memory_base);
	struct pte_table *pte_table_ptr = (struct pte_table *)(pde_table_ptr[(virt_addr >> 20) & 0x1ff]->phy_addr + kernel_memory_base);
	struct pte_entry *pte_entry_ptr = (struct pte_entry *)(pte_table_ptr[(virt_addr >> 11) & 0x1ff]->phy_addr + kernel_memory_base);
	
	//Now we find the right pte_entry through five level tables;
	return pte_entry_ptr;
}
/**
 * Map a virtual address to a physical address in the struct virt_page
 */
void do_map(struct virt_page)
{
	struct pte_entry *pte_entry_ptr = find_page_table_entry(virt_page->virt_addr);
	pte_entry_ptr->p = 1;
	pte_entry_ptr->r_w = (virt_page->flag & page_flag_write);
	pte_entry_ptr->u_s = (virt_page->flag & page_flag_read);
	pte_entry_ptr->pwd = 1;
	pte_entry_ptr->pcd = 1;
	pte_entry_ptr->a = 0;
	pte_entry_ptr->d = 0;
	pte_entry_ptr->pat = 0;//PAT could be enable in the future.
	pte_entry_ptr->g = 1;
	pte_entry_ptr->phy_addr = virt_page->phy_page->phy_addr >> 12;
// 	pte_entry_ptr->pk 
	pte_entry_ptr->xd = 0;
	
}
/**
 * Unmap a virtual address.
 */
void do_unmap(struct virt_page)
{
	struct pte_entry *pte_entry_ptr = find_page_table_entry(virt_page->virt_addr);
	pte_entry_ptr->p = 0;
}
