#ifndef _PROC_H_
#define _PROC_H_

#include "tcb.h"
#include <ktypes.h>
/*
 * Kernel runnable context (thread).
 * This is what is put to sleep and reactivated.
 * Thread context.  Processes may have multiple threads.
 */
struct thread
{
	id_t			id;	//Thread ID
	long			status;	//Thread status:-1 stopped 0 pending 1 runnable
	struct list_head	list;	//List of all threads
	struct mutex		mutex;	//Thread struct lock

	struct tcb		tcb;	//Thread control blocks(machine-dependent)
};
/*
 * pargs, used to hold a copy of the command line, if it had a sane length.
 */
struct args 
{
	uint	ar_ref;		/* Reference count. */
	uint	ar_length;	/* Length. */
	uchar	*ar_args;	/* Arguments. */
};
/*
 * Process structure.
 */
struct proc
{
	id_t			id;	//Process ID
	struct list_head	list;	//List of all processes
	struct list_head	threads;//Thread list entry
	struct mutex		mutex;	//Process struct lock

	struct proc		*parent;//Parent Process
	struct list_head	*child;	//Child Process list entry

	nice_t	 		nice;	//Nice of the process
	struct pargs		args;	//Arguments from command line
	char			*pwd;	//Current working directory
};
/*
 * Process groups may have a or more processes.
 * Each process associates with a process groups.
 */
struct pgrp
{
	id_t			id;	//Group ID
	struct list_head	list;	//List of all process groups
	struct list_head	procs;	//Process struct entry

};
/*
 * Session consists of a set of process groups,
 * associating with a user and maybe a terminal device.
 */
struct session
{
	id_t			id;	//Session ID
	struct list_head	list;	//List of all sessions
	struct list_head	grps;	//Group struct entry

};

struct namespace
{
	id_t			id;	//Namespace ID
	struct list_head	list;	//List of all namespaces

};

static inline struct proc *current_thread(void)
{
	__asm__("
}
#endif
