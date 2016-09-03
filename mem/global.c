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
#ifndef default_gnamespacetablesize
	#define default_gnamespacetablesize  1024
#endif
//Global variable table,order critical.
struct gvt
{
	size_t gthreadsablesize;
	size_t gprocpablesize;
	size_t gpgrptablesize;
	size_t gsessiontablesize;
	size_t gnamespacetablesize;
	
	struct thread *gthreadtable;
	struct proc *gproctable;
	struct pgrp *gpgrptable;
	struct session *gsessiontable;
	struct namespace *gnamespacetable;
	
	struct mutex *gthreadtablemutex;
	struct mutex *gproctablemutex;
	struct mutex *gpgrptablemutex;
	struct mutex *gsessiontablemutex;
	struct mutex *gnamespacetablemutex;
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
	gVT->gNamespaceTable = kmalloc(sizeof(struct namespace*) * gnamespacetablesize);
	
	kmemset(gVT->gThreadTable, NULL, gVT->gthreadtablesize);
	kmemset(gVT->gProcTable, NULL, gVT->gproctablesize);
	kmemset(gVT->gPgrpTable, NULL, gVT->gpgrptablesize);
	kmemset(gVT->gSessionTable, NULL, gVT->gsessiontablesize);
	kmemset(gVT->gNamespaceTable, NULL, gVT->gnamespacetablesize);
}
