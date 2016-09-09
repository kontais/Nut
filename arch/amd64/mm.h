#ifndef _MM_H_
#define _MM_M_

/**
 * Global Descriptor Table Resgister
 */
struct gdt
{
	struct seg_dsc *seg_dsc;
	size_t length;
}
/**
 * Local Descriptor Table Register
 */
struct ldt
{
	struct seg_dsc *seg_dsc;
	size_t legnth;
}
/**
 * Interrupt Description Table Register
 */
struct idt
{
	struct seg_sel *seg_sel;
	size_t length;
	
}
struct seg_sel
{
	UINT16 rpl:2,
	       ti:1,
	       index:13;
}
struct seg_dsc
{
	
struct int_gate_dsc
{
	UINT16 offset_0_15;
	struct seg_sel seg_sel;
	UINT16 ist:3,
	       _reserved_1:5,
	       type:4,
	       _reserved_2:1,
	       dpl:2,
	       p:1;
	UINT16 offset_15_31;
	UINT32 offset_32_63;
	UINT32 _reserved_3;
}
#endif
