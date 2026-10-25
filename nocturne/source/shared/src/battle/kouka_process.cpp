// The kouka process (original unit: nbKoukaProcess): plays the presentation
// queue. Rewritten from the original instructions; the players not
// rewritten yet run as original code.
#include "nocturne/battle/kouka_process.hpp"

#include <algorithm>

#include "nocturne/address.hpp"
#include "nocturne/version_constants.hpp"
#include "nocturne/battle/buffs.hpp"
#include "nocturne/battle/formation.hpp"
#include "nocturne/battle/calc.hpp"
#include "nocturne/battle/help.hpp"
#include "nocturne/effect/cut.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"
#include "nocturne/kernel/main_loop.hpp"
#include "nocturne/script/vm.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kQueueName = addr(0x00544350);         // "nb_kouka"
constexpr uint32_t kStockPanelFading = addr(0x00551208);  // uint32 (gp-relative): the stock panel fades out
constexpr uint32_t kUnitModelMotion = 0x8c;         // a unit model's motion (its +0x1c: the playing one)
constexpr uint32_t kUnitModelFlags = 0xa4;

uint32_t& word(uint32_t address) { return *guest::table<uint32_t>(address); }

MainProcessData& battle(EffectQueue& k) { return *k.data; }

using Player = void (*)(EffectQueue&, EffectPacket&);

// Who plays a packet type: a rewritten player, or the original's address.
struct PlayerEntry {
    Player play;
    uint32_t original;
};

PlayerEntry playerFor(int8_t type)
{
    switch (type) {
    case kSkillEffect: case kSkillEffect2: case kSkillEffect1: case kSkillEffect3: return {playSkillEffect, 0};
    case kTargetMove: case kHomeMove: return {playMove, 0};
    case kRot: case kHomeRot: return {nullptr, addr(0x0025f228)};                                  // RunRotKouka
    case kUnitCol: case kUnitHomeCol: case kUnitA: case kUnitHomeA: return {playUnitColor, 0};
    case kDamageMotion: case kAilmentDamageMotion: case kAilmentMotion: case kLightDamageMotion:
        return {playDamageMotion, 0};
    case kReturn: return {playReturn, 0};
    case kSummon: return {playSummon, 0};
    case kDodge: return {playDodge, 0};
    case kSkillColorOff: case kSkillColor: return {playSkillColor, 0};
    case kHitEff: return {playHitEffect, 0};
    case kNumberEff: return {nullptr, addr(0x0025ffb0)};                                           // RunNumEffectKouka
    case kHpMp: return {playHpMp, 0};
    case kPress: case kNewPress: return {playPress, 0};
    case kAilment: return {playAilment, 0};
    case kAilmentMotionCure: return {playAilmentMotionCure, 0};
    case kWordEff: return {nullptr, addr(0x002601e8)};                                             // RunMojiEffectKouka
    case kAilmentEff: return {playAilmentEffect, 0};
    case kAilmentCureEff: return {playAilmentCureEffect, 0};
    case kSe: case kSe2: case kSe3: return {playSound, 0};
    case kMotion: case kSkillMotion: return {playMotion, 0};
    case kHitStop: return {playHitStop, 0};
    case kMotionStop: case kMotionStopClear: return {playMotionStop, 0};
    case kAnalyze: return {playAnalyze, 0};
    case kStatusMessage: return {playStatusMessage, 0};
    case kDeadPcm: return {nullptr, addr(0x00260888)};                                             // RunPcmKouka
    case kFormOnOff: return {playFormationShow, 0};
    case kOngyokiClone: case kOngyokiClone2: case kOngyokiOut: case kOngyokiOut2: return {playBossEffect, 0};
    case kFormFlagOnOff: return {playFormationFlag, 0};
    case kFly: return {nullptr, addr(0x00260aa8)};                                                 // RunFlyKouka
    case kDeadEvent: return {playDeathEvent, 0};
    case kFadeOut: case kFadeIn: return {playFade, 0};
    case kSkillName: return {playSkillName, 0};
    case kBuff: return {playBuff, 0};
    case kFlareCharge: return {playFlareCharge, 0};
    case kPadShock: return {playPadShock, 0};
    case kPanelStockFadeOut: return {playStockPanelFadeOut, 0};
    case kPanelStockEnd: return {playStockPanelEnd, 0};
    case kPassiveEffectEnd: return {playPassiveEffectEnd, 0};
    default: return {nullptr, 0};
    }
}

