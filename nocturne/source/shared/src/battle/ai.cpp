// Enemy AI (original unit: nbAi).
#include "nocturne/battle/ai.hpp"

#include <cstddef>
#include <cstdio>
#include <cstdlib>

#include "nocturne/battle/affinity.hpp"
#include "nocturne/battle/buffs.hpp"
#include "nocturne/battle/calc.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/damage.hpp"
#include "nocturne/battle/targeting.hpp"
#include "nocturne/data/devil_ai.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb::ai {

namespace {

MainProcessData& mainOf(ActionProcessData& act) { return *act.data; }
int32_t self(const ActionProcessData& act) { return act.form->formindex; }
uint32_t bitFor(int32_t formindex) { return 1u << (formindex & 31); }

// A party record counts if present and not out of action (flags 0x38).
bool active(const Party& party) { return (party.flag & 1) && !(party.flag & 0x38); }

Party& partyAt(ActionProcessData& act, int32_t index) { return mainOf(act).party[index]; }
UnitWork& unitOf(ActionProcessData& act, Party& party) { return *GetUnitWorkPointer(mainOf(act), party); }

void pickSelf(ActionProcessData& act) { act.aiselect = bitFor(self(act)); }
void pick(ActionProcessData& act, int32_t index) { act.aiselect |= bitFor(partyAt(act, index).formindex); }

// Party records 0..3 are the player's side, 4..13 the AI's.
constexpr int32_t kEnemiesBegin = 0, kEnemiesEnd = 4, kAlliesBegin = 4, kAlliesEnd = 14;

void pickAll(ActionProcessData& act, int32_t begin, int32_t end)
{
    for (int32_t k = begin; k < end; ++k)
        if (active(partyAt(act, k)))
            pick(act, k);
}

template <class Test>
bool pickWhere(ActionProcessData& act, int32_t begin, int32_t end, Test test)
{
    for (int32_t k = begin; k < end; ++k) {
        Party& party = partyAt(act, k);
        if (active(party) && test(k, party))
            pick(act, k);
    }
    return act.aiselect != 0;
}

uint32_t hpPercent(const UnitWork& unit)
{
    if (unit.maxhp == 0)
        divideByZeroTrap();
    return unit.hp * 100u / unit.maxhp;
}

dat::AiRecord recordOf(const ActionProcessData& act) { return dat::aiRecord(act.work->id); }

AiAction actionAt(const ActionProcessData& act, uint32_t table, int32_t action) { return recordOf(act).action(table, action); }

Formation& slot(MainProcessData& main, int32_t index)
{
    return *guest::table<Formation>(main.form.address + static_cast<uint32_t>(index) * sizeof(Formation));
}

bool selectable(MainProcessData& main, int32_t index) { return (slot(main, index).stat & FormationStat::Selectable) != 0; }
void markSelected(MainProcessData& main, int32_t index) { slot(main, index).stat |= FormationStat::Selected; }

void markAllSelectable(MainProcessData& main)
{
    for (int32_t i = 0; i < 16; ++i)
        if (selectable(main, i))
            markSelected(main, i);
}

bool anySelected(MainProcessData& main)
{
    for (int32_t i = 0; i < 16; ++i)
        if (slot(main, i).stat & FormationStat::Selected)
            return true;
    return false;
}

// The unit in a formation slot; an empty slot reads guest address 0, as the
// original does.
const UnitWork& unitInSlot(int32_t index)
{
    UnitWork* unit = GetUnitWorkFromFormindex(index);
    return unit ? *unit : *guest::table<const UnitWork>(0);
}

// Codes of ChkAiHojo: 0..9 -kaja/-nda pairs on counters 4..8, 11..17
// counters 9..15; 10 and 18+ never hold.
bool buffCode(int32_t code, int32_t* type, bool* debuff)
{
    if (static_cast<uint32_t>(code) >= 18 || code == 10)
        return false;
    *type = code < 10 ? 4 + code / 2 : code - 2;
    *debuff = code < 10 && (code & 1);
    return true;
}

// The skill the unit's command uses: attack 0, skill / item its index.
bool commandSkill(const UnitWork& unit, int32_t* skill)
{
    int16_t command = unit.nowcommand;
    if (command == 1 || command == 5) {
        *skill = unit.nowindex;
        return true;
    }
    *skill = 0;
    return command == 0;
}

} // namespace

