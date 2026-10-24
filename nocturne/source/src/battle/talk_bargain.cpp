// The talks' group 6 (original unit: NbNegoFlowTwo): the bargaining. The
// talk skill's affinity rules set how the demon is disposed (6_1); it asks
// for something (an item, Macca, HP or MP, a question, nothing), the player
// gives or refuses, and the weights of the talk skill (6_24), shifted by
// the disposition and the round, decide whether it agrees (group 9), talks
// on, asks a question (group 7) or refuses (group 10). A helper in the
// party may step in with a talk skill (6_51..6_57, 6_74). Rewritten from
// the original instructions. Messages are in the demon's flow or affinity
// table, or the help tables.
#include "nocturne/battle/talk_flow.hpp"

#include "nocturne/battle/camera.hpp"
#include "nocturne/battle/formation.hpp"
#include "nocturne/battle/help.hpp"
#include "nocturne/battle/kouka.hpp"
#include "nocturne/battle/macca_window.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t step(uint32_t number) { return 0x60000u | number; }
constexpr uint32_t kDeal = 0x90001;
constexpr uint32_t kNoDeal = 0xa0001;
constexpr uint32_t kHelperLeaves = step(0x4a);       // 6_74: the helper's way back, then workid[6]
constexpr uint32_t kHelperStepsIn = step(0x34);      // 6_52: then workid[0] or [1]
constexpr uint32_t kDemand = step(0x46);             // 6_70: give it?
constexpr uint32_t kMovePacketsAway = 0x00265298;     // a unit steps back, fading out (VU0)
constexpr uint32_t kMovePacketsOut = 0x00265130;      // ... steps aside, turning
constexpr uint32_t kMovePacketsIn = 0x002653a0;       // ... steps forward, fading in

// What the demon asks for (TalkState::requesttype here).
enum Request : int32_t { kAskItem, kAskMacca, kAskQuestion, kAskDrain, kAskFight, kAskMaccaGift };

int32_t flowWindow(const TalkState& n) { return n.flowmsg[n.ekucyo]; }

void showFlowMessage(TalkState& n, int32_t message, bool select = false) { showTalkMessage(n, flowWindow(n), message, select); }

const TalkSkill& talkSkillOf(int32_t skill) { return guest::table<const TalkSkill>(kTalkSkillTable)[skill - 0x180]; }

// The early demons that are kinder before event 8.
bool youngDemon(uint16_t id) { return id == devil::Kodama || id == devil::Pixie || id == devil::Shikigami || id == devil::HuaPo; }

// ... and the ones a Taunt-like helper skill (0x19D) can't move.
bool unmovedBy19d(uint16_t id)
{
    return id == devil::PyroJack || id == devil::JackFrost || id == devil::Pixie || id == devil::HuaPo ||
           id == devil::Sudama || id == devil::Kodama;
}

bool behindOnStat1(const UnitWork& a, const UnitWork& b, int32_t margin)
{
    return dat::param(a, Param::Unused1) < dat::param(b, Param::Unused1) - margin;
}

int32_t roundMacca(int32_t value)
{
    value = (value + 5) / 10 * 10;
    return value != 0 ? value : 1;
}

// A message not the last one shown of four (base..base + 3).
int32_t freshMessage(int32_t base, int32_t& last)
{
    int32_t message;
    do
        message = base + static_cast<int32_t>(sdf::GetRandInt(4));
    while (message == last);
    last = message;
    return message;
}

// The helper in buffPartyIndex: its unit and its formation.
UnitWork& helperUnit(TalkState& n) { return *GetUnitWorkPointer(*n.data, n.data->party[n.buffPartyIndex]); }
Formation& helperForm(TalkState& n)
{
    return guest::table<Formation>(n.data->form.address)[n.data->party[n.buffPartyIndex].formindex];
}

void movePackets(uint32_t entry, TalkState& n, Formation& form, Formation& target)
{
    guest::callMovePackets(entry, 0, static_cast<int32_t>(n.actdata.address), guest::addressOf(&form), guest::addressOf(&target));
}

// A helper's skill for the moment, kept (party slot << 16 | skill).
bool takeHelper(TalkState& n, int32_t moment)
{
    const uint32_t buff = useBuffSkill(n, moment);
    if (buff == 0)
        return false;
    n.buffPartyIndex = static_cast<int32_t>(buff >> 16);
    n.buffSkill = static_cast<int32_t>(buff & 0xffff);
    return true;
}

} // namespace

// ChkAisyo @ 0x0026EB08
bool checkAffinity(const UnitWork& a, const UnitWork& b, uint32_t jo, int32_t sw)
{
    switch (jo) {
    case 0x80000001:
        if (b.level - 10 < a.level)
            return false;
        return sdf::GetRandInt(100) <= 0x45;
    case 0x80000000:
        if (evt::GetAgeOfMoon() != 0)
            return false;
        return dat::devilFormat(b.id).race != Race::Tyrant;
    case 0x80000002:
        if (sw != 0)
            return false;
        return (dat::devilTalkFormat(b.id).speechTrait & 2) != 0;
    default:
        break;
    }
    const uint32_t traits = a.isPlayerCharacter() ? 0x14 : dat::devilTalkFormat(a.id).speechTrait;
    for (int32_t i = 0; i < 31; ++i) {
        const uint32_t bit = 1u << i;
        if (!(jo & bit))
            continue;
        switch (bit) {
        case 2: case 4: case 8: case 0x10: case 0x20:
            if (!(traits & bit))
                return false;
            break;
        case 0x40:
            if (a.level < b.level + 10u)
                return false;
            break;
        case 0x80:
            if (b.level - 10 < a.level)
                return false;
            break;
        case 0x100:
            if (a.isPlayerCharacter() || b.isPlayerCharacter() || dat::devilFormat(a.id).race != dat::devilFormat(b.id).race)
                return false;
            break;
        case 0x200:
            if (static_cast<int16_t>(a.id) != devil::Valkyrie)
                return false;
            break;
        case 0x400:
            if (static_cast<int16_t>(a.id) != devil::KikuriHime)
                return false;
            break;
        default:
            break;
        }
    }
    return true;
}

// nbChkNegoAisyo @ 0x0026EE90
bool pairAffinity(const TalkState& n, uint32_t mine, uint32_t theirs, int32_t sw)
{
    return pairAffinity(*n.pwork, *n.ework, mine, theirs, sw);
}

// nbChkNegoAisyo2 @ 0x0026EF18 (both checks are made)
bool pairAffinity(const UnitWork& s, const UnitWork& d, uint32_t mine, uint32_t theirs, int32_t sw)
{
    const bool one = checkAffinity(s, d, mine, sw);
    const bool other = checkAffinity(d, s, theirs, sw);
    return one && other;
}

