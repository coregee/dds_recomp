// The battle's presentation queue (original units: nbKoukaProcess,
// nbMakePacket). Rewritten from the original instructions.
#include "nocturne/battle/kouka.hpp"

#include "nocturne/address.hpp"
#include "nocturne/battle/calc.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/event_process.hpp"
#include "nocturne/effect/boss.hpp"
#include "nocturne/effect/system.hpp"
#include "nocturne/external.hpp"
#include "nocturne/build.hpp"
#include "nocturne/guest.hpp"
#include "nocturne/hardtype.hpp"

namespace nocturne::nb {

namespace {

EffectPacket& addTo(int32_t startframe, int32_t framelength, int32_t uniqueid, PacketType type)
{
    EffectPacket& p = addPacket(effectQueue(), startframe, framelength, uniqueid);
    p.type = type;
    return p;
}

EffectPacket& add(int32_t startframe, int32_t uniqueid, PacketType type) { return addTo(startframe, 0, uniqueid, type); }

// A packet on a formation slot.
EffectPacket& addFor(int32_t startframe, int32_t uniqueid, Formation* form, PacketType type)
{
    EffectPacket& p = add(startframe, uniqueid, type);
    p.form.address = guest::addressOf(form);
    return p;
}

// The queue as the main process data names it (some functions reach it this way).
EffectQueue* queueOfMainProcess()
{
    const uint32_t process = GetMainProcessData()->EffectQueueProcessID;
    if (!process)
        return nullptr;
    return guest::table<EffectQueue>(dds3::GetProcessData(process));
}

// A damage number or word on the same unit ends where the new one starts.
void shortenEarlier(EffectQueue& k, PacketType type, int32_t startframe, int32_t uniqueid, Formation* form)
{
    for (EffectPacket* p = k.first.get(); p; p = p->next.get()) {
        if (p->type != type || p->uniqueid != uniqueid || p->form.address != guest::addressOf(form))
            continue;
        if (startframe < p->startframe + p->framelength) {
            const int32_t length = startframe - static_cast<uint16_t>(p->startframe);
            p->framelength = static_cast<int16_t>(length);
            if (static_cast<int16_t>(length) < 0)
                p->framelength = 0;
        }
    }
}

// A sound effect, unless the same one already starts within 5 frames before.
EffectPacket* addSound(int32_t startframe, int32_t uniqueid, uint32_t se, PacketType type)
{
    if (soundQueued(startframe, static_cast<int32_t>(se), 5))
        return nullptr;
    EffectPacket& p = add(startframe, uniqueid, type);
    p.data1.setInt(static_cast<int32_t>(se));
    return &p;
}

} // namespace

// ---- the queue -----------------------------------------------------------------------------

// nbGetKoukaProcessData @ 0x0025E8E0: the "nbKoukaProcess" process's data.
EffectQueue& effectQueue()
{
    return *guest::table<EffectQueue>(dds3::GetProcessData(dds3::SearchProcessName(addr(0x00544350))));
}

// nbGetUniqueIdKoukaPacketCnt @ 0x0025E928: packets of one action.
int32_t countActionPackets(int32_t uniqueid)
{
    int32_t count = 0;
    for (const EffectPacket* p = effectQueue().first.get(); p; p = p->next.get())
        if (p->uniqueid == uniqueid)
            ++count;
    return count;
}

// nbGetKoukaPacketTypeCnt @ 0x0025E978
int32_t countPacketsOfType(int8_t type)
{
    int32_t count = 0;
    for (const EffectPacket* p = effectQueue().first.get(); p; p = p->next.get())
        if (p->type == type)
            ++count;
    return count;
}

// LinkKoukaPacket @ 0x0025E9C8: at the end.
void linkPacket(EffectQueue& k, EffectPacket& p)
{
    const uint32_t self = guest::addressOf(&p);
    if (!k.first)
        k.first.address = self;
    if (!k.last) {
        k.last.address = self;
    } else {
        k.last->next.address = self;
        p.prev = k.last;
        k.last.address = self;
    }
    ++k.packetcnt;
}

// UnlinkKoukaPacket @ 0x0025EA00
void unlinkPacket(EffectQueue& k, EffectPacket& p)
{
    if (!p.prev)
        k.first = p.next;
    else
        p.prev->next = p.next;
    if (!p.next)
        k.last = p.prev;
    else
        p.next->prev = p.prev;
    --k.packetcnt;
}

// nbAddKoukaPacket @ 0x0025EA48: a cleared packet (its vector is left as
// the pool gave it) at the end of the queue.
EffectPacket& addPacket(EffectQueue& k, int32_t startframe, int32_t framelength, int32_t uniqueid)
{
    EffectPacket& p = *guest::table<EffectPacket>(mem::PoolAllocate(sizeof(EffectPacket)));
    p.startframe = static_cast<int16_t>(startframe);
    p.framelength = static_cast<int16_t>(framelength);
    p.uniqueid = uniqueid;
    p.partyno = -1;
    p.type = 0;
    p.flag = 0;
    p.time = 0;
    p.next.address = 0;
    p.prev.address = 0;
    p.form.address = 0;
    p.unit.address = 0;
    p.party.address = 0;
    p.cuteff = 0;
    p.data1.raw = 0;
    p.data2.raw = 0;
    linkPacket(k, p);
    return p;
}

// DelKoukaPacket @ 0x0025EAF0: a packet leaves the queue, freeing the
// effect it started (a skill's cut and, for 0x2B, its effect; a hit
// effect's part; Ongyo-Ki's clones).
void deletePacketFrom(EffectQueue& k, EffectPacket& p)
{
    switch (p.type) {
    case kSkillEffect:
    case kSkillEffect2:
    case kSkillEffect3:
        if (p.cuteff) {
            eff::BTLCutDelete(p.cuteff);
            p.cuteff = 0;
        }
        if (p.type == kSkillEffect3)
            eff::BTLDelete(p.data1.raw);
        break;
    case kSkillEffect1:
        if (p.cuteff) {
            eff::BTLSystemCutDelete(p.cuteff);
            p.cuteff = 0;
        }
        break;
    case kHitEff:
        if (p.data1.raw <= 10 && p.data1.raw != 3)   // (kind 3 has no part)
            eff::BTLPartDelete(p.data2.raw);
        break;
    case kOngyokiClone: eff::OngyokiCloneEffectDelete(p.data1.raw); break;
    case kOngyokiClone2: eff::OngyokiCloneEffect2Delete(p.data1.raw); break;
    case kOngyokiOut: eff::OngyokiEffectDelete(p.data1.raw); break;
    case kOngyokiOut2: eff::OngyokiEffect2Delete(p.data1.raw); break;
    default: break;
    }
    unlinkPacket(k, p);
    mem::PoolRelease(guest::addressOf(&p));
}

// nbDelKoukaPacket @ 0x0025EC28
void deletePacket(EffectPacket& p) { deletePacketFrom(effectQueue(), p); }

// 0x0025EC58 (no original name): every packet of an action.
void deleteActionPackets(int32_t uniqueid)
{
    EffectQueue* k = queueOfMainProcess();
    if (!k)
        return;
    for (EffectPacket* p = k->first.get(); p;) {
        EffectPacket* next = p->next.get();
        if (p->uniqueid == uniqueid)
            deletePacket(*p);
        p = next;
    }
}

// nbDelAllKoukaPacketType @ 0x0025ECC0: every packet of a type.
void deletePacketsOfType(int32_t type)
{
    EffectQueue* k = queueOfMainProcess();
    if (!k)
        return;
    for (EffectPacket* p = k->first.get(); p;) {
        EffectPacket* next = p->next.get();
        if (p->type == type)
            deletePacket(*p);
        p = next;
    }
}

// nbDelAllMojiNumEffectKoukaPacket @ 0x0025ED28: the numbers and words
// shown over one slot.
void deleteNumberWordPackets(const Formation* form)
{
    EffectQueue* k = queueOfMainProcess();
    if (!k)
        return;
    for (EffectPacket* p = k->first.get(); p;) {
        EffectPacket* next = p->next.get();
        if ((p->type == kNumberEff || p->type == kWordEff) && p->form.address == guest::addressOf(form))
            deletePacket(*p);
        p = next;
    }
}

// nbOnOffKoukaPacketFlag @ 0x0025EE78: flag bits of every packet of a type.
void setPacketTypeFlag(int32_t type, uint32_t flg, int32_t sw)
{
    EffectQueue* k = queueOfMainProcess();
    if (!k)
        return;
    for (EffectPacket* p = k->first.get(); p; p = p->next.get()) {
        if (p->type != type)
            continue;
        p->flag = static_cast<uint8_t>(sw ? p->flag | flg : p->flag & ~flg);
    }
}

// nbCheckSePacket @ 0x0025EF10: a sound `se` starting in (start - frame, start].
bool soundQueued(int32_t start, int32_t se, int32_t frame)
{
    const EffectPacket* p = guest::table<EffectQueue>(dds3::GetProcessData(GetMainProcessData()->EffectQueueProcessID))->first.get();
    for (; p; p = p->next.get()) {
        if (start < p->startframe || static_cast<int32_t>(static_cast<uint32_t>(start) - static_cast<uint32_t>(frame)) >= p->startframe)
            continue;
        if ((p->type == kSe || p->type == kSe2 || p->type == kSe3) && p->data1.i() == se)
            return true;
    }
    return false;
}

// ---- one packet each -----------------------------------------------------------------------

// nbAddSkillEffectKoukaPacket @ 0x00261500
EffectPacket& addSkillEffectPacket(int32_t startframe, int32_t framelength, int32_t uniqueid, uint32_t cuteff)
{
    EffectPacket& p = addTo(startframe, framelength, uniqueid, kSkillEffect);
    p.cuteff = cuteff;
    return p;
}

// nbAddSkillEffectKoukaPacket2 @ 0x00261638: open-ended (flag 1) without a length.
EffectPacket& addSkillEffectPacket2(int32_t startframe, int32_t framelength, int32_t uniqueid, uint32_t hbtl,
                                          int16_t cutno, Formation* form, int16_t j)
{
    EffectPacket& p = addTo(startframe, framelength, uniqueid, kSkillEffect2);
    if (framelength == 0)
        p.flag |= 1;
    p.form.address = guest::addressOf(form);
    p.data1.raw = hbtl;
    p.data2.setHalves(cutno, j);
    p.cuteff = 0;
    return p;
}

// nbAddSkillEffectKoukaPacket1 @ 0x002616E8
EffectPacket& addSkillEffectPacket1(int32_t startframe, int32_t framelength, int32_t uniqueid, uint32_t cuteff)
{
    EffectPacket& p = addTo(startframe, framelength, uniqueid, kSkillEffect1);
    p.cuteff = cuteff;
    return p;
}

// nbAddHatudoEffectEndPacket @ 0x00261758: ends a passive's ("hatudo") effect.
EffectPacket& addPassiveEffectEndPacket(int32_t startframe, int32_t uniqueid) { return add(startframe, uniqueid, kPassiveEffectEnd); }

// nbAddTargetMoveKoukaPacket @ 0x00261AA0: a party member moves to `pos`.
EffectPacket& addMoveToTargetPacket(int32_t startframe, int32_t uniqueid, int32_t partyno, const Vec4& pos, ee::Float speed)
{
    EffectPacket& p = add(startframe, uniqueid, kTargetMove);
    p.partyno = partyno;
    p.v = pos;
    p.data1.setFloat(speed);
    return p;
}

// nbAddHomeMoveKoukaPacket @ 0x00261B30: ... back to its place.
EffectPacket& addMoveHomePacket(int32_t startframe, int32_t uniqueid, int32_t partyno, ee::Float speed)
{
    EffectPacket& p = add(startframe, uniqueid, kHomeMove);
    p.data1.setFloat(speed);
    p.partyno = partyno;
    return p;
}

// nbAddRotKoukaPacket @ 0x00261BA0: turns to `v`.
EffectPacket& addTurnPacket(int32_t startframe, int32_t uniqueid, int32_t partyno, const Vec4& v, int32_t speed)
{
    EffectPacket& p = add(startframe, uniqueid, kRot);
    p.partyno = partyno;
    p.v = v;
    p.data1.setInt(speed);
    return p;
}

// 0x00261C30 (no HD name; played with nbAddRotKoukaPacket's): turns back home.
EffectPacket& addTurnHomePacket(int32_t startframe, int32_t uniqueid, int32_t partyno, int32_t speed)
{
    EffectPacket& p = add(startframe, uniqueid, kHomeRot);
    p.data1.setInt(speed);
    p.partyno = partyno;
    return p;
}

// nbAddUnitColKoukaPacket @ 0x00261CA0: tints a unit over `frame` frames.
EffectPacket& addUnitColorPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t col, int32_t frame)
{
    EffectPacket& p = addFor(startframe, uniqueid, form, kUnitCol);
    p.data2.raw = col;
    p.data1.setInt(frame);
    return p;
}

