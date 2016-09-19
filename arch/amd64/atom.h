#ifndef _ATOM_H_
#define _ATOM_H_

#include <tyoes.h>
static inline void atomic_set(atomic_t *val, atomic_t new_val)
{
	asm volatile (
		"mov %1, %%rax\n\t"
		"mov %0, %%rdx\n\t"
		"mov %%rax, (%%rdx)\n\t"
		:
		:"m"(val), "m"(new_val)
	    );
}
static inline atomic_t atomic_set(atomic_t *val, atomic_t new_val)
{
	asm volatile (
		"mov %1, %%rax\n\t"
		"mov %0, %%rdx\n\t"
		"mov %%rax, (%%rdx)\n\t"
		:
		:"m"(val), "m"(new_val)
	    );
}
#endif
