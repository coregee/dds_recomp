// The battle's presentation queue (original units: nbKoukaProcess,
// nbMakePacket). Rewritten from the original instructions.
#include "nocturne/battle/kouka.hpp"

#include "nocturne/battle/combatant.hpp"
#include "nocturne/external.hpp"

namespace nocturne::nb {

namespace {

KoukaPacket& addTo(int32_t startframe, int32_t framelength, int32_t uniqueid, KoukaType type)
{
    KoukaPacket& p = nbAddKoukaPacket(nbGetKoukaProcessData(), startframe, framelength, uniqueid);
    p.type = type;
    return p;
}

KoukaPacket& add(int32_t startframe, int32_t uniqueid, KoukaType type) { return addTo(startframe, 0, uniqueid, type); }

// A packet on a formation slot.
KoukaPacket& addFor(int32_t startframe, int32_t uniqueid, Formation* form, KoukaType type)
{
    KoukaPacket& p = add(startframe, uniqueid, type);
    p.form.address = guest::addressOf(form);
    return p;
}

// The queue as the main process data names it (some functions reach it this way).
KoukaProcessData* queueOfMainProcess()
{
    const uint32_t process = GetMainProcessData()->KoukaProcessID;
    if (!process)
        return nullptr;
    return guest::table<KoukaProcessData>(dds3::GetProcessData(process));
}

// A damage number or word on the same unit ends where the new one starts.
void shortenEarlier(KoukaProcessData& k, KoukaType type, int32_t startframe, int32_t uniqueid, Formation* form)
{
    for (KoukaPacket* p = k.first.get(); p; p = p->next.get()) {
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
KoukaPacket* addSound(int32_t startframe, int32_t uniqueid, uint32_t se, KoukaType type)
{
    if (nbCheckSePacket(startframe, static_cast<int32_t>(se), 5))
        return nullptr;
    KoukaPacket& p = add(startframe, uniqueid, type);
    p.data1.setInt(static_cast<int32_t>(se));
    return &p;
}

} // namespace

// ---- the queue -----------------------------------------------------------------------------

// nbGetKoukaProcessData @ 0x0025E8E0: the "nbKoukaProcess" process's data.
KoukaProcessData& nbGetKoukaProcessData()
{
    return *guest::table<KoukaProcessData>(dds3::GetProcessData(dds3::SearchProcessName(0x00544350)));
}

// nbGetUniqueIdKoukaPacketCnt @ 0x0025E928: packets of one action.
int32_t nbGetUniqueIdKoukaPacketCnt(int32_t uniqueid)
{
    int32_t count = 0;
    for (const KoukaPacket* p = nbGetKoukaProcessData().first.get(); p; p = p->next.get())
        if (p->uniqueid == uniqueid)
            ++count;
    return count;
}

// nbGetKoukaPacketTypeCnt @ 0x0025E978
int32_t nbGetKoukaPacketTypeCnt(int8_t type)
{
    int32_t count = 0;
    for (const KoukaPacket* p = nbGetKoukaProcessData().first.get(); p; p = p->next.get())
        if (p->type == type)
            ++count;
    return count;
}

// LinkKoukaPacket @ 0x0025E9C8: at the end.
void LinkKoukaPacket(KoukaProcessData& k, KoukaPacket& p)
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
void UnlinkKoukaPacket(KoukaProcessData& k, KoukaPacket& p)
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
KoukaPacket& nbAddKoukaPacket(KoukaProcessData& k, int32_t startframe, int32_t framelength, int32_t uniqueid)
{
    KoukaPacket& p = *guest::table<KoukaPacket>(mem::PoolAllocate(sizeof(KoukaPacket)));
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
    LinkKoukaPacket(k, p);
    return p;
}

// nbOnOffKoukaPacketFlag @ 0x0025EE78: flag bits of every packet of a type.
void nbOnOffKoukaPacketFlag(int32_t type, uint32_t flg, int32_t sw)
{
    KoukaProcessData* k = queueOfMainProcess();
    if (!k)
        return;
    for (KoukaPacket* p = k->first.get(); p; p = p->next.get()) {
        if (p->type != type)
            continue;
        p->flag = static_cast<uint8_t>(sw ? p->flag | flg : p->flag & ~flg);
    }
}

// nbCheckSePacket @ 0x0025EF10: a sound `se` starting in (start - frame, start].
bool nbCheckSePacket(int32_t start, int32_t se, int32_t frame)
{
    const KoukaPacket* p = guest::table<KoukaProcessData>(dds3::GetProcessData(GetMainProcessData()->KoukaProcessID))->first.get();
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
KoukaPacket& nbAddSkillEffectKoukaPacket(int32_t startframe, int32_t framelength, int32_t uniqueid, uint32_t cuteff)
{
    KoukaPacket& p = addTo(startframe, framelength, uniqueid, kSkillEffect);
    p.cuteff = cuteff;
    return p;
}

// nbAddSkillEffectKoukaPacket2 @ 0x00261638: open-ended (flag 1) without a length.
KoukaPacket& nbAddSkillEffectKoukaPacket2(int32_t startframe, int32_t framelength, int32_t uniqueid, uint32_t hbtl,
                                          int16_t cutno, Formation* form, int16_t j)
{
    KoukaPacket& p = addTo(startframe, framelength, uniqueid, kSkillEffect2);
    if (framelength == 0)
        p.flag |= 1;
    p.form.address = guest::addressOf(form);
    p.data1.raw = hbtl;
    p.data2.setHalves(cutno, j);
    p.cuteff = 0;
    return p;
}

// nbAddSkillEffectKoukaPacket1 @ 0x002616E8
KoukaPacket& nbAddSkillEffectKoukaPacket1(int32_t startframe, int32_t framelength, int32_t uniqueid, uint32_t cuteff)
{
    KoukaPacket& p = addTo(startframe, framelength, uniqueid, kSkillEffect1);
    p.cuteff = cuteff;
    return p;
}

// nbAddHatudoEffectEndPacket @ 0x00261758: ends a passive's ("hatudo") effect.
KoukaPacket& nbAddHatudoEffectEndPacket(int32_t startframe, int32_t uniqueid) { return add(startframe, uniqueid, kHatudoEffectEnd); }

// nbAddTargetMoveKoukaPacket @ 0x00261AA0: a party member moves to `pos`.
KoukaPacket& nbAddTargetMoveKoukaPacket(int32_t startframe, int32_t uniqueid, int32_t partyno, const Vec4& pos, ee::Float speed)
{
    KoukaPacket& p = add(startframe, uniqueid, kTargetMove);
    p.partyno = partyno;
    p.v = pos;
    p.data1.setFloat(speed);
    return p;
}

// nbAddHomeMoveKoukaPacket @ 0x00261B30: ... back to its place.
KoukaPacket& nbAddHomeMoveKoukaPacket(int32_t startframe, int32_t uniqueid, int32_t partyno, ee::Float speed)
{
    KoukaPacket& p = add(startframe, uniqueid, kHomeMove);
    p.data1.setFloat(speed);
    p.partyno = partyno;
    return p;
}

// nbAddRotKoukaPacket @ 0x00261BA0: turns to `v`.
KoukaPacket& nbAddRotKoukaPacket(int32_t startframe, int32_t uniqueid, int32_t partyno, const Vec4& v, int32_t speed)
{
    KoukaPacket& p = add(startframe, uniqueid, kRot);
    p.partyno = partyno;
    p.v = v;
    p.data1.setInt(speed);
    return p;
}

// 0x00261C30 (no HD name; played with nbAddRotKoukaPacket's): turns back home.
KoukaPacket& nbAddHomeRotKoukaPacket(int32_t startframe, int32_t uniqueid, int32_t partyno, int32_t speed)
{
    KoukaPacket& p = add(startframe, uniqueid, kHomeRot);
    p.data1.setInt(speed);
    p.partyno = partyno;
    return p;
}

// nbAddUnitColKoukaPacket @ 0x00261CA0: tints a unit over `frame` frames.
KoukaPacket& nbAddUnitColKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t col, int32_t frame)
{
    KoukaPacket& p = addFor(startframe, uniqueid, form, kUnitCol);
    p.data2.raw = col;
    p.data1.setInt(frame);
    return p;
}

// nbAddUnitHomeColKoukaPacket @ 0x00261D20: ... back to its own colour.
KoukaPacket& nbAddUnitHomeColKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t frame)
{
    KoukaPacket& p = addFor(startframe, uniqueid, form, kUnitHomeCol);
    p.data1.setInt(frame);
    return p;
}

// nbAddUnitAKoukaPacket @ 0x00261D90: fades a unit to alpha `a`.
KoukaPacket& nbAddUnitAKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t a, int32_t frame)
{
    KoukaPacket& p = addFor(startframe, uniqueid, form, kUnitA);
    p.data2.raw = a;
    p.data1.setInt(frame);
    return p;
}

// nbAddUnitHomeAKoukaPacket @ 0x00261E10
KoukaPacket& nbAddUnitHomeAKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t frame)
{
    KoukaPacket& p = addFor(startframe, uniqueid, form, kUnitHomeA);
    p.data1.setInt(frame);
    return p;
}

