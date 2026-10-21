#ifndef NOCTURNE_IOP_DMA_DISPATCH_H
#define NOCTURNE_IOP_DMA_DISPATCH_H
#include "iop_sifman_irq.h"
/* DICR value/publication profile, separate from CPU exception dispatch. */
typedef struct {
 NocturneIopSifmanDevice sifman;
 uint32_t dicr1,dicr2,dma_enable,intc_status,cause,irq_requests;
 uint32_t reads,writes,event_count,events[512][4];
} NocturneIopDmaDevice;
int nocturneIopDmaRead(NocturneIopDmaDevice *,uint32_t,uint32_t *);
int nocturneIopDmaWrite(NocturneIopDmaDevice *,uint32_t,uint32_t);
/* Genuine source SIF0 completion request, not a guest callback result. */
int nocturneIopDmaPublishSif0(NocturneIopDmaDevice *);
uint32_t nocturneIopDmaDispatchResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopDmaDevice *);
/* Fixed observed INTRMANI/SIFMAN loaded profile; unknown callbacks transfer. */
uint32_t nocturneIopDmaRoute(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopDmaDevice *);
#endif
