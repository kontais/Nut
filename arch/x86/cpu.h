#ifndef _CPU_H_
#define _CPU_H_

static inline void __halt(void)
{
	asm ("hlt");
}

#endif