namespace {

// Flow6_1 @ 0x0026EFA0: the demon's disposition by the talk skill's rules:
// well disposed (6_3), badly (6_6) or neither (6_2). With the stock full,
// a talk to recruit ends at 9_6.
int32_t disposition(TalkState& n)
{
    addCandidate(n, step(3));
    addCandidate(n, step(0x50));
    addCandidate(n, step(6));
    addCandidate(n, 0x90006);
    addCandidate(n, step(2));
    if (dat::isStockFull() && n.talkRequestType == 0) {
        n.nextTalkId = n.candidates[3];
        return 0;
    }
    const TalkSkill& skill = talkSkillOf(static_cast<int32_t>(n.talkSkill));
    n.affinity = 0;
    for (const TalkSkillRule& rule : skill.good)
        if ((rule.mine != 0 || rule.theirs != 0) && pairAffinity(n, rule.mine, rule.theirs, 1)) {
            n.affinity = 1;
            n.affinityMessage = rule.message;
            break;
        }
    if (n.affinity == 0)
        for (const TalkSkillRule& rule : skill.bad)
            if ((rule.mine != 0 || rule.theirs != 0) && pairAffinity(n, rule.mine, rule.theirs, 0)) {
                n.affinity = 2;
                n.affinityMessage = rule.message;
                break;
            }
    switch (n.affinity) {
    case 0: n.nextTalkId = step(2); break;
    case 1: n.nextTalkId = step(3); break;
    case 2: n.nextTalkId = step(6); break;
    default: break;
    }
    return 0;
}

// Flow6_2 @ 0x0026F1F0: neither: a talker with Charisma goes on (6_80);
// else an opening word (0x1C..0x1F) and the request (6_9).
int32_t neutral(TalkState& n)
{
    addCandidate(n, step(9));
    addCandidate(n, step(0x50));
    if (dat::hasSkill(*n.pwork, skill::Charisma)) {
        n.nextTalkId = n.candidates[1];
    } else {
        showFlowMessage(n, freshMessage(0x1c, n.mes6_2));
        n.nextTalkId = n.candidates[0];
    }
    return 0;
}

// Flow6_3 @ 0x0026F3A0: well disposed: it nods (the rule's message).
int32_t wellDisposed(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = agreeMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        addCandidate(n, step(4));
        showTalkMessage(n, n.aisyomsg[n.ekucyo], n.affinityMessage, false);
    }
    return 0;
}

// Flow6_4 @ 0x0026F420: a deal at once 65 times in a hundred; else 6_5.
int32_t dealAtOnce(TalkState& n)
{
    addCandidate(n, step(5));
    addCandidate(n, kDeal);
    n.nextTalkId = n.candidates[static_cast<int32_t>(sdf::GetRandInt(100)) < 0x41 ? 1 : 0];
    return 0;
}

// Flow6_5 @ 0x0026F488 (affinity message 0x26), then the request.
int32_t wellDisposedTalks(TalkState& n)
{
    addCandidate(n, step(9));
    showTalkMessage(n, n.aisyomsg[n.ekucyo], 0x26, false);
    return 0;
}

// Flow6_6 @ 0x0026F4D8: badly disposed: it shakes its head (the rule's
// message).
int32_t badlyDisposed(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = refuseMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        addCandidate(n, step(7));
        showTalkMessage(n, n.aisyomsg[n.ekucyo], n.affinityMessage, false);
    }
    return 0;
}

// Flow6_7 @ 0x0026F558: no deal at once 70 times in a hundred; else 6_8.
int32_t noDealAtOnce(TalkState& n)
{
    addCandidate(n, step(8));
    addCandidate(n, kNoDeal);
    n.nextTalkId = n.candidates[static_cast<int32_t>(sdf::GetRandInt(100)) < 0x46 ? 1 : 0];
    return 0;
}

// Flow6_8 @ 0x0026F5C0 (affinity message 0x27), then the request.
int32_t badlyDisposedTalks(TalkState& n)
{
    addCandidate(n, step(9));
    showTalkMessage(n, n.aisyomsg[n.ekucyo], 0x27, false);
    return 0;
}

// Flow6_9 @ 0x0026F610: what it asks for, from its talk record's request
// weights, not twice the same kind running (nor a fight after the first
// two asks: no demon's weights hold one); a talk to recruit asks an item, a
// gift-asking skill Macca.
int32_t asksFor(TalkState& n)
{
    addCandidate(n, step(0x11));
    addCandidate(n, step(0x15));
    addCandidate(n, step(0xb));
    addCandidate(n, step(0xa));
    addCandidate(n, step(0xc));
    int32_t request;
    for (;;) {
        request = pickRequestType(dat::devilTalkFormat(n.ework->id).reqtype);
        if (static_cast<uint32_t>(n.prevreqtype) < 2)
            break;
        if (request != kAskFight && request != n.prevreqtype)
            break;
    }
    n.requestdata = 0;
    if (n.talkRequestType == 4)
        request = kAskItem;
    if (n.talkRequestType == 5)
        request = kAskMaccaGift;
    n.requesttype = request;
    diag::print(diag::Message::TalkRequest, request);
    switch (request) {
    case kAskItem: case kAskMacca: n.nextTalkId = n.candidates[0]; break;
    case kAskQuestion: n.nextTalkId = n.candidates[1]; break;
    case kAskDrain: n.nextTalkId = n.candidates[2]; break;
    case kAskFight: n.nextTalkId = n.candidates[3]; break;
    case kAskMaccaGift: n.nextTalkId = n.candidates[4]; break;
    default: break;
    }
    n.prevreqtype = request;
    return 0;
}

// Flow6_10 @ 0x0026F778: it wants a fight (message 0x42), then the demand.
int32_t wantsFight(TalkState& n)
{
    if (n.requesttype != kAskFight) {
        n.prevreqtype = kAskFight;
        n.requesttype = kAskFight;
    }
    addCandidate(n, kDemand);
    showFlowMessage(n, 0x42);
    return 0;
}

// Flow6_11 @ 0x0026F7E0: it wants to drain (message 0x41), then the demand.
int32_t wantsDrain(TalkState& n)
{
    if (n.requesttype != kAskDrain) {
        n.prevreqtype = kAskDrain;
        n.requesttype = kAskDrain;
    }
    addCandidate(n, kDemand);
    showFlowMessage(n, 0x41);
    return 0;
}

