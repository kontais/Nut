#include <klibc.h>

int sys_exec(struct proc *proc, const char *path, char *const argv[], char *const envp[])
{
	
	destroy_threads(&proc->threads);
	vm_unmap(&proc->vm);
	
	args_save(&proc->args, argv);
	envs_save(&proc->envs, envp);
	
	vm_map(&proc->vm);
	file_load(path, &proc->vm);
	thread_add(&proc->threads);
	
	shed_ready_queue_add(proc);
	return 0;
}
