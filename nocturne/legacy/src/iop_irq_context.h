#ifndef NOCTURNE_IOP_IRQ_CONTEXT_H
#define NOCTURNE_IOP_IRQ_CONTEXT_H
#include "iop_dma_dispatch.h"
/* CPU GPR/HI/LO machine remains168B. CP0 and device state are explicit,
 * separate inputs; no prebuilt return frame or ready thread is supplied. */
typedef struct {
 NocturneIopDmaDevice dma;
 uint32_t cp0[32],intc_mask,reads,writes,wake_requests,event_count,events[64][4];
 uint32_t cp0_event_count,cp0_events[16][3],rfe_count;
} NocturneIopIrqContext;
int nocturneIopIrqRead(NocturneIopIrqContext *,uint32_t,uint32_t *);
int nocturneIopIrqWrite(NocturneIopIrqContext *,uint32_t,uint32_t);
int nocturneIopCp0Event(NocturneIopIrqContext *,uint32_t,uint32_t,uint32_t);
uint32_t nocturneIopIrqContextResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopIrqContext *);
uint32_t nocturneIopIrqContextRoute(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopIrqContext *);
#endif
