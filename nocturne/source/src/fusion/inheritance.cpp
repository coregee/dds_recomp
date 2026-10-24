// Skill inheritance (original unit: cmb).
#include "nocturne/fusion/inheritance.hpp"

#include <cstring>

#include "nocturne/data/tables.hpp"
#include "nocturne/external.hpp"

namespace nocturne::cmb {

// cmbGetKeisyoSkillScore @ 0x00222AA0
//
// Looks up the column whose key is the skill's element and the row whose key
// is the devil's inheritance type. An absent key leaves the index one past
// the end, and the original then reads whatever follows (the next row's key,
// or the padding after the table); that is reproduced by reading raw bytes.
uint8_t inheritScore(int16_t skillattr, int16_t keisyotype)
{
    const auto* raw = dat::tableAt<uint8_t>(dat::address::InheritanceScores);
    auto key = [&](uint32_t offset) {
        int16_t value;
        std::memcpy(&value, raw + offset, 2);
        return value;
    };
    uint32_t column = 0;
    while (column < 16 && key(2 + 2 * column) != skillattr)
        ++column;
    uint32_t row = 0;
    while (row < 13 && key(0x22 + 0x22 * row) != keisyotype)
        ++row;
    return raw[0x24 + 2 * column + 0x22 * row];
}

// cmbGetKeisyoSkillMotion @ 0x00222B70: only the skill's lowest set form bit
// counts.
uint8_t inheritFormMatch(uint16_t skillForm, uint16_t devilForm)
{
    for (uint32_t bit = 0; bit < 16; ++bit)
        if (skillForm & (1u << bit))
            return static_cast<uint8_t>((devilForm >> bit) & 1);
    return 0;
}

// cmbGetKeisyoSkillLevel @ 0x00222BB0: 1 for skills not in the table.
uint8_t inheritLevel(uint16_t skill)
{
    const InheritanceLevel* levels = dat::tableAt<InheritanceLevel>(dat::address::InheritanceLevel);
    for (int i = 0; i < 227; ++i)
        if (levels[i].skill == skill)
            return levels[i].level;
    return 1;
}

// cmbCalcKeisyoSkillRate @ 0x00222BF0
uint8_t inheritRate(const UnitWork& unit, uint16_t skill)
{
    const SkillInfo& info = dat::skillInfo(skill);
    const DevilFormat& devil = dat::devilFormat(unit.id);
    uint8_t score = inheritScore(info.skillattr, devil.inheritType);
    if (!inheritFormMatch(info.inheritMask, devil.inheritMask))
        return 0;
    uint8_t divisor = inheritLevel(skill);
    if (divisor == 0)
        divideByZeroTrap();
    int32_t rate = score / divisor + unit.level - devil.level + 1;
    if (rate >= 100)
        rate = 99;
    return static_cast<uint8_t>(rate);   // a negative rate wraps, as in the original
}

// cmbCalcTotalKeisyoSkillRate @ 0x001FF3B8
int32_t totalInheritRate(const UnitWork& unit)
{
    int32_t total = 0;
    for (uint16_t skill : unit.inheritedSkills)
        if (skill)
            total += inheritRate(unit, skill);
    return total;
}

// cmbGetKeisyoSkillEndIndex @ 0x001FDDA8
int8_t inheritedEnd(const UnitWork& unit)
{
    for (int i = 0; i < 24; ++i)
        if (unit.inheritedSkills[i] == 0)
            return static_cast<int8_t>(i);
    return -1;
}

// cmbClearKeisyoSkill @ 0x001FF0A8 (the keiattr bytes after the list stay)
void clearInherited(UnitWork& unit)
{
    std::memset(unit.inheritedSkills, 0, sizeof unit.inheritedSkills);
}

// cmbChkKeisyoSkillOwner @ 0x001FEDF0
int8_t findInherited(uint16_t skill, const UnitWork& unit)
{
    for (int i = 0; i < 24; ++i)
        if (unit.inheritedSkills[i] == skill)
            return static_cast<int8_t>(i);
    return -1;
}

// cmbChkKeisyoSkillNums @ 0x001FEE30
int8_t countInherited(const UnitWork& unit)
{
    int8_t count = 0;
    for (uint16_t skill : unit.inheritedSkills)
        if (skill)
            ++count;
    return count;
}

} // namespace nocturne::cmb