// nbAddUnitHomeColKoukaPacket @ 0x00261D20: ... back to its own colour.
EffectPacket& addUnitColorHomePacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t frame)
{
    EffectPacket& p = addFor(startframe, uniqueid, form, kUnitHomeCol);
    p.data1.setInt(frame);
    return p;
}

// nbAddUnitAKoukaPacket @ 0x00261D90: fades a unit to alpha `a`.
EffectPacket& addUnitAlphaPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t a, int32_t frame)
{
    EffectPacket& p = addFor(startframe, uniqueid, form, kUnitA);
    p.data2.raw = a;
    p.data1.setInt(frame);
    return p;
}

// nbAddUnitHomeAKoukaPacket @ 0x00261E10
EffectPacket& addUnitAlphaHomePacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t frame)
{
    EffectPacket& p = addFor(startframe, uniqueid, form, kUnitHomeA);
    p.data1.setInt(frame);
    return p;
}

// nbAddSakeKoukaPacket @ 0x00261E80: a dodge ("sake"), with its sound. The
// step is 0.9 of the unit's radius, at most 100.
EffectPacket& addDodgePacket(int32_t startframe, int32_t uniqueid, Formation& form)
{
    EffectPacket& p = add(startframe, uniqueid, kDodge);
    ee::Float step = form.r * *guest::table<ee::Float>(addr(0x0054e510));   // 0.9
    if (!(step <= ee::Float(100.0f)))
        step = 100.0f;
    p.form.address = guest::addressOf(&form);
    p.data1.setFloat(step);
    p.data2.raw = *guest::table<uint32_t>(addr(0x0054e514));                 // 0.3
    addSoundPacket(startframe, uniqueid, 0x10010);
    return p;
}

