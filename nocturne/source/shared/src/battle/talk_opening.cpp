// The talks' group 1 (original unit: NbNegoFlowOne): the opening of an
// ordinary talk (step 0x10007). It decides who talks and how: a talker or
// demon that can't (an ailment), a boss, a demon whose Loan comes due, the
// full moon (group 2), one of its own kind (group 4), a fated pair (group
// 5), one already in the stock (group 3), another enemy breaking in, the
// race's own words; else the bargaining (group 6). Many steps go through
// 1_31, the introduction (the two face each other), with the step to go on
// to noted in workid[3]. Rewritten from the original instructions.
// Messages are in the demon's flow table, the bosses' or the help table.
#include "nocturne/address.hpp"
#include "nocturne/battle/talk_flow.hpp"

#include "nocturne/battle/camera.hpp"
#include "nocturne/battle/formation.hpp"
#include "nocturne/battle/kouka.hpp"
#include "nocturne/battle/sound.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"
#include "nocturne/build.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t step(uint32_t number) { return 0x10000u | number; }
constexpr uint32_t kIntroduction = step(0x1f);
constexpr uint32_t kTalkSkills = addr(0x003e1338);   // [skill - 0x180] the talk skills: kind first (0x68 bytes)
constexpr uint32_t kCantAct = 0x20;            // ActionProcessData::stat (tentative)
constexpr uint32_t kTalkBreakIns = 0x800000;   // MainProcessData::stat: other enemies may break in (tentative)

int32_t flowWindow(const TalkState& n) { return n.flowmsg[n.ekucyo]; }

void showFlowMessage(TalkState& n, int32_t message) { showTalkMessage(n, flowWindow(n), message, false); }

// The value 0xF0..0xF6 here marks a boss's talk (the field's HD name is
// press4_hansya); the first release has no such talks.
bool bossTalk(const TalkState& n)
{
    return !kBuild.vanilla && static_cast<uint16_t>(n.data->press4_repel - 0xf0) < 7;
}

// An enemy slot (4..13) present and able to act, not the demon talked to.
bool otherEnemy(const TalkState& n, int32_t slot)
{
    const uint16_t flag = static_cast<uint16_t>(n.data->party[slot].flag);
    return (flag & 1) && (flag & 2) && !(flag & 0x38) && slot != n.epartyindex;
}

UnitWork& unitOf(TalkState& n, int32_t slot) { return *GetUnitWorkPointer(*n.data, n.data->party[slot]); }

const DevilTalkFormat& talkFormatOf(const UnitWork& unit) { return dat::devilTalkFormat(unit.id); }

// Tyrants, Viles and Gurr.
bool tyrantLike(const UnitWork& w)
{
    const Race race = dat::race(w);
    return race == Race::Tyrant || race == Race::Vile || w.id == devil::Gurr;
}

// The pairs whose meeting has words of its own (the demon and one of its
// kind talking), with their flow message.
struct OwnPair { uint16_t devil; int32_t message; };
constexpr OwnPair kOwnPairs[] = {
    {devil::Amaterasu, 0x74}, {devil::Odin, 0x75}, {devil::Atavaka, 0x76}, {devil::Scathach, 0x77},
    {devil::Sati, 0x78},      {devil::BeijiWeng, 0x79}, {devil::Kali, 0x7a}, {devil::Mikazuchi, 0x7b},
    {devil::Chimera, 0x7c},   {devil::Baihu, 0x7d}, {devil::Barong, 0x7e}, {devil::Yatagarasu, 0x7f},
};

} // namespace

// Flow1_3 @ 0x0026CD80: a talker who can't talk, unable to act, goes to the
// introduction and 1_4; else 1_5.
int32_t talkerCanTalk(TalkState& n)
{
    addCandidate(n, step(5));
    addCandidate(n, kIntroduction);
    n.workid[3] = step(4);
    n.nextTalkId = n.candidates[!dat::canTalk(*n.pwork) && (n.actdata->stat & kCantAct) ? 1 : 0];
    return 0;
}