// Flow6_12 @ 0x0026F848: it offers Macca (its gift amount) to a talker
// well above its level, the more the further above (20..97 in a hundred,
// none at gaps of 9, 14, 19 and 24 levels: the bands don't meet): 6_14;
// else 6_13.
int32_t offersMacca(TalkState& n)
{
    if (n.requesttype != kAskMaccaGift) {
        n.prevreqtype = kAskMaccaGift;
        n.requesttype = kAskMaccaGift;
    }
    n.requestdata = demonGivesMacca(n, *n.pwork, *n.ework);
    addCandidate(n, step(0xd));
    addCandidate(n, step(0xe));
    const int32_t pl = n.pwork->level, el = n.ework->level;
    int32_t chance = 0;
    if ((pl - 5 < el || (chance = 20, el <= pl - 9)) && (pl - 10 < el || (chance = 40, el <= pl - 14)) &&
        (pl - 15 < el || (chance = 60, el <= pl - 19)) && (pl - 20 < el || (chance = 80, el <= pl - 24)) &&
        (chance = 97, pl - 25 < el))
        chance = 0;
    n.nextTalkId = n.candidates[static_cast<int32_t>(sdf::GetRandInt(100)) < chance ? 1 : 0];
    return 0;
}

// Flow6_13 @ 0x0026F980: one near death backs off 70 times in a hundred
// (6_14); else 6_16.
int32_t nearDeath(TalkState& n)
{
    addCandidate(n, step(0x10));
    addCandidate(n, step(0xe));
    n.nextTalkId = n.candidates[0];
    if (dat::isDying(*n.ework) && static_cast<int32_t>(sdf::GetRandInt(100)) < 0x46)
        n.nextTalkId = n.candidates[1];
    return 0;
}

// Flow6_14 @ 0x0026F9F8: it shakes its head (message 0x44 after 6_12, 0x45
// after 6_13) and leaves (6_15).
int32_t backsOff(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = refuseMotion(n, *n.eform);
        return 0;
    }
    if (n.talkPhase != 1)
        return 0;
    addCandidate(n, step(0xf));
    const uint32_t previous = previousTalkId(n);
    showFlowMessage(n, previous == step(0xc) ? 0x44 : previous == step(0xd) ? 0x45 : 0);
    return 0;
}

// Flow6_15 @ 0x0026FAB8: it leaves (help message 1; result 2).
int32_t leaves(TalkState& n)
{
    showTalkMessage(n, n.helpmsg, 1, false);
    return 2;
}

// Flow6_16 @ 0x0026FAE0: it asks the Macca (message 0x43), the window open.
int32_t asksMaccaGift(TalkState& n)
{
    addCandidate(n, kDemand);
    setMaccaVariable(flowWindow(n), n.requestdata);
    showFlowMessage(n, 0x43);
    showMacca(0);
    return 0;
}

// Flow6_17 @ 0x0026FB50: an item or Macca (either at random for other
// kinds): how much (an item from its level band, item 8 when none); then
// by its disposition 6_20, 6_18 (half) or 6_19 (double).
int32_t itemOrMacca(TalkState& n)
{
    if (static_cast<uint32_t>(n.requesttype) > 1) {
        n.requesttype = sdf::GetRandInt(2) == 0 ? kAskMacca : kAskItem;
        n.prevreqtype = n.requesttype;
    }
    if (n.requesttype == kAskMacca)
        n.requestdata = demonAsksMacca(n, *n.pwork, *n.ework);
    if (n.requesttype == kAskItem) {
        n.requestdata = demonAsksItem(n, *n.pwork, *n.ework);
        if (n.requestdata == 0)
            n.requestdata = 8;
    }
    addCandidate(n, step(0x14));
    addCandidate(n, step(0x12));
    addCandidate(n, step(0x13));
    switch (n.affinity) {
    case 0: n.nextTalkId = n.candidates[0]; break;
    case 1: n.nextTalkId = n.candidates[1]; break;
    case 2: n.nextTalkId = n.candidates[2]; break;
    default: break;
    }
    return 0;
}

// Flow6_18 @ 0x0026FC60: well disposed, half the Macca.
int32_t halfMacca(TalkState& n)
{
    if (n.requesttype == kAskMacca)
        n.requestdata /= 2;
    addCandidate(n, step(0x14));
    return 0;
}

// Flow6_19 @ 0x0026FCB0: badly disposed, double.
int32_t doubleMacca(TalkState& n)
{
    if (n.requesttype == kAskMacca)
        n.requestdata <<= 1;
    addCandidate(n, step(0x14));
    return 0;
}

// Flow6_20 @ 0x0026FCF8: it asks (Macca 0x3F, the window open; an item
// 0x40). Macca is halved before event 8, and from event 0x1A until 0x16 is
// 80%, rounded to tens.
int32_t asksIt(TalkState& n)
{
    addCandidate(n, kDemand);
    if (n.requesttype == kAskMacca) {
        if (!evt::BitCheck(8))
            n.requestdata = roundMacca(n.requestdata / 2);
        if (evt::BitCheck(0x1a) && !evt::BitCheck(0x16))
            n.requestdata = roundMacca(n.requestdata * 8 / 10);
        setMaccaVariable(flowWindow(n), n.requestdata);
        showFlowMessage(n, 0x3f);
        showMacca(0);
        return 0;
    }
    setItemVariable(flowWindow(n), n.requestdata);
    showFlowMessage(n, 0x40);
    return 0;
}

// Flow6_21 @ 0x0026FE98: a question (message 0x3E, or 0x38 after a deal),
// group 7 going on to 6_24 pleased or 6_65 not.
int32_t asksQuestion(TalkState& n)
{
    if (n.requesttype != kAskQuestion) {
        n.prevreqtype = kAskQuestion;
        n.requesttype = kAskQuestion;
    }
    addCandidate(n, 0x70001);
    n.workid[4] = step(0x18);
    n.workid[5] = step(0x41);
    showFlowMessage(n, n.cnt6_37 == 0 ? 0x3e : 0x38);
    return 0;
}

// Flow6_22 @ 0x00270110: given: the item or Macca changes hands (6_24), if
// the player has it; else 6_23.
int32_t gives(TalkState& n)
{
    switch (n.requesttype) {
    case kAskItem: case kAskMacca:
        addCandidate(n, step(0x18));
        addCandidate(n, step(0x17));
        break;
    case kAskMaccaGift:
        addCandidate(n, 0x80001);
        addCandidate(n, step(0x17));
        break;
    default:
        break;
    }
    switch (n.requesttype) {
    case kAskItem:
        if (dat::hasItem(n.requestdata, 1)) {
            n.nextTalkId = n.candidates[0];
            dat::addItem(n.requestdata, -1);
        } else {
            n.nextTalkId = n.candidates[1];
        }
        break;
    case kAskMacca: case kAskMaccaGift:
        if (dat::hasMacca(n.requestdata)) {
            n.nextTalkId = n.candidates[0];
            dat::addMacca(-n.requestdata);
        } else {
            n.nextTalkId = n.candidates[1];
        }
        break;
    default:
        break;
    }
    return 0;
}

// Flow6_23 @ 0x00270230: the player hasn't got it: it shakes its head
// (Macca 0x50, an item 0x51); on to 6_65.
int32_t notOnHand(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = refuseMotion(n, *n.eform);
        return 0;
    }
    if (n.talkPhase != 1)
        return 0;
    addCandidate(n, step(0x41));
    n.workid[2] = step(0x45);
    int32_t message = 0;
    switch (n.requesttype) {
    case kAskItem: message = 0x51; break;
    case kAskMacca: case kAskMaccaGift: message = 0x50; break;
    default: break;
    }
    showFlowMessage(n, message);
    return 0;
}

