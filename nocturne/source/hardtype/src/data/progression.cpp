// Items' skills (original unit: datCalc): Hardtype's own (shared/src/data/progression.cpp has the rest).
#include "nocturne/data/progression.hpp"

#include "nocturne/data/tables.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"
#include "nocturne/hardtype.hpp"

namespace nocturne::dat {

// datGetItemSkillNo @ 0x00245C90 (and 0x2FDDF0): as US Maniax's, but an
// item with skill 0x89 gives its stand-in 0xDC, and notes the pair.
int32_t itemSkill(int32_t item)
{
    const int32_t* choices = guest::table<const int32_t>(0x00543170);
    if (item == 1)
        return choices[sdf::GetRandInt(6)];
    const uint16_t skill = dat::item(item).skillid;
    if (skill != 0x89)
        return skill;
    hardtype::actingSkill() = skill;
    hardtype::standInSkill() = 0xdc;
    return 0xdc;
}

} // namespace nocturne::dat
