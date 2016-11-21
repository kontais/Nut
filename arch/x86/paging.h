#ifndef _PAGING_H_
#define _PAGING_H_

//Bit order:big endian
struct cr3
{
	uint64_t _reserved_1:12
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
	struct plm4_entry[512];
};
struct pdpte_table
{
	struct pdpte_entry[512];
};
struct pde_table
{
	struct pde_entry[512];
};
struct pte_table
{
	struct pte_entry[512];
};

// uint64_t get_phy_addr(struct plm4_entry *plm4, uint64_t virt_addr);
// uint64_t* get_virt_addr(struct plm4_entry *plm4, uint64_t phy_addr);

int modify_mapping(struct plm4_entry *plm4, uint64_t virt_addr, uint64_t phy_addr, int flag);
int query_mapping(struct plm4_entry *plm4, uint64_t virt_addr, uint64_t *phy_addr, int *flag);


#endif

