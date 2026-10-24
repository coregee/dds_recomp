// The talks' group 9 (original unit: NbNegoFlowOk): the deal is struck. The
// demon offers to join, or gives what the talk was for: Macca, an item (a
// stone for a stone-asking talk) or information. Rewritten from the
// original instructions. The messages are numbers in the demon's flow
// table (by its speech style); the help table's say what the player got.
#include "nocturne/battle/talk_flow.hpp"

#include "nocturne/battle/camera.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kTalkGained = 8;   // ActionProcessData::stat: the talk got the player something

constexpr uint32_t step(uint32_t number) { return 0x90000u | number; }
constexpr uint32_t kFarewell = 0xa001c;         // group 10's partings
constexpr uint32_t kFarewellNoDeal = 0xa001d;

int32_t flowWindow(const TalkState& n) { return n.flowmsg[n.ekucyo]; }

void showFlowMessage(TalkState& n, int32_t message, bool select = false) { showTalkMessage(n, flowWindow(n), message, select); }

// The demon nods; the step goes on once it has.
void nod(TalkState& n) { n.waitframe = agreeMotion(n, *n.eform); }

// What the player got goes on record for the action.
void gained(TalkState& n) { n.actdata->stat |= kTalkGained; }

// Flow9_1 @ 0x00272718: the deal is struck; on to what the talk was for (the request
// kind: 0 joining, 1..5 a gift, 6 information). A demon whose race is not
// Wilder, Haunt or Foul counts its deals (cnt6_37); on the first, if it
// was to join and counter cnt6_36 is past 1, once event 8 is set it goes
// to candidate 4 instead (0x6004A) eight times in ten (never Kodama or
// Shikigami).
int32_t dealStruck(TalkState& n)
{
    addCandidate(n, step(2));
    addCandidate(n, step(11));
    addCandidate(n, step(19));
    addCandidate(n, 0x6004a);
    n.workid[6] = 0x60015;
    const Race race = dat::race(*n.ework);
    if (race != Race::Foul && race != Race::Haunt && race != Race::Wilder)
        ++n.cnt6_37;
    const uint16_t id = n.ework->id;
    if (n.talkRequestType == 0 && n.cnt6_36 > 1 && n.cnt6_37 == 1 && evt::BitCheck(8) && id != devil::Kodama &&
        id != devil::Shikigami && sdf::GetRandInt(10) < 8) {
        n.nextTalkId = n.candidates[3];
        return 0;
    }
    cameraOnTalkTarget(*n.eform);
    switch (n.talkRequestType) {
    case 0: n.nextTalkId = n.candidates[0]; break;
    case 1: case 2: case 3: case 4: case 5: n.nextTalkId = n.candidates[1]; break;
    case 6: n.nextTalkId = n.candidates[2]; break;
    default: break;
    }
    return 0;
}

// Flow9_2 @ 0x00272888: it nods and offers to join (message 0xA7).
int32_t offersToJoin(TalkState& n)
{
    if (n.talkPhase == 0) {
        nod(n);
    } else if (n.talkPhase == 1) {
        addCandidate(n, step(3));
        showFlowMessage(n, 0xa7);
    }
    return 0;
}

// Flow9_3 @ 0x00272908: with room in the stock, on to the level check; else 9_6.
int32_t checkStockRoom(TalkState& n)
{
    addCandidate(n, step(4));
    addCandidate(n, step(6));
    n.nextTalkId = n.candidates[dat::isStockFull() ? 1 : 0];
    return 0;
}

// Flow9_4 @ 0x00272960: a demon above the Demi-fiend's level won't join (9_9).
int32_t checkLevel(TalkState& n)
{
    addCandidate(n, step(5));
    addCandidate(n, step(9));
    diag::print(diag::Message::TalkLevels, dat::playerLevel(), n.ework->level);
    n.nextTalkId = n.candidates[dat::playerLevel() < n.ework->level ? 1 : 0];
    return 0;
}

// Flow9_5 @ 0x002729E8: it joins (help message 2).
int32_t joins(TalkState& n)
{
    gained(n);
    addCandidate(n, step(7));
    showTalkMessage(n, n.helpmsg, 2, false);
    return 0;
}

// Flow9_6 @ 0x00272A40: the stock is full (message 0xAB).
int32_t stockFull(TalkState& n)
{
    addCandidate(n, step(10));
    showFlowMessage(n, 0xab);
    return 0;
}

// Flow9_7 @ 0x00272A90: the talk ends with the demon joined (result 9).
int32_t joined(TalkState&) { return 9; }

// Flow9_9 @ 0x00272A98: the Demi-fiend is too weak for it (message 0xAC).
int32_t tooWeak(TalkState& n)
{
    addCandidate(n, step(10));
    showFlowMessage(n, 0xac);
    return 0;
}

// Flow9_10 @ 0x00272AE8: it can't join after all (message 0xAD), and leaves.
int32_t cannotJoin(TalkState& n)
{
    addCandidate(n, kFarewellNoDeal);
    showFlowMessage(n, 0xad);
    return 0;
}

// Flow9_11 @ 0x00272B38: a gift by the request kind: Macca (9_13) for 1 and 5, an item
// (9_16) for 3 and 4, either for 2. Any other kind becomes 1, and the step
// runs again.
int32_t chooseGift(TalkState& n)
{
    addCandidate(n, step(13));
    addCandidate(n, step(16));
    switch (n.talkRequestType) {
    case 1: case 5: n.nextTalkId = n.candidates[0]; break;
    case 2: n.nextTalkId = n.candidates[sdf::GetRandInt(2)]; break;
    case 3: case 4: n.nextTalkId = n.candidates[1]; break;
    default: n.talkRequestType = 1; break;
    }
    return 0;
}

