#include <sched.h>
#include <proc.h>
#include <list.h>


list_head_t thread_list;
list_head_t proc_list;


thread_t *current_thread;
proc_t *current_proc;


thread_t *th1,*th2,*th3;

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
	
	current_thread = NULL;
	current_proc = NULL;
	
	list_init(&thread_list);
	list_init(&proc_list);
	
	th1 =  malloc(sizeof(thread_t));
	th2 =  malloc(sizeof(thread_t));
	th3 =  malloc(sizeof(thread_t));
	current_thread = th1;
	current_context = &th1->tcb.context;
// 	current_thread = malloc(sizeof(thread_t));
	void *stack1 = malloc(4096);
	void *stack2 = malloc(4096);
	void thread1(void);
	thread_init(th2, NULL, &thread1, stack1+4096);
	void thread2(void);
	thread_init(th3, NULL, &thread2, stack2+4096);
	
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
