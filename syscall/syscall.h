#ifndef _SYSCALL_H_
#define _SYSCALL_H_

#include <fs.h>
#include <sched.h>
#include <proc.h>

#define	SYS_syscall	0
#define	SYS_exit	1
#define	SYS_fork	2
#define	SYS_read	3
#define	SYS_write	4
#define	SYS_open	5
#define	SYS_close	6
#define	SYS_wait4	7

#define	SYS_pipe	42


void sys_syscall(void);
int sys_open(const char *path, int oflag);
ssize_t sys_write(int fd, const void *buf, size_t count);

#define SYS_CALL_TABLE_SIZE 1

#endif
