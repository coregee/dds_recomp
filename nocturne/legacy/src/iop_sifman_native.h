#ifndef NOCTURNE_IOP_SIFMAN_NATIVE_H
#define NOCTURNE_IOP_SIFMAN_NATIVE_H
#include "iop_heap_service_native.h"
/* Original loaded216-word SIFMAN owner, DMA9/SIF0 IOP->EE. The IRQ prefix can
 * be shared with the existing received-RPC owner. CHCR start writes publish
 * a pending CPU request and tag pointer. No FIFO copy, clock, CHCR completion,
 * IRQ delivery, DMA ID or scheduler reply is synthesized. SBUS control stores
 * observable unforced bits: IOP reads OR F0000002. Debugger byte reads of EE
 * F240 are not valid evidence of its raw value in this installed build.
 * Events are exact original guest access tuples: write,address,width,value. */
typedef struct {
 NocturneIopHeapDevice irq;
 uint32_t madr,bcr,chcr,tadr,sbus_control,pending_start,start_tag,start_requests,chcr_reads,chcr_writes,tadr_writes,bcr_writes,sbus_reads,sbus_writes;
 uint32_t event_count,events[16][4];
} NocturneIopSifmanDevice;
uint32_t nocturneIopSifmanResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopSifmanDevice *);
#endif