// Flow9_13 @ 0x00272BE8: it nods and offers Macca (message 0xA8), half again as much
// for a Loan.
int32_t offersMacca(TalkState& n)
{
    if (n.talkPhase == 0) {
        nod(n);
    } else if (n.talkPhase == 1) {
        addCandidate(n, step(14));
        n.getmakka = demonGivesMacca(n, *n.pwork, *n.ework);
        if (n.talkSkill == skill::Loan)
            n.getmakka = n.getmakka * 3 / 2;
        setMaccaVariable(flowWindow(n), n.getmakka);
        showFlowMessage(n, 0xa8);
    }
    return 0;
}

// Flow9_14 @ 0x00272CB8: "got Macca" (help message 3).
int32_t receivesMacca(TalkState& n)
{
    gained(n);
    addCandidate(n, step(15));
    setMaccaVariable(n.helpmsg, n.getmakka);
    showTalkMessage(n, n.helpmsg, 3, false);
    return 0;
}

// Flow9_15 @ 0x00272D18: the Macca is added; a Loan counts against the demon's race
// (up to 255).
int32_t addsMacca(TalkState& n)
{
    addCandidate(n, kFarewell);
    dat::addMacca(n.getmakka);
    if (n.talkSkill == skill::Loan) {
        uint8_t& loans = dat::globalWork().loanCounts[static_cast<uint8_t>(dat::devilFormat(n.ework->id).race)];
        if (loans != 0xff)
            ++loans;
    }
    return 0;
}

// Flow9_16 @ 0x00272DA0: an item from its talk record (a stone for request kind 3;
// item 6 or 0x6A when it has none, though every demon's gifts add up to
// 100). If the player can't carry more, it
// says so (message 0x97) and gives Macca instead (9_14); else it nods and
// offers the item (message 0xA9).
int32_t offersItem(TalkState& n)
{
    switch (n.talkPhase) {
    case 0:
        if (n.talkRequestType == 3) {
            n.getitem = demonGivesStone(*n.ework);
            if (n.getitem == 0)
                n.getitem = 0x6a;
        } else {
            n.getitem = demonGivesItem(*n.ework);
            if (n.getitem == 0)
                n.getitem = 6;
        }
        if (dat::isItemFull(n.getitem)) {
            setItemVariable(flowWindow(n), n.getitem);
            showFlowMessage(n, 0x97);
            n.getmakka = demonGivesMacca(n, *n.pwork, *n.ework);
            addCandidate(n, step(14));
        }
        break;
    case 1:
        nod(n);
        break;
    case 2:
        addCandidate(n, step(17));
        setItemVariable(flowWindow(n), n.getitem);
        showFlowMessage(n, 0xa9);
        break;
    default:
        break;
    }
    return 0;
}

// Flow9_17 @ 0x00272F08: "got the item" (help message 5).
int32_t receivesItem(TalkState& n)
{
    gained(n);
    addCandidate(n, step(18));
    setItemVariable(n.helpmsg, n.getitem);
    showTalkMessage(n, n.helpmsg, 5, false);
    return 0;
}

// Flow9_18 @ 0x00272F68: the item is added.
int32_t addsItem(TalkState& n)
{
    addCandidate(n, kFarewell);
    dat::addItem(n.getitem, 1);
    return 0;
}

// Flow9_19 @ 0x00272FA8: it nods and offers to tell something (message 0xAA).
int32_t offersInformation(TalkState& n)
{
    if (n.talkPhase == 0) {
        nod(n);
    } else if (n.talkPhase == 1) {
        addCandidate(n, step(20));
        showFlowMessage(n, 0xaa);
    }
    return 0;
}

// Flow9_20 @ 0x00273028: asks what about (message 0x112, then selection 0x113); the
// second answer asks for the second kind of information.
int32_t asksWhatAbout(TalkState& n)
{
    if (n.talkPhase == 0) {
        showFlowMessage(n, 0x112);
    } else if (n.talkPhase == 1) {
        showFlowMessage(n, 0x113, true);
    } else if (n.talkPhase == 2) {
        n.getinfotype = n.nowselect != 0 ? 2 : 0;
        addCandidate(n, step(21));
    }
    return 0;
}

// Flow9_21 @ 0x002730D8: the information is chosen.
int32_t choosesInformation(TalkState& n)
{
    gained(n);
    addCandidate(n, step(22));
    n.getinfomsg = pickInfoMessage(n.getinfotype);
    return 0;
}

// Flow9_22 @ 0x00273128: it tells it (from its information table).
int32_t tellsInformation(TalkState& n)
{
    addCandidate(n, kFarewell);
    showTalkMessage(n, n.infomsg[n.ekucyo], n.getinfomsg, false);
    return 0;
}

} // namespace

const TalkStep kDealSteps[23] = {
    nullptr,          dealStruck,      offersToJoin,     checkStockRoom,     checkLevel,
    joins,            stockFull,       joined,           nullptr,            tooWeak,
    cannotJoin,       chooseGift,      nullptr,          offersMacca,        receivesMacca,
    addsMacca,        offersItem,      receivesItem,     addsItem,           offersInformation,
    asksWhatAbout,    choosesInformation, tellsInformation,
};

// nbNegoFlowOk @ 0x00273178
int32_t dealFlow(TalkState& n) { return kDealSteps[n.talkId & 0xffff](n); }

} // namespace nocturne::nb
