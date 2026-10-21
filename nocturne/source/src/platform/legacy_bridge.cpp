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

struct datUnitWork_PS2; // legacy name for nocturne::UnitWork

extern "C" {
uint64_t nbGetMainProcessData(void);
uint64_t nbGetUnitWorkFromFormindex(uint64_t formindex);
uint64_t nbGetPartyFromFormindex(uint64_t formindex);
uint64_t nbGetUnitWorkPointer(uint64_t main_data, uint64_t party);
uint64_t nbGetNormalSkillAttr(uint64_t skill);
uint64_t nbGetAisyo(uint64_t skill, uint64_t target, uint64_t attribute);
int32_t nbHatudoCheckSkill(datUnitWork_PS2* work, int32_t skill);
float nbGetHojoRitu(uint64_t formation, uint64_t type);
uint64_t nbGetDevilFormatFlag(uint64_t form);
uint64_t nbGetBadStat(uint64_t form_index);
uint64_t nbCheckFormationPlayerSide(uint64_t form_index);
uint64_t nbGetUnitID(uint64_t work);
uint64_t datGet3Zokusei(uint64_t unit);
int32_t datGetParam(datUnitWork_PS2* work, int32_t paratype);
uint32_t datAddHp(datUnitWork_PS2* work, int32_t hp);
uint32_t datAddMp(datUnitWork_PS2* work, int32_t mp);
void datSetBadStat(datUnitWork_PS2* work, uint32_t badstat);
void datResetBadStat(datUnitWork_PS2* work, uint32_t badstat);
int32_t datCheckSyojiSkill(datUnitWork_PS2* work, uint32_t skill);
int32_t datCheckSkillInParty(int32_t skillid);
int32_t datGetPlayerLevel(void);
int32_t datBossRashChk(int32_t eid);
uint64_t ps2UnitMagicHitPower_00242CB0(uint64_t unit);   // datGetMagicHitPow
uint64_t ps2UnitEvasionPower_00242D50(uint64_t unit);    // datGetSakePow
uint32_t evtBitCheck(int32_t no);
uint32_t evtGetAgeOfMoon(void);
uint32_t sdfGetRandInt(uint32_t* state, uint32_t limit);
float sdfGetRandFloat(uint32_t* state);
uint64_t ps2LibcPrintf(uint64_t format, ...);
[[noreturn]] void nocturneCompilerArithmeticTrap(uint32_t code);
}

