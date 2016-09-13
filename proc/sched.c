#include "proc.h"

struct run_queue
{
	list_head queue;
	struct thread *thread;
}*running;

void get_current_thread_pcb(void)
{
	//Save old thread's pcb into %rax register.
	asm (
		"mov %0, %%rax"
		:
		: "m"(current->thread->pcb)
		:
	);
}
/**
 * This function is called after context is saved,
 * then we can schedule.
 */
void sched(void)
{
	current = current->queue->next;
	

	//Save new thread's pcb into %rax register.
	asm (
		"mov %0, %%rax"
		:
		: "m"(current->thread->pcb)
		:
	);
	
}