// nbAddSakeKoukaPacket @ 0x00261E80: a dodge ("sake"), with its sound. The
// step is 0.9 of the unit's radius, at most 100.
KoukaPacket& nbAddSakeKoukaPacket(int32_t startframe, int32_t uniqueid, Formation& form)
{
    KoukaPacket& p = add(startframe, uniqueid, kSake);
    ee::Float step = form.r * *guest::table<ee::Float>(0x0054e510);   // 0.9
    if (!(step <= ee::Float(100.0f)))
        step = 100.0f;
    p.form.address = guest::addressOf(&form);
    p.data1.setFloat(step);
    p.data2.raw = *guest::table<uint32_t>(0x0054e514);                 // 0.3
    nbAddSePacket(startframe, uniqueid, 0x10010);
    return p;
}

// 0x00261F30 (no HD name; played with nbAddMotionStopClearPacket's)
KoukaPacket& nbAddMotionStopPacket(int32_t startframe, int32_t uniqueid, Formation* form)
{
    return addFor(startframe, uniqueid, form, kMotionStop);
}

// nbAddMotionStopClearPacket @ 0x00261F90
KoukaPacket& nbAddMotionStopClearPacket(int32_t startframe, int32_t uniqueid, Formation* form)
{
    return addFor(startframe, uniqueid, form, kMotionStopClear);
}