void play(EffectQueue& k, EffectPacket& p)
{
    const PlayerEntry entry = playerFor(p.type);
    if (entry.play)
        entry.play(k, p);
    else if (entry.original)
        guest::callEffectPlayer(entry.original, guest::addressOf(&k), guest::addressOf(&p));
}

// Packets on a unit wait while its formation is busy (flag bits 0..2).
bool waitsForUnit(int8_t type)
{
    switch (type) {
    case kSkillEffect: case kUnitCol: case kUnitHomeCol: case kUnitA: case kUnitHomeA: case kDamageMotion:
    case kAilmentDamageMotion: case kSummon: case kDodge: case kAilmentMotionCure: case kSkillEffect2:
    case kSkillEffect1: case kMotion: case kMotionStop: case kMotionStopClear: case kAilmentMotion:
    case kFormOnOff: case kSkillEffect3: case kFly: case kBuff: case kLightDamageMotion: case kSkillMotion:
        return true;
    default:
        return false;
    }
}

EffectQueue& queueOf(uint32_t process) { return *guest::table<EffectQueue>(dds3::GetProcessData(process)); }

} // namespace

// nbKoukaProcess1 @ 0x00260F38: one frame of the queue. A packet counts
// down its start; then it plays every frame (unless paused, flag 2) and
// counts down its length (unless held, flag 1); once the length runs out
// the packet is deleted.
int32_t runEffectQueue(uint32_t process)
{
    EffectQueue& k = queueOf(process);
    for (EffectPacket* p = k.first.get(); p;) {
        EffectPacket* next = p->next.get();
        if (!waitsForUnit(p->type) || !p->form || (p->form->flag & 7) == 0) {
            if (p->startframe >= 1) {
                --p->startframe;
            } else if (p->framelength < 0) {
                deletePacket(*p);
            } else if (!(p->flag & 2)) {
                play(k, *p);
                if (!(p->flag & 1))
                    --p->framelength;
                ++p->time;
            }
        }
        p = next;
    }
    return 0;
}

// nbKoukaShutdown @ 0x002613F8
void shutdownEffectQueue(uint32_t process)
{
    const uint32_t address = dds3::GetProcessData(process);
    EffectQueue& k = *guest::table<EffectQueue>(address);
    while (k.first)
        deletePacketFrom(k, *k.first);
    k.data->EffectQueueProcessID = 0;
    mem::PoolRelease(address);
}

// InitKoukaProcessData @ 0x00261450
uint32_t newEffectQueue(MainProcessData& data)
{
    const uint32_t address = mem::PoolAllocate(sizeof(EffectQueue));
    EffectQueue& k = *guest::table<EffectQueue>(address);
    k.data.address = guest::addressOf(&data);
    k.last.address = 0;
    k.packetcnt = 0;
    k.first.address = 0;
    return address;
}

// nbInitKoukaProcess @ 0x00261490
void startEffectQueue(MainProcessData& data)
{
    const uint32_t queue = newEffectQueue(data);
    const uint32_t process = dds3::StartProcess(kQueueName, 0x2b08, 1, 1, addr(0x00260f38), addr(0x002613f8), queue);
    dds3::LinkProcess(data.MainProcessID, process);
    data.EffectQueueProcessID = process;
}

// nbDelUnEventKoukaPacket @ 0x0025EDC0: the queue emptied but for sounds,
// voices and screen fades; units on their way back to the stock arrive,
// and a skill's colour ends.
void deleteNonEventPackets()
{
    MainProcessData& main = *GetMainProcessData();
    if (main.EffectQueueProcessID == 0)
        return;
    EffectQueue& k = queueOf(main.EffectQueueProcessID);
    for (EffectPacket* p = k.first.get(); p;) {
        EffectPacket* next = p->next.get();
        switch (p->type) {
        case kReturn:
            playReturn(k, *p);
            deletePacket(*p);
            break;
        case kSkillColorOff:
            eff::BTLSkillEnd();
            break;
        case kSe: case kSe2: case kSe3: case kDeadPcm: case kFadeOut: case kFadeIn:
            break;
        default:
            deletePacket(*p);
            break;
        }
        p = next;
    }
}

