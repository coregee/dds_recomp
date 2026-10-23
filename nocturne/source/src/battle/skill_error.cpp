// Whether a skill would do anything (original unit: nbSkillError): before a
// skill is used, in battle or from the menu, the game refuses one that
// can't change its targets (healing the unhurt, curing an ailment no one
// has, a buff at its limit). Rewritten from the original instructions.
#include "nocturne/battle/skill_error.hpp"

#include "nocturne/battle/buffs.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/target_select.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/types.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

bool dead(const UnitWork& unit) { return unit.ailment() == static_cast<uint16_t>(Ailment::Dead); }

// The units and parties of the formation slots in `select`.
struct Targets {
    UnitWork* units[16];
    Party* parties[16];
    int32_t unitCount = 0, partyCount = 0;
};

Targets targetsOf(uint32_t select)
{
    Targets t;
    for (int32_t f = 0; f < 16; ++f) {
        if (!(select & 1u << f))
            continue;
        if (UnitWork* unit = GetUnitWorkFromFormindex(f))
            t.units[t.unitCount++] = unit;
        if (Party* party = GetPartyFromFormindex(f))
            t.parties[t.partyCount++] = party;
    }
    return t;
}

// Skill groups (by ID; the HD remaster names the checks, not the groups).
bool healsHp(int32_t s) { return (s >= 0x24 && s <= 0x29) || s == 0x51 || s == 0x5e; }
bool healsMp(int32_t s) { return s == 0x2a || (s >= 0x52 && s <= 0x54) || s == 0x5d; }
bool cures(int32_t s) { return (s >= 0x2b && s <= 0x30) || s == 0x58; }
bool revives(int32_t s) { return s == 0x31 || s == 0x32; }

} // namespace

// CheckDeadUnit @ 0x00290048: anyone in the stock dead.
bool CheckDeadUnit()
{
    for (const UnitWork& unit : dat::globalWork().units)
        if ((unit.flag & UnitFlag::Valid) && dead(unit))
            return true;
    return false;
}

// CheckDeadUnit2 @ 0x002900A0: any of the units dead.
bool CheckDeadUnit2(UnitWork* const* list, int32_t cnt)
{
    for (int32_t i = 0; i < cnt; ++i)
        if (dead(*list[i]))
            return true;
    return false;
}

// CheckMaxHp @ 0x002900E8: all of them at full HP.
bool CheckMaxHp(UnitWork* const* list, int32_t cnt)
{
    for (int32_t i = 0; i < cnt; ++i)
        if (list[i]->hp < list[i]->maxhp)
            return false;
    return true;
}

// CheckMaxMp @ 0x00290138: all of them at full MP.
bool CheckMaxMp(UnitWork* const* list, int32_t cnt)
{
    for (int32_t i = 0; i < cnt; ++i)
        if (list[i]->mp < list[i]->maxmp)
            return false;
    return true;
}

// CheckBad @ 0x00290188: any of them with one of the ailments.
bool CheckBad(UnitWork* const* list, int32_t cnt, uint32_t bad)
{
    for (int32_t i = 0; i < cnt; ++i)
        if (list[i]->ailment() & bad)
            return true;
    return false;
}

// CheckHojo @ 0x002901D0: whether any of the parties has a buff counter the
// skill's hojotype would still move (bits 1/2: attack up / down, 4/8 magic,
// 0x10/0x20 evasion, 0x40/0x80 defense, 0x100/0x200 accuracy; 0x1000 ..
// 0x20000 the nulls and repels, 0x1000000 Focus, which only go up).
bool CheckHojo(Party* const* list, int32_t cnt, uint32_t hojo)
{
    struct Bit {
        uint32_t bit;
        int32_t type;
        bool up;
    };
    static constexpr Bit bits[] = {
        {0x1, 4, true},       {0x2, 4, false},       {0x4, 5, true},        {0x8, 5, false},
        {0x10, 6, true},      {0x20, 6, false},      {0x40, 7, true},       {0x80, 7, false},
        {0x100, 8, true},     {0x200, 8, false},     {0x1000, 9, true},     {0x2000, 10, true},
        {0x4000, 11, true},   {0x8000, 12, true},    {0x10000, 13, true},   {0x20000, 14, true},
        {0x1000000, 15, true},
    };
    for (int32_t i = 0; i < cnt; ++i)
        for (const Bit& b : bits)
            if ((hojo & b.bit) && list[i]->count[b.type] != (b.up ? buffMax(b.type) : buffMin(b.type)))
                return true;
    return false;
}

// nbDispSkillErrorMessage @ 0x00290490: errors 2 ("no one to revive") and 4
// (buffs) say so on the help line; 1, 2 and 4 make the error sound.
void nbDispSkillErrorMessage(int32_t err)
{
    const MainProcessData& main = *GetMainProcessData();
    if (err == 2)
        nb::DispMsgHelp(main.jyokyomsgid, 0x42, 3);
    else if (err == 4)
        nb::DispMsgHelp(main.jyokyomsgid, 0x46, 3);
    if (err == 1 || err == 2 || err == 4)
        nbPlaySe(13);
}