// Flow1_4 @ 0x0026CDF8: after a pause, the demon won't listen (message
// 0x111, or 0x98 under a full Kagutsuchi but for the moonproof); the talk
// fails.
int32_t wontListen(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = 30;
        return 0;
    }
    if (n.talkPhase != 1)
        return 0;
    showFlowMessage(n, !moonproof(n.ework->id) && evt::GetAgeOfMoon() == 8 ? 0x98 : 0x111);
    return 1;
}

// Flow1_5 @ 0x0026CF18: the demon-specific talk skills: Soul Recruit from a
// Valkyrie, Mischief from Loki, Death Pact from Mithra go on to 1_6 (their
// words, temp_param[0]); else 1_10.
int32_t specialSkill(TalkState& n)
{
    addCandidate(n, step(6));
    addCandidate(n, step(10));
    n.nextTalkId = n.candidates[1];
    int32_t words = 0;
    switch (n.talkSkill) {
    case skill::SoulRecruit: words = n.pwork->id == devil::Valkyrie ? 3 : 0; break;
    case skill::Mischief: words = n.pwork->id == devil::Loki ? 4 : 0; break;
    case skill::DeathPact: words = n.pwork->id == devil::Mithra ? 5 : 0; break;
    default: break;
    }
    if (words != 0) {
        n.temp_param[0] = words;
        n.nextTalkId = n.candidates[0];
    }
    return 0;
}

// Flow1_6 @ 0x0026CFF0: the skill's words come in the introduction.
int32_t skillWords(TalkState& n)
{
    addCandidate(n, step(10));
    n.flag1_6 = 1;
    return 0;
}

// Flow1_7 @ 0x0026D028: the first step: a demon that can't talk, 1_8; else
// 1_3.
int32_t demonCanTalk(TalkState& n)
{
    addCandidate(n, step(8));
    addCandidate(n, step(3));
    n.nextTalkId = n.candidates[dat::canTalk(*n.ework) ? 1 : 0];
    return 0;
}

// Flow1_8 @ 0x0026D080: the introduction, then 1_9.
int32_t demonCantTalk(TalkState& n)
{
    addCandidate(n, kIntroduction);
    n.workid[3] = step(9);
    return 0;
}

// Flow1_9 @ 0x0026D0C0: why it can't talk (by its ailment: messages
// 8..0xE); the talk fails.
int32_t demonsAilment(TalkState& n)
{
    int32_t message = 8;
    switch (n.ework->badstat & 0xfff) {
    case 1: message = 10; break;
    case 2: message = 0xe; break;
    case 4: message = 0xb; break;
    case 8: message = 0xd; break;
    case 0x10: message = 0xc; break;
    case 0x200: message = 9; break;
    default: break;
    }
    showFlowMessage(n, message);
    return 1;
}

// Flow1_10 @ 0x0026D190: the introduction; a boss (an ID from 0x100, a
// battle that refuses talks or a boss's talk) then refuses (1_11); others go
// on (1_26).
int32_t bossOrNot(TalkState& n)
{
    addCandidate(n, kIntroduction);
    addCandidate(n, step(0x1a));
    n.workid[3] = step(0xb);
    n.nextTalkId = n.candidates[n.ework->id < 0x100 ? 1 : 0];
    if (battleRefusesTalk(*n.data))
        n.nextTalkId = n.candidates[0];
    if (bossTalk(n))
        n.nextTalkId = n.candidates[0];
    return 0;
}

