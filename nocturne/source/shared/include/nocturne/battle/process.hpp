// Battle ("nb" = new battle) process state, PS2 layout.
//
// These structures are only partly identified. Named fields are either
// confirmed by native code in the rewritten functions or, where marked
// "tentative", placed by the HD remaster's field order (nbMainProcessData_t
// etc.), which keeps declaration order but not offsets.
#pragma once

#include <cstddef>
#include <cstdint>

#include "nocturne/data/records.hpp"
#include "nocturne/ee/float.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

// Formation indices: 0..3 are the player's active party, 4..13 the enemies.
inline constexpr int32_t kPlayerFormations = 4;
inline constexpr int32_t kFirstEnemyFormation = 4;
inline constexpr int32_t kFormationCount = 14;

struct Vec4 { ee::Float x, y, z, w; };

// nbFormation: a combatant's on-screen slot (model, position, effects).
struct Formation {
    Vec4 orgpos, orgrot, pos, rot, center;
    ee::Float r, h, cr;
    ee::Float scl;            // model scale; shrinks with HP (nbSetHpScale)
    ee::Float oneshotr, allshotr, movey, movez;
    int32_t type;
    uint32_t time;
    uint32_t stat;            // FormationStat bits
    uint32_t flag;
    uint32_t anime;
    uint32_t basic;           // dds3Basic_t*
    int32_t serial;
    uint32_t hunit;
    int16_t partyindex;
    int16_t formindex;
    uint32_t unknown_94;
    uint32_t ailmentEffect;   // the ailment's effect on the unit (effBTLPart; anime bit 0x100) (tentative)
    uint32_t homeColor;       // the unit's own colour and alpha, which the home colour packets restore (tentative)
    ee::Float motionSpeed;    // the motion's speed, restored after a hit stop (tentative)
    int16_t motionend;        // how the skill motion ends (nbGetMotionEndType): 2 fades the unit out,
                              // which UnitKyoseiDisp fades back in; 3 ...  (tentative name)
    int16_t motionenddata;    // its data (nbGetMotionEndData): the fade's start
    uint8_t unknown_a8[6];
    int16_t motiontype;       // the motion type the action plays (SetAction_READY)
    uint8_t unknown_b0[4];
    uint32_t pacRequest;      // a PAC file request the unit holds, freed when the battle ends (ClearStage) (tentative)
    uint8_t unknown_b8[4];
    // A dodge (type 2): how far it steps back and how fast (tentative names).
    ee::Float dodgeStep, dodgeSpeed, dodgeDistance, dodgeStartSpeed;
    uint8_t unknown_cc[0xf0 - 0xcc];
};
static_assert(sizeof(Formation) == 0xf0);
static_assert(offsetof(Formation, motionend) == 0xa4 && offsetof(Formation, motiontype) == 0xae);
static_assert(offsetof(Formation, scl) == 0x5c);
static_assert(offsetof(Formation, stat) == 0x78);
static_assert(offsetof(Formation, formindex) == 0x92);
static_assert(offsetof(Formation, ailmentEffect) == 0x98 && offsetof(Formation, motionSpeed) == 0xa0);
static_assert(offsetof(Formation, dodgeStep) == 0xbc && offsetof(Formation, dodgeStartSpeed) == 0xc8);

namespace FormationStat {
inline constexpr uint32_t Present     = 0x0001; // a combatant stands here
inline constexpr uint32_t Shadow      = 0x0002; // tentative: one of Ongyo-Ki's clones (SetOngShadowPacket)
inline constexpr uint32_t Selectable  = 0x0004; // a valid target for the current action
inline constexpr uint32_t Selected    = 0x0008; // chosen as a target
inline constexpr uint32_t CheckParty  = 0x0040; // check the party flags before targeting (tentative)
inline constexpr uint32_t PartySlot   = 0x0100; // slots 0..3 (initFormation)
inline constexpr uint32_t EnemySlot   = 0x0200; // slots 4..13
inline constexpr uint32_t ExtraSlot   = 0x0400; // slots 14 and 15
inline constexpr uint32_t SummonSlot  = 0x0800; // an empty slot an ally may be called into
inline constexpr uint32_t Unknown1000 = 0x1000; // nbGetKoukaType result 11
inline constexpr uint32_t Unknown2000 = 0x2000; // makes crits near-certain on Hard
} // namespace FormationStat

