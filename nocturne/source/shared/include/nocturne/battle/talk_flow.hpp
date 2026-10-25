// The talks' steps (original units: the NbNegoFlow* flows, one per group of
// steps). A step's ID is its group << 16 | its number; each group's flow
// function runs the step by its number, with the step's phase counting up
// on each call (TalkState::talkPhase). A step queues its possible next steps
// (addCandidate; the first is taken unless it sets nextTalkId), may show a
// message (showTalkMessage) or wait (waitframe), and returns 0, or a nonzero
// result that ends the talk (docs/talks.md).
#pragma once

#include <cstdint>

#include "nocturne/address.hpp"
#include "nocturne/battle/talk.hpp"

namespace nocturne::nb {

using TalkStep = int32_t (*)(TalkState& n);

// The talk skills (the table at 0x3E1338, by skill - 0x180; 0x68 bytes).
// A rule holds when the talker and the demon meet its two conditions
// (pairAffinity: the first of the talker toward the demon, the second the
// other way round); then the demon is well disposed (good) or badly (bad).
struct TalkSkillRule {        // datNegoAisyo_s
    uint32_t mine, theirs;   // ChkAisyo conditions; 0 and 0: no rule (HD: from, to)
    int32_t message;         // the affinity table's message (HD: mes)
};
struct TalkSkill {           // datNegoSkill_t
    int32_t kind;            // what the demon is asked for (InitNegoProcessData) (HD: type)
    uint8_t weights[4];      // the bargaining's outcomes (6_24): a deal, more talk, a question, refusal (HD: rate)
    TalkSkillRule good[4];   // (HD: killeraisyo)
    TalkSkillRule bad[4];    // (HD: ngaisyo)
};
static_assert(sizeof(TalkSkill) == 0x68);
inline constexpr uint32_t kTalkSkillTable = addr(0x003e1338);

// ChkAisyo: does `a` meet condition `jo` toward `b`? The condition's bits
// (all must hold): 2..0x20 a's speech traits (the Demi-fiend's: 0x14),
// 0x40 a at least 10 levels above b, 0x80 at least 10 below, 0x100 the same
// race (neither the Demi-fiend), 0x200 a is a Valkyrie, 0x400 Kikuri-Hime.
// Three values instead: 0x80000000 a new Kagutsuchi and b no Tyrant,
// 0x80000001 a at least 10 levels below b seven times in ten, 0x80000002
// b's speech trait 2 (only when `sw` is 0).
bool checkAffinity(const UnitWork& a, const UnitWork& b, uint32_t jo, int32_t sw);
// nbChkNegoAisyo: the talker and the demon, each way.
bool pairAffinity(const TalkState& n, uint32_t mine, uint32_t theirs, int32_t sw);
// nbChkNegoAisyo2: the same for any two.
bool pairAffinity(const UnitWork& s, const UnitWork& d, uint32_t mine, uint32_t theirs, int32_t sw);

// The questions' tables (groups 2 and 7), by the demon's speech style.
// [speech style][7] the questions of its own set: the full moon's two,
// then the other five. The first answer pleases it with the chance by how
// the player's side compares, the second answer otherwise. (Every entry in
// the game's table is {0, 70, 30}, and no unit has stat 1: the first answer
// pleases seven times in ten.)
struct OwnQuestion {
    int16_t judge;    // 0: by stat 1 (Param::Unused1), 1: by level; else even odds
    uint8_t chanceAhead, chanceBehind;   // percent
};
inline constexpr uint32_t kOwnQuestionAnswers = addr(0x003e2538);
// [speech style][36] where an answer to a question of a kind moves the
// player: the full moon's [kind % 3][answer 0..2], then the others'
// [kind % 3][question 0..1][answer 0..2] (kinds 3, 1, 2 in that order).
struct QuestionReason {
    int8_t reason;    // datAddKotowariPoint's
    uint8_t unused;
};
inline constexpr uint32_t kQuestionReasons = addr(0x003e28a0);

// The demons a full Kagutsuchi doesn't stir (the steps of groups 1, 2 and
// 16 single them out; a list in each, the same).
bool moonproof(uint16_t devil);
bool deathPact(const TalkState& n);   // CheckSkillShinoKeiyaku: a Death Pact, the talker standing

// Runs the talk's current step: its group's flow (the original's table at
// 0x4EF468 for any other group: none in the game, the tests' stand-in).
int32_t runTalkStep(TalkState& n);
// [version] Flow1_10: a battle whose demons won't talk, as with bosses
//.
bool battleRefusesTalk(const MainProcessData& data);

// ---- group 1: the opening (NbNegoFlowOne) ----
int32_t openingFlow(TalkState& n);             // nbNegoFlowOne
extern const TalkStep kOpeningSteps[40];

// ---- group 2: a talk under a full Kagutsuchi (NbNegoFlowFullMoon) ----
int32_t fullMoonFlow(TalkState& n);            // nbNegoFlowFullMoon
extern const TalkStep kFullMoonSteps[17];

// ---- group 4: the demon meets its own kind (NbNegoFlowDouchara) ----
int32_t kinFlow(TalkState& n);                 // nbNegoFlowDouchara
extern const TalkStep kKinSteps[14];

// ---- group 5: a fated pair meets (NbNegoFlowInnen) ----
int32_t fatedFlow(TalkState& n);               // nbNegoFlowInnen
extern const TalkStep kFatedSteps[22];

// ---- group 6: the bargaining (NbNegoFlowTwo) ----
int32_t bargainFlow(TalkState& n);             // nbNegoFlowTwo
extern const TalkStep kBargainSteps[82];

// ---- group 7: a question (NbNegoFlowQuestion) ----
// Whoever starts it notes where to go on after: workid[4] when the demon is
// pleased with the answer, workid[5] when not.
int32_t questionFlow(TalkState& n);            // nbNegoFlowQuestion
extern const TalkStep kQuestionSteps[27];

// ---- group 8: NbNegoFlowFight ----
int32_t fightFlow(TalkState& n);               // nbNegoFlowFight
extern const TalkStep kFightSteps[20];

// ---- group 9: the deal is struck (NbNegoFlowOk) ----
// The demon agreed: it joins, or gives Macca, an item or information.
int32_t dealFlow(TalkState& n);                // nbNegoFlowOk: the step by its number
extern const TalkStep kDealSteps[23];          // by step number (none at 0, 8, 12)

// ---- group 10: no deal (NbNegoFlowNg) ----
int32_t noDealFlow(TalkState& n);              // nbNegoFlowNg
extern const TalkStep kNoDealSteps[34];

// ---- group 11: the demon drains the talker (NbNegoFlowDrain) ----
int32_t drainFlow(TalkState& n);               // nbNegoFlowDrain
extern const TalkStep kDrainSteps[10];

// ---- group 12: the last enemy speaks up (NbNegoFlowMukan) ----
int32_t speakUpFlow(TalkState& n);             // nbNegoFlowMukan
extern const TalkStep kSpeakUpSteps[50];

// ---- group 13: a demon that ambushed the party (NbNegoFlowSensei) ----
// It asks a question or demands an item.
int32_t ambushFlow(TalkState& n);              // nbNegoFlowSensei
extern const TalkStep kAmbushSteps[13];

// ---- group 15: the last enemy begs for its life (NbNegoFlowInoti) ----
int32_t mercyFlow(TalkState& n);               // nbNegoFlowInoti
extern const TalkStep kMercySteps[24];

// ---- the short groups (talk_minor.cpp) ----
int32_t stockFlow(TalkState& n);               // nbNegoFlowStock: group 3
extern const TalkStep kStockSteps[3];
int32_t askToJoinFlow(TalkState& n);           // nbNegoFlowBinjo: group 14, a demon asks to join
extern const TalkStep kAskToJoinSteps[3];
int32_t tauntFlow(TalkState& n);               // nbNegoFlowKoketa: group 16, a taunt after a failed escape
extern const TalkStep kTauntSteps[4];

} // namespace nocturne::nb
