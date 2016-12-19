#include <klibc.h>
int sys_exec(struct proc *proc, const char *path, char *const argv[], char *const envp[])
{
	init proc struct;
	alloc page;
	load file;
	map region;
	insert into proc queue;
	ret;
	
	
	
}