// ===========================================================================
// Conditions
// ===========================================================================

// nbAiChkMyHp @ 0x002853D8
bool ownHpAtMost(ActionProcessData& act, int32_t percent)
{
    if (static_cast<int32_t>(hpPercent(*act.work)) > percent)
        return false;
    pickSelf(act);
    return true;
}

// nbAiChkMyMp @ 0x00285438: MP itself, not a percentage.
bool ownMpAtMost(ActionProcessData& act, int32_t mp)
{
    if (act.work->mp > mp)
        return false;
    pickSelf(act);
    return true;
}

// nbAiChkFrHp @ 0x00285470
bool allyHpAtMost(ActionProcessData& act, int32_t percent)
{
    for (int32_t k = kAlliesBegin; k < kAlliesEnd; ++k) {
        Party& party = partyAt(act, k);
        if (!active(party))
            continue;
        if (static_cast<int32_t>(hpPercent(unitOf(act, party))) <= percent)
            pick(act, k);
    }
    return act.aiselect != 0;
}

// nbAiChkDmgCnt @ 0x00285578: buff counter 0 counts hits taken.
bool damageCountAtLeast(ActionProcessData& act, int32_t count)
{
    if (buffCounter(self(act), 0) < count)
        return false;
    pickSelf(act);
    return true;
}

// nbAiChkChkCnt @ 0x002855D8: counts how often this AI check was evaluated
// (counter 1..3 for checks 0..2, capped at 127); check() resets it when the
// check succeeds.
bool checkedAtLeast(ActionProcessData& act, int32_t count)
{
    int32_t value = buffCounter(self(act), act.aijokentbl + 1);
    if (value < 127)
        ++value;
    setBuffCounter(self(act), act.aijokentbl + 1, value);
    if (value < count)
        return false;
    pickSelf(act);
    return true;
}

// nbAiChkFrCnt @ 0x00285668
bool allyCountAtMost(ActionProcessData& act, int32_t count)
{
    if (mainOf(act).enemypcnt > count)
        return false;
    pickAll(act, kAlliesBegin, kAlliesEnd);
    return true;
}

// nbAiChkEnCnt @ 0x002856F0
bool enemyCountAtMost(ActionProcessData& act, int32_t count)
{
    if (mainOf(act).playerpcnt > count)
        return false;
    pickAll(act, kEnemiesBegin, kEnemiesEnd);
    return true;
}

// nbAiChkMyBad @ 0x00285778
bool ownAilment(ActionProcessData& act, int32_t ailment)
{
    if (act.work->ailment() != ailment)
        return false;
    pickSelf(act);
    return true;
}

// nbAiChkFrBad @ 0x002857B0
bool allyAilment(ActionProcessData& act, int32_t ailment)
{
    return pickWhere(act, kAlliesBegin, kAlliesEnd, [&](int32_t, Party& p) { return unitOf(act, p).ailment() == ailment; });
}

// nbAiChkEnBad @ 0x00285890
bool enemyAilment(ActionProcessData& act, int32_t ailment)
{
    return pickWhere(act, kEnemiesBegin, kEnemiesEnd, [&](int32_t, Party& p) { return unitOf(act, p).ailment() == ailment; });
}

// nbAiChkEnAllBad @ 0x00285970: as many afflicted as the player's side
// has combatants.
bool allEnemiesAilment(ActionProcessData& act, int32_t ailment)
{
    uint32_t bits = 0;
    int32_t count = 0;
    for (int32_t k = kEnemiesBegin; k < kEnemiesEnd; ++k) {
        Party& party = partyAt(act, k);
        if (active(party) && unitOf(act, party).ailment() == ailment) {
            ++count;
            bits |= bitFor(party.formindex);
        }
    }
    if (count != mainOf(act).playerpcnt)
        return false;
    act.aiselect = bits;
    return true;
}

// nbAiChkEnId @ 0x00285A70: not the Demi-fiend.
bool enemyIsDevil(ActionProcessData& act, int32_t devil)
{
    return pickWhere(act, kEnemiesBegin, kEnemiesEnd, [&](int32_t, Party& p) {
        const UnitWork& unit = unitOf(act, p);
        return !unit.isPlayerCharacter() && unit.id == devil;
    });
}

