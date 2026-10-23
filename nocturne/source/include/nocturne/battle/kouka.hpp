// The battle's presentation queue (original units: nbKoukaProcess,
// nbMakePacket). An action is shown as a list of "kouka" (effect) packets,
// each starting at a frame of the action's timeline: motions, moves,
// colours, damage numbers, sounds, fades. The builders here only queue
// packets; the kouka process plays them (not rewritten yet).
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
struct KoukaData {
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
struct KoukaPacket {
    int16_t startframe;
    int16_t framelength;
    int8_t type;                 // KoukaType
    uint8_t flag;
    uint16_t time;
    int32_t uniqueid;            // the action it belongs to
    Ptr32<KoukaPacket> next, prev;
    Ptr32<Formation> form;
    Ptr32<UnitWork> unit;
    Ptr32<Party> party;
    int32_t partyno;
    uint32_t cuteff;             // effBTLCutHandle_t
    KoukaData data1, data2;
    Vec4 v;
};
static_assert(sizeof(KoukaPacket) == 0x40 && offsetof(KoukaPacket, form) == 0x14 && offsetof(KoukaPacket, v) == 0x30);

// nbKoukaProcessData_t
struct KoukaProcessData {
    Ptr32<MainProcessData> data;
    int32_t packetcnt;
    Ptr32<KoukaPacket> first, last;
};

// The packet types, by what plays them.
enum KoukaType : int8_t {
    kSkillEffect = 0x00, kTargetMove = 0x01, kHomeMove = 0x02, kRot = 0x03, kHomeRot = 0x04,
    kUnitCol = 0x05, kUnitHomeCol = 0x06, kUnitA = 0x07, kUnitHomeA = 0x08, kDmgMot = 0x09, kBadDmgMot = 0x0a,
    kReturn = 0x0b, kSummon = 0x0c, kSake = 0x0d, kSkillColorOff = 0x0e, kHitEff = 0x0f, kNumEff = 0x10,
    kHpMp = 0x11, kPress = 0x12, kBadStat = 0x13, kBadMotKaifuku = 0x14, kSkillEffect2 = 0x15, kMojiEff = 0x16,
    kBadEff = 0x17, kBadEffKaifuku = 0x18, kSe = 0x19, kSkillEffect1 = 0x1a, kMotion = 0x1b, kSe2 = 0x1c,
    kSe3 = 0x1d, kHitStop = 0x1e, kNewPress = 0x1f, kMotionStop = 0x20, kMotionStopClear = 0x21,
    kAnalyze = 0x22, kJyokyoHelp = 0x23, kDeadPcm = 0x24, kBadMot = 0x25, kFormOnOff = 0x26,
    kFormFlagOnOff = 0x2c, kFly = 0x2d, kDeadEvent = 0x2e, kFadeOut = 0x2f, kFadeIn = 0x30, kSkillName = 0x31,
    kHojo = 0x32, kFlareCharge = 0x33, kPadShock = 0x34, kEasyDmgMot = 0x35, kSkillColor = 0x36,
    kSkillMotion = 0x37, kPanelStockFadeOut = 0x38, kPanelStockEnd = 0x39, kHatudoEffectEnd = 0x3a,
};

// ---- the queue ----
KoukaProcessData& nbGetKoukaProcessData();
int32_t nbGetUniqueIdKoukaPacketCnt(int32_t uniqueid);
int32_t nbGetKoukaPacketTypeCnt(int8_t type);
void LinkKoukaPacket(KoukaProcessData& k, KoukaPacket& p);
void UnlinkKoukaPacket(KoukaProcessData& k, KoukaPacket& p);
KoukaPacket& nbAddKoukaPacket(KoukaProcessData& k, int32_t startframe, int32_t framelength, int32_t uniqueid);
void nbOnOffKoukaPacketFlag(int32_t type, uint32_t flg, int32_t sw);
bool nbCheckSePacket(int32_t start, int32_t se, int32_t frame);

// ---- one packet each (startframe, uniqueid first) ----
KoukaPacket& nbAddSkillEffectKoukaPacket(int32_t startframe, int32_t framelength, int32_t uniqueid, uint32_t cuteff);
KoukaPacket& nbAddSkillEffectKoukaPacket2(int32_t startframe, int32_t framelength, int32_t uniqueid, uint32_t hbtl,
                                          int16_t cutno, Formation* form, int16_t j);
KoukaPacket& nbAddSkillEffectKoukaPacket1(int32_t startframe, int32_t framelength, int32_t uniqueid, uint32_t cuteff);
KoukaPacket& nbAddHatudoEffectEndPacket(int32_t startframe, int32_t uniqueid);
KoukaPacket& nbAddTargetMoveKoukaPacket(int32_t startframe, int32_t uniqueid, int32_t partyno, const Vec4& pos, ee::Float speed);
KoukaPacket& nbAddHomeMoveKoukaPacket(int32_t startframe, int32_t uniqueid, int32_t partyno, ee::Float speed);
KoukaPacket& nbAddRotKoukaPacket(int32_t startframe, int32_t uniqueid, int32_t partyno, const Vec4& v, int32_t speed);
KoukaPacket& nbAddHomeRotKoukaPacket(int32_t startframe, int32_t uniqueid, int32_t partyno, int32_t speed);
KoukaPacket& nbAddUnitColKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t col, int32_t frame);
KoukaPacket& nbAddUnitHomeColKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t frame);
KoukaPacket& nbAddUnitAKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t a, int32_t frame);
KoukaPacket& nbAddUnitHomeAKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t frame);
KoukaPacket& nbAddSakeKoukaPacket(int32_t startframe, int32_t uniqueid, Formation& form);
KoukaPacket& nbAddMotionStopPacket(int32_t startframe, int32_t uniqueid, Formation* form);
KoukaPacket& nbAddMotionStopClearPacket(int32_t startframe, int32_t uniqueid, Formation* form);
KoukaPacket& nbAddMotionKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t motion);
KoukaPacket& nbAddSkillMotionKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, int16_t motion,
                                         int16_t endtype, ee::Float ritu);
