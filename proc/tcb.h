#ifndef _TCB_H_
#define _TCB_H_
/**
 * Thread control block(TCB) definitions.
 * This is machine-dependent.
 */
#ifdef AMD64
#include <arch/amd64/tcb.h>
#else ifdef ARM
#include <arch/arm/tcb.h>
#endif

#endif
