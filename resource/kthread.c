#include <proc.h>
#include <klibc.h>
#include <list.h>

/**
 * Allocate and init a thread
 * @ptr pointer to specific struct
 * @mask indicating type of the struct
 * @return allocated id or -1 on error
 */

struct thread* kthreadalloc(void)
{
	struct thread *thread = kmalloc(sizeof(struct thread));
	kmemset(thread, 0, sizeof(struct thread));
	
	//Register the thread
	thread->id = kidalloc(thread, KRS_TID);
	
	//Init
	thread->status = status;
	list_init(&thread->list);
	mutex_init(&thread->mutex);
	
	return thread;
}

void kthreadfree(struct thread* thread)
{
	kidfree(thread->id, KRS_TID);
	kfree(thread);
}