// Flow6_24 @ 0x00270300: the round's outcome, by the talk skill's weights:
// a deal (9_1), talk on (6_25), a question (6_37) or refusal (6_43);
// shifted by the disposition and stat 1, fixed for talk type 3, and by the
// round (cnt6_36): after a deal (cnt6_37 1) a deal again; early rounds
// lean to talk, a question after event 8; later rounds to a deal. A third
// refusal from the fourth round may end in 6_74 instead (message 99).
int32_t outcome(TalkState& n)
{
    addCandidate(n, kDeal);
    addCandidate(n, step(0x19));
    addCandidate(n, step(0x25));
    addCandidate(n, step(0x2b));
    addCandidate(n, 0xa000d);
    addCandidate(n, kHelperLeaves);
    ++n.cnt6_36;
    int32_t w[4];
    const uint8_t* weights = talkSkillOf(static_cast<int32_t>(n.talkSkill)).weights;
    for (int32_t i = 0; i < 4; ++i)
        w[i] = weights[i];
    const bool tyrant = dat::race(*n.ework) == Race::Tyrant;
    if (n.affinity == 1) {
        const int32_t shift = tyrant ? 5 : 10;
        w[3] -= shift;
        w[2] -= shift;
        w[0] += shift * 2;
    } else if (n.affinity == 2) {
        w[3] += 10;
        w[2] += 10;
        w[0] -= 20;
    }
    if (!tyrant) {
        const int32_t p = dat::param(*n.pwork, Param::Unused1), e = dat::param(*n.ework, Param::Unused1);
        if (e + 5 < p) {
            w[3] -= 5;
            w[2] -= 5;
            w[0] += 10;
        } else if (p < e - 5) {
            w[3] += 5;
            w[2] += 5;
            w[0] -= 10;
        }
    }
    if (n.talkType == 3) {
        w[0] = 0x46;
        w[1] = 0x14;
        w[2] = 5;
        w[3] = 5;
    }
    if (n.cnt6_37 == 1) {
        n.nextTalkId = n.candidates[0];
        return 0;
    }
    if (n.requesttype == kAskQuestion) {
        w[2] += w[3];
        w[3] = 0;
    }
    const int32_t round = n.cnt6_36;
    if (round < 2) {
        if (evt::BitCheck(8)) {
            n.nextTalkId = n.candidates[2];
            return 0;
        }
        if (n.talkRequestType == 0) {
            n.nextTalkId = n.candidates[2];
            return 0;
        }
    }
    const int32_t pl = n.pwork->level, el = n.ework->level;
    if (round < 3 && evt::BitCheck(8) && !(el < pl - 10)) {
        w[2] += w[0];
        w[0] = 0;
    }
    if (round >= 4) {
        n.nextTalkId = n.candidates[0];
        return 0;
    }
    if (n.talkRequestType != 0 && round > 1) {
        n.nextTalkId = n.candidates[0];
        return 0;
    }
    if (youngDemon(n.ework->id) && !evt::BitCheck(8) && n.talkRequestType == 0 && n.cnt6_36 >= 2) {
        w[0] += w[3] + w[2];
        w[3] = 0;
        w[2] = 0;
    }
    if (el <= pl - 0x11 && sdf::GetRandInt(100) < 4) {
        w[2] += w[3];
        w[3] = 0;
    }
    const int32_t roll = static_cast<int32_t>(sdf::GetRandInt(100));
    int32_t pick = 0;
    if (w[0] < roll) {
        int32_t sum = 0;
        for (;;) {
            sum += w[pick];
            ++pick;
            if (pick > 3 || roll <= sum + w[pick])
                break;
        }
    }
    if (pick == 4)
        pick = 2;
    n.nextTalkId = n.candidates[pick];
    if (pick != 3 || n.cnt6_36 < 2 || n.talkRequestType != 0)
        return 0;
    if (sdf::GetRandInt(10) > 5)
        return 0;
    showFlowMessage(n, 99);
    n.nextTalkId = n.candidates[4];
    return 0;
}

// Flow6_25 @ 0x00270800: talk on (0x25..0x28).
int32_t talksOn(TalkState& n)
{
    addCandidate(n, step(0x1a));
    showFlowMessage(n, freshMessage(0x25, n.mes6_25));
    return 0;
}

// Flow6_26 @ 0x00270878: with helpers' skills left, 6_27; else 6_28.
int32_t anyHelper(TalkState& n)
{
    addCandidate(n, step(0x1b));
    addCandidate(n, step(0x1c));
    n.nextTalkId = n.candidates[countBuffSkills(n) < 1 ? 1 : 0];
    return 0;
}

// Flow6_27 @ 0x002708D0: a helper's skill for this moment (3), its
// outcomes 6_29 or 6_33; none, 6_28.
int32_t helperForTalk(TalkState& n)
{
    addCandidate(n, kHelperStepsIn);
    addCandidate(n, step(0x1c));
    n.workid[0] = step(0x1d);
    n.workid[1] = step(0x21);
    n.nextTalkId = n.candidates[takeHelper(n, 3) ? 0 : 1];
    return 0;
}

// Flow6_28 @ 0x00270960: a deal (9_1) two times in ten, else 6_36; early
// rounds after event 8 with a demon not far below, 6_36; the fourth round
// after event 8 with one far below, the deal.
int32_t dealOrOn(TalkState& n)
{
    addCandidate(n, kDeal);
    addCandidate(n, step(0x24));
    const int32_t round = n.cnt6_36;
    if (round < 2 && evt::BitCheck(8)) {
        n.nextTalkId = n.candidates[1];
        return 0;
    }
    const int32_t pl = n.pwork->level, el = n.ework->level;
    if (round == 3 && evt::BitCheck(8) && el <= pl - 0x11) {
        n.nextTalkId = n.candidates[0];
        return 0;
    }
    if (round < 3 && evt::BitCheck(8) && pl - 10 <= el) {
        n.nextTalkId = n.candidates[1];
        return 0;
    }
    n.nextTalkId = n.candidates[sdf::GetRandInt(10) < 2 ? 0 : 1];
    return 0;
}

// Flow6_29 @ 0x00270A80: the helper's affinity: well matched, 6_30; else
// 6_32.
int32_t helperMatched(TalkState& n)
{
    addCandidate(n, step(0x1e));
    addCandidate(n, step(0x20));
    n.nextTalkId = n.candidates[n.buffAffinity == 1 ? 0 : 1];
    return 0;
}

// Flow6_30 @ 0x00270AE0 (the helper's affinity message)
int32_t helperWords(TalkState& n)
{
    addCandidate(n, step(0x1f));
    showTalkMessage(n, n.aisyomsg[n.ekucyo], n.buffAffinityMessage, false);
    return 0;
}

