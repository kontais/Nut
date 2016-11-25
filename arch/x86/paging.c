#include <paging.h>
#include <klibc.h>
#include <types.h>
/**
 * Modify the page tables.
 * @plm4 top entry of the page table
 * @virt_addr virtual address to be mapped
 * @phy_addr physical address to be mapped to
 * @flag extra function flags to set
 * @retval 0 : succeed
 * 	  -1 : error
 */
uint64_t syscall_base_addr = 0;
uint64_t kernel_image_base_addr = 0;
uint64_t kernel_heap_base_addr = 0;
uint64_t virtual_map_base_addr = 0;
uint64_t kernel_stack_base_addr = 0;
uint64_t phy_map_addr = 0;

#define SYSCALL_BASE		0xffffffffff000000
#define KERNEL_IMAGE_BASE	0xffffffff80000000
#define KERNEL_HEAP_BASE	0xfffff80000000000
#define VIRTUAL_MAP_BASE	0xfffff40000000000
#define KERNEL_STACK_BASE	0xfffff00000000000
#define PHY_MAP_BASE		0xffff800000000000

static inline uint64_t __convert_virt_to_phy(uint64_t addr)
{
	return addr - phy_map_addr;
}
static inline uint64_t __convert_phy_to_virt(uint64_t addr)
{
	return addr + phy_map_addr;
}
static inline uint64_t __get_virt_addr(uint64_t *entry)
{
	return __convert_phy_to_virt((*entry & PAGING_MASK_ADDR));
}
static inline uint64_t __get_phy_addr(uint64_t *entry)
{
	return *entry & PAGING_MASK_ADDR;
}
static inline uint64_t __get_flag(uint64_t *entry)
{
	return *entry & (PAGING_MASK_P | PAGING_MASK_R_W | PAGING_MASK_U_S | PAGING_MASK_PWT | PAGING_MASK_PCD | PAGING_MASK_A | PAGING_MASK_D | PAGING_MASK_PAT | PAGING_MASK_G | PAGING_MASK_XD);
}
// static uint64_t make_a_new_entry_table(uint64_t init_entry)
// {
// 	uint64_t addr = phy_mm_pool_alloc();
// 	for (int i = 0; i < 512; i ++)
// 	{
// 		*(uint64_t *)(addr + i) = init_entry;
// 	}
// 	return addr;
// }

static uint64_t __mk_entry(uint64_t addr, uint64_t flag)
{
	return addr & PAGING_MASK_ADDR | flag ;
}
static void __init_table(void *table, uint64_t init_entry)
{
	for (int i = 0; i < 512; i ++)
	{
		*((uint64_t *)table + i) = init_entry;
	}
}
static void __set_entry(void *table, uint16_t n, uint64_t addr, uint64_t flag)
{
	assert(n < 512 && n >= 0);
	*((uint64_t *)table + n) = addr & PAGING_MASK_ADDR | flag;
}

uint64_t page_table_head = 0;
static void *__continous_alloc(void)
{
	page_table_head += 0x1000;
	return (void *)(page_table_head - 0x1000);
}
int __do_mapping(struct plm4e_table *plm4e, uint64_t virt_addr, uint64_t phy_addr, uint64_t flag, void *(*alloc)(void))
{
	struct pdpte_table *pdpte;
	struct pde_table *pde;
	struct pte_table *pte;
	uint64_t *plm4e_entry = plm4e->entry + (virt_addr >> 39 & PAGING_MASK_ENTRY_OFFSET);
	if (!(*plm4e_entry & PAGING_MASK_P))
	{
		pdpte = (*alloc)();
		__init_table(pdpte, PAGING_MASK_PWT | PAGING_MASK_PCD);
		*plm4e_entry = __mk_entry(__convert_virt_to_phy((uint64_t )pdpte), PAGING_MASK_P | PAGING_MASK_PWT | PAGING_MASK_PCD);
	}
	else
		pdpte = (struct pdpte_table *)__get_virt_addr(plm4e_entry);
	
	uint64_t *pdpte_entry = pdpte->entry + (virt_addr >> 30 & PAGING_MASK_ENTRY_OFFSET);
	if (!(*pdpte_entry & PAGING_MASK_P))
	{
		pde = (*alloc)();
		__init_table(pde, PAGING_MASK_PWT | PAGING_MASK_PCD);
		*pdpte_entry = __mk_entry(__convert_virt_to_phy((uint64_t )pde), PAGING_MASK_P | PAGING_MASK_PWT | PAGING_MASK_PCD);
	}
	else
		pde = (struct pde_table *)__get_virt_addr(pdpte_entry);
	
	uint64_t *pde_entry = pde->entry + (virt_addr >> 21 & PAGING_MASK_ENTRY_OFFSET);
	if (!(*pde_entry & PAGING_MASK_P))
	{
		pte = (*alloc)();
		__init_table(pte, PAGING_MASK_PWT | PAGING_MASK_PCD);
		*pde_entry = __mk_entry(__convert_virt_to_phy((uint64_t )pte), PAGING_MASK_P | PAGING_MASK_PWT | PAGING_MASK_PCD);
// 		printf("%lx\n", (uint64_t)*pde_entry);
	}
	else
		pte = (struct pte_table *)__get_virt_addr(pde_entry);
	
	uint64_t *pte_entry = pte->entry + (virt_addr >> 12 & PAGING_MASK_ENTRY_OFFSET);
	*pte_entry = __mk_entry(phy_addr, flag);
}
int __map_by_pages(struct plm4e_table *plm4e, uint64_t virt_start_addr, uint64_t phy_start_addr, uint64_t number_of_pages, uint64_t flag, void *(*phy_page_alloc)(void))
{
	for (; number_of_pages -- > 0; phy_start_addr += 0x1000, virt_start_addr += 0x1000)
	{
		__do_mapping(plm4e, virt_start_addr, phy_start_addr, flag, phy_page_alloc);
	}
}