// nbAddMotionKoukaPacket @ 0x00261FF0
KoukaPacket& nbAddMotionKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t motion)
{
    KoukaPacket& p = addFor(startframe, uniqueid, form, kMotion);
    p.data1.setInt(motion);
    return p;
}

// nbAddSkillMotionKoukaPacket @ 0x00262060
KoukaPacket& nbAddSkillMotionKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, int16_t motion,
                                         int16_t endtype, ee::Float ritu)
{
    KoukaPacket& p = addFor(startframe, uniqueid, form, kSkillMotion);
    p.data2.setFloat(ritu);
    p.data1.setHalves(motion, endtype);
    return p;
}

// nbAddDmgMotKoukaPacket @ 0x002620F0: the hit reaction ("week": a weakness hit).
KoukaPacket& nbAddDmgMotKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, ee::Float range, int32_t week)
{
    KoukaPacket& p = addFor(startframe, uniqueid, form, kDmgMot);
    p.data2.setInt(week);
    p.data1.setFloat(range);
    return p;
}

// nbAddEasyDmgMotKoukaPacket @ 0x00262170
KoukaPacket& nbAddEasyDmgMotKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, ee::Float range)
{
    KoukaPacket& p = addFor(startframe, uniqueid, form, kEasyDmgMot);
    p.data1.setFloat(range);
    return p;
}

