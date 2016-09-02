#ifndef _MACHINE_TCB_H_
#define _MACHINE_TCB_H_
#include <ktypes.h>
/**
 * Thread control blocks definitions,
 * including registers and 
 */
struct tcb
{
//General-perpose registers
	uint64_t RAX;
	uint64_t RBX;
	uint64_t RCX;
	uint64_t RDX;
	uint64_t RBP;
	uint64_t RSI;
	uint64_t RDI;
	uint64_t RSP;
//New general-perpose registers(GPRs)
	uint64_t R8D;
	uint64_t R9D;
	uint64_t R10D;
	uint64_t R11D;
	uint64_t R12D;
	uint64_t R13D;
	uint64_t R14D;
	uint64_t R15D;
//Segment registers
	uint64_t CS;//CS,DS,ES,SS are treated as if each
	uint64_t DS;//segment base is 0 in 64-bit mode.
	uint64_t ES;//FS,GS may be used as additional base
	uint64_t SS;//registers in linear address calculations.
	uint64_t FS;//SS is the stack pointer(SP)
	uint64_t GS;
//Flags and Status register
	uint64_t RFLAGS;
//Instruction Pointer register
	uint64_t RIP;//RIP in the program counter(PC)

//FPU registers
//TODO: add all the registers!
}
#endif
