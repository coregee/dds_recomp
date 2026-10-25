// An action's side events (original unit: nbActionProcess): counters, an
// enemy starting a conversation, a failed escape, death scripts, and the
// action's own stat bits. Rewritten from the original instructions.
//
// Many push a new action onto the battle's queue (nbPushAction): 1 an enemy
// begs for its life (inoti), 2 an enemy asks to join (binjo), 3 a free hit
// after a failed escape (koketa), 4 a counter, 5 a death script.
#include "nocturne/battle/action.hpp"

#include "nocturne/battle/buffs.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/kouka.hpp"
#include "nocturne/battle/target_select.hpp"
#include "nocturne/battle/targeting.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kForceNego = 0x2000000;   // BattleStat: talks always happen (tentative: a debug switch)
constexpr int32_t kTalkCounter = 0x10;      // buff counter 16: the enemy has already talked (Mukan)

Formation& formAt(ActionProcessData& a, int32_t formindex) { return a.data->form[formindex]; }

// Talks need a battle whose press-turn reflection field isn't 0xF0..0xF6
// (tentative: special battles; the first release has no such check), a
// moon that isn't full, and so on.
bool talkableBattle(const MainProcessData& main)
{
    const bool special = !kBuild.vanilla && static_cast<uint16_t>(static_cast<uint16_t>(main.press4_repel) - 0xf0) <= 6;
    return !special && !(main.stat & BattleStat::BossBattle);
}

bool fullMoon() { return evt::GetAgeOfMoon() == 8; }

int32_t chance(const MainProcessData& main, int32_t percent) { return (main.stat & kForceNego) ? 100 : percent; }

// The first enemy slot with someone in it (0x28FA80, no name).
Formation* firstEnemy()
{
    MainProcessData& main = *GetMainProcessData();
    for (int32_t f = kFirstEnemyFormation; f < kFormationCount; ++f)
        if (main.form[f].stat & FormationStat::Present)
            return &main.form[f];
    return nullptr;
}

} // namespace

// SetTarget @ 0x00251428: the player chooses the targets for the unit's
// command. A summon (command 6, or skill 0xDF) sets the stage to 1.
void setTarget(ActionProcessData& a)
{
    const UnitWork& unit = *a.work;
    const bool summon = unit.nowcommand == 6 || (unit.nowcommand == 1 && unit.nowindex == 0xdf);
    a.data->StageMajor = summon ? 1 : 0;
    a.data->StageMinor = 0;
    a.select = 0;
    int32_t type = 0, rule = 0, area = 0;
    targetTypeRuleArea(a, unit, &type, &rule, &area, false);
    startTargetCursor(a, a.partyindex, type, rule, area);
}

// SetAction_TARSEL @ 0x00254178
void enterTargetSelect(ActionProcessData& a) { setTarget(a); }

// SetTargetPlayer @ 0x00251EF0: the Demi-fiend as the only target.
void targetDemiFiend(ActionProcessData& a)
{
    for (int32_t f = 0; f < 16; ++f)
        formAt(a, f).stat &= ~(FormationStat::Selectable | FormationStat::Selected);
    for (int32_t f = 0; f < 16; ++f) {
        Formation& form = formAt(a, f);
        if ((form.stat & FormationStat::Present) && (form.stat & FormationStat::CheckParty) && (form.stat & 0x100) &&
            GetUnitWorkFromFormindex(f)->isPlayerCharacter()) {
            form.stat |= FormationStat::Selected;
            return;
        }
    }
}

// SetTargetParty @ 0x00251FD8: the unit in party slot `partyindex` as the only target.
void targetPartySlot(ActionProcessData& a, int32_t partyindex)
{
    for (int32_t f = 0; f < 16; ++f)
        formAt(a, f).stat &= ~(FormationStat::Selectable | FormationStat::Selected);
    for (int32_t f = 0; f < 16; ++f) {
        Formation& form = formAt(a, f);
        if ((form.stat & FormationStat::Present) && (form.stat & FormationStat::CheckParty) && form.partyindex == partyindex) {
            form.stat |= FormationStat::Selected;
            return;
        }
    }
}

