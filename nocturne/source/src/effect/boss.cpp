// Boss effects (original unit: effPCPBoss): the lengths of Ongyo-Ki's
// effects. Rewritten from the original instructions.
#include "nocturne/effect/boss.hpp"

namespace nocturne::eff {

// effPCPBossONGYGetLength @ 0x00198860
int32_t effPCPBossONGYGetLength() { return 22; }

// effPCPBossONGY2GetLength @ 0x00198FF8
int32_t effPCPBossONGY2GetLength() { return 27; }

// effPCPBossBUNSINGetLength @ 0x00199B08
int32_t effPCPBossBUNSINGetLength() { return 24; }

// effPCPBossBUNSIN2GetLength @ 0x00199CB0
int32_t effPCPBossBUNSIN2GetLength() { return effPCPBossBUNSINGetLength() << 1; }

} // namespace nocturne::eff
