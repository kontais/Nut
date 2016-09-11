#ifndef _SEGMENTS_H_
#define _SEGMENTS_H_

/**
 * Protected-Mode Memory Management register difinitions
 * The three tables consist of linear arrays of arbitrary combines of descriptors.
 * Segment selector is used as a pointer with implicit base address in the table register
 * to the descriptor in the corresponding table.
 */

/**
 * Global Descriptor Table Resgister
 */
struct gdt
{
	uint16_t limit;	//Limits all should be must be 8N-1
	uint64_t base;
};
/**
 * Local Descriptor Table Register
 */
struct ldt
{
	uint16_t limit;
	uint64_t base;
};
/**
 * Interrupt Description Table Register
 */
struct idt
{
	uint16_t limit;
	uint64_t base;
};
/**
 * Segment selector
 */
struct seg_sel
{
	uint16_t rpl:2,
	         ti:1,
	         index:13;
};
/**
 * Segment descriptor
 */
struct seg_dsc
{
	uint16_t seg_limit_0_15;
	uint16_t base_0_15;
	uint8_t  base_16_23:
	uint8_t  type:4,
	         s:1,
	         dpl:2,
	         p:1;
	uint8_t  seg_limit_16_19:4,
	         avl:1,
	         l:1,
	         d_b:1,
	         g:1;
	uint8_t  base_24_31;
};
/**
 * Call gate descriptor
 */
struct call_gate_dsc
{
	uint16_t offset_0_15;
	struct   seg_sel seg_sel;
	uint8_t  _reserved_1:8;
	uint8_t  type_1:4,
	         _reserved_2:1,
	         dpl:2,
	         p:1;
	uint16_t offset_16_31;
	uint32_t offset_32_63;
	uint32_t _reserved_3:8,
	         type_1:5,
	         _reserved_4:19;
};
/**
 * Interrupt/trap segment descriptor
 */
struct int_trap_seg_dsc
{
	uint16_t offset_0_15;
	struct   seg_sel seg_sel;
	uint16_t ist:4,
	         _reserved_1:5,
	         type:4,
	         _reserved_2:1,
	         dpl:2,
	         p:1;
	uint16_t offset_15_31;
	uint32_t offset_32_63;
	uint32_t _reserved_3;
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
	uint16_t seg_limit_0_15;
	uint16_t base_0_15;
	uint8_t  base_16_23;
	uint8_t  type:4,
	         _reserved_2:1,
	         dpl:2,
	         p:1;
	uint8_t  seg_limit_16_19:4,
	         avl:1,
	         _reserved_3:2,
	         g:1;
	uint8_t  base_24_31:
	uint32_t base_32_63;
	uint32_t _reserved_4:8,
	         _reserved_5:5,
	         _reserved_6:19;
};
/**
 * Task-state format
 */
struct tss
{
	uint32_t _reserved_1;
	uint32_t RPS0_lower;
	uint32_t RSP0_upper;
	uint32_t RSP1_lower;
	uint32_t RSP1_upper;
	uint32_t RSP2_lower;
	uint32_t RSP2_upper;
	uint32_t _reserved_2;
	uint32_t _reserved_3;
	uint32_t IST1_lower;
	uint32_t IST1_upper;
	uint32_t IST2_lower;
	uint32_t IST2_upper;
	uint32_t IST3_lower;
	uint32_t IST3_upper;
	uint32_t IST4_lower;
	uint32_t IST4_upper;
	uint32_t IST5_lower;
	uint32_t IST5_upper;
	uint32_t IST6_lower;
	uint32_t IST6_upper;
	uint32_t IST7_lower;
	uint32_t IST7_upper;
	uint32_t _reserved_4;
	uint32_t _reserved_5;
	uint16_t _reserved_6;
	uint16_t IO_base;
}
#endif
