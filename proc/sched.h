#ifndef _SCHED_H_
#define _SCHED_H_

#include <klibc.h>
#include <proc.h>

#include <queue.h>

proc_t *get_current_proc(void);
thread_t *get_current_thread(void);
queue_t *get_ready_queue(void);
#endif

