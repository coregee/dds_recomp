// The talks' group 8 (original unit: NbNegoFlowFight). Without the debug
// menu to choose among the candidates, it runs 8_1 to 8_5: the demon (0x9F)
// either agrees after all (8_6, on to group 9) or refuses and leaves (8_7).
// The other branches, reachable only from the debug menu, end in a fight
// (result 1), the demon leaving (2), a fixed 6,600 Macca message (8_18) or
// result 4. Rewritten from the original instructions. Messages are in the
// demon's flow table or the help table.
#include "nocturne/battle/talk_flow.hpp"

#include "nocturne/external.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t step(uint32_t number) { return 0x80000u | number; }

int32_t flowWindow(const TalkState& n) { return n.flowmsg[n.ekucyo]; }

// Flow8_1 @ 0x00276760: message 0x9F.
int32_t opens(TalkState& n)
{
    addCandidate(n, step(2));
    showTalkMessage(n, flowWindow(n), 0x9f, false);
    return 0;
}

// Flow8_2 @ 0x002767B0
int32_t afterOpening(TalkState& n)
{
    addCandidate(n, step(3));
    return 0;
}

// Flow8_3 @ 0x002767D8: three ways on; without the debug menu, the first.
int32_t threeWays(TalkState& n)
{
    addCandidate(n, step(4));
    addCandidate(n, step(8));
    addCandidate(n, step(11));
    return 0;
}

// Flow8_4 @ 0x00276828
int32_t toDecision(TalkState& n)
{
    addCandidate(n, step(5));
    return 0;
}

// Flow8_5 @ 0x00276850: it agrees (8_6) or leaves (8_7), at random.
int32_t agreesOrLeaves(TalkState& n)
{
    addCandidate(n, step(6));
    addCandidate(n, step(7));
    n.nextTalkId = n.candidates[sdf::GetRandInt(2)];
    return 0;
}

// Flow8_6 @ 0x002768B0: it agrees after all (message 0xA0; on to 9_1).
int32_t agrees(TalkState& n)
{
    addCandidate(n, 0x90001);
    showTalkMessage(n, flowWindow(n), 0xa0, false);
    return 0;
}

// Flow8_7 @ 0x00276900: it shakes its head (message 0xA1) and leaves
// (result 2).
int32_t leaves(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = refuseMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        showTalkMessage(n, flowWindow(n), 0xa1, false);
        return 2;
    }
    return 0;
}

// Flow8_8 @ 0x00276980 (the debug menu's second way)
int32_t secondWay(TalkState& n)
{
    addCandidate(n, step(9));
    return 0;
}

// Flow8_9 @ 0x002769A8
int32_t secondWayChoice(TalkState& n)
{
    addCandidate(n, step(10));
    addCandidate(n, step(19));
    return 0;
}

// Flow8_10 @ 0x002769E8
int32_t secondWayFight(TalkState& n)
{
    addCandidate(n, step(14));
    addCandidate(n, step(13));
    return 0;
}

// Flow8_11 @ 0x00276A28 (the debug menu's third way)
int32_t thirdWay(TalkState& n)
{
    addCandidate(n, step(12));
    addCandidate(n, step(13));
    return 0;
}

// Flow8_12 @ 0x00276A68: it shakes its head (message 0xA4 or 0xA5) and
// fights (result 1).
int32_t refusesAndFights(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = refuseMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        showTalkMessage(n, flowWindow(n), 0xa4 + static_cast<int32_t>(sdf::GetRandInt(2)), false);
        return 1;
    }
    return 0;
}

// Flow8_13 @ 0x00276AF8: message 0xA6.
int32_t warns(TalkState& n)
{
    addCandidate(n, step(17));
    showTalkMessage(n, flowWindow(n), 0xa6, false);
    return 0;
}

// Flow8_14 @ 0x00276B48: 8_15 or 8_16, at random.
int32_t eitherFight(TalkState& n)
{
    addCandidate(n, step(15));
    addCandidate(n, step(16));
    n.nextTalkId = n.candidates[sdf::GetRandInt(2)];
    return 0;
}

// Flow8_15 @ 0x00276BA8: it shakes its head (message 0xA3) and fights.
int32_t shakesHeadAndFights(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = refuseMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        showTalkMessage(n, flowWindow(n), 0xa3, false);
        return 1;
    }
    return 0;
}

// Flow8_16 @ 0x00276C28: message 0xA2; it fights.
int32_t fights(TalkState& n)
{
    showTalkMessage(n, flowWindow(n), 0xa2, false);
    return 1;
}

// Flow8_17 @ 0x00276C60
int32_t toMacca(TalkState& n)
{
    addCandidate(n, step(18));
    return 0;
}

// Flow8_18 @ 0x00276C88: help message 4 with 6,600 Macca; it fights.
int32_t maccaAndFights(TalkState& n)
{
    setMaccaVariable(n.helpmsg, 6600);
    showTalkMessage(n, n.helpmsg, 4, false);
    return 1;
}

// Flow8_19 @ 0x00276CD0 (result 4)
int32_t ends(TalkState&) { return 4; }

} // namespace

const TalkStep kFightSteps[20] = {
    nullptr,         opens,          afterOpening,       threeWays,        toDecision,
    agreesOrLeaves,  agrees,         leaves,             secondWay,        secondWayChoice,
    secondWayFight,  thirdWay,       refusesAndFights,   warns,            eitherFight,
    shakesHeadAndFights, fights,     toMacca,            maccaAndFights,   ends,
};

// nbNegoFlowFight @ 0x00276CD8
int32_t fightFlow(TalkState& n) { return kFightSteps[n.talkId & 0xffff](n); }

} // namespace nocturne::nb