// 0x00261F30 (no HD name; played with nbAddMotionStopClearPacket's)
EffectPacket& addMotionStopPacket(int32_t startframe, int32_t uniqueid, Formation* form)
{
    return addFor(startframe, uniqueid, form, kMotionStop);
}

// nbAddMotionStopClearPacket @ 0x00261F90
EffectPacket& addMotionStopClearPacket(int32_t startframe, int32_t uniqueid, Formation* form)
{
    return addFor(startframe, uniqueid, form, kMotionStopClear);
}

// nbAddMotionKoukaPacket @ 0x00261FF0
EffectPacket& addMotionPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t motion)
{
    EffectPacket& p = addFor(startframe, uniqueid, form, kMotion);
    p.data1.setInt(motion);
    return p;
}

// nbAddSkillMotionKoukaPacket @ 0x00262060
EffectPacket& addSkillMotionPacket(int32_t startframe, int32_t uniqueid, Formation* form, int16_t motion,
                                         int16_t endtype, ee::Float ritu)
{
    EffectPacket& p = addFor(startframe, uniqueid, form, kSkillMotion);
    p.data2.setFloat(ritu);
    p.data1.setHalves(motion, endtype);
    return p;
}

// nbAddDmgMotKoukaPacket @ 0x002620F0: the hit reaction ("week": a weakness hit).
EffectPacket& addDamageMotionPacket(int32_t startframe, int32_t uniqueid, Formation* form, ee::Float range, int32_t week)
{
    EffectPacket& p = addFor(startframe, uniqueid, form, kDamageMotion);
    p.data2.setInt(week);
    p.data1.setFloat(range);
    return p;
}

// nbAddEasyDmgMotKoukaPacket @ 0x00262170
EffectPacket& addLightDamageMotionPacket(int32_t startframe, int32_t uniqueid, Formation* form, ee::Float range)
{
    EffectPacket& p = addFor(startframe, uniqueid, form, kLightDamageMotion);
    p.data1.setFloat(range);
    return p;
}

// nbAddBadDmgMotKoukaPacket @ 0x002621E0
EffectPacket& addAilmentDamageMotionPacket(int32_t startframe, int32_t uniqueid, Formation* form, ee::Float range,
                                       uint32_t badstat)
{
    EffectPacket& p = addFor(startframe, uniqueid, form, kAilmentDamageMotion);
    p.data2.raw = badstat;
    p.data1.setFloat(range);
    return p;
}

// nbAddBadMotKoukaPacket @ 0x00262260
EffectPacket& addAilmentMotionPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t badstat)
{
    EffectPacket& p = addFor(startframe, uniqueid, form, kAilmentMotion);
    p.data2.raw = badstat;
    return p;
}

// nbAddReturnKoukaPacket @ 0x002622D0: a unit leaves the field.
EffectPacket& addReturnPacket(int32_t startframe, int32_t uniqueid, Party* party, int32_t dead)
{
    EffectPacket& p = add(startframe, uniqueid, kReturn);
    p.data1.setInt(dead);
    p.party.address = guest::addressOf(party);
    return p;
}

// nbAddSummonKoukaPacket @ 0x00262340
EffectPacket& addSummonPacket(int32_t startframe, int32_t uniqueid, int16_t side, int16_t stockno, int16_t formindex)
{
    EffectPacket& p = add(startframe, uniqueid, kSummon);
    p.data2.raw = (p.data2.raw & 0xffff0000u) | static_cast<uint16_t>(formindex);
    p.data1.setHalves(side, stockno);
    return p;
}

// 0x002623C0 (no HD name; played with nbAddSkillColorOffPacket's)
EffectPacket& addSkillColorPacket(int32_t startframe, int32_t uniqueid, int32_t col, int32_t frame)
{
    EffectPacket& p = add(startframe, uniqueid, kSkillColor);
    p.data2.setInt(frame);
    p.data1.setInt(col);
    return p;
}

// nbAddSkillColorOffPacket @ 0x00262430
EffectPacket& addSkillColorOffPacket(int32_t startframe, int32_t uniqueid) { return add(startframe, uniqueid, kSkillColorOff); }

