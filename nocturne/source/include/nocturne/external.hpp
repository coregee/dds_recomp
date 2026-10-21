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
} // namespace scr

// Engine process table.
namespace dds3 {
uint32_t SearchProcessName(uint32_t name);   // name: address of a C string
uint32_t GetProcessData(uint32_t process);   // the process's data, as an address
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
};
// Integer arguments are passed sign-extended; %f arguments are ee::Double bits.
void print(Message message, int64_t a = 0, int64_t b = 0, int64_t c = 0, int64_t d = 0, int64_t e = 0);
} // namespace diag

// The original code divides with a trap on zero (MIPS BREAK 7).
[[noreturn]] void divideByZeroTrap();

} // namespace nocturne
