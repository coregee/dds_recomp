#ifndef NOCTURNE_IOP_THREAD_START_H
#define NOCTURNE_IOP_THREAD_START_H
#include "iop_ready_queue.h"
/* Original constructor/start and installed exception-vector statements. CPU
 * SYSCALL entry follows the pinned CPU primitive; vector/dispatch/frame stores
 * are executed by their actual native owners. No saved frame is returned by a hook. */
typedef struct {NocturneIopReadyQueue queue;uint32_t syscalls;} NocturneIopThreadStart;
uint32_t nocturneIopThreadStartResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopThreadStart *);
uint32_t nocturneIopThreadStartRoute(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopThreadStart *);
#endif
