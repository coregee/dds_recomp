#ifndef NOCTURNE_IOP_SLEEP_WAKE_H
#define NOCTURNE_IOP_SLEEP_WAKE_H
#include "iop_thread_start.h"
uint32_t nocturneIopSleepWakeResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopThreadStart *);
uint32_t nocturneIopSleepWakeRoute(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopThreadStart *);
#endif
