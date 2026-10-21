#ifndef NOCTURNE_IOP_SIFMAN_IRQ_H
#define NOCTURNE_IOP_SIFMAN_IRQ_H
#include "iop_sifman_native.h"
/* Original94-word ISR and original2-word exported retonly. Real callbacks
 * transfer to their original target. The retonly target is a declared finite
 * callback input, not an injected return. Queued restarts publish DMA requests;
 * neither guest exception entry/restoration nor device completion is supplied. */
uint32_t nocturneIopSifmanIrqResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopSifmanDevice *);
#endif
