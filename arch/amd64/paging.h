#ifndef _PAGING_H_
#define _PAGING_H_


union cr3
{
	UINT64 _ignored_1:3,
	       pwd:1,
	       pcd:1,
	       _ignored_2:7,
	       addr:40,
	       _reserved_1:12;
	UINT64 PCID:12,
	       addr:40,
	       _reserved:12;
};
typedef union cr3 struct cr3;


struct plm4
{
	UINT64 p:1,
	       r_w:1,
	       u_s:1,
	       pwt:1,
	       pcd:1,
	       a:1,
	       _ignored_1:1,
	       _reserved_1:1,
	       _ignored_2:3,
	       addr:
#endif
