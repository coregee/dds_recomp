#ifndef NOCTURNE_IOP_LIBSD_DMA_CALLBACK_H
#define NOCTURNE_IOP_LIBSD_DMA_CALLBACK_H
#include "iop_libsd_effect.h"
/* Original DMA callback takes this native record's guest address. */
typedef struct {uint32_t mode,argument;} NocturneIopLibSdTransferRecord;
_Static_assert(sizeof(NocturneIopLibSdTransferRecord)==8,"Original transfer record");
uint32_t nocturneIopLibSdDmaCallbackResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopLibSdEffect *);
uint32_t nocturneIopLibSdDmaCallbackRoute(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopLibSdEffect *);
#endif