// CheckArrCounter @ 0x00252060: Ahriman (first form) counters a kind of
// action of the party's once the story has unlocked it: event bits
// 0x851..0x856 for a physical attack, magic attack, healing, magic, an
// item and a summon (the action's stat bits 0x10000..0x200000).
bool checkAhrimanCounter(ActionProcessData& a)
{
    if (a.partyindex >= 4)
        return false;
    Formation& enemy = *firstEnemy();
    if (timeListDead(a, enemy.formindex))
        return false;
    if (GetUnitWorkFromFormindex(enemy.formindex)->id != devil::Ahriman1stFormBoss)
        return false;
    bool counter = false;
    for (int32_t k = 0; k < 6; ++k)
        if (evt::BitCheck(0x851 + k) && (a.stat & 0x10000u << k))
            counter = true;
    if (!counter)
        return false;
    nb::PushAction(4, enemy.partyindex, a.partyindex, 0xf3);
    diag::print(diag::Message::AhrimanCounter);
    return true;
}

// CheckCounter @ 0x002521C8: the unit hit (`from`) strikes back at `to`
// with Avenge, Retaliate or Counter (passives 0x133, 0x132, 0x131, tried in
// that order, each at 100 / its rate percent), unless `to` is down or
// `from` is shocked, frozen, asleep, bound, stunned, charmed or stoned.
bool checkCounter(ActionProcessData& a, int32_t from, int32_t to)
{
    static constexpr uint32_t passives[] = {skill::Avenge, skill::Retaliate, skill::Counter};
    static constexpr int32_t counters[] = {0xa6, 0xa5, 0xa4};
    if (timeListDead(a, to))
        return false;
    const UnitWork& unit = *GetUnitWorkFromFormindex(from);
    switch (unit.ailment()) {
    case 1: case 2: case 4: case 0x10: case 0x80: case 0x100: case 0x400: return false;
    default: break;
    }
    int32_t counter = 0;
    for (int i = 0; i < 3; ++i) {
        if (!dat::hasSkill(unit, passives[i]))
            continue;
        const int32_t rate = dat::specialSkill(passives[i]).n;
        if (rate == 0)
            divideByZeroTrap();
        if (sdf::GetRandInt(100) < 100 / rate) {
            counter = counters[i];
            break;
        }
    }
    if (counter == 0)
        return false;
    nb::PushAction(4, formAt(a, from).partyindex, formAt(a, to).partyindex, counter);
    diag::print(diag::Message::Counter);
    return true;
}

// CheckMukanNego @ 0x00252400: the last enemy who can still talk (one that
// talks, mukantype, and isn't in the stock) speaks up, from the third turn
// on, 5% of the time, once.
bool checkLastEnemyTalks(ActionProcessData& a)
{
    MainProcessData& main = *a.data;
    const UnitWork& unit = *a.work;
    if (!talkableBattle(main) || talksSwitchedOff() || !(a.party->flag & PartyFlag::EnemySide) ||
        dat::devilTalkFormat(unit.id).lastEnemyTalk == 0)
        return false;
    if (dat::findDevil(unit.id) >= 0 || fullMoon() || !dat::canTalk(unit) || !dat::canTalk(dat::globalWork().units[0]))
        return false;
    if (main.enemypcnt <= 1 || buffCounter(a.form->formindex, kTalkCounter) != 0)
        return false;
    if (!(main.stat & kForceNego) && main.turn < 3)
        return false;
    int32_t silent = 0;
    for (int32_t f = kFirstEnemyFormation; f < kFormationCount; ++f) {
        const Formation& form = main.form[f];
        if ((form.stat & FormationStat::Present) && (form.stat & FormationStat::CheckParty) && buffCounter(f, kTalkCounter) == 0)
            ++silent;
    }
    if (silent != 1 || sdf::GetRandInt(100) >= chance(main, 5))
        return false;
    addBuff(a.form->formindex, kTalkCounter, 1, false);
    return true;
}

// CheckSenseiNego @ 0x002525F0: an enemy that ambushed the party (the
// enemies moved first) opens with talk, 21 / enemies percent of the time.
bool checkAmbushTalk(ActionProcessData& a)
{
    MainProcessData& main = *a.data;
    if (!talkableBattle(main) || talksSwitchedOff() || !(main.stat & BattleStat::EnemiesFirst) || (main.stat & BattleStat::BackAttack) ||
        (main.stat & 0x100))
        return false;
    if (fullMoon() || dat::devilTalkFormat(a.work->id).ambushTalk == 0)
        return false;
    if (!dat::canTalk(*a.work) || !dat::canTalk(dat::globalWork().units[0]))
        return false;
    int32_t percent = 100;
    if (!(main.stat & kForceNego)) {
        if (main.enemypcnt == 0)
            divideByZeroTrap();
        percent = 21 / main.enemypcnt;
    }
    if (sdf::GetRandInt(100) >= percent)
        return false;
    main.stat |= 0x100;
    return true;
}

