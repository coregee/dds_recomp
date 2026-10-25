// Which combatants an action can target (original unit: nbCalc / nbTarSel).
#include "nocturne/battle/targeting.hpp"

#include "nocturne/address.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kTargetSelectName = addr(0x005442b8);   // "nb_tarsel"

Formation& slot(const MainProcessData& main, int32_t index)
{
    return *guest::table<Formation>(main.form.address + static_cast<uint32_t>(index) * sizeof(Formation));
}

} // namespace

// nbGetItemSkillNo @ 0x00259C48: the roll for item 1 still happens.
int32_t itemSkillFor(const ActionProcessData& act, int32_t item)
{
    int32_t skill = dat::itemSkill(item);
    return item == 1 ? act.massuruid : skill;
}

// nbGetTargetTypeRuleArea @ 0x00258DE8. `fromAi`: called by the AI's target
// choice, which a version may tell by the return address.
void targetTypeRuleArea(const ActionProcessData& act, const UnitWork& unit, int32_t* type, int32_t* rule,
                        int32_t* area, bool reverse, bool fromAi)
{
    int32_t t = 0, r = 0, a = 0;
    switch (unit.nowcommand) {
    case 0:   // attack
        r = reverse ? 2 : 0;
        a = reverse ? 1 : 2;
        if (passiveActive(unit, skill::AttackAll) && !reverse)
            t = 1;
        break;
    case 1:   // skill
    case 5: { // item
        int32_t skill = unit.nowcommand == 1 ? unit.nowindex : itemSkillFor(act, unit.nowindex);
        const NormalSkill& record = dat::normalSkill(skill);
        uint8_t targettype = record.targettype, targetrule = record.targetrule;
        adjustSkillTarget(skill, fromAi, targettype, targetrule);
        if (targettype < 3)
            t = targettype;
        if (record.targetarea & 1)
            a = reverse ? 2 : 1;
        a |= record.targetarea & 2;
        r = targetrule & 15;
        break;
    }
    case 4:
        a = 2;
        break;
    case 6: {
        const MainProcessData& main = *act.data;
        if (!(main.stat & BattleStat::InitiativeRolled)) {
            r = summonRule(unit, main);
            a = 1;
        }
        break;
    }
    default:
        break;
    }
    if (type) *type = t;
    if (rule) *rule = r;
    if (area) *area = a;
}

// GetTarSelProcessData @ 0x0025D690
TargetCursor& targetSelectData()
{
    return *guest::table<TargetCursor>(dds3::GetProcessData(dds3::SearchProcessName(kTargetSelectName)));
}

// CheckFormCursor @ 0x0025DA78. Slots 0..3 are the player's side, 4..13 the
// enemies'; BattleStat 0x8 swaps which counts as "own".
bool canTarget(int32_t self, int32_t type, int32_t rule, int32_t area, int32_t target)
{
    const MainProcessData& main = *targetSelectData().data;
    const Formation& candidate = slot(main, target);
    bool swapped = (main.stat & BattleStat::InitiativeRolled) != 0;
    bool enemySlot = static_cast<uint32_t>(target - 4) < 10;
    bool playerSlot = target < 4;
    if (type != 2 && (area & 3) != 3) {
        bool allowed = false;
        if (area & 1)
            allowed = swapped ? enemySlot : playerSlot;
        else if (area & 2)
            allowed = swapped ? playerSlot : enemySlot;
        if (!allowed)
            return false;
    }
    if ((rule & 1) && self != target)
        return false;
    if ((rule & 2) && self == target)
        return false;
    uint32_t stat = candidate.stat;
    if (!(stat & FormationStat::Present) && !((rule & 4) && (stat & FormationStat::SummonSlot)))
        return false;
    if ((rule & 8) && (stat & FormationStat::Present))
        return false;
    if (stat & FormationStat::CheckParty) {
        const Party& party = main.party[candidate.partyindex];
        if (party.flag & 0x38)
            return false;
    }
    return true;
}

// nbSetSelectOkMark @ 0x0025DC00. The other side's list is sorted by
// Formation::orgpos.x with a simple exchange sort (not stable).
bool markTargetable(int32_t partyIndex, int32_t type, int32_t rule, int32_t area)
{
    TargetCursor& select = targetSelectData();
    select.friendcnt = 0;
    select.enemycnt = 0;
    for (int32_t candidate = 0; candidate < 16; ++candidate) {
        const MainProcessData& main = *select.data;
        Formation& form = slot(main, candidate);
        int32_t self = main.party[partyIndex].formindex;
        form.stat &= ~(FormationStat::Selectable | FormationStat::Selected);
        if (!canTarget(self, type, rule, area, candidate))
            continue;
        form.stat |= FormationStat::Selectable;
        if (candidate < 14) {
            bool own = (candidate < 4) == !(main.stat & BattleStat::InitiativeRolled);
            if (own)
                select.friendno[select.friendcnt++] = static_cast<int8_t>(candidate);
            else
                select.enemyno[select.enemycnt++] = static_cast<int8_t>(candidate);
        }
    }
    const MainProcessData& main = *select.data;
    for (int32_t i = 0; i < select.enemycnt - 1; ++i) {
        for (int32_t j = i + 1; j < select.enemycnt; ++j) {
            int8_t first = select.enemyno[i], next = select.enemyno[j];
            if (slot(main, next).orgpos.x < slot(main, first).orgpos.x) {
                select.enemyno[i] = next;
                select.enemyno[j] = first;
            }
        }
    }
    return select.friendcnt + select.enemycnt != 0;
}

} // namespace nocturne::nb
