// What a unit does when an ailment takes its turn (original unit: nbBadAi).
// Rewritten from the original instructions.
#include "nocturne/battle/bad_ai.hpp"

#include "nocturne/battle/ai.hpp"
#include "nocturne/battle/calc.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/targeting.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/types.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

namespace address {
constexpr uint32_t RituList = 0x00575490;     // BadRitu[]
constexpr uint32_t RituCount = 0x00551558;    // int32 (gp-relative)
} // namespace address

BadRitu* rituList() { return guest::table<BadRitu>(address::RituList); }
int32_t& rituCount() { return *guest::table<int32_t>(address::RituCount); }

// The status line for a panicked or charmed unit (other ailments show none).
void ailmentMessage(ActionProcessData& a, int32_t panic, int32_t charm)
{
    const UnitWork& unit = *a.work;
    switch (unit.ailment()) {
    case static_cast<uint16_t>(Ailment::Panic): nbSetJyokyoMes(a, panic, 1, unit.id); break;
    case static_cast<uint16_t>(Ailment::Charm): nbSetJyokyoMes(a, charm, 1, unit.id); break;
    default: break;
    }
}

// Status line messages ("<devil> is ...")
constexpr int32_t kMesPanicAct = 0x2e, kMesCharmAct = 0x36;
constexpr int32_t kMesPanicWait = 0x30, kMesCharmWait = 0x38;
constexpr int32_t kMesCursedAttack = 0x4a, kMesCursedDamage = 0x4c;

} // namespace

// ---- targets ---------------------------------------------------------------------------------

// SetSingleTarget @ 0x0028E3C8: one of the selectable slots at random.
void SetSingleTarget(ActionProcessData& a)
{
    int8_t candidates[16];
    uint32_t count = 0;
    for (int f = 0; f < 16; ++f)
        if (a.data->form[f].stat & FormationStat::Selectable)
            candidates[count++] = static_cast<int8_t>(f);
    if (count > 0) {
        const int32_t pick = candidates[sdf::GetRandInt(static_cast<int32_t>(count))];
        a.data->form[pick].stat |= FormationStat::Selected;
    }
}

// SetGroupTarget @ 0x0028E470: every selectable slot.
void SetGroupTarget(ActionProcessData& a)
{
    for (int f = 0; f < 16; ++f) {
        Formation& form = a.data->form[f];
        if (form.stat & FormationStat::Selectable)
            form.stat |= FormationStat::Selected;
    }
}

// SetTarget @ 0x0028E4B0: targets for the unit's command (`rev`: from the
// other side's point of view, as the ailment turns the unit around);
// false when there are none.
bool SetTarget(ActionProcessData& a, int32_t rev)
{
    int32_t type = 0, rule = 0, area = 0;
    targetTypeRuleArea(a, *a.work, &type, &rule, &area, rev != 0);
    if (!markTargetable(a.partyindex, type, rule, area))
        return false;
    if (type == 0)
        SetSingleTarget(a);
    else if (type >= 0 && type < 3)
        SetGroupTarget(a);
    a.select = ai::selectedBits(*a.data);
    return true;
}

// ---- skills -----------------------------------------------------------------------------------

// CheckBadActionSkill @ 0x0028E560: type 2 the healing skills 0x24..0x29,
// type 3 the buffs 0x40..0x44.
bool CheckBadActionSkill(int32_t skill, int32_t type)
{
    if (type == 2)
        return skill >= 0x24 && skill < 0x2a;
    if (type == 3)
        return skill >= 0x40 && skill < 0x45;
    return false;
}

// GetBadActionSkill @ 0x0028E5C8: one of the unit's skills of that type at
// random: from its skill list on the player's side, from its devil's AI
// tables on the enemy's.
int32_t GetBadActionSkill(ActionProcessData& a, int32_t type)
{
    uint16_t candidates[64];
    uint32_t count = 0;
    const UnitWork& unit = *a.work;
    if (isPlayerSide(a.form->formindex)) {
        for (int i = 0; i < unit.skillcnt; ++i)
            if (CheckBadActionSkill(unit.skill[i], type))
                candidates[count++] = unit.skill[i];
    } else {
        for (const auto& table : dat::devilAI(unit.id).aitable)
            for (const AiAction& action : table)
                if (action.skill && !(action.skill & 0x8000) && CheckBadActionSkill(action.skill, type))
                    candidates[count++] = action.skill;
    }
    if (count == 0)
        return -1;
    return static_cast<int16_t>(candidates[sdf::GetRandInt(static_cast<int32_t>(count))]);
}

// ---- the actions ---------------------------------------------------------------------------

