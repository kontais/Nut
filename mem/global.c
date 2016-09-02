#include "global.h"

struct thread *gThreadTable = NULL;
size_t gThreadTableSize = 0;
struct proc *gProcTable = NULL;
size_t gProcTableSize = 0;
struct pgrp *gPgrpTable = NULL;
size_t gPgrpTableSize = 0;
struct session *gSessionTable = NULL;
size_t gSessionTableSize = 0;
struct namespace *gNamespaceTable = NULL;
size_t gNamespaceTableSize = 0;

void global_init(void)
{
	gThreadTable = kmalloc(sizeof(struct thread*) * gThreadTableSize);
	if (gThreadTable == NULL)
		kpanic("Cannot alloc ThreadTable!");
	gProcTable = kmalloc(sizeof(struct proc*) * gProcTableSize);
	if (gProcTable == NULL)
		kpanic("Cannot alloc ProcTable!");
	gPgrpTable = kmalloc(sizeof(struct pgrp*) * gPgrpTableSize);
	if (gPgrpTable == NULL)
		kpanic("Cannot alloc PgrpTable!");
	gSessionTable = kmalloc(sizeof(struct session*) * gSessionTableSize);
	if (gSessionTable == NULL)
		kpanic("Cannot alloc SessionTable!");
	gNamespaceTable = kmalloc(sizeof(struct namespace*) * gNamespaceTableSize);
	if (gNamespaceTable == NULL)
		kpanic("Cannot alloc NamespaceTable!");
}