// Flow1_11 @ 0x0026D238: after a pause, a boss's words (the bosses' table:
// 0x80 for a boss's talk, else by its ID; an ordinary demon's 0x12A); the
// talk fails.
int32_t bossRefuses(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = 30;
        return 0;
    }
    if (n.talkPhase != 1)
        return 0;
    if (bossTalk(n))
        showTalkMessage(n, n.bossmsg, 0x80, false);
    else if (n.ework->id < 0x100)
        showFlowMessage(n, 0x12a);
    else
        showTalkMessage(n, n.bossmsg, n.ework->id - 0x100, false);
    return 1;
}

// Flow1_12 @ 0x0026D7F0: a Loan comes due: with three or more taken from
// its race and over 499 Macca on hand, 30 times in a hundred (50 from six,
// 70 from eleven) it collects (the introduction, then 1_15); else 1_39.
int32_t loanDue(TalkState& n)
{
    addCandidate(n, kIntroduction);
    addCandidate(n, step(0x27));
    n.nextTalkId = n.candidates[1];
    n.workid[3] = step(0xf);
    const uint8_t loans = dat::globalWork().loanCounts[static_cast<uint8_t>(dat::devilFormat(n.ework->id).race)];
    if (loans > 2 && dat::globalWork().macca > 499) {
        const int32_t chance = loans <= 5 ? 30 : loans <= 10 ? 50 : 70;
        if (static_cast<int32_t>(sdf::GetRandInt(100)) < chance)
            n.nextTalkId = n.candidates[0];
    }
    return 0;
}

// Flow1_13 @ 0x0026D8D8
int32_t loanDueGoesOn(TalkState& n)
{
    addCandidate(n, step(0xe));
    addCandidate(n, step(0xf));
    return 0;
}

// Flow1_14 @ 0x0026D918: message 6.
int32_t loanWords(TalkState& n)
{
    addCandidate(n, step(0xf));
    showFlowMessage(n, 6);
    return 0;
}

// Flow1_15 @ 0x0026D968: it shakes its head (message 7).
int32_t collects(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = refuseMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        addCandidate(n, step(0x10));
        showFlowMessage(n, 7);
    }
    return 0;
}

// Flow1_16 @ 0x0026D9E8: a third of the player's Macca, and the race's
// Loans forgiven.
int32_t collectsThird(TalkState& n)
{
    addCandidate(n, step(0x11));
    n.getmakka = dat::globalWork().macca / 3;
    dat::globalWork().loanCounts[static_cast<uint8_t>(dat::devilFormat(n.ework->id).race)] = 0;
    return 0;
}

// Flow1_17 @ 0x0026DA60: "lost Macca" (help message 4); the talk fails.
int32_t paysUp(TalkState& n)
{
    setMaccaVariable(n.helpmsg, n.getmakka);
    showTalkMessage(n, n.helpmsg, 4, false);
    dat::addMacca(-n.getmakka);
    return 1;
}

// Flow1_18 @ 0x0026DAB0: under a full Kagutsuchi (not for Corpus), the
// moonproof included, the introduction and group 2; else 0x10021 (1_33).
int32_t fullMoonOrNot(TalkState& n)
{
    addCandidate(n, step(0x21));
    addCandidate(n, kIntroduction);
    n.workid[3] = 0x20001;
    if (moonproof(n.ework->id))
        n.nextTalkId = n.candidates[1];
    else if (dat::race(*n.ework) == Race::Corpus)
        n.nextTalkId = n.candidates[0];
    else
        n.nextTalkId = n.candidates[evt::GetAgeOfMoon() == 8 ? 1 : 0];
    return 0;
}

// Flow1_19 @ 0x0026DBE0: a demon of the talker's kind (neither the
// Demi-fiend): the introduction and group 4; else 1_20.
int32_t kinOrNot(TalkState& n)
{
    addCandidate(n, step(0x14));
    addCandidate(n, kIntroduction);
    n.nextTalkId = n.candidates[0];
    n.workid[3] = 0x40001;
    if (!n.pwork->isPlayerCharacter() && !n.ework->isPlayerCharacter() && n.pwork->id == n.ework->id) {
        n.nextTalkId = n.candidates[1];
        n.flag1_6 = 0;
    }
    return 0;
}