namespace {

// BadKaja / BadKaifuku: a skill of the type, at targets as if from the
// other side.
int32_t castSkill(ActionProcessData& a, int32_t type)
{
    const int32_t skill = GetBadActionSkill(a, type);
    if (skill < 0)
        return 1;
    UnitWork& unit = *a.work;
    unit.nowindex = static_cast<uint16_t>(skill);
    unit.nowcommand = 1;   // a skill
    if (!SetTarget(a, 1))
        return 1;
    ailmentMessage(a, kMesPanicAct, kMesCharmAct);
    return 0;
}

} // namespace

// BadKaja @ 0x0028E758
int32_t BadKaja(ActionProcessData& a) { return castSkill(a, 3); }

// BadKaifuku @ 0x0028E818
int32_t BadKaifuku(ActionProcessData& a) { return castSkill(a, 2); }

// BadAttack @ 0x0028E8D8: an attack at targets as if from the other side.
int32_t BadAttack(ActionProcessData& a)
{
    UnitWork& unit = *a.work;
    unit.nowindex = 0;
    unit.nowcommand = 0;   // attack
    if (!SetTarget(a, 1))
        return 1;
    if (isCursed(a.form->formindex))
        nbSetJyokyoMes(a, kMesCursedAttack, 1, a.work->id);
    else
        ailmentMessage(a, kMesPanicAct, kMesCharmAct);
    a.stat |= 0x200;
    return 0;
}

// BadMaka @ 0x0028E9B8: skill 0xF7, throwing Macca away; only with Macca
// on hand on the player's side, and once a battle for an enemy.
int32_t BadMaka(ActionProcessData& a)
{
    if (isPlayerSide(a.form->formindex) && dat::globalWork().maka == 0)
        return 1;
    UnitWork& unit = *a.work;
    Party& party = *a.party;
    if (unit.isEnemy() && (party.flag & PartyFlag::ThrewMacca))
        return 1;
    party.flag = static_cast<int16_t>(party.flag | PartyFlag::ThrewMacca);
    unit.nowindex = 0xf7;
    unit.nowcommand = 1;   // a skill
    if (!SetTarget(a, 0))
        return 1;
    ailmentMessage(a, kMesPanicAct, kMesCharmAct);
    return 0;
}

// BadNego @ 0x0028EAB8: on the player's side, talks to the enemy.
int32_t BadNego(ActionProcessData& a)
{
    if (!isPlayerSide(a.form->formindex))
        return 1;
    UnitWork& unit = *a.work;
    unit.nowcommand = 4;   // talk
    unit.nowindex = 0x180;
    a.negotype = 6;
    if (!SetTarget(a, 0))
        return 1;
    ailmentMessage(a, kMesPanicAct, kMesCharmAct);
    return 0;
}

// BadReturn @ 0x0028EB80: a devil (not the Demi-fiend, not a special unit
// 0x100 and up) goes back to the stock.
int32_t BadReturn(ActionProcessData& a)
{
    UnitWork& unit = *a.work;
    if (unit.isPlayerCharacter() || unit.id >= 0x100)
        return 1;
    unit.nowindex = 0;
    unit.nowcommand = 7;   // return / escape
    ailmentMessage(a, kMesPanicAct, kMesCharmAct);
    return 0;
}

// BadBadWait @ 0x0028EC18: loses the turn.
int32_t BadBadWait(ActionProcessData& a)
{
    UnitWork& unit = *a.work;
    unit.nowcommand = 8;
    unit.nowindex = 0;
    ailmentMessage(a, kMesPanicWait, kMesCharmWait);
    return 0;
}

// BadDamage @ 0x0028EC90: the curse hurts the unit.
int32_t BadDamage(ActionProcessData& a)
{
    UnitWork& unit = *a.work;
    unit.nowcommand = 10;
    unit.nowindex = 0;
    nbSetJyokyoMes(a, kMesCursedDamage, 1, unit.id);
    return 0;
}

// ---- choosing ------------------------------------------------------------------------------

// GetBadAiAction @ 0x0028ECC8: an action drawn by weight.
int32_t GetBadAiAction()
{
    const BadRitu* list = rituList();
    const int32_t count = rituCount();
    uint32_t total = 0;
    for (int32_t i = 0; i < count; ++i)
        total += static_cast<uint32_t>(list[i].ritu);
    if (total == 0)
        return -1;
    const int32_t roll = sdf::GetRandInt(static_cast<int32_t>(total));
    int32_t sum = 0;
    for (int32_t i = 0; i < count; ++i) {
        if (list[i].ritu == 0)
            continue;
        sum += list[i].ritu;
        if (roll < sum)
            return list[i].type;
    }
    return kBadWait2;
}

// AddRituList @ 0x0028ED98
void AddRituList(int32_t type, int32_t ritu)
{
    BadRitu& entry = rituList()[rituCount()];
    entry.type = type;
    entry.ritu = ritu;
    ++rituCount();
}

