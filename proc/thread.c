#include <proc.h>
#include <cpu_intrins.h>
#include <klibc.h>
#include <cpu_reg.h>


int thread_init(thread_t *thread, proc_t *proc, uint64_t entrypoint, uint64_t stack_top)
{
	memset(thread, 0, sizeof(thread_t));
	
	thread->id = tid_alloc();
	thread->status = 0;
	list_init(&thread->list);
	thread->proc = proc;
	memset(&thread->tcb.context, 0, sizeof(context_t));
	thread->tcb.context.RIP = entrypoint;
	thread->tcb.context.RSP = stack_top;
	thread->tcb.context.SS = 0x8;
	thread->tcb.context.FS = 0x8;
	thread->tcb.context.GS = 0x8;
	thread->tcb.context.CS = proc == NULL ? 0x10 : 0x28;
// 	thread->tcb.RFLAGS = __read_rflags__();
	thread->tcb.context.RFLAGS = REG_FLAGS_IF_MASK;
	
	if (proc != NULL)
	{
		list_add_before(&proc->threads, &thread->list);
	}
	return 0;
}

void thread_destroy(thread_t *thread, proc_t *proc)
{
	tid_free(thread->id);
	if (proc != NULL)
	{
		list_del(&thread->list);
	}
}
