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
	struct list_head	t_list;	//List of all threads
	struct mutex		t_mutex;//Thread struct lock
	id_t			t_tid;	//Thread ID
	
	struct tcb		*t_tcb;	//Thread control blocks(machine-dependent)
};
/*
 * pargs, used to hold a copy of the command line, if it had a sane length.
 */
struct pargs 
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
	struct list_head	p_plist;	//List of all processes
	struct list_head	p_threads;	//Thread list entry
	struct mutex		p_mutex;	//Process struct lock
	id_t			p_pid;		//Process ID
	id_t			p_uid;		//User ID
	struct list_head	p_parent;	//Parent Process
	struct list_head	p_child;	//Child Process list entry
	
	nice_t	 		p_nice;		//Nice of the process
	struct pargs		p_args;		//Arguments from command line
	char			*p_wd;		//Current working directory
};
/*
 * Process groups may have a or more processes.
 * Each process associates with a process groups.
 */
struct pgrp
{
	struct list_head	g_glist;	//List of all process groups
	struct list_head	g_procs;	//Process struct entry
	id_t			g_gid;		//Group ID
	id_t			g_uid;		//User ID
};
/*
 * Session consists of a set of process groups,
 * associating with a user and maybe a terminal device.
 */
struct session
{
	struct list_head	s_slist;	//List of all sessions
	struct list_head	s_pgrps;	//Group struct entry
	id_t			s_sid;		//Session ID
	id_t			s_uid;		//User ID
};

struct namespace
{
	struct list_head	n_nlist;	//List of all namespaces
	id_t			n_nid;		//Namespace ID
	id_t			n_uid;		//User ID
};

static inline struct proc *current_thread(void)
{
	__asm__("
}
#endif