// nbAddBadDmgMotKoukaPacket @ 0x002621E0
KoukaPacket& nbAddBadDmgMotKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, ee::Float range,
                                       uint32_t badstat)
{
    KoukaPacket& p = addFor(startframe, uniqueid, form, kBadDmgMot);
    p.data2.raw = badstat;
    p.data1.setFloat(range);
    return p;
}

// nbAddBadMotKoukaPacket @ 0x00262260
KoukaPacket& nbAddBadMotKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t badstat)
{
    KoukaPacket& p = addFor(startframe, uniqueid, form, kBadMot);
    p.data2.raw = badstat;
    return p;
}

// nbAddReturnKoukaPacket @ 0x002622D0: a unit leaves the field.
KoukaPacket& nbAddReturnKoukaPacket(int32_t startframe, int32_t uniqueid, Party* party, int32_t dead)
{
    KoukaPacket& p = add(startframe, uniqueid, kReturn);
    p.data1.setInt(dead);
    p.party.address = guest::addressOf(party);
    return p;
}

// nbAddSummonKoukaPacket @ 0x00262340
KoukaPacket& nbAddSummonKoukaPacket(int32_t startframe, int32_t uniqueid, int16_t side, int16_t stockno, int16_t formindex)
{
    KoukaPacket& p = add(startframe, uniqueid, kSummon);
    p.data2.raw = (p.data2.raw & 0xffff0000u) | static_cast<uint16_t>(formindex);
    p.data1.setHalves(side, stockno);
    return p;
}

// 0x002623C0 (no HD name; played with nbAddSkillColorOffPacket's)
KoukaPacket& nbAddSkillColorPacket(int32_t startframe, int32_t uniqueid, int32_t col, int32_t frame)
{
    KoukaPacket& p = add(startframe, uniqueid, kSkillColor);
    p.data2.setInt(frame);
    p.data1.setInt(col);
    return p;
}

// nbAddSkillColorOffPacket @ 0x00262430
KoukaPacket& nbAddSkillColorOffPacket(int32_t startframe, int32_t uniqueid) { return add(startframe, uniqueid, kSkillColorOff); }

// nbAddBadEffKaifukuPacket @ 0x00262610: an ailment cured.
KoukaPacket& nbAddBadEffKaifukuPacket(int32_t startframe, int32_t uniqueid, Formation* form)
{
    return addFor(startframe, uniqueid, form, kBadEffKaifuku);
}

// nbAddBadEffKoukaPacket @ 0x00262670: an ailment's effect, numbered
// 1..11 for Shock .. Stone (0 for anything else).
KoukaPacket& nbAddBadEffKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t bad)
{
    KoukaPacket& p = add(startframe, uniqueid, kBadEff);
    p.form.address = guest::addressOf(form);
    int32_t effect = 0;
    for (int32_t i = 0; i < 11; ++i)
        if (bad == 1u << i)
            effect = i + 1;
    p.data1.setInt(effect);
    return p;
}

// nbAddNumEffKoukaPacket @ 0x002627C0: a damage number (n, n2: HP, MP).
void nbAddNumEffKoukaPacket(int32_t startframe, int32_t frame, int32_t uniqueid, Formation* form, int32_t n, int32_t n2,
                            int32_t type)
{
    KoukaProcessData& k = nbGetKoukaProcessData();
    shortenEarlier(k, kNumEff, startframe, uniqueid, form);
    KoukaPacket& p = nbAddKoukaPacket(k, startframe, frame, uniqueid);
    p.partyno = n2;
    p.form.address = guest::addressOf(form);
    p.data1.setInt(type);
    p.data2.setInt(n);
    p.type = kNumEff;
}

