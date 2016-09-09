#ifndef _CPU_H_
#define _CPU_H_

/**
 * This structure holds all the information about a logical CPU core.
 */
struct CPU
{
	UINT ID;
	struct thread *running;
	struct list thread_queue;
	UINT thread_queue_length;
	struct gdt *gdt;
	struct idt *idt;
	struct tss *tss;
	struct ldt *ltd;

};


#endif
