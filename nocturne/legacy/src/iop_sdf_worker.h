#ifndef NOCTURNE_IOP_SDF_WORKER_H
#define NOCTURNE_IOP_SDF_WORKER_H
#include "iop_sema.h"
#include "sound_worker_protocol.h"
typedef struct NocturneIopSoundQueue {uint16_t count,read_index;uint32_t dropped;} NocturneIopSoundQueue;
_Static_assert(sizeof(NocturneIopSoundQueue)==8,"Original queue metadata");
_Static_assert(offsetof(NocturneIopSoundQueue,dropped)==4,"Original dropped count");
uint32_t nocturneIopSdfWorkerResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopSif1Dispatch *);
uint32_t nocturneIopSdfWorkerRoute(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopSif1Dispatch *);
#endif