/**
 * Create a default identified-mapped memory map with a given base address.
 * All table will be placed in a continuous space.
 * @base base address of top table
 * @range max range of physical address
 * @retval bytes of the total tables
 * NOTE:The function should be called only during the boot sequence.
 */
uint64_t create_default_identified_mapped_tables(uint64_t page_table_base, uint64_t number_of_pages)
{
	struct plm4e_table *plm4e;
	page_table_head = page_table_base;
	plm4e = __continous_alloc();
	__init_table(plm4e, PAGING_MASK_PWT | PAGING_MASK_PCD);
	__map_by_pages(plm4e, 0, 0, number_of_pages, PAGING_MASK_P | PAGING_MASK_R_W | PAGING_MASK_PWT | PAGING_MASK_PCD, &__continous_alloc);
// 	printf("%s","Hello,wolrd.\n");
// 	printf("%s","Nice to meet you.\n");
// 	asm ("hlt");
// 	printf("%lx\n", (uint64_t)plm4e);
	__map_by_pages(plm4e, PHY_MAP_BASE, 0, number_of_pages, PAGING_MASK_P | PAGING_MASK_R_W | PAGING_MASK_PWT | PAGING_MASK_PCD, &__continous_alloc);
	__map_by_pages(plm4e, KERNEL_IMAGE_BASE, 0x100000, 0x100, PAGING_MASK_P | PAGING_MASK_R_W | PAGING_MASK_PWT | PAGING_MASK_PCD, &__continous_alloc);
	__map_by_pages(plm4e, KERNEL_HEAP_BASE, 0x200000, 0x100, PAGING_MASK_P | PAGING_MASK_R_W | PAGING_MASK_PWT | PAGING_MASK_PCD, &__continous_alloc);
	__map_by_pages(plm4e, KERNEL_STACK_BASE, 0x300000, 0x100, PAGING_MASK_P | PAGING_MASK_R_W | PAGING_MASK_PWT | PAGING_MASK_PCD, &__continous_alloc);
// 	__map_by_pages(plm4e, 0, 0, number_of_pages, PAGING_MASK_P | PAGING_MASK_R_W | PAGING_MASK_PWT | PAGING_MASK_PCD, &__continous_alloc);
	
	uint64_t out = 0;
	uint64_t pe = 0x400000 | 0x18;
	asm (
		"mov %1, %%rax\r\n"
		"mov %%rax, %%cr3\r\n"
 		"mov %%cr3, %%rbx\r\n"
		"mov %%rbx, %0\r\n"
		: "=m" (out)
		: "m" (pe)
	);
	printf("%lx\n", out);
	asm(
		"mov %0, %%rax\r\n"
		"add $jump, %%rax\r\n"
		"jmp *%%rax\r\n"
		:
		: "r"(KERNEL_IMAGE_BASE)
	);
	asm ("jump:");
	printf("%s","Hello,wolrd.\n");
	printf("%s","Nice to meet you.\n");
	asm (
		"call read\r\n"
		"read:\r\n"
		"pop %0\r\n"
		: "=m" (out)
		: 
	);
	printf("%lx\n", out);
	printf("%lx\n", page_table_head);
	extern char text_start[];
	extern char text_end[];
	extern char data_start[];
	extern char data_end[];
	extern char bss_start[];
	extern char bss_end[];
	printf("text_start=%lx\n", text_start);
	printf("text_end=%lx\n", text_end);
	printf("data_start=%lx\n", data_start);
	printf("data_end=%lx\n", data_end);
	printf("bss_start=%lx\n", bss_start);
	printf("bss_end=%lx\n", bss_end);
// 	printf("data_load=%lx\n", data_load_start);
	asm ("hlt");
	phy_map_addr = PHY_MAP_BASE; 
	return page_table_head - page_table_base;
}
int mm_init(void)
{
	create_default_identified_mapped_tables(0x400000, 0x120000000 >> 12);
}
// int modify_mapping(struct pml4e_table *plm4e, uint64_t virt_addr, uint64_t phy_addr, uint64_t flag, void *(*alloc)(void))
// {
// 	uint64_t plm4e_entry = plm4e->entry[virt_addr >> 39 & PAGING_MASK_ENTRY_OFFSET];
// 	if (!(plm4e_entry & PAGING_MASK_P))
// 	{
// 		plm4e_entry = make_a_new_entry_table(0);
// 	}
// 	uint64_t pdpte_entry = ((struct pdpte_table *)get_virt_addr_of_page_entry(plm4e_entry))->entry[virt_addr >> 30 & PAGING_MASK_ENTRY_OFFSET];
// 	if (!(pdpte_entry & PAGING_MASK_P))
// 	{
// 		pdpte_entry = make_a_new_entry_table(0);
// 	}
// 	uint64_t pde_entry = ((struct pde_table *)get_virt_addr_of_page_entry(pdpte_entry))->entry[virt_addr >> 21 & PAGING_MASK_ENTRY_OFFSET];
// 	if (!(pde_entry & PAGING_MASK_P))
// 	{
// 		pde_entry = make_a_new_entry_table(0);
// 	}
// 	uint64_t pte_entry = ((struct pte_table *)get_virt_addr_of_page_entry(pde_entry))->entry[virt_addr >> 12 & PAGING_MASK_ENTRY_OFFSET];
// 	pte_entry = (phy_addr & PAGING_MASK_ADDR) | flag;
// 	return 0;
// }
int query_mapping(struct plm4e_table *plm4e, uint64_t virt_addr, uint64_t *phy_addr, uint64_t *flag)
{
	struct pdpte_table *pdpte;
	struct pde_table *pde;
	struct pte_table *pte;
	uint64_t *plm4e_entry = plm4e->entry + (virt_addr >> 39 & PAGING_MASK_ENTRY_OFFSET);
	if (!(*plm4e_entry & PAGING_MASK_P))
	{
		return -1;
	}
	else
		pdpte = (struct pdpte_table *)__get_virt_addr(plm4e_entry);
	
	uint64_t *pdpte_entry = pdpte->entry + (virt_addr >> 30 & PAGING_MASK_ENTRY_OFFSET);
	if (!(*pdpte_entry & PAGING_MASK_P))
	{
		return -1;
	}
	else
		pde = (struct pde_table *)__get_virt_addr(pdpte_entry);
	
	uint64_t *pde_entry = pde->entry + (virt_addr >> 21 & PAGING_MASK_ENTRY_OFFSET);
	if (!(*pde_entry & PAGING_MASK_P))
	{
		return -1;
	}
	else
		pte = (struct pte_table *)__get_virt_addr(pde_entry);
	
	uint64_t *pte_entry = pte->entry + (virt_addr >> 12 & PAGING_MASK_ENTRY_OFFSET);
	if (!(*pte_entry & PAGING_MASK_P))
	{
		return -1;
	}
	else
	{
		*phy_addr = __get_phy_addr(pte_entry);
		*flag = __get_flag(pte_entry);
		return 0;
	}
}