// RunBossEffectKouka @ 0x0025EFD0: a frame of Ongyo-Ki's effects.
void playBossEffect(EffectQueue&, EffectPacket& p)
{
    switch (p.type) {
    case kOngyokiClone: eff::OngyokiCloneEffectDraw(p.data1.raw); break;
    case kOngyokiClone2: eff::OngyokiCloneEffect2Draw(p.data1.raw); break;
    case kOngyokiOut: eff::OngyokiEffectDraw(p.data1.raw); break;
    case kOngyokiOut2: eff::OngyokiEffect2Draw(p.data1.raw); break;
    default: break;
    }
}

// RunSkillEffectKouka @ 0x0025F100: the packet's cut starts on its first
// frame (data1: the effect, data2: cut number and stat) and is drawn after;
// type 0x1A's is a system cut.
void playSkillEffect(EffectQueue&, EffectPacket& p)
{
    if (p.cuteff == 0) {
        diag::print(diag::Message::CutCreate);
        p.cuteff = eff::BTLCutCreate(p.data1.raw, static_cast<uint16_t>(p.data2.raw), p.form.get(),
                                     static_cast<uint32_t>(static_cast<int16_t>(p.data2.raw >> 16)));
        return;
    }
    switch (p.type) {
    case kSkillEffect: case kSkillEffect2: case kSkillEffect3: eff::BTLCutDraw(p.cuteff); break;
    case kSkillEffect1: eff::drawSystemCut(p.cuteff); break;
    default: break;
    }
}

// RunHatudoEffectEndKouka @ 0x0025F068: a passive that fired cuts its
// action's first cut short: 12 more frames.
void playPassiveEffectEnd(EffectQueue& k, EffectPacket& p)
{
    for (EffectPacket* q = k.first.get(); q; q = q->next.get()) {
        if (q->uniqueid != p.uniqueid || q->type != kSkillEffect1 || q->framelength < 0xd)
            continue;
        q->framelength = 0xc;
        eff::BattleCut& cut = *guest::table<eff::BattleCut>(q->cuteff);
        eff::setCutEndFrame(cut, eff::frame(cut) + 0xc);
    }
}

// RunMoveKouka @ 0x0025F1A8: a party member walks to its target (data1:
// speed, v: where) or home.
void playMove(EffectQueue& k, EffectPacket& p)
{
    if (!(battle(k).party[p.partyno].flag & 1))
        return;
    if (p.type == kTargetMove)
        MoveToTarget(ee::Float::fromBits(p.data1.raw), p.partyno, &p.v);
    else if (p.type == kHomeMove)
        MoveHome(ee::Float::fromBits(p.data1.raw), p.partyno);
}

// RunUnitColKouka @ 0x0025F370: the unit's colour (5) or alpha (7) moves to
// data2 over data1 frames, or back to its own (6, 8).
void playUnitColor(EffectQueue&, EffectPacket& p)
{
    Formation& form = *p.form;
    if (!(form.stat & 1) || !(form.stat & 2))
        return;
    const int32_t frames = p.data1.i();
    const bool home = p.type == kUnitHomeCol || p.type == kUnitHomeA;
    const uint32_t value = home ? form.homeColor : p.data2.raw;
    if (p.type == kUnitCol || p.type == kUnitHomeCol)
        UnitSetColor(form.hunit, frames, value);
    else if (p.type == kUnitA || p.type == kUnitHomeA)
        UnitSetAlpha(form.hunit, frames, value);
}

