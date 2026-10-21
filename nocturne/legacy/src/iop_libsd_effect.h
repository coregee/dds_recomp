#ifndef NOCTURNE_IOP_LIBSD_EFFECT_H
#define NOCTURNE_IOP_LIBSD_EFFECT_H
#include "iop_event_heap.h"
/* DMA4/7 register values only. No DMA completion or audio progression. */
typedef struct {NocturneIopLibSd prior;uint32_t voice_dma[6];} NocturneIopLibSdEffect;
typedef struct {int32_t core,mode;int16_t depth_left,depth_right;int32_t delay,feedback;} NocturneIopEffectAttr;
_Static_assert(sizeof(NocturneIopEffectAttr)==20,"Original effect descriptor");
_Static_assert(offsetof(NocturneIopEffectAttr,delay)==12,"Original effect delay");
int nocturneIopLibSdEffectIo(NocturneIopLibSdEffect *,uint32_t,uint32_t,uint32_t,uint32_t *);
uint32_t nocturneIopLibSdEffectResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopLibSdEffect *);
uint32_t nocturneIopLibSdEffectRoute(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopLibSdEffect *);
#endif