// nbAiChkFrId @ 0x00285B60: not counting the AI's own party record.
bool allyIsDevil(ActionProcessData& act, int32_t devil)
{
    for (int32_t k = kAlliesBegin; k < kAlliesEnd; ++k) {
        if (k == act.partyindex)
            continue;
        Party& party = partyAt(act, k);
        if (active(party) && unitOf(act, party).id == devil)
            pick(act, k);
    }
    return act.aiselect != 0;
}

// nbAiChkHojo @ 0x00285C48
bool hasBuff(int32_t formindex, int32_t code)
{
    int32_t type;
    bool debuff;
    if (!buffCode(code, &type, &debuff))
        return false;
    int32_t value = buffCounter(formindex, type);
    return debuff ? value < 0 : value > 0;
}

// nbAiChkHojoMax @ 0x00285D30
bool buffAtLimit(int32_t formindex, int32_t code, uint32_t callerKey)
{
    int32_t type;
    bool debuff;
    if (!buffCode(code, &type, &debuff))
        return false;
    int32_t value = buffCounter(formindex, type);
    return debuff ? value <= buffMin(type, callerKey) : value >= buffMax(type, callerKey);
}

// nbAiChkEnHojo @ 0x00285EC8
bool enemyBuff(ActionProcessData& act, int32_t code)
{
    return pickWhere(act, kEnemiesBegin, kEnemiesEnd, [&](int32_t, Party& p) { return hasBuff(p.formindex, code); });
}

// nbAiChkFrHojo @ 0x00285FA8
bool allyBuff(ActionProcessData& act, int32_t code)
{
    return pickWhere(act, kAlliesBegin, kAlliesEnd, [&](int32_t, Party& p) { return hasBuff(p.formindex, code); });
}

namespace {

// (the buff limits' key both leave: the slot's offset, 128 x k, plus 1)
uint32_t slotKey(int32_t k) { return 128u * static_cast<uint32_t>(k) + 1; }

} // namespace

// nbAiChkEnHojoMax @ 0x00286088
bool enemyBuffAtLimit(ActionProcessData& act, int32_t code)
{
    return pickWhere(act, kEnemiesBegin, kEnemiesEnd, [&](int32_t k, Party& p) { return buffAtLimit(p.formindex, code, slotKey(k)); });
}

// nbAiChkFrHojoMax @ 0x00286168
bool allyBuffAtLimit(ActionProcessData& act, int32_t code)
{
    return pickWhere(act, kAlliesBegin, kAlliesEnd, [&](int32_t k, Party& p) { return buffAtLimit(p.formindex, code, slotKey(k)); });
}

// nbAiChkBa @ 0x00286248
bool backAttack(ActionProcessData& act, int32_t)
{
    if (!(mainOf(act).stat & BattleStat::BackAttack))
        return false;
    pickAll(act, kEnemiesBegin, kEnemiesEnd);
    return true;
}

// nbAiChkSensei @ 0x002862D0
bool enemiesStruckFirst(ActionProcessData& act, int32_t)
{
    if (!(mainOf(act).stat & BattleStat::EnemiesFirst))
        return false;
    pickAll(act, kEnemiesBegin, kEnemiesEnd);
    return true;
}

// nbAiChkEnLight @ 0x00286358 / nbAiChkEnDark @ 0x00286440 (alignment +1 / -1)
bool enemyIsLight(ActionProcessData& act, int32_t)
{
    return pickWhere(act, kEnemiesBegin, kEnemiesEnd, [&](int32_t, Party& p) {
        const UnitWork& unit = unitOf(act, p);
        return !unit.isPlayerCharacter() && dat::alignment(unit) == 1;
    });
}

// nbAiChkEnDark @ 0x00286440
bool enemyIsDark(ActionProcessData& act, int32_t)
{
    return pickWhere(act, kEnemiesBegin, kEnemiesEnd, [&](int32_t, Party& p) {
        const UnitWork& unit = unitOf(act, p);
        return !unit.isPlayerCharacter() && dat::alignment(unit) == -1;
    });
}

// nbAiChkPow @ 0x00286530: Focus is buff code 17.
bool ownFocus(ActionProcessData& act, int32_t)
{
    if (!hasBuff(self(act), 17))
        return false;
    pickSelf(act);
    return true;
}