// RunMotionKouka @ 0x0025F4F0: the unit's motion (0x1B, data1; 0x17 loops
// back and forth), or a skill's motion (0x37: data1 low half the motion,
// high half how it ends, data2 its speed): ending 0 plays once, 1 holds the
// last frame, 2 and 3 hold it and clear the model's motion words.
void playMotion(EffectQueue&, EffectPacket& p)
{
    Formation& form = *p.form;
    if (p.type == kMotion) {
        if (p.data1.i() != 0x17)
            SetUnitMotion(form, p.data1.i(), 0, ee::Float::fromInt(1));
        else
            SetUnitMotion(form, 0x17, 2, ee::Float::fromInt(1));
    } else if (p.type == kSkillMotion) {
        const int16_t motion = static_cast<int16_t>(p.data1.raw);
        const int16_t ending = static_cast<int16_t>(p.data1.raw >> 16);
        const ee::Float speed = ee::Float::fromBits(p.data2.raw);
        if (ending == 1) {
            SetUnitMotion(form, motion, 3, speed);
        } else if (ending == 0) {
            SetUnitMotion(form, motion, 0, speed);
        } else if (ending == 2 || ending == 3) {
            SetUnitMotion(form, motion, 3, speed);
            UnitSetMotionWords(form.hunit, 0, 0);
        }
    }
}

// RunDamageMotionKouka @ 0x0025F620: the unit staggers (9: data1 how far,
// data2 a weak hit; 0x35 lightly), or an ailment's motion starts (0x0A with
// the hit, 0x25 alone; data2 the ailment, -1 none: back to standing).
// Ailments 4, 8, 0x20, 0x40, 0x80, 0x100 and 0x200 stagger then hold their
// pose (0x100 at half speed); 1, 2, 0x10 and 0x400 take their own motion.
void playDamageMotion(EffectQueue&, EffectPacket& p)
{
    Formation& form = *p.form;
    const ee::Float range = ee::Float::fromBits(p.data1.raw);
    switch (p.type) {
    case kLightDamageMotion: SetDamage2(form, range); return;
    case kDamageMotion: SetDamage(form, range, p.data2.i()); return;
    case kAilmentDamageMotion: case kAilmentMotion: break;
    default: return;
    }
    const int32_t bad = p.data2.i();
    const bool withHit = p.type == kAilmentDamageMotion;
    switch (bad) {
    case 1: case 2: case 0x10: case 0x400:
        if (withHit)
            SetBadstatMotion(form, bad, range);
        else
            SetBadstatMotion2(form);
        return;
    case -1:   // none: standing again
        SetDamage2(form, range);
        SetUnitMotion(form, 2, 0, ee::Float::fromInt(1));
        form.anime &= ~0x80u;
        SetWaitMotion(form, 2, ee::Float::fromInt(1));
        UnitSetMotionWords(form.hunit, 0, 0);
        return;
    case 4: case 8: case 0x20: case 0x40: case 0x80: case 0x100: case 0x200:
        if (withHit) {
            SetDamage(form, range, 1);
            if (form.anime & 0x80)
                word(word(word(form.hunit + kUnitModelMotion) + 0x1c) + 0x20) = form.motionSpeed.bits();
        }
        form.anime &= ~0x80u;
        SetWaitMotion(form, 2, bad == 0x100 ? ee::Float::fromBits(0x3f000000) : ee::Float::fromInt(1));
        return;
    default:
        SetBadstatMotion(form, bad, range);
        return;
    }
}

// RunMotionStopKouka @ 0x0025F458: the unit's motion freezes (0x20) or
// goes on at its saved speed (0x21).
void playMotionStop(EffectQueue&, EffectPacket& p)
{
    Formation& form = *p.form;
    if (!(form.stat & 1) || !(form.stat & 2))   // (stat 2: the model is loaded)
        return;
    const uint32_t model = form.hunit;
    uint32_t& flags = word(model + kUnitModelFlags);
    uint32_t& speed = word(word(word(model + kUnitModelMotion) + 0x1c) + 0x20);
    if (p.type == kMotionStop) {
        flags |= 0x400000;
        speed = 0;
    } else if (p.type == kMotionStopClear) {
        speed = form.motionSpeed.bits();
        flags = (flags & 0xffbfffbf) | 0x20;
    }
}

// RunReturnKouka @ 0x0025F950: a unit goes back to the stock (data1: it
// died). Encounter 0x10F notes that one did (stat 0x2000).
void playReturn(EffectQueue& k, EffectPacket& p)
{
    ReturnUnit(p.party->partyindex, 0, p.data1.i());
    MainProcessData& main = battle(k);
    if (main.encno == 0x10f)
        main.stat |= 0x2000;
}

