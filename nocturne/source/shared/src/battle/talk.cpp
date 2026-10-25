// Talks with a demon (original unit: nbNegoProcess): the talk's helpers.
// Rewritten from the original instructions.
#include "nocturne/battle/talk.hpp"
#include "nocturne/address.hpp"
#include "nocturne/battle/sound.hpp"
#include "nocturne/battle/talk_flow.hpp"

#include <cstring>
#include <utility>

#include "nocturne/data/tables.hpp"
#include "nocturne/ee/float.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"
#include "nocturne/interface/message.hpp"
#include "nocturne/battle/kouka.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/unit.hpp"

namespace nocturne::nb {

namespace {

// Weighted choices (percent weights, summed in order until past a 0..99 roll).
constexpr uint32_t kRequestWeights = addr(0x003e22a8);       // [reqtype][5]: what a demon asks for
constexpr uint32_t kAskedItems = addr(0x003e2318);           // [level band][4] {item, weight}
constexpr uint32_t kExtraRequestWeights = addr(0x003e23b8);  // [tuikareqtype][3]
constexpr uint32_t kAskedItemsB = addr(0x003e23f8);          // [level band][3] {item, weight}
constexpr uint32_t kMaccaRate = addr(0x0054e5a0);            // float (gp-relative): 0.8
constexpr uint32_t kInfo = addr(0x003e4058);                 // [60] the information messages: 3 event bits, then the rest (0xCC bytes)
constexpr uint32_t kOwnQuestions = addr(0x003e2508);         // [privateselindex][4] question weights (datNegoPrivateQues)
constexpr uint32_t kTalkSkills = addr(0x003e1338);           // [skill - 0x180] the talk skills: kind (0x68 bytes)
constexpr uint32_t kFatedPairs = addr(0x003e3158);           // [64] {used, player's devil, demon, ...} (0x3C bytes)

const uint8_t* bytes(uint32_t address) { return guest::table<const uint8_t>(address); }

// The first of `count` weights (`stride` bytes apart) whose running sum
// passes the roll; the first if none does.
int32_t pickWeighted(const uint8_t* weights, int32_t count, int32_t stride)
{
    const int32_t roll = static_cast<int32_t>(sdf::GetRandInt(100));
    int32_t sum = 0;
    for (int32_t i = 0; i < count; ++i) {
        sum += weights[i * stride];
        if (roll < sum)
            return i;
    }
    return 0;
}

// Macca amounts are rounded to tens, and never 0.
int32_t roundMacca(int32_t value)
{
    value = (value + 5) / 10 * 10;
    return value != 0 ? value : 1;
}

// A gift from one of the talk record's lists of four {weight, item}.
int32_t pickGift(const TalkGift (&gifts)[4])
{
    const int32_t roll = static_cast<int32_t>(sdf::GetRandInt(100));
    int32_t sum = 0;
    for (const TalkGift& gift : gifts) {
        sum += gift.weight;
        if (roll < sum)
            return gift.item;
    }
    return 0;
}

const int16_t* infoEntry(int32_t message) { return guest::table<const int16_t>(kInfo + static_cast<uint32_t>(message) * 0xcc); }

} // namespace

// nbAddNegoIdKouho @ 0x0026A8A0
void addCandidate(TalkState& n, uint32_t id)
{
    if (n.candidateCount < 8)
        n.candidates[n.candidateCount++] = id;
}

// nbGetPrevNegoId @ 0x0026A8D0
uint32_t previousTalkId(const TalkState& n) { return n.history[n.historyindex]; }

// nbGetBackNoNegoId @ 0x0026A8E8: `back` steps before the last.
uint32_t talkIdBack(const TalkState& n, int32_t back) { return n.history[(n.historyindex - back + 15) % 14]; }

// nbSetMesMakka @ 0x0026A918
void setMaccaVariable(int32_t window, int32_t macca) { mes::SetVarFormatted(window, 3, macca, mes::kVarNumber); }

// nbSetMesItem @ 0x0026A938
void setItemVariable(int32_t window, int32_t item) { mes::SetVarFormatted(window, 2, item, mes::kVarItem); }

// nbClsNegoMessage @ 0x0026A958
void closeTalkWindow(TalkState& n)
{
    if (n.msgwndid >= 0) {
        mes::MsgWndCls(n.msgwndid);
        n.msgwndid = -1;
    }
}

// nbDispNegoMessage @ 0x0026A998: the message is shown by the talk process.
void showTalkMessage(TalkState& n, int32_t msgid, int32_t msgno, bool select)
{
    n.nowmsgid = msgid;
    n.nowmsgno = msgno;
    n.nowselect = 0;
    if (select) {
        n.stat |= 4;
    } else {
        n.nowmes = msgno;
        n.stat &= ~4u;
    }
}

// nbCheckNegoMessage @ 0x0026A9D0: the message has been read (a selection:
// answered, the answer in nowselect); the window is let go.
bool talkMessageDone(TalkState& n)
{
    if (n.nowmsgid < 0) {
        n.nowmsgid = -1;
        return true;
    }
    if (!(n.stat & 4)) {
        if (mes::CommandGetPhase(n.nowmsgid) >= 0)
            return false;
        mes::CommandSetPhase(n.nowmsgid, 0);
    } else {
        if (mes::CommandGetSelPhase(n.nowmsgid) >= 0)
            return false;
        mes::CommandSetSelPhase(n.nowmsgid, 0);
        n.nowselect = mes::CommandGetSelectNo(n.nowmsgid);
        mes::RequestSelectRelease(n.nowmsgid);
    }
    n.nowmsgid = -1;
    return true;
}

// nbSetNegoMesVar @ 0x0026AA88
void setTalkVariables(int32_t window, const UnitWork& player, const UnitWork& enemy)
{
    mes::SetVarFormatted(window, 0, enemy.id, mes::kVarDevil);
    mes::SetVarFormatted(window, 4, static_cast<int32_t>(dat::devilFormat(enemy.id).race), mes::kVarRace);
    if (player.flag & UnitFlag::PlayerCharacter) {
        mes::SetVarFormatted(window, 1, 0, mes::kVarCharacter);
        mes::SetVarFormatted(window, 5, static_cast<int32_t>(dat::devilFormat(0).race), mes::kVarRace);
    } else {
        mes::SetVarFormatted(window, 1, static_cast<int16_t>(player.id), mes::kVarDevil);
        mes::SetVarFormatted(window, 5, static_cast<int32_t>(dat::devilFormat(player.id).race), mes::kVarRace);
    }
}

// nbGetNegoYaruMakkaA @ 0x0026AB80: five to eight times its Macca reward.
int32_t demonGivesMacca(TalkState&, const UnitWork&, const UnitWork& b)
{
    const uint32_t roll = sdf::GetRandInt(4);
    return roundMacca(static_cast<int32_t>(dat::devilFormat(b.id).dropmakka * (roll + 5)));
}

// nbGetNegoYaruMakkaB @ 0x0026AC00: 40..69% of what it would ask.
int32_t demonGivesMaccaB(TalkState& n, const UnitWork& a, const UnitWork& b)
{
    const int32_t asked = demonAsksMacca(n, a, b);
    const uint32_t roll = sdf::GetRandInt(30);
    return roundMacca(static_cast<int32_t>(asked * static_cast<int32_t>(roll + 40)) / 100);
}

// nbGetNegoKureMakkaA @ 0x0026AC78: the demon's level x 21..30 x 0.8.
int32_t demonAsksMacca(TalkState&, const UnitWork&, const UnitWork& b)
{
    const uint32_t roll = sdf::GetRandInt(10);
    const int32_t base = static_cast<int32_t>(b.level * (roll + 21));
    const ee::Float rate = *guest::table<const ee::Float>(kMaccaRate);
    return roundMacca((ee::Float::fromInt(base) * rate).toInt());
}

// nbGetNegoKureMakkaB @ 0x0026ACF8: 50..69% of that.
int32_t demonAsksMaccaB(TalkState& n, const UnitWork& a, const UnitWork& b)
{
    const int32_t asked = demonAsksMacca(n, a, b);
    const uint32_t roll = sdf::GetRandInt(20);
    return roundMacca(static_cast<int32_t>(asked * static_cast<int32_t>(roll + 50)) / 100);
}

// nbGetNegoKureHpA @ 0x0026AD70: 14..21% of its maximum HP, 20..29% when
// event bit 8 is set.
int32_t demonAsksHp(TalkState&, const UnitWork&, const UnitWork& b)
{
    const int32_t percent = evt::BitCheck(8) ? static_cast<int32_t>(sdf::GetRandInt(10)) + 20
                                             : static_cast<int32_t>(sdf::GetRandInt(8)) + 14;
    return static_cast<int32_t>(b.maxhp * static_cast<uint32_t>(percent)) / 100;
}

// nbGetNegoKureHpB @ 0x0026ADE8: 10..19%.
int32_t demonAsksHpB(TalkState&, const UnitWork&, const UnitWork& b)
{
    const uint32_t roll = sdf::GetRandInt(10);
    return static_cast<int32_t>(b.maxhp * (roll + 10)) / 100;
}

// nbGetNegoKureMpA @ 0x0026AE38: 10..39% of its maximum MP.
int32_t demonAsksMp(TalkState&, const UnitWork&, const UnitWork& b)
{
    const uint32_t roll = sdf::GetRandInt(30);
    return static_cast<int32_t>(b.maxmp * (roll + 10)) / 100;
}

// nbGetNegoKureMpB @ 0x0026AE88: 10..19%.
int32_t demonAsksMpB(TalkState&, const UnitWork&, const UnitWork& b)
{
    const uint32_t roll = sdf::GetRandInt(10);
    return static_cast<int32_t>(b.maxmp * (roll + 10)) / 100;
}

// nbGetKureItemA @ 0x0026AED8: an item by the demon's level band (five
// levels each), 0 for level 0 or 100 and up.
int32_t demonAsksItem(TalkState&, const UnitWork&, const UnitWork& b)
{
    if (b.level == 0 || b.level >= 100)
        return 0;
    const int32_t band = (b.level - 1) / 5;
    const int32_t choice = pickAskedItem(band);
    return bytes(kAskedItems)[(band * 4 + choice) * 2];
}

// nbSelectKureItemA @ 0x0026AF58
int32_t pickAskedItem(int32_t levelBand) { return pickWeighted(bytes(kAskedItems + 1) + levelBand * 8, 4, 2); }

// nbGetKureItemB @ 0x0026AFD8: the same from the second table.
int32_t demonAsksItemB(TalkState&, const UnitWork&, const UnitWork& b)
{
    if (b.level == 0 || b.level >= 100)
        return 0;
    const int32_t band = (b.level - 1) / 5;
    const int32_t choice = pickAskedItemB(band);
    return bytes(kAskedItemsB)[(band * 3 + choice) * 2];
}

// nbSelectKureItemB @ 0x0026B058
int32_t pickAskedItemB(int32_t levelBand) { return pickWeighted(bytes(kAskedItemsB + 1) + levelBand * 6, 3, 2); }

// nbGetNegoRequestType @ 0x0026B0E0
int32_t pickRequestType(int32_t reqtype) { return pickWeighted(bytes(kRequestWeights) + reqtype * 5, 5, 1); }

// nbGetNegoTuikaRequestType @ 0x0026B160 ("tuika" = 追加, extra)
int32_t pickExtraRequestType(int32_t tuikareqtype)
{
    return pickWeighted(bytes(kExtraRequestWeights) + tuikareqtype * 3, 3, 1);
}

// nbSetAllHojoSkillWork @ 0x0026B1E0: every party slot's helper skills are
// cleared (and their "used" mark, flag 0x80); the player's side but the one
// talking lists the talk skills of kind 7 its unit has, if it can talk.
void collectBuffSkills(TalkState& n)
{
    MainProcessData& main = *n.data;
    for (int32_t i = 0; i < kFormationCount; ++i) {
        Party& party = main.party[i];
        for (uint16_t& skill : party.buffSkills)
            skill = 0;
        const uint16_t flag = static_cast<uint16_t>(party.flag);
        party.flag = static_cast<int16_t>(flag & 0xff7f);
        if (i >= 4 || !(flag & 1) || i == n.ppartyindex)
            continue;
        const UnitWork& unit = *GetUnitWorkPointer(main, party);
        if (!dat::canTalk(unit))
            continue;
        // (no limit: past eight the original writes on into the party record)
        uint16_t* slot = guest::table<uint16_t>(guest::addressOf(&party) + offsetof(Party, buffSkills));
        for (int32_t k = 0; k < unit.skillcnt; ++k) {
            const uint16_t skill = unit.skill[k];
            if (dat::skillInfo(skill).type == 2 &&
                *guest::table<const int32_t>(kTalkSkills + (static_cast<uint32_t>(skill) - 0x180) * 0x68) == 7)
                *slot++ = skill;
        }
    }
}

// nbGetHojoSkillWorkCnt @ 0x0026B368: the helper skills not yet used.
int32_t countBuffSkills(const TalkState& n)
{
    int32_t count = 0;
    for (int32_t i = 0; i < 4; ++i) {
        const Party& party = n.data->party[i];
        if (!(party.flag & 1) || (party.flag & 0x80))
            continue;
        for (uint16_t skill : party.buffSkills)
            if (skill != 0 && !(skill & 0x8000))
                ++count;
    }
    return count;
}

namespace {

// Which helper skills apply at each moment of a talk (nbSearchHojoSkillWork's
// type): 0x199 at 0; 0x19A, 0x1A2, 0x1A3 at 1; 0x19B, 0x1A3 at 2; at 3
// 0x19D..0x1A1, 0x1A3, 0x1A4, and 0x19C when the helper is of the demon's race.
bool buffSkillApplies(uint16_t skill, int32_t type, const UnitWork& helper, const UnitWork& demon)
{
    switch (type) {
    case 0: return skill == 0x199;
    case 1: return skill == 0x19a || skill == 0x1a2 || skill == 0x1a3;
    case 2: return skill == 0x19b || skill == 0x1a3;
    case 3:
        switch (skill) {
        case 0x19c: return dat::devilFormat(helper.id).race == dat::devilFormat(demon.id).race;
        case 0x19d: case 0x19e: case 0x19f: case 0x1a0: case 0x1a1: case 0x1a3: case 0x1a4: return true;
        default: return false;
        }
    default: return false;
    }
}

} // namespace

// nbSearchHojoSkillWork @ 0x0026B3F8: the helpers (the player's side but the
// one talking), the most agile first; the first not yet used who has a skill that
// applies uses one of them at random: the skill and the helper are marked
// used (0x8000, flag 0x80).
uint32_t useBuffSkill(TalkState& n, int32_t type)
{
    MainProcessData& main = *n.data;
    int32_t helpers[4];
    int32_t count = 0;
    for (int32_t i = 0; i < 4; ++i)
        if ((main.party[i].flag & 1) && i != n.ppartyindex)
            helpers[count++] = i;
    if (count == 0)
        return 0;
    for (int32_t i = 0; i < count - 1; ++i)
        for (int32_t j = i + 1; j < count; ++j) {
            const UnitWork& a = *GetUnitWorkPointer(main, main.party[helpers[i]]);
            const UnitWork& b = *GetUnitWorkPointer(main, main.party[helpers[j]]);
            if (dat::param(a, Param::Agility) < dat::param(b, Param::Agility))
                std::swap(helpers[i], helpers[j]);
        }
    for (int32_t h = 0; h < count; ++h) {
        Party& party = main.party[helpers[h]];
        const UnitWork& helper = *GetUnitWorkPointer(main, party);
        if (party.flag & 0x80)
            continue;
        uint32_t options[8];
        int32_t optionCount = 0;
        for (uint16_t skill : party.buffSkills)
            if (skill != 0 && !(skill & 0x8000) && buffSkillApplies(skill, type, helper, *n.ework))
                options[optionCount++] = skill;
        if (optionCount <= 0)
            continue;
        const uint32_t chosen = options[sdf::GetRandInt(optionCount)];
        for (uint16_t& skill : party.buffSkills)
            if (skill == chosen)
                skill = static_cast<uint16_t>(chosen | 0x8000);
        party.flag = static_cast<int16_t>(party.flag | 0x80);
        return static_cast<uint32_t>(helpers[h]) << 16 | chosen;
    }
    return 0;
}

// nbGetQuestionType @ 0x0026B7C8: the question the demon asks. A demon
// with its own questions (privatesel 1) picks one of four from its set.
// Others ask (half the time once the player has answered at least half as
// many by kind as in all, else eight times in ten) a question of kind 1, 2
// or 3, weighted by how the player's answers so far rank.
int32_t questionType(const UnitWork& w)
{
    const DevilTalkFormat& f = dat::devilTalkFormat(w.id);
    if (f.privatesel == 1)
        return pickWeighted(bytes(kOwnQuestions) + f.privateselindex * 4, 4, 1);
    const uint8_t* answers = dat::globalWork().questionAnswers;
    int32_t byKind = 0;
    for (int32_t i = 1; i <= 3; ++i)
        byKind += answers[i];
    const bool ask = answers[0] < byKind * 2 ? sdf::GetRandInt(2) == 0 : sdf::GetRandInt(100) < 0x50;
    if (!ask)
        return 0;
    // Rank the kinds by their counts, as the original does. (It then compares
    // the kinds' indices, which always differ, so the odds never change:
    // kind 2 three times in ten, else kind 3; never kind 1.)
    uint32_t high = 1, low = 2;
    if (answers[1] < answers[2]) {
        high = 2;
        low = 1;
    }
    uint32_t first = high;
    if (answers[high] < answers[3]) {
        first = low;
        low = high;
    }
    uint32_t middle = low, last = 3;
    if (answers[low] < answers[3]) {
        middle = 3;
        last = low;
    }
    int32_t chanceOne = 0, chanceTwo = 0x1e;
    if (first == middle && middle == last) {
        chanceOne = chanceTwo = 0x21;
    } else if (first == middle && last < middle) {
        chanceOne = chanceTwo = 0xf;
    } else if (middle < first && middle == last) {
        chanceTwo = 0x32;
    }
    const int32_t roll = static_cast<int32_t>(sdf::GetRandInt(100));
    if (roll < chanceOne)
        return 1;
    return roll < chanceOne + chanceTwo ? 2 : 3;
}

// nbGetNegoYaruItemA @ 0x0026BA28
int32_t demonGivesItem(const UnitWork& w) { return pickGift(dat::devilTalkFormat(w.id).itemA); }

// nbGetNegoYaruItemB @ 0x0026BAB8
int32_t demonGivesItemB(const UnitWork& w) { return pickGift(dat::devilTalkFormat(w.id).itemB); }

// nbGetNegoYaruStone @ 0x0026BB48
int32_t demonGivesStone(const UnitWork& w) { return pickGift(dat::devilTalkFormat(w.id).stones); }

// nbGetInfoMsg @ 0x0026BBD8: one of 30 messages (infotype 2: the second
// 30): with eight chances in ten one whose event bits are all set, if any,
// else any that has none.
int32_t pickInfoMessage(int32_t infotype)
{
    const int32_t first = infotype == 2 ? 0x1e : 0;
    int32_t plain[30], unlocked[30];
    uint32_t plainCount = 0, unlockedCount = 0;
    for (int32_t i = 0; i < 30; ++i)
        if (infoEntry(first + i)[0] == 0)
            plain[plainCount++] = first + i;
    for (int32_t i = 0; i < 30; ++i)
        if (infoAvailable(first + i))
            unlocked[unlockedCount++] = first + i;
    bool useUnlocked = false;
    if (unlockedCount != 0)
        useUnlocked = sdf::GetRandInt(10) > 1;
    const int32_t message = useUnlocked ? unlocked[sdf::GetRandInt(static_cast<int32_t>(unlockedCount))]
                                        : plain[sdf::GetRandInt(static_cast<int32_t>(plainCount))];
    diag::print(diag::Message::InfoChosen, useUnlocked ? 1 : 0, message);
    diag::print(diag::Message::InfoCounts, plainCount, unlockedCount);
    return message;
}

// nbCheckSelectMesJoukenAri @ 0x0026BD50: the message has event bits (up to
// three) and all are set.
bool infoAvailable(int32_t message)
{
    const int16_t* bits = infoEntry(message);
    if (bits[0] == 0)
        return false;
    for (int32_t i = 0; i < 3; ++i) {
        if (bits[i] == 0)
            return true;
        if (!evt::BitCheck(bits[i]))
            return false;
    }
    return true;
}

// nbSetNegoNoMotion @ 0x0026BDE0: the window closes, the unit shakes its
// head (motion 15) with its voice's second sound; 15 frames.
int32_t refuseMotion(TalkState& n, Formation& form)
{
    closeTalkWindow(n);
    const int32_t action = static_cast<int32_t>(n.actdata.address);
    addMotionPacket(0, action, &form, 0xf);
    addSoundPacket2(0, action, formationTalkBank(form) + 1);
    return 0xf;
}

// nbSetNegoYesMotion @ 0x0026BE40: ... nods (motion 14) with its voice.
int32_t agreeMotion(TalkState& n, Formation& form)
{
    closeTalkWindow(n);
    const int32_t action = static_cast<int32_t>(n.actdata.address);
    addMotionPacket(0, action, &form, 0xe);
    addSoundPacket2(0, action, formationTalkBank(form));
    return 0xf;
}

// nbGetInnenNegoID @ 0x0026BEA0 ("innen" = 因縁, fate): the entry for this
// player-side devil and demon, if any.
int32_t fatedPair(const TalkState& n)
{
    for (int32_t i = 0; i < 64; ++i) {
        const int16_t* pair = guest::table<const int16_t>(kFatedPairs + static_cast<uint32_t>(i) * 0x3c);
        if (pair[0] != 0 && n.pwork->id == static_cast<uint16_t>(pair[1]) && n.ework->id == static_cast<uint16_t>(pair[2]))
            return i;
    }
    return -1;
}

// ---- the process ----

namespace {

constexpr uint32_t kTalkName = addr(0x00551160);      // "nb_nego"
constexpr uint32_t kTalkMessages = addr(0x004e3be8);  // [31] {flow, affinity, question, info} message tables
constexpr uint32_t kBossMessages = addr(0x004eb810);
constexpr uint32_t kHelpMessages = addr(0x004ee8b0);
constexpr uint32_t kHelpMessages2 = addr(0x004ef0c8);
constexpr uint32_t kFatedMessages = addr(0x004e3dd8);
constexpr uint32_t kDebugMode = 0x400000;       // battle stat: the talks' debug menu

constexpr uint32_t kRunTalk = addr(0x0026c4f0), kShowMessage = addr(0x0026c400), kWaitMessage = addr(0x0026c390), kEndTalk = addr(0x0026c4c0);
constexpr uint32_t kShutdownTalk = addr(0x0026c780);

TalkState& talkOf(uint32_t process) { return *guest::table<TalkState>(dds3::GetProcessData(process)); }
uint32_t addressOf(const TalkState& n) { return guest::addressOf(&n); }

// A message table of the talk: its window, with the talk's variables set.
int32_t openTable(TalkState& n, uint32_t table)
{
    const int32_t window = mes::Initialize(table);
    setTalkVariables(window, *n.pwork, *n.ework);
    return window;
}

void closeTable(int32_t& window)
{
    if (window >= 0) {
        mes::Release(window);
        window = -1;
    }
}

} // namespace

// nbSetNegoPose @ 0x0024CF70 (no original name)
// The demon takes its talking pose (motion 13),
// unless asleep (8), stoned or the like (4, 0x200).
void takeTalkPose(Formation& form)
{
    UnitWork* unit = GetUnitWorkFromFormindex(form.formindex);
    if (!unit)
        return;
    const uint16_t bad = unit->badstat & 0xfff;
    if (bad == 8 || bad == (bad < 9 ? 4 : 0x200))
        return;
    SetWaitMotion(form, 0xd, ee::Float::fromInt(1));
    SetUnitMotion(form, 0xd, 0, ee::Float::fromInt(1));
}

// InitNegoProcessData @ 0x0026C8F0: the talk's first step by its type (0, 6
// an ordinary talk from step 0x10007; 1..5 one started by a talk skill, the
// skill 0x180 but for 3), the request kind by the talk skill's kind, both
// sides, and its message tables.
uint32_t newTalk(ActionProcessData& act, int32_t pformindex, int32_t eformindex, int32_t talkType, int32_t skill)
{
    const uint32_t address = mem::PoolAllocate(sizeof(TalkState));
    std::memset(guest::table<uint8_t>(address), 0, sizeof(TalkState));
    TalkState& n = *guest::table<TalkState>(address);
    n.actdata.address = guest::addressOf(&act);
    n.data = act.data;
    switch (talkType) {
    case 0: case 6: n.talkId = 0x10007; break;
    case 1: n.talkId = 0xc0001; skill = 0x180; break;
    case 2: n.talkId = 0xd0001; skill = 0x180; break;
    case 3: n.talkId = 0xe0001; break;
    case 4: n.talkId = 0xf0001; skill = 0x180; break;
    case 5: n.talkId = 0x100001; skill = 0x180; break;
    default: break;
    }
    n.talkType = talkType;
    n.prevreqtype = -1;
    n.nowmsgid = -1;
    n.msgwndid = -1;
    n.flag1_6 = 0;
    n.flag1_39 = 0;
    switch (*guest::table<const int32_t>(kTalkSkills + static_cast<uint32_t>(skill - 0x180) * 0x68)) {
    case 0: n.talkRequestType = 0; break;
    case 1: n.talkRequestType = 2; break;
    case 2: n.talkRequestType = 3; break;
    case 3: n.talkRequestType = 4; break;
    case 4: n.talkRequestType = 1; break;
    case 5: n.talkRequestType = 5; break;
    case 6: n.talkRequestType = 6; break;
    default: n.talkRequestType = 0; break;   // (kind 7 too)
    }
    n.talkSkill = static_cast<uint32_t>(skill);
    MainProcessData& main = *n.data;
    n.pwork.address = guest::addressOf(GetUnitWorkFromFormindex(pformindex));
    n.pparty.address = guest::addressOf(GetPartyFromFormindex(pformindex));
    n.pformindex = pformindex;
    n.pform.address = guest::addressOf(&main.form[pformindex]);
    n.ppartyindex = main.form[pformindex].partyindex;
    n.ework.address = guest::addressOf(GetUnitWorkFromFormindex(eformindex));
    n.eparty.address = guest::addressOf(GetPartyFromFormindex(eformindex));
    n.eformindex = eformindex;
    n.epartyindex = main.form[eformindex].partyindex;
    n.pkucyo = static_cast<int32_t>(dat::devilTalkFormat(n.pwork->id).speechStyle);
    n.eform.address = guest::addressOf(&main.form[eformindex]);
    n.ekucyo = static_cast<int32_t>(dat::devilTalkFormat(n.ework->id).speechStyle);
    const uint32_t* tables = guest::table<const uint32_t>(kTalkMessages);
    for (int32_t i = 0; i < 31; ++i) {
        n.flowmsg[i] = -1;
        if (tables[i * 4] != 0)
            n.flowmsg[i] = openTable(n, tables[i * 4]);
    }
    n.questionmsg = openTable(n, tables[n.ekucyo * 4 + 2]);
    for (int32_t i = 0; i < 31; ++i) {
        n.infomsg[i] = -1;
        if (tables[i * 4 + 3] != 0)
            n.infomsg[i] = openTable(n, tables[i * 4 + 3]);
    }
    for (int32_t i = 0; i < 31; ++i) {
        n.aisyomsg[i] = -1;
        if (tables[i * 4 + 1] != 0)
            n.aisyomsg[i] = openTable(n, tables[i * 4 + 1]);
    }
    n.bossmsg = openTable(n, kBossMessages);
    n.helpmsg = openTable(n, kHelpMessages);
    n.helpmsg2 = openTable(n, kHelpMessages2);
    n.innenmsg = openTable(n, kFatedMessages);
    loadTalkSound(*n.eform);
    return address;
}

// nbInitNegoProcess @ 0x0026CCF0: the demon faces the talk, the helpers'
// skills are listed, the music turns down, and the talk runs as a child of
// the battle (TalkProcessID).
void startTalk(ActionProcessData& act, int32_t pformindex, int32_t eformindex, int32_t talkType, int32_t skill)
{
    const uint32_t address = newTalk(act, pformindex, eformindex, talkType, skill);
    TalkState& n = *guest::table<TalkState>(address);
    takeTalkPose(*n.eform);
    collectBuffSkills(n);
    snd::VolumeHalfDown();
    const uint32_t process = dds3::StartProcess(kTalkName, 0x3f9, 1, 1, kRunTalk, kShutdownTalk, address);
    dds3::LinkProcess(act.data->MainProcessID, process);
    act.data->TalkProcessID = process;
}

// nbNegoProcess1 @ 0x0026C4F0: the talk waits for its action's packets and
// its wait frames, then runs its steps. A step's flow function (by the step
// ID's high half) runs with its phase counting up; a result ends the talk
// (endtype); a step that chose its next one (or left candidates: the first)
// moves on, the step and its message going into the history. A message to
// show goes to nbNegoProcessMessage. With the debug menu on, it runs one
// step a frame and lets the menu pick among the candidates.
uint32_t runTalk(uint32_t process)
{
    TalkState& n = talkOf(process);
    const uint32_t self = addressOf(n);
    if (countActionPackets(static_cast<int32_t>(n.actdata.address)) >= 1)
        return 0;
    if (n.waitframe >= 1) {
        --n.waitframe;
        return 0;
    }
    if (n.data->stat & kDebugMode)
        TalkDebugDraw(self);
    do {
        if (!(n.stat & 1)) {
            if (n.endid != 1 && n.nextTalkId == 0) {
                n.nextTalkId = 0;
                n.candidateCount = 0;
                const int32_t result = runTalkStep(n);
                ++n.talkPhase;
                if (result != 0) {
                    n.endid = 1;
                    n.endtype = result;
                }
                uint32_t next = n.nextTalkId;
                if (next == 0 && n.candidateCount > 0)
                    n.nextTalkId = next = n.candidates[0];
                if (next != 0 && (n.data->stat & kDebugMode)) {
                    n.selectcur = 0;
                    n.stat |= 1;
                    if (n.candidateCount > 0 && n.candidates[0] != next)
                        for (int32_t i = 1; i < n.candidateCount; ++i)
                            if (n.candidates[i] == next) {
                                n.selectcur = i;
                                break;
                            }
                }
            }
        } else {
            TalkDebugSelectDraw(self);
            if (TalkDebug(self) != 0)
                n.stat &= ~1u;
        }
        if (countActionPackets(static_cast<int32_t>(n.actdata.address)) >= 1 || n.waitframe >= 1)
            return 0;
        if (n.nowmsgid >= 0)
            return kShowMessage;
        if (!(n.stat & 1)) {
            if (n.endid == 1)
                return kEndTalk;
            if (n.nextTalkId != 0) {
                n.historyindex = (n.historyindex + 1) % 14;
                n.history[n.historyindex] = n.talkId;
                n.historymes[n.historyindex] = n.nowmes;
                n.talkPhase = 0;
                n.candidateCount = 0;
                n.talkId = n.nextTalkId;
                n.nextTalkId = 0;
                n.nowmes = 0;
            }
        }
    } while (!(n.data->stat & kDebugMode));
    return 0;
}

// nbNegoProcessMessage @ 0x0026C400: the step's message (or selection)
// opens in its window, the talk's window before it closing.
uint32_t showTalkStepMessage(uint32_t process)
{
    TalkState& n = talkOf(process);
    if (n.data->stat & kDebugMode)
        TalkDebugDraw(addressOf(n));
    if (n.msgwndid >= 0 && n.msgwndid != n.nowmsgid) {
        mes::MsgWndCls(n.msgwndid);
        n.msgwndid = -1;
    }
    mes::MarkBitStat(n.nowmsgid, 0x200000);
    if (!(n.stat & 4))
        mes::RequestMessage(n.nowmsgid, n.nowmsgno, 0);
    else
        mes::RequestSelect(n.nowmsgid, n.nowmsgno);
    n.msgwndid = n.nowmsgid;
    return kWaitMessage;
}

// nbNegoProcessMessageChk @ 0x0026C390: back to the steps once it is read.
uint32_t waitTalkStepMessage(uint32_t process)
{
    TalkState& n = talkOf(process);
    if (n.data->stat & kDebugMode)
        TalkDebugDraw(addressOf(n));
    if (!talkMessageDone(n))
        return 0;
    diag::print(diag::Message::TalkMessageEnd);
    return kRunTalk;
}

// nbNegoProcessEnd @ 0x0026C4C0
uint32_t endTalk(uint32_t process)
{
    TalkState& n = talkOf(process);
    n.data->talkResult = n.endtype;
    return 0xffffffffu;
}

// nbNegoShutdown @ 0x0026C780: the message tables let go, the battle's
// talk process cleared, the music back up.
void shutdownTalk(uint32_t process)
{
    const uint32_t address = dds3::GetProcessData(process);
    TalkState& n = *guest::table<TalkState>(address);
    for (int32_t& window : n.flowmsg)
        closeTable(window);
    closeTable(n.questionmsg);
    for (int32_t& window : n.infomsg)
        closeTable(window);
    for (int32_t& window : n.aisyomsg)
        closeTable(window);
    closeTable(n.bossmsg);
    closeTable(n.helpmsg);
    closeTable(n.helpmsg2);
    closeTable(n.innenmsg);
    if (n.data->TalkProcessID != 0)
        n.data->TalkProcessID = 0;
    mem::PoolRelease(address);
    snd::VolumeHalfUp();
}

} // namespace nocturne::nb
