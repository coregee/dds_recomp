// Boss effects (original unit: effPCPBoss): the lengths of Ongyo-Ki's
// effects. Rewritten from the original instructions.
#include "nocturne/effect/boss.hpp"

namespace nocturne::eff {

// effPCPBossONGYGetLength @ 0x00198860
int32_t ongyokiEffectLength() { return 22; }

// effPCPBossONGY2GetLength @ 0x00198FF8
int32_t ongyokiEffect2Length() { return 27; }

// effPCPBossBUNSINGetLength @ 0x00199B08
int32_t ongyokiCloneEffectLength() { return 24; }

// effPCPBossBUNSIN2GetLength @ 0x00199CB0
int32_t ongyokiCloneEffect2Length() { return ongyokiCloneEffectLength() << 1; }

} // namespace nocturne::eff
