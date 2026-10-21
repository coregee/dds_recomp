#ifndef NOCTURNE_IOP_BIND_H
#define NOCTURNE_IOP_BIND_H
#include "iop_sif1_dispatch.h"
#include "iop_rpc_layout.h"
uint32_t nocturneIopBindResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopSif1Dispatch *);
uint32_t nocturneIopBindRoute(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopSif1Dispatch *);
#endif
