#ifndef NOCTURNE_IOP_THREAD_CONTEXT_H
#define NOCTURNE_IOP_THREAD_CONTEXT_H
#include "iop_irq_context.h"
/* Source-owned IOP context callback and syscall20 frame producer. The optional
 * byte write is a recorded debug-port request, not a hardware timing model. */
typedef struct {NocturneIopIrqContext irq;uint32_t debug_port70,debug_port70_writes;} NocturneIopThreadContext;
uint32_t nocturneIopThreadContextResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopThreadContext *);
uint32_t nocturneIopThreadContextRoute(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopThreadContext *);
#endif
