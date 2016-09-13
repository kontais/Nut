#ifndef _MM_H_
#define _MM_H_
/**
 * The fisrt 1GB of address space is preserved for kernel and 
 * the rest is for user space.
 * This function initialize the page table.
 */
struct memory_map
{
	struct region
	{
		uint64_t virt_addr;
		uint64_t phy_addr;
		uint64_t page_nums;
	}*region;
	uint64_t nums;
}
/**
 * Physical address page definition.
 * Flag definition:
 */

struct phy_page
{
	struct   list_head list;
	uint64_t phy_addr;
	uint32_t ref;
};
#define page_flag_read	0x01
#define page_flag_write	0x02
#define page_flag_exec  0x04
struct virt_page
{
	struct   list_head list;
	struct   phy_page  *phy_page;
	uint64_t virt_addr;
	uint32_t flag;
};
struct phy_page_table
{
	struct list_head *used;
	struct list_head *free;
};
#endif
