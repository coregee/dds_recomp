// The talks' group 10 (original unit: NbNegoFlowNg): no deal. The demon
// refuses: a helper may step in; it may attack (result 4), or leave (2),
// and some refuse yet leave a parting gift: Macca, an item or healing. With
// a Death Pact (and the talker standing), the talk ends instead with the
// talker striking the demon with Death (10_33). Steps 10_28..10_30 are the
// partings the other groups go on to. Rewritten from the original
// instructions. Messages are in the demon's flow or affinity table, or the
// help tables.
#include "nocturne/battle/talk_flow.hpp"

#include "nocturne/battle/camera.hpp"
#include "nocturne/battle/kouka.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t step(uint32_t number) { return 0xa0000u | number; }
constexpr uint32_t kDeathPactStrike = step(0x21);

int32_t flowWindow(const TalkState& n) { return n.flowmsg[n.ekucyo]; }

void showFlowMessage(TalkState& n, int32_t message) { showTalkMessage(n, flowWindow(n), message, false); }

// The early demons that are kinder before event 8.
bool youngDemon(uint16_t id) { return id == devil::Kodama || id == devil::Pixie || id == devil::Shikigami; }

} // namespace

// CheckSkillShinoKeiyaku @ 0x002731A8 (the HD remaster's name): a Death
// Pact ("shi no keiyaku") with the talker still standing.
bool deathPact(const TalkState& n) { return n.talkSkill == skill::DeathPact && n.pwork->hp != 0; }

namespace {

// The talk ends with `result`, or, with a Death Pact, with the strike
// first (the result kept for after it).
int32_t endOrStrike(TalkState& n, int32_t result)
{
    if (!deathPact(n))
        return result;
    addCandidate(n, kDeathPactStrike);
    n.temp_param[0] = result;
    return 0;
}

// The message for what it was asked for (request kinds 1..5), or 0.
int32_t byRequest(const TalkState& n, int32_t macca, int32_t item, int32_t either)
{
    switch (n.talkRequestType) {
    case 1: case 5: return macca;
    case 2: return sdf::GetRandInt(2) != 0 ? either : macca;
    case 3: return item;
    case 4: return either;
    default: return 0;
    }
}

// By the request kind: joining c[1], a gift c[0], information c[2].
void byRequestKind(TalkState& n)
{
    switch (n.talkRequestType) {
    case 0: n.nextTalkId = n.candidates[1]; break;
    case 1: case 2: case 3: case 4: case 5: n.nextTalkId = n.candidates[0]; break;
    case 6: n.nextTalkId = n.candidates[2]; break;
    default: break;
    }
}

// Flow10_1 @ 0x002731D0: no deal. A young demon before event 8 asked to
// join goes on to 10_11; on a first refusal it shakes its head (10_2) or
// goes on (10_11) at random (Corpus always on); later, six in ten it is
// asked again (0x6002B).
int32_t noDeal(TalkState& n)
{
    addCandidate(n, step(2));
    addCandidate(n, step(11));
    addCandidate(n, 0x6002b);
    if (youngDemon(n.ework->id) && !evt::BitCheck(8) && n.talkRequestType == 0) {
        n.nextTalkId = n.candidates[1];
        return 0;
    }
    if (n.cnt6_37 == 0) {
        n.nextTalkId = n.candidates[sdf::GetRandInt(2)];
        if (dat::race(*n.ework) == Race::Corpus)
            n.nextTalkId = n.candidates[1];
    } else {
        n.nextTalkId = n.candidates[sdf::GetRandInt(10) < 6 ? 2 : 1];
    }
    return 0;
}

// Flow10_2 @ 0x002732D0: it shakes its head (message 0xD7 or 0xD8).
int32_t shakesHead(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = refuseMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        addCandidate(n, step(3));
        showFlowMessage(n, 0xd7 + static_cast<int32_t>(sdf::GetRandInt(2)));
    }
    return 0;
}