// nbAiChkPlv @ 0x00286580
bool playerLevelAtLeast(ActionProcessData&, int32_t level)
{
    return dat::playerLevel() >= level;
}

// nbAiChkPPartyLv @ 0x002865B0
bool partyLevelAtLeast(ActionProcessData& act, int32_t level)
{
    return averageCombatLevel(mainOf(act), Side::Player) >= level;
}

// nbAiChkTurn @ 0x002865E8
bool turnAtLeast(ActionProcessData& act, int32_t turn)
{
    return mainOf(act).turn >= turn;
}

// nbAiChkEnHamamHk @ 0x00286600: no Null/Repel/Drain against Expel.
bool enemyNotImmuneToExpel(ActionProcessData& act, int32_t)
{
    return pickWhere(act, kEnemiesBegin, kEnemiesEnd, [&](int32_t, Party& p) {
        return !(dat::affinity(unitOf(act, p), Attribute::Expel) & 0x70000);
    });
}

// nbAiChkSkillNoMp @ 0x002866E8
bool cannotAfford(ActionProcessData& act, int32_t skill)
{
    if (checkSkillCost(self(act), skill) == SkillCheck::Ok)
        return false;
    pickSelf(act);
    return true;
}

// nbAiChkJoken @ 0x00286730: dispatches through the table at 0x4F0788
// (type 21 is a second entry for checkedAtLeast). The original has no bounds
// check; types past 28 jump through unrelated words.
bool condition(ActionProcessData& act, uint32_t word)
{
    int32_t type = static_cast<int32_t>(word >> 16);
    if (type == 0)
        return true;
    int32_t n = static_cast<int32_t>(word & 0xffff);
    uint32_t previous = act.aiselect;
    act.aiselect = 0;
    bool holds;
    switch (type) {
    case 1: holds = ownHpAtMost(act, n); break;
    case 2: holds = allyHpAtMost(act, n); break;
    case 3: holds = damageCountAtLeast(act, n); break;
    case 4: case 21: holds = checkedAtLeast(act, n); break;
    case 5: holds = allyCountAtMost(act, n); break;
    case 6: holds = enemyCountAtMost(act, n); break;
    case 7: holds = ownAilment(act, n); break;
    case 8: holds = allyAilment(act, n); break;
    case 9: holds = enemyAilment(act, n); break;
    case 10: holds = allEnemiesAilment(act, n); break;
    case 11: holds = enemyIsDevil(act, n); break;
    case 12: holds = allyIsDevil(act, n); break;
    case 13: holds = enemyBuff(act, n); break;
    case 14: holds = allyBuff(act, n); break;
    case 15: holds = backAttack(act, n); break;
    case 16: holds = enemyIsLight(act, n); break;
    case 17: holds = enemyIsDark(act, n); break;
    case 18: holds = ownFocus(act, n); break;
    case 19: holds = playerLevelAtLeast(act, n); break;
    case 20: holds = partyLevelAtLeast(act, n); break;
    case 22: holds = turnAtLeast(act, n); break;
    case 23: holds = enemiesStruckFirst(act, n); break;
    case 24: holds = ownMpAtMost(act, n); break;
    case 25: holds = enemyBuffAtLimit(act, n); break;
    case 26: holds = allyBuffAtLimit(act, n); break;
    case 27: holds = enemyNotImmuneToExpel(act, n); break;
    case 28: holds = cannotAfford(act, n); break;
    default:   // a version's own types, or else the original calls whatever word follows the table
        if (!versionCondition(type, n, holds))
            std::abort();
        break;
    }
    if (!holds)
        return false;
    if (previous)
        selectionAfterCondition(act, type) &= previous;
    return true;
}

// ===========================================================================
// Choosing an action
// ===========================================================================

// nbAiAiChk @ 0x002867A8: all of the check's conditions (two in US Maniax).
bool check(ActionProcessData& act, int32_t index)
{
    clearSelectionForCheck(act, index);
    const dat::AiRecord record = recordOf(act);
    act.aijokentbl = index;
    bool counted = false;
    for (int32_t k = 0; k < dat::AiRecord::kConditions; ++k) {
        const uint32_t word = record.condition(index, k);
        if (!condition(act, word))
            return false;
        counted |= (word >> 16) == 4;
    }
    // Only type 4 resets the check count (type 21 doesn't).
    if (counted)
        setBuffCounter(self(act), index + 1, 0);
    return true;
}