// nbAddBadEffKaifukuPacket @ 0x00262610: an ailment cured.
EffectPacket& addAilmentCureEffectPacket(int32_t startframe, int32_t uniqueid, Formation* form)
{
    return addFor(startframe, uniqueid, form, kAilmentCureEff);
}

// nbAddHitEffKoukaPacket @ 0x00262480: each kind's part effect and sound
// (0 none). Kind 3 has no effect; kinds past 10 neither.
EffectPacket* addHitEffectPacket(int32_t startframe, int32_t uniqueid, Formation& form, uint32_t kind)
{
    struct HitEffect { int32_t part; uint32_t sound; };
    static constexpr HitEffect kHitEffects[11] = {
        {0x18, 0}, {0x11, 0x10008}, {0x12, 0x10009}, {0, 0}, {0x1a, 0x10001}, {0x14, 0x10000},
        {0x0e, 0}, {0x19, 0}, {0x1b, 0x10005}, {0x1c, 0x10007}, {0x1d, 0x10006}};
    constexpr uint32_t kNoEffect = 3;
    if (!(form.stat & FormationStat::Present))
        return nullptr;
    EffectPacket& p = add(startframe, uniqueid, kHitEff);
    p.form.address = guest::addressOf(&form);
    p.data1.raw = kind;
    if (kind >= 11)
        return &p;
    if (kind == kNoEffect) {
        p.framelength = 0;
        return &p;
    }
    const HitEffect& effect = kHitEffects[kind];
    p.data2.raw = eff::BTLPartCreate(&form, effect.part);
    p.framelength = static_cast<int16_t>(eff::systemEffectLength(*guest::table<const eff::SystemEffect>(p.data2.raw)));
    diag::print(diag::Message::HitEffectLength, p.framelength);
    if (effect.sound != 0)
        addSoundPacket(startframe, uniqueid, effect.sound);
    return &p;
}

// nbAddBadEffKoukaPacket @ 0x00262670: an ailment's effect, numbered
// 1..11 for Shock .. Stone (0 for anything else).
EffectPacket& addAilmentEffectPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t bad)
{
    EffectPacket& p = add(startframe, uniqueid, kAilmentEff);
    p.form.address = guest::addressOf(form);
    int32_t effect = 0;
    for (int32_t i = 0; i < 11; ++i)
        if (bad == 1u << i)
            effect = i + 1;
    p.data1.setInt(effect);
    return p;
}

// nbAddNumEffKoukaPacket @ 0x002627C0: a damage number (n, n2: HP, MP).
void addNumberPacket(int32_t startframe, int32_t frame, int32_t uniqueid, Formation* form, int32_t n, int32_t n2,
                            int32_t type)
{
    EffectQueue& k = effectQueue();
    shortenEarlier(k, kNumberEff, startframe, uniqueid, form);
    EffectPacket& p = addPacket(k, startframe, frame, uniqueid);
    p.partyno = n2;
    p.form.address = guest::addressOf(form);
    p.data1.setInt(type);
    p.data2.setInt(n);
    p.type = kNumberEff;
}

// nbAddMojiEffKoukaPacket @ 0x002628D0: a word ("moji"): weak, resist ...;
// type 4 also plays its sound.
void addWordPacket(int32_t startframe, int32_t frame, int32_t uniqueid, Formation* form, int32_t type)
{
    EffectQueue& k = effectQueue();
    shortenEarlier(k, kWordEff, startframe, uniqueid, form);
    if (type == 4)
        addSoundPacket(startframe, uniqueid, 0x1000a);
    EffectPacket& p = addPacket(k, startframe, frame, uniqueid);
    p.data1.setInt(type);
    p.form.address = guest::addressOf(form);
    p.type = kWordEff;
}

// nbAddHpMpKoukaPacket @ 0x002629E8: applies an HP (type 0) or MP change.
EffectPacket& addHpMpPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t n, int32_t type)
{
    EffectPacket& p = addFor(startframe, uniqueid, form, kHpMp);
    p.data2.setInt(n);
    p.data1.setInt(type);
    return p;
}

// nbAddPressPacket @ 0x00262A68
EffectPacket& addPressPacket(int32_t startframe, int32_t uniqueid, ee::Float press)
{
    EffectPacket& p = add(startframe, uniqueid, kPress);
    p.data1.setFloat(press);
    return p;
}

// nbAddNewPressPacket @ 0x00262AC8: press turn icons gained or lost.
EffectPacket& addPressResultPacket(int32_t startframe, int32_t uniqueid, int16_t press_p, int16_t press_ten)
{
    EffectPacket& p = add(startframe, uniqueid, kNewPress);
    p.data1.setHalves(press_p, press_ten);
    return p;
}

// nbAddBadStatKoukaPacket @ 0x00262B38: sets (sw 1) or clears an ailment.
EffectPacket& addAilmentPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t badstat, int32_t sw)
{
    EffectPacket& p = addFor(startframe, uniqueid, form, kAilment);
    p.data2.raw = badstat;
    p.data1.setInt(sw);
    return p;
}

// nbAddBadMotKaifukuPacket @ 0x00262BB8
EffectPacket& addAilmentMotionCurePacket(int32_t startframe, int32_t uniqueid, Formation* form)
{
    return addFor(startframe, uniqueid, form, kAilmentMotionCure);
}

// nbAddDeadPcmPacket @ 0x00262C18: the unit's death cry (255 when flying).
EffectPacket* addDeathVoicePacket(int32_t startframe, int32_t uniqueid, Formation& form)
{
    const UnitWork* unit = GetUnitWorkFromFormindex(form.formindex);
    if (!unit)
        return nullptr;
    EffectPacket& p = add(startframe, uniqueid, kDeadPcm);
    p.form.address = guest::addressOf(&form);
    p.data1.setInt((unit->badstat & kAilmentMask) == ailment::Fly ? 0xff : unit->id);
    return &p;
}

// nbAddSePacket @ 0x00262CC0 / nbAddSePacket2 @ 0x00262D38 / 0x00262DB0:
// three sound channels, each skipping a repeat within 5 frames.
EffectPacket* addSoundPacket(int32_t startframe, int32_t uniqueid, uint32_t se) { return addSound(startframe, uniqueid, se, kSe); }

