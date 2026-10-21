#ifndef NOCTURNE_IOP_RPC_REPLY_NATIVE_H
#define NOCTURNE_IOP_RPC_REPLY_NATIVE_H
#include "iop_heap_service_native.h"
/* Original loaded-profile SIFCMD composition. Packet pool/counters, real heap
 * callback, reply headers, command packing and DMA descriptor construction.
 * SIFMAN DMA submission targets remain real transfers; no DMA ID, callback,
 * IRQ, reply completion or scheduler result is supplied. BREAK stops at the
 * processor-domain boundary. ICTRL values have no clock/IRQ delivery owner. */
uint32_t nocturneIopRpcReplyResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopHeapDevice *);
#endif