// nbSetPlayerFormation @ 0x0028B0A0 (`empty` unused)
void setPlayerFormation(MainProcessData& data, int32_t) { SetPartyFormation(data, 0x100); }

// RunSummonKouka @ 0x0025F9A8: a summoned devil appears (data1: side and
// stock index, data2: its slot); its side is laid out again, and on its
// own side's turn the turn order takes it in.
void playSummon(EffectQueue& k, EffectPacket& p)
{
    UpdateOrder();
    const int16_t side = static_cast<int16_t>(p.data1.raw);
    const int16_t formindex = static_cast<int16_t>(p.data2.raw);
    SummonUnit(side, static_cast<int16_t>(p.data1.raw >> 16), formindex);
    MainProcessData& main = battle(k);
    if (side == 0) {
        setPlayerFormation(main, 0);
        if (!(main.stat & 8))
            AddToOrder(formindex);
    } else if (side == 1) {
        SetEnemyFormation(main);
        if (main.stat & 8)
            AddToOrder(formindex);
    }
}

// nbSetSakeMotion's step (0x0024DF58; tentative name)
void startDodge(ee::Float step, ee::Float speed, Formation& form)
{
    form.dodgeStartSpeed = speed;
    form.type = 2;
    form.dodgeStep = step;
    form.dodgeDistance = ee::Float::fromBits(0);
    form.dodgeSpeed = speed;
}

// RunSakeKouka @ 0x0025FA50: the target sidesteps (data1: how far, data2:
// how fast).
void playDodge(EffectQueue&, EffectPacket& p)
{
    startDodge(ee::Float::fromBits(p.data1.raw), ee::Float::fromBits(p.data2.raw), *p.form);
}

// RunBadEffKouka @ 0x0025FA70: the unit's ailment effect (data1: its kind,
// 0 none) replaces the one it had.
void playAilmentEffect(EffectQueue&, EffectPacket& p)
{
    Formation& form = *p.form;
    if ((form.anime & 0x100) && form.ailmentEffect != 0) {
        eff::BTLPartEnd(form.ailmentEffect);
        form.ailmentEffect = 0;
        form.anime &= ~0x100u;
    }
    if (p.data1.raw != 0) {
        form.ailmentEffect = eff::BTLPartCreate(&form, p.data1.i());
        form.anime |= 0x100;
    }
}

// RunBadEffKaifukuKouka @ 0x0025FAF8: the unit's ailment effect ends.
void playAilmentCureEffect(EffectQueue&, EffectPacket& p)
{
    Formation& form = *p.form;
    if ((form.anime & 0x100) && form.ailmentEffect != 0) {
        eff::BTLPartEnd(form.ailmentEffect);
        form.ailmentEffect = 0;
        form.anime &= ~0x100u;
    }
}

// RunHitEffectKouka @ 0x0025FB58: a hit effect's frame (data1: its kind;
// kind 3 draws nothing).
void playHitEffect(EffectQueue&, EffectPacket& p)
{
    switch (p.data1.raw) {
    case 0: case 1: case 2: case 4: case 5: case 6: case 7: case 8: case 9: case 10:
        eff::BTLPartDraw(p.data2.raw);
        break;
    default:
        break;
    }
}

// RunHpMpKouka @ 0x002604E8: HP or MP change (data1: which, data2: by how
// much), unless nothing can change (stat 0x20000).
void playHpMp(EffectQueue& k, EffectPacket& p)
{
    if (!(battle(k).stat & 0x20000))
        addHpMp(p.form->formindex, static_cast<Resource>(p.data1.i()), p.data2.i());
}

// RunBadStatKouka @ 0x00260600: an ailment set or cleared (data1: set,
// data2: which).
void playAilment(EffectQueue&, EffectPacket& p) { setAilment(p.form->formindex, p.data1.raw != 0, p.data2.raw); }