// nbAddSePacket2 @ 0x00262D38
EffectPacket* addSoundPacket2(int32_t startframe, int32_t uniqueid, uint32_t se) { return addSound(startframe, uniqueid, se, kSe2); }

// 0x00262DB0 (no HD name)
EffectPacket* addSoundPacket3(int32_t startframe, int32_t uniqueid, uint32_t se) { return addSound(startframe, uniqueid, se, kSe3); }

// nbAddHitStopPacket @ 0x00262E28: two frames' pause.
EffectPacket& addHitStopPacket(int32_t startframe, int32_t uniqueid) { return addTo(startframe, 2, uniqueid, kHitStop); }

// nbAddAnalyzePacket @ 0x00262E78
EffectPacket& addAnalyzePacket(int32_t startframe, int32_t uniqueid, Formation* form)
{
    EffectPacket& p = addTo(startframe, 2, uniqueid, kAnalyze);
    p.form.address = guest::addressOf(form);
    return p;
}

// nbAddJyokyoHelpPacket @ 0x00262ED8: a situation ("jyokyo") message.
EffectPacket& addStatusMessagePacket(int32_t startframe, int32_t uniqueid, int16_t no, int16_t var_id, int32_t var_ind)
{
    EffectPacket& p = add(startframe, uniqueid, kStatusMessage);
    p.data2.setInt(var_ind);
    p.data1.setHalves(no, var_id);
    return p;
}

// nbAddSkillNamePacket @ 0x00262F58
EffectPacket& addSkillNamePacket(int32_t startframe, int32_t uniqueid, int32_t id)
{
    EffectPacket& p = add(startframe, uniqueid, kSkillName);
    p.data1.setInt(id);
    return p;
}

// nbAddFormOnOffPacket @ 0x00262FB8: shows or hides a unit.
EffectPacket& addFormationShowPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t sw)
{
    EffectPacket& p = addFor(startframe, uniqueid, form, kFormOnOff);
    p.data1.setInt(sw);
    return p;
}

// nbAddFormFlagOnOffPacket @ 0x00263028
EffectPacket& addFormationFlagPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t sw, uint32_t flag)
{
    EffectPacket& p = addFor(startframe, uniqueid, form, kFormFlagOnOff);
    p.data2.raw = flag;
    p.data1.setInt(sw);
    return p;
}

// nbAddFlyKoukaPacket @ 0x002630A8
EffectPacket& addFlyPacket(int32_t startframe, int32_t uniqueid, Formation* form)
{
    EffectPacket& p = addFor(startframe, uniqueid, form, kFly);
    p.data1.raw = 0;
    return p;
}

// nbAddOngBunshinPacket @ 0x00263110 (no HD name: the HD remaster has only
// the three-clone version)
EffectPacket& addOngyokiClonePacket(int32_t startframe, int32_t uniqueid, Formation* sform, Formation* eform)
{
    EffectPacket& p = addPacket(effectQueue(), startframe, eff::ongyokiCloneEffectLength(), uniqueid);
    p.data1.raw = eff::OngyokiCloneEffectCreate({guest::addressOf(sform), guest::addressOf(eform)});
    p.type = kOngyokiClone;
    return p;
}

// nbAddOngBunshin2Packet @ 0x002631A0
EffectPacket& addOngyokiClonePacket2(int32_t startframe, int32_t uniqueid, Formation* sform, Formation* form1,
                                    Formation* form2, Formation* form3)
{
    EffectPacket& p = addPacket(effectQueue(), startframe, eff::ongyokiCloneEffect2Length(), uniqueid);
    p.data1.raw = eff::OngyokiCloneEffect2Create(
        {guest::addressOf(sform), guest::addressOf(form1), guest::addressOf(form2), guest::addressOf(form3)});
    p.type = kOngyokiClone2;
    return p;
}

// nbAddOngOutPacket @ 0x00263250
EffectPacket& addOngyokiOutPacket(int32_t startframe, int32_t uniqueid, Formation* form)
{
    EffectPacket& p = addPacket(effectQueue(), startframe, eff::ongyokiEffectLength(), uniqueid);
    p.data1.raw = eff::OngyokiEffectCreate({guest::addressOf(form)});
    p.type = kOngyokiOut;
    return p;
}

// nbAddOngOut2Packet @ 0x002632D0
EffectPacket& addOngyokiOutPacket2(int32_t startframe, int32_t uniqueid, Formation* form)
{
    EffectPacket& p = addPacket(effectQueue(), startframe, eff::ongyokiEffect2Length(), uniqueid);
    p.data1.raw = eff::OngyokiEffect2Create({guest::addressOf(form)});
    p.type = kOngyokiOut2;
    return p;
}

// nbAddDeadEventKoukaPacket @ 0x00263350: a death that starts an event.
// It also ends the battle (endtype 7); the event number it hands the main
// process is the new packet's still-empty data, 0.
EffectPacket& addDeathEventPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t eventno)
{
    EffectQueue& k = effectQueue();
    EffectPacket& p = addPacket(k, startframe, 0, uniqueid);
    MainProcessData& main = *k.data;
    main.actionstackp = 0;
    p.form.address = guest::addressOf(form);
    main.endtype = 7;
    main.eventno = p.data1.i();
    p.data1.setInt(eventno);
    p.type = kDeadEvent;
    return p;
}

// nbAddFadeOutKoukaPacket @ 0x002633E8 / nbAddFadeInKoukaPacket @ 0x00263458
EffectPacket& addFadeOutPacket(int32_t startframe, int32_t uniqueid, int32_t length, int32_t coltype)
{
    EffectPacket& p = add(startframe, uniqueid, kFadeOut);
    p.data2.setInt(coltype);
    p.data1.setInt(length);
    return p;
}

// nbAddFadeInKoukaPacket @ 0x00263458
EffectPacket& addFadeInPacket(int32_t startframe, int32_t uniqueid, int32_t length, int32_t coltype)
{
    EffectPacket& p = add(startframe, uniqueid, kFadeIn);
    p.data2.setInt(coltype);
    p.data1.setInt(length);
    return p;
}

// nbAddHojoKoukaPacket @ 0x002634C8: a buff or debuff ("hojo") shown.
EffectPacket& addBuffPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t hojotype, int32_t hojopoint)
{
    EffectPacket& p = addFor(startframe, uniqueid, form, kBuff);
    p.data2.setInt(hojopoint);
    p.data1.raw = hojotype;
    return p;
}

