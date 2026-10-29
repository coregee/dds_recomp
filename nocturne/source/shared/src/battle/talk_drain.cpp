// The talks' group 11 (original unit: NbNegoFlowDrain): the demon drains
// the talker. It takes HP (the drawing that would pick MP always comes up
// HP), healing itself as much; Endure or Never Yield keep the talker at 1
// HP, else it may die. Then the talk goes on as it may. Rewritten from the
// original instructions. Messages are in the demon's flow table.
#include "nocturne/battle/talk_flow.hpp"

#include <algorithm>

#include "nocturne/battle/action.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/kouka.hpp"
#include "nocturne/battle/battle_panel.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/external.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t step(uint32_t number) { return 0xb0000u | number; }
constexpr uint32_t kNoDrain = 0x20000;   // MainProcessData::stat: drains take nothing (tentative)

int32_t flowWindow(const TalkState& n) { return n.flowmsg[n.ekucyo]; }

int32_t uniqueid(const TalkState& n) { return static_cast<int32_t>(n.actdata.address); }

// Flow11_1 @ 0x00276D08
int32_t drainBegins(TalkState& n)
{
    addCandidate(n, step(2));
    return 0;
}

// Flow11_2 @ 0x00276D30: how much: HP (requesthpmp 0; MP 1, but the
// drawing is of one), the second kind of amount after group 6's 0x6002A.
int32_t howMuch(TalkState& n)
{
    addCandidate(n, step(3));
    const bool afterOffer = talkIdBack(n, 2) == 0x6002a;
    if (sdf::GetRandInt(1) == 0) {
        n.requesthpmp = 0;
        n.requestdata = afterOffer ? demonAsksHpB(n, *n.pwork, *n.ework) : demonAsksHp(n, *n.pwork, *n.ework);
    } else {
        n.requesthpmp = 1;
        n.requestdata = afterOffer ? demonAsksMpB(n, *n.pwork, *n.ework) : demonAsksMp(n, *n.pwork, *n.ework);
    }
    if (n.data->stat & kNoDrain)
        n.requestdata = 0;
    return 0;
}

// Flow11_3 @ 0x00276E20: the drain. MP: shown taken and given (and how
// much of the talker's MP it was, in percent, kept in requestdata). HP:
// the demon heals by it (up to its max), the talker loses it (held at 1 by
// Endure or Never Yield), maybe dying.
int32_t drains(TalkState& n)
{
    addCandidate(n, step(4));
    closeTalkWindow(n);
    panelPartyShow();
    diag::print(diag::Message::TalkDrain, n.requestdata);
    if (n.requesthpmp != 0) {
        makeHealPackets(0xf, uniqueid(n), *n.eform, 0, -1, n.requestdata, false);
        makeDamagePackets(0x2d, uniqueid(n), *n.pform, 3, -1, n.requestdata, 0, false, false, 0, true, 0);
        n.requestdata = n.requestdata < 1 ? 100 : n.pwork->mp * 100 / n.requestdata;
        n.waitframe = 20;
        return 0;
    }
    const UnitWork& demon = *n.ework;
    const int32_t healed = demon.hp + n.requestdata <= demon.maxhp ? n.requestdata : demon.maxhp - demon.hp;
    addTimeListHpAt(*n.actdata, n.eformindex, healed);
    makeHealPackets(0, 0, *n.eform, 0, n.requestdata, -1, false);
    addHitEffectPacket(0, 0, *n.eform, 9);
    int32_t damage = n.requestdata;
    const int32_t saver = checkEndure(n.pformindex) ? skill::Endure : checkNeverYield(n.pformindex) ? skill::NeverYield : 0;
    if (saver != 0 && damage > 0 && damage >= n.pwork->hp) {
        addSkillNamePacket(0x2d, uniqueid(n), saver);
        damage = n.pwork->hp - 1;
        markEndureUsed(n.pformindex);
    }
    const int32_t hp = n.pwork->hp;
    addTimeListHpAt(*n.actdata, n.pformindex, -std::min(damage, hp));
    const bool dies = hp <= damage;
    makeDamagePackets(0x2d, uniqueid(n), *n.pform, 3, damage, -1, 0, false, dies, 0, true, 0);
    if (dies)
        makeDeathPackets(0x4b, uniqueid(n), *n.pform, 0);
    n.waitframe = 20;
    return 0;
}

// Flow11_4 @ 0x002770A0: the talker standing goes on (11_6); fallen, 11_5.
int32_t afterDrain(TalkState& n)
{
    addCandidate(n, step(6));
    addCandidate(n, step(5));
    panelPartyHide();
    diag::print(diag::Message::TalkDrainedHp, n.pwork->hp);
    n.nextTalkId = n.candidates[n.pwork->hp == 0 ? 1 : 0];
    return 0;
}

// Flow11_5 @ 0x00277118: the talker fell: the Demi-fiend's fall ends in
// group 8's 0x80013; another's goes on (11_9).
int32_t talkerFell(TalkState& n)
{
    addCandidate(n, 0x80013);
    addCandidate(n, step(9));
    n.nextTalkId = n.candidates[(n.pwork->flag & UnitFlag::PlayerCharacter) ? 0 : 1];
    return 0;
}

// Flow11_6 @ 0x00277178: MP (11_7) or HP (11_8).
int32_t mpOrHp(TalkState& n)
{
    addCandidate(n, step(7));
    addCandidate(n, step(8));
    n.nextTalkId = n.candidates[n.requesthpmp == 1 ? 0 : 1];
    return 0;
}

// Flow11_7 @ 0x002771D8: MP drained dry, when it was under half the
// talker's: 11_9; else group 6's 0x60018.
int32_t mpDrained(TalkState& n)
{
    addCandidate(n, step(9));
    addCandidate(n, 0x60018);
    n.nextTalkId = n.candidates[n.pwork->mp == 0 && n.requestdata < 50 ? 0 : 1];
    return 0;
}

// Flow11_8 @ 0x00277248: satisfied (message 0x99 or 0x9C); on to group 6's
// 0x60018.
int32_t satisfied(TalkState& n)
{
    addCandidate(n, 0x60018);
    showTalkMessage(n, flowWindow(n), sdf::GetRandInt(2) != 0 ? 0x9c : 0x99, false);
    return 0;
}

// Flow11_9 @ 0x002772B0: not enough: it shakes its head (message 0x9D, or
// 0x9E for MP) and goes on to group 10's 0xA0001 (after 11_5) or 0xA0018
// (after 11_7).
int32_t notEnough(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = refuseMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        addCandidate(n, 0xa0001);
        addCandidate(n, 0xa0018);
        showTalkMessage(n, flowWindow(n), n.requesthpmp != 0 ? 0x9e : 0x9d, false);
        const uint32_t previous = previousTalkId(n);
        if (previous == step(5))
            n.nextTalkId = n.candidates[1];
        else if (previous == step(7))
            n.nextTalkId = n.candidates[0];
    }
    return 0;
}

} // namespace

const TalkStep kDrainSteps[10] = {
    nullptr,  drainBegins, howMuch, drains, afterDrain, talkerFell, mpOrHp, mpDrained, satisfied, notEnough,
};

// nbNegoFlowDrain @ 0x00277388
int32_t drainFlow(TalkState& n) { return kDrainSteps[n.talkId & 0xffff](n); }

} // namespace nocturne::nb
