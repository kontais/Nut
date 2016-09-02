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
extern struct namespace *gNamespaceTable;
extern size_t gNamespaceTableSize;


#endif
