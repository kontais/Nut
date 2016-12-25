#include <sched.h>
#include <proc.h>
#include <list.h>
#include <queue.h>

list_head_t thread_list;
list_head_t proc_list;

thread_t *current_thread;
proc_t *current_proc;

queue_t *ready_queue;

proc_t *get_current_proc(void)
{
	return current_proc;
}
thread_t *get_current_thread(void)
{
	return current_thread;
}
queue_t *get_ready_queue(void)
{
	return ready_queue;
}
void sched_init(void)
{
	current_proc = NULL;
	
	list_init(&thread_list);
	list_init(&proc_list);
	
	ready_queue = malloc(sizeof(queue_t));
	queue_init(ready_queue);
	thread_t *initial_kernel_thread = malloc(sizeof(thread_t));
	
	current_thread = initial_kernel_thread;
	list_add_before(&thread_list, &initial_kernel_thread->list);
	initial_kernel_thread->proc = NULL;
	initial_kernel_thread->status = 0;
	memset(&initial_kernel_thread->tcb, 0, sizeof(tcb_t));
	
	queue_enqueue(ready_queue, initial_kernel_thread);
	
	save_context = &initial_kernel_thread->tcb.context;
	
	printf("Scheduler initializing complete.\n");
}
/**
 * This function is called after context is saved,
 * then we can schedule.
 */
void sched(void)
{
// 	printf("\n");
// 	printf("%lx\n", th1->tcb.RIP);
// 	printf("Schedule.\n");
	
	thread_t *load_thread = queue_dequeue(ready_queue);
	
	load_context = &load_thread->tcb.context;
	save_context = &load_thread->tcb.context;
	
	queue_enqueue(ready_queue, load_thread);
	
	current_thread = load_thread;
	current_proc = load_thread->proc;
	if (current_proc != NULL)
		vm_map_do_mapping(current_proc->vm_map);
	
// 	if (current_thread == th2)
// 	{
// 		current_thread = th3;
// 		current_context = &th3->tcb.context;
// 	}
// 	else
// 	{
// 		current_thread = th2;
// 		current_context = &th2->tcb.context;
// 	}
// 	if (list_empty(&thread_list))
// 	{
// 		current_thread = NULL;
// 		current_proc = NULL;
// 	}
// 	else
// 	{
// 		current_thread = list_entry(current_thread->list.next, struct thread, list);
// 		current_proc = current_thread->proc;
// 	}
}
