// The battle's presentation queue (original units: nbKoukaProcess,
// nbMakePacket). An action is shown as a list of "kouka" (effect) packets,
// each starting at a frame of the action's timeline: motions, moves,
// colours, damage numbers, sounds, fades. The builders here only queue
// packets; the kouka process plays them (kouka_process.hpp).
//
// Records are in their PS2 layout; names are the HD remaster's. Builder
// names without an HD counterpart are descriptive and marked so.
#pragma once

#include <cstddef>
#include <cstdint>

#include "nocturne/battle/process.hpp"
#include "nocturne/ee/float.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

// nbKoukaData_t: a packet parameter, one word read as bytes, halves, an
// int, a float or a pointer.
struct PacketData {
    uint32_t raw;
    void setInt(int32_t value) { raw = static_cast<uint32_t>(value); }
    void setFloat(ee::Float value) { raw = value.bits(); }
    void setHalves(int16_t low, int16_t high)
    {
        raw = static_cast<uint16_t>(low) | static_cast<uint32_t>(static_cast<uint16_t>(high)) << 16;
    }
    int32_t i() const { return static_cast<int32_t>(raw); }
};

// nbKoukaPacket_t (0x40 bytes, from the pool)
struct EffectPacket {
    int16_t startframe;
    int16_t framelength;
    int8_t type;                 // KoukaType
    uint8_t flag;
    uint16_t time;
    int32_t uniqueid;            // the action it belongs to
    Ptr32<EffectPacket> next, prev;
    Ptr32<Formation> form;
    Ptr32<UnitWork> unit;
    Ptr32<Party> party;
    int32_t partyno;
    uint32_t cuteff;             // effBTLCutHandle_t
    PacketData data1, data2;
    Vec4 v;
};
static_assert(sizeof(EffectPacket) == 0x40 && offsetof(EffectPacket, form) == 0x14 && offsetof(EffectPacket, v) == 0x30);

// nbKoukaProcessData_t
struct EffectQueue {
    Ptr32<MainProcessData> data;
    int32_t packetcnt;
    Ptr32<EffectPacket> first, last;
};

// The packet types, by what plays them.
enum PacketType : int8_t {
    kSkillEffect = 0x00, kTargetMove = 0x01, kHomeMove = 0x02, kRot = 0x03, kHomeRot = 0x04,
    kUnitCol = 0x05, kUnitHomeCol = 0x06, kUnitA = 0x07, kUnitHomeA = 0x08, kDamageMotion = 0x09, kAilmentDamageMotion = 0x0a,
    kReturn = 0x0b, kSummon = 0x0c, kDodge = 0x0d, kSkillColorOff = 0x0e, kHitEff = 0x0f, kNumberEff = 0x10,
    kHpMp = 0x11, kPress = 0x12, kAilment = 0x13, kAilmentMotionCure = 0x14, kSkillEffect2 = 0x15, kWordEff = 0x16,
    kAilmentEff = 0x17, kAilmentCureEff = 0x18, kSe = 0x19, kSkillEffect1 = 0x1a, kMotion = 0x1b, kSe2 = 0x1c,
    kSe3 = 0x1d, kHitStop = 0x1e, kNewPress = 0x1f, kMotionStop = 0x20, kMotionStopClear = 0x21,
    kAnalyze = 0x22, kStatusMessage = 0x23, kDeadPcm = 0x24, kAilmentMotion = 0x25, kFormOnOff = 0x26,
    kOngyokiClone = 0x27, kOngyokiClone2 = 0x28, kOngyokiOut = 0x29, kOngyokiOut2 = 0x2a, // Ongyo-Ki's clones
    kSkillEffect3 = 0x2b,   // tentative name: a skill effect that also owns a battle effect (data1)
    kFormFlagOnOff = 0x2c, kFly = 0x2d, kDeadEvent = 0x2e, kFadeOut = 0x2f, kFadeIn = 0x30, kSkillName = 0x31,
    kBuff = 0x32, kFlareCharge = 0x33, kPadShock = 0x34, kLightDamageMotion = 0x35, kSkillColor = 0x36,
    kSkillMotion = 0x37, kPanelStockFadeOut = 0x38, kPanelStockEnd = 0x39, kPassiveEffectEnd = 0x3a,
};

// ---- the queue ----
EffectQueue& effectQueue();
int32_t countActionPackets(int32_t uniqueid);
int32_t countPacketsOfType(int8_t type);
void linkPacket(EffectQueue& k, EffectPacket& p);
void unlinkPacket(EffectQueue& k, EffectPacket& p);
EffectPacket& addPacket(EffectQueue& k, int32_t startframe, int32_t framelength, int32_t uniqueid);
void deletePacketFrom(EffectQueue& k, EffectPacket& p);
void deletePacket(EffectPacket& p);
void deleteActionPackets(int32_t uniqueid);
void deletePacketsOfType(int32_t type);
void deleteNumberWordPackets(const Formation* form);
void setPacketTypeFlag(int32_t type, uint32_t flg, int32_t sw);
bool soundQueued(int32_t start, int32_t se, int32_t frame);