// nbAddMojiEffKoukaPacket @ 0x002628D0: a word ("moji"): weak, resist ...;
// type 4 also plays its sound.
void nbAddMojiEffKoukaPacket(int32_t startframe, int32_t frame, int32_t uniqueid, Formation* form, int32_t type)
{
    KoukaProcessData& k = nbGetKoukaProcessData();
    shortenEarlier(k, kMojiEff, startframe, uniqueid, form);
    if (type == 4)
        nbAddSePacket(startframe, uniqueid, 0x1000a);
    KoukaPacket& p = nbAddKoukaPacket(k, startframe, frame, uniqueid);
    p.data1.setInt(type);
    p.form.address = guest::addressOf(form);
    p.type = kMojiEff;
}

// nbAddHpMpKoukaPacket @ 0x002629E8: applies an HP (type 0) or MP change.
KoukaPacket& nbAddHpMpKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t n, int32_t type)
{
    KoukaPacket& p = addFor(startframe, uniqueid, form, kHpMp);
    p.data2.setInt(n);
    p.data1.setInt(type);
    return p;
}

// nbAddPressPacket @ 0x00262A68
KoukaPacket& nbAddPressPacket(int32_t startframe, int32_t uniqueid, ee::Float press)
{
    KoukaPacket& p = add(startframe, uniqueid, kPress);
    p.data1.setFloat(press);
    return p;
}

// nbAddNewPressPacket @ 0x00262AC8: press turn icons gained or lost.
KoukaPacket& nbAddNewPressPacket(int32_t startframe, int32_t uniqueid, int16_t press_p, int16_t press_ten)
{
    KoukaPacket& p = add(startframe, uniqueid, kNewPress);
    p.data1.setHalves(press_p, press_ten);
    return p;
}

// nbAddBadStatKoukaPacket @ 0x00262B38: sets (sw 1) or clears an ailment.
KoukaPacket& nbAddBadStatKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t badstat, int32_t sw)
{
    KoukaPacket& p = addFor(startframe, uniqueid, form, kBadStat);
    p.data2.raw = badstat;
    p.data1.setInt(sw);
    return p;
}

// nbAddBadMotKaifukuPacket @ 0x00262BB8
KoukaPacket& nbAddBadMotKaifukuPacket(int32_t startframe, int32_t uniqueid, Formation* form)
{
    return addFor(startframe, uniqueid, form, kBadMotKaifuku);
}

// nbAddDeadPcmPacket @ 0x00262C18: the unit's death cry (255 when flying).
KoukaPacket* nbAddDeadPcmPacket(int32_t startframe, int32_t uniqueid, Formation& form)
{
    const UnitWork* unit = GetUnitWorkFromFormindex(form.formindex);
    if (!unit)
        return nullptr;
    KoukaPacket& p = add(startframe, uniqueid, kDeadPcm);
    p.form.address = guest::addressOf(&form);
    p.data1.setInt((unit->badstat & kAilmentMask) == ailment::Fly ? 0xff : unit->id);
    return &p;
}

// nbAddSePacket @ 0x00262CC0 / nbAddSePacket2 @ 0x00262D38 / 0x00262DB0:
// three sound channels, each skipping a repeat within 5 frames.
KoukaPacket* nbAddSePacket(int32_t startframe, int32_t uniqueid, uint32_t se) { return addSound(startframe, uniqueid, se, kSe); }

// nbAddSePacket2 @ 0x00262D38
KoukaPacket* nbAddSePacket2(int32_t startframe, int32_t uniqueid, uint32_t se) { return addSound(startframe, uniqueid, se, kSe2); }

// 0x00262DB0 (no HD name)
KoukaPacket* nbAddSePacket3(int32_t startframe, int32_t uniqueid, uint32_t se) { return addSound(startframe, uniqueid, se, kSe3); }

