// The talks' group 2 (original unit: NbNegoFlowFullMoon): a talk under a
// full Kagutsuchi. Some demons talk as usual; some won't talk at all; the
// rest, excited, ask one question and, pleased with the answer, join the
// party or hand over Macca; displeased, they leave or attack. Rewritten
// from the original instructions. Messages are in the demon's flow table,
// the question table for its speech style, or the help table.
#include "nocturne/battle/talk_flow.hpp"

#include "nocturne/battle/camera.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t step(uint32_t number) { return 0x20000u | number; }

int32_t flowWindow(const TalkState& n) { return n.flowmsg[n.ekucyo]; }

// Demons that won't talk under it without a word of refusal first.
bool silentUnderMoon(uint16_t id)
{
    return id == devil::Gurr || (id >= devil::Flaemis && id <= devil::Erthys) || id == devil::Aciel ||
           id == devil::Arahabaki;
}

bool behindOnStat1(const TalkState& n)
{
    return dat::param(*n.pwork, Param::Unused1) < dat::param(*n.ework, Param::Unused1);
}

} // namespace

// Flow2_1 @ 0x00274228: who talks: the moonproof as usual (0x10020); Tyrants,
// Viles, Elements, Mitamas and the silent won't (2_2); the others half the
// time (2_3, a question).
int32_t moonDecides(TalkState& n)
{
    addCandidate(n, step(3));
    addCandidate(n, step(2));
    addCandidate(n, 0x10020);
    const uint16_t id = n.ework->id;
    if (moonproof(id)) {
        n.nextTalkId = n.candidates[2];
        return 0;
    }
    const Race race = dat::race(*n.ework);
    if (race == Race::Tyrant || race == Race::Vile || silentUnderMoon(id) || race == Race::Element ||
        race == Race::Mitama) {
        n.nextTalkId = n.candidates[1];
        return 0;
    }
    n.nextTalkId = n.candidates[static_cast<int32_t>(sdf::GetRandInt(100)) < 50 ? 1 : 0];
    return 0;
}

// Flow2_2 @ 0x002743E8: it shakes its head (but the silent) and refuses
// (message 0x1A or 0x1B); the talk ends (result 1).
int32_t moonRefuses(TalkState& n)
{
    if (n.talkPhase == 0) {
        if (!silentUnderMoon(n.ework->id)) {
            n.waitframe = refuseMotion(n, *n.eform);
            return 0;
        }
    } else if (n.talkPhase != 1) {
        return 0;
    }
    showTalkMessage(n, flowWindow(n), 0x1a + static_cast<int32_t>(sdf::GetRandInt(2)), false);
    return 1;
}

// Flow2_3 @ 0x002744B8
int32_t moonQuestionBegins(TalkState& n)
{
    addCandidate(n, step(4));
    return 0;
}

// Flow2_4 @ 0x002744E0: the question's kind (counted in the player's
// answers, as in group 7).
int32_t moonPicksQuestion(TalkState& n)
{
    addCandidate(n, step(5));
    n.qtype = questionType(*n.ework);
    uint8_t& asked = dat::globalWork().questionAnswers[n.qtype];
    if (asked != 0xff)
        ++asked;
    return 0;
}

// Flow2_5 @ 0x00274540: the question and its answers: one of its own set's
// first two (0xB, 0x11), or the kind's (5, 7, 3); on to 2_6.
int32_t moonAsks(TalkState& n)
{
    if (n.talkPhase == 0) {
        int32_t message = 0;
        n.qindex = 0;
        switch (n.qtype) {
        case 0:
            n.qindex = static_cast<int32_t>(sdf::GetRandInt(2));
            message = n.qindex != 0 ? 0x11 : 0xb;
            break;
        case 1: message = 5; break;
        case 2: message = 7; break;
        case 3: message = 3; break;
        default: break;
        }
        showTalkMessage(n, n.questionmsg, message, false);
    } else if (n.talkPhase == 1) {
        int32_t message = 0;
        switch (n.qtype) {
        case 0: message = n.qindex != 0 ? 0x12 : 0xc; break;
        case 1: message = 6; break;
        case 2: message = 8; break;
        case 3: message = 4; break;
        default: break;
        }
        showTalkMessage(n, n.questionmsg, message, true);
        addCandidate(n, step(6));
    }
    return 0;
}

// Flow2_6 @ 0x00274690: is it pleased? (2_7 yes, 2_13 no.) Its own
// question as in group 7; a question of a kind seven in ten (three behind
// on stat 1), the answer moving the player toward a Reason.
int32_t moonJudges(TalkState& n)
{
    addCandidate(n, step(7));
    addCandidate(n, step(13));
    int32_t chance = 50;
    if (n.qtype == 0) {
        const OwnQuestion& q = guest::table<const OwnQuestion>(kOwnQuestionAnswers)[n.ekucyo * 7 + n.qindex];
        if (q.judge == 0 || q.judge == 1) {
            const bool behind = q.judge == 0 ? behindOnStat1(n) : n.pwork->level < n.ework->level;
            const int32_t first = behind ? q.chanceBehind : q.chanceAhead;
            chance = n.nowselect != 0 ? 100 - first : first;
        }
    } else if (n.qtype >= 0 && n.qtype <= 3) {
        chance = behindOnStat1(n) ? 30 : 70;
    }
    const int32_t roll = static_cast<int32_t>(sdf::GetRandInt(100));
    if (n.qtype >= 1 && n.qtype <= 3) {
        const int32_t entry = n.ekucyo * 36 + (n.qtype % 3) * 3 + n.nowselect;
        dat::addReasonPoints(guest::table<const QuestionReason>(kQuestionReasons)[entry].reason, 1);
    }
    n.nextTalkId = n.candidates[roll < chance ? 0 : 1];
    return 0;
}

