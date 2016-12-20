#include <proc.h>
#include <tcb.h>
#include <list.h>

list_head_t thread_list;
list_head_t proc_list;

thread_t *current_thread;
proc_t *current_proc;

thread_t *th1,*th2,*th3;
/**
 * This function is called after context is saved,
 * then we can schedule.
 */

void context_save(uint64_t *stack_top)
{
	int regnum = sizeof(tcb_t) >> 3;
	uint64_t *save_location = (uint64_t *)&current_thread->tcb;
	for (int i = 0; i < regnum; i ++)
		*save_location++ = *stack_top++;
}
void context_load(uint64_t *stack_top)
{
	int regnum = sizeof(tcb_t) >> 3;
	uint64_t *save_location = (uint64_t *)&current_thread->tcb;
	for (int i = 0; i < regnum; i ++)
		 *stack_top++ = *save_location++;
}
void sched_init(void)
{
	current_thread = NULL;
	current_proc = NULL;
	
	list_init(&thread_list);
	list_init(&proc_list);
	
	th1 =  malloc(sizeof(thread_t));
	th2 =  malloc(sizeof(thread_t));
	th3 =  malloc(sizeof(thread_t));
	current_thread = th1;
// 	current_thread = malloc(sizeof(thread_t));
	void *stack1 = malloc(4096);
	void *stack2 = malloc(4096);
	void thread1(void);
	thread_init(th2, NULL, &thread1, stack1+4096);
	void thread2(void);
	thread_init(th3, NULL, &thread2, stack2+4096);
	
// 	int regnum = sizeof(tcb_t) >> 3;
// 	uint64_t *save_location = (uint64_t *)&th2->tcb;
// 	for (int i = 0; i < regnum; i ++)
// 		printf("%lx\n", *save_location++);
}
void sched(void)
{
// 	int regnum = sizeof(tcb_t) >> 3;
// 	uint64_t *save_location = (uint64_t *)&current_thread->tcb;
// 	for (int i = 0; i < regnum; i ++)
// 		printf("%lx\n", *save_location++);
// 	printf("\n");
// 	printf("%lx\n", th1->tcb.RIP);
// 	printf("Schedule.\n");
	if (current_thread == th2)
		current_thread = th3;
	else
		current_thread = th2;
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