// nbAiGetKoudou @ 0x00286888: by weight among actions not yet tried.
int32_t drawAction(ActionProcessData& act, uint32_t table)
{
    int32_t candidates[5];
    int32_t count = 0;
    uint32_t total = 0;
    const int32_t actions = recordOf(act).actions(table);   // (5, or what a Hardtype table holds: never more)
    for (int32_t k = 0; k < actions; ++k) {
        uint8_t tried = static_cast<uint8_t>(act.aichktbl[k]);
        if (tried == 0 || (tried & 0x80)) {
            candidates[count++] = k;
            total += actionAt(act, table, k).weight;
        }
    }
    if (count == 0 || total == 0)
        return -1;
    int32_t roll = sdf::GetRandInt(static_cast<int32_t>(total));
    uint32_t sum = 0;
    for (int32_t i = 0; i < count; ++i) {
        sum += actionAt(act, table, candidates[i]).weight;
        if (roll < static_cast<int32_t>(sum))
            return candidates[i];
    }
    return -1;
}

// nbAiSetKoudou @ 0x002869A0. Skill words 0x8000..0x8003 are attack, escape
// (command 7), pass (3) and command 9; 0x9xxx..0xFxxx are calls for help
// (skills 0xE2, 0xE3, 0xE5, 0xE6, 0xFC, 0xDE) with the devil in the low 12
// bits, and 0xExxx command 9 with its parameter in MainProcessData.
void setAction(ActionProcessData& act, uint32_t table, int32_t action)
{
    UnitWork& unit = *act.work;
    unit.nowcommand = 0;
    unit.nowindex = 0;
    uint16_t skill = actionAt(act, table, action).skill;
    switch (skill) {
    case 0x8000: unit.nowcommand = 0; setNormalAttack(unit); return;
    case 0x8001: unit.nowcommand = 7; return;
    case 0x8002: unit.nowcommand = 3; return;
    case 0x8003: unit.nowcommand = 9; return;
    default: break;
    }
    unit.nowcommand = 1;
    if (!(skill & 0x8000)) {
        unit.nowindex = skill;
        return;
    }
    switch (skill & 0xf000) {
    case 0x9000: unit.nowindex = 0xe2; break;
    case 0xa000: unit.nowindex = 0xe3; break;
    case 0xb000: unit.nowindex = 0xe5; break;
    case 0xc000: unit.nowindex = 0xe6; break;
    case 0xd000: unit.nowindex = 0xfc; break;
    case 0xf000: unit.nowindex = 0xde; break;
    case 0xe000:
        unit.nowcommand = 9;
        mainOf(act).eventno = skill & 0xfff;
        break;
    default:   // 0x8xxx otherwise: no skill, just the parameter
        break;
    }
    act.aisummonid = skill & 0xfff;
}

// nbAiChkCost @ 0x00287860: AI levels 1 and 2 respect skill costs.
bool costBlocks(ActionProcessData& act)
{
    int32_t skill;
    if (!commandSkill(*act.work, &skill))
        return false;
    if (checkSkillCost(self(act), skill) == SkillCheck::Ok)
        return false;
    uint16_t level = recordOf(act).level();
    return level != 0 && level < 3;
}

// nbAiChkClose @ 0x00287928
bool canProceed(ActionProcessData& act)
{
    int32_t skill;
    if (!commandSkill(*act.work, &skill))
        return true;
    if (checkSkillUse(self(act), skill) <= 0)
        return true;
    uint16_t level = recordOf(act).level();
    return level == 0 || level >= 3;
}

// nbRunAiSub @ 0x00287B40: draw actions until one has targets; if none,
// the unit passes.
int32_t runTable(ActionProcessData& act, uint32_t table)
{
    for (int8_t& tried : act.aichktbl)
        tried = 0;
    int32_t action;
    for (;;) {
        action = drawAction(act, table);
        diag::print(diag::Message::AiActionTable, action);
        if (action < 0)
            break;
        setAction(act, table, action);
        if (!costBlocks(act) && canProceed(act)) {
            uint32_t target = actionAt(act, table, targetedAction(act, action)).target;
            if (selectTargets(act, static_cast<int32_t>(target >> 16), static_cast<int32_t>(target & 0xffff)) == 0)
                break;
        }
        act.aichktbl[action] = 1;
    }
    if (action < 0) {
        act.select = 0;
        act.work->nowcommand = 3;
        act.work->nowindex = 0;
    } else {
        act.select = selectedBits(mainOf(act));
    }
    return 0;
}