// nbAddFlareChargePacket @ 0x00263548
EffectPacket& addFlareChargePacket(int32_t startframe, int32_t uniqueid, int32_t point)
{
    EffectPacket& p = add(startframe, uniqueid, kFlareCharge);
    p.data1.setInt(point);
    return p;
}

// nbAddPadShockPacket @ 0x002635A8: the pad's vibration.
EffectPacket& addPadShockPacket(int32_t startframe, int32_t uniqueid, int16_t mode, int16_t pow, int16_t time)
{
    EffectPacket& p = add(startframe, uniqueid, kPadShock);
    p.data2.raw = (p.data2.raw & 0xffff0000u) | static_cast<uint16_t>(time);
    p.data1.setHalves(mode, pow);
    return p;
}

// nbAddPanelStockFadeOutPacket @ 0x00263628 / nbAddPanelStockEndPacket @ 0x00263678
EffectPacket& addStockPanelFadeOutPacket(int32_t startframe, int32_t uniqueid) { return add(startframe, uniqueid, kPanelStockFadeOut); }

// nbAddPanelStockEndPacket @ 0x00263678
EffectPacket& addStockPanelEndPacket(int32_t startframe, int32_t uniqueid) { return add(startframe, uniqueid, kPanelStockEnd); }

// ---- packets for a whole event ---------------------------------------------------------------

// nbMakeSummonPacket @ 0x002636C8: the unit appears and fades in.
int32_t makeSummonPackets(int32_t startframe, int32_t uniqueid, int16_t side, int16_t stockno, int16_t formindex)
{
    Formation* form = &GetMainProcessData()->form[formindex];
    addSummonPacket(startframe, uniqueid, side, stockno, formindex);
    makeFadeInPackets(startframe + 1, uniqueid, form, 0, 0xf, 0xf, 0x14);
    return 1;
}

// nbMakeReturnPacket @ 0x00263778: the unit fades out and leaves.
int32_t makeReturnPackets(int32_t startframe, int32_t uniqueid, Party& party)
{
    Formation* forms = GetMainProcessData()->form.get();
    party.flag = static_cast<int16_t>(party.flag | 0x20);
    makeFadeOutPackets(startframe, uniqueid, &forms[party.formindex], 0, 6, 6, 6);
    addReturnPacket(startframe + 0xd, uniqueid, &party, 0);
    return 1;
}

// nbMakeUnitFadeInPacket @ 0x00263810
int32_t makeFadeInPackets(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t col, int32_t delay,
                               int32_t aframe, int32_t colframe)
{
    addUnitColorPacket(startframe, uniqueid, form, col, 0);
    addUnitAlphaHomePacket(startframe, uniqueid, form, aframe);
    addUnitColorHomePacket(startframe + delay, uniqueid, form, colframe);
    return 1;
}

// nbMakeUnitFadeOutPacket @ 0x002638A0
int32_t makeFadeOutPackets(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t col, int32_t delay,
                                int32_t colframe, int32_t aframe)
{
    addUnitColorPacket(startframe, uniqueid, form, col, colframe);
    addUnitAlphaPacket(startframe + delay, uniqueid, form, 0, aframe);
    return 1;
}

// nbMakeDeadVisualPacket @ 0x00263918. The death types:
//   0 the unit reels (an ailment damage motion) and fades out over 10 frames
//   1 it fades out at once in a flash (hit effect 6)
//   2 a death with its own script or event: the ailment cured, the unit
//     slumps (models with a slump, 0x18 animations or more) or reels; an
//     event fades the screen out (and in again) and starts.
// Each but 1 sounds 0x10000 (1: 0x10004), with the cry, 7 frames on.
int32_t makeDeathVisualPackets(int32_t startframe, int32_t uniqueid, Formation& form, int32_t deadtype, int32_t deadpcm)
{
    constexpr int32_t kSlumpModels = 0x18;   // animations a model with the slump has
    if (diesByEvent(form))
        deadtype = 2;
    uint32_t sound = 0;
    switch (deadtype) {
    case 1:
        makeFadeOutPackets(startframe, uniqueid, &form, 0, 2, 2, 2);
        sound = 0x10004;
        addHitEffectPacket(startframe + 1, uniqueid, form, 6);
        break;
    case 0:
        addAilmentDamageMotionPacket(startframe, uniqueid, &form, ee::Float(17.0f), 0);
        sound = 0x10000;
        makeFadeOutPackets(startframe + 7, uniqueid, &form, 0, 10, 10, 10);
        break;
    case 2: {
        makeAilmentCurePackets(startframe, uniqueid, form);
        if (animationCount(form) < kSlumpModels)
            addAilmentDamageMotionPacket(startframe, uniqueid, &form, ee::Float(30.0f), ~0u);
        else
            addMotionPacket(startframe, uniqueid, &form, 1);
        sound = 0x10000;
        if (const int32_t eventno = hasDeathEvent(form)) {
            const int32_t fadeTime = deadEventFadeTime(eventno);
            const int32_t fadeOut = deadEventFadeOutFrame(eventno);
            const int32_t fadeStop = deadEventFadeStopFrame(eventno);
            const int32_t fadeIn = deadEventFadeInFrame(eventno);
            const int32_t fadeStart = startframe + fadeTime;
            addFadeOutPacket(fadeStart, uniqueid, fadeOut, 1);
            if (fadeIn > 0)
                addFadeInPacket(startframe + fadeStop + fadeOut + 2 + fadeTime, uniqueid, fadeIn, 1);
            addDeathEventPacket(fadeStart + fadeOut + fadeStop - 3, uniqueid, &form, eventno);
        }
        break;
    }
    default:
        break;
    }
    if (deadpcm != 0) {
        addDeathVoicePacket(startframe + 7, uniqueid, form);
        if (sound != 0)
            addSoundPacket(startframe + 7, uniqueid, sound);
    }
    if (form.stat & FormationStat::PartySlot) {
        if (GetUnitWorkFromFormindex(form.formindex)->flag & UnitFlag::PlayerCharacter)
            addPadShockPacket(startframe, uniqueid, 1, 0xfa, 0x1e);
        else
            addPadShockPacket(startframe, uniqueid, 1, 0x96, 0x14);
    }
    return 1;
}