// CheckInotiNego @ 0x00252720: the last enemy, struck by the party's attack,
// skill or item and left at 24% HP or less, may beg for its life (6%), if
// it isn't above the Demi-fiend's level.
bool checkBegForLife(ActionProcessData& a)
{
    MainProcessData& main = *a.data;
    if (!talkableBattle(main) || (a.party->flag & (PartyFlag::EnemySide | PartyFlag::Inactive)) || a.partyindex >= 4)
        return false;
    if (fullMoon() || !dat::canTalk(*a.work))
        return false;
    const int16_t command = a.work->nowcommand;
    if (command < 0 || (command > 1 && command != 5))
        return false;
    if (main.enemypcnt != 1)
        return false;
    for (int32_t f = kFirstEnemyFormation; f < kFormationCount; ++f) {
        const Formation& form = main.form[f];
        if (!(form.stat & FormationStat::Present) || !(form.stat & FormationStat::Selected) ||
            !(form.stat & FormationStat::CheckParty))
            continue;
        const UnitWork& enemy = *GetUnitWorkFromFormindex(f);
        const uint16_t flag = static_cast<uint16_t>(main.party[form.partyindex].flag);
        if (!(flag & PartyFlag::Active) || (flag & 0x20) || timeListDead(a, f) ||
            dat::devilTalkFormat(enemy.id).begForLife == 0)
            continue;
        if (!(main.stat & kForceNego)) {
            if (enemy.maxhp == 0)
                divideByZeroTrap();
            if (static_cast<uint32_t>(a.timelist[f].hp) * 100u / enemy.maxhp > 24)
                continue;
        }
        if (!a.work->isPlayerCharacter() && a.work->id == enemy.id)
            continue;
        if (!dat::canTalk(enemy) || (!(main.stat & kForceNego) && enemy.level > dat::globalWork().units[0].level))
            continue;
        if (sdf::GetRandInt(100) < chance(main, 6)) {
            nb::PushAction(1, form.partyindex, a.partyindex, 0);
            diag::print(diag::Message::BegForLifeSide, form.partyindex, enemy.id);
            return true;
        }
    }
    return false;
}

// CheckBinjoNego @ 0x002529D0: after the party's action (action stat 8),
// an enemy it didn't target may ask to join (2%), if not already in the
// stock; once per enemy (party flag 0x40).
bool checkAskToJoin(ActionProcessData& a)
{
    MainProcessData& main = *a.data;
    if (!talkableBattle(main) || (a.party->flag & (PartyFlag::EnemySide | PartyFlag::Inactive)) || a.partyindex >= 4 ||
        !(a.stat & 8))
        return false;
    if (fullMoon() || !dat::canTalk(*a.work))
        return false;
    for (int32_t f = kFirstEnemyFormation; f < kFormationCount; ++f) {
        const Formation& form = main.form[f];
        if (!(form.stat & FormationStat::Present) || (form.stat & FormationStat::Selected) ||
            !(form.stat & FormationStat::CheckParty))
            continue;
        Party& party = main.party[form.partyindex];
        if (!(party.flag & PartyFlag::Active) || (party.flag & 0x20) || (party.flag & 0x40))
            continue;
        const UnitWork& enemy = *GetUnitWorkFromFormindex(f);
        if (timeListDead(a, f) || dat::devilTalkFormat(enemy.id).askToJoin == 0)
            continue;
        if (!a.work->isPlayerCharacter() && a.work->id == enemy.id)
            continue;
        if (dat::findDevil(enemy.id) >= 0 || !dat::canTalk(enemy))
            continue;
        if (sdf::GetRandInt(100) < chance(main, 2)) {
            party.flag = static_cast<int16_t>(party.flag | 0x40);
            nb::PushAction(2, form.partyindex, a.partyindex, 0);
            diag::print(diag::Message::AskToJoinSide, form.partyindex);
            return true;
        }
    }
    return false;
}

// CheckDeadScript @ 0x00252C28: an enemy the action killed whose death runs
// a script queues it (not for action type 5).
void checkDeathScripts(ActionProcessData& a)
{
    if (a.type == 5)
        return;
    for (int32_t f = kFirstEnemyFormation; f < kFormationCount; ++f) {
        Formation& form = formAt(a, f);
        if (!(form.stat & FormationStat::Present) || !timeListDead(a, f))
            continue;
        if (const int32_t script = hasDeathScript(form))
            nb::PushAction(5, form.partyindex, 0, script);
    }
}

