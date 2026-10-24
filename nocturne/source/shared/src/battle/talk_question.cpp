// The talks' group 7 (original unit: NbNegoFlowQuestion): the demon asks a
// question. A demon with a question set of its own (nbGetQuestionType: 0)
// asks one of five from its speech style's set; the others ask one of two
// of a kind (1..3), whose answers move the player toward a Reason. Pleased
// with the answer, it goes on to the step its asker noted in workid[4];
// displeased, to workid[5]. Rewritten from the original instructions. The
// messages are in the question table for the demon's speech style.
#include "nocturne/battle/talk_flow.hpp"

#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t step(uint32_t number) { return 0x70000u | number; }

const OwnQuestion& ownQuestion(const TalkState& n)
{
    return guest::table<const OwnQuestion>(kOwnQuestionAnswers)[n.ekucyo * 7 + 2 + n.qindex];
}

// The message for one of the own questions (0..4: 6 numbers apart), or 0.
int32_t ownMessage(const TalkState& n, int32_t first)
{
    return n.qindex >= 0 && n.qindex <= 4 ? first + n.qindex * 6 : 0;
}

// The message for a question of a kind: the first or second (qindex) of
// its pair, or 0 for no kind.
int32_t kindMessage(const TalkState& n, int32_t kind1, int32_t kind2, int32_t kind3)
{
    int32_t first;
    switch (n.qtype) {
    case 1: first = kind1; break;
    case 2: first = kind2; break;
    case 3: first = kind3; break;
    default: return 0;
    }
    return n.qindex != 0 ? first + 2 : first;
}

// Flow7_1 @ 0x00275DF8: on to the question (7_3).
int32_t questionBegins(TalkState& n)
{
    addCandidate(n, step(3));
    return 0;
}

// Flow7_3 @ 0x00275E20: the question's kind (counted in the player's
// answers, [0] for the own questions), and which of its questions.
int32_t picksQuestion(TalkState& n)
{
    addCandidate(n, step(15));
    addCandidate(n, step(11));
    n.qtype = questionType(*n.ework);
    uint8_t& asked = dat::globalWork().questionAnswers[n.qtype];
    if (asked != 0xff)
        ++asked;
    if (n.qtype == 0) {
        n.qindex = static_cast<int32_t>(sdf::GetRandInt(5));
        n.nextTalkId = n.candidates[0];
    } else {
        n.qindex = static_cast<int32_t>(sdf::GetRandInt(2));
        n.nextTalkId = n.candidates[1];
    }
    return 0;
}

// Flow7_11 @ 0x00275EC8: a question of a kind: the question, then its
// answers (a selection); on to 7_22.
int32_t asksOfKind(TalkState& n)
{
    if (n.talkPhase == 0) {
        showTalkMessage(n, n.questionmsg, kindMessage(n, 0x1f, 0x23, 0x1b), false);
    } else if (n.talkPhase == 1) {
        showTalkMessage(n, n.questionmsg, kindMessage(n, 0x20, 0x24, 0x1c), true);
        addCandidate(n, step(22));
    }
    return 0;
}

// Flow7_15 @ 0x00276018: one of its own questions, then its answers; on
// to 7_20.
int32_t asksOwn(TalkState& n)
{
    if (n.talkPhase == 0) {
        showTalkMessage(n, n.questionmsg, ownMessage(n, 0x29), false);
    } else if (n.talkPhase == 1) {
        showTalkMessage(n, n.questionmsg, ownMessage(n, 0x2a), true);
        addCandidate(n, step(20));
    }
    return 0;
}

// Flow7_20 @ 0x00276130: is it pleased with the answer to its own
// question? (7_23 yes, 7_24 no.)
int32_t judgesOwnAnswer(TalkState& n)
{
    addCandidate(n, step(23));
    addCandidate(n, step(24));
    const OwnQuestion& q = ownQuestion(n);
    int32_t chance = 50;
    if (q.judge == 0 || q.judge == 1) {
        const bool behind = q.judge == 0 ? dat::param(*n.pwork, Param::Unused1) < dat::param(*n.ework, Param::Unused1)
                                         : n.pwork->level < n.ework->level;
        const int32_t first = behind ? q.chanceBehind : q.chanceAhead;
        chance = n.nowselect != 0 ? 100 - first : first;
    }
    n.nextTalkId = n.candidates[static_cast<int32_t>(sdf::GetRandInt(100)) < chance ? 0 : 1];
    return 0;
}

// Flow7_22 @ 0x00276260: the answer to a question of a kind moves the
// player toward its Reason; is it pleased? (7_25 yes, 7_26 no: seven in
// ten, three behind on stat 1, eight with affinity 1, two with 2.)
int32_t judgesKindAnswer(TalkState& n)
{
    addCandidate(n, step(25));
    addCandidate(n, step(26));
    int32_t chance = dat::param(*n.pwork, Param::Unused1) < dat::param(*n.ework, Param::Unused1) ? 30 : 70;
    if (n.affinity == 1)
        chance = 80;
    else if (n.affinity == 2)
        chance = 20;
    if (n.qtype >= 1 && n.qtype <= 3) {
        const int32_t entry = n.ekucyo * 36 + 9 + (n.qtype % 3) * 6 + n.qindex * 3 + n.nowselect;
        dat::addReasonPoints(guest::table<const QuestionReason>(kQuestionReasons)[entry].reason, 1);
    }
    n.nextTalkId = n.candidates[static_cast<int32_t>(sdf::GetRandInt(100)) < chance ? 0 : 1];
    return 0;
}

// Flow7_23 @ 0x00276448: pleased with the answer to its own question: it
// nods and says so.
int32_t pleasedOwn(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = agreeMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        addCandidate(n, n.workid[4]);
        const int32_t first = ownMessage(n, 0x2b);
        showTalkMessage(n, n.questionmsg, first != 0 && n.nowselect != 0 ? first + 2 : first, false);
    }
    return 0;
}

// Flow7_24 @ 0x00276540: displeased with the answer to its own question:
// it shakes its head and says so.
int32_t displeasedOwn(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = refuseMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        addCandidate(n, n.workid[5]);
        n.workid[2] = 0x60045;
        const int32_t first = ownMessage(n, 0x2c);
        showTalkMessage(n, n.questionmsg, first != 0 && n.nowselect != 0 ? first + 2 : first, false);
    }
    return 0;
}

// Flow7_25 @ 0x00276640: pleased with the answer (message 0x27).
int32_t pleasedKind(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = agreeMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        addCandidate(n, n.workid[4]);
        showTalkMessage(n, n.questionmsg, 0x27, false);
    }
    return 0;
}

// Flow7_26 @ 0x002766B0: displeased with the answer (message 0x28).
int32_t displeasedKind(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = refuseMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        addCandidate(n, n.workid[5]);
        n.workid[2] = 0x60045;
        showTalkMessage(n, n.questionmsg, 0x28, false);
    }
    return 0;
}

} // namespace

const TalkStep kQuestionSteps[27] = {
    nullptr,         questionBegins, nullptr,      picksQuestion,    nullptr,       nullptr,     nullptr,
    nullptr,         nullptr,        nullptr,      nullptr,          asksOfKind,    nullptr,     nullptr,
    nullptr,         asksOwn,        nullptr,      nullptr,          nullptr,       nullptr,     judgesOwnAnswer,
    nullptr,         judgesKindAnswer, pleasedOwn, displeasedOwn,    pleasedKind,   displeasedKind,
};

// nbNegoFlowQuestion @ 0x00276730
int32_t questionFlow(TalkState& n) { return kQuestionSteps[n.talkId & 0xffff](n); }

} // namespace nocturne::nb