// nbParty: per-combatant battle bookkeeping (buffs, affinities).
struct Party {
    int16_t flag;             // PartyFlag bits
    int16_t formindex;
    int16_t statindex;
    uint16_t partyindex;
    int16_t count[20];        // buff/debuff ("hojo") counters by type
    uint32_t affinities[16];  // current packed affinity per Attribute (HD: aisyo)
    uint16_t buffSkills[8];   // (HD: hojoskill)
};
static_assert(sizeof(Party) == 128);
static_assert(offsetof(Party, affinities) == 0x30);

namespace PartyFlag {
inline constexpr uint16_t Active     = 0x001;
inline constexpr uint16_t EnemySide  = 0x002;
inline constexpr uint16_t Inactive   = 0x004; // tentative
inline constexpr uint16_t Left       = 0x020; // the unit has left the battle (nbMakeReturnPacket)
inline constexpr uint16_t AlwaysCrit = 0x100; // tentative: forces critical hits
inline constexpr uint16_t EndureFired = 0x200; // Endure / Never Yield saved this unit
inline constexpr uint16_t EndureSpent = 0x400; // ... and cannot again this battle
inline constexpr uint16_t ThrewMacca  = 0x800; // an ailment made the unit throw Macca (BadMaka)
} // namespace PartyFlag

// An action waiting on the battle's stack (nbPushAction): what kind (see
// battle/action_events.cpp: 4 a counter, 5 a death script, ...), who acts,
// on whom, and a value of its own.
struct QueuedAction {
    int32_t type;
    int32_t from, to;   // party indexes
    int32_t data;
};
static_assert(sizeof(QueuedAction) == 16);

