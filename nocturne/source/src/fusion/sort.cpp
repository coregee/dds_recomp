// Sorting for fusion (original unit: fclStockSort).
#include "nocturne/fusion/sort.hpp"

#include "nocturne/data/tables.hpp"
#include "nocturne/libc/qsort.hpp"

namespace nocturne::cmb {

namespace {

// cmbKeisyoSort_t: an inherited skill and its attribute byte, sorted together.
struct InheritedSkill {
    uint16_t skill;
    uint8_t attr;
    uint8_t padding;
};
static_assert(sizeof(InheritedSkill) == 4);

// cmbSortKeisyoSkillCallback (0x2131E0): ascending skill ID, empty slots last.
int compareInherited(const void* left, const void* right)
{
    uint16_t a = static_cast<const InheritedSkill*>(left)->skill;
    uint16_t b = static_cast<const InheritedSkill*>(right)->skill;
    if (a == 0 && b != 0) return 1;
    if (a != 0 && b == 0) return -1;
    return a > b ? 1 : a < b ? -1 : 0;
}

// (0x213230) by race, then highest level first.
int compareDevils(const void* left, const void* right)
{
    const DevilFormat* a = static_cast<const DevilSortEntry*>(left)->format.get();
    const DevilFormat* b = static_cast<const DevilSortEntry*>(right)->format.get();
    if (a->race != b->race)
        return a->race > b->race ? 1 : -1;
    if (a->level != b->level)
        return a->level > b->level ? -1 : 1;
    return 0;
}

} // namespace

// cmbSortKeisyoSkill @ 0x00213350 (with cmbKeisyoSkillSortCopy 0x213280 and
// cmbKeisyoSkillSortReturn 0x2132C0)
void sortInheritedSkills(UnitWork& unit)
{
    InheritedSkill skills[24];
    for (int i = 0; i < 24; ++i) {
        skills[i].skill = unit.keisyoskill[i];
        skills[i].attr = unit.keiattr[i];
    }
    libc::qsort(skills, 24, sizeof skills[0], compareInherited);
    for (int i = 0; i < 24; ++i) {
        unit.keisyoskill[i] = skills[i].skill;
        unit.keiattr[i] = skills[i].attr;
    }
}

// (0x002133A0)
void sortDevilsByRace(DevilSortEntry* entries, uint16_t count)
{
    for (uint16_t i = 0; i < count; ++i) {
        entries[i].devil = i;
        entries[i].format.address = dat::address::DevilFormat + i * static_cast<uint32_t>(sizeof(DevilFormat));
    }
    libc::qsort(entries, count, sizeof entries[0], compareDevils);
}

} // namespace nocturne::cmb
