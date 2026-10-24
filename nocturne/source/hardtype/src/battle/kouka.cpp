// The presentation queue (original unit: nbKoukaProcess): Hardtype's own (shared/src/battle/kouka.cpp has the rest).
#include "nocturne/battle/kouka.hpp"

#include "nocturne/guest.hpp"
#include "nocturne/hardtype.hpp"

namespace nocturne::nb {

// nbMakeNewPressPacket @ 0x00264368 (and 0x2FE480): for a result of type 0..17
// the noted pair is read and cleared: acting skill 0x10E counts as type 3,
// 0x86 takes 8 icons of each kind, and after a summon (skill 0xFF) the type
// is 1.
bool versionPressResult(int32_t& ptype, int32_t callerSkill, int32_t& dFull, int32_t& dHalf)
{
    const uint16_t acting = hardtype::actingSkill();
    hardtype::actingSkill() = 0;
    hardtype::standInSkill() = 0;
    if (acting == 0x10e) {
        ptype = 3;
        return false;
    }
    if (acting == 0x86) {
        dFull = -8;
        dHalf = -8;
        return true;
    }
    if (callerSkill == 0xff)
        ptype = 1;
    return false;
}

// nbMakeBadKaifukuPacket @ 0x002645A8 (and 0x2FE7A0): ailment 4 when bit 1 or
// 2 is set in the byte 0xE past what the unit lookup left in a0 (meant as the
// unit's ailment, it is the battle record's word 0xC for a unit in battle).
uint32_t curedAilment(int32_t formindex, uint32_t bad)
{
    const int8_t byte = *guest::table<int8_t>(hardtype::unitLookupRegister(formindex) + 0xe);
    return (byte & 3) ? 4 : bad;
}

} // namespace nocturne::nb
