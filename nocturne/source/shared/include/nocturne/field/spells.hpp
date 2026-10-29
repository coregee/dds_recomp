// The field's spells in effect (original unit: the field's event code,
// around 0x1234F8) and the field's sequence and process flags. Estoma,
// Riberama, Liftoma and Lightoma each set their bit of the global work's
// `fieldskills` (records.hpp) and clear one of the area state's effect bits
// (AreaLoadState::spellEffects); Estoma and Riberama end each other.
#pragma once

#include <cstdint>

namespace nocturne::fld {

// fldEsutoMaStart / Clear / Chk (0x1238A0 / 0x123870 / 0x1238D8): Estoma.
void startEstoma();
void clearEstoma();
bool estomaActive();
// fldRiberaMaStart / Clear / Chk (0x1237D8 / 0x1237A8 / 0x123810): Riberama.
void startRiberama();
void clearRiberama();
bool riberamaActive();
// fldRifutoMaStart / Clear / Chk (0x123718 / 0x1236E8 / 0x123748): Liftoma.
void startLiftoma();
void clearLiftoma();
bool liftomaActive();
// fldLightMaClear / Chk (0x1234F8 / 0x1235B0): Lightoma. Its check is 1 in
// effect, else 0 where the area allows it and -1 where it doesn't (tentative).
void clearLightoma();
int32_t lightomaState();

// The field's sequence flags (fldSeqOnFlag / OffFlag / CheckFlag, 0x125990..)
// and process flags (fldProcOnFlag / OffFlag / CheckFlag, 0x1259D0..).
void setSequenceFlags(uint32_t flags);
void clearSequenceFlags(uint32_t flags);
bool anySequenceFlag(uint32_t flags);
void setProcessFlags(uint32_t flags);
void clearProcessFlags(uint32_t flags);
bool anyProcessFlag(uint32_t flags);

} // namespace nocturne::fld
