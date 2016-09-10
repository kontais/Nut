#ifndef _MM_H_
#define _MM_M_

/**
 * Memory Management register difinitions
 * The three tables consist of linear arrays of arbitrary combines of descriptors.
 * Segment selector is used as a pointer with implicit base address in the table register
 * to the descriptor in the corresponding table.
 */

/**
 * Global Descriptor Table Resgister
 */
struct gdt
{
	UINT16 limit;	//Limits all should be must be 8N-1
	UINT64 base;
};
/**
 * Local Descriptor Table Register
 */
struct ldt
{
	UINT16 limit;
	UINT64 base;
};
/**
 * Interrupt Description Table Register
 */
struct idt
{
	UINT16 limit;
	UINT64 base;
};
/**
 * Segment selector
 */
struct seg_sel
{
	UINT16 rpl:2,
	       ti:1,
	       index:13;
};
/**
 * Segment descriptor
 */
struct seg_dsc
{
	UINT16 seg_limit_0_15;
	UINT16 base_0_15;
	UINT8  base_16_23:
	UINT8  type:4,
	       s:1,
	       dpl:2,
	       p:1;
	UINT8  seg_limit_16_19:4,
	       avl:1,
	       l:1,
	       d_b:1,
	       g:1;
	UINT8  base_24_31;
};
/**
 * Call gate descriptor
 */
struct call_gate_dsc
{
	UINT16 offset_0_15;
	struct seg_sel seg_sel;
	UINT8  _reserved_1:8;
	UINT8  type_1:4,
	       _reserved_2:1,
	       dpl:2,
	       p:1;
	UINT16 offset_16_31;
	UINT32 offset_32_63;
	UINT32 _reserved_3:8,
	       type_1:5,
	       _reserved_4:19;
};
/**
 * Interrupt/trap segment descriptor
 */
struct int_trap_seg_dsc
{
	UINT16 offset_0_15;
	struct seg_sel seg_sel;
	UINT16 ist:4,
	       _reserved_1:5,
	       type:4,
	       _reserved_2:1,
	       dpl:2,
	       p:1;
	UINT16 offset_15_31;
	UINT32 offset_32_63;
	UINT32 _reserved_3;
};
/**
 * Task switch is not supported in 64-bit mode
 * but operation system must create at lieat one
 * tss. after activating IA-32e mode.It must execute
 * the LTR instruction(in 64-bit mode) to load
 * the TR register with a pointer to the 64-bit
 * TSS responsible for both 64-bit-mode programs
 * and compatibility-mode programs.
 * 
 * Task-state segment descriptor
 */
struct tss_dsc
{
	UINT16 seg_limit_0_15;
	UINT16 base_0_15;
	UINT8  base_16_23;
	UINT8  type:4,
	       _reserved_2:1,
	       dpl:2,
	       p:1;
	UINT8  seg_limit_16_19:4,
	       avl:1,
	       _reserved_3:2,
	       g:1;
	UINT8  base_24_31:
	UINT32 base_32_63;
	UINT32 _reserved_4:8,
	       _reserved_5:5,
	       _reserved_6:19;
};
/**
 * Task-state format
 */
struct tss
{
	UINT32 _reserved_1;
	UINT32 RPS0_lower;
	UINT32 RSP0_upper;
	UINT32 RSP1_lower;
	UINT32 RSP1_upper;
	UINT32 RSP2_lower;
	UINT32 RSP2_upper;
	UINT32 _reserved_2;
	UINT32 _reserved_3;
	UINT32 IST1_lower;
	UINT32 IST1_upper;
	UINT32 IST2_lower;
	UINT32 IST2_upper;
	UINT32 IST3_lower;
	UINT32 IST3_upper;
	UINT32 IST4_lower;
	UINT32 IST4_upper;
	UINT32 IST5_lower;
	UINT32 IST5_upper;
	UINT32 IST6_lower;
	UINT32 IST6_upper;
	UINT32 IST7_lower;
	UINT32 IST7_upper;
	UINT32 _reserved_4;
	UINT32 _reserved_5;
	UINT16 _reserved_6;
	UINT16 IO_base;
}
#endif
