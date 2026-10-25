// The talks' group 15 (original unit: NbNegoFlowInoti, "life"): the last
// enemy, near death, begs for its life. It offers to join, Macca, an item
// or information; spared, it keeps its word or runs off. Rewritten from the
// original instructions. Messages are in the demon's flow table or the help
// table.
#include "nocturne/battle/talk_flow.hpp"

#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"
#include "nocturne/build.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t step(uint32_t number) { return 0xf0000u | number; }

// What it offers (TalkState::requesttype here).
enum Offer : int32_t { kOfferJoin, kOfferMacca, kOfferItem, kOfferInformation };

int32_t flowWindow(const TalkState& n) { return n.flowmsg[n.ekucyo]; }

// Flow15_1 @ 0x00278CB8: on to the first group's step 0x1001F, this
// group's step 5 noted for later (workid[3]).
int32_t begs(TalkState& n)
{
    addCandidate(n, 0x1001f);
    n.workid[3] = step(5);
    return 0;
}

// Flow15_5 @ 0x00278CF8: what it offers, at random (Wilders, Haunts and
// Foul: always to join). Macca instead of joining when one like it is in
// the stock, the stock is full or it is above the Demi-fiend's level, and
// instead of an item (its second list's, item 1 when none) the player
// can't carry.
int32_t choosesOffer(TalkState& n)
{
    addCandidate(n, step(6));
    n.requesttype = static_cast<int32_t>(sdf::GetRandInt(4));
    const Race race = dat::race(*n.ework);
    if (race == Race::Wilder || race == Race::Haunt || race == Race::Foul)
        n.requesttype = kOfferJoin;
    if (n.requesttype == kOfferJoin &&
        (dat::findDevil(n.ework->id) >= 0 || dat::isStockFull() || dat::playerLevel() < n.ework->level))
        n.requesttype = kOfferMacca;
    if (n.requesttype == kOfferItem) {
        const int32_t item = demonGivesItemB(*n.ework);
        n.requestdata = item != 0 ? item : 1;
        if (dat::isItemFull(n.requestdata))
            n.requesttype = kOfferMacca;
    }
    if (n.requesttype == kOfferMacca)
        n.requestdata = demonGivesMaccaB(n, *n.pwork, *n.ework);
    return 0;
}

// Flow15_6 @ 0x00278E40: the offer (messages 0x10A..0x10D).
int32_t offers(TalkState& n)
{
    addCandidate(n, step(7));
    int32_t message = 0;
    switch (n.requesttype) {
    case kOfferJoin:
        message = 0x10a;
        break;
    case kOfferMacca:
        message = 0x10b;
        setMaccaVariable(flowWindow(n), n.requestdata);
        setMaccaVariable(n.helpmsg, n.requestdata);
        break;
    case kOfferItem:
        message = 0x10c;
        setItemVariable(flowWindow(n), n.requestdata);
        setItemVariable(n.helpmsg, n.requestdata);
        break;
    case kOfferInformation:
        message = 0x10d;
        break;
    default:
        break;
    }
    showTalkMessage(n, flowWindow(n), message, false);
    return 0;
}

// Flow15_7 @ 0x00278F40: spare it? (selection 0xD2): yes 15_8, no 15_23.
int32_t spareIt(TalkState& n)
{
    if (n.talkPhase == 0) {
        showTalkMessage(n, flowWindow(n), 0xd2, true);
    } else if (n.talkPhase == 1) {
        addCandidate(n, step(8));
        addCandidate(n, step(23));
        n.nextTalkId = n.candidates[n.nowselect == 0 ? 0 : 1];
    }
    return 0;
}

// Flow15_8 @ 0x00278FD8: spared, it keeps its word (15_10) 85 times in a
// hundred, 40 for a demon of honbou type 1 (none is); else it runs off
// (15_20).
int32_t keepsWord(TalkState& n)
{
    addCandidate(n, step(10));
    addCandidate(n, step(20));
    const int32_t chance = dat::devilTalkFormat(n.ework->id).honboutype == 1 ? 40 : 85;
    n.nextTalkId = n.candidates[static_cast<int32_t>(sdf::GetRandInt(100)) < chance ? 0 : 1];
    return 0;
}