// RunSeKouka @ 0x002606D8: a sound effect (data1). 0x19 plays it; 0x1C
// plays it if its bank is in, noting either way; 0x1D waits a frame at a
// time until the bank is in. The event boss's music for a repelled skill
// 0x107 stops at sound 0x10008 or 0x10009, for 0x113 at 0x10008.
void playSound(EffectQueue& k, EffectPacket& p)
{
    const int32_t sound = p.data1.i();
    const bool ready = snd::BankReady(static_cast<uint32_t>(sound));
    MainProcessData& main = battle(k);
    if (main.d31_repel107 != 0 && static_cast<uint32_t>(sound - 0x10008) < 2) {
        main.d31_repel107 = 0;
        snd::StopEffectMidi(kRepelledSkillMusic);
    }
    if (main.d31_repel113 != 0 && sound == 0x10008) {
        main.d31_repel113 = 0;
        snd::StopEffectMidi(0x1c740000);
    }
    switch (p.type) {
    case kSe2:
        if (!ready) {
            scr::scrPrintf(optionalAddr(0x00544680), static_cast<uint32_t>(sound));   // "se2 [%08X] chk err"
            return;
        }
        scr::scrPrintf(optionalAddr(0x00544668), static_cast<uint32_t>(sound));       // "se2 [%08X] play!"
        snd::Play(sound, 0x7f, 0x3f);
        break;
    case kSe:
        snd::Play(sound, 0x7f, 0x3f);
        break;
    case kSe3:
        if (ready)
            snd::Play(sound, 0x7f, 0x3f);
        else
            p.framelength = 1;   // (try again next frame)
        break;
    default:
        break;
    }
}

// RunHitStopKouka @ 0x00260928: the game stops 12 frames, then runs at a
// third of its speed for 24.
void playHitStop(EffectQueue&, EffectPacket& p)
{
    if (p.time == 0)
        dds3::stop(0xc);
    else if (p.time == 1)
        dds3::slowOn(3, 0x18);
}

// RunPressKouka @ 0x00260528: the press gauge moves (0x12, data1: by how
// much, kept within 0..1), or the press turn icons change (0x1F, data1: full
// and blinking icons gained). On the player's turn the blinking icons lost
// are counted (d31_press_total). Not while the units' state is held (0x10000).
void playPress(EffectQueue& k, EffectPacket& p)
{
    MainProcessData& main = battle(k);
    if (main.stat & 0x10000)
        return;
    if (p.type == kPress) {
        ee::Float gauge = main.press3 + ee::Float::fromBits(p.data1.raw);
        if (gauge < ee::Float::fromBits(0))
            gauge = ee::Float::fromBits(0);
        if (ee::Float::fromInt(1) < gauge)
            gauge = ee::Float::fromInt(1);
        main.press3 = gauge;
    } else if (p.type == kNewPress) {
        const bool playerTurn = !(main.stat & 8);
        const int32_t before = playerTurn ? main.press4_ten : 0;
        main.press4_p = static_cast<int16_t>(std::max(main.press4_p + static_cast<int16_t>(p.data1.raw), 0));
        const int32_t blinking = std::max(main.press4_ten + static_cast<int16_t>(p.data1.raw >> 16), 0);
        main.press4_ten = static_cast<int16_t>(blinking);
        if (playerTurn)
            main.d31_press_total += static_cast<uint32_t>(before - blinking);
    }
}

// RunBadMotKaifukuKouka @ 0x00260628: an ailment's motion ends: the motion
// plays at its saved speed, the unit back to standing.
void playAilmentMotionCure(EffectQueue&, EffectPacket& p)
{
    Formation& form = *p.form;
    word(word(word(form.hunit + kUnitModelMotion) + 0x1c) + 0x20) = form.motionSpeed.bits();
    SetWaitMotion(form, 0, ee::Float::fromInt(1));
    SetUnitMotion(form, 0, 1, ee::Float::fromInt(1));
    form.time = 0;
    form.type = 0;
    form.anime &= ~0x80u;
}

// RunAnalyzeKouka @ 0x00260978: the panel shows the unit's page.
void playAnalyze(EffectQueue&, EffectPacket& p)
{
    if (UnitWork* unit = GetUnitWorkFromFormindex(p.form->formindex)) {
        PanelSetAnalyzeUnit(unit);
        PanelSetEnabled(false);
    }
}

