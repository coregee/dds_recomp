// Game functions the rewritten modules call but which have not been rewritten
// yet. Each is implemented by a bridge to the legacy recovered C (or, in the
// tests, by deterministic fakes). As modules are rewritten, their functions
// move out of this header into a proper module header.
//
// Signatures use the original names and argument meanings from the HD
// remaster, with typed pointers in place of raw addresses.
#pragma once

#include <cstdint>

#include "nocturne/battle/process.hpp"
#include "nocturne/data/records.hpp"
#include "nocturne/data/types.hpp"
#include "nocturne/ee/float.hpp"

namespace nocturne {

namespace dat {
bool BossRashChk(int32_t encno);                           // boss refight (reduced rewards)
} // namespace dat

namespace nb {
MainProcessData* GetMainProcessData();
UnitWork* GetUnitWorkFromFormindex(int32_t formindex);   // null for an empty slot
Party* GetPartyFromFormindex(int32_t formindex);
UnitWork* GetUnitWorkPointer(MainProcessData& data, Party& party);
} // namespace nb

// The script VM (flowscript), as seen by script commands.
namespace scr {
uint32_t GetData();                 // the running script's data (for AI scripts: ActionProcessData)
int32_t GetIntPara(int32_t index);  // an integer argument
void SetIntReturnValue(int32_t value);
int32_t GetMessageHandle();         // the script's message window, or negative
} // namespace scr

// Window panels (itfPanel). Panels are addresses of itf::Panel records.
namespace itf {
uint32_t PnlRegist2(int32_t type, uint32_t texture);
void PnlSetPosition(uint32_t panel, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t z);
void PnlSetPositionOffset(uint32_t panel, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t z);
void PnlSetColor(uint32_t panel, int32_t red, int32_t green, int32_t blue, int32_t alpha);
void PnlRelease(uint32_t panel);
} // namespace itf

// Textures.
namespace tex {
uint32_t Load(uint32_t name);              // (0x1CB0D8) load a .TMX file into a texture
void DeferredRelease(uint32_t texture);    // ps2TextureDeferredRelease

// A rectangle of pixels to send to video memory (ps2TextureQueueUpload).
struct UploadRecord {
    uint32_t pixels;
    uint32_t unknown_04;        // not set by the font engine
    uint8_t flags;              // 2: free the pixels once sent
    uint8_t psm;                // pixel format (20: 4 bits per pixel)
    uint16_t width;             // of the destination, in pixels
    uint32_t base;              // the destination, in words
    uint16_t x, y, w, h;
};
static_assert(sizeof(UploadRecord) == 24);
void QueueUpload(const UploadRecord& record);
} // namespace tex

namespace snd {
void Play(int32_t sound, int32_t volume, int32_t pan);   // ps2SoundPlay
} // namespace snd

// Movable memory blocks (sdfMemHandle).
namespace mem {
uint32_t PoolAllocate(int32_t size);      // ps2PoolAllocate: a small block
void PoolRelease(uint32_t block);         // ps2PoolRelease
uint32_t HandleAllocate(int32_t size);
uint32_t HandleAcquirePointer(uint32_t handle);
void HandleFree(uint32_t handle);
} // namespace mem

namespace file {
uint32_t Load(uint32_t path);   // sdfDevLoadFile: a whole file in a new memory handle
uint32_t Load(uint32_t path, uint32_t* data);   // ... and where it is
} // namespace file

namespace pac {
// Turn the offsets listed in a relocation table into addresses (base + offset).
void RelocatePointers(uint32_t destination, uint32_t base, uint32_t table, uint32_t bytes);
} // namespace pac

namespace guest {
void callFunction(uint32_t entry);   // call original code through a function pointer
int32_t callCommand(uint32_t entry); // a script command not rewritten yet
} // namespace guest

// Engine process table.
namespace dds3 {
uint32_t SearchProcessName(uint32_t name);   // name: address of a C string
uint32_t GetProcessData(uint32_t process);   // the process's data, as an address
// Starts a process: `processfunc` runs every frame, `shutdownfunc` at its
// end (both original code addresses).
uint32_t StartProcess(uint32_t name, int32_t priority, int32_t startdelay, int32_t shutdowndelay,
                      uint32_t processfunc, uint32_t shutdownfunc, uint32_t data);
int32_t GetFrameIndex();   // which of the two display buffers is being built (0x100418)
void SetProcessData(uint32_t process, uint32_t data);
void KillProcess(uint32_t process, int32_t delay);
bool ExistProcess(uint32_t process);
int32_t GetRunTime(uint32_t process);
void FadeIn(int32_t r, int32_t g, int32_t b, int32_t frames);    // from the color
void FadeOut(int32_t r, int32_t g, int32_t b, int32_t frames);   // to the color
} // namespace dds3

namespace evt {
bool BitCheck(int32_t bit);
void BitOn(int32_t bit);
void BitOff(int32_t bit);
uint32_t GetAgeOfMoon();      // 0..15, 0 = new, 8 = full Kagutsuchi
int32_t GetAgeOfMoon16();     // the phase in sixteenths (tentative)
} // namespace evt

namespace sdf {
int32_t GetRandInt(int32_t limit);   // uniform in [0, limit) from the default RNG
uint32_t GetRand();                  // the raw 32-bit value
ee::Float GetRandFloat();            // uniform in [0, 1)
} // namespace sdf

// Original debug printf. Messages are identified by the address of their
// format string so a host build can print the original Japanese text.
namespace diag {
enum class Message : uint32_t {
    Critical         = 0x005449c0, // "critical p:%d, z = %d, a = %d"
    PhysicalHitRate  = 0x005449e0, // 物理ヒット率 = %d   (physical hit rate)
    MagicHitRate     = 0x005449f8, // 魔法ヒット率 = %d   (magic hit rate)
    StoneShatterRate = 0x00544bf8, // 石化一撃確率 = %d   (stone one-hit chance)
    AilmentRecovery  = 0x00544c10, // バットステータス回復確率 = %d
    FirstStrike      = 0x00544d70, // 先制率 Plv, Elv, Tbl, z, rnd
    BackAttack       = 0x00544da8, // バックアタック確率 X, Y, B, rand
    EscapeRate       = 0x00544de0, // 逃走率 = %d
    ConsecutiveRate  = 0x00544df0, // "renzoku ritu = %d, index = %d"
    Miss             = 0x00551140, // "MISS!!"
    AttackRatio      = 0x00544d00, // "atkritu = %f"
    DefenseRatio     = 0x00544d10, // "defritu = %f"
    MagicHeal        = 0x00544d30, // 回復 waza = %d, atkritu = %f 回復値=%d (heal: power, ratio, amount)
    StingerVsBoss    = 0x00544b48, // "DANTE SUTING BOSS NG..."
    CurseKillBlocked = 0x00544b68, // "SIBAE JYUSATU TAISEI ARI NG..." (target resists Death)
    PestilenceNoPoison = 0x00544b88, // "PESTO POISON NASI NG..."
    AilmentChance    = 0x00544ba8, // バッドステータス反映確率 waza:%d aisyo:%d ritu:%d rnd:%d
    AilmentCureRate  = 0x00544be8, // "bad ritu:%f"
    ResetLevel       = 0x00543188, // "YAMI-B Lv:%d"
    ResetExp         = 0x00543198, // "YAMI-B Exp:%d"
    FusionAccident   = 0x0053caf8, // "Combione accident!!!..." (passed the accident type)
    CompendiumFull   = 0x0053d7e8, // "****** FATAL!! The encyclopedia record is bound to burst!!!"
    AiActionTable    = 0x00545830, // "Koukatbl = %d" (the action chosen)
    AiTable          = 0x00545840, // "AItbl = %d"
    AiNoSkill        = 0x005457d8, // "no skill"
    AiNoTarget       = 0x005457e8, // "taisyo nashi!!!" (no target)
    SkillRewritten   = 0x00544170, // スキル書き換え!! (normal attack data rewritten)
    NoMessagePage    = 0x00535a80, // "itfMesMngRequestMessage() escape 1" (a message with no pages)
    NotASelection    = 0x00535aa8, // "itfMesMngRequestSelect() - Invalid Type : %d"
    NameTranslate    = 0x00535998, // "NAME[%d] : Translate." (an entered name's glyphs loaded)
    NameRestore      = 0x005359b0, // "NAME[%d] : Restore." (and freed)
    ProcedureStart   = 0x0052e270, // "procedure start <%s>"
    ProcedureEnd     = 0x0052e2b8, // "procedure end <%s>"
    ScriptsBefore    = 0x0052e2e0, // "before = %d" (scripts running)
    ScriptRelease    = 0x0052e2f0, // "scrAllReleaseScript <%s>"
    ScriptKillProcess = 0x0052e310, // "dds3KillProcess"
    ScriptReleaseWork = 0x0052e328, // "scrReleaseScript"
    ScriptsAfter     = 0x0052e340, // "after = %d"
    ScriptRunWithoutProcess = 0x0052f5e8, // SCR_RUN from a script without a process (EUC-JP)
    ScriptPut        = 0x0052f588, // "put -> %d"
    ScriptPuts       = 0x0052f5a8, // "puts -> %s"
};
// Integer arguments are passed sign-extended; %f arguments are ee::Double bits.
void print(Message message, int64_t a = 0, int64_t b = 0, int64_t c = 0, int64_t d = 0, int64_t e = 0);
} // namespace diag

// The original code divides with a trap on zero (MIPS BREAK 7).
[[noreturn]] void divideByZeroTrap();

} // namespace nocturne