// Flow2_7 @ 0x00274908: pleased, it nods.
int32_t moonPleased(TalkState& n)
{
    addCandidate(n, step(8));
    n.waitframe = agreeMotion(n, *n.eform);
    return 0;
}

// Flow2_8 @ 0x00274948
int32_t moonPleasedGoesOn(TalkState& n)
{
    addCandidate(n, step(9));
    return 0;
}

// Flow2_9 @ 0x00274970: says so (by the question and the answer).
int32_t moonSaysPleased(TalkState& n)
{
    addCandidate(n, step(10));
    int32_t message = 0;
    if (n.qtype == 0)
        message = (n.qindex == 0 ? 0xd : 0x13) + (n.nowselect != 0 ? 2 : 0);
    else if (n.qtype >= 0 && n.qtype <= 3)
        message = 9;
    showTalkMessage(n, n.questionmsg, message, false);
    return 0;
}

// Flow2_10 @ 0x00274A10: it hands over Macca (message 0x29, 2_11) or joins
// (0x2A, 2_12): Macca seven in ten; never for Wilders, Haunts and Foul;
// always when one like it is in the stock, the stock is full or it is above
// the Demi-fiend's level, and from Tyrants and Viles.
int32_t moonGiftOrJoin(TalkState& n)
{
    addCandidate(n, step(11));
    addCandidate(n, step(12));
    int32_t chance = 70;
    const Race race = dat::race(*n.ework);
    if (race == Race::Wilder || race == Race::Haunt || race == Race::Foul)
        chance = 0;
    if (dat::findDevil(n.ework->id) >= 0)
        chance = 100;
    if (dat::isStockFull())
        chance = 100;
    if (dat::playerLevel() < n.ework->level)
        chance = 100;
    if (race == Race::Tyrant || race == Race::Vile || static_cast<int32_t>(sdf::GetRandInt(100)) < chance) {
        showTalkMessage(n, flowWindow(n), 0x29, false);
        n.nextTalkId = n.candidates[0];
    } else {
        showTalkMessage(n, flowWindow(n), 0x2a, false);
        n.nextTalkId = n.candidates[1];
    }
    return 0;
}

// Flow2_11 @ 0x00274B98: "got Macca" (help message 3), as much as it
// would give for a gift.
int32_t moonGivesMacca(TalkState& n)
{
    addCandidate(n, 0xa001c);
    n.getmakka = demonGivesMaccaB(n, *n.pwork, *n.ework);
    setMaccaVariable(n.helpmsg, n.getmakka);
    showTalkMessage(n, n.helpmsg, 3, false);
    dat::addMacca(n.getmakka);
    return 0;
}

// Flow2_12 @ 0x00274C08: it joins (help message 9; on to 9_7).
int32_t moonJoins(TalkState& n)
{
    addCandidate(n, 0x90007);
    showTalkMessage(n, n.helpmsg, 9, false);
    return 0;
}

// Flow2_13 @ 0x00274C50: displeased, it shakes its head and says so.
int32_t moonDispleased(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = refuseMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        addCandidate(n, step(14));
        int32_t message = 0;
        if (n.qtype == 0)
            message = (n.qindex == 0 ? 0xe : 0x14) + (n.nowselect != 0 ? 2 : 0);
        else if (n.qtype >= 0 && n.qtype <= 3)
            message = 10;
        showTalkMessage(n, n.questionmsg, message, false);
    }
    return 0;
}

// Flow2_14 @ 0x00274D18: it leaves (message 0x2E, 2_15) or attacks (0x2F,
// 2_16), at random.
int32_t moonLeavesOrAttacks(TalkState& n)
{
    addCandidate(n, step(15));
    addCandidate(n, step(16));
    cameraOnTalkTarget(*n.eform);
    if (sdf::GetRandInt(2) == 0) {
        showTalkMessage(n, flowWindow(n), 0x2f, false);
        n.nextTalkId = n.candidates[1];
    } else {
        showTalkMessage(n, flowWindow(n), 0x2e, false);
        n.nextTalkId = n.candidates[0];
    }
    return 0;
}

// Flow2_15 @ 0x00274DB8: it leaves (help message 1).
int32_t moonLeaves(TalkState& n)
{
    addCandidate(n, 0xa001d);
    showTalkMessage(n, n.helpmsg, 1, false);
    return 0;
}

// Flow2_16 @ 0x00274E00: it attacks (result 4), unless the talk was a
// Death Pact and the one talking still stands: then group 10's 0xA0021.
int32_t moonAttacks(TalkState& n)
{
    if (n.talkSkill != skill::DeathPact || n.pwork->hp == 0)
        return 4;
    addCandidate(n, 0xa0021);
    n.temp_param[0] = 4;
    return 0;
}

const TalkStep kFullMoonSteps[17] = {
    nullptr,          moonDecides,    moonRefuses,      moonQuestionBegins, moonPicksQuestion, moonAsks,
    moonJudges,       moonPleased,    moonPleasedGoesOn, moonSaysPleased,   moonGiftOrJoin,    moonGivesMacca,
    moonJoins,        moonDispleased, moonLeavesOrAttacks, moonLeaves,      moonAttacks,
};

// nbNegoFlowFullMoon @ 0x00274E60
int32_t fullMoonFlow(TalkState& n) { return kFullMoonSteps[n.talkId & 0xffff](n); }

} // namespace nocturne::nb
