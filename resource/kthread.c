#include <proc.h>
#include <klibc.h>
#include <list.h>

/**
 * Allocate and init a thread
 * @ptr pointer to specific struct
 * @mask indicating type of the struct
 * @return allocated id or -1 on error
 */

struct thread* kthreadalloc(void *entry, struct args *arg, void *stack, long status)
{
	struct thread *thread = kmalloc(sizeof(struct thread));
	kmemset(thread, 0, sizeof(struct thread));
	
	//Register the thread
	id_t tid = kidalloc(thread, KRSALLOC_TID);
	
	//Init
	list_init(&thread->list);
	mutex_init(&thread->mutex);
	
	
	
	return thread;
}