// nbAddHitStopPacket @ 0x00262E28: two frames' pause.
KoukaPacket& nbAddHitStopPacket(int32_t startframe, int32_t uniqueid) { return addTo(startframe, 2, uniqueid, kHitStop); }

// nbAddAnalyzePacket @ 0x00262E78
KoukaPacket& nbAddAnalyzePacket(int32_t startframe, int32_t uniqueid, Formation* form)
{
    KoukaPacket& p = addTo(startframe, 2, uniqueid, kAnalyze);
    p.form.address = guest::addressOf(form);
    return p;
}

// nbAddJyokyoHelpPacket @ 0x00262ED8: a situation ("jyokyo") message.
KoukaPacket& nbAddJyokyoHelpPacket(int32_t startframe, int32_t uniqueid, int16_t no, int16_t var_id, int32_t var_ind)
{
    KoukaPacket& p = add(startframe, uniqueid, kJyokyoHelp);
    p.data2.setInt(var_ind);
    p.data1.setHalves(no, var_id);
    return p;
}

// nbAddSkillNamePacket @ 0x00262F58
KoukaPacket& nbAddSkillNamePacket(int32_t startframe, int32_t uniqueid, int32_t id)
{
    KoukaPacket& p = add(startframe, uniqueid, kSkillName);
    p.data1.setInt(id);
    return p;
}

// nbAddFormOnOffPacket @ 0x00262FB8: shows or hides a unit.
KoukaPacket& nbAddFormOnOffPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t sw)
{
    KoukaPacket& p = addFor(startframe, uniqueid, form, kFormOnOff);
    p.data1.setInt(sw);
    return p;
}

// nbAddFormFlagOnOffPacket @ 0x00263028
KoukaPacket& nbAddFormFlagOnOffPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t sw, uint32_t flag)
{
    KoukaPacket& p = addFor(startframe, uniqueid, form, kFormFlagOnOff);
    p.data2.raw = flag;
    p.data1.setInt(sw);
    return p;
}

// nbAddFlyKoukaPacket @ 0x002630A8
KoukaPacket& nbAddFlyKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form)
{
    KoukaPacket& p = addFor(startframe, uniqueid, form, kFly);
    p.data1.raw = 0;
    return p;
}

// nbAddDeadEventKoukaPacket @ 0x00263350: a death that starts an event.
// It also ends the battle (endtype 7); the event number it hands the main
// process is the new packet's still-empty data, 0.
KoukaPacket& nbAddDeadEventKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t eventno)
{
    KoukaProcessData& k = nbGetKoukaProcessData();
    KoukaPacket& p = nbAddKoukaPacket(k, startframe, 0, uniqueid);
    MainProcessData& main = *k.data;
    main.actionstackp = 0;
    p.form.address = guest::addressOf(form);
    main.endtype = 7;
    main.aiextra = p.data1.i();
    p.data1.setInt(eventno);
    p.type = kDeadEvent;
    return p;
}

// nbAddFadeOutKoukaPacket @ 0x002633E8 / nbAddFadeInKoukaPacket @ 0x00263458
KoukaPacket& nbAddFadeOutKoukaPacket(int32_t startframe, int32_t uniqueid, int32_t length, int32_t coltype)
{
    KoukaPacket& p = add(startframe, uniqueid, kFadeOut);
    p.data2.setInt(coltype);
    p.data1.setInt(length);
    return p;
}

// nbAddFadeInKoukaPacket @ 0x00263458
KoukaPacket& nbAddFadeInKoukaPacket(int32_t startframe, int32_t uniqueid, int32_t length, int32_t coltype)
{
    KoukaPacket& p = add(startframe, uniqueid, kFadeIn);
    p.data2.setInt(coltype);
    p.data1.setInt(length);
    return p;
}

