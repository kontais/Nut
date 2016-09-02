#include <proc.h>

void dup_thread(struct thread *thread)
{
	//Request a mutex on the thread context
	
	//First duplicate the thread context
	struct thread *new_thread = kmalloc(sizeof(struct thread));
	kmemcpy(new_thread, thread, sizeof(struct thread));
	//Modify necessary information
	thread->tid = alloc
	//Then mark the address space Copy-on-wirte
	
	
	//Release the mutex
}
