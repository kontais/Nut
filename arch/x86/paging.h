#ifndef _PAGING_H_
#define _PAGING_H_


struct cr3
{
	uint64_t _ignored_1:3,
	         pwd:1,
	         pcd:1,
	         _ignored_2:7,
	         phy_addr:40,
	         _reserved_1:12;
// 	uint64_t PCID:12,
// 	        addr:40,
// 	        _reserved:12;
};


struct plm4_entryd
{
	uint64_t p:1,
	         r_w:1,
	         u_s:1,
	         pwt:1,
	         pcd:1,
	         a:1,
	         _ignored_1:1,
	         _reserved_1:1,
	         _ignored_2:4,
	         phy_addr:40,
	         _ignored_3:11,
	         xd:1;
};

struct pdpte_entry
{
	uint64_t p:1,
	         r_w:1,
		 u_s:1,
		 pwt:1,
		 pcd:1,
		 a:1,
		 _ignored_1:1,
		 ps:1,
		 _ignored_2:4,
		 phy_addr:40,
		 _ignored_3:11,
		 xd:1;
};
struct pde_entry
{
	uint64_t p:1,
	         r_w:1,
		 u_s:1,
		 pwd:1,
		 pcd:1,
		 a:1,
		 _ignored_1:1,
		 ps:1,
		 _ignored_2:4,
		 phy_addr:40,
		 _ignored_3:11,
		 xd:1;
};
struct pte_entry
{
	uint64_t p:1,
	         r_w:1,
		 u_s:1,
		 pwd:1,
		 pcd:1,
		 a:1,
		 d:1,
		 pat:1,
		 g:1,
		 _ignored_1:3,
		 phy_addr:40,
		 _ignored_2:7,
		 pk:4,
		 xd:1;
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
#endif