// Flow1_20 @ 0x0026DC78: one like it already in the stock, asked to join:
// the introduction and group 3; else 1_21.
int32_t inStockOrNot(TalkState& n)
{
    addCandidate(n, step(0x15));
    addCandidate(n, kIntroduction);
    n.workid[3] = 0x30001;
    n.nextTalkId = n.candidates[0];
    if (!n.ework->isPlayerCharacter() && dat::findDevil(n.ework->id) >= 0 && n.talkRequestType == 0) {
        n.nextTalkId = n.candidates[1];
        n.flag1_6 = 0;
    }
    return 0;
}

// Flow1_21 @ 0x0026DD08: with other enemies (and break-ins allowed), 1_22;
// else 1_27.
int32_t othersOrNot(TalkState& n)
{
    addCandidate(n, step(0x16));
    addCandidate(n, step(0x1b));
    n.nextTalkId = n.candidates[n.data->enemypcnt == 1 ? 1 : 0];
    if (!(n.data->stat & kTalkBreakIns))
        n.nextTalkId = n.candidates[1];
    return 0;
}

// Flow1_22 @ 0x0026DD88: another enemy that would always break in (tokubou
// type 1; able to talk): one at random does (1_23); else 1_24.
int32_t alwaysBreaksIn(TalkState& n)
{
    addCandidate(n, step(0x18));
    addCandidate(n, step(0x17));
    n.nextTalkId = n.candidates[0];
    uint8_t slots[32];
    uint32_t count = 0;
    for (int32_t slot = 4; slot < 14; ++slot) {
        if (!otherEnemy(n, slot))
            continue;
        const UnitWork& unit = unitOf(n, slot);
        if (dat::canTalk(unit) && talkFormatOf(unit).tokuboutype == 1)
            slots[count++] = static_cast<uint8_t>(slot);
    }
    if (count > 0) {
        const uint8_t slot = slots[sdf::GetRandInt(count)];
        n.nextTalkId = n.candidates[1];
        n.boupartyindex = slot;
    }
    return 0;
}

// Flow1_23 @ 0x0026DED0: the demon shakes its head, the one breaking in
// speaks (message 0x10 in its own flow table); the demon attacks.
int32_t brokenIn(TalkState& n)
{
    UnitWork& other = unitOf(n, n.boupartyindex);
    if (n.talkPhase == 0) {
        n.waitframe = refuseMotion(n, *n.eform);
        return 0;
    }
    if (n.talkPhase != 1)
        return 0;
    if (talkFormatOf(other).tokuboutype == 1) {
        const int32_t window = n.flowmsg[talkFormatOf(other).speechStyle];
        setTalkVariables(window, *n.pwork, other);
        showTalkMessage(n, window, 0x10, false);
    }
    return 4;
}

// Flow1_24 @ 0x0026DFA8: another enemy may break in (not tokubou type 2;
// able to talk): each one in turn, 50 / (the other enemies) times in a
// hundred (1_25); else 1_27. (The share is worked out first: with no other
// enemy, the original traps on the division.)
int32_t mayBreakIn(TalkState& n)
{
    addCandidate(n, step(0x1b));
    addCandidate(n, step(0x19));
    n.nextTalkId = n.candidates[0];
    const int32_t others = n.data->enemypcnt - 1;
    if (others == 0)
        divideByZeroTrap();
    const int32_t chance = 50 / others;
    for (int32_t slot = 4; slot < 14; ++slot) {
        if (!otherEnemy(n, slot))
            continue;
        const UnitWork& unit = unitOf(n, slot);
        if (dat::canTalk(unit) && talkFormatOf(unit).tokuboutype != 2 && static_cast<int32_t>(sdf::GetRandInt(100)) < chance) {
            n.boupartyindex = slot;
            n.nextTalkId = n.candidates[1];
            return 0;
        }
    }
    return 0;
}