// nbRunAi @ 0x00287CB8: the first check that holds picks the table, else
// the first table.
int32_t run(ActionProcessData& act)
{
    uint32_t table = recordOf(act).firstTable();
    for (int32_t index = 0; index < recordOf(act).checks(); ++index) {
        if (check(act, index)) {
            table = recordOf(act).table(index);
            break;
        }
    }
    diag::print(diag::Message::AiTable, static_cast<int32_t>(table));
    return runTable(act, table);
}

// ===========================================================================
// Choosing targets
// ===========================================================================

namespace {

// The lowest value under 10000 among selectable slots (first one wins ties).
template <class Value>
void selectLowest(ActionProcessData& act, bool skipFlying, Value value)
{
    MainProcessData& main = mainOf(act);
    int32_t best = -1;
    uint32_t lowest = 10000;
    for (int32_t i = 0; i < 16; ++i) {
        if (!selectable(main, i))
            continue;
        const UnitWork& unit = unitInSlot(i);
        if (skipFlying && unit.ailment() == ailment::Fly)
            continue;
        uint32_t candidate = value(unit);
        if (candidate < lowest) {
            lowest = candidate;
            best = i;
        }
    }
    if (best >= 0)
        markSelected(main, best);
}

template <class Test>
void selectWhere(ActionProcessData& act, Test test)
{
    MainProcessData& main = mainOf(act);
    for (int32_t i = 0; i < 16; ++i)
        if (selectable(main, i) && test(unitInSlot(i)))
            markSelected(main, i);
}

} // namespace

// nbAiSelLifeMin @ 0x00286EC0
void selectLowestHp(ActionProcessData& act)
{
    selectLowest(act, false, [](const UnitWork& u) { return uint32_t{u.hp}; });
}

// nbAiSelBaarLv @ 0x00286F88
void selectLowestLevelNotFlying(ActionProcessData& act)
{
    selectLowest(act, true, [](const UnitWork& u) { return uint32_t{u.level}; });
}

// nbAiSelLvMin @ 0x00287070
void selectLowestLevel(ActionProcessData& act)
{
    selectLowest(act, false, [](const UnitWork& u) { return uint32_t{u.level}; });
}

// nbAiSelBad @ 0x00287138
void selectAilment(ActionProcessData& act, int32_t ailment)
{
    selectWhere(act, [&](const UnitWork& u) { return u.ailment() == ailment; });
}

// nbAiSelId @ 0x002871D8
void selectDevil(ActionProcessData& act, int32_t devil)
{
    selectWhere(act, [&](const UnitWork& u) { return !u.isPlayerCharacter() && u.id == devil; });
}

// nbAiSelLight @ 0x00287288
void selectLight(ActionProcessData& act)
{
    selectWhere(act, [](const UnitWork& u) { return !u.isPlayerCharacter() && dat::alignment(u) == 1; });
}

// nbAiSelDark @ 0x00287338
void selectDark(ActionProcessData& act)
{
    selectWhere(act, [](const UnitWork& u) { return !u.isPlayerCharacter() && dat::alignment(u) == -1; });
}

// nbAiSelPlayer @ 0x002873E8
void selectDemiFiend(ActionProcessData& act)
{
    selectWhere(act, [](const UnitWork& u) { return u.isPlayerCharacter(); });
}

// nbAiSelJoken @ 0x00287478
void selectByCondition(ActionProcessData& act)
{
    MainProcessData& main = mainOf(act);
    for (int32_t i = 0; i < 16; ++i)
        if (selectable(main, i) && (act.aiselect & (1u << i)))
            markSelected(main, i);
}

// nbAiSelRnd @ 0x002874C8: everyone; the caller then picks one at random.
void selectAll(ActionProcessData& act)
{
    markAllSelectable(mainOf(act));
}

