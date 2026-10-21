#ifndef NOCTURNE_IOP_LIBSD_H
#define NOCTURNE_IOP_LIBSD_H
#include "iop_sdf_worker.h"
/* Declared register-value profile for original driver code. This is not an
 * SPU2 audio/DMA/timing model. No status transition or device completion is
 * synthesized. Existing INTC/DICR value owners retain their own semantics. */
typedef struct {
 NocturneIopSif1Dispatch prior;
 uint32_t iop[6];
 uint16_t spu2[1024];
 uint32_t io_event_count,io_events[4096][4];
} NocturneIopLibSd;
int nocturneIopLibSdIo(NocturneIopLibSd *,uint32_t,uint32_t,uint32_t,uint32_t *);
uint32_t nocturneIopLibSdResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopLibSd *);
uint32_t nocturneIopLibSdRoute(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopLibSd *);
#endif
