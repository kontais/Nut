#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include <types.h>
extern struct thread *gThreadTable;
extern size_t gThreadTableSize;
extern struct proc *gProcTable;
extern size_t gProcTableSize;
extern struct pgrp *gPgrpTable;
extern size_t gPgrpTableSize;
extern struct session *gSessionTable;
extern size_t gSessionTableSize;
extern struct zone *gZoneTable;
extern size_t gZoneTableSize;

/**
 * These data are thread specific,which means
 * they varies when accessed from different threads.
 */

/**
 * current_thread:return pointer to current thread structure
 * type:struct thread *
 */
#define current_thread __asm__("mo":"")


#endif
