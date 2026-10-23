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
void nbDispJyokyoHelp(uint64_t msgid, uint64_t no, uint64_t var_id, uint64_t var_ind);   // 0x2892A8
uint64_t ps2BattleAction_00263C00(uint64_t startframe, uint64_t uniqueid, uint64_t form, uint64_t type, uint64_t hp,
                                  uint64_t mp, uint64_t badstat, uint64_t hiteff, uint64_t dead, uint64_t deadtype,
                                  uint64_t moji, uint64_t animeoff);   // nbMakeDamagePacket
void nbPanelAnalyzeStart(void);
uint64_t nbPanelStockSelect(uint64_t data, uint64_t sw);
uint64_t ps2MovieCheckAdpcmFlag(void);
uint64_t ps2MovieStopAdpcm(void);
void nocturneInvokeBattleActionEntry(uint32_t entry, uint64_t context);
uint64_t nocturneInvokeBattleActionUpdate(uint32_t target, uint64_t context);
void nbPushAction(uint64_t type, uint64_t from, uint64_t to, uint64_t data);
uint64_t ps2BattleAction_00263918(uint64_t startframe, uint64_t uniqueid, uint64_t form, uint64_t deadtype,
                                  uint64_t deadpcm);   // nbMakeDeadVisualPacket
void ps2BattlePanelSetEnabled_00282200(uint64_t enabled);
uint64_t ps2ProcessGetRunTime(uint64_t process);
void dds3FadeIn(uint64_t r, uint64_t g, uint64_t b, uint64_t frames);
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

uint32_t eff::PCPBossONGYCreate(const PCPBossONGYParam& param) { return createWith(ps2BattleActionSkill_00198200, param); }
uint32_t eff::PCPBossONGY2Create(const PCPBossONGY2Param& param) { return createWith(ps2BattleActionSkill_00198868, param); }
uint32_t eff::PCPBossBUNSINCreate(const PCPBossBUNSINParam& param) { return createWith(effPCPBossBUNSINCreate, param); }
uint32_t eff::PCPBossBUNSIN2Create(const PCPBossBUNSIN2Param& param) { return createWith(effPCPBossBUNSIN2Create, param); }
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
void nb::MakeKaifukuPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t type, int32_t hp, int32_t mp,
                           uint32_t badstat)
{
    nbMakeKaifukuPacket(signExtend(startframe), signExtend(uniqueid), word(guest::addressOf(form)), signExtend(type),
                        signExtend(hp), signExtend(mp), word(badstat));
}
void nb::DispJyokyoHelp(int32_t msgid, int32_t no, int32_t var_id, int32_t var_ind)
{
    nbDispJyokyoHelp(signExtend(msgid), signExtend(no), signExtend(var_id), signExtend(var_ind));
}
void nb::MakeDamagePacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t type, int32_t hp, int32_t mp,
                          int32_t badstat, int32_t hiteff, int32_t dead, int32_t deadtype, int32_t moji, int32_t animeoff)
{
    ps2BattleAction_00263C00(signExtend(startframe), signExtend(uniqueid), word(guest::addressOf(form)), signExtend(type),
                             signExtend(hp), signExtend(mp), signExtend(badstat), signExtend(hiteff), signExtend(dead),
                             signExtend(deadtype), signExtend(moji), signExtend(animeoff));
}
void nb::PanelAnalyzeStart() { nbPanelAnalyzeStart(); }
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
void nb::MakeDeadVisualPacket(int32_t startframe, int32_t uniqueid, Formation* form, int32_t deadtype, int32_t deadpcm)
{
    ps2BattleAction_00263918(signExtend(startframe), signExtend(uniqueid), word(guest::addressOf(form)),
                             signExtend(deadtype), signExtend(deadpcm));
}
void nb::PanelSetEnabled(bool enabled) { ps2BattlePanelSetEnabled_00282200(enabled ? 1 : 0); }
int32_t dds3::GetRunTime(uint32_t process) { return static_cast<int32_t>(ps2ProcessGetRunTime(word(process))); }
void dds3::PadAct(uint32_t mode, uint8_t pow, uint32_t frame) { dds3PadAct(mode, pow, frame); }
void dds3::FadeIn(int32_t r, int32_t g, int32_t b, int32_t frames) { dds3FadeIn(signExtend(r), signExtend(g), signExtend(b), signExtend(frames)); }
void dds3::FadeOut(int32_t r, int32_t g, int32_t b, int32_t frames) { dds3FadeOut(signExtend(r), signExtend(g), signExtend(b), signExtend(frames)); }
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
    ps2LibcPrintf(static_cast<uint32_t>(message), static_cast<uint64_t>(a), static_cast<uint64_t>(b),
                  static_cast<uint64_t>(c), static_cast<uint64_t>(d), static_cast<uint64_t>(e));
}

void divideByZeroTrap() { nocturneCompilerArithmeticTrap(7); }

} // namespace nocturne