// nbAiSelAi @ 0x00286B68. The best score is found among the scored slots,
// but marked by counting *all* selectable slots, so with AI level 2 a
// skipped (immune) slot shifts the choice.
int32_t selectBest(ActionProcessData& act, int32_t, bool group)
{
    MainProcessData& main = mainOf(act);
    uint16_t level = recordOf(act).level();
    int32_t skill = 0;   // attack
    int16_t command = act.work->nowcommand;
    if (command == 1) {
        skill = act.work->nowindex;
    } else if (command != 0) {
        diag::print(diag::Message::AiNoSkill);
        return 0;
    }
    if (level == 0) {
        markAllSelectable(main);
        return 0;
    }
    if (level > 2)
        return 0;
    int32_t scores[16];
    int32_t count = 0;
    for (int32_t i = 0; i < 16; ++i) {
        if (!selectable(main, i))
            continue;
        if (level == 2) {
            uint32_t affinity = virtualAffinity(skill, self(act), i);
            if (affinity == 0x20000 || affinity == 0x10000 || affinity == 0x40000)
                continue;
        }
        int32_t score = estimateEffect(skill, self(act), i);
        if (level == 1 || score != 0)
            scores[count++] = score;
    }
    if (count == 0) {
        diag::print(diag::Message::AiNoTarget);
        return -1;
    }
    if (group) {
        markAllSelectable(main);
        return 0;
    }
    int32_t best = 0, ordinal = 0;
    for (int32_t i = 0; i < count; ++i) {
        if (best < scores[i]) {
            best = scores[i];
            ordinal = i;
        }
    }
    int32_t seen = 0;
    for (int32_t i = 0; i < 16; ++i) {
        if (selectable(main, i) && seen++ == ordinal) {
            markSelected(main, i);
            break;
        }
    }
    return 0;
}

// nbSetSingleTarget2 @ 0x00287508: selector 0 (or one that selects nobody)
// uses the AI level; then one of the selected is kept at random.
int32_t selectSingleTarget(ActionProcessData& act, int32_t selector, int32_t parameter)
{
    MainProcessData& main = mainOf(act);
    if (static_cast<uint32_t>(selector) >= 11)
        selector = 0;
    switch (selector) {
    case 1: selectLowestHp(act); break;
    case 2: selectAilment(act, parameter); break;
    case 3: selectDevil(act, parameter); break;
    case 4: selectLight(act); break;
    case 5: selectDark(act); break;
    case 6: selectDemiFiend(act); break;
    case 7: selectByCondition(act); break;
    case 8: selectAll(act); break;
    case 9: selectLowestLevelNotFlying(act); break;
    case 10: selectLowestLevel(act); break;
    default: break;
    }
    if (!anySelected(main)) {
        selector = 0;
        parameter = 0;
    }
    int32_t result = selector == 0 ? selectBest(act, parameter, false) : 0;
    int32_t candidates[16];
    int32_t count = 0;
    for (int32_t i = 0; i < 16; ++i)
        if (slot(main, i).stat & FormationStat::Selected)
            candidates[count++] = i;
    if (count) {
        int32_t chosen = candidates[sdf::GetRandInt(count)];
        for (int32_t i = 0; i < 16; ++i)
            if (i != chosen)
                slot(main, i).stat &= ~FormationStat::Selected;
    }
    return result;
}

// nbSetGroupTarget2 @ 0x00287778: any selector 1..10 takes everyone.
int32_t selectGroupTarget(ActionProcessData& act, int32_t selector, int32_t parameter)
{
    MainProcessData& main = mainOf(act);
    if (selector != 0 && static_cast<uint32_t>(selector) < 11)
        markAllSelectable(main);
    else
        selector = 0;
    if (!anySelected(main)) {
        selector = 0;
        parameter = 0;
    }
    return selector ? 0 : selectBest(act, parameter, true);
}

// nbSetAiTarget @ 0x002879F0. Calls for help target the empty slots.
int32_t selectTargets(ActionProcessData& act, int32_t selector, int32_t parameter)
{
    UnitWork* unit = act.work.get();
    int16_t command = unit->nowcommand;
    if (command != 0 && command != 1 && command != 5)
        return 0;
    if (command == 1) {
        uint16_t skill = unit->nowindex;
        if (skill == 0xde || (skill >= 0xe2 && skill < 0xe7) || skill == 0xfc) {
            prepareSummonSlots(mainOf(act), static_cast<int32_t>(act.aisummonid));
            selector = 8;
            unit = act.work.get();
        }
    }
    int32_t type, rule, area;
    targetTypeRuleArea(act, *unit, &type, &rule, &area, false, true);   // (the call Hardtype tells by its return address)
    markTargetable(act.partyindex, type, rule, area);
    int32_t result = 0;
    if (type == 0)
        result = selectSingleTarget(act, selector, parameter);
    else if (static_cast<uint32_t>(type) < 3)
        result = selectGroupTarget(act, selector, parameter);
    if (result) {
        act.work->nowcommand = 3;
        act.work->nowindex = 0;
    }
    return result;
}