// Flow10_3 @ 0x00273358: with helpers' skills left, 10_4; else 10_6.
int32_t anyHelper(TalkState& n)
{
    addCandidate(n, step(6));
    addCandidate(n, step(4));
    n.nextTalkId = n.candidates[countBuffSkills(n) < 1 ? 0 : 1];
    return 0;
}

// Flow10_4 @ 0x002733B0: a helper's skill for this moment (type 1): on to
// group 6's 0x60034 with it, its outcomes 10_10 or 10_5; none, 10_6.
int32_t helperStepsIn(TalkState& n)
{
    addCandidate(n, 0x60034);
    addCandidate(n, step(6));
    n.workid[0] = step(10);
    n.workid[1] = step(5);
    const uint32_t buff = useBuffSkill(n, 1);
    if (buff == 0) {
        n.nextTalkId = n.candidates[1];
    } else {
        n.nextTalkId = n.candidates[0];
        n.buffPartyIndex = static_cast<int32_t>(buff >> 16);
        n.buffSkill = static_cast<int32_t>(buff & 0xffff);
    }
    return 0;
}

// Flow10_5 @ 0x00273440: the helper failed: it shakes its head (message
// 0xDA).
int32_t helperFailed(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = refuseMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        addCandidate(n, step(6));
        cameraOnTalkTarget(*n.eform);
        showFlowMessage(n, 0xda);
    }
    return 0;
}

// Flow10_6 @ 0x002734C8: it attacks, by what it was asked: a gift 10_7,
// joining 10_8, information 10_9.
int32_t attacks(TalkState& n)
{
    addCandidate(n, step(7));
    addCandidate(n, step(8));
    addCandidate(n, step(9));
    cameraOnTalkTarget(*n.eform);
    byRequestKind(n);
    return 0;
}

// Flow10_7 @ 0x00273560 (messages 0xDC..0xDE by the gift asked for)
int32_t attacksOverGift(TalkState& n)
{
    showFlowMessage(n, byRequest(n, 0xdc, 0xdd, 0xde));
    return endOrStrike(n, 4);
}

// Flow10_8 @ 0x00273630 (message 0xDB)
int32_t attacksOverJoining(TalkState& n)
{
    showFlowMessage(n, 0xdb);
    return endOrStrike(n, 4);
}

// Flow10_9 @ 0x002736A8 (message 0xDF)
int32_t attacksOverInformation(TalkState& n)
{
    showFlowMessage(n, 0xdf);
    return endOrStrike(n, 4);
}

// Flow10_10 @ 0x00273898: the helper won it over (its affinity message, or
// 0xD9); the talk starts over (group 6's 0x6004A).
int32_t helperWins(TalkState& n)
{
    addCandidate(n, 0x6004a);
    n.workid[6] = 0x60009;
    n.cnt6_36 = 0;
    n.cnt6_37 = 0;
    if (n.buffAffinity == 1)
        showTalkMessage(n, n.aisyomsg[n.ekucyo], n.buffAffinityMessage, false);
    else
        showFlowMessage(n, 0xd9);
    return 0;
}

// Flow10_11 @ 0x00273928: message 0xE0.
int32_t refusesGently(TalkState& n)
{
    addCandidate(n, step(12));
    showFlowMessage(n, 0xe0);
    return 0;
}

// Flow10_12 @ 0x00273978: a parting gift (10_13) four times in ten (seven
// with affinity 1, never with 2; never on the first refusal); else 10_21.
int32_t partingGiftOrNot(TalkState& n)
{
    addCandidate(n, step(13));
    addCandidate(n, step(21));
    int32_t chance = 40;
    if (n.affinity == 1)
        chance = 70;
    else if (n.affinity == 2)
        chance = 0;
    if (n.cnt6_36 == 0)
        n.nextTalkId = n.candidates[1];
    else
        n.nextTalkId = n.candidates[static_cast<int32_t>(sdf::GetRandInt(100)) < chance ? 0 : 1];
    return 0;
}

// Flow10_13 @ 0x00273A20: an item (10_16) two times in three, else healing
// (10_17).
int32_t choosesPartingGift(TalkState& n)
{
    addCandidate(n, step(16));
    addCandidate(n, step(16));
    addCandidate(n, step(17));
    n.nextTalkId = n.candidates[sdf::GetRandInt(3)];
    return 0;
}

