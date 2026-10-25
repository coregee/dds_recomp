// Items' skills (original unit: datCalc): US Maniax's own (shared/src/data/progression.cpp has the rest).
#include "nocturne/data/progression.hpp"

#include "nocturne/address.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::dat {

// datGetItemSkillNo @ 0x00245C90 (the six choices are the words at 0x543170)
int32_t itemSkill(int32_t item)
{
    const int32_t* choices = guest::table<const int32_t>(addr(0x00543170));
    if (item == 1)
        return choices[sdf::GetRandInt(6)];
    return dat::item(item).skillid;
}

} // namespace nocturne::dat