KoukaPacket& nbAddDmgMotKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, ee::Float range, int32_t week);
KoukaPacket& nbAddEasyDmgMotKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, ee::Float range);
KoukaPacket& nbAddBadDmgMotKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, ee::Float range,
                                       uint32_t badstat);
KoukaPacket& nbAddBadMotKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t badstat);
KoukaPacket& nbAddReturnKoukaPacket(int32_t startframe, int32_t uniqueid, Party* party, int32_t dead);
KoukaPacket& nbAddSummonKoukaPacket(int32_t startframe, int32_t uniqueid, int16_t side, int16_t stockno, int16_t formindex);
KoukaPacket& nbAddSkillColorPacket(int32_t startframe, int32_t uniqueid, int32_t col, int32_t frame);
KoukaPacket& nbAddSkillColorOffPacket(int32_t startframe, int32_t uniqueid);
KoukaPacket& nbAddBadEffKaifukuPacket(int32_t startframe, int32_t uniqueid, Formation* form);
KoukaPacket& nbAddBadEffKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t bad);
void nbAddNumEffKoukaPacket(int32_t startframe, int32_t frame, int32_t uniqueid, Formation* form, int32_t n, int32_t n2,
                            int32_t type);
void nbAddMojiEffKoukaPacket(int32_t startframe, int32_t frame, int32_t uniqueid, Formation* form, int32_t type);
KoukaPacket& nbAddHpMpKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t n, int32_t type);
KoukaPacket& nbAddPressPacket(int32_t startframe, int32_t uniqueid, ee::Float press);
KoukaPacket& nbAddNewPressPacket(int32_t startframe, int32_t uniqueid, int16_t press_p, int16_t press_ten);
KoukaPacket& nbAddBadStatKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t badstat, int32_t sw);
KoukaPacket& nbAddBadMotKaifukuPacket(int32_t startframe, int32_t uniqueid, Formation* form);
KoukaPacket* nbAddDeadPcmPacket(int32_t startframe, int32_t uniqueid, Formation& form);
KoukaPacket* nbAddSePacket(int32_t startframe, int32_t uniqueid, uint32_t se);
KoukaPacket* nbAddSePacket2(int32_t startframe, int32_t uniqueid, uint32_t se);
KoukaPacket* nbAddSePacket3(int32_t startframe, int32_t uniqueid, uint32_t se);
KoukaPacket& nbAddHitStopPacket(int32_t startframe, int32_t uniqueid);
KoukaPacket& nbAddAnalyzePacket(int32_t startframe, int32_t uniqueid, Formation* form);
KoukaPacket& nbAddJyokyoHelpPacket(int32_t startframe, int32_t uniqueid, int16_t no, int16_t var_id, int32_t var_ind);
KoukaPacket& nbAddSkillNamePacket(int32_t startframe, int32_t uniqueid, int32_t id);
KoukaPacket& nbAddFormOnOffPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t sw);
KoukaPacket& nbAddFormFlagOnOffPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t sw, uint32_t flag);
KoukaPacket& nbAddFlyKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form);
KoukaPacket& nbAddDeadEventKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t eventno);
KoukaPacket& nbAddFadeOutKoukaPacket(int32_t startframe, int32_t uniqueid, int32_t length, int32_t coltype);
KoukaPacket& nbAddFadeInKoukaPacket(int32_t startframe, int32_t uniqueid, int32_t length, int32_t coltype);
KoukaPacket& nbAddHojoKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t hojotype, int32_t hojopoint);
KoukaPacket& nbAddFlareChargePacket(int32_t startframe, int32_t uniqueid, int32_t point);
KoukaPacket& nbAddPadShockPacket(int32_t startframe, int32_t uniqueid, int16_t mode, int16_t pow, int16_t time);
KoukaPacket& nbAddPanelStockFadeOutPacket(int32_t startframe, int32_t uniqueid);
KoukaPacket& nbAddPanelStockEndPacket(int32_t startframe, int32_t uniqueid);

// ---- packets for a whole event ----
int32_t nbMakeSummonPacket(int32_t startframe, int32_t uniqueid, int16_t side, int16_t stockno, int16_t formindex);
int32_t nbMakeReturnPacket(int32_t startframe, int32_t uniqueid, Party& party);
int32_t nbMakeUnitFadeInPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t col, int32_t delay,
                               int32_t aframe, int32_t colframe);
int32_t nbMakeUnitFadeOutPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t col, int32_t delay,
                                int32_t colframe, int32_t aframe);
int32_t nbMakeDeadPacket(int32_t startframe, int32_t uniqueid, Formation& form, int32_t deadchk);
int32_t nbMakePressPacket(int32_t startframe, int32_t uniqueid, ee::Float press);
int32_t nbMakeNewPressPacket(int32_t startframe, int32_t uniqueid, int32_t ptype);
int32_t nbMakeFlyBadPacket(int32_t startframe, int32_t uniqueid, Formation* form);
int32_t nbMakeBadDamagePacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t bad);
int32_t nbMakeBadKaifukuPacket(int32_t startframe, int32_t uniqueid, Formation& form);

} // namespace nocturne::nb