// Flow10_15 @ 0x00273A90: Macca (message 0xE2).
int32_t partingMacca(TalkState& n)
{
    addCandidate(n, step(18));
    n.getmakka = demonGivesMaccaB(n, *n.pwork, *n.ework);
    cameraOnTalkTarget(*n.eform);
    setMaccaVariable(flowWindow(n), n.getmakka);
    showFlowMessage(n, 0xe2);
    return 0;
}

// Flow10_16 @ 0x00273B18: an item from its second list (0x24 when none;
// every demon has some), healing instead when the player can't carry
// more.
int32_t partingItem(TalkState& n)
{
    addCandidate(n, step(19));
    addCandidate(n, step(17));
    n.getitem = demonGivesItemB(*n.ework);
    if (n.getitem == 0)
        n.getitem = 0x24;
    if (!dat::isItemFull(n.getitem)) {
        n.nextTalkId = n.candidates[0];
        cameraOnTalkTarget(*n.eform);
        setItemVariable(flowWindow(n), n.getitem);
        showFlowMessage(n, 0xe1);
    } else {
        n.nextTalkId = n.candidates[1];
    }
    return 0;
}

// Flow10_17 @ 0x00273BD8: healing (message 0xE3).
int32_t partingHealing(TalkState& n)
{
    addCandidate(n, step(20));
    showFlowMessage(n, 0xe3);
    return 0;
}

// Flow10_18 @ 0x00273C28: the Macca is added.
int32_t addsMacca(TalkState& n)
{
    addCandidate(n, step(30));
    dat::addMacca(n.getmakka);
    return 0;
}

// Flow10_19 @ 0x00273C60: the item is added.
int32_t addsItem(TalkState& n)
{
    addCandidate(n, step(31));
    dat::addItem(n.getitem, 1);
    return 0;
}

// Flow10_20 @ 0x00273CA0: the talker is shown healed to full.
int32_t heals(TalkState& n)
{
    addCandidate(n, step(32));
    closeTalkWindow(n);
    PanelSetEnabled(true);
    MakeHealPackets(0, 0, n.pform.get(), 0, n.pwork->maxhp, -1, 0);
    addHitEffectPacket(0, 0, *n.pform, 8);
    n.waitframe = 0;
    return 0;
}

// Flow10_21 @ 0x00273D20: it leaves (10_28), or attacks (10_24) half the
// time (a young demon before event 8: leaves).
int32_t leavesOrAttacks(TalkState& n)
{
    addCandidate(n, step(24));
    addCandidate(n, step(28));
    const bool leaves = (youngDemon(n.ework->id) && !evt::BitCheck(8)) || sdf::GetRandInt(10) < 5;
    n.nextTalkId = n.candidates[leaves ? 1 : 0];
    return 0;
}

// Flow10_22 @ 0x00273DB8: a parting word after a gift (message 0xEA).
int32_t thanks(TalkState& n)
{
    addCandidate(n, step(23));
    showFlowMessage(n, 0xea);
    return 0;
}

// Flow10_23 @ 0x00273E08: it leaves (help message 1).
int32_t leaves(TalkState& n)
{
    addCandidate(n, step(29));
    showTalkMessage(n, n.helpmsg, 1, false);
    return 0;
}

// Flow10_24 @ 0x00273E50: it attacks, by what it was asked: a gift 10_25,
// joining 10_26, information 10_27.
int32_t attacksAfterAll(TalkState& n)
{
    addCandidate(n, step(25));
    addCandidate(n, step(26));
    addCandidate(n, step(27));
    byRequestKind(n);
    return 0;
}

// Flow10_25 @ 0x00273EE0 (messages 0xE6..0xE8), result 1
int32_t fightsOverGift(TalkState& n)
{
    showFlowMessage(n, byRequest(n, 0xe6, 0xe7, 0xe8));
    return endOrStrike(n, 1);
}