// Flow1_25 @ 0x0026E0F0: the one breaking in: a word over it, the camera on
// it, its voice loaded; then it shakes its head and speaks (message 0x11 in
// its own flow table); the demon attacks.
int32_t breaksIn(TalkState& n)
{
    UnitWork& other = unitOf(n, n.boupartyindex);
    Formation& form = guest::table<Formation>(n.data->form.address)[n.data->party[n.boupartyindex].formindex];
    if (n.talkPhase == 0) {
        addWordPacket(0, 0x1e, static_cast<int32_t>(n.actdata.address), &form, 0);
        cameraOnObstructor(form);
        loadTalkSound(form);
        return 0;
    }
    if (n.talkPhase != 1)
        return 0;
    refuseMotion(n, form);
    const int32_t window = n.flowmsg[talkFormatOf(other).speechStyle];
    setTalkVariables(window, *n.pwork, other);
    showTalkMessage(n, window, 0x11, false);
    return 4;
}

// Flow1_26 @ 0x0026E218: a fated pair (not under a full Kagutsuchi): the
// introduction and group 5; else 0x10012 (1_18).
int32_t fatedOrNot(TalkState& n)
{
    addCandidate(n, step(0x12));
    addCandidate(n, kIntroduction);
    n.workid[3] = 0x50001;
    if (evt::GetAgeOfMoon() == 8) {
        n.nextTalkId = n.candidates[0];
        return 0;
    }
    const int32_t pair = fatedPair(n);
    if (pair == -1) {
        n.nextTalkId = n.candidates[0];
    } else {
        n.nextTalkId = n.candidates[1];
        n.innen_id = pair;
        n.flag1_6 = 0;
    }
    return 0;
}

// Flow1_27 @ 0x0026E2B0: the introduction, then 0x1001E (1_30), or 1_28 for
// a demon of honbou type 1 (none is).
int32_t honbouOrNot(TalkState& n)
{
    addCandidate(n, kIntroduction);
    addCandidate(n, step(0x1c));
    n.workid[3] = step(0x1e);
    n.nextTalkId = n.candidates[talkFormatOf(*n.ework).honboutype == 1 ? 1 : 0];
    return 0;
}

// Flow1_28 @ 0x0026E338: half the time a demon not near death won't talk
// (1_29); else on (the introduction, or for talk type 3 straight to 1_30).
int32_t wontTalk(TalkState& n)
{
    addCandidate(n, step(0x1d));
    addCandidate(n, n.talkType == 3 ? step(0x1e) : kIntroduction);
    n.nextTalkId = n.candidates[1];
    n.workid[3] = step(0x1e);
    if (!dat::isDying(*n.ework) && static_cast<int32_t>(sdf::GetRandInt(100)) < 50)
        n.nextTalkId = n.candidates[0];
    return 0;
}

// Flow1_29 @ 0x0026E3E8: it shakes its head (message 0x12) and attacks.
int32_t refusesToTalk(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = refuseMotion(n, *n.eform);
    } else if (n.talkPhase == 1) {
        showFlowMessage(n, 0x12);
        return 4;
    }
    return 0;
}

// Flow1_30 @ 0x0026E468: after a pause, what it wants to hear about
// (message 0x13 + the request kind; 0xF to join with it the last enemy).
int32_t opens(TalkState& n)
{
    if (n.talkPhase == 0) {
        n.waitframe = 15;
    } else if (n.talkPhase == 1) {
        addCandidate(n, step(0x22));
        showFlowMessage(n, n.talkRequestType == 0 && n.data->enemypcnt == 1 ? 0xf : n.talkRequestType + 0x13);
    }
    return 0;
}

