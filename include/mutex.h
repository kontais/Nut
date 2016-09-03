#ifndef _MUTEX_H_
#define _MUTEX_H_
#include <types.h>
struct mutex
{
	/*-1:unlocked,0:locked,positive:locked,waiters*/
	atomic_t 		status;
	spinlock_t 		wait_lock;
	struct list_head	 wait_list;
};

struct wait_list
{
	struct list_head	list;
	struct thread		*task;
}
void might_sleep(void)
{
	if (atomic_read(&lock->status) != -1)
	{
		
		sched();
	}
	
}
/**
 * Init mutex
 */
static inline void mutex_init(struct mutex *lock)
{
	atomic_set(&lock->status, -1);
	spinlock_init(&lock->wait_lock);
	list_init(&lock->wait_list);
}
/**
 * Lock mutex.If it's locked already,then blocks
 * until it's unlocked and lock.
 */
static inline void mutex_lock(struct mutex *lock)
{
	might_sleep();
	atomic_set(&lock->status, 0);
}
/**
 * Test whether mutex is locked.
 */
static inline int mutex_trylock(struct mutex *lock)
{
	return atomic_read(&lock->status) == 0;
}
/**
 * Unlock mutex.If it's not locked,do nothing.
 */
static inline void mutex_unlock(struct mutex *lock)
{
	atomic_set(&lock->status, atomic_read(&lock->status)-1);
}
#endif