// nbMainProcessData: the battle as a whole.
struct MainProcessData {
    Ptr32<Formation> form;    // [kFormationCount] (32 allocated)
    uint32_t formHandle;      // its memory handle
    Ptr32<UnitWork> enemyunit;   // [10] the enemies' units (nbAppendEnemyDevilWork)
    uint32_t enemyunitHandle;
    Ptr32<Party> party;       // [kFormationCount]
    uint32_t partyHandle;
    int16_t playerpcnt;       // tentative
    int16_t enemypcnt;        // tentative: enemy combatant count
    int16_t activeunit;
    uint16_t unknown_1e;
    uint32_t sound, sound_mem;   // tentative
    // Where this encounter came from: encountPack(encpackno)
    //   .enctable[packno].entries[packindex].encountid == encno
    int32_t encpackno;
    int32_t packno;
    int32_t packindex;
    int32_t encno;            // index into the Encount table
    int32_t formationtype;
    uint32_t actionstack;     // queued actions: {type, from, to, data} words (nbPushAction)
    int32_t actionstackp;     // how many
    uint32_t endtype;         // how the battle ended (3 = escaped)
    int8_t order[12];         // tentative
    int8_t orderindex;
    uint8_t unknown_55;
    int16_t previndex;
    uint16_t prevcommand, prevcommind, prevflag, debug;
    uint32_t stat;            // BattleStat bits (legacy headers call this "flag")
    uint32_t flag;
    uint8_t turn;
    int8_t phase, nextphase;
    uint8_t esccnt;           // escape attempts so far; each one helps
    uint16_t phasetime;
    uint32_t battletime;
    ee::Float press3;
    int16_t press4_p;         // press turns: full icons left
    int16_t press4_ten;       // ... and blinking (half) ones
    // The battle's stage (nbInitMainProcess's arguments; the opening loads it).
    // HD order puts press4_hansya / press4_miss here.
    int16_t stageMajor, stageMinor;
    int16_t StageMajor, StageMinor;
    int32_t summonallowed;    // nonzero: enemies may call allies (tentative; HD order suggests nakamayobi)
    int32_t eventno;          // the event to run when the action ends: a death's (RunDeadEventKouka), a script's (BTL_EVENT), AI command 0xExxx with action 9
    int32_t eventrid;         // tentative (HD order)
    int16_t talkPlayerSlot, talkEnemySlot;    // tentative (HD order): the talks' two sides (HD: negopformindex, negoeformindex)
    int32_t talkResult;       // nonzero: an AI script started talks (CheckAction_AISCR) (HD: negoresult)
    uint8_t item[4];          // spoils so far
    uint8_t itemcnt[4];
    uint32_t macca;           // Macca earned (HD: maka)
    uint32_t exp;             // EXP earned
    uint32_t baselight, niidalight, gamecamera, niidacamera, eventcamera;   // tentative (HD order)
    // The battle's processes.
    uint32_t MainProcessID;   // the battle itself; AI scripts run as its children
    uint32_t BeforeProcessID, AfterProcessID, ResultProcessID, StageProcessID, UnitProcessID; // tentative (HD order) (HD: MaeProcessID, AtoProcessID)
    uint32_t ActionProcessID[4];   // a ring of action processes (battle/action.hpp)
    int32_t NowActionProcess;
    uint32_t CommandMenuProcessID, TargetCursorProcessID, EffectProcessID; // tentative (HD order) (HD: CommSelProcessID, TarSelProcessID)
    uint32_t EffectQueueProcessID; // the presentation queue's process (battle/kouka.hpp) (HD: KoukaProcessID)
    uint32_t TalkProcessID, CameraProcessID, DebugProcessID;   // tentative (HD order) (HD: NegoProcessID)
    uint32_t AiScriptProcessID;   // the AI or death script running, or 0
    uint32_t PanelProcessID, HelpProcessID, AutoCommProcessID, EncProcessID, EventProcessID;   // tentative (HD order)
    uint32_t PassiveEffect;                                  // tentative (HD order) (HD: HatudoEff)
    uint32_t hPnlTex1, hPnlTex2, hPnlTex3, hPnlTex4;         // tentative (HD order)
    int32_t statusMessageTable; // the status line's message table (nbDispJyokyoHelp) (HD: jyokyomsgid)
    int32_t miscmsgid;
    uint32_t flyh, flymem;    // tentative (HD order)
    // Counted for an event boss (tentative): the press turns, and whether
    // skills 0x107 / 0x113 were repelled (HD: rebe / anda "hansya", reflect).
    uint32_t d31_press_total, d31_repel107, d31_repel113;   // (HD: d31_rebehansya, d31_andahansya)
    int32_t piercedResistance;   // set when Pierce ignored Null/Drain (tentative name)
};
static_assert(offsetof(MainProcessData, party) == 0x10 && offsetof(MainProcessData, enemyunit) == 8);
static_assert(offsetof(MainProcessData, encpackno) == 0x28);
static_assert(offsetof(MainProcessData, encno) == 0x34);
static_assert(offsetof(MainProcessData, endtype) == 0x44);
static_assert(offsetof(MainProcessData, orderindex) == 0x54);
static_assert(offsetof(MainProcessData, stat) == 0x60);
static_assert(offsetof(MainProcessData, esccnt) == 0x6b);
static_assert(offsetof(MainProcessData, press4_p) == 0x78 && offsetof(MainProcessData, summonallowed) == 0x84);
static_assert(offsetof(MainProcessData, EffectQueueProcessID) == 0xf4);
static_assert(offsetof(MainProcessData, talkResult) == 0x94 && offsetof(MainProcessData, MainProcessID) == 0xbc);
static_assert(offsetof(MainProcessData, AiScriptProcessID) == 0x104);
static_assert(offsetof(MainProcessData, statusMessageTable) == 0x130);
static_assert(offsetof(MainProcessData, item) == 0x98);
static_assert(offsetof(MainProcessData, exp) == 0xa4);
static_assert(offsetof(MainProcessData, piercedResistance) == 0x14c);

namespace BattleStat {
inline constexpr uint32_t BossBattle          = 0x00000001; // tentative: Stinger ("DANTE SUTING BOSS NG") and the Melody instant kills fail
inline constexpr uint32_t EnemyTurn           = 0x00000008; // the enemies' turn (from the start when they go first)
inline constexpr uint32_t BackAttack          = 0x00000010;
inline constexpr uint32_t EnemiesFirst        = 0x00000080;
inline constexpr uint32_t Unknown400          = 0x00000400; // encounter 0xC7's (SetFlag): Ongyo-Ki's clones' battle (tentative)
inline constexpr uint32_t Unknown800          = 0x00000800; // the encounter's flag 8 (SetFlag)
inline constexpr uint32_t NoDebugDisplay      = 0x00200000; // tentative: the debug pad's displays off
inline constexpr uint32_t DebugMenu           = 0x01000000; // tentative: pad button 10 may open the debug menu
inline constexpr uint32_t KeepOrder           = 0x00040000; // tentative: a turn's press icons don't move the order on (nbSetChkTurnPhase)
inline constexpr uint32_t ForceEnemiesFirst   = 0x00008000; // tentative: CheckSenseiOrBackAttack makes the enemies go first
inline constexpr uint32_t DebugAlwaysHit      = 0x08000000; // debug event bit 0xC07
inline constexpr uint32_t DebugAlwaysRepel    = 0x40000000; // debug event bit 0xC0D
inline constexpr uint32_t ForceBackAttack     = 0x80000000; // tentative: ... and from behind
} // namespace BattleStat