// nbMakeDamagePacket @ 0x00263C00: a hit on `form`. On a unit's slot: its
// death if `dead`, else the ailment it takes or its hit reaction (type: a
// HitType, 3 for a light hit), and the hit's effect if `hiteff`. Then the HP
// and MP it loses (a negative amount: no change), shown as numbers if
// `numbers`, with the critical's or weakness's word; the numbers and words
// come `animeoff` frames after the hit.
int32_t makeDamagePackets(int32_t startframe, int32_t uniqueid, Formation& form, int32_t type, int32_t hp, int32_t mp,
                          uint32_t bad, bool hiteff, bool dead, int32_t deadtype, bool numbers, int32_t animeoff)
{
    constexpr int32_t kShownFrames = 0x2d;
    constexpr int32_t kLightHit = 3;
    enum : int32_t { kHpNumber = 0, kMpNumber = 1, kBothNumbers = 4 };
    enum : int32_t { kWeakWord = 1, kCriticalWord = 2 };
    const bool unitSlot = form.formindex < 16;
    if (unitSlot) {
        if (dead) {
            makeDeathVisualPackets(startframe, uniqueid, form, deadtype, 1);
        } else {
            switch (static_cast<Ailment>(bad)) {
            case Ailment::Shock: case Ailment::Freeze: case Ailment::Sleep: case Ailment::Panic:
            case Ailment::Bind: case Ailment::Mute: case Ailment::Poison: case Ailment::Charm:
            case Ailment::Stun: case Ailment::Stone: case Ailment::Dead:
                makeAilmentPackets(startframe, uniqueid, &form, bad);
                break;
            case Ailment::Fly:
                makeFlyAilmentPackets(startframe, uniqueid, &form);
                break;
            default:
                if (type >= 0 && type < kLightHit) {
                    addDamageMotionPacket(startframe, uniqueid, &form, ee::Float(17.0f), 1);
                } else if (type == kLightHit) {
                    addLightDamageMotionPacket(startframe, uniqueid, &form, ee::Float(10.0f));
                    addSoundPacket(startframe, uniqueid, 0x10002);
                }
                break;
            }
        }
        if (hiteff) {
            if (type == static_cast<int32_t>(HitType::Critical))
                addHitEffectPacket(startframe, uniqueid, form, 7);
            else if (type == static_cast<int32_t>(HitType::Normal) || type == static_cast<int32_t>(HitType::Weakness))
                addHitEffectPacket(startframe, uniqueid, form, 0);
        }
    }
    const int32_t frame = startframe + animeoff + 1;
    const bool shown = unitSlot && numbers;
    if (hp >= 0 && mp >= 0) {
        if (shown)
            addNumberPacket(frame, kShownFrames, uniqueid, &form, hp, mp, kBothNumbers);
        addHpMpPacket(startframe, uniqueid, &form, -hp, 0);
        addHpMpPacket(startframe, uniqueid, &form, -mp, 1);
    } else if (mp >= 0) {
        if (shown)
            addNumberPacket(frame, kShownFrames, uniqueid, &form, mp, 0, kMpNumber);
        addHpMpPacket(startframe, uniqueid, &form, -mp, 1);
    } else if (hp >= 0) {
        if (shown)
            addNumberPacket(frame, kShownFrames, uniqueid, &form, hp, 0, kHpNumber);
        addHpMpPacket(startframe, uniqueid, &form, -hp, 0);
    }
    if (numbers) {
        if (type == static_cast<int32_t>(HitType::Critical))
            addWordPacket(frame, kShownFrames, uniqueid, &form, kCriticalWord);
        else if (type == static_cast<int32_t>(HitType::Weakness))
            addWordPacket(frame, kShownFrames, uniqueid, &form, kWeakWord);
    }
    return 1;
}

// nbMakeKaifukuPacket @ 0x00264010: a heal on `form` ("kaifuku": recovery).
// On a unit's slot, type 1 shows a hit effect and type 3 (Drain Attack) a
// glow; types 0 and 2 (a drain's user) show nothing. Then the HP and MP it
// gains (negative: none), shown as numbers on a unit's slot, and the cure
// of its ailment if `cures`.
int32_t makeHealPackets(int32_t startframe, int32_t uniqueid, Formation& form, int32_t type, int32_t hp, int32_t mp,
                        bool cures)
{
    constexpr int32_t kShownFrames = 0x2d;
    constexpr uint32_t kDrainGlow = 0x8086eb9b;
    enum : int32_t { kHpNumber = 2, kMpNumber = 3, kBothNumbers = 5 };
    const bool unitSlot = form.formindex < 16;
    if (unitSlot) {
        if (type == 1) {
            addHitEffectPacket(startframe, uniqueid, form, 2);
        } else if (type == 3) {
            addUnitColorPacket(startframe, uniqueid, &form, kDrainGlow, 10);
            addUnitColorHomePacket(startframe + 10, uniqueid, &form, 10);
        }
    }
    const int32_t frame = startframe + 1;
    if (hp >= 0 && mp >= 0) {
        if (unitSlot)
            addNumberPacket(frame, kShownFrames, uniqueid, &form, hp, mp, kBothNumbers);
        addHpMpPacket(startframe, uniqueid, &form, hp, 0);
        addHpMpPacket(startframe, uniqueid, &form, mp, 1);
    } else if (mp >= 0) {
        if (unitSlot)
            addNumberPacket(frame, kShownFrames, uniqueid, &form, mp, 0, kMpNumber);
        addHpMpPacket(startframe, uniqueid, &form, mp, 1);
    } else if (hp >= 0) {
        if (unitSlot)
            addNumberPacket(frame, kShownFrames, uniqueid, &form, hp, 0, kHpNumber);
        addHpMpPacket(startframe, uniqueid, &form, hp, 0);
    }
    if (cures)
        makeAilmentCurePackets(frame, uniqueid, form);
    return 1;
}