// nbAddHojoKoukaPacket @ 0x002634C8: a buff or debuff ("hojo") shown.
KoukaPacket& nbAddHojoKoukaPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t hojotype, int32_t hojopoint)
{
    KoukaPacket& p = addFor(startframe, uniqueid, form, kHojo);
    p.data2.setInt(hojopoint);
    p.data1.raw = hojotype;
    return p;
}

// nbAddFlareChargePacket @ 0x00263548
KoukaPacket& nbAddFlareChargePacket(int32_t startframe, int32_t uniqueid, int32_t point)
{
    KoukaPacket& p = add(startframe, uniqueid, kFlareCharge);
    p.data1.setInt(point);
    return p;
}

// nbAddPadShockPacket @ 0x002635A8: the pad's vibration.
KoukaPacket& nbAddPadShockPacket(int32_t startframe, int32_t uniqueid, int16_t mode, int16_t pow, int16_t time)
{
    KoukaPacket& p = add(startframe, uniqueid, kPadShock);
    p.data2.raw = (p.data2.raw & 0xffff0000u) | static_cast<uint16_t>(time);
    p.data1.setHalves(mode, pow);
    return p;
}

// nbAddPanelStockFadeOutPacket @ 0x00263628 / nbAddPanelStockEndPacket @ 0x00263678
KoukaPacket& nbAddPanelStockFadeOutPacket(int32_t startframe, int32_t uniqueid) { return add(startframe, uniqueid, kPanelStockFadeOut); }

// nbAddPanelStockEndPacket @ 0x00263678
KoukaPacket& nbAddPanelStockEndPacket(int32_t startframe, int32_t uniqueid) { return add(startframe, uniqueid, kPanelStockEnd); }

// ---- packets for a whole event ---------------------------------------------------------------

// nbMakeSummonPacket @ 0x002636C8: the unit appears and fades in.
int32_t nbMakeSummonPacket(int32_t startframe, int32_t uniqueid, int16_t side, int16_t stockno, int16_t formindex)
{
    Formation* form = &GetMainProcessData()->form[formindex];
    nbAddSummonKoukaPacket(startframe, uniqueid, side, stockno, formindex);
    nbMakeUnitFadeInPacket(startframe + 1, uniqueid, form, 0, 0xf, 0xf, 0x14);
    return 1;
}

// nbMakeReturnPacket @ 0x00263778: the unit fades out and leaves.
int32_t nbMakeReturnPacket(int32_t startframe, int32_t uniqueid, Party& party)
{
    Formation* forms = GetMainProcessData()->form.get();
    party.flag = static_cast<int16_t>(party.flag | 0x20);
    nbMakeUnitFadeOutPacket(startframe, uniqueid, &forms[party.formindex], 0, 6, 6, 6);
    nbAddReturnKoukaPacket(startframe + 0xd, uniqueid, &party, 0);
    return 1;
}

// nbMakeUnitFadeInPacket @ 0x00263810
int32_t nbMakeUnitFadeInPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t col, int32_t delay,
                               int32_t aframe, int32_t colframe)
{
    nbAddUnitColKoukaPacket(startframe, uniqueid, form, col, 0);
    nbAddUnitHomeAKoukaPacket(startframe, uniqueid, form, aframe);
    nbAddUnitHomeColKoukaPacket(startframe + delay, uniqueid, form, colframe);
    return 1;
}

// nbMakeUnitFadeOutPacket @ 0x002638A0
int32_t nbMakeUnitFadeOutPacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t col, int32_t delay,
                                int32_t colframe, int32_t aframe)
{
    nbAddUnitColKoukaPacket(startframe, uniqueid, form, col, colframe);
    nbAddUnitAKoukaPacket(startframe + delay, uniqueid, form, 0, aframe);
    return 1;
}

