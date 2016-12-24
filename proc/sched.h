#ifndef _SCHED_H_
#define _SCHED_H_

#include <klibc.h>
#include <proc.h>


proc_t *get_current_proc(void);
thread_t *get_current_thread(void);

#endif

