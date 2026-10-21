#ifndef NOCTURNE_IOP_SEMA_H
#define NOCTURNE_IOP_SEMA_H
#include "iop_bind.h"
#include <stddef.h>
/* Original THREADMAN.irx guest layout; all addresses are 32-bit guest values. */
typedef struct NocturneIopSemaphore {
 uint32_t next,previous;uint16_t tag,id;
 uint32_t attr,waiter_count,wait_next,wait_previous,option;
 int32_t count,max_count;
} NocturneIopSemaphore;
_Static_assert(sizeof(NocturneIopSemaphore)==0x28u,"Original semaphore accessed prefix");
_Static_assert(offsetof(NocturneIopSemaphore,tag)==8,"Original tag");
_Static_assert(offsetof(NocturneIopSemaphore,waiter_count)==0x10,"Original waiter count");
_Static_assert(offsetof(NocturneIopSemaphore,wait_next)==0x14,"Original wait-list head");
_Static_assert(offsetof(NocturneIopSemaphore,count)==0x20,"Original count");
_Static_assert(offsetof(NocturneIopSemaphore,max_count)==0x24,"Original maximum");
uint32_t nocturneIopSemaResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopSif1Dispatch *);
uint32_t nocturneIopSemaRoute(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopSif1Dispatch *);
#endif