// Flow1_31 @ 0x0026E508: the introduction. First the two face each other
// (by the talk type, from the talker's side or the demon's), the party's
// slots back in place and both shown; then a call's pause; then a skill's
// words (temp_param[0], once) and Corpus's refusal (the talk fails); then
// on to the step noted in workid[3].
int32_t introduction(TalkState& n)
{
    switch (n.talkPhase) {
    case 0: {
        Formation* focus = nullptr;
        switch (n.talkType) {
        case 0: case 6:
            GetMotionNo(*n.pform, 0);
            focus = n.pform.get();
            break;
        case 1: case 2: case 3: case 4:
            GetMotionNo(*n.eform, 0);
            focus = n.eform.get();
            break;
        default:
            break;
        }
        if (focus) {
            const ee::Float hundred = ee::Float::fromBits(0x42c80000);
            n.pform->cr = hundred / n.pform->scl;
            n.eform->cr = hundred / n.eform->scl;
            MakeTargetPacket(ee::Float::fromBits(0x3f800000), 0, *n.actdata, *focus, n.actdata->select & 0xffff, 3);
            cameraOnPair(*n.pform, *n.eform);
        }
        Formation* forms = guest::table<Formation>(n.data->form.address);
        for (int32_t i = 0; i < 4; ++i)
            resetFormationPlace(forms[i]);
        showFormation(*n.pform);
        showFormation(*n.eform);
        return 0;
    }
    case 2: {
        if (n.flag1_6 == 1) {
            showFlowMessage(n, n.temp_param[0]);
            n.flag1_6 = 0;
        }
        if (n.flag1_39 == 1) {
            showFlowMessage(n, n.temp_param[0]);
            return 1;
        }
        return 0;
    }
    case 3:
        addCandidate(n, n.workid[3]);
        return 0;
    default:
        return 0;
    }
}

// Flow1_32 @ 0x0026D3F0: after a pause, the race's or the pair's words.
// The demon and one of its kind with words of their own (the talk ends,
// result 2); a moonproof demon's (0x80), a Tyrant-like asked to join
// (0x127), or 0x20; the talk fails.
int32_t raceWords(TalkState& n)
{
    n.waitframe = 15;
    for (const OwnPair& pair : kOwnPairs)
        if (n.ework->id == pair.devil && n.pwork->id == pair.devil) {
            showFlowMessage(n, pair.message);
            return 2;
        }
    if (moonproof(n.ework->id))
        showFlowMessage(n, 0x80);
    else if (tyrantLike(*n.ework) && n.talkRequestType == 0)
        showFlowMessage(n, 0x127);
    else
        showFlowMessage(n, 0x20);
    return 1;
}

// Flow1_33 @ 0x0026D300: the introduction and 1_32's words for one of the
// talker's kind, a Tyrant-like asked to join, or a dark demon (alignment
// -1) not talked to with Jive Talk; else 1_12.
int32_t wordsOrNot(TalkState& n)
{
    addCandidate(n, step(0xc));
    addCandidate(n, kIntroduction);
    n.workid[3] = step(0x20);
    if (n.pwork->id == n.ework->id) {
        n.nextTalkId = n.candidates[0];
        return 0;
    }
    if (tyrantLike(*n.ework) && n.talkRequestType == 0) {
        n.nextTalkId = n.candidates[1];
        return 0;
    }
    n.nextTalkId = n.candidates[dat::alignment(*n.ework) < 0 && n.talkSkill != skill::JiveTalk ? 1 : 0];
    return 0;
}

// Flow1_34 @ 0x0026E788: by the talk skill's kind: none, 1_35; else 1_38.
int32_t bySkillKind(TalkState& n)
{
    addCandidate(n, step(0x23));
    addCandidate(n, step(0x26));
    const int32_t kind = *guest::table<const int32_t>(kTalkSkills + (n.talkSkill - 0x180) * 0x68);
    n.nextTalkId = n.candidates[kind == 0 ? 0 : 1];
    return 0;
}