// ---- one packet each (startframe, uniqueid first) ----
EffectPacket& addSkillEffectPacket(int32_t startframe, int32_t framelength, int32_t uniqueid, uint32_t cuteff);
EffectPacket& addSkillEffectPacket2(int32_t startframe, int32_t framelength, int32_t uniqueid, uint32_t hbtl,
                                          int16_t cutno, Formation* form, int16_t j);
EffectPacket& addSkillEffectPacket1(int32_t startframe, int32_t framelength, int32_t uniqueid, uint32_t cuteff);
EffectPacket& addPassiveEffectEndPacket(int32_t startframe, int32_t uniqueid);
EffectPacket& addMoveToTargetPacket(int32_t startframe, int32_t uniqueid, int32_t partyno, const Vec4& pos, ee::Float speed);
EffectPacket& addMoveHomePacket(int32_t startframe, int32_t uniqueid, int32_t partyno, ee::Float speed);
EffectPacket& addTurnPacket(int32_t startframe, int32_t uniqueid, int32_t partyno, const Vec4& v, int32_t speed);
EffectPacket& addTurnHomePacket(int32_t startframe, int32_t uniqueid, int32_t partyno, int32_t speed);
EffectPacket& addUnitColorPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t col, int32_t frame);
EffectPacket& addUnitColorHomePacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t frame);
EffectPacket& addUnitAlphaPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t a, int32_t frame);
EffectPacket& addUnitAlphaHomePacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t frame);
EffectPacket& addDodgePacket(int32_t startframe, int32_t uniqueid, Formation& form);
EffectPacket& addMotionStopPacket(int32_t startframe, int32_t uniqueid, Formation* form);
EffectPacket& addMotionStopClearPacket(int32_t startframe, int32_t uniqueid, Formation* form);
EffectPacket& addMotionPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t motion);
EffectPacket& addSkillMotionPacket(int32_t startframe, int32_t uniqueid, Formation* form, int16_t motion,
                                         int16_t endtype, ee::Float ritu);
EffectPacket& addDamageMotionPacket(int32_t startframe, int32_t uniqueid, Formation* form, ee::Float range, int32_t week);
EffectPacket& addLightDamageMotionPacket(int32_t startframe, int32_t uniqueid, Formation* form, ee::Float range);
EffectPacket& addAilmentDamageMotionPacket(int32_t startframe, int32_t uniqueid, Formation* form, ee::Float range,
                                       uint32_t badstat);
EffectPacket& addAilmentMotionPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t badstat);
EffectPacket& addReturnPacket(int32_t startframe, int32_t uniqueid, Party* party, int32_t dead);
EffectPacket& addSummonPacket(int32_t startframe, int32_t uniqueid, int16_t side, int16_t stockno, int16_t formindex);
EffectPacket& addSkillColorPacket(int32_t startframe, int32_t uniqueid, int32_t col, int32_t frame);
EffectPacket& addSkillColorOffPacket(int32_t startframe, int32_t uniqueid);
EffectPacket& addAilmentCureEffectPacket(int32_t startframe, int32_t uniqueid, Formation* form);
EffectPacket& addAilmentEffectPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t bad);
// nbAddHitEffKoukaPacket (0x262480): a hit's effect on `form` (kinds below),
// as long as the effect plays, with its sound; none on an empty slot.
EffectPacket* addHitEffectPacket(int32_t startframe, int32_t uniqueid, Formation& form, uint32_t kind);
void addNumberPacket(int32_t startframe, int32_t frame, int32_t uniqueid, Formation* form, int32_t n, int32_t n2,
                            int32_t type);
void addWordPacket(int32_t startframe, int32_t frame, int32_t uniqueid, Formation* form, int32_t type);
EffectPacket& addHpMpPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t n, int32_t type);
EffectPacket& addPressPacket(int32_t startframe, int32_t uniqueid, ee::Float press);
EffectPacket& addPressResultPacket(int32_t startframe, int32_t uniqueid, int16_t press_p, int16_t press_ten);
EffectPacket& addAilmentPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t badstat, int32_t sw);
EffectPacket& addAilmentMotionCurePacket(int32_t startframe, int32_t uniqueid, Formation* form);
EffectPacket* addDeathVoicePacket(int32_t startframe, int32_t uniqueid, Formation& form);
EffectPacket* addSoundPacket(int32_t startframe, int32_t uniqueid, uint32_t se);
EffectPacket* addSoundPacket2(int32_t startframe, int32_t uniqueid, uint32_t se);
EffectPacket* addSoundPacket3(int32_t startframe, int32_t uniqueid, uint32_t se);
EffectPacket& addHitStopPacket(int32_t startframe, int32_t uniqueid);
EffectPacket& addAnalyzePacket(int32_t startframe, int32_t uniqueid, Formation* form);
EffectPacket& addStatusMessagePacket(int32_t startframe, int32_t uniqueid, int16_t no, int16_t var_id, int32_t var_ind);
EffectPacket& addSkillNamePacket(int32_t startframe, int32_t uniqueid, int32_t id);
// Ongyo-Ki: splitting into clones and leaving the field (the effect's
// handle in data1, the effect's length as the packet's).
EffectPacket& addOngyokiClonePacket(int32_t startframe, int32_t uniqueid, Formation* sform, Formation* eform);
EffectPacket& addOngyokiClonePacket2(int32_t startframe, int32_t uniqueid, Formation* sform, Formation* form1,
                                    Formation* form2, Formation* form3);
