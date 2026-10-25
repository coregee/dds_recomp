// The talks' group 12 (original unit: NbNegoFlowMukan): the last enemy
// able to talk speaks up (CheckMukanNego), or a demon opens an ambush with
// talk (talk type 2, whose messages differ). By weights in its talk record
// it asks one of two questions or offers something; asked, the answer
// pleases it or not by how the two sides compare; offering, it joins,
// tells something, gives Macca or an item, or just leaves. Rewritten from
// the original instructions. Messages are in the demon's flow table or the
// help table.
#include "nocturne/address.hpp"
#include "nocturne/battle/talk_flow.hpp"

#include "nocturne/data/ids.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t step(uint32_t number) { return 0xc0000u | number; }
constexpr int32_t kAmbushTalk = 2;   // TalkState::talkType

// [DevilTalkFormat::lastEnemyTalkIndex][3] percent weights: question 12_3,
// question 12_4, or no question (12_24). (The six rows in use are all
// 33, 33, 34.)
constexpr uint32_t kSpeakUpWeights = addr(0x003e2470);

int32_t flowWindow(const TalkState& n) { return n.flowmsg[n.ekucyo]; }

void showFlowMessage(TalkState& n, int32_t message, bool select = false)
{
    showTalkMessage(n, flowWindow(n), message, select);
}

// A question and its answers: the question (`message`), the answers
// (`selection`), then pleased (first two) or not (last two) by the
// answer: the first answer pleases it 80 times in a hundred, 60 when the
// talker is the lower level, halved again when behind on stat 1; the
// second answer the other way round.
void asks(TalkState& n, int32_t message, int32_t selection, uint32_t pleasedFirst)
{
    switch (n.talkPhase) {
    case 0:
        showFlowMessage(n, message);
        break;
    case 1:
        showFlowMessage(n, selection, true);
        break;
    case 2: {
        for (uint32_t i = 0; i < 4; ++i)
            addCandidate(n, step(pleasedFirst + i));
        const bool lower = n.pwork->level < n.ework->level;
        const bool even = dat::param(*n.ework, Param::Unused1) <= dat::param(*n.pwork, Param::Unused1);
        const int32_t chance = even ? (lower ? 60 : 80) : (lower ? 20 : 40);
        if (n.nowselect == 0)
            n.nextTalkId = n.candidates[static_cast<int32_t>(sdf::GetRandInt(100)) < chance ? 0 : 1];
        else
            n.nextTalkId = n.candidates[static_cast<int32_t>(sdf::GetRandInt(100)) < 100 - chance ? 2 : 3];
        break;
    }
    default:
        break;
    }
}

// Pleased (a nod, on to 12_26's offer) or not (a head shake, on to
// 0xC002E: 12_46), with its message.
void reacts(TalkState& n, bool pleased, int32_t message)
{
    if (n.talkPhase == 0) {
        n.waitframe = pleased ? agreeMotion(n, *n.eform) : refuseMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        addCandidate(n, pleased ? step(0x1a) : step(0x2e));
        showFlowMessage(n, message);
    }
}

// The message for an ambush's talk, or the last enemy's.
int32_t byTalk(const TalkState& n, int32_t ambush, int32_t lastEnemy)
{
    return n.talkType == kAmbushTalk ? ambush : lastEnemy;
}

// Flow12_1 @ 0x002774A8: on to the first group's step 0x1001F, this
// group's step 2 noted for later (workid[3]).
int32_t speaksUp(TalkState& n)
{
    addCandidate(n, 0x1001f);
    n.workid[3] = step(2);
    return 0;
}

// Flow12_2 @ 0x002774E8: a question (12_3 or 12_4) or none (12_24), by
// its weights.
int32_t questionOrNot(TalkState& n)
{
    addCandidate(n, step(3));
    addCandidate(n, step(4));
    addCandidate(n, step(0x18));
    const uint8_t* weights =
        guest::table<const uint8_t>(kSpeakUpWeights) + dat::devilTalkFormat(n.ework->id).lastEnemyTalkIndex * 3;
    const int32_t roll = static_cast<int32_t>(sdf::GetRandInt(100));
    int32_t sum = 0;
    for (int32_t i = 0; i < 3; ++i) {
        sum += weights[i];
        if (roll < sum) {
            n.nextTalkId = n.candidates[i];
            break;
        }
    }
    return 0;
}

// Flow12_3 @ 0x00277600: a question (0xEB, answers 0xD5): 12_16..12_19.
int32_t asksFirst(TalkState& n)
{
    asks(n, 0xeb, 0xd5, 0x10);
    return 0;
}

// Flow12_4 @ 0x00277798: the other question (0xEC, answers 0xD6):
// 12_20..12_23.
int32_t asksSecond(TalkState& n)
{
    asks(n, 0xec, 0xd6, 0x14);
    return 0;
}