// nbMakeDeadPacket @ 0x002641F8: a dead unit on the field leaves, unless its
// death starts an event or it is the Demi-fiend (deadchk 1: leaves anyway).
int32_t nbMakeDeadPacket(int32_t startframe, int32_t uniqueid, Formation& form, int32_t deadchk)
{
    MainProcessData& main = *GetMainProcessData();
    if (!(form.stat & FormationStat::Present) || !(form.stat & FormationStat::CheckParty))
        return 1;
    Party& party = main.party[form.partyindex];
    const UnitWork& unit = *GetUnitWorkPointer(main, party);
    party.flag = static_cast<int16_t>(party.flag | 0x30);
    if ((!nbCheckEventDead(form) && !(unit.flag & UnitFlag::PlayerCharacter)) || deadchk == 1)
        nbAddReturnKoukaPacket(startframe, uniqueid, &party, 1);
    return 1;
}

// nbMakePressPacket @ 0x002642E0: `press` shared over the side's units
// (the enemies' when stat bit 8 is set).
int32_t nbMakePressPacket(int32_t startframe, int32_t uniqueid, ee::Float press)
{
    const MainProcessData& main = *GetMainProcessData();
    const int16_t count = (main.stat & 8) ? main.enemypcnt : main.playerpcnt;
    nbAddPressPacket(startframe, uniqueid, press / ee::Float::fromInt(count));
    return 1;
}

// nbMakeNewPressPacket @ 0x00264368: how a result changes the press turn
// icons (press4_p full, press4_ten blinking), neither above 8.
int32_t nbMakeNewPressPacket(int32_t startframe, int32_t uniqueid, int32_t ptype)
{
    const MainProcessData& main = *GetMainProcessData();
    const int32_t full = main.press4_p, half = main.press4_ten;
    const bool fewerFull = full < half;
    int32_t dFull = 0, dHalf = 0;
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
    case 17: dHalf = 3; break;
    default: break;
    }
    if (full + dFull >= 9)
        dFull = 8 - full;
    if (half + dHalf >= 9)
        dHalf = 8 - half;
    nbAddNewPressPacket(startframe, uniqueid, static_cast<int16_t>(dFull), static_cast<int16_t>(dHalf));
    return 1;
}

// nbMakeFlyBadPacket @ 0x00264508
int32_t nbMakeFlyBadPacket(int32_t startframe, int32_t uniqueid, Formation* form)
{
    nbAddFlyKoukaPacket(startframe, uniqueid, form);
    return 1;
}

// nbMakeBadDamagePacket @ 0x00264528: an ailment inflicted.
int32_t nbMakeBadDamagePacket(int32_t startframe, int32_t uniqueid, Formation* form, uint32_t bad)
{
    nbAddBadDmgMotKoukaPacket(startframe, uniqueid, form, 17.0f, bad);
    nbAddBadEffKoukaPacket(startframe, uniqueid, form, bad);
    nbAddBadStatKoukaPacket(startframe, uniqueid, form, bad, 1);
    return 1;
}

// nbMakeBadKaifukuPacket @ 0x002645A8: an ailment cured; the cure's motion
// and effect for the player's side and a real ailment.
int32_t nbMakeBadKaifukuPacket(int32_t startframe, int32_t uniqueid, Formation& form)
{
    const int32_t formindex = form.formindex;
    const uint32_t bad = badStat(formindex);
    if (bad != 0)
        nbAddBadStatKoukaPacket(startframe, uniqueid, &form, 0xfff, 0);
    if (formindex > 15)
        return 1;
    switch (bad) {
    case 1: case 2: case 4: case 8: case 0x10: case 0x20: case 0x40: case 0x80:
    case 0x100: case 0x200: case 0x400: case 0x800:
        nbAddBadMotKaifukuPacket(startframe, uniqueid, &form);
        nbAddBadEffKaifukuPacket(startframe, uniqueid, &form);
        break;
    default:
        break;
    }
    return 1;
}

} // namespace nocturne::nb