// nbSetPlayerSummonFormation @ 0x0028B448: the first empty party slot
// after an occupied one becomes the summon slot, placed 150 units plus the
// neighbour's radius beyond it, facing the same way.
void prepareAllySummonSlot(MainProcessData& main)
{
    for (int32_t i = 0; i < 4; ++i)
        slot(main, i).stat &= ~FormationStat::SummonSlot;
    for (int32_t i = 1; i < 4; ++i) {
        Formation& form = slot(main, i);
        if (form.stat & FormationStat::Present)
            continue;
        const Formation& prev = slot(main, i - 1);
        form.orgpos = prev.orgpos;
        form.orgpos.x = form.orgpos.x + (prev.r + ee::Float::fromInt(100) + ee::Float::fromInt(50));
        form.pos = form.orgpos;
        form.orgrot = prev.orgrot;
        form.rot = form.orgrot;
        form.stat |= FormationStat::SummonSlot;
        return;
    }
}

// nbSetEnemySummonFormation @ 0x0028B528: the first empty enemy slots up
// to the encounter's party size become summon slots, sized for the devil.
// (The count isn't limited to the ten enemy slots.)
bool prepareSummonSlots(MainProcessData& main, int32_t devil)
{
    for (int32_t i = 4; i < 14; ++i)
        slot(main, i).stat &= ~FormationStat::SummonSlot;
    uint8_t count = dat::encount(main.encno).maxparty;
    if (!main.summonallowed || !count)
        return false;
    const UnitVisual& visual =
        *guest::table<const UnitVisual>(dat::address::UnitVisual + static_cast<uint32_t>(devil) * sizeof(UnitVisual));
    bool any = false;
    for (int32_t i = 0; i < count; ++i) {
        Formation& form = slot(main, i + 4);
        if (form.stat & FormationStat::Present)
            continue;
        form.stat |= FormationStat::SummonSlot;
        if (devil > 0)
            form.r = visual.size * visual.scale;
        any = true;
    }
    return any;
}

// nbGetSelectBit @ 0x00246B68
uint32_t selectedBits(const MainProcessData& main)
{
    uint32_t bits = 0;
    for (int32_t i = 0; i < 16; ++i) {
        const Formation& form = *guest::table<const Formation>(main.form.address + static_cast<uint32_t>(i) * sizeof(Formation));
        if (form.stat & FormationStat::Selected)
            bits |= 1u << i;
    }
    return bits;
}

// nbSetNormalSkill0 @ 0x00259018: writes into the skill tables themselves.
void setNormalAttack(UnitWork& unit)
{
    uint16_t command = static_cast<uint16_t>(unit.nowcommand);
    int32_t base;
    NormalSkill* normal = guest::table<NormalSkill>(dat::address::NormalSkill);
    if (command == 0) {
        base = 0;
        normal[0].targettype = passiveActive(unit, skill::AttackAll) ? 1 : 0;
    } else if (command == 1) {
        uint16_t skill = unit.nowindex;
        if (skill < 0xa4 || skill >= 0xa8)
            return;
        base = skill;
    } else {
        return;
    }
    uint8_t element = 0, hits = 1;
    if (!unit.isPlayerCharacter()) {
        const DevilFormat& format = dat::devilFormat(unit.id);
        element = static_cast<uint8_t>(format.attackattr);
        hits = format.attackcnt;
    }
    guest::table<SkillInfo>(dat::address::SkillInfo)[base].skillattr = static_cast<int8_t>(element);
    normal[base].targetcntmax = hits;
    normal[base].targetcntmin = hits;
    guest::table<uint8_t>(dat::address::SkillHitEffect)[base * 4 + 1] = 0;
    diag::print(diag::Message::SkillRewritten);
}

} // namespace nocturne::nb::ai