// Flow12_16 @ 0x002779F8
int32_t firstPleased(TalkState& n) {
    reacts(n, true, 0xee);
    return 0;
}
// Flow12_17 @ 0x00277A78
int32_t firstDispleased(TalkState& n) {
    reacts(n, false, 0xef);
    return 0;
}
// Flow12_18 @ 0x00277AF8
int32_t firstPleasedOther(TalkState& n) {
    reacts(n, true, 0xf0);
    return 0;
}
// Flow12_19 @ 0x00277B78
int32_t firstDispleasedOther(TalkState& n) {
    reacts(n, false, 0xf1);
    return 0;
}
// Flow12_20 @ 0x00277BF8
int32_t secondPleased(TalkState& n) {
    reacts(n, true, 0xf2);
    return 0;
}
// Flow12_21 @ 0x00277C78
int32_t secondDispleased(TalkState& n) {
    reacts(n, false, 0xf3);
    return 0;
}
// Flow12_22 @ 0x00277CF8
int32_t secondPleasedOther(TalkState& n) {
    reacts(n, true, 0xf4);
    return 0;
}
// Flow12_23 @ 0x00277D78
int32_t secondDispleasedOther(TalkState& n) {
    reacts(n, false, 0xf5);
    return 0;
}

// Flow12_24 @ 0x00277930: no question: it shakes its head (message 0xED).
int32_t noQuestion(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = refuseMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        addCandidate(n, step(0x19));
        showFlowMessage(n, 0xed);
    }
    return 0;
}

// Flow12_25 @ 0x002779B0: it leaves (help message 1).
int32_t leavesWithoutQuestion(TalkState& n)
{
    addCandidate(n, 0xa001d);
    showTalkMessage(n, n.helpmsg, 1, false);
    return 0;
}

// Flow12_26 @ 0x00277DF8
int32_t pleasedGoesOn(TalkState& n)
{
    addCandidate(n, step(0x1b));
    return 0;
}

// Flow12_27 @ 0x00277E20: its offer, at random: to join (12_28),
// information (12_35), Macca (12_40) or an item (12_43). Wilders, Haunts
// and Foul offer to join; Tyrants, Viles and Gurr, Macca; and Macca instead
// of joining when one like it is in the stock, the stock is full or it is
// above the Demi-fiend's level.
int32_t offers(TalkState& n)
{
    addCandidate(n, step(0x1c));
    addCandidate(n, step(0x23));
    addCandidate(n, step(0x28));
    addCandidate(n, step(0x2b));
    n.nextTalkId = n.candidates[sdf::GetRandInt(4)];
    const Race race = dat::race(*n.ework);
    if (race == Race::Wilder || race == Race::Haunt || race == Race::Foul)
        n.nextTalkId = n.candidates[0];
    if (race == Race::Tyrant || race == Race::Vile || n.ework->id == devil::Gurr)
        n.nextTalkId = n.candidates[2];
    if (n.nextTalkId == n.candidates[0]) {
        if (dat::findDevil(n.ework->id) >= 0)
            n.nextTalkId = n.candidates[2];
        if (dat::isStockFull())
            n.nextTalkId = n.candidates[2];
    }
    diag::print(diag::Message::SpeakUpLevels, dat::playerLevel(), n.ework->level);
    if (n.nextTalkId == n.candidates[0] && dat::playerLevel() < n.ework->level)
        n.nextTalkId = n.candidates[2];
    return 0;
}

// Flow12_28 @ 0x00277FB8: it offers to join (0xF9; an ambush's 0x105).
int32_t offersToJoin(TalkState& n)
{
    addCandidate(n, step(0x1d));
    showFlowMessage(n, byTalk(n, 0x105, 0xf9));
    return 0;
}

// Flow12_29 @ 0x00278038: take it? (selection 0xD4): yes 12_30, no 12_38.
int32_t takeIt(TalkState& n)
{
    if (n.talkPhase == 0) {
        showFlowMessage(n, 0xd4, true);
    } else if (n.talkPhase == 1) {
        addCandidate(n, step(0x1e));
        addCandidate(n, step(0x26));
        n.nextTalkId = n.candidates[n.nowselect];
    }
    return 0;
}

// Flow12_30 @ 0x002780D0: it nods (0xFA or 0xFB; an ambush's 0x106 or
// 0x107).
int32_t gladToJoin(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = agreeMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        addCandidate(n, step(0x1f));
        const bool second = sdf::GetRandInt(2) != 0;
        showFlowMessage(n, n.talkType == kAmbushTalk ? (second ? 0x107 : 0x106) : (second ? 0xfb : 0xfa));
    }
    return 0;
}

// Flow12_31 @ 0x002781C0: it joins (help message 2; result 9).
int32_t joins(TalkState& n)
{
    showTalkMessage(n, n.helpmsg, 2, false);
    return 9;
}

// Flow12_35 @ 0x002781E8: it offers to tell something (0xF6; an ambush's
// 0x102).
int32_t offersInformation(TalkState& n)
{
    addCandidate(n, step(0x24));
    showFlowMessage(n, byTalk(n, 0x102, 0xf6));
    return 0;
}

// Flow12_36 @ 0x00278268: the information, of either kind at random.
int32_t choosesInformation(TalkState& n)
{
    addCandidate(n, step(0x25));
    n.getinfotype = sdf::GetRandInt(2) == 0 ? 0 : 2;
    n.getinfomsg = pickInfoMessage(n.getinfotype);
    return 0;
}