EffectPacket& addOngyokiOutPacket(int32_t startframe, int32_t uniqueid, Formation* form);
EffectPacket& addOngyokiOutPacket2(int32_t startframe, int32_t uniqueid, Formation* form);
EffectPacket& addFormationShowPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t sw);
EffectPacket& addFormationFlagPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t sw, uint32_t flag);
EffectPacket& addFlyPacket(int32_t startframe, int32_t uniqueid, Formation* form);
EffectPacket& addDeathEventPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t eventno);
EffectPacket& addFadeOutPacket(int32_t startframe, int32_t uniqueid, int32_t length, int32_t coltype);
EffectPacket& addFadeInPacket(int32_t startframe, int32_t uniqueid, int32_t length, int32_t coltype);
EffectPacket& addBuffPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t hojotype, int32_t hojopoint);
EffectPacket& addFlareChargePacket(int32_t startframe, int32_t uniqueid, int32_t point);
EffectPacket& addPadShockPacket(int32_t startframe, int32_t uniqueid, int16_t mode, int16_t pow, int16_t time);
EffectPacket& addStockPanelFadeOutPacket(int32_t startframe, int32_t uniqueid);
EffectPacket& addStockPanelEndPacket(int32_t startframe, int32_t uniqueid);

// ---- packets for a whole event ----
int32_t makeSummonPackets(int32_t startframe, int32_t uniqueid, int16_t side, int16_t stockno, int16_t formindex);
int32_t makeReturnPackets(int32_t startframe, int32_t uniqueid, Party& party);
int32_t makeFadeInPackets(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t col, int32_t delay,
                               int32_t aframe, int32_t colframe);
int32_t makeFadeOutPackets(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t col, int32_t delay,
                                int32_t colframe, int32_t aframe);
int32_t makeDeathPackets(int32_t startframe, int32_t uniqueid, Formation& form, int32_t deadchk);
// nbMakeDeadVisualPacket (0x263918): how a unit dies (deadtype; 2 for a unit
// whose death runs a script or event), its cry if `deadpcm`, and the pad's
// shock for the party's (stronger for the Demi-fiend). Returns 1.
int32_t makeDeathVisualPackets(int32_t startframe, int32_t uniqueid, Formation& form, int32_t deadtype, int32_t deadpcm);
// nbMakeDamagePacket (0x263C00): a hit's death, ailment or reaction and
// effect on a unit's slot, then its HP and MP loss (negative: none), shown as
// numbers and words `animeoff` frames later if `numbers`. Returns 1.
int32_t makeDamagePackets(int32_t startframe, int32_t uniqueid, Formation& form, int32_t type, int32_t hp, int32_t mp,
                          uint32_t bad, bool hiteff, bool dead, int32_t deadtype, bool numbers, int32_t animeoff);
// nbMakeKaifukuPacket (0x264010): a heal's effect (type 1) or Drain Attack's
// glow (type 3) on a unit's slot, then its HP and MP gain (negative: none)
// and, if `cures`, its ailment's cure. Returns 1.
int32_t makeHealPackets(int32_t startframe, int32_t uniqueid, Formation& form, int32_t type, int32_t hp, int32_t mp,
                        bool cures);
int32_t makePressPackets(int32_t startframe, int32_t uniqueid, ee::Float press);
// `callerSkill`: what a version may read of its caller (Hardtype: the skill
// SetAction_SKILL leaves in s6; the other callers never leave 0xFF there).
int32_t makePressResultPackets(int32_t startframe, int32_t uniqueid, int32_t ptype, int32_t callerSkill = 0);
// [version] A result type's press changes of the version's own (true: dFull
// and dHalf set; it may also change ptype).
bool versionPressResult(int32_t& ptype, int32_t callerSkill, int32_t& dFull, int32_t& dHalf);
int32_t makeFlyAilmentPackets(int32_t startframe, int32_t uniqueid, Formation* form);
int32_t makeAilmentPackets(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t bad);
int32_t makeAilmentCurePackets(int32_t startframe, int32_t uniqueid, Formation& form);
uint32_t curedAilment(int32_t formindex, uint32_t bad);   // [version] ... the ailment it takes as cured

} // namespace nocturne::nb
