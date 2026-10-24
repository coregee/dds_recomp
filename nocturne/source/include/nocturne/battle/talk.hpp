// Talks with a demon (original unit: nbNegoProcess): the talk's record, its
// process, and its helpers: the candidate next steps and the steps already
// taken, the message window, the message variables, and what a demon gives
// or asks for. The steps themselves are in talk_flow.hpp.
//
// Records are in their PS2 layout; names are the HD remaster's, in English
// where they were romanized ("yaru" = give, "kure" = give me).
#pragma once

#include <cstddef>
#include <cstdint>

#include "nocturne/battle/process.hpp"
#include "nocturne/data/records.hpp"

namespace nocturne::nb {

// nbNegoProcessData_t (0x33C bytes, from the pool)
struct TalkState {
    Ptr32<MainProcessData> data;
    Ptr32<ActionProcessData> actdata;
    uint32_t stat;              // bit 4: the message on screen is a selection
    int32_t talkType;           // (HD: negotype)
    int32_t waitframe;
    uint32_t talkId;            // the current step (HD: nownegoid)
    int32_t talkPhase;          // (HD: nownegophase)
    uint32_t nextTalkId;        // (HD: nextnegoid)
    int32_t candidateCount;     // the possible next steps (HD: nextkouhocnt)
    uint32_t candidates[8];     // (HD: nextkouho)
    int32_t nowmsgid;           // the window showing the step's message, -1 none
    int32_t nowmsgno;
    int32_t nowmes;             // the message (not a selection) last shown
    int32_t msgwndid;           // the talk's window, -1 none
    uint32_t unknown_54;
    int32_t nowselect;          // the answer chosen
    uint32_t workid[8];
    int32_t requesttype, requestdata, requesthpmp, prevreqtype;   // what the demon asks for
    int32_t cnt6_36, cnt6_37, cnt6_58, cnt6_66;   // counters and messages of particular steps
    int32_t mes6_2, mes6_25, mes6_67;
    int32_t flag1_6, flag1_39;
    int32_t historyindex;
    uint32_t history[14];       // the steps taken, a ring
    int32_t historymes[14];     // ... and their messages
    int32_t endid, endtype;
    int32_t talkRequestType;    // (HD: negoreqtype)
    uint32_t talkSkill;         // the skill that started the talk (HD: negoskillid)
    int32_t affinity, affinityMessage;          // (HD: aisyo, aisyomes)
    int32_t buffPartyIndex, buffSkill;          // a helper's buff (HD: hojopartyindex, hojoskillid)
    int32_t buffSucceeded, buffAffinity, buffAffinityMessage;   // (HD: hojoseikou, hojoaisyo, hojoaisyomes)
    int32_t qtype, qindex;      // the question asked
    Ptr32<UnitWork> pwork, ework;   // the player's side and the demon
    int32_t pformindex, eformindex;
    Ptr32<Formation> pform, eform;
    int32_t ppartyindex, epartyindex;
    Ptr32<Party> pparty, eparty;
    int32_t pkucyo, ekucyo;     // their speech styles (DevilTalkFormat::speechStyle)
    int32_t innen_id;           // the fated pair (nbGetInnenNegoID), -1 none
    int32_t temp_param[4];
    int32_t boupartyindex;
    int32_t getmakka, getitem, getinfotype, getinfomsg;   // what the player got
    // The talk's message tables (windows of the message manager), -1 none;
    // the steps use the demon's speech style's (ekucyo).
    int32_t flowmsg[31];        // the steps' messages
    int32_t questionmsg;        // the questions (the demon's style's only)
    int32_t aisyomsg[31];       // the helpers' affinity messages (HD name: "aisyo", affinity)
    int32_t infomsg[31];        // the information a demon tells
    int32_t helpmsg, helpmsg2, innenmsg, bossmsg;
    int32_t selectcur;          // the debug menu's cursor
};
static_assert(offsetof(TalkState, candidates) == 0x24 && offsetof(TalkState, msgwndid) == 0x50);
static_assert(offsetof(TalkState, nowselect) == 0x58 && offsetof(TalkState, history) == 0xb4);
static_assert(offsetof(TalkState, pwork) == 0x158 && offsetof(TalkState, ppartyindex) == 0x170);
static_assert(offsetof(TalkState, prevreqtype) == 0x88 && offsetof(TalkState, flag1_6) == 0xa8);
static_assert(offsetof(TalkState, flowmsg) == 0x1b0 && offsetof(TalkState, infomsg) == 0x2ac);
static_assert(sizeof(TalkState) == 0x33c);

// ---- the process ("nb_nego", a child of the battle's) ----
// Each returns the address of the process function to run next (0: the same
// again, -1: the talk is over).
uint32_t newTalk(ActionProcessData& act, int32_t pformindex, int32_t eformindex, int32_t talkType,
                 int32_t skill);                            // InitNegoProcessData: the record's address
void startTalk(ActionProcessData& act, int32_t pformindex, int32_t eformindex, int32_t talkType,
               int32_t skill);                              // nbInitNegoProcess
uint32_t runTalk(uint32_t process);                         // nbNegoProcess1: the steps
uint32_t showTalkStepMessage(uint32_t process);             // nbNegoProcessMessage
uint32_t waitTalkStepMessage(uint32_t process);             // nbNegoProcessMessageChk
uint32_t endTalk(uint32_t process);                         // nbNegoProcessEnd: the result to the battle
void shutdownTalk(uint32_t process);                        // nbNegoShutdown
void takeTalkPose(Formation& form);                         // nbSetNegoPose: the demon faces the talk

// ---- steps ----
void addCandidate(TalkState& n, uint32_t id);              // nbAddNegoIdKouho (at most 8)
uint32_t previousTalkId(const TalkState& n);               // nbGetPrevNegoId
uint32_t talkIdBack(const TalkState& n, int32_t back);     // nbGetBackNoNegoId

// ---- the message window ----
void setMaccaVariable(int32_t window, int32_t macca);      // nbSetMesMakka: {var 3}
void setItemVariable(int32_t window, int32_t item);        // nbSetMesItem: {var 2}
void closeTalkWindow(TalkState& n);                        // nbClsNegoMessage
void showTalkMessage(TalkState& n, int32_t msgid, int32_t msgno, bool select);   // nbDispNegoMessage
bool talkMessageDone(TalkState& n);                        // nbCheckNegoMessage
// nbSetNegoMesVar: {var 0} the demon, {var 4} its race; {var 1} and {var 5}
// the player's side (the Demi-fiend's name).
void setTalkVariables(int32_t window, const UnitWork& player, const UnitWork& enemy);

// ---- what changes hands (a: the player's side, b: the demon) ----
int32_t demonGivesMacca(TalkState& n, const UnitWork& a, const UnitWork& b);       // nbGetNegoYaruMakkaA
int32_t demonGivesMaccaB(TalkState& n, const UnitWork& a, const UnitWork& b);      // nbGetNegoYaruMakkaB
int32_t demonAsksMacca(TalkState& n, const UnitWork& a, const UnitWork& b);        // nbGetNegoKureMakkaA
int32_t demonAsksMaccaB(TalkState& n, const UnitWork& a, const UnitWork& b);       // nbGetNegoKureMakkaB
int32_t demonAsksHp(TalkState& n, const UnitWork& a, const UnitWork& b);           // nbGetNegoKureHpA
int32_t demonAsksHpB(TalkState& n, const UnitWork& a, const UnitWork& b);          // nbGetNegoKureHpB
int32_t demonAsksMp(TalkState& n, const UnitWork& a, const UnitWork& b);           // nbGetNegoKureMpA
int32_t demonAsksMpB(TalkState& n, const UnitWork& a, const UnitWork& b);          // nbGetNegoKureMpB
int32_t demonAsksItem(TalkState& n, const UnitWork& a, const UnitWork& b);         // nbGetKureItemA
int32_t pickAskedItem(int32_t levelBand);                                          // nbSelectKureItemA
int32_t demonAsksItemB(TalkState& n, const UnitWork& a, const UnitWork& b);        // nbGetKureItemB
int32_t pickAskedItemB(int32_t levelBand);                                         // nbSelectKureItemB
int32_t pickRequestType(int32_t reqtype);                  // nbGetNegoRequestType
int32_t pickExtraRequestType(int32_t tuikareqtype);        // nbGetNegoTuikaRequestType
// What the demon gives from its talk record's lists (weighted, 0 none).
int32_t demonGivesItem(const UnitWork& w);                 // nbGetNegoYaruItemA
int32_t demonGivesItemB(const UnitWork& w);                // nbGetNegoYaruItemB
int32_t demonGivesStone(const UnitWork& w);                // nbGetNegoYaruStone

// ---- the helpers' buffs: party members who can help the talk ----
void collectBuffSkills(TalkState& n);                      // nbSetAllHojoSkillWork
int32_t countBuffSkills(const TalkState& n);               // nbGetHojoSkillWorkCnt
// nbSearchHojoSkillWork: a helper's skill for this moment of the talk
// (type 0..3), used up; party slot << 16 | skill, or 0.
uint32_t useBuffSkill(TalkState& n, int32_t type);

// ---- questions ----
int32_t questionType(const UnitWork& w);                   // nbGetQuestionType: 0 none, else the kind

// ---- information the demon tells ----
int32_t pickInfoMessage(int32_t infotype);                 // nbGetInfoMsg
bool infoAvailable(int32_t message);                       // nbCheckSelectMesJoukenAri

// ---- answers ----
int32_t refuseMotion(TalkState& n, Formation& form);       // nbSetNegoNoMotion: shakes its head
int32_t agreeMotion(TalkState& n, Formation& form);        // nbSetNegoYesMotion: nods
int32_t fatedPair(const TalkState& n);                     // nbGetInnenNegoID: the pair's entry, -1 none

} // namespace nocturne::nb