// Flow12_37 @ 0x002782C8: it tells it (from its information table).
int32_t tells(TalkState& n)
{
    addCandidate(n, 0xa001c);
    showTalkMessage(n, n.infomsg[n.ekucyo], n.getinfomsg, false);
    return 0;
}

// Flow12_38 @ 0x00278318: turned down (message 0x108 or 0x109).
int32_t turnedDown(TalkState& n)
{
    addCandidate(n, step(0x27));
    showFlowMessage(n, sdf::GetRandInt(2) == 0 ? 0x108 : 0x109);
    return 0;
}

// Flow12_39 @ 0x002783A0: it leaves (help message 1).
int32_t leavesTurnedDown(TalkState& n)
{
    addCandidate(n, 0xa001d);
    showTalkMessage(n, n.helpmsg, 1, false);
    return 0;
}

// Flow12_40 @ 0x002783E8: it offers Macca (0xF7; an ambush's 0x103).
int32_t offersMacca(TalkState& n)
{
    addCandidate(n, step(0x29));
    showFlowMessage(n, byTalk(n, 0x103, 0xf7));
    n.getmakka = demonGivesMaccaB(n, *n.pwork, *n.ework);
    return 0;
}

// Flow12_41 @ 0x00278480: "got Macca" (help message 3).
int32_t receivedMacca(TalkState& n)
{
    addCandidate(n, step(0x2a));
    setMaccaVariable(n.helpmsg, n.getmakka);
    showTalkMessage(n, n.helpmsg, 3, false);
    return 0;
}

// Flow12_42 @ 0x002784D0: the Macca is added; it leaves.
int32_t addsMacca(TalkState& n)
{
    addCandidate(n, 0xa001d);
    dat::addMacca(n.getmakka);
    return 0;
}

// Flow12_43 @ 0x00278508: it offers an item from its second list (item 1
// when none; every demon has some) (0xF8; an ambush's 0x104), Macca
// instead when the player can't carry more.
int32_t offersItem(TalkState& n)
{
    addCandidate(n, step(0x2c));
    addCandidate(n, step(0x28));
    n.getitem = demonGivesItemB(*n.ework);
    if (n.getitem == 0)
        n.getitem = 1;
    if (!dat::isItemFull(n.getitem))
        showFlowMessage(n, byTalk(n, 0x104, 0xf8));
    else
        n.nextTalkId = n.candidates[1];
    return 0;
}

// Flow12_44 @ 0x002785D0: "got the item" (help message 5).
int32_t receivedItem(TalkState& n)
{
    addCandidate(n, step(0x2d));
    setItemVariable(n.helpmsg, n.getitem);
    showTalkMessage(n, n.helpmsg, 5, false);
    return 0;
}

// Flow12_45 @ 0x00278620: the item is added; it leaves.
int32_t addsItem(TalkState& n)
{
    addCandidate(n, 0xa001d);
    dat::addItem(n.getitem, 1);
    return 0;
}

// Flow12_46 @ 0x00278660
int32_t displeasedGoesOn(TalkState& n)
{
    addCandidate(n, step(0x2f));
    return 0;
}

// Flow12_47 @ 0x00278688: displeased, it leaves (12_48) or attacks
// (12_49), at random.
int32_t leavesOrAttacks(TalkState& n)
{
    addCandidate(n, step(0x30));
    addCandidate(n, step(0x31));
    n.nextTalkId = n.candidates[sdf::GetRandInt(2) == 0 ? 0 : 1];
    return 0;
}

// Flow12_48 @ 0x002786E8: it leaves.
int32_t leaves(TalkState& n)
{
    addCandidate(n, 0xa001d);
    return 0;
}

// Flow12_49 @ 0x00278710: it attacks (result 4).
int32_t attacks(TalkState&) { return 4; }

constexpr TalkStep kNone = nullptr;

} // namespace

const TalkStep kSpeakUpSteps[50] = {
    kNone,        speaksUp,          questionOrNot,      asksFirst,        asksSecond,
    kNone,        kNone,             kNone,              kNone,            kNone,
    kNone,        kNone,             kNone,              kNone,            kNone,
    kNone,        firstPleased,      firstDispleased,    firstPleasedOther, firstDispleasedOther,
    secondPleased, secondDispleased, secondPleasedOther, secondDispleasedOther, noQuestion,
    leavesWithoutQuestion, pleasedGoesOn, offers,        offersToJoin,     takeIt,
    gladToJoin,   joins,             kNone,              kNone,            kNone,
    offersInformation, choosesInformation, tells,        turnedDown,       leavesTurnedDown,
    offersMacca,  receivedMacca,     addsMacca,          offersItem,       receivedItem,
    addsItem,     displeasedGoesOn,  leavesOrAttacks,    leaves,           attacks,
};

// nbNegoFlowMukan @ 0x00278718
int32_t speakUpFlow(TalkState& n) { return kSpeakUpSteps[n.talkId & 0xffff](n); }

} // namespace nocturne::nb
