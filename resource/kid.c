#include <global.h>
//The offset in the GVT
#define KRS_TID 0x00
#define KRS_PID 0x01
#define KRS_GID 0x02
#define KRS_SID 0x03
#define KRS_NID 0x04

/**
 * Allocate and register an ID for a specific struct.
 * @ptr pointer to specific struct
 * @mask indicating type of the struct
 * @return allocated id or -1 on error
 */
id_t kidalloc(void *ptr, uint8_t mask)
{
	long alloc_id = -1;
	long *start = (long *)*((void *)&gVT->gThreadTable + mask);
	size_t size = *((size_t *)&(gVT->gThreadTableSize) + mask);
	mutex_lock((struct mutex *)((void *)gVT->gthreadtablemutex + mask));
	for (long i = 0; i < size; ++ i)
	{
		if (*(start + i) == NULL)
		{
			*(start + i) = ptr;
			alloc_id = i;
			break;
		}
	}
	mutex_unlock((struct mutex *)((void *)gVT->gthreadtablemutex + mask));
	return alloc_id;
}

/**
 * Free an ID
 * @id id to be freed
 */
void kidfree(id_t id, uint8_t mask)
{
	void *start = *((void *)&gVT->gThreadTable + mask);
	size_t size = *((size_t *)&(gVT->gThreadTableSize) + mask);
	mutex_lock((struct mutex *)((void *)gVT->gthreadtablemutex + mask));
	if ( id < size )
	{
		*(start + id) = NULL;
	}
	mutex_unlock((struct mutex *)((void *)gVT->gthreadtablemutex + mask));
}