// Flow6_31 @ 0x00270B30: a deal nine times in ten; else 6_35.
int32_t helpedDeal(TalkState& n)
{
    addCandidate(n, kDeal);
    addCandidate(n, step(0x23));
    n.nextTalkId = n.candidates[sdf::GetRandInt(10) == 0 ? 1 : 0];
    return 0;
}

// Flow6_32 @ 0x00270B90: the helper's skill works eight times in ten (a
// deal, with the skill's words for 0x19D..0x19F, 0x1A2..0x1A4); else 6_34.
int32_t helperSkill(TalkState& n)
{
    addCandidate(n, kDeal);
    addCandidate(n, step(0x22));
    if (sdf::GetRandInt(10) < 2) {
        n.nextTalkId = n.candidates[1];
        return 0;
    }
    int32_t message = 0;
    switch (n.buffSkill) {
    case 0x1a2: message = 0x6e; break;
    case 0x1a4: message = 0x6f; break;
    case 0x19d: message = 0x70; break;
    case 0x19e: message = 0x71; break;
    case 0x19f: message = 0x72; break;
    case 0x1a3: message = 0x73; break;
    default: break;
    }
    if (message != 0)
        showFlowMessage(n, message);
    n.nextTalkId = n.candidates[0];
    return 0;
}

// Flow6_33 @ 0x00270CA8: the helper failed; 0x19D on the early demons
// angers them (message 0x8E, 6_38); else 6_34.
int32_t helperFailed(TalkState& n)
{
    addCandidate(n, kDeal);
    addCandidate(n, step(0x22));
    addCandidate(n, step(0x26));
    if (n.buffSkill == 0x19d && unmovedBy19d(n.ework->id)) {
        showFlowMessage(n, 0x8e);
        n.nextTalkId = n.candidates[2];
    } else {
        sdf::GetRandInt(10);
        n.nextTalkId = n.candidates[1];
    }
    return 0;
}

// Flow6_34 @ 0x00270D88 (message 0x47), then 6_38.
int32_t unmoved(TalkState& n)
{
    addCandidate(n, step(0x26));
    showFlowMessage(n, 0x47);
    return 0;
}

// Flow6_35 @ 0x00270DD8 (message 0x114): the helper leaves, then 6_39.
int32_t almostDeal(TalkState& n)
{
    addCandidate(n, kHelperLeaves);
    n.workid[6] = step(0x27);
    showFlowMessage(n, 0x114);
    return 0;
}

// Flow6_36 @ 0x00270E38: a deal (9_1), or more talk (6_38) for an early
// demon before event 8 asked to join, the first three rounds.
int32_t dealOrMore(TalkState& n)
{
    addCandidate(n, step(0x26));
    addCandidate(n, kDeal);
    n.nextTalkId = n.candidates[0];
    if (youngDemon(n.ework->id) && !evt::BitCheck(8) && n.talkRequestType == 0 && n.cnt6_36 >= 3)
        n.nextTalkId = n.candidates[1];
    return 0;
}

// Flow6_37 @ 0x00270EE0: more talk (6_38), or a deal for an early demon
// before event 8 asked to join after the second round, or in the third
// round after event 8 with one far below.
int32_t moreOrDeal(TalkState& n)
{
    addCandidate(n, step(0x26));
    addCandidate(n, kDeal);
    if (youngDemon(n.ework->id) && !evt::BitCheck(8) && n.talkRequestType == 0 && n.cnt6_36 > 2) {
        n.nextTalkId = n.candidates[1];
        return 0;
    }
    n.nextTalkId = n.candidates[0];
    if (n.cnt6_36 == 3 && evt::BitCheck(8) && n.ework->level <= n.pwork->level - 0x11)
        n.nextTalkId = n.candidates[1];
    return 0;
}

// Flow6_38 @ 0x00270FF0: by the round (0x5D..0x60): the helper leaves,
// then 6_39.
int32_t roundWords(TalkState& n)
{
    addCandidate(n, kHelperLeaves);
    n.workid[6] = step(0x27);
    int32_t message;
    switch (n.cnt6_36) {
    case 1: message = 0x5d; break;
    case 2: message = 0x5e; break;
    case 3: message = 0x5f; break;
    default:
        if (n.cnt6_36 < 4)
            return 0;
        message = 0x60;
        break;
    }
    showFlowMessage(n, message);
    return 0;
}

// Flow6_39 @ 0x002710B0: one more thing it asks for, from its record's
// extra weights: an item (its second level band, item 0x10 when none),
// Macca (the second amount), or to drain (either of the others the first
// time). A Kodama before event 8 asked to join wants to drain.
int32_t asksMore(TalkState& n)
{
    addCandidate(n, step(0x28));
    if (n.ework->id == devil::Kodama && !evt::BitCheck(8) && n.talkRequestType == 0) {
        if (sdf::GetRandInt(1) == 0)   // (always)
            n.requesttype = kAskDrain;
    } else {
        switch (pickExtraRequestType(dat::devilTalkFormat(n.ework->id).tuikareqtype)) {
        case 0: n.requesttype = kAskMacca; break;
        case 1: n.requesttype = kAskItem; break;
        case 2: n.requesttype = kAskDrain; break;
        default: break;
        }
    }
    n.requestdata = 0;
    if (n.talkRequestType == 4)
        n.requesttype = kAskItem;
    if (n.prevreqtype != kAskDrain && n.requesttype == kAskDrain)
        n.requesttype = sdf::GetRandInt(2) == 0 ? kAskMacca : kAskItem;
    if (n.requesttype == kAskMacca) {
        n.requestdata = demonAsksMaccaB(n, *n.pwork, *n.ework);
    } else if (n.requesttype == kAskItem) {
        n.requestdata = demonAsksItemB(n, *n.pwork, *n.ework);
        if (n.requestdata == 0)
            n.requestdata = 0x10;
    }
    n.prevreqtype = n.requesttype;
    return 0;
}

// Flow6_40 @ 0x00271258: it asks (Macca 0x4A, the window open; an item
// 0x4B; to drain 0x4C).
int32_t asksMoreWords(TalkState& n)
{
    addCandidate(n, step(0x29));
    int32_t message = 0;
    switch (n.requesttype) {
    case kAskMacca:
        message = 0x4a;
        setMaccaVariable(flowWindow(n), n.requestdata);
        showMacca(0);
        break;
    case kAskItem:
        message = 0x4b;
        setItemVariable(flowWindow(n), n.requestdata);
        break;
    case kAskDrain:
        message = 0x4c;
        break;
    default:
        break;
    }
    showFlowMessage(n, message);
    return 0;
}

// Flow6_41 @ 0x00271338
int32_t asksMoreGoesOn(TalkState& n)
{
    addCandidate(n, step(0x2a));
    return 0;
}