// MakeRituList @ 0x0028EDC8: the actions and their weights.
//   charmed:             attack 40, heal 20, buff 20, wait 20
//   cursed:              attack 50, hurt itself 50
//   otherwise, by who the unit is:
//     the Demi-fiend:    throw Macca 20, talk 30 (not in a boss battle), wait 20
//     an ally devil:     throw Macca 20, talk 20 (not in a boss battle), return 10, wait 20
//     an enemy:          throw Macca 30, return 20, wait 40
// A panicked unit gets the last set: the original skips the charm state
// for panic (it is set in a branch delay slot that panic's branch doesn't
// reach), and the curse isn't checked either. The list is printed as a
// debug message.
void MakeRituList(ActionProcessData& a)
{
    enum { kOther, kCharmed, kCursed } state = kOther;
    const uint32_t ailment = badStat(a.form->formindex);
    if (ailment == static_cast<uint32_t>(Ailment::Charm))
        state = kCharmed;
    else if (ailment != static_cast<uint32_t>(Ailment::Panic) && isCursed(a.form->formindex))
        state = kCursed;

    rituCount() = 0;
    const UnitWork& unit = *a.work;
    const bool boss = (a.data->stat & BattleStat::BossBattle) != 0;
    for (int32_t type = 0; type <= 9; ++type) {
        switch (state) {
        case kCharmed:
            if (type == kBadAttack)
                AddRituList(type, 40);
            else if (type == kBadKaifuku || type == kBadKaja || type == kBadWait2)
                AddRituList(type, 20);
            break;
        case kCursed:
            if (type == kBadAttack || type == kBadDamage)
                AddRituList(type, 50);
            break;
        case kOther:
            if (unit.isPlayerCharacter()) {
                if (type == kBadNego && !boss)
                    AddRituList(type, 30);
                else if (type == kBadMaka || type == kBadWait2)
                    AddRituList(type, 20);
            } else if (!unit.isEnemy()) {
                if ((type == kBadNego && !boss) || type == kBadMaka || type == kBadWait2)
                    AddRituList(type, 20);
                else if (type == kBadReturn)
                    AddRituList(type, 10);
            } else {
                if (type == kBadReturn)
                    AddRituList(type, 20);
                else if (type == kBadMaka)
                    AddRituList(type, 30);
                else if (type == kBadWait2)
                    AddRituList(type, 40);
            }
            break;
        }
    }
    for (int32_t i = 0; i < rituCount(); ++i)
        diag::print(diag::Message::BadRitu, rituList()[i].type, rituList()[i].ritu);
}

// nbRunBadAi @ 0x0028F0A0: draws actions until one can be done. An action
// that can't is struck from the list; after ten tries the unit waits.
int32_t nbRunBadAi(ActionProcessData& a)
{
    int32_t failed = 1;
    MakeRituList(a);
    for (int32_t tries = 1;; ++tries) {
        const int32_t type = GetBadAiAction();
        switch (type) {
        case kBadWait:
        case kBadWait2: failed = BadBadWait(a); break;
        case kBadAttack: failed = BadAttack(a); break;
        case kBadKaifuku: failed = BadKaifuku(a); break;
        case kBadKaja: failed = BadKaja(a); break;
        case kBadMaka: failed = BadMaka(a); break;
        case kBadNego: failed = BadNego(a); break;
        case kBadReturn: failed = BadReturn(a); break;
        case kBadDamage: failed = BadDamage(a); break;
        case kBadNothing: break;
        default: failed = 1; break;
        }
        if (type >= 0 && failed) {
            BadRitu* list = rituList();
            for (int32_t i = 0; i < rituCount(); ++i) {
                if (list[i].type == type) {
                    list[i].ritu = 0;
                    break;
                }
            }
        }
        if (tries > 10) {
            failed = 0;
            BadBadWait(a);
        }
        if (!failed)
            return 0;
    }
}

// ---- the status line ---------------------------------------------------------------------

// nbGetJyokyoMes @ 0x00259300: each message has a second form, used when
// the sides are swapped (BattleStat 8).
int32_t nbGetJyokyoMes(const MainProcessData& data, int32_t jyokyomes)
{
    return (data.stat & BattleStat::InitiativeRolled) ? jyokyomes + 1 : jyokyomes;
}

// nbSetJyokyoMes @ 0x002592B0
void nbSetJyokyoMes(ActionProcessData& a, int32_t jyokyomes, int32_t var_id, int32_t var_ind)
{
    a.jyokyomes = nbGetJyokyoMes(*a.data, jyokyomes);
    a.jyo_varid = var_id;
    a.jyo_varind = var_ind;
}

} // namespace nocturne::nb
