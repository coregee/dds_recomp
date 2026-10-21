#ifndef NOCTURNE_IOP_RPC_RECEIVE_H
#define NOCTURNE_IOP_RPC_RECEIVE_H
#include "iop_sleep_wake.h"
uint32_t nocturneIopRpcReceiveResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopThreadStart *);
uint32_t nocturneIopRpcReceiveRoute(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopThreadStart *);
#endif
