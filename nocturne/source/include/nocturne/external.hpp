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
int32_t GetParam(const UnitWork& unit, Param paratype);  // stat incl. Mitama bonus, clamped 1..40
int32_t Get3Zokusei(const UnitWork& unit);               // raw alignment: -1, 0 or 1
int32_t GetSakePow(const UnitWork& unit);                // evasion power ("sake" = 避け)
int32_t GetMagicHitPow(const UnitWork& unit);            // magic accuracy power
void AddHp(UnitWork& unit, int32_t amount);
void AddMp(UnitWork& unit, int32_t amount);
void SetBadStat(UnitWork& unit, uint32_t badstat);
void ResetBadStat(UnitWork& unit, uint32_t badstat);
bool CheckSyojiSkill(const UnitWork& unit, int32_t skill); // does the unit own this skill
bool CheckSkillInParty(int32_t skill);                     // does any active party member
int32_t GetPlayerLevel();
bool BossRashChk(int32_t encno);                           // boss refight (reduced rewards)
} // namespace dat

namespace nb {
MainProcessData* GetMainProcessData();
UnitWork* GetUnitWorkFromFormindex(int32_t formindex);   // null for an empty slot
Party* GetPartyFromFormindex(int32_t formindex);
UnitWork* GetUnitWorkPointer(MainProcessData& data, Party& party);
Attribute GetNormalSkillAttr(int32_t nskill);
Affinity GetAisyo(int32_t nskill, int32_t formindex, Attribute attr);
bool HatudoCheckSkill(const UnitWork& unit, int32_t skill);  // does a passive activate now ("hatudo" = 発動)
ee::Float GetHojoRitu(int32_t formindex, int32_t type);      // buff multiplier
uint32_t GetDevilFormatFlag(int32_t formindex);
uint32_t GetBadStat(int32_t formindex);
bool CheckFormationPlayerSide(int32_t formindex);
int32_t GetUnitID(const UnitWork& unit);                     // model ID, 0 = default model
} // namespace nb

namespace evt {
bool BitCheck(int32_t bit);
uint32_t GetAgeOfMoon();      // 0..15, 0 = new, 8 = full Kagutsuchi
} // namespace evt

namespace sdf {
int32_t GetRandInt(int32_t limit);   // uniform in [0, limit) from the default RNG
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
};
void print(Message message, int32_t a = 0, int32_t b = 0, int32_t c = 0, int32_t d = 0, int32_t e = 0);
} // namespace diag

// The original code divides with a trap on zero (MIPS BREAK 7).
[[noreturn]] void divideByZeroTrap();

} // namespace nocturne
