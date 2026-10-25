// Implements nocturne/external.hpp on top of the legacy recovered C ABI.
//
// The legacy functions pass guest addresses as uint64_t register images and
// sign-extend 32-bit results. This file is the only place in the rewrite that
// deals with that; everything else sees typed references.
//
// Link with the legacy objects (or, in tests, with the fake world). Also
// requires a platform implementation of nocturne::guest::resolve/addressOf.
#include <cstdint>

#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

extern "C" {
uint64_t nbGetMainProcessData(void);
uint64_t nbGetUnitWorkFromFormindex(uint64_t formindex);
uint64_t nbGetPartyFromFormindex(uint64_t formindex);
uint64_t nbGetUnitWorkPointer(uint64_t main_data, uint64_t party);
int32_t cmpRemoveDevilEx(uint16_t devil);
void effBTLDelete(uint64_t handle);
void effBTLCutDelete(uint64_t cut);
uint64_t effBTLCutCreate(uint64_t effect, uint64_t cut, uint64_t form, uint64_t state);
void effBTLCutDraw(uint64_t cut);   // 0x16B0F0: no legacy C yet
void effBTLSkillSetFormationInfo(uint64_t formindex, uint64_t targets);
void nbInitNegoProcess(uint64_t act, uint64_t pformindex, uint64_t eformindex, uint64_t negotype, uint64_t skill);   // 0x26CCF0: no legacy C yet
void nbSetWaitMotion(uint64_t form, uint64_t motion, uint32_t speed);                   // 0x24D238: float in f12; no plain legacy C
void nbSetUnitMotion(uint64_t form, uint64_t motion, uint64_t loop, uint32_t speed);    // 0x24CFF8: float in f12; no plain legacy C
void nbPanelAllShow(void);
void effBTLSkillStart(uint64_t skill, uint64_t arg);      // 0x16B7A8: no named legacy C yet (the tests fake it)
void effBTLSkillEnd(void);                                // 0x16B850: no named legacy C yet
uint64_t effBTLBedName(uint64_t skill);                   // 0x1748A0: no named legacy C yet
uint64_t effBTLLoad(uint64_t data);                       // 0x16A9C0
uint64_t ps2SoundBankStatus(uint64_t bank);
void ps2SoundSetBankSource(uint64_t data, uint64_t size); // 0x2C1DB0
uint64_t fileRequest(uint64_t path);                      // 0x296A68
uint64_t fileCheckEnd(uint64_t request);
uint64_t fileGetMemHandle(uint64_t request);
uint64_t fileGetLoadSize(uint64_t request);
void ps2ResourceRequestRelease(uint64_t request);
uint64_t nbGetMotionActframe(uint64_t form, uint64_t motion, uint32_t speed);   // 0x24D3A0: float in f12
uint32_t nbGetMotionSpeed(uint64_t form, uint64_t motion, uint32_t speed);      // 0x24D428: float in f12 and f0
uint64_t nbGetMotionNo(uint64_t form, uint64_t motion);                         // 0x24D490
void nbMakeSkillEffectPacket(uint64_t start, uint64_t timer, uint64_t act, uint64_t form, uint64_t hiteff,
                             uint64_t motiontype, uint64_t skill);              // 0x2617A8
void nbAddHitEffPacket(uint64_t start, uint64_t act, uint64_t form, uint64_t kind);   // 0x262480
void nbMakeTargetPacket(uint64_t start, uint64_t act, uint64_t form, uint64_t targets, uint64_t kind,
                        uint32_t speed);                                        // 0x2648C0: float in f12           // 0x279C30: no named legacy C yet (the tests fake it)
void nbPanelPressGaugeShow(void);    // 0x27C2C0: no named legacy C yet
void nbPanelStockSelectInit(void);   // 0x27FA98: no named legacy C yet
void nbPanelStockEnd(void);          // 0x27FA78: no named legacy C yet
void effBTLSystemCutDelete(uint64_t cut);       // 0x1740B8: no legacy C yet (the tests fake it)
void effBTLPartDelete(uint64_t part);           // 0x173D78: no legacy C yet
void effPCPBossONGYDelete(uint64_t handle);     // 0x198298: no legacy C yet
void effPCPBossONGY2Delete(uint64_t handle);    // 0x198900: no legacy C yet
void effPCPBossBUNSINDelete(uint64_t handle);   // 0x1990F0: no legacy C yet
void effPCPBossBUNSIN2Delete(uint64_t handle);  // 0x199BC8: no legacy C yet
uint64_t ps2BattleActionSkill_00198200(uint64_t param);   // effPCPBossONGYCreate
uint64_t ps2BattleActionSkill_00198868(uint64_t param);   // effPCPBossONGY2Create
uint64_t effPCPBossBUNSINCreate(uint64_t param);          // 0x199000: no legacy C yet (the tests fake it)
uint64_t effPCPBossBUNSIN2Create(uint64_t param);         // 0x199B10: no legacy C yet (the tests fake it)
uint32_t evtBitCheck(int32_t no);
uint32_t evtGetAgeOfMoon(void);
uint32_t sdfGetRandInt(uint32_t* state, uint32_t limit);
uint32_t sdfGetRand(uint32_t* state);
float sdfGetRandFloat(uint32_t* state);
uint64_t ps2LibcPrintf(uint64_t format, ...);
void evtBitOn(int32_t no);
uint32_t evtGetAgeOfMoon16(void);
uint64_t dds3SearchProcessName(uint64_t name);
uint64_t dds3GetProcessData(uint64_t process);
void evtBitOff(int32_t no);
[[noreturn]] void nocturneCompilerArithmeticTrap(uint32_t code);
uint64_t ps2SoundPlay(uint64_t sound, uint64_t volume, uint64_t pan);
uint32_t ps2MemoryHandleAllocate(int32_t size);
uint32_t ps2MemoryHandleAcquirePointer(uint32_t handle);
void ps2MemoryHandleFree(uint32_t handle);
void ps2PacRelocatePointers(uint64_t destination, uint64_t base, uint64_t table, uint64_t bytes);
void nocturneInvokeMessageKutiCallback(uint32_t entry);
uint64_t dds3StartProcess(uint64_t name, uint64_t priority, uint64_t startdelay, uint64_t shutdowndelay,
                          uint64_t processfunc, uint64_t shutdownfunc, uint64_t data);
void ps2TextureDeferredRelease(uint64_t texture);
uint64_t ps2InterfaceLoadTexture(uint64_t name);   // 0x1CB0D8: no legacy C yet (the tests fake it)
uint32_t ps2PoolAllocate(int32_t size);
uint64_t ps2TextureQueueUpload(uint64_t record);
uint64_t ps2KernelGetFontContextIndex(void);
uint64_t sdfDevLoadFile(uint64_t path, uint64_t data_out, uint64_t size_out);
void ps2PoolRelease(uint32_t slot);
void dds3SetProcessData(uint64_t process, uint64_t data);
uint64_t dds3KillProcess(uint64_t process, uint64_t delay);
uint64_t dds3ExistProcess(uint64_t process);
void dds3LinkProcess(uint64_t parent, uint64_t process);
// No named legacy C yet (the tests fake them):
void nbMakeKaifukuPacket(uint64_t startframe, uint64_t uniqueid, uint64_t form, uint64_t type, uint64_t hp, uint64_t mp,
                         uint64_t badstat);   // 0x264010
uint64_t ps2BattleAction_00263C00(uint64_t startframe, uint64_t uniqueid, uint64_t form, uint64_t type, uint64_t hp,
                                  uint64_t mp, uint64_t badstat, uint64_t hiteff, uint64_t dead, uint64_t deadtype,
                                  uint64_t moji, uint64_t animeoff);   // nbMakeDamagePacket
void nbPanelAnalyzeStart(void);
uint64_t nbPanelStockSelect(uint64_t data, uint64_t sw);
void nbPanelAnalyzeEnd(void);
void nbUpdateOrder(void);
uint64_t ps2MovieCheckAdpcmFlag(void);
uint64_t ps2MovieStopAdpcm(void);
void nocturneInvokeBattleActionEntry(uint32_t entry, uint64_t context);
uint64_t nocturneInvokeBattleActionUpdate(uint32_t target, uint64_t context);
void nbPushAction(uint64_t type, uint64_t from, uint64_t to, uint64_t data);
uint64_t ps2BattleAction_00263918(uint64_t startframe, uint64_t uniqueid, uint64_t form, uint64_t deadtype,
                                  uint64_t deadpcm);   // nbMakeDeadVisualPacket
void ps2BattlePanelSetEnabled_00282200(uint64_t enabled);
void effPCPBossONGYDraw(uint64_t handle);        // 0x1982C8: no legacy C yet
void effPCPBossONGY2Draw(uint64_t handle);       // 0x198930
void effPCPBossBUNSINDraw(uint64_t handle);      // 0x199600
void effPCPBossBUNSIN2Draw(uint64_t handle);     // 0x199C08
uint64_t ps2BattleAction_00173CB0(uint64_t form, uint64_t kind);   // effBTLPartCreate
void effBTLPartEnd(uint64_t part);               // 0x173D28: no legacy C yet
void effBTLPartDraw(uint64_t part);              // 0x173DC8: no legacy C yet
void ps2BattlePanelSetAnalyzeUnit_00280538(uint64_t unit);
void dds3ObjectBaseOnFlag(uint64_t basic, uint64_t flag);
void dds3ObjectBaseOffFlag(uint64_t basic, uint64_t flag);
void dds3SetPosPoseSet(uint64_t basic, uint64_t pos);
void nbSetFormRot(uint64_t form, uint64_t rot);
void NegoDebugDraw(uint64_t talk);         // 0x26BF00: no legacy C yet
void NegoDebugSelectDraw(uint64_t talk);   // 0x26C0D8
uint64_t NegoDebug(uint64_t talk);         // 0x26C2D8
uint64_t nocturneInvokeBattleTalkStep(uint32_t entry, uint64_t talk);
uint64_t frDrawFontEx2(uint64_t font, uint64_t mode, uint64_t ot);
uint64_t nocturneInvokeOriginal(uint32_t entry, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2SoundPlayMidi_002C1670(uint64_t midi);
uint64_t ps2SoundFadeOut_002C2070(uint64_t midi);
uint64_t ps2SoundSelectOutput_002C20F0(uint64_t value);
uint64_t ps2SoundSelectChannel_002C1E70(uint64_t value);
void ps2SoundEnsureBank(uint64_t bank);
uint64_t ps2ResourcePacRequestFree(uint64_t request);
void ps2BattleActionRequest_00296B88(void);
void ps2BattlePanelSetOrderingOffset_002797B0(uint64_t offset);
void ps2BattlePanelSetPrimitive(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
void ps2BattlePanelSetAlpha(uint64_t mode);
void ps2BattlePanelDrawTexturedRect(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
uint64_t nocturneInvokeBattleMovePackets(uint32_t entry, uint64_t startframe, uint64_t uniqueid, uint64_t form, uint64_t target);
void nbPanelAutoHide(void);
void ps2BattlePanelHideHookA(void);
void nbCameraScriptSet1Shot(uint64_t form);
void nbCameraScriptSetBougai(uint64_t form);
void nbReturnUnit(uint64_t partyindex, uint64_t arg, uint64_t dead);         // 0x24D980: no legacy C yet
void nbMoveTarget(uint64_t partyno, uint64_t pos, uint32_t speed);          // 0x24DD10: float in f12; no legacy C
void nbMoveHome(uint64_t partyno, uint32_t speed);                          // 0x24DE40: float in f12; no legacy C
void evtSetAgeOfMoon(int32_t age);
void nocturneInvokeBattleKoukaPlayer(uint32_t entry, uint64_t queue, uint64_t packet);
uint64_t ps2ProcessGetRunTime(uint64_t process);
void dds3FadeIn(uint64_t r, uint64_t g, uint64_t b, uint64_t frames);
void dds3FadeIn2(uint64_t frames);
void nbUnitSetColor(uint64_t unit, uint64_t frames, uint64_t color);   // 0x1E3700: no legacy C yet
void ps2BattleOutcome_001E3B78(uint64_t unit, uint64_t a, uint64_t b);
void nbSetDamage(uint64_t form, uint64_t week, uint32_t range);          // 0x24DF78: float in f12; no legacy C
void nbSetDamage2(uint64_t form, uint32_t range);                       // 0x24E020: float in f12; no legacy C
void nbSetBadstatMotion(uint64_t form, uint64_t type, uint32_t range);   // 0x24E040: float in f12; no legacy C
void nbSetBadstatMotion2(uint64_t form);                                // 0x24E0E8: no legacy C
void ps2BattleFormation_0028A340(uint64_t data, uint64_t group);   // nbSetPartyFormation
void ps2BattleFormation_0028A758(uint64_t data);                   // nbSetEnemyFormation
void ps2BattleFormation_0024D8C0(uint64_t side, uint64_t stockno, uint64_t formindex);
void ps2BattleOrder_00258048(uint64_t formindex);
void ps2SoundStopEffectMidi_002C1730(uint64_t sound);
void ps2SoundVolumeHalfDown_002C20A0(void);
void ps2SoundVolumeHalfUp_002C20C8(void);
void nbUnitSetAlpha(uint64_t unit, uint64_t frames, uint64_t alpha);   // 0x1E37E8: no legacy C yet
void dds3PadAct(uint64_t mode, uint64_t pow, uint64_t frame);
void dds3FadeOut(uint64_t r, uint64_t g, uint64_t b, uint64_t frames);
uint64_t nocturneInvokeScriptFunction(uint32_t entry, uint64_t work, unsigned command);
uint32_t nocturneLibcStreamLocalAddress(void* buffer, uint32_t bytes);
void nocturneLibcStreamEndLocal(void);
}

namespace nocturne {
namespace {

template <class T>
T* fromAddress(uint64_t address)
{
    return address ? guest::table<T>(static_cast<uint32_t>(address)) : nullptr;
}

uint64_t addressOf(const void* pointer) { return guest::addressOf(pointer); }

uint64_t signExtend(int32_t value) { return static_cast<uint64_t>(static_cast<int64_t>(value)); }

} // namespace

// ---- dat ---------------------------------------------------------------------

void eff::BTLDelete(uint32_t handle) { effBTLDelete(handle); }
void eff::BTLCutDelete(uint32_t cut) { effBTLCutDelete(cut); }
void eff::BTLCutDraw(uint32_t cut) { effBTLCutDraw(signExtend(static_cast<int32_t>(cut))); }
uint32_t eff::BTLCutCreate(uint32_t effect, uint16_t cutNo, nb::Formation* form, uint32_t stat)
{
    return static_cast<uint32_t>(effBTLCutCreate(signExtend(static_cast<int32_t>(effect)), cutNo, signExtend(static_cast<int32_t>(guest::addressOf(form))), stat));
}
void eff::BTLSystemCutDelete(uint32_t cut) { effBTLSystemCutDelete(cut); }
void eff::BTLPartDelete(uint32_t part) { effBTLPartDelete(part); }
void eff::OngyokiEffectDelete(uint32_t handle) { effPCPBossONGYDelete(handle); }
void eff::OngyokiEffect2Delete(uint32_t handle) { effPCPBossONGY2Delete(handle); }
void eff::OngyokiCloneEffectDelete(uint32_t handle) { effPCPBossBUNSINDelete(handle); }
void eff::OngyokiCloneEffect2Delete(uint32_t handle) { effPCPBossBUNSIN2Delete(handle); }

namespace {
// Calls an effect's create function with its parameters in guest memory.
template <class Param>
uint32_t createWith(uint64_t (*create)(uint64_t), const Param& param)
{
    Param copy = param;
    const uint32_t address = nocturneLibcStreamLocalAddress(&copy, sizeof copy);
    const uint32_t handle = static_cast<uint32_t>(create(signExtend(static_cast<int32_t>(address))));
    nocturneLibcStreamEndLocal();
    return handle;
}
} // namespace

uint32_t eff::OngyokiEffectCreate(const OngyokiEffectParam& param) { return createWith(ps2BattleActionSkill_00198200, param); }
uint32_t eff::OngyokiEffect2Create(const OngyokiEffect2Param& param) { return createWith(ps2BattleActionSkill_00198868, param); }
uint32_t eff::OngyokiCloneEffectCreate(const OngyokiCloneEffectParam& param) { return createWith(effPCPBossBUNSINCreate, param); }
uint32_t eff::OngyokiCloneEffect2Create(const OngyokiCloneEffect2Param& param) { return createWith(effPCPBossBUNSIN2Create, param); }
int32_t cmp::RemoveDevilEx(uint16_t devil) { return static_cast<int32_t>(cmpRemoveDevilEx(devil)); }

// ---- nb ----------------------------------------------------------------------

nb::MainProcessData* nb::GetMainProcessData() { return fromAddress<MainProcessData>(nbGetMainProcessData()); }
UnitWork* nb::GetUnitWorkFromFormindex(int32_t formindex) { return fromAddress<UnitWork>(nbGetUnitWorkFromFormindex(signExtend(formindex))); }
nb::Party* nb::GetPartyFromFormindex(int32_t formindex) { return fromAddress<Party>(nbGetPartyFromFormindex(signExtend(formindex))); }

UnitWork* nb::GetUnitWorkPointer(MainProcessData& data, Party& party)
{
    return fromAddress<UnitWork>(nbGetUnitWorkPointer(addressOf(&data), addressOf(&party)));
}

// ---- evt / sdf -----------------------------------------------------------------

bool evt::BitCheck(int32_t bit) { return evtBitCheck(bit) != 0; }
void evt::BitOn(int32_t bit) { evtBitOn(bit); }
void evt::BitOff(int32_t bit) { evtBitOff(bit); }
uint32_t evt::GetAgeOfMoon() { return evtGetAgeOfMoon(); }
int32_t sdf::GetRandInt(int32_t limit) { return static_cast<int32_t>(sdfGetRandInt(nullptr, static_cast<uint32_t>(limit))); }
ee::Float sdf::GetRandFloat() { return sdfGetRandFloat(nullptr); }
uint32_t sdf::GetRand() { return sdfGetRand(nullptr); }
int32_t evt::GetAgeOfMoon16() { return static_cast<int32_t>(evtGetAgeOfMoon16()); }

// ---- scr / dds3 ---------------------------------------------------------------

uint32_t dds3::SearchProcessName(uint32_t name) { return static_cast<uint32_t>(dds3SearchProcessName(name)); }
uint32_t dds3::GetProcessData(uint32_t process) { return static_cast<uint32_t>(dds3GetProcessData(signExtend(static_cast<int32_t>(process)))); }

// ---- fr / itf / snd / mem / pac --------------------------------------------------

namespace {
uint64_t word(uint32_t address) { return signExtend(static_cast<int32_t>(address)); }   // a guest address register
} // namespace


void snd::Play(int32_t sound, int32_t volume, int32_t pan) { ps2SoundPlay(signExtend(sound), signExtend(volume), signExtend(pan)); }
uint32_t mem::HandleAllocate(int32_t size) { return ps2MemoryHandleAllocate(size); }
uint32_t mem::HandleAcquirePointer(uint32_t handle) { return ps2MemoryHandleAcquirePointer(handle); }
void mem::HandleFree(uint32_t handle) { ps2MemoryHandleFree(handle); }
void pac::RelocatePointers(uint32_t destination, uint32_t base, uint32_t table, uint32_t bytes)
{
    ps2PacRelocatePointers(word(destination), word(base), word(table), word(bytes));
}
void guest::callFunction(uint32_t entry) { nocturneInvokeMessageKutiCallback(entry); }
uint32_t tex::Load(uint32_t name) { return static_cast<uint32_t>(ps2InterfaceLoadTexture(word(name))); }
void tex::DeferredRelease(uint32_t texture) { ps2TextureDeferredRelease(word(texture)); }

// The record is staged on the guest stack, as the original passes its own.
void tex::QueueUpload(const UploadRecord& record)
{
    UploadRecord copy = record;
    uint32_t address = nocturneLibcStreamLocalAddress(&copy, sizeof copy);
    ps2TextureQueueUpload(word(address));
    nocturneLibcStreamEndLocal();
}

uint32_t mem::PoolAllocate(int32_t size) { return ps2PoolAllocate(size); }
uint32_t file::Load(uint32_t path) { return static_cast<uint32_t>(sdfDevLoadFile(word(path), 0, 0)); }
uint32_t file::Load(uint32_t path, uint32_t* data)
{
    uint32_t address = nocturneLibcStreamLocalAddress(data, sizeof *data);
    uint32_t handle = static_cast<uint32_t>(sdfDevLoadFile(word(path), word(address), 0));
    nocturneLibcStreamEndLocal();
    return handle;
}
void mem::PoolRelease(uint32_t block) { ps2PoolRelease(block); }
void dds3::SetProcessData(uint32_t process, uint32_t data) { dds3SetProcessData(word(process), word(data)); }
void dds3::KillProcess(uint32_t process, int32_t delay) { dds3KillProcess(word(process), signExtend(delay)); }
bool dds3::ExistProcess(uint32_t process) { return dds3ExistProcess(word(process)) != 0; }
void dds3::LinkProcess(uint32_t parent, uint32_t process) { dds3LinkProcess(word(parent), word(process)); }
void nb::MakeHealPackets(int32_t startframe, int32_t uniqueid, Formation* form, int32_t type, int32_t hp, int32_t mp,
                           uint32_t badstat)
{
    nbMakeKaifukuPacket(signExtend(startframe), signExtend(uniqueid), word(guest::addressOf(form)), signExtend(type),
                        signExtend(hp), signExtend(mp), word(badstat));
}
void nb::MakeDamagePackets(int32_t startframe, int32_t uniqueid, Formation* form, int32_t type, int32_t hp, int32_t mp,
                          int32_t badstat, int32_t hiteff, int32_t dead, int32_t deadtype, int32_t moji, int32_t animeoff)
{
    ps2BattleAction_00263C00(signExtend(startframe), signExtend(uniqueid), word(guest::addressOf(form)), signExtend(type),
                             signExtend(hp), signExtend(mp), signExtend(badstat), signExtend(hiteff), signExtend(dead),
                             signExtend(deadtype), signExtend(moji), signExtend(animeoff));
}
void nb::PanelAnalyzeStart() { nbPanelAnalyzeStart(); }
void nb::PanelAnalyzeEnd() { nbPanelAnalyzeEnd(); }
void nb::UpdateOrder() { nbUpdateOrder(); }
void nb::PanelAllShow() { nbPanelAllShow(); }
void eff::BTLSkillStart(int32_t skill, int32_t arg) { effBTLSkillStart(signExtend(skill), signExtend(arg)); }
void eff::BTLSkillEnd() { effBTLSkillEnd(); }
uint32_t eff::BTLBedName(int32_t skill) { return static_cast<uint32_t>(effBTLBedName(signExtend(skill))); }
uint32_t eff::BTLLoad(uint32_t data) { return static_cast<uint32_t>(effBTLLoad(word(data))); }
bool snd::BankReady(uint32_t bank) { return ps2SoundBankStatus(word(bank)) != 0; }
int32_t snd::BankStatus(uint32_t bank) { return static_cast<int32_t>(ps2SoundBankStatus(word(bank))); }
void snd::SelectOutput(int32_t piece) { ps2SoundSelectOutput_002C20F0(signExtend(piece)); }
void snd::SelectChannel(int32_t value) { ps2SoundSelectChannel_002C1E70(signExtend(value)); }
void snd::SetBankSource(uint32_t data, int32_t size) { ps2SoundSetBankSource(word(data), signExtend(size)); }
uint32_t file::Request(uint32_t path) { return static_cast<uint32_t>(fileRequest(word(path))); }
bool file::CheckEnd(uint32_t request) { return fileCheckEnd(word(request)) != 0; }
uint32_t file::GetMemHandle(uint32_t request) { return static_cast<uint32_t>(fileGetMemHandle(word(request))); }
int32_t file::GetLoadSize(uint32_t request) { return static_cast<int32_t>(fileGetLoadSize(word(request))); }
void file::RequestRelease(uint32_t request) { ps2ResourceRequestRelease(word(request)); }
int32_t nb::GetMotionActframe(ee::Float speed, Formation& form, int32_t motion)
{
    return static_cast<int32_t>(nbGetMotionActframe(word(guest::addressOf(&form)), signExtend(motion), speed.bits()));
}
ee::Float nb::GetMotionSpeed(ee::Float speed, Formation& form, int32_t motion)
{
    return ee::Float::fromBits(nbGetMotionSpeed(word(guest::addressOf(&form)), signExtend(motion), speed.bits()));
}
int32_t nb::GetMotionNo(Formation& form, int32_t motion)
{
    return static_cast<int32_t>(nbGetMotionNo(word(guest::addressOf(&form)), signExtend(motion)));
}
void nb::MakeSkillEffectPacket(int32_t startframe, int32_t timer, ActionProcessData& a, Formation& form, int32_t hiteff,
                               int32_t motiontype, int32_t skill)
{
    nbMakeSkillEffectPacket(signExtend(startframe), signExtend(timer), word(guest::addressOf(&a)), word(guest::addressOf(&form)),
                            signExtend(hiteff), signExtend(motiontype), signExtend(skill));
}
void nb::AddHitEffPacket(int32_t startframe, ActionProcessData& a, Formation& form, int32_t kind)
{
    nbAddHitEffPacket(signExtend(startframe), word(guest::addressOf(&a)), word(guest::addressOf(&form)), signExtend(kind));
}
void nb::AddHitEffPacket(int32_t startframe, int32_t uniqueid, Formation& form, int32_t kind)
{
    nbAddHitEffPacket(signExtend(startframe), signExtend(uniqueid), word(guest::addressOf(&form)), signExtend(kind));
}
void nb::MakeTargetPacket(ee::Float speed, int32_t start, ActionProcessData& a, Formation& form, uint32_t targets, int32_t kind)
{
    nbMakeTargetPacket(signExtend(start), word(guest::addressOf(&a)), word(guest::addressOf(&form)), word(targets),
                       signExtend(kind), speed.bits());
}
void eff::BTLSkillSetFormationInfo(int32_t formindex, uint32_t targets) { effBTLSkillSetFormationInfo(signExtend(formindex), word(targets)); }
void nb::StartTalkProcess(ActionProcessData& a, int32_t pformindex, int32_t eformindex, int32_t negotype, int32_t skill)
{
    nbInitNegoProcess(word(guest::addressOf(&a)), signExtend(pformindex), signExtend(eformindex), signExtend(negotype), signExtend(skill));
}
void nb::SetWaitMotion(Formation& form, int32_t motion, ee::Float speed)
{
    nbSetWaitMotion(word(guest::addressOf(&form)), signExtend(motion), speed.bits());
}
void nb::SetUnitMotion(Formation& form, int32_t motion, int32_t loop, ee::Float speed)
{
    nbSetUnitMotion(word(guest::addressOf(&form)), signExtend(motion), signExtend(loop), speed.bits());
}
void nb::PanelPressGaugeShow() { nbPanelPressGaugeShow(); }
void nb::PanelStockSelectInit() { nbPanelStockSelectInit(); }
void nb::PanelStockEnd() { nbPanelStockEnd(); }
uint32_t nb::PanelStockSelect(MainProcessData& data, int32_t sw)
{
    return static_cast<uint32_t>(nbPanelStockSelect(word(guest::addressOf(&data)), signExtend(sw)));
}
bool movie::CheckAdpcmFlag() { return ps2MovieCheckAdpcmFlag() != 0; }
void movie::StopAdpcm() { ps2MovieStopAdpcm(); }
void guest::callActionSet(uint32_t entry, uint32_t action) { nocturneInvokeBattleActionEntry(entry, word(action)); }
int32_t guest::callActionCheck(uint32_t entry, uint32_t action)
{
    return static_cast<int32_t>(nocturneInvokeBattleActionUpdate(entry, word(action)));
}
void nb::PushAction(int32_t type, int32_t from, int32_t to, int32_t data)
{
    nbPushAction(signExtend(type), signExtend(from), signExtend(to), signExtend(data));
}
void nb::MakeDeathVisualPackets(int32_t startframe, int32_t uniqueid, Formation* form, int32_t deadtype, int32_t deadpcm)
{
    ps2BattleAction_00263918(signExtend(startframe), signExtend(uniqueid), word(guest::addressOf(form)),
                             signExtend(deadtype), signExtend(deadpcm));
}
void nb::PanelSetEnabled(bool enabled) { ps2BattlePanelSetEnabled_00282200(enabled ? 1 : 0); }
void nb::PanelSetAnalyzeUnit(UnitWork* unit) { ps2BattlePanelSetAnalyzeUnit_00280538(word(guest::addressOf(unit))); }
void dds3::ObjectBaseOnFlag(uint32_t basic, uint32_t flag) { dds3ObjectBaseOnFlag(word(basic), word(flag)); }
void dds3::ObjectBaseOffFlag(uint32_t basic, uint32_t flag) { dds3ObjectBaseOffFlag(word(basic), word(flag)); }
void dds3::SetPosPoseSet(uint32_t basic, uint32_t pos) { dds3SetPosPoseSet(word(basic), word(pos)); }
void nb::SetFormRot(Formation& form, const Vec4& rot) { nbSetFormRot(word(guest::addressOf(&form)), word(guest::addressOf(&rot))); }
void nb::TalkDebugDraw(uint32_t talk) { NegoDebugDraw(word(talk)); }
void nb::TalkDebugSelectDraw(uint32_t talk) { NegoDebugSelectDraw(word(talk)); }
int32_t nb::TalkDebug(uint32_t talk) { return static_cast<int32_t>(NegoDebug(word(talk))); }
uint32_t guest::callOriginal(uint32_t entry, uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3)
{
    return static_cast<uint32_t>(nocturneInvokeOriginal(entry, word(a0), word(a1), word(a2), word(a3)));
}
void snd::PlayMidi(int32_t midi) { ps2SoundPlayMidi_002C1670(signExtend(midi)); }
void snd::FadeOutMidi(int32_t midi) { ps2SoundFadeOut_002C2070(signExtend(midi)); }
void snd::EnsureBank(uint32_t bank) { ps2SoundEnsureBank(word(bank)); }
void file::PacRequestFree(uint32_t request) { ps2ResourcePacRequestFree(word(request)); }
void file::WaitIdle() { ps2BattleActionRequest_00296B88(); }
uint32_t fr::DrawFontEx2(Request& font, int32_t mode, int32_t ot)
{
    return static_cast<uint32_t>(frDrawFontEx2(word(guest::addressOf(&font)), signExtend(mode), signExtend(ot)));
}
void nb::PanelSetOrderingOffset(int32_t offset) { ps2BattlePanelSetOrderingOffset_002797B0(signExtend(offset)); }
void nb::PanelSetPrimitive(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e, int32_t f, int32_t g, int32_t h)
{
    ps2BattlePanelSetPrimitive(signExtend(a), signExtend(b), signExtend(c), signExtend(d), signExtend(e), signExtend(f), signExtend(g),
                               signExtend(h));
}
void nb::PanelSetAlpha(int32_t mode) { ps2BattlePanelSetAlpha(signExtend(mode)); }
void nb::PanelDrawTexturedRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t u, int32_t v, int32_t tw, int32_t th,
                               uint32_t color, uint32_t texture)
{
    ps2BattlePanelDrawTexturedRect(signExtend(x), signExtend(y), signExtend(w), signExtend(h), signExtend(u), signExtend(v),
                                   signExtend(tw), signExtend(th), signExtend(static_cast<int32_t>(color)), word(texture));
}
int32_t guest::callTalkStep(uint32_t entry, uint32_t talk) { return static_cast<int32_t>(nocturneInvokeBattleTalkStep(entry, word(talk))); }
int32_t guest::callMovePackets(uint32_t entry, int32_t startframe, int32_t uniqueid, uint32_t form, uint32_t target)
{
    return static_cast<int32_t>(nocturneInvokeBattleMovePackets(entry, signExtend(startframe), signExtend(uniqueid), word(form), word(target)));
}
void nb::PanelAutoHide() { nbPanelAutoHide(); }
void nb::PanelHide() { ps2BattlePanelHideHookA(); }
void nb::CameraScriptSet1Shot(Formation* form) { nbCameraScriptSet1Shot(word(guest::addressOf(form))); }
void nb::CameraScriptSetBougai(Formation* form) { nbCameraScriptSetBougai(word(guest::addressOf(form))); }
void nb::ReturnUnit(int32_t partyindex, int32_t arg, int32_t dead) { nbReturnUnit(signExtend(partyindex), signExtend(arg), signExtend(dead)); }
void nb::MoveToTarget(ee::Float speed, int32_t partyno, const Vec4* pos)
{
    nbMoveTarget(signExtend(partyno), word(guest::addressOf(pos)), speed.bits());
}
void nb::MoveHome(ee::Float speed, int32_t partyno) { nbMoveHome(signExtend(partyno), speed.bits()); }
void eff::OngyokiEffectDraw(uint32_t handle) { effPCPBossONGYDraw(word(handle)); }
void eff::OngyokiEffect2Draw(uint32_t handle) { effPCPBossONGY2Draw(word(handle)); }
void eff::OngyokiCloneEffectDraw(uint32_t handle) { effPCPBossBUNSINDraw(word(handle)); }
void eff::OngyokiCloneEffect2Draw(uint32_t handle) { effPCPBossBUNSIN2Draw(word(handle)); }
uint32_t eff::BTLPartCreate(nb::Formation* form, int32_t kind)
{
    return static_cast<uint32_t>(ps2BattleAction_00173CB0(word(guest::addressOf(form)), signExtend(kind)));
}
void eff::BTLPartEnd(uint32_t part) { effBTLPartEnd(word(part)); }
void eff::BTLPartDraw(uint32_t part) { effBTLPartDraw(word(part)); }
void evt::SetAgeOfMoon(int32_t age) { evtSetAgeOfMoon(age); }
void guest::callEffectPlayer(uint32_t entry, uint32_t queue, uint32_t packet)
{
    nocturneInvokeBattleKoukaPlayer(entry, word(queue), word(packet));
}
int32_t dds3::GetRunTime(uint32_t process) { return static_cast<int32_t>(ps2ProcessGetRunTime(word(process))); }
void dds3::PadAct(uint32_t mode, uint8_t pow, uint32_t frame) { dds3PadAct(mode, pow, frame); }
void dds3::FadeIn(int32_t r, int32_t g, int32_t b, int32_t frames) { dds3FadeIn(signExtend(r), signExtend(g), signExtend(b), signExtend(frames)); }
void dds3::FadeOut(int32_t r, int32_t g, int32_t b, int32_t frames) { dds3FadeOut(signExtend(r), signExtend(g), signExtend(b), signExtend(frames)); }
void dds3::FadeIn2(int32_t frames) { dds3FadeIn2(signExtend(frames)); }
void nb::UnitSetColor(uint32_t unit, int32_t frames, uint32_t color) { nbUnitSetColor(word(unit), signExtend(frames), word(color)); }
void nb::UnitSetAlpha(uint32_t unit, int32_t frames, uint32_t alpha) { nbUnitSetAlpha(word(unit), signExtend(frames), word(alpha)); }
void nb::SetDamage(Formation& form, ee::Float range, int32_t week) { nbSetDamage(word(guest::addressOf(&form)), signExtend(week), range.bits()); }
void nb::SetDamage2(Formation& form, ee::Float range) { nbSetDamage2(word(guest::addressOf(&form)), range.bits()); }
void nb::SetBadstatMotion(Formation& form, int32_t type, ee::Float range)
{
    nbSetBadstatMotion(word(guest::addressOf(&form)), signExtend(type), range.bits());
}
void nb::SetBadstatMotion2(Formation& form) { nbSetBadstatMotion2(word(guest::addressOf(&form))); }
void nb::UnitSetMotionWords(uint32_t unit, int16_t a, int16_t b) { ps2BattleOutcome_001E3B78(word(unit), signExtend(a), signExtend(b)); }
void nb::SetPartyFormation(MainProcessData& data, uint32_t group) { ps2BattleFormation_0028A340(word(guest::addressOf(&data)), group); }
void nb::SetEnemyFormation(MainProcessData& data) { ps2BattleFormation_0028A758(word(guest::addressOf(&data))); }
void nb::SummonUnit(int32_t side, int32_t stockno, int32_t formindex)
{
    ps2BattleFormation_0024D8C0(signExtend(side), signExtend(stockno), signExtend(formindex));
}
void nb::AddToOrder(int32_t formindex) { ps2BattleOrder_00258048(signExtend(formindex)); }
void snd::VolumeHalfDown() { ps2SoundVolumeHalfDown_002C20A0(); }
void snd::VolumeHalfUp() { ps2SoundVolumeHalfUp_002C20C8(); }
void snd::StopEffectMidi(uint32_t sound) { ps2SoundStopEffectMidi_002C1730(word(sound)); }
int32_t guest::callCommand(uint32_t entry) { return static_cast<int32_t>(nocturneInvokeScriptFunction(entry, 0, 1)); }
int32_t dds3::GetFrameIndex() { return static_cast<int32_t>(ps2KernelGetFontContextIndex()); }
uint32_t dds3::StartProcess(uint32_t name, int32_t priority, int32_t startdelay, int32_t shutdowndelay,
                            uint32_t processfunc, uint32_t shutdownfunc, uint32_t data)
{
    return static_cast<uint32_t>(dds3StartProcess(word(name), signExtend(priority), signExtend(startdelay),
                                                  signExtend(shutdowndelay), word(processfunc), word(shutdownfunc),
                                                  word(data)));
}

// ---- diagnostics / traps -----------------------------------------------------

void diag::print(Message message, int64_t a, int64_t b, int64_t c, int64_t d, int64_t e)
{
    if (static_cast<uint32_t>(message) == 0)
        return;   // a print this version doesn't have (optionalAddr)
    ps2LibcPrintf(static_cast<uint32_t>(message), static_cast<uint64_t>(a), static_cast<uint64_t>(b),
                  static_cast<uint64_t>(c), static_cast<uint64_t>(d), static_cast<uint64_t>(e));
}

void divideByZeroTrap() { nocturneCompilerArithmeticTrap(7); }

} // namespace nocturne
