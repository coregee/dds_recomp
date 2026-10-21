#ifndef NOCTURNE_IOP_READY_QUEUE_H
#define NOCTURNE_IOP_READY_QUEUE_H
#include "iop_thread_context.h"
/* A declared timer-register value is consumed by the original hardware LW.
 * This carries no autonomous counter progression, IRQ timing or timer return. */
typedef struct {NocturneIopThreadContext thread;uint32_t counter_value,counter_reads;} NocturneIopReadyQueue;
uint32_t nocturneIopReadyQueueResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopReadyQueue *);
uint32_t nocturneIopReadyQueueRoute(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopReadyQueue *);
#endif
