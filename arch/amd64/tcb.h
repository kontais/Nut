#ifndef _MACHINE_TCB_H_
#define _MACHINE_TCB_H_
#include <ktypes.h>
/**
 * Thread control blocks definitions,
 * including registers and 
 */
struct tcb
{
/**
 * General-perpose registers
 * Special uses:
 * RAX:Accumulator for operands and results data
 * RCX:Counter for string and loop operations
 * RDX:I/O pointer
 * RBX:Pointer to data in the DS segment
 * RBP:Pointer to data on the stack(in the SS segment)
 * RSP:Stack pointer(in the SS segment)
 * RSI:Pointer to data in the segment pointed to by the DS register;
 *     source pointer for string operations
 * RDI:Pointer to data(or destination)in the segment pointed by the ES register;
 *     destination pointer for string operations
 * 
 */
	uint64_t RAX;
	uint64_t RCX;
	uint64_t RDX;
	uint64_t RBX;
	uint64_t RBP;
	uint64_t RSP;
	uint64_t RSI;
	uint64_t RDI;
//New general-perpose registers(GPRs)
	uint64_t R8;
	uint64_t R9;
	uint64_t R10;
	uint64_t R11;
	uint64_t R12;
	uint64_t R13;
	uint64_t R14;
	uint64_t R15;
//Segment registers
//	uint64_t CS;//CS,DS,ES,SS are treated as if each
//	uint64_t DS;//segment base is 0 in 64-bit mode.
//	uint64_t ES;//FS,GS may be used as additional base
//	uint64_t SS;//registers in linear address calculations.
	uint64_t FS;
	uint64_t GS;
//Flags and Status register
	uint64_t RFLAGS;
//Instruction Pointer register
	uint64_t RIP;//RIP in the program counter(PC)

//FPU registers
//TODO: add all the registers!
}
#endif