// int query_mapping(struct plm4_entry *plm4, uint64_t virt_addr, uint64_t *phy_addr, int *flag)
// {
// //change the method ,for example:high 16 000
// 	int i,k;
// 	uint64_t py,vir;
// 	vir_addr=vir_addr&0x0000ffffffffffff;   //remove high 16 bits
// //get the begain phy_addr of pdpte_entry
// //plm4.p is the flag which judges weather the paging is present
// 	if(plm4.p==0){
// 		printf("false to query!\n");
// 		return 0;
// 	}
// 	else{
// 		vir=vir_addr>>39;
// 		py=vir&0x1ff;
// 		plm4=plm4+py;
// 	}
// //get the begain phy_addr of pde_entry
// 	if(plm4.p==0){
// 		printf("false to query!\n");
// 		return 0;
// 	}
// 	else{
// 		vir=vir_addr>>30;
// 		py=vir&0x1ff;
// 		plm4=plm4+py;
// 	}
// //get the begain phy_addr of pte_entry
// 	if(plm4.p==0){
// 		printf("false to query!\n");
// 		return 0;
// 	}
// 	else{
// 		vir=vir_addr>>21;
// 		py=vir&0x1ff;
// 		plm4=plm4+py;
// 	}
// //get the begain phy_addr of pte4k_entry
// 	if(plm4.p==0){
// 		printf("false to query!\n");
// 		return 0;
// 	}
// 	else{
// 		vir=vir_addr>>12;
// 		py=vir&0x1ff;
// 		plm4=plm4+py;
// 	}
// //get phy_addr 
// 	if((plm4.p)==0){
// 		printf("false to query!\n");
// 		return 0;
// 	}
// 	else{
// 		py=vir_addr&0xfff;
// 		plm4=plm4+py;
// 	}
// //get the final flag and phy_addr
// 	*phy_addr=*plm4;
// 	return 0;
// }



