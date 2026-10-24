// The talks' group 4 (original unit: NbNegoFlowDouchara, "the same
// character"): the demon meets one of its own kind on the player's side.
// A few have their own words and leave it at that; the others give Macca,
// an item or the talker's full health, or just leave. Rewritten from the
// original instructions. Messages are in the demon's flow table or the
// help tables.
#include "nocturne/battle/talk_flow.hpp"

#include "nocturne/data/ids.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/external.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t step(uint32_t number) { return 0x40000u | number; }

int32_t flowWindow(const TalkState& n) { return n.flowmsg[n.ekucyo]; }

// The kin with words of their own (their flow message).
struct OwnWords { uint16_t devil; int32_t message; };
constexpr OwnWords kOwnWords[] = {
    {devil::Sarutahiko, 0x8c}, {devil::Setanta, 0x8d}, {devil::Mada, 0x81}, {devil::Girimehkala, 0x82},
    {devil::TaoTie, 0x83},     {devil::Pazuzu, 0x84},  {devil::Baphomet, 0x85}, {devil::Mot, 0x86},
    {devil::Aciel, 0x87},      {devil::Surt, 0x88},    {devil::Abaddon, 0x89},  {devil::Loki, 0x8a},
    {devil::Gurr, 0x8b},
};

// Flow4_1 @ 0x00274F38: a pause, then the kin's own words (and the talk
// ends, result 2), or a greeting (message 0x31).
int32_t meetsKin(TalkState& n)
{
    addCandidate(n, step(2));
    n.waitframe = 15;
    for (const OwnWords& words : kOwnWords)
        if (n.ework->id == words.devil && n.pwork->id == words.devil) {
            showTalkMessage(n, flowWindow(n), words.message, false);
            return 2;
        }
    showTalkMessage(n, flowWindow(n), 0x31, false);
    return 0;
}

// Flow4_2 @ 0x00275280: a gift (4_3) or a parting (4_12), at random.
int32_t giftOrParting(TalkState& n)
{
    addCandidate(n, step(3));
    addCandidate(n, step(12));
    n.nextTalkId = n.candidates[sdf::GetRandInt(2)];
    return 0;
}

// Flow4_3 @ 0x002752E0
int32_t gift(TalkState& n)
{
    addCandidate(n, step(4));
    return 0;
}

// Flow4_4 @ 0x00275308: Macca, an item or healing, at random.
int32_t chooseGift(TalkState& n)
{
    addCandidate(n, step(5));
    addCandidate(n, step(6));
    addCandidate(n, step(7));
    n.nextTalkId = n.candidates[sdf::GetRandInt(3)];
    return 0;
}

// Flow4_5 @ 0x00275378: Macca (message 0x33).
int32_t offersMacca(TalkState& n)
{
    addCandidate(n, step(8));
    n.getmakka = demonGivesMaccaB(n, *n.pwork, *n.ework);
    setMaccaVariable(flowWindow(n), n.getmakka);
    showTalkMessage(n, flowWindow(n), 0x33, false);
    return 0;
}

// Flow4_6 @ 0x002753F8: an item from its second list (item 0x12 when it
// has none; every demon has some); Macca instead when the player can't
// carry more.
int32_t offersItem(TalkState& n)
{
    addCandidate(n, step(9));
    addCandidate(n, step(5));
    n.getitem = demonGivesItemB(*n.ework);
    if (n.getitem == 0)
        n.getitem = 0x12;
    if (!dat::isItemFull(n.getitem)) {
        setItemVariable(flowWindow(n), n.getitem);
        showTalkMessage(n, flowWindow(n), 0x34, false);
    } else {
        n.nextTalkId = n.candidates[1];
    }
    return 0;
}

// Flow4_7 @ 0x002754A8: healing (message 0x35).
int32_t offersHealing(TalkState& n)
{
    addCandidate(n, step(10));
    showTalkMessage(n, flowWindow(n), 0x35, false);
    return 0;
}

// Flow4_8 @ 0x002754F8: the Macca is added.
int32_t addsMacca(TalkState& n)
{
    addCandidate(n, step(11));
    dat::addMacca(n.getmakka);
    return 0;
}

// Flow4_9 @ 0x00275530: the item is added.
int32_t addsItem(TalkState& n)
{
    addCandidate(n, step(11));
    dat::addItem(n.getitem, 1);
    return 0;
}

// Flow4_10 @ 0x00275570: the talker is shown healed to full (the numbers
// and the effect; the panel back on to show it).
int32_t heals(TalkState& n)
{
    addCandidate(n, step(11));
    closeTalkWindow(n);
    PanelSetEnabled(true);
    MakeHealPackets(0, 0, n.pform.get(), 0, n.pwork->maxhp, -1, 0);
    AddHitEffPacket(0, 0, *n.pform, 8);
    n.waitframe = 0;
    return 0;
}

// Flow4_11 @ 0x002755F0: what the player got (help messages 3 Macca, 5 an
// item; the second help table's 7 healing, with a second's wait).
int32_t received(TalkState& n)
{
    addCandidate(n, step(12));
    PanelSetEnabled(false);
    switch (previousTalkId(n)) {
    case step(8):
        setMaccaVariable(n.helpmsg, n.getmakka);
        showTalkMessage(n, n.helpmsg, 3, false);
        break;
    case step(9):
        setItemVariable(n.helpmsg, n.getitem);
        showTalkMessage(n, n.helpmsg, 5, false);
        break;
    case step(10):
        showTalkMessage(n, n.helpmsg2, 7, false);
        n.waitframe = 60;
        break;
    default:
        break;
    }
    return 0;
}

// Flow4_12 @ 0x002756D8: a parting word (message 0x32).
int32_t parts(TalkState& n)
{
    addCandidate(n, step(13));
    showTalkMessage(n, flowWindow(n), 0x32, false);
    return 0;
}

// Flow4_13 @ 0x00275728: it leaves (help message 1); the talk ends
// (result 2).
int32_t leaves(TalkState& n)
{
    showTalkMessage(n, n.helpmsg, 1, false);
    return 2;
}

} // namespace

const TalkStep kKinSteps[14] = {
    nullptr,     meetsKin,  giftOrParting, gift,     chooseGift, offersMacca, offersItem,
    offersHealing, addsMacca, addsItem,    heals,    received,   parts,       leaves,
};

// nbNegoFlowDouchara @ 0x00275750
int32_t kinFlow(TalkState& n) { return kKinSteps[n.talkId & 0xffff](n); }

} // namespace nocturne::nb
