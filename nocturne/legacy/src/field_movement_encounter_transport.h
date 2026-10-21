#ifndef NOCTURNE_FIELD_MOVEMENT_ENCOUNTER_TRANSPORT_H
#define NOCTURNE_FIELD_MOVEMENT_ENCOUNTER_TRANSPORT_H
#include "battle_native_flow.h"
#include "battle_renderer_indexed_cache.h"
/* New family transport only. A failure retains the true selected raw PC and
 * never resumes a static caller. Typed old callees claim only their ABI. */
uint32_t nocturneFieldMovementConfigure(const NocturneWakeupMachine *,const NocturneIndexedCacheConfig *,const uint32_t *,uint32_t,uint64_t);
uint32_t nocturneFieldMovementRun(uint32_t entry);
const uint64_t *nocturneFieldMovementLastStop(void);
const NocturneWakeupMachine *nocturneFieldMovementRawState(void);
const NocturneIndexedCacheState *nocturneFieldMovementCacheState(void);
const uint64_t *nocturneFieldMovementRouteCounts(void);
#endif
