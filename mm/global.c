#include "global.h"
#include <mm.h>
#include <types.h>
#include <klibc.h>
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
struct gvt
{
	size_t gthreadtablesize;
	size_t gproctablesize;
	size_t gpgrptablesize;
	size_t gsessiontablesize;
	size_t gzonetablesize;
	
	struct thread *gthreadtable;
	struct proc *gproctable;
	struct pgrp *gpgrptable;
	struct session *gsessiontable;
	struct zone *gzonetable;
	
	struct mutex *gthreadtablemutex;
	struct mutex *gproctablemutex;
	struct mutex *gpgrptablemutex;
	struct mutex *gsessiontablemutex;
	struct mutex *gzonetablemutex;

	struct CPU *gCPUTables;
	size_t gCPUTableSize;
}*gvt;

void global_init(void)
{
	gvt = kmalloc(sizeof(struct gvt));
	gvt->gthreadtablesize = default_gthreadtablesize;
	gvt->gproctablesize = default_gproctablesize;
	gvt->gpgrptablesize = default_gpgrptablesize;
	gvt->gsessiontablesize = default_gsessiontablesize;
	gvt->gzonetablesize = default_gzonetablesize;
	
	gvt->gthreadtable = kmalloc(sizeof(struct thread*) * gvt->gthreadtablesize);
	gvt->gproctable = kmalloc(sizeof(struct proc*) * gvt->gproctablesize);
	gvt->gpgrptable = kmalloc(sizeof(struct pgrp*) * gvt->gpgrptablesize);
	gvt->gsessiontable = kmalloc(sizeof(struct session*) * gvt->gsessiontablesize);
	gvt->gzonetable = kmalloc(sizeof(struct namespace*) * gvt->gzonetablesize);
	
	kmemset(gvt->gthreadtable, NULL, gvt->gthreadtablesize);
	kmemset(gvt->gproctable, NULL, gvt->gproctablesize);
	kmemset(gvt->gpgrptable, NULL, gvt->gpgrptablesize);
	kmemset(gvt->gsessiontable, NULL, gvt->gsessiontablesize);
	kmemset(gvt->gzonetable, NULL, gvt->gzonetablesize);
}
// struct CPU *get_urrent_CPU(void)
// {
// 	uint64_t ID = get_CPU_ID();
// 	uint64_t index;
// 	for (index = 0; index < gvt->gCPUTableSize; index ++)
// 	{
// 		if ((gvt->gCPUtables + index)->ID == ID)
// 			break;
// 	}
// 	if (index == gvt->gCPUTableSize)
// 		return NULL;
// 	else
// 		return *(gvt->gCPUtables + index);
// }
// 
// struct proc *get_current_thread(void)
// {
// 	return get_current_CPU()->thread->running;
// }