// Flow6_42 @ 0x00271360: give it? (selection 0x48): given (6_22, or for a
// drain group 11), else 6_65; the window closed.
int32_t giveMore(TalkState& n)
{
    if (n.talkPhase == 0) {
        showFlowMessage(n, 0x48, true);
    } else if (n.talkPhase == 1) {
        addCandidate(n, n.requesttype == kAskDrain ? 0xb0001 : step(0x16));
        addCandidate(n, step(0x41));
        n.workid[2] = step(0x27);
        n.nextTalkId = n.candidates[n.nowselect == 0 ? 0 : 1];
        hideMacca();
    }
    return 0;
}

// Flow6_43 @ 0x00271440: a refusal (0x4E), then 6_44 (0x62), or with it
// the last enemy from the fourth round, six times in ten a deal after all
// (0x61).
int32_t refuses(TalkState& n)
{
    if (n.talkPhase == 0) {
        showFlowMessage(n, 0x4e);
        return 0;
    }
    if (n.talkPhase != 1)
        return 0;
    addCandidate(n, step(0x2c));
    addCandidate(n, kDeal);
    if (n.data->enemypcnt == 1 && n.cnt6_36 >= 4 && sdf::GetRandInt(10) < 6) {
        showFlowMessage(n, 0x61);
        n.nextTalkId = n.candidates[1];
        return 0;
    }
    showFlowMessage(n, 0x62);
    n.nextTalkId = n.candidates[0];
    return 0;
}

// Flow6_44 @ 0x00271550: with helpers' skills left, 6_45; else group 10.
int32_t refusalHelper(TalkState& n)
{
    addCandidate(n, 0xa0017);
    addCandidate(n, step(0x2d));
    n.nextTalkId = n.candidates[countBuffSkills(n) < 1 ? 0 : 1];
    return 0;
}

// Flow6_45 @ 0x002715A8: a helper's skill for this moment (2), its
// outcomes 6_46 or 6_47; none, group 10.
int32_t refusalHelperSkill(TalkState& n)
{
    addCandidate(n, 0xa0017);
    addCandidate(n, kHelperStepsIn);
    n.workid[0] = step(0x2e);
    n.workid[1] = step(0x2f);
    n.nextTalkId = n.candidates[takeHelper(n, 2) ? 1 : 0];
    return 0;
}

// Flow6_46 @ 0x00271638: won back (0x4F): the helper leaves and the talk
// starts over (6_9).
int32_t wonBack(TalkState& n)
{
    addCandidate(n, kHelperLeaves);
    n.workid[6] = step(9);
    showFlowMessage(n, 0x4f);
    n.cnt6_36 = 0;
    n.cnt6_37 = 0;
    return 0;
}

// Flow6_47 @ 0x002716A0: it leaves (the second help table's 9; a second's
// wait).
int32_t helperLost(TalkState& n)
{
    addCandidate(n, 0xa001d);
    showTalkMessage(n, n.helpmsg2, 9, false);
    n.waitframe = 60;
    return 0;
}

// Flow6_48 @ 0x002716F0: refused: haggle (6_49) up to three times; then
// group 10.
int32_t haggleOrNot(TalkState& n)
{
    addCandidate(n, step(0x31));
    addCandidate(n, kNoDeal);
    n.nextTalkId = n.candidates[n.cnt6_58 < 3 ? 0 : 1];
    return 0;
}

// Flow6_49 @ 0x00271750: Macca can be haggled (6_50); else 6_65.
int32_t haggleMacca(TalkState& n)
{
    addCandidate(n, step(0x32));
    addCandidate(n, step(0x41));
    n.workid[2] = step(0x45);
    n.nextTalkId = n.candidates[n.requesttype == kAskMacca ? 0 : 1];
    return 0;
}

// Flow6_50 @ 0x002717B8: with helpers' skills left, 6_51; else 6_65.
int32_t haggleHelper(TalkState& n)
{
    addCandidate(n, step(0x33));
    addCandidate(n, step(0x41));
    n.workid[2] = step(0x45);
    n.nextTalkId = n.candidates[countBuffSkills(n) < 1 ? 1 : 0];
    return 0;
}

// Flow6_51 @ 0x00271820: a helper's skill for this moment (0), its
// outcomes 6_58 or 6_63; none, 6_65.
int32_t haggleHelperSkill(TalkState& n)
{
    addCandidate(n, kHelperStepsIn);
    addCandidate(n, step(0x41));
    n.workid[0] = step(0x3a);
    n.workid[1] = step(0x3f);
    n.workid[2] = step(0x45);
    n.nextTalkId = n.candidates[takeHelper(n, 0) ? 0 : 1];
    return 0;
}

// Flow6_52 @ 0x002718B8: a helper steps in (the window closed).
int32_t helperSteps(TalkState& n)
{
    addCandidate(n, step(0x35));
    closeTalkWindow(n);
    n.buffSucceeded = 0;
    n.buffAffinity = 0;
    return 0;
}

// Flow6_53 @ 0x002718F8: the helper takes the talker's place: its skill
// named (help messages 0xC..0x15), the talker steps back and away, the
// helper forward (stat 8 while it stands in), the skill's name shown.
int32_t helperTakesPlace(TalkState& n)
{
    Formation& from = helperForm(n);
    int32_t message = 0;
    switch (n.buffSkill) {
    case 0x199: message = 0xc; break;
    case 0x19a: message = 0xd; break;
    case 0x19b: message = 0xf; break;
    case 0x19c: message = 0x10; break;
    case 0x19d: message = 0x12; break;
    case 0x19e: message = 0x13; break;
    case 0x19f: message = 0x14; break;
    case 0x1a2: message = 0xe; break;
    case 0x1a3: message = 0x15; break;
    case 0x1a4: message = 0x11; break;
    default: break;
    }
    switch (n.talkPhase) {
    case 0:
        cameraOnHelper(from, *n.pform, *n.eform);
        showTalkMessage(n, n.helpmsg, message, false);
        break;
    case 1:
        closeTalkWindow(n);
        cameraOnPair(*n.pform, *n.eform);
        movePackets(kMovePacketsAway, n, *n.pform, *n.eform);
        hideFormation(from);
        movePackets(kMovePacketsOut, n, from, *n.eform);
        n.waitframe = 10;
        break;
    case 2:
        hideFormation(*n.pform);
        makeFadeInPackets(1, static_cast<int32_t>(n.actdata.address), n.pform.get(), 0, 0, 0, 0);
        movePackets(kMovePacketsIn, n, from, *n.eform);
        n.stat |= 8;
        showFormation(from);
        cameraOnPair(from, *n.eform);
        n.waitframe = 5;
        break;
    case 3:
        showSkillName(n.buffSkill);
        diag::print(diag::Message::TalkHelper, n.buffPartyIndex, n.buffSkill);
        n.waitframe = 60;
        break;
    case 4:
        addCandidate(n, step(0x36));
        break;
    default:
        break;
    }
    return 0;
}

