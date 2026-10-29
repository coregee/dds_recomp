// The field's spells in effect and its sequence and process flags.
// Rewritten from the original instructions.
#include "nocturne/field/spells.hpp"

#include "nocturne/address.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/field/next_area.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::fld {

namespace {

constexpr uint32_t kLightomaArea = addr(0x0054eafc);   // int32 (gp-relative): nonzero where Lightoma can work (tentative)
constexpr uint32_t kSequenceFlags = addr(0x0054eb80);  // uint32 (gp-relative)
constexpr uint32_t kProcessFlags = addr(0x0054eb88);   // uint32 (gp-relative)

// The spells' bits in the global work's `fieldskills` and in the area
// state's effect bits (the other way round).
enum : uint32_t { kEstoma = 1, kRiberama = 2, kLiftoma = 4, kLightoma = 8 };
enum : uint32_t { kLightomaEffect = 1, kLiftomaEffect = 2, kRiberamaEffect = 4, kEstomaEffect = 8 };

uint32_t& spells() { return dat::globalWork().fieldskills; }
uint32_t& word(uint32_t address) { return *guest::table<uint32_t>(address); }

void endEffect(uint32_t effect) { areaLoadState().spellEffects &= ~effect; }

} // namespace

// fldEsutoMaStart @ 0x001238A0
void startEstoma()
{
    spells() = (spells() | kEstoma) & ~kRiberama;
    endEffect(kEstomaEffect);
}

// fldEsutoMaClear @ 0x00123870
void clearEstoma()
{
    spells() &= ~kEstoma;
    endEffect(kEstomaEffect);
}

// fldEsutoMaChk @ 0x001238D8
bool estomaActive() { return (spells() & kEstoma) != 0; }

// fldRiberaMaStart @ 0x001237D8
void startRiberama()
{
    spells() = (spells() | kRiberama) & ~kEstoma;
    endEffect(kRiberamaEffect);
}

// fldRiberaMaClear @ 0x001237A8
void clearRiberama()
{
    spells() &= ~kRiberama;
    endEffect(kRiberamaEffect);
}

// fldRiberaMaChk @ 0x00123810
bool riberamaActive() { return (spells() & kRiberama) != 0; }

// fldRifutoMaStart @ 0x00123718
void startLiftoma()
{
    spells() |= kLiftoma;
    endEffect(kLiftomaEffect);
}

// fldRifutoMaClear @ 0x001236E8
void clearLiftoma()
{
    spells() &= ~kLiftoma;
    endEffect(kLiftomaEffect);
}

// fldRifutoMaChk @ 0x00123748
bool liftomaActive() { return (spells() & kLiftoma) != 0; }

// fldLightMaClear @ 0x001234F8
void clearLightoma()
{
    spells() &= ~kLightoma;
    endEffect(kLightomaEffect);
}

// fldLightMaChk @ 0x001235B0
int32_t lightomaState()
{
    if (spells() & kLightoma)
        return 1;
    return word(kLightomaArea) != 0 ? 0 : -1;
}

// fldSeqOnFlag @ 0x00125990
void setSequenceFlags(uint32_t flags) { word(kSequenceFlags) |= flags; }

// fldSeqOffFlag @ 0x001259A8
void clearSequenceFlags(uint32_t flags) { word(kSequenceFlags) &= ~flags; }

// fldSeqCheckFlag @ 0x001259C0
bool anySequenceFlag(uint32_t flags) { return (word(kSequenceFlags) & flags) != 0; }

// fldProcOnFlag @ 0x001259D0
void setProcessFlags(uint32_t flags) { word(kProcessFlags) |= flags; }

// fldProcOffFlag @ 0x001259E0
void clearProcessFlags(uint32_t flags) { word(kProcessFlags) &= ~flags; }

// fldProcCheckFlag @ 0x001259F8
bool anyProcessFlag(uint32_t flags) { return (word(kProcessFlags) & flags) != 0; }

} // namespace nocturne::fld
