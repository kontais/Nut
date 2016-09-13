#include "global.h"

#ifndef default_gthreadtablesize
	#define default_gthreadtablesize  1024
#endif
#ifndef default_gproctablesize
	#define default_gproctablesize  1024
#endif
#ifndef default_gpgrptablesize
	#define default_gpgrptablesize  1024
#endif
#ifndef default_gsessiontablesize
	#define default_gsessiontablesize  1024
#endif
#ifndef default_gzonetablesize
	#define default_gzonetablesize  1024
#endif
//Global variable table,order critical.
struct gVT
{
	size_t gThreadsTableSize;
	size_t gProcTableSize;
	size_t gPgrpTableSize;
	size_t gSessionTableSize;
	size_t gZoneTableSize;
	
	struct thread *gThreadTable;
	struct proc *gProcTable;
	struct pgrp *gPgrpTable;
	struct session *gSessionTable;
	struct zone *gZoneTable;
	
	struct mutex *gthreadtablemutex;
	struct mutex *gproctablemutex;
	struct mutex *gpgrptablemutex;
	struct mutex *gsessiontablemutex;
	struct mutex *gzonetablemutex;

	struct CPU *gCPUTables;
	size_t CPU gCPUTableSize;
}*gvt;

void global_init(void)
{
	gVT = kmalloc(sizeof(struct gVT));
	gVT->gthreadtablesize = default_gthreadtablesize;
	gVT->gproctablesize = default_gproctablesize;
	gVT->gpgrptablesize = default_gpgrptablesize;
	gVT->gsessiontablesize = default_gsessiontablesize;
	gVT->gnamespacetablesize = default_gnamespacetablesize;
	
	gVT->gThreadTable = kmalloc(sizeof(struct thread*) * gthreadtablesize);
	gVT->gProcTable = kmalloc(sizeof(struct proc*) * gproctablesize);
	gVT->gPgrpTable = kmalloc(sizeof(struct pgrp*) * gpgrptablesize);
	gVT->gSessionTable = kmalloc(sizeof(struct session*) * gsessiontablesize);
	gVT->gZoneTable = kmalloc(sizeof(struct namespace*) * gzonetablesize);
	
	kmemset(gVT->gThreadTable, NULL, gVT->gthreadtablesize);
	kmemset(gVT->gProcTable, NULL, gVT->gproctablesize);
	kmemset(gVT->gPgrpTable, NULL, gVT->gpgrptablesize);
	kmemset(gVT->gSessionTable, NULL, gVT->gsessiontablesize);
	kmemset(gVT->gZoneTable, NULL, gVT->gzonetablesize);z
}
struct CPU *get_urrent_CPU(void)
{
	UINT ID = get_CPU_ID(void);
	UINT index;
	for (index = 0; index < gVT->gCPUTableSize; index ++)
	{
		if ((gVT->gCPUtables + index)->ID == ID)
			break;
	}
	if (index == gVT->gCPUTableSize)
		return NULL;
	else
		return *(gVT->gCPUtables + index);
}

struct proc *get_current_thread(void)
{
	return get_current_CPU()->thread->running;
}