// nbActionProcessData: one unit's action in progress. Also the enemy AI's
// working state (the ai* fields).
// nbTimeList_t: when a unit is next free and done during an action, and
// its HP as the action's packets will leave it.
struct TimeList {
    uint16_t lockframe;
    uint16_t endframe;
    uint16_t hp;
    uint16_t pad;
};

// (The PS2 record has no uniqueid: the action's own address identifies its
// kouka packets.)
struct ActionProcessData {
    Ptr32<MainProcessData> data;
    uint32_t stat;
    int8_t seq, nextseq;      // the action's state (ActionSeq)
    uint16_t seqtime;
    int32_t seqcnt;
    int32_t skilltime;
    ee::Float press;
    int32_t newpresstype;
    int16_t newpress_p, newpress_ten;
    int32_t newaddpresstype;
    Ptr32<Party> party;       // the acting unit's
    Ptr32<Formation> form;
    Ptr32<UnitWork> work;
    int32_t partyindex;
    int32_t type;
    int32_t target;
    uint32_t select;          // chosen targets, one bit per formation slot
    uint32_t timer;
    int32_t runerr;
    int32_t statusMessage, statusVarType, statusVarValue;   // (HD: jyokyomes, jyo_varid, jyo_varind)
    int32_t adata;
    int32_t autoskill;        // passive that fired (e.g. Might); tentative name
    int32_t allhpdamage, allmpdamage;
    int32_t massuruid;        // the skill item 1 rolled (nbGetItemSkillNo)
    int32_t talkType;         // how a talk goes (6: started by an ailment, BadNego) (HD: negotype)
    int32_t motion;           // the motion the action plays (nbGetMotionNo), -1 none
    int32_t motionSound;      // its sound bank is being loaded (nbMemoryLoadMotionSe) (HD: motse)
    uint32_t hEffBTL;         // the skill's effect (effBTL_t)
    uint32_t hBed;            // the skill's effect file (.BED) being loaded
    uint32_t hSkillSe;        // its sound file (/sound/MIDIxxxx.SMG) being loaded
    uint32_t hSkillMem;       // ... and its memory
    uint32_t skillmidi;       // the sound bank's ID
    TimeList timelist[32];    // by formation index
    uint32_t packettime;
    int32_t hitstopframe;
    uint32_t aiselect;        // targets the AI conditions picked, one bit per party index
    int32_t aijokentbl;       // which AI check is being evaluated
    int8_t aichktbl[5];       // actions already tried this turn
    uint8_t unknown_19d[3];
    uint32_t aisummonid;      // devil to call, or the skill's parameter
};
static_assert(offsetof(ActionProcessData, party) == 0x24);
static_assert(offsetof(ActionProcessData, select) == 0x3c);
static_assert(offsetof(ActionProcessData, autoskill) == 0x58);
static_assert(offsetof(ActionProcessData, aiselect) == 0x190);
static_assert(offsetof(ActionProcessData, seq) == 0x08 && offsetof(ActionProcessData, timelist) == 0x88);
static_assert(offsetof(ActionProcessData, aisummonid) == 0x1a0);
static_assert(offsetof(ActionProcessData, talkType) == 0x68);

// nbTarSelProcessData: the target-selection process (cursor and lists).
struct TargetCursor {
    Ptr32<MainProcessData> data;
    Ptr32<ActionProcessData> act;
    uint8_t stat;
    int8_t ctype;
    uint8_t crule, carea, nowcarea;
    int8_t nowno, nowform;
    uint8_t unknown_0f;
    int16_t partyindex;
    int8_t friendcnt;         // selectable slots on the actor's side ...
    int8_t enemycnt;          // ... and the other side
    int8_t friendno[12];
    int8_t enemyno[12];       // enemies sorted by screen position (Formation::orgpos.x)
    int32_t nameDelay;        // frames before the target's name shows (HD: jyokyotime)
    int32_t time;             // the cursor's animation (0..29)
    int32_t alpha_a, alpha_b; // the cursor's two rings
    ee::Float scale_a, scale_b;
};
static_assert(offsetof(TargetCursor, friendcnt) == 0x12);
static_assert(offsetof(TargetCursor, nameDelay) == 0x2c && sizeof(TargetCursor) == 0x44);
static_assert(offsetof(TargetCursor, enemyno) == 0x20);

} // namespace nocturne::nb