// CheckKoketaNego @ 0x00252CD8: after the party's failed escape, a random
// enemy that can act gets a free action (not one shocked, frozen, asleep,
// bound, stunned or stoned).
bool checkFreeActionAfterEscape(ActionProcessData& a)
{
    if ((a.party->flag & (PartyFlag::EnemySide | PartyFlag::Inactive)) || a.partyindex >= 4)
        return false;
    MainProcessData& main = *a.data;
    uint8_t candidates[32];
    uint32_t count = 0;
    for (int32_t f = kFirstEnemyFormation; f < kFormationCount; ++f) {
        const Formation& form = main.form[f];
        if (!(form.stat & FormationStat::Present) || !(form.stat & FormationStat::CheckParty))
            continue;
        const uint16_t flag = static_cast<uint16_t>(main.party[form.partyindex].flag);
        if (!(flag & PartyFlag::Active) || (flag & 0x20))
            continue;
        const UnitWork& enemy = *GetUnitWorkFromFormindex(f);
        if (timeListDead(a, f))
            continue;
        switch (enemy.ailment()) {
        case 1: case 2: case 4: case 0x10: case 0x100: case 0x400: continue;
        default: break;
        }
        candidates[count++] = static_cast<uint8_t>(form.partyindex);
    }
    if (count == 0)
        return false;
    const int8_t chosen = static_cast<int8_t>(candidates[sdf::GetRandInt(static_cast<int32_t>(count))]);
    nb::PushAction(3, chosen, a.partyindex, 0);
    diag::print(diag::Message::EscapeErrParty);
    return true;
}

// KyouseiPress @ 0x00252EA8: the press turns end at once (no icons left);
// the command menu closes.
void debugEndPressTurns(ActionProcessData& a)
{
    MainProcessData& main = *a.data;
    main.press4_p = 0;
    main.press4_ten = 0;
    if (main.CommandMenuProcessID)
        dds3::KillProcess(main.CommandMenuProcessID, 0);
}

// DokodemoPoa @ 0x00252EE8: every enemy dies at once; the command menu
// closes.
void debugWinBattle(ActionProcessData& a)
{
    for (int32_t f = kFirstEnemyFormation; f < kFormationCount; ++f) {
        Formation& form = formAt(a, f);
        if ((form.stat & FormationStat::Present) && (form.stat & FormationStat::CheckParty)) {
            nb::MakeDeathVisualPackets(0, static_cast<int32_t>(guest::addressOf(&a)), &form, 0, 1);
            setTimeList(a, f, 0, 30, 30);
            queueDeath(a, f);
        }
    }
    if (a.data->CommandMenuProcessID)
        dds3::KillProcess(a.data->CommandMenuProcessID, 0);
}

namespace {

// HP or MP effect types that hurt (and those that heal).
bool hurts(uint16_t type)
{
    switch (type) {
    case 1: case 3: case 4: case 6: case 8: case 10: case 12: case 13: case 14: return true;
    default: return false;
    }
}
bool heals(uint16_t type)
{
    switch (type) {
    case 2: case 5: case 7: case 9: case 11: case 15: return true;
    default: return false;
    }
}

} // namespace

// SetNowActionStat @ 0x00252FB8: what the party's action does, as stat bits
// (printed by SetAction_END): 0x10000 a physical attack, 0x20000 a magic
// attack (damage or an ailment), 0x40000 healing, 0x80000 magic, 0x100000
// an item, 0x200000 a summon (programs 2 and 3, or command 6). The skill's
// healing types are read whatever the command.
void noteActionKind(ActionProcessData& a, int32_t comm, int32_t nskill)
{
    nskill = checkedSkill(nskill);   // (the acting skill, by version)
    if (a.partyindex >= 4)
        return;
    const NormalSkill& skill = dat::normalSkill(nskill);
    if (comm == 0) {
        a.stat |= 0x10000;
    } else if (comm == 1 && skill.damageClass == 0) {
        if (hurts(skill.hptype) || hurts(skill.mptype))
            a.stat |= 0x10000;
    }
    if (comm == 1 && skill.damageClass == 1) {
        if (hurts(skill.hptype) || hurts(skill.mptype) || skill.badtype == 1 || skill.badtype == 3)
            a.stat |= 0x20000;
    }
    if (heals(skill.hptype) || heals(skill.mptype))
        a.stat |= 0x40000;
    if (comm == 1 && skill.damageClass == 1)
        a.stat |= 0x80000;
    if (comm == 5)
        a.stat |= 0x100000;
    if ((comm == 1 && (skill.program == 2 || skill.program == 3)) || comm == 6)
        a.stat |= 0x200000;
}

} // namespace nocturne::nb