// nbMakeDeadPacket @ 0x002641F8: a dead unit on the field leaves, unless its
// death starts an event or it is the Demi-fiend (deadchk 1: leaves anyway).
int32_t makeDeathPackets(int32_t startframe, int32_t uniqueid, Formation& form, int32_t deadchk)
{
    MainProcessData& main = *GetMainProcessData();
    if (!(form.stat & FormationStat::Present) || !(form.stat & FormationStat::CheckParty))
        return 1;
    Party& party = main.party[form.partyindex];
    const UnitWork& unit = *GetUnitWorkPointer(main, party);
    party.flag = static_cast<int16_t>(party.flag | 0x30);
    if ((!diesByEvent(form) && !(unit.flag & UnitFlag::PlayerCharacter)) || deadchk == 1)
        addReturnPacket(startframe, uniqueid, &party, 1);
    return 1;
}

// nbMakePressPacket @ 0x002642E0: `press` shared over the side's units
// (the enemies' when stat bit 8 is set).
int32_t makePressPackets(int32_t startframe, int32_t uniqueid, ee::Float press)
{
    const MainProcessData& main = *GetMainProcessData();
    const int16_t count = (main.stat & 8) ? main.enemypcnt : main.playerpcnt;
    addPressPacket(startframe, uniqueid, press / ee::Float::fromInt(count));
    return 1;
}

// nbMakeNewPressPacket @ 0x00264368: how a result changes the press turn
// icons (press4_p full, press4_ten blinking), neither above 8.
int32_t makePressResultPackets(int32_t startframe, int32_t uniqueid, int32_t ptype, int32_t callerSkill)
{
    const MainProcessData& main = *GetMainProcessData();
    const int32_t full = main.press4_p, half = main.press4_ten;
    const bool fewerFull = full < half;
    int32_t dFull = 0, dHalf = 0;
    if (static_cast<uint32_t>(ptype) < 18 && versionPressResult(ptype, callerSkill, dFull, dHalf))
        ptype = -1;   // (set already)
    switch (ptype) {
    case 0: case 8: case 9: case 10: case 11: case 12:   // a turn used
        dHalf = -1;
        if (!fewerFull)
            dFull = -1;
        break;
    case 1:
        if (fewerFull)
            dHalf = -1;
        else
            dFull = -1;
        break;
    case 2: case 3:
        if (full == 0)
            dHalf = -1;
        else
            dFull = -1;
        break;
    case 4: case 5:
        dHalf = -2;
        if (!fewerFull)
            dFull = -2;
        else if (half - 2 < full)
            dFull = -(full - half + 2);
        break;
    case 6: case 7: case 13: case 14:                     // all turns lost
        dHalf = -10;
        dFull = -10;
        break;
    case 15: dHalf = 2; break;
    case 16: dHalf = 4; break;
    case 17:                                              // (not in the first release)
        if (!kBuild.vanilla)
            dHalf = 3;
        break;
    default: break;
    }
    if (full + dFull >= 9)
        dFull = 8 - full;
    if (half + dHalf >= 9)
        dHalf = 8 - half;
    addPressResultPacket(startframe, uniqueid, static_cast<int16_t>(dFull), static_cast<int16_t>(dHalf));
    return 1;
}

// nbMakeFlyBadPacket @ 0x00264508
int32_t makeFlyAilmentPackets(int32_t startframe, int32_t uniqueid, Formation* form)
{
    addFlyPacket(startframe, uniqueid, form);
    return 1;
}

// nbMakeBadDamagePacket @ 0x00264528: an ailment inflicted.
int32_t makeAilmentPackets(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t bad)
{
    addAilmentDamageMotionPacket(startframe, uniqueid, form, 17.0f, bad);
    addAilmentEffectPacket(startframe, uniqueid, form, bad);
    addAilmentPacket(startframe, uniqueid, form, bad, 1);
    return 1;
}

// nbMakeBadKaifukuPacket @ 0x002645A8: an ailment cured; the cure's motion
// and effect for the player's side and a real ailment.
int32_t makeAilmentCurePackets(int32_t startframe, int32_t uniqueid, Formation& form)
{
    const int32_t formindex = form.formindex;
    const uint32_t bad = curedAilment(formindex, badStat(formindex));
    if (bad != 0)
        addAilmentPacket(startframe, uniqueid, &form, 0xfff, 0);
    if (formindex > 15)
        return 1;
    switch (bad) {
    case 1: case 2: case 4: case 8: case 0x10: case 0x20: case 0x40: case 0x80:
    case 0x100: case 0x200: case 0x400: case 0x800:
        addAilmentMotionCurePacket(startframe, uniqueid, &form);
        addAilmentCureEffectPacket(startframe, uniqueid, &form);
        break;
    default:
        break;
    }
    return 1;
}

} // namespace nocturne::nb

// ===========================================================================
// By version (nocturne/build.hpp): the alternatives the builds choose between
// ===========================================================================

namespace nocturne::nb {

#if NOCTURNE_HARDTYPE
// nbMakeNewPressPacket @ 0x00264368 (and 0x2FE480): for a result of type 0..17
// the noted pair is read and cleared: acting skill 0x10E counts as type 3,
// 0x86 takes 8 icons of each kind, and after a summon (skill 0xFF) the type
// is 1.
bool versionPressResult(int32_t& ptype, int32_t callerSkill, int32_t& dFull, int32_t& dHalf)
{
    const uint16_t acting = hardtype::actingSkill();
    hardtype::actingSkill() = 0;
    hardtype::standInSkill() = 0;
    if (acting == 0x10e) {
        ptype = 3;
        return false;
    }
    if (acting == 0x86) {
        dFull = -8;
        dHalf = -8;
        return true;
    }
    if (callerSkill == 0xff)
        ptype = 1;
    return false;
}
#else
// nbMakeNewPressPacket @ 0x00264368: none.
bool versionPressResult(int32_t&, int32_t, int32_t&, int32_t&) { return false; }
#endif

#if NOCTURNE_HARDTYPE
// nbMakeBadKaifukuPacket @ 0x002645A8 (and 0x2FE7A0): ailment 4 when bit 1 or
// 2 is set in the byte 0xE past what the unit lookup left in a0 (meant as the
// unit's ailment, it is the battle record's word 0xC for a unit in battle).
uint32_t curedAilment(int32_t formindex, uint32_t bad)
{
    const int8_t byte = *guest::table<int8_t>(hardtype::unitLookupRegister(formindex) + 0xe);
    return (byte & 3) ? 4 : bad;
}
#else
// nbMakeBadKaifukuPacket @ 0x002645A8: the unit's.
uint32_t curedAilment(int32_t, uint32_t bad) { return bad; }
#endif

} // namespace nocturne::nb