// Flow6_54 @ 0x00271C98: words of its own for Kikuri-Hime's 0x1A2 and
// Dionysus's 0x1A3 (6_55); else 6_56.
int32_t helperOwnWords(TalkState& n)
{
    addCandidate(n, step(0x38));
    addCandidate(n, step(0x37));
    n.nextTalkId = n.candidates[0];
    const UnitWork& helper = helperUnit(n);
    if (n.buffSkill == 0x1a2 && helper.id == devil::KikuriHime) {
        n.temp_param[0] = 2;
        n.nextTalkId = n.candidates[1];
        n.temp_param[1] = 0x58;
    }
    if (n.buffSkill == 0x1a3 && helper.id == devil::Dionysus) {
        n.temp_param[0] = 6;
        n.nextTalkId = n.candidates[1];
        n.temp_param[1] = 0x59;
    }
    return 0;
}

// Flow6_55 @ 0x00271D60: those words (in speech style temp_param[0]'s
// table).
int32_t helperSpeaks(TalkState& n)
{
    addCandidate(n, step(0x38));
    showTalkMessage(n, n.flowmsg[n.temp_param[0]], n.temp_param[1], false);
    return 0;
}

// Flow6_56 @ 0x00271DB0: the helper's affinity with the demon, by its
// skill's good rules (skills 0x19C..0x1A1, 0x1A3 and 0x1A4; others none).
int32_t helperAffinity(TalkState& n)
{
    addCandidate(n, step(0x39));
    const int32_t skill = n.buffSkill;
    if (skill < 0x19c || skill == 0x1a2 || skill > 0x1a4) {
        n.buffAffinity = 0;
        return 0;
    }
    const UnitWork& helper = helperUnit(n);
    for (const TalkSkillRule& rule : talkSkillOf(skill).good)
        if ((rule.mine != 0 || rule.theirs != 0) && pairAffinity(helper, *n.ework, rule.mine, rule.theirs, 1)) {
            n.buffAffinity = 1;
            n.buffAffinityMessage = rule.message;
            break;
        }
    return 0;
}

// Flow6_57 @ 0x00271F00: does the helper's skill work? Seven times in ten
// (0x1A2 85), ten more or less by stat 1, never 0x19D on the early demons:
// workid[0], else workid[1].
int32_t helperWorks(TalkState& n)
{
    addCandidate(n, n.workid[0]);
    addCandidate(n, n.workid[1]);
    int32_t chance = n.buffSkill == 0x1a2 ? 0x55 : 0x46;
    const int32_t e = dat::param(*n.ework, Param::Unused1), p = dat::param(*n.pwork, Param::Unused1);
    if (e + 5 < p)
        chance += 10;
    else if (p < e - 5)
        chance -= 10;
    if (n.buffSkill == 0x19d && unmovedBy19d(n.ework->id))
        chance = 0;
    if (static_cast<int32_t>(sdf::GetRandInt(100)) < chance) {
        n.buffSucceeded = 1;
        n.nextTalkId = n.candidates[0];
    } else {
        n.buffSucceeded = 0;
        n.nextTalkId = n.candidates[1];
    }
    return 0;
}

// Flow6_58 @ 0x00272028: haggled down: half the Macca (the haggles
// counted).
int32_t haggledDown(TalkState& n)
{
    ++n.cnt6_58;
    n.requestdata /= 2;
    addCandidate(n, step(0x3b));
    return 0;
}

// Flow6_59 @ 0x00272070: by the haggle: 6_71, 6_72, 6_73.
int32_t haggleWords(TalkState& n)
{
    addCandidate(n, step(0x47));
    addCandidate(n, step(0x48));
    addCandidate(n, step(0x49));
    if (n.cnt6_58 > 0 && n.cnt6_58 < 4)
        n.nextTalkId = n.candidates[n.cnt6_58 - 1];
    return 0;
}

// Asks the haggled Macca (message), the window open, then the demand.
void asksHaggled(TalkState& n, int32_t message)
{
    addCandidate(n, kDemand);
    setMaccaVariable(flowWindow(n), n.requestdata);
    showFlowMessage(n, message);
    showMacca(0);
}

// Flow6_60 @ 0x00272148
int32_t haggledOnce(TalkState& n)
{
    asksHaggled(n, 0x55);
    return 0;
}

// Flow6_61 @ 0x00272218
int32_t haggledTwice(TalkState& n)
{
    asksHaggled(n, 0x56);
    return 0;
}

// Flow6_62 @ 0x002722E8
int32_t haggledThrice(TalkState& n)
{
    asksHaggled(n, 0x57);
    return 0;
}

// Flow6_63 @ 0x00272358: the haggle failed: it shakes its head (0x53); the
// helper leaves, then 6_64.
int32_t haggleFailed(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = refuseMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        addCandidate(n, kHelperLeaves);
        n.workid[6] = step(0x40);
        showFlowMessage(n, 0x53);
    }
    return 0;
}

// Flow6_64 @ 0x002723E0
int32_t asksAgain(TalkState& n)
{
    asksHaggled(n, 0x54);
    return 0;
}

// Flow6_65 @ 0x00272450: not given: no deal, try again (6_66), or after a
// deal a deal again. Half the time (Tyrants 40, others 30 well disposed;
// 70 badly; stat 1 by five) no deal; from the fourth round, three times in
// ten try again, else a deal after all (0x129).
int32_t notGiven(TalkState& n)
{
    addCandidate(n, kNoDeal);
    addCandidate(n, step(0x42));
    addCandidate(n, kDeal);
    int32_t chance = 0x32;
    const bool tyrant = dat::race(*n.ework) == Race::Tyrant;
    if (n.affinity == 1)
        chance = tyrant ? 0x28 : 0x1e;
    else if (n.affinity == 2)
        chance = 0x46;
    if (!tyrant) {
        const int32_t p = dat::param(*n.pwork, Param::Unused1), e = dat::param(*n.ework, Param::Unused1);
        if (e + 5 < p)
            chance -= 5;
        else if (p < e - 5)
            chance += 5;
    }
    if (n.cnt6_37 != 0) {
        n.nextTalkId = n.candidates[0];
        return 0;
    }
    if (n.cnt6_36 < 4) {
        n.nextTalkId = n.candidates[static_cast<int32_t>(sdf::GetRandInt(100)) < chance ? 0 : 1];
    } else if (sdf::GetRandInt(10) < 3) {
        n.nextTalkId = n.candidates[1];
    } else {
        showFlowMessage(n, 0x129);
        n.nextTalkId = n.candidates[2];
    }
    return 0;
}

