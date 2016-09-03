#include <proc.h>
#include <klibc.h>
void dup_thread(struct thread *thread)
{
	//Request a mutex on the thread context
	mutex_lock(thread->t_mutex);
	//First duplicate the thread context
	struct thread *new_thread = kmalloc(sizeof(struct thread));
	if (new_thread == NULL)
		kpanic("Out of memory.");
	kmemcpy(new_thread, thread, sizeof(struct thread));
	
	//Modify necessary information
	thread->tid = alloc(TID);
	//Then mark the address space Copy-on-wirte
	
	
	//Release the mutex
	mutex_unlock(thread->t_mutex);
}