// Flow15_10 @ 0x00279078: it nods and makes good on the offer (message
// 0x117 joining, else 0x10F).
int32_t makesGood(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = agreeMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        addCandidate(n, step(11));
        addCandidate(n, step(12));
        addCandidate(n, step(13));
        addCandidate(n, step(14));
        if (n.requesttype >= kOfferJoin && n.requesttype <= kOfferInformation) {
            showTalkMessage(n, flowWindow(n), n.requesttype == kOfferJoin ? 0x117 : 0x10f, false);
            n.nextTalkId = n.candidates[n.requesttype];
        }
    }
    return 0;
}

// Flow15_11 @ 0x002791E8: it joins (help message 2; result 3).
int32_t joins(TalkState& n)
{
    showTalkMessage(n, n.helpmsg, 2, false);
    return 3;
}

// Flow15_12 @ 0x00279210: "got Macca" (help message 3).
int32_t givesMacca(TalkState& n)
{
    addCandidate(n, step(17));
    showTalkMessage(n, n.helpmsg, 3, false);
    return 0;
}

// Flow15_13 @ 0x00279258: "got the item" (help message 5).
int32_t givesItem(TalkState& n)
{
    addCandidate(n, step(18));
    showTalkMessage(n, n.helpmsg, 5, false);
    return 0;
}

// Flow15_14 @ 0x002792A0: the information, of either kind at random.
int32_t choosesInformation(TalkState& n)
{
    addCandidate(n, step(19));
    n.getinfotype = sdf::GetRandInt(2) == 0 ? 0 : 2;
    n.getinfomsg = pickInfoMessage(n.getinfotype);
    return 0;
}

// Flow15_17 @ 0x00279300: the Macca is added; it leaves.
int32_t addsMacca(TalkState& n)
{
    addCandidate(n, 0xa001d);
    dat::addMacca(n.requestdata);
    return 0;
}

// Flow15_18 @ 0x00279338: the item (any but 0) is added; it leaves.
int32_t addsItem(TalkState& n)
{
    addCandidate(n, 0xa001d);
    if (static_cast<uint32_t>(n.requestdata) - 1 < static_cast<uint32_t>(kItemCount - 1))
        dat::addItem(n.requestdata, 1);
    return 0;
}

// Flow15_19 @ 0x00279388: it tells it (from its information table).
int32_t tells(TalkState& n)
{
    addCandidate(n, 0xa001c);
    showTalkMessage(n, n.infomsg[n.ekucyo], n.getinfomsg, false);
    return 0;
}

// Flow15_20 @ 0x002793D8: it runs off (message 0x10E, in the step's second
// call).
int32_t runsOff(TalkState& n)
{
    if (n.talkPhase == 1) {
        addCandidate(n, step(22));
        showTalkMessage(n, flowWindow(n), 0x10e, false);
    }
    return 0;
}

// Flow15_22 @ 0x00279440 (result 4)
int32_t ranOff(TalkState&) { return 4; }

// Flow15_23 @ 0x00279448: not spared (message 0x115; result 7).
int32_t notSpared(TalkState& n)
{
    showTalkMessage(n, flowWindow(n), 0x115, false);
    return 7;
}

} // namespace

const TalkStep kMercySteps[24] = {
    nullptr,  begs,      nullptr,   nullptr,    nullptr,     choosesOffer, offers,  spareIt,
    keepsWord, nullptr,  makesGood, joins,      givesMacca,  givesItem,    choosesInformation, nullptr,
    nullptr,  addsMacca, addsItem,  tells,      runsOff,     nullptr,      ranOff,  notSpared,
};

// nbNegoFlowInoti @ 0x00279480
int32_t mercyFlow(TalkState& n) { return kMercySteps[n.talkId & 0xffff](n); }

} // namespace nocturne::nb
