// The talks' group 5 (original unit: NbNegoFlowInnen, "fate"): a fated
// pair meets, a devil on the player's side and the demon (the table at
// 0x3E3158, nbGetInnenNegoID). Once per pair (event 0xB00 + the pair), and
// not with the demon already in the stock, they play out their exchange
// from the record: its messages, with nods and head shakes, then gifts or
// a fight. Rewritten from the original instructions. Messages are in the
// fated pairs' table or the help table. Several of its steps are empty.
#include "nocturne/address.hpp"
#include "nocturne/battle/talk_flow.hpp"

#include "nocturne/battle/kouka.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t step(uint32_t number) { return 0x50000u | number; }

// A fated pair's record (datInnenNegoTable_t, 0x3C bytes).
struct FatedPair {
    int16_t used;               // (HD: check)
    uint16_t playerDevil, demon;   // (HD: id1, id2)
    int16_t outcome;            // 0: gifts, 1: a fight (result 4) (HD: result)
    struct { uint16_t item, count; } gifts[6];   // up to the first with no item; no pair has more than two (HD: item)
    uint16_t firstMessage, messageCount;          // the exchange (HD: mainmes, mescnt)
    uint16_t winMessage, loseMessage;             // steps 5_15's and 5_14's; the same in every pair (HD: winmes, losemes)
    uint16_t fullMessage;                         // (HD: fullmes; unused here)
    struct { int16_t message, who, nod; } motions[3];   // (HD: innen_motion) on the exchange's message (1-based): who 1 the
                                                        // player's devil, else the demon; nod 1, else a head shake
};
static_assert(sizeof(FatedPair) == 0x3c);
constexpr uint32_t kFatedPairs = addr(0x003e3158);

const FatedPair& pairOf(const TalkState& n) { return guest::table<const FatedPair>(kFatedPairs)[n.innen_id]; }

// The pair's gift `index` (read past the six as the original does: the
// record's next fields).
uint16_t giftItem(const TalkState& n, int32_t index)
{
    return *guest::table<const uint16_t>(kFatedPairs + static_cast<uint32_t>(n.innen_id * 0x3c + 8 + index * 4));
}

// All the gifts are added.
void addGifts(TalkState& n)
{
    const FatedPair& pair = pairOf(n);
    for (int32_t i = 0; i < 6 && pair.gifts[i].item != 0; ++i) {
        n.getitem = pair.gifts[i].item;
        dat::addItem(pair.gifts[i].item, pair.gifts[i].count);
    }
}

// Each gift in turn (a step's phase), shown with the help message; the
// talk ends with `result` after the last.
int32_t showGift(TalkState& n, int32_t message, int32_t result)
{
    const uint16_t item = giftItem(n, n.talkPhase);
    if (item == 0)
        return result;
    n.getitem = item;
    setItemVariable(n.helpmsg, item);
    showTalkMessage(n, n.helpmsg, message, false);
    return 0;
}

// Flow5_1 @ 0x00275780
int32_t fateBegins(TalkState& n)
{
    addCandidate(n, step(2));
    return 0;
}

// Flow5_2 @ 0x002757A8: the exchange (5_3), once per pair and not with the
// demon in the stock; else an ordinary talk (0x10021).
int32_t firstMeeting(TalkState& n)
{
    addCandidate(n, step(3));
    addCandidate(n, 0x10021);
    if (dat::findDevil(n.ework->id) < 0 && !evt::BitCheck(n.innen_id + 0xb00)) {
        n.nextTalkId = n.candidates[0];
        evt::BitOn(n.innen_id + 0xb00);
    } else {
        n.nextTalkId = n.candidates[1];
    }
    return 0;
}

// Flow5_3 @ 0x00275840: the exchange, a message a call, each with its
// nods and head shakes; then on to 5_4.
int32_t exchange(TalkState& n)
{
    const FatedPair& pair = pairOf(n);
    if (n.talkPhase >= pair.messageCount) {
        addCandidate(n, step(4));
        return 0;
    }
    showTalkMessage(n, n.innenmsg, pair.firstMessage + n.talkPhase, false);
    for (const auto& motion : pair.motions)
        if (motion.message == n.talkPhase + 1)
            addMotionPacket(0, 0, motion.who == 1 ? n.pform.get() : n.eform.get(), motion.nod == 1 ? 14 : 15);
    return 0;
}

// Flow5_4 @ 0x002759A8: gifts (5_6), or a fight (result 4).
int32_t outcome(TalkState& n)
{
    switch (pairOf(n).outcome) {
    case 0:
        addCandidate(n, step(6));
        n.nextTalkId = n.candidates[0];
        return 0;
    case 1:
        return 4;
    default:
        return 0;
    }
}

// Flow5_6 @ 0x00275A20: the gifts are added; then shown (5_9).
int32_t givesGifts(TalkState& n)
{
    addGifts(n);
    addCandidate(n, step(9));
    return 0;
}

// Flow5_9 @ 0x00275B08: the gifts, one a call (help message 8); the talk
// ends (result 2).
int32_t showsGifts(TalkState& n) { return showGift(n, 8, 2); }

// Flow5_14 @ 0x00275BA8: the pair's lose message; the talk ends (result 6).
int32_t lost(TalkState& n)
{
    showTalkMessage(n, n.innenmsg, pairOf(n).loseMessage, false);
    return 6;
}

// Flow5_15 @ 0x00275BF0: the pair's win message; on to the gifts (5_18).
int32_t won(TalkState& n)
{
    addCandidate(n, step(18));
    showTalkMessage(n, n.innenmsg, pairOf(n).winMessage, false);
    return 0;
}

// Flow5_18 @ 0x00275C60: the gifts are added; then shown (5_21).
int32_t givesGiftsAgain(TalkState& n)
{
    addGifts(n);
    addCandidate(n, step(21));
    return 0;
}

// Flow5_21 @ 0x00275D48: the gifts, one a call (help message 5); the talk
// ends (result 6).
int32_t showsGiftsAgain(TalkState& n) { return showGift(n, 5, 6); }

// Flow5_5 @ 0x00275A18
// Flow5_7 @ 0x00275AF8
// Flow5_8 @ 0x00275B00
// Flow5_10 @ 0x00275B88
// Flow5_11 @ 0x00275B90
// Flow5_12 @ 0x00275B98
// Flow5_13 @ 0x00275BA0
// Flow5_16 @ 0x00275C50
// Flow5_17 @ 0x00275C58
// Flow5_19 @ 0x00275D38
// Flow5_20 @ 0x00275D40
// The empty steps.
int32_t nothing(TalkState&) { return 0; }

} // namespace

const TalkStep kFatedSteps[22] = {
    nullptr,  fateBegins, firstMeeting, exchange, outcome,   nothing,   givesGifts, nothing,
    nothing,  showsGifts, nothing,      nothing,  nothing,   nothing,   lost,       won,
    nothing,  nothing,    givesGiftsAgain, nothing, nothing, showsGiftsAgain,
};

// nbNegoFlowInnen @ 0x00275DC8
int32_t fatedFlow(TalkState& n) { return kFatedSteps[n.talkId & 0xffff](n); }

} // namespace nocturne::nb
