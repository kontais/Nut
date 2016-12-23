#include <proc.h>
#include <list.h>
#include <sched.h>

int proc_init(proc_t *proc, proc_t *parent, pargs_t *args, penvs_t *envs, vm_map_t *vm_map)
{
	proc->id = pid_alloc();
	list_init(&proc->list);
	list_init(&proc->threads);
	list_init(&proc->child);
	proc->parent = parent;
	proc->nice = 0;
	proc->args = args;
	proc->envs = envs;
	proc->vm_map = vm_map;
	if (parent != NULL)
	{
		memcpy(proc->fd_table, parent->fd_table, FD_TABLE_SIZE * sizeof(void *));
		list_add_before(&parent->child, &proc->list);
	}
	else
	{
		memset(proc->fd_table, 0, FD_TABLE_SIZE * sizeof(void *));
	}
}
void proc_destroy(proc_t *proc)
{
	assert(proc->parent != NULL);
	pid_free(proc->id);
	
	list_head_t *it;
	if (!list_empty(&proc->child))
	{
		list_for_each(it, &proc->child)
		{
			proc_t *child_proc = list_entry(it, proc_t, list);
			child_proc->parent = proc->parent;
			list_del(&child_proc->list);
			list_add_before(&proc->parent->child, &child_proc->list);
			
		}
	}
}
