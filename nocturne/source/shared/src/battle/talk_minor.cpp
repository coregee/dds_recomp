// The talks' short groups: 3 (original unit: NbNegoFlowStock), 14
// (NbNegoFlowBinjo, a demon asking to join) and 16 (NbNegoFlowKoketa, a
// demon taunting the party after a failed escape). Rewritten from the
// original instructions. Messages are numbers in the demon's flow table.
#include "nocturne/battle/talk_flow.hpp"

#include "nocturne/battle/camera.hpp"
#include "nocturne/battle/kouka.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"

namespace nocturne::nb {

namespace {

int32_t flowWindow(const TalkState& n) { return n.flowmsg[n.ekucyo]; }

// ---- group 3 ----

// Flow3_1 @ 0x00274E90: message 0x30.
int32_t stockSays(TalkState& n)
{
    addCandidate(n, 0x30002);
    showTalkMessage(n, flowWindow(n), 0x30, false);
    return 0;
}

// Flow3_2 @ 0x00274EE0: help message 1, and the talk ends (result 2).
int32_t stockEnds(TalkState& n)
{
    showTalkMessage(n, n.helpmsg, 1, false);
    return 2;
}

// ---- group 14: a demon asks to join ----

// Flow14_1 @ 0x002773B8: on to the first group's step 0x1001F, step 0xE0002
// noted for later (workid[3]).
int32_t asksToJoin(TalkState& n)
{
    addCandidate(n, 0x1001f);
    n.workid[3] = 0xe0002;
    return 0;
}

// Flow14_2 @ 0x002773F8: it nods and speaks (message 0x110).
int32_t asksToJoinNods(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = agreeMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        addCandidate(n, 0x1001e);
        showTalkMessage(n, flowWindow(n), 0x110, false);
    }
    return 0;
}

// ---- group 16: a taunt after a failed escape ----

// Flow16_1 @ 0x002794B0: a word over the demon, the camera on it; Wilder,
// Haunt and Foul demons take 16_3, the others 16_2.
int32_t taunts(TalkState& n)
{
    addCandidate(n, 0x100002);
    addCandidate(n, 0x100003);
    addWordPacket(0, 0x1e, static_cast<int32_t>(n.actdata.address), n.eform.get(), 0);
    cameraOnObstructor(*n.eform);
    const Race race = dat::race(*n.ework);
    if (race == Race::Wilder || race == Race::Haunt || race == Race::Foul)
        n.nextTalkId = n.candidates[1];
    return 0;
}

// Flow16_2 @ 0x00279538: message 0x12C, or 0x128 under a full Kagutsuchi
// but for the moonproof; the talk ends (result 4).
int32_t tauntSays(TalkState& n)
{
    showTalkMessage(n, flowWindow(n), !moonproof(n.ework->id) && evt::GetAgeOfMoon() == 8 ? 0x128 : 0x12c, false);
    return 4;
}

// Flow16_3 @ 0x00279628: message 0x12C; the talk ends (result 4).
int32_t tauntEnds(TalkState& n)
{
    showTalkMessage(n, flowWindow(n), 0x12c, false);
    return 4;
}

} // namespace

const TalkStep kStockSteps[3] = {nullptr, stockSays, stockEnds};
const TalkStep kAskToJoinSteps[3] = {nullptr, asksToJoin, asksToJoinNods};
const TalkStep kTauntSteps[4] = {nullptr, taunts, tauntSays, tauntEnds};

// nbNegoFlowStock @ 0x00274F08
int32_t stockFlow(TalkState& n) { return kStockSteps[n.talkId & 0xffff](n); }

// nbNegoFlowBinjo @ 0x00277478
int32_t askToJoinFlow(TalkState& n) { return kAskToJoinSteps[n.talkId & 0xffff](n); }

// nbNegoFlowKoketa @ 0x00279660
int32_t tauntFlow(TalkState& n) { return kTauntSteps[n.talkId & 0xffff](n); }

} // namespace nocturne::nb