// Flow10_26 @ 0x00273FB8 (message 0xE5), result 1
int32_t fightsOverJoining(TalkState& n)
{
    showFlowMessage(n, 0xe5);
    return endOrStrike(n, 1);
}

// Flow10_27 @ 0x00274030 (message 0xE9), result 1
int32_t fightsOverInformation(TalkState& n)
{
    showFlowMessage(n, 0xe9);
    return endOrStrike(n, 1);
}

// Flow10_28 @ 0x002740A8: a parting word (message 0xE4).
int32_t parts(TalkState& n)
{
    addCandidate(n, step(23));
    showFlowMessage(n, 0xe4);
    return 0;
}

// Flow10_29 @ 0x002740F8: the talk ends with the demon gone (result 2).
int32_t gone(TalkState&) { return 2; }

// Flow10_30 @ 0x00274100: "got Macca" (help message 3).
int32_t receivedMacca(TalkState& n)
{
    addCandidate(n, step(22));
    setMaccaVariable(n.helpmsg, n.getmakka);
    showTalkMessage(n, n.helpmsg, 3, false);
    return 0;
}

// Flow10_31 @ 0x00274150: "got the item" (help message 5).
int32_t receivedItem(TalkState& n)
{
    addCandidate(n, step(22));
    setItemVariable(n.helpmsg, n.getitem);
    showTalkMessage(n, n.helpmsg, 5, false);
    return 0;
}

// Flow10_32 @ 0x002741A0: "healed" (the second help table's 7), the panel
// off, a second's wait.
int32_t healed(TalkState& n)
{
    addCandidate(n, step(22));
    showTalkMessage(n, n.helpmsg2, 7, false);
    PanelSetEnabled(false);
    n.waitframe = 60;
    return 0;
}

// Flow10_33 @ 0x00273720: the Death Pact's strike: the two face each other
// (message 0x122), the demon is struck with Death (repelled, drained or
// nulled as its affinity has it), a pause, and the talk ends as it would
// have (temp_param[0]).
int32_t deathPactStrike(TalkState& n)
{
    switch (n.talkPhase) {
    case 0:
        cameraOnPair(*n.pform, *n.eform);
        break;
    case 1:
        showFlowMessage(n, 0x122);
        break;
    case 2: {
        const uint32_t flags = dat::affinityFlags(*n.ework, Attribute::Death);
        if (flags & Affinity::Repel) {
            addHitEffectPacket(0, 0, *n.eform, 1);
        } else if (flags & Affinity::Drain) {
            addHitEffectPacket(0, 0, *n.eform, 2);
        } else if (flags & (Affinity::Null | Affinity::Unknown100000)) {   // (0x100000 never alone on Death)
            addHitEffectPacket(0, 0, *n.eform, 3);
            addWordPacket(0, 0x2d, 0, n.eform.get(), 4);
        } else {
            makeAilmentPackets(0, 0, n.eform.get(), 0x400);
            addHitEffectPacket(0, 0, *n.eform, 10);
        }
        break;
    }
    case 3:
        n.waitframe = 45;
        break;
    case 4:
        return n.temp_param[0];
    default:
        break;
    }
    return 0;
}

} // namespace

const TalkStep kNoDealSteps[34] = {
    nullptr,             noDeal,             shakesHead,         anyHelper,          helperStepsIn,
    helperFailed,        attacks,            attacksOverGift,    attacksOverJoining, attacksOverInformation,
    helperWins,          refusesGently,      partingGiftOrNot,   choosesPartingGift, nullptr,
    partingMacca,        partingItem,        partingHealing,     addsMacca,          addsItem,
    heals,               leavesOrAttacks,    thanks,             leaves,             attacksAfterAll,
    fightsOverGift,      fightsOverJoining,  fightsOverInformation, parts,           gone,
    receivedMacca,       receivedItem,       healed,             deathPactStrike,
};

// nbNegoFlowNg @ 0x002741F8
int32_t noDealFlow(TalkState& n) { return kNoDealSteps[n.talkId & 0xffff](n); }

} // namespace nocturne::nb
