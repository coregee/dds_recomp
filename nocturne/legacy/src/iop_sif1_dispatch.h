#ifndef NOCTURNE_IOP_SIF1_DISPATCH_H
#define NOCTURNE_IOP_SIF1_DISPATCH_H
#include "iop_rpc_receive.h"
/* DMA10 CPU register writes and pending start only. Device transfer/completion
 * and the enclosing hardware IRQ/scheduler exit remain separate owners. */
typedef struct {
 NocturneIopThreadStart thread;
 uint32_t bcr,chcr,pending_start,start_requests,chcr_writes,bcr_writes;
 uint32_t event_count,events[8][4];
} NocturneIopSif1Dispatch;
uint32_t nocturneIopSif1DispatchResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopSif1Dispatch *);
uint32_t nocturneIopSif1DispatchRoute(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopSif1Dispatch *);
#endif