// Flow1_35 @ 0x0026E808: a demon above the Demi-fiend's level (its kind's
// level), 1_36; else 1_37.
int32_t byLevel(TalkState& n)
{
    addCandidate(n, step(0x24));
    addCandidate(n, step(0x25));
    n.nextTalkId = n.candidates[dat::playerLevel() < dat::devilFormat(n.ework->id).level ? 0 : 1];
    return 0;
}

// Flow1_36 @ 0x0026E888: message 0x36; the talk fails.
int32_t tooStrong(TalkState& n)
{
    showFlowMessage(n, 0x36);
    return 1;
}

// Flow1_37 @ 0x0026E8C0: Elements (0x65), Mitamas (0x66) and Corpus (0x37)
// won't bargain (the talk fails); others go on to group 6.
int32_t raceBargains(TalkState& n)
{
    int32_t message = 0;
    switch (dat::devilFormat(n.ework->id).race) {
    case Race::Element: message = 0x65; break;
    case Race::Mitama: message = 0x66; break;
    case Race::Corpus: message = 0x37; break;
    default: break;
    }
    if (message != 0) {
        showFlowMessage(n, message);
        return 1;
    }
    addCandidate(n, 0x60001);
    return 0;
}

// Flow1_38 @ 0x0026E9A0: Corpus talked to with skill 0x193 (message 100;
// the talk fails); else group 6.
int32_t corpusSkill(TalkState& n)
{
    if (dat::devilFormat(n.ework->id).race == Race::Corpus && n.talkSkill == skill::Skill193) {
        showFlowMessage(n, 100);
        return 1;
    }
    addCandidate(n, 0x60001);
    return 0;
}

// Flow1_39 @ 0x0026EA30: Corpus asked to join refuses in the introduction
// (message 0x2B or 0x2C); else 1_19.
int32_t corpusRefuses(TalkState& n)
{
    if (dat::devilFormat(n.ework->id).race == Race::Corpus && n.talkRequestType == 0) {
        n.flag1_39 = 1;
        addCandidate(n, kIntroduction);
        n.temp_param[0] = sdf::GetRandInt(2) == 0 ? 0x2c : 0x2b;
    } else {
        addCandidate(n, step(0x13));
    }
    return 0;
}

const TalkStep kOpeningSteps[40] = {
    nullptr,        nullptr,        nullptr,        talkerCanTalk,  wontListen,     specialSkill,   skillWords,
    demonCanTalk,   demonCantTalk,  demonsAilment,  bossOrNot,      bossRefuses,    loanDue,        loanDueGoesOn,
    loanWords,      collects,       collectsThird,  paysUp,         fullMoonOrNot,  kinOrNot,       inStockOrNot,
    othersOrNot,    alwaysBreaksIn, brokenIn,       mayBreakIn,     breaksIn,       fatedOrNot,     honbouOrNot,
    wontTalk,       refusesToTalk,  opens,          introduction,   raceWords,      wordsOrNot,     bySkillKind,
    byLevel,        tooStrong,      raceBargains,   corpusSkill,    corpusRefuses,
};

// nbNegoFlowOne @ 0x0026EAD8
int32_t openingFlow(TalkState& n) { return kOpeningSteps[n.talkId & 0xffff](n); }

} // namespace nocturne::nb

// ===========================================================================
// By version (nocturne/build.hpp): the alternatives the builds choose between
// ===========================================================================

namespace nocturne::nb {

#if NOCTURNE_HARDTYPE
// Flow1_10 @ 0x0026D190 (and 0x2FEF80): a boss battle (stat 1), or an
// encounter with flag 0x40.
bool battleRefusesTalk(const MainProcessData& data)
{
    return (dat::encount(data.encno).flag & 0x40) || (data.stat & 1);
}
#else
// Flow1_10 @ 0x0026D190: a boss battle (stat 1).
bool battleRefusesTalk(const MainProcessData& data) { return (data.stat & 1) != 0; }
#endif

} // namespace nocturne::nb
