// Compile-time check that tools/ghidra/nocturne_types.h (the types imported
// into Ghidra) matches the C++ records.
#include <cstddef>
#include <cstdint>

#include "nocturne/battle/process.hpp"
#include "nocturne/data/records.hpp"

namespace ghidra {
#define PTR32(T) uint32_t
#include "nocturne_types.h"
} // namespace ghidra

namespace {

using namespace nocturne;

#define SAME_SIZE(G, R) static_assert(sizeof(ghidra::G) == sizeof(R), #G " size differs from " #R)
#define SAME_OFFSET(G, R, gf, rf) static_assert(offsetof(ghidra::G, gf) == offsetof(R, rf), #G "." #gf " offset differs")

SAME_SIZE(datUnitWork, UnitWork);
SAME_OFFSET(datUnitWork, UnitWork, badstat, badstat);
SAME_OFFSET(datUnitWork, UnitWork, mitamaparam, mitamaparam);
SAME_OFFSET(datUnitWork, UnitWork, hensinmaeexp, hensinmaeexp);
SAME_SIZE(datNormalSkill, NormalSkill);
SAME_OFFSET(datNormalSkill, NormalSkill, program, program);
SAME_OFFSET(datNormalSkill, NormalSkill, magiclimit, magiclimit);
SAME_SIZE(datSpecialSkill, SpecialSkill);
SAME_SIZE(datDevilFormat, DevilFormat);
SAME_OFFSET(datDevilFormat, DevilFormat, specialbit, specialbit);
SAME_OFFSET(datDevilFormat, DevilFormat, reserve1, reserve1);
SAME_SIZE(datEncount, Encount);
SAME_OFFSET(datEncount, Encount, btlsound, btlsound);
SAME_SIZE(datEncountRitu, EncountRitu);
SAME_SIZE(datEncountTbl, EncountTbl);
SAME_SIZE(datEncountPack, EncountPack);
SAME_OFFSET(datEncountPack, EncountPack, enctable, enctable);
SAME_SIZE(datGlobalWork, GlobalWork);
SAME_OFFSET(datGlobalWork, GlobalWork, units, units);
SAME_SIZE(nbFormation, nb::Formation);
SAME_OFFSET(nbFormation, nb::Formation, formindex, formindex);
SAME_SIZE(nbParty, nb::Party);
SAME_OFFSET(nbParty, nb::Party, aisyo, aisyo);
SAME_OFFSET(nbMainProcessData, nb::MainProcessData, esccnt, esccnt);
SAME_OFFSET(nbMainProcessData, nb::MainProcessData, exp, exp);
SAME_OFFSET(nbMainProcessData, nb::MainProcessData, piercedResistance, piercedResistance);
SAME_OFFSET(nbActionProcessData, nb::ActionProcessData, autoskill, autoskill);

} // namespace