// RunHelpKouka @ 0x002609C0: the status line (data1: message and its
// variable's type, data2: the variable).
void playStatusMessage(EffectQueue& k, EffectPacket& p)
{
    if (p.type == kStatusMessage)
        showStatusMessage(battle(k).statusMessageTable, static_cast<int16_t>(p.data1.raw),
                          static_cast<int16_t>(p.data1.raw >> 16), p.data2.i());
}

// RunFormOnOffKouka @ 0x00260A00: the unit's model hidden (data1 0) or shown.
void playFormationShow(EffectQueue&, EffectPacket& p)
{
    Formation* form = p.form.get();
    if (!form || !(form->stat & FormationStat::Present))
        return;
    if (p.data1.raw == 0)
        hideFormationModel(form->formindex);
    else
        showFormationModel(form->formindex);
}

// RunFormFlagOnOffKouka @ 0x00260A58: formation stat bits (data2) set or cleared.
void playFormationFlag(EffectQueue&, EffectPacket& p)
{
    Formation* form = p.form.get();
    if (!form || !(form->stat & FormationStat::Present))
        return;
    if (p.data1.raw != 0)
        form->stat |= p.data2.raw;
    else
        form->stat &= ~p.data2.raw;
}

// RunDeadEventKouka @ 0x00260D68: a death starts its event (data1); the
// queued actions are dropped.
void playDeathEvent(EffectQueue& k, EffectPacket& p)
{
    MainProcessData& main = battle(k);
    main.actionstackp = 0;
    main.eventno = p.data1.i();
}

// RunFadeKouka @ 0x00260D80: the screen fades out to black (data2 0) or
// white (1) over data1 frames, or back in.
void playFade(EffectQueue&, EffectPacket& p)
{
    if (p.type == kFadeOut) {
        if (p.data2.raw == 0)
            dds3::FadeOut(0, 0, 0, p.data1.i());
        else if (p.data2.raw == 1)
            dds3::FadeOut(0xff, 0xff, 0xff, p.data1.i());
    } else if (p.type == kFadeIn) {
        dds3::FadeIn2(p.data1.i());
    }
}

// RunSkillNameKouka @ 0x00260E18
void playSkillName(EffectQueue&, EffectPacket& p) { showSkillName(p.data1.i()); }

// RunHojoKouka @ 0x00260E30: buffs applied (data1: which, data2: how much).
void playBuff(EffectQueue&, EffectPacket& p) { applyBuffs(p.form->formindex, p.data1.raw, p.data2.i(), false); }

// RunFlareChargeKouka @ 0x00260E58: Kagutsuchi moves on two sixteenths.
void playFlareCharge(EffectQueue&, EffectPacket&) { evt::SetAgeOfMoon((evt::GetAgeOfMoon16() + 2) % 16); }

// RunPadShockKouka @ 0x00260E98: the pad vibrates (mode, strength, frames).
void playPadShock(EffectQueue&, EffectPacket& p)
{
    dds3::PadAct(static_cast<uint32_t>(static_cast<int16_t>(p.data1.raw)), static_cast<uint8_t>(p.data1.raw >> 16),
                 static_cast<uint32_t>(static_cast<int16_t>(p.data2.raw)));
}

// RunSkillColorKouka @ 0x00260EB8: the skill's field colour starts (data1:
// colour, data2: frames) or ends.
void playSkillColor(EffectQueue&, EffectPacket& p)
{
    if (p.type == kSkillColorOff)
        eff::BTLSkillEnd();
    else if (p.type == kSkillColor)
        eff::BTLSkillStart(p.data1.i(), p.data2.i());
}

// 0x0027FA88 (tentative name)
void startStockPanelFadeOut() { word(kStockPanelFading) = 1; }

// RunStockPanelFadeOutKouka @ 0x00260F08
void playStockPanelFadeOut(EffectQueue&, EffectPacket&) { startStockPanelFadeOut(); }

// RunStockPanelEndKouka @ 0x00260F20
void playStockPanelEnd(EffectQueue&, EffectPacket&) { PanelStockEnd(); }

} // namespace nocturne::nb
