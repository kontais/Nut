#ifndef _PROC_H_
#define _PROC_H_
struct namespace
{
	
	
}
/*
 * Session consists of a set of process groups,
 * associating with a user and maybe a terminal device.
 */
struct session
{
	
	
}
/*
 * Process groups may have a or more processes.
 * Each process associates with a process groups.
 */
struct pgrp
{
	
}
/*
 * Process structure.
 */
struct proc
{
	struct mtx	p_mtx;	//Process struct lock
	pid_t		pid;	//Process ID
	
	
	
	
}
/*
 * Kernel runnable context (thread).
 * This is what is put to sleep and reactivated.
 * Thread context.  Processes may have multiple threads.
 */
struct thread
{
	struct mtx	t_mtx;	//Thread struct lock
	tid_t		tid;	//Thread ID
	
}
/*
 * pargs, used to hold a copy of the command line, if it had a sane length.
 */
struct pargs {
	uint	ar_ref;		/* Reference count. */
	uint	ar_length;	/* Length. */
	uchar	*ar_args;	/* Arguments. */
};
#endif
