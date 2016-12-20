#ifndef _PROC_H_
#define _PROC_H_

#include <tcb.h>
#include <ktypes.h>
// #include <mutex.h>
#include <fs.h>
#include <vm.h>
typedef struct pargs
{
	int argc;
	char *argv[];
}pargs_t;
typedef struct penvs
{
	char *pwd;
}penvs_t;
/*
 * Kernel runnable context (thread).
 * This is what is put to sleep and reactivated.
 * Thread context.  Processes may have multiple threads.
 */
typedef struct thread
{
	id_t			id;	//Thread ID
	long			status;	//Thread status:-1 stopped 0 pending 1 runnable
	struct list_head	list;	//List of all threads
	struct proc		*proc;	//Process it belongs to
// 	struct mutex		mutex;	//Thread struct lock

	tcb_t			tcb;	//Thread control blocks(machine-dependent)
	size_t 			stack_size;//Size of the stack
	uint64_t		entry_point;//Entry point of the thread
}thread_t;

/*
 * Process structure.
 */

typedef struct proc
{
	id_t			id;	//Process ID
	struct list_head	list;	//List of all processes
	struct list_head	threads;//Thread list entry
// 	struct mutex		mutex;	//Process struct lock

	struct proc		*parent;//Parent Process
	struct list_head	*child;	//Child Process list entry

	nice_t	 		nice;	//Nice of the process
	pargs_t			args;	//Arguments from command line
	penvs_t			envs;	//Current working directory

	vm_map_t		vm;	//Virtual memory map
	
	fd_t			fd_table[512];//File descriptor table
}proc_t;
// /*
//  * Process groups may have a or more processes.
//  * Each process associates with a process groups.
//  */
// struct pgrp
// {
// 	id_t			id;	//Group ID
// 	struct list_head	list;	//List of all process groups
// 	struct list_head	procs;	//Process struct entry
// 
// };
// /*
//  * Session consists of a set of process groups,
//  * associating with a user and maybe a terminal device.
//  */
// struct session
// {
// 	id_t			id;	//Session ID
// 	struct list_head	list;	//List of all sessions
// 	struct list_head	grps;	//Group struct entry
// 
// };
// 
// struct zone
// {
// 	id_t			id;	//Zone
// 	struct list_head	list;	//List of all namespaces
// 
// };

#define MAX_PID		256
#define PID_TABLE_SIZE	(MAX_PID * sizeof(uint8_t))

#define MAX_TID		1024
#define TID_TABLE_SIZE	(MAX_TID * sizeof(uint8_t))
#endif