// nbCheckBattleSkillError1 @ 0x00290520: reviving skills (0x31, 0x32) with
// no one dead in the stock: error 2.
int32_t nbCheckBattleSkillError1(int32_t nskill)
{
    return revives(nskill) && !CheckDeadUnit() ? 2 : 0;
}

// nbCheckBattleSkillError2 @ 0x00290568: the chosen targets (a formation
// bitmask). Error 1 for healing the unhurt or curing an ailment no one has,
// 4 for a buff with nothing left to move. Not with the always-hit debug bit.
int32_t nbCheckBattleSkillError2(int32_t nskill, uint32_t select)
{
    if (GetMainProcessData()->stat & BattleStat::DebugAlwaysHit)
        return 0;
    Targets t = targetsOf(select);
    if (t.unitCount == 0)
        return 0;
    const NormalSkill& skill = dat::normalSkill(nskill);
    if (healsHp(nskill))
        return CheckMaxHp(t.units, t.unitCount) ? 1 : 0;
    if (cures(nskill))
        return CheckBad(t.units, t.unitCount, skill.badstatus) ? 0 : 1;
    switch (nskill) {
    case 0x33: case 0x55: case 0x56: case 0x5c: case 0xed: case 0xee: case 0xef: case 0xf0: case 0xf6: case 0xf8:
        // HP and MP both full
        if (!CheckMaxHp(t.units, t.unitCount))
            return 0;
        return CheckMaxMp(t.units, t.unitCount) ? 1 : 0;
    case 0x44: case 0x45: case 0x46: case 0xe0:
        return CheckHojo(t.parties, t.partyCount, skill.hojotype) ? 0 : 4;
    case 0xda:
        // HP full and none of the ailment
        if (!CheckMaxHp(t.units, t.unitCount))
            return 0;
        return CheckBad(t.units, t.unitCount, skill.badstatus) ? 0 : 1;
    default:
        return healsMp(nskill) ? (CheckMaxMp(t.units, t.unitCount) ? 1 : 0) : 0;
    }
}

// nbCheckBattleSkillError3 @ 0x00290780: buffs (0x34..0x36, 0x40..0x43,
// 0xCB..0xCE, 0x109, 0x114) with nothing left to move: error 3.
int32_t nbCheckBattleSkillError3(int32_t nskill, uint32_t select)
{
    GetMainProcessData();
    Targets t = targetsOf(select);
    if (t.unitCount == 0)
        return 0;
    const bool buff = (nskill >= 0x34 && nskill <= 0x36) || (nskill >= 0x40 && nskill <= 0x43) ||
                      (nskill >= 0xcb && nskill <= 0xce) || nskill == 0x109 || nskill == 0x114;
    if (!buff)
        return 0;
    return CheckHojo(t.parties, t.partyCount, dat::normalSkill(nskill).hojotype) ? 0 : 3;
}

// nbCheckCampSkillError @ 0x00290908: a skill used from the menu on the
// stock units in `select`. One dead target is an error (1) unless the skill
// revives (0x31, 0x32) or is 0x49..0x4C; those four are refused (4) while
// their bit of the global work's word 0xA4C is set.
int32_t nbCheckCampSkillError(int32_t nskill, uint32_t select)
{
    GlobalWork& global = dat::globalWork();
    UnitWork* list[16];
    int32_t count = 0;
    for (int32_t i = 0; i < 16; ++i)
        if ((select & 1u << i) && (global.units[i].flag & UnitFlag::Valid))
            list[count++] = &global.units[i];
    diag::print(diag::Message::SkillSkill, nskill);
    const bool special = revives(nskill) || (nskill >= 0x49 && nskill <= 0x4c);
    if (!special && count == 1 && CheckDeadUnit2(list, 1))
        return 1;
    const NormalSkill& skill = dat::normalSkill(nskill);
    if (healsHp(nskill))
        return CheckMaxHp(list, count) ? 1 : 0;
    if (healsMp(nskill))
        return CheckMaxMp(list, count) ? 1 : 0;
    if (cures(nskill))
        return CheckBad(list, count, skill.badstatus) ? 0 : 1;
    if (revives(nskill))
        return CheckDeadUnit2(list, count) ? 0 : 1;
    switch (nskill) {
    case 0x49: case 0x4a: case 0x4b: case 0x4c:
        return (global.fieldskills & 1u << (nskill - 0x49)) ? 4 : 0;
    case 0x50: case 0x55: case 0x56: case 0x5c: case 0xed: case 0xee: case 0xef: case 0xf0: case 0xf6: case 0xf8:
        if (!CheckMaxHp(list, count))
            return 0;
        return CheckMaxMp(list, count) ? 1 : 0;
    default:
        return 0;
    }
}

} // namespace nocturne::nb
