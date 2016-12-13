#include "proc.h"
#include <list.h>

struct list_head proc_queue;

/**
 * This function is called after context is saved,
 * then we can schedule.
 */
void shed_init(void)
{
	list_init(&proc_queue);
	struct proc
}
void sched(void)
{
	
	
}
