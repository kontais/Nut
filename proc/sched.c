#include <sched.h>
#include <proc.h>
#include <list.h>
#include <queue.h>
#include <mm.h>
#include <paging.h>
list_head_t thread_list;
list_head_t proc_list;

volatile thread_t *current_thread;
volatile proc_t *current_proc;

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
	initial_kernel_thread->tid = tid_alloc();
	list_add_before(&thread_list, &initial_kernel_thread->list);
	initial_kernel_thread->proc = NULL;
	initial_kernel_thread->status = 0;
	memset(&initial_kernel_thread->tcb, 0, sizeof(tcb_t));
	
	queue_enqueue(ready_queue, initial_kernel_thread);
	
	save_context = &initial_kernel_thread->tcb.context;
	load_context = &initial_kernel_thread->tcb.context;
	
	printf("Scheduler initializing complete.\n");
}
void __sched(void)
{
	static uint8_t count = 0;
	if (count ++ % 10 != 0)
		return;
	sched();
}
/**
 * This function is called after context is saved,
 * then we can schedule.
 */
void sched(void)
{
	printf("Sched\n");
// 	printf("%lx\n", th1->tcb.RIP);
// 	printf("Schedule.\n");
	
	thread_t *load_thread;
	do
	{
		load_thread = queue_dequeue(ready_queue);
		assert(load_thread != NULL);
		if (load_thread->status == -1)
			printf("Delete one thread in ready queue\n");
		printf("%ld ", load_thread->tid);
		
	}while(load_thread->status == -1);
	
	load_context = &load_thread->tcb.context;
	save_context = &load_thread->tcb.context;
	
	queue_enqueue(ready_queue, load_thread);
// 	printf("Mapping\n");
	current_thread = load_thread;
	current_proc = load_thread->proc;
	if (current_proc != NULL)
	{
		printf("Changed mapping\n");
		vm_map_do_mapping(current_proc->vm_map);
	}
// 	int ret = modify_chunk_mapping(get_current_plm4e(), 0x0, 0x1F80000, 1, DEFAULT_USER_TEXT_PTE_FLAGS);
// 	printf("%d\n", ret);
	printf("%lx\n", *(uint64_t*)0x0);
	printf("%lx\n", *(uint64_t*)(0x1F80000 + PHY_MAP_BASE));
// 	printf("Mapping done\n");
}