// Flow6_66 @ 0x002725E0: try again (6_67) up to three times; then no deal.
int32_t tryAgain(TalkState& n)
{
    ++n.cnt6_66;
    addCandidate(n, step(0x43));
    addCandidate(n, kNoDeal);
    n.nextTalkId = n.candidates[n.cnt6_66 < 4 ? 0 : 1];
    return 0;
}

// Flow6_67 @ 0x00272648: a word (0x21..0x24), then workid[2].
int32_t triesAgain(TalkState& n)
{
    addCandidate(n, n.workid[2]);
    showFlowMessage(n, freshMessage(0x21, n.mes6_67));
    return 0;
}

// Flow6_69 @ 0x002726C0: back to the request.
int32_t backToRequest(TalkState& n)
{
    addCandidate(n, step(9));
    return 0;
}

// Flow6_70 @ 0x0026FF40: give it? The demand (a selection: an item 0x3A,
// Macca 0x39 or after a haggle 0x52, to drain 0x3B, a fight 0x3C, Macca
// as a gift 0x3D); refused, 6_48; given, the giving (6_22), or a drain
// (group 11), or a fight (group 8). The window closes.
int32_t demand(TalkState& n)
{
    if (n.talkPhase == 0) {
        int32_t message;
        switch (n.requesttype) {
        case kAskItem: message = 0x3a; break;
        case kAskMacca: {
            const uint32_t previous = previousTalkId(n);
            message = (previous >= step(0x3c) && previous < step(0x3f)) || previous == step(0x40) ? 0x52 : 0x39;
            break;
        }
        case kAskDrain: message = 0x3b; break;
        case kAskFight: message = 0x3c; break;
        case kAskMaccaGift: message = 0x3d; break;
        default: return 0;
        }
        showFlowMessage(n, message, true);
        return 0;
    }
    if (n.talkPhase != 1)
        return 0;
    diag::print(diag::Message::TalkSelect, n.nowselect);
    addCandidate(n, step(0x30));
    switch (n.requesttype) {
    case kAskItem: case kAskMacca: case kAskMaccaGift: addCandidate(n, step(0x16)); break;
    case kAskDrain: addCandidate(n, 0xb0001); break;
    case kAskFight: addCandidate(n, 0x80001); break;
    default: break;
    }
    n.nextTalkId = n.candidates[n.nowselect == 0 ? 1 : 0];
    hideMacca();
    return 0;
}

// The helper leaves (6_74), then the step noted.
void afterHelper(TalkState& n, uint32_t next, int32_t message)
{
    addCandidate(n, kHelperLeaves);
    n.workid[6] = next;
    showFlowMessage(n, message);
}

// Flow6_71 @ 0x002720E8 (0x5A), then 6_60.
int32_t haggleOnce(TalkState& n)
{
    afterHelper(n, step(0x3c), 0x5a);
    return 0;
}

// Flow6_72 @ 0x002721B8 (0x5B), then 6_61.
int32_t haggleTwice(TalkState& n)
{
    afterHelper(n, step(0x3d), 0x5b);
    return 0;
}

// Flow6_73 @ 0x00272288 (0x5C), then 6_62.
int32_t haggleThrice(TalkState& n)
{
    afterHelper(n, step(0x3e), 0x5c);
    return 0;
}

// Flow6_74 @ 0x00271B20: a helper standing in steps back, the talker
// forward again; then workid[6].
int32_t helperLeaves(TalkState& n)
{
    if (!(n.stat & 8)) {
        addCandidate(n, n.workid[6]);
        return 0;
    }
    Formation& form = helperForm(n);
    switch (n.talkPhase) {
    case 0:
        movePackets(kMovePacketsAway, n, form, *n.eform);
        hideFormation(*n.pform);
        movePackets(kMovePacketsOut, n, *n.pform, *n.eform);
        cameraOnPair(*n.pform, *n.eform);
        n.waitframe = 10;
        break;
    case 1:
        hideFormation(form);
        makeFadeInPackets(1, static_cast<int32_t>(n.actdata.address), &form, 0, 0, 0, 0);
        addMoveHomePacket(0, 0, n.buffPartyIndex, ee::Float::fromBits(0x3f800000));
        showFormation(*n.pform);
        movePackets(kMovePacketsIn, n, *n.pform, *n.eform);
        n.waitframe = 10;
        break;
    case 2:
        addCandidate(n, n.workid[6]);
        n.stat &= ~8u;
        break;
    default:
        break;
    }
    return 0;
}

// Flow6_80 @ 0x0026F2A0: Charisma: four times in ten 6_81; else an opening
// word (0x1C..0x1F) and the request.
int32_t charisma(TalkState& n)
{
    addCandidate(n, step(0x51));
    addCandidate(n, step(9));
    if (sdf::GetRandInt(10) < 4) {
        n.nextTalkId = n.candidates[0];
        return 0;
    }
    showFlowMessage(n, freshMessage(0x1c, n.mes6_2));
    n.nextTalkId = n.candidates[1];
    return 0;
}

// Flow6_81 @ 0x0026F350: charmed (message 0x126), on to 6_4.
int32_t charmed(TalkState& n)
{
    addCandidate(n, step(4));
    showFlowMessage(n, 0x126);
    return 0;
}

constexpr TalkStep kNone = nullptr;

} // namespace

const TalkStep kBargainSteps[82] = {
    kNone,          disposition,     neutral,         wellDisposed,     dealAtOnce,       wellDisposedTalks,
    badlyDisposed,  noDealAtOnce,    badlyDisposedTalks, asksFor,       wantsFight,       wantsDrain,
    offersMacca,    nearDeath,       backsOff,        leaves,           asksMaccaGift,    itemOrMacca,
    halfMacca,      doubleMacca,     asksIt,          asksQuestion,     gives,            notOnHand,
    outcome,        talksOn,         anyHelper,       helperForTalk,    dealOrOn,         helperMatched,
    helperWords,    helpedDeal,      helperSkill,     helperFailed,     unmoved,          almostDeal,
    dealOrMore,     moreOrDeal,      roundWords,      asksMore,         asksMoreWords,    asksMoreGoesOn,
    giveMore,       refuses,         refusalHelper,   refusalHelperSkill, wonBack,        helperLost,
    haggleOrNot,    haggleMacca,     haggleHelper,    haggleHelperSkill, helperSteps,     helperTakesPlace,
    helperOwnWords, helperSpeaks,    helperAffinity,  helperWorks,      haggledDown,      haggleWords,
    haggledOnce,    haggledTwice,    haggledThrice,   haggleFailed,     asksAgain,        notGiven,
    tryAgain,       triesAgain,      kNone,           backToRequest,    demand,           haggleOnce,
    haggleTwice,    haggleThrice,    helperLeaves,    kNone,            kNone,            kNone,
    kNone,          kNone,           charisma,        charmed,
};

// nbNegoFlowTwo @ 0x002726E8
int32_t bargainFlow(TalkState& n) { return kBargainSteps[n.talkId & 0xffff](n); }

} // namespace nocturne::nb
