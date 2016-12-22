#include <sched.h>
#include <proc.h>
#include <list.h>
#include <queue.h>

list_head_t thread_list;
list_head_t proc_list;

thread_t *current_thread;
proc_t *current_proc;

queue_t *ready_queue;

uint8_t *pid_table;
uint8_t *tid_table;
//Simple functions to manipulate PID and TID
id_t pid_alloc(void)
{
	for (int i = 0; i < MAX_PID; i ++)
	{
		if(*(pid_table + i) == 0)
		{
			*(pid_table + i) = 1;
			return i;
		}
	}
	return -1;
}
void pid_free(id_t id)
{
	*(pid_table + id) = 0;
}
id_t tid_alloc(void)
{
	for (int i = 0; i < MAX_PID; i ++)
	{
		if(*(tid_table + i) == 0)
		{
			*(tid_table + i) = 1;
			return i;
		}
	}
	return -1;
}
void tid_free(id_t id)
{
	*(tid_table + id) = 0;
}
void id_table_init(void)
{
	pid_table = malloc(PID_TABLE_SIZE);
	memset(pid_table, 0, PID_TABLE_SIZE);
	tid_table = malloc(TID_TABLE_SIZE);
	memset(tid_table, 0, TID_TABLE_SIZE);
}

void sched_init(void)
{
	id_table_init();
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
}
/**
 * This function is called after context is saved,
 * then we can schedule.
 */
void sched(void)
{
// 	printf("\n");
// 	printf("%lx\n", th1->tcb.RIP);
	printf("Schedule.\n");
	
	thread_t *load_thread = queue_dequeue(ready_queue);

	load_context = &load_thread->tcb.context;
	save_context = &load_thread->tcb.context;
	
	queue_enqueue(ready_queue, load_thread);
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
