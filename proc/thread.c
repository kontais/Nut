#include <proc.h>
#include <cpu_intrins.h>
#include <klibc.h>
//Simple functions to manipulate PID and TID
uint8_t *pid_table;
uint8_t *tid_table;

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


int proc_init(void)
{
	pid_table = malloc(PID_TABLE_SIZE);
	memset(pid_table, 0, PID_TABLE_SIZE);
	tid_table = malloc(TID_TABLE_SIZE);
	memset(tid_table, 0, TID_TABLE_SIZE);
	
	sched_init();
}

int thread_init(thread_t *thread, proc_t *proc, uint64_t entrypoint, uint64_t stack_top)
{
	memset(thread, 0, sizeof(thread_t));
	
	thread->id = tid_alloc();
	thread->status = 0;
	list_init(&thread->list);
	thread->proc = proc;
	memset(&thread->tcb, 0, sizeof(tcb_t));
	thread->tcb.RIP = entrypoint;
	thread->tcb.RSP = stack_top;
	thread->tcb.SS = 0x8;
	thread->tcb.FS = 0x8;
	thread->tcb.GS = 0x8;
	thread->tcb.CS = proc == NULL ? 0x10 : 0x28;
// 	thread->tcb.RFLAGS = __read_rflags__();
	thread->tcb.RFLAGS = 1 << 9;
	return 0;
}
