#ifndef _PAGING_H_
#define _PAGING_H_

//Bit order:big endian
struct cr3
{
	uint64_t _reserved_1:12,
		 phy_addr:40,
		 _ignored_2:7,
		 pcd:1,
		 pwt:1,
		 _ignored_1:3;
// 	uint64_t PCID:12,
// 	        addr:40,
// 	        _reserved:12;
};


struct plm4_entry
{
	uint64_t xd:1,
		 _ignored_3:11,
		 phy_addr:40,
		 _ignored_2:4,
		 _reserved_1:1,
		 _ignored_1:1,
		 a:1,
		 pcd:1,
		 pwt:1,
		 u_s:1,
		 r_w:1,
		 p:1;
};

struct pdpte_entry
{
	uint64_t xd:1,
		 _ignored_3:11,
		 phy_addr:40,
		 _ignored_2:4,
		 ps:1,
		 _ignored_1:1,
		 a:1,
		 pcd:1,
		 pwt:1,
		 u_s:1,
		 r_w:1,
		 p:1;
};
struct pde_entry
{
	uint64_t xd:1,
		 _ignored_3:11,
		 phy_addr:40,
		 _ignored_2:4,
		 ps:1,
		 _ignored_1:1,
		 a:1,
		 pcd:1,
		 pwt:1,
		 u_s:1,
		 r_w:1,
		 p:1;
};
struct pte_entry
{
	uint64_t xd:1,
		 pk:4,
		 _ignored_2:7,
		 phy_addr:40,
		 _ignored_1:3,
		 g:1,
		 pat:1,
		 d:1,
		 a:1,
		 pcd:1,
		 pwt:1,
		 u_s:1,
		 r_w:1,
		 p:1;
};
struct pml4e_table
{
	struct plm4_entry entry[512];
};
struct pdpte_table
{
	struct pdpte_entry entry[512];
};
struct pde_table
{
	struct pde_entry entry[512];
};
struct pte_table
{
	struct pte_entry entry[512];
};

#define PAGING_MASK_P		0x0000000000000001
#define PAGING_MASK_R_W		0x0000000000000002
#define PAGING_MASK_U_S		0x0000000000000004
#define PAGING_MASK_PWT		0x0000000000000008
#define PAGING_MASK_PCD		0x0000000000000010
#define PAGING_MASK_A		0x0000000000000020
#define PAGING_MASK_D		0x0000000000000040
#define PAGING_MASK_PAT		0x0000000000000080
#define PAGING_MASK_G		0x0000000000000100
#define PAGING_MASK_ADDR	0x0000fffffffff000
#define PAGING_MASK_XD		0x8000000000000000

#define PAGING_MASK_ENTRY_OFFSET	     0x1ff


#define SYSCALL_BASE		0xffffffffff000000
#define KERNEL_IMAGE_BASE	0xffffffff80000000
#define KERNEL_HEAP_BASE	0xfffff80000000000
#define VIRTUAL_MAP_BASE	0xfffff40000000000
#define KERNEL_STACK_BASE	0xfffff00000000000
#define PHY_MAP_BASE		0xffff800000000000
// uint64_t get_phy_addr(struct plm4_entry *plm4, uint64_t virt_addr);
// uint64_t* get_virt_addr(struct plm4_entry *plm4, uint64_t phy_addr);

int modify_mapping(struct pml4e_table *plm4e, uint64_t virt_addr, uint64_t phy_addr, uint64_t flag);
int query_mapping(struct pml4e_table *plm4e, uint64_t virt_addr, uint64_t *phy_addr, uint64_t *flag);

#endif