namespace nocturne {
namespace {

template <class T>
T* fromAddress(uint64_t address)
{
    return address ? guest::table<T>(static_cast<uint32_t>(address)) : nullptr;
}

uint64_t addressOf(const void* pointer) { return guest::addressOf(pointer); }

datUnitWork_PS2* legacy(const UnitWork& unit)
{
    return const_cast<datUnitWork_PS2*>(reinterpret_cast<const datUnitWork_PS2*>(&unit));
}

uint64_t signExtend(int32_t value) { return static_cast<uint64_t>(static_cast<int64_t>(value)); }

} // namespace

// ---- dat ---------------------------------------------------------------------

int32_t dat::GetParam(const UnitWork& unit, Param paratype) { return datGetParam(legacy(unit), static_cast<int32_t>(paratype)); }
int32_t dat::Get3Zokusei(const UnitWork& unit) { return static_cast<int32_t>(datGet3Zokusei(addressOf(&unit))); }
int32_t dat::GetSakePow(const UnitWork& unit) { return static_cast<int32_t>(ps2UnitEvasionPower_00242D50(addressOf(&unit))); }
int32_t dat::GetMagicHitPow(const UnitWork& unit) { return static_cast<int32_t>(ps2UnitMagicHitPower_00242CB0(addressOf(&unit))); }
void dat::AddHp(UnitWork& unit, int32_t amount) { datAddHp(legacy(unit), amount); }
void dat::AddMp(UnitWork& unit, int32_t amount) { datAddMp(legacy(unit), amount); }
void dat::SetBadStat(UnitWork& unit, uint32_t badstat) { datSetBadStat(legacy(unit), badstat); }
void dat::ResetBadStat(UnitWork& unit, uint32_t badstat) { datResetBadStat(legacy(unit), badstat); }
bool dat::CheckSyojiSkill(const UnitWork& unit, int32_t skill) { return datCheckSyojiSkill(legacy(unit), static_cast<uint32_t>(skill)) != 0; }
bool dat::CheckSkillInParty(int32_t skill) { return datCheckSkillInParty(skill) != 0; }
int32_t dat::GetPlayerLevel() { return datGetPlayerLevel(); }
bool dat::BossRashChk(int32_t encno) { return datBossRashChk(encno) != 0; }

// ---- nb ----------------------------------------------------------------------

nb::MainProcessData* nb::GetMainProcessData() { return fromAddress<MainProcessData>(nbGetMainProcessData()); }
UnitWork* nb::GetUnitWorkFromFormindex(int32_t formindex) { return fromAddress<UnitWork>(nbGetUnitWorkFromFormindex(signExtend(formindex))); }
nb::Party* nb::GetPartyFromFormindex(int32_t formindex) { return fromAddress<Party>(nbGetPartyFromFormindex(signExtend(formindex))); }

UnitWork* nb::GetUnitWorkPointer(MainProcessData& data, Party& party)
{
    return fromAddress<UnitWork>(nbGetUnitWorkPointer(addressOf(&data), addressOf(&party)));
}

Attribute nb::GetNormalSkillAttr(int32_t nskill)
{
    return static_cast<Attribute>(static_cast<int32_t>(nbGetNormalSkillAttr(signExtend(nskill))));
}

Affinity nb::GetAisyo(int32_t nskill, int32_t formindex, Attribute attr)
{
    uint64_t raw = nbGetAisyo(signExtend(nskill), signExtend(formindex), signExtend(static_cast<int32_t>(attr)));
    return Affinity{static_cast<uint32_t>(raw)};
}

bool nb::HatudoCheckSkill(const UnitWork& unit, int32_t skill) { return nbHatudoCheckSkill(legacy(unit), skill) != 0; }
ee::Float nb::GetHojoRitu(int32_t formindex, int32_t type) { return nbGetHojoRitu(signExtend(formindex), signExtend(type)); }
uint32_t nb::GetDevilFormatFlag(int32_t formindex) { return static_cast<uint32_t>(nbGetDevilFormatFlag(signExtend(formindex))); }
uint32_t nb::GetBadStat(int32_t formindex) { return static_cast<uint32_t>(nbGetBadStat(signExtend(formindex))); }
bool nb::CheckFormationPlayerSide(int32_t formindex) { return nbCheckFormationPlayerSide(signExtend(formindex)) != 0; }
int32_t nb::GetUnitID(const UnitWork& unit) { return static_cast<int32_t>(nbGetUnitID(addressOf(&unit))); }

// ---- evt / sdf -----------------------------------------------------------------

bool evt::BitCheck(int32_t bit) { return evtBitCheck(bit) != 0; }
uint32_t evt::GetAgeOfMoon() { return evtGetAgeOfMoon(); }
int32_t sdf::GetRandInt(int32_t limit) { return static_cast<int32_t>(sdfGetRandInt(nullptr, static_cast<uint32_t>(limit))); }
ee::Float sdf::GetRandFloat() { return sdfGetRandFloat(nullptr); }

// ---- diagnostics / traps -----------------------------------------------------

void diag::print(Message message, int32_t a, int32_t b, int32_t c, int32_t d, int32_t e)
{
    ps2LibcPrintf(static_cast<uint32_t>(message), signExtend(a), signExtend(b), signExtend(c), signExtend(d), signExtend(e));
}

void divideByZeroTrap() { nocturneCompilerArithmeticTrap(7); }

} // namespace nocturne
