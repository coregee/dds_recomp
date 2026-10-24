// The talks' group 13 (original unit: NbNegoFlowSensei): a demon that
// ambushed the party opens with talk. It asks a question (group 7) or
// demands an item; refused, or not given what it asked, it fights (result
// 1) or, half the time when refused, lets the party go. Rewritten from the
// original instructions. Messages are numbers in the demon's flow table.
#include "nocturne/battle/talk_flow.hpp"

#include "nocturne/data/ids.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t step(uint32_t number) { return 0xd0000u | number; }

int32_t flowWindow(const TalkState& n) { return n.flowmsg[n.ekucyo]; }

void showFlowMessage(TalkState& n, int32_t message, bool select = false) { showTalkMessage(n, flowWindow(n), message, select); }

// Flow13_1 @ 0x00278748: on to the first group's step 0x1001F, this
// group's step 2 noted for later (workid[3]).
int32_t ambushOpens(TalkState& n)
{
    addCandidate(n, 0x1001f);
    n.workid[3] = step(2);
    return 0;
}

// Flow13_2 @ 0x00278788: a question (13_3) or an item (13_4), at random;
// Wilder, Haunt and Foul demons always want an item.
int32_t questionOrItem(TalkState& n)
{
    addCandidate(n, step(3));
    addCandidate(n, step(4));
    n.nextTalkId = n.candidates[sdf::GetRandInt(2)];
    const Race race = dat::race(*n.ework);
    if (race == Race::Wilder || race == Race::Haunt || race == Race::Foul)
        n.nextTalkId = n.candidates[1];
    return 0;
}

// Flow13_3 @ 0x00278828: a question (message 0xFE; on to group 7, whose
// outcomes go on to 0xC001A or 13_11).
int32_t asksQuestion(TalkState& n)
{
    addCandidate(n, 0x70001);
    n.workid[4] = 0xc001a;
    n.workid[5] = step(11);
    showFlowMessage(n, 0xfe);
    return 0;
}

// Flow13_4 @ 0x00278890: it demands an item (message 0xFF).
int32_t demandsItem(TalkState& n)
{
    addCandidate(n, step(5));
    n.requesttype = 0;
    n.requestdata = demonAsksItem(n, *n.pwork, *n.ework);
    setItemVariable(flowWindow(n), n.requestdata);
    showFlowMessage(n, 0xff);
    return 0;
}

// Flow13_5 @ 0x00278910: hand it over? (selection 0xD3): yes 13_6, no 13_7.
int32_t handOver(TalkState& n)
{
    if (n.talkPhase == 0) {
        showFlowMessage(n, 0xd3, true);
    } else if (n.talkPhase == 1) {
        addCandidate(n, step(6));
        addCandidate(n, step(7));
        n.nextTalkId = n.candidates[n.nowselect == 0 ? 0 : 1];
    }
    return 0;
}

// Flow13_6 @ 0x002789A8: with the item on hand, 13_9; else 13_8.
int32_t checkItemOnHand(TalkState& n)
{
    addCandidate(n, step(9));
    addCandidate(n, step(8));
    n.nextTalkId = n.candidates[dat::hasItem(n.requestdata, 1) ? 0 : 1];
    return 0;
}

// Flow13_7 @ 0x00278A08: refused, it gets angry (13_10) or lets the party
// go (13_12), at random.
int32_t refused(TalkState& n)
{
    addCandidate(n, step(10));
    addCandidate(n, step(12));
    n.nextTalkId = n.candidates[sdf::GetRandInt(2)];
    return 0;
}

// Flow13_8 @ 0x00278AB8: the party hasn't got it: it shakes its head
// (messages 0x51, 0x12B) and fights.
int32_t notOnHand(TalkState& n)
{
    switch (n.talkPhase) {
    case 0: n.waitframe = refuseMotion(n, *n.eform); break;
    case 1: showFlowMessage(n, 0x51); break;
    case 2: showFlowMessage(n, 0x12b); break;
    case 3: return 1;
    default: break;
    }
    return 0;
}

// Flow13_9 @ 0x00278B70: it nods and takes the item (message 0x101).
int32_t takesItem(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = agreeMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        addCandidate(n, 0xc001a);
        showFlowMessage(n, 0x101);
        dat::addItem(n.requestdata, -1);
    }
    return 0;
}

// Flow13_10 @ 0x00278BF8: angered, it shakes its head (message 0x100) and
// fights.
int32_t angered(TalkState& n)
{
    switch (n.talkPhase) {
    case 0: n.waitframe = refuseMotion(n, *n.eform); break;
    case 1: showFlowMessage(n, 0x100); break;
    case 2: return 1;
    default: break;
    }
    return 0;
}

// Flow13_11 @ 0x00278C80: it fights.
int32_t fights(TalkState&) { return 1; }

// Flow13_12 @ 0x00278A68: it lets the party go (message 0x116).
int32_t letsGo(TalkState& n)
{
    addCandidate(n, 0xa001c);
    showFlowMessage(n, 0x116);
    return 0;
}

} // namespace

const TalkStep kAmbushSteps[13] = {
    nullptr,   ambushOpens, questionOrItem, asksQuestion, demandsItem, handOver, checkItemOnHand,
    refused,   notOnHand,   takesItem,      angered,      fights,      letsGo,
};

// nbNegoFlowSensei @ 0x00278C88
int32_t ambushFlow(TalkState& n) { return kAmbushSteps[n.talkId & 0xffff](n); }

} // namespace nocturne::nb
