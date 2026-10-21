#ifndef NOCTURNE_OBJECT_ATTACHMENT_TRANSPORT_H
#define NOCTURNE_OBJECT_ATTACHMENT_TRANSPORT_H
#include "battle_native_flow.h"
#include "battle_renderer_indexed_cache.h"
uint32_t nocturneObjectAttachmentConfigure(const NocturneWakeupMachine *,const NocturneIndexedCacheConfig *,const uint32_t *,uint32_t,uint64_t);
uint32_t nocturneObjectAttachmentRun(uint32_t);
const uint64_t *nocturneObjectAttachmentLastStop(void);
const NocturneWakeupMachine *nocturneObjectAttachmentRawState(void);
const uint64_t *nocturneObjectAttachmentRouteCounts(void);
#endif
