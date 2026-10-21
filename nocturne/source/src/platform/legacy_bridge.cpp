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
int32_t datBossRashChk(int32_t eid);
uint32_t evtBitCheck(int32_t no);
uint32_t evtGetAgeOfMoon(void);
uint32_t sdfGetRandInt(uint32_t* state, uint32_t limit);
uint32_t sdfGetRand(uint32_t* state);
float sdfGetRandFloat(uint32_t* state);
uint64_t ps2LibcPrintf(uint64_t format, ...);
struct datUnitWork_PS2;
int8_t cmbGetHeartsParam(int8_t id, int8_t index);
void cmbSubHeartsParam(uint8_t id, datUnitWork_PS2* unit);
void ps2HeartsAddParam(uint8_t id, datUnitWork_PS2* unit);
uint8_t cmbGetPlayerRaceID(datUnitWork_PS2* unit);
int32_t fclEncycRegist(datUnitWork_PS2* unit, int32_t overwrite);
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

datUnitWork_PS2* legacy(UnitWork& unit) { return reinterpret_cast<datUnitWork_PS2*>(&unit); }

uint64_t signExtend(int32_t value) { return static_cast<uint64_t>(static_cast<int64_t>(value)); }

} // namespace

// ---- dat ---------------------------------------------------------------------

bool dat::BossRashChk(int32_t encno) { return datBossRashChk(encno) != 0; }

// ---- nb ----------------------------------------------------------------------

nb::MainProcessData* nb::GetMainProcessData() { return fromAddress<MainProcessData>(nbGetMainProcessData()); }
UnitWork* nb::GetUnitWorkFromFormindex(int32_t formindex) { return fromAddress<UnitWork>(nbGetUnitWorkFromFormindex(signExtend(formindex))); }
nb::Party* nb::GetPartyFromFormindex(int32_t formindex) { return fromAddress<Party>(nbGetPartyFromFormindex(signExtend(formindex))); }

UnitWork* nb::GetUnitWorkPointer(MainProcessData& data, Party& party)
{
    return fromAddress<UnitWork>(nbGetUnitWorkPointer(addressOf(&data), addressOf(&party)));
}

// ---- cmb (Magatama) / fcl (compendium) -------------------------------------------

int8_t cmb::GetHeartsParam(int8_t id, int8_t stat) { return cmbGetHeartsParam(id, stat); }
void cmb::SubHeartsParam(uint8_t id, UnitWork& unit) { cmbSubHeartsParam(id, legacy(unit)); }
void cmb::HeartsAddParam(uint8_t id, UnitWork& unit) { ps2HeartsAddParam(id, legacy(unit)); }
uint8_t cmb::GetPlayerRaceID(UnitWork& unit) { return cmbGetPlayerRaceID(legacy(unit)); }
int32_t fcl::EncycRegist(UnitWork& unit, bool overwrite) { return fclEncycRegist(legacy(unit), overwrite ? 1 : 0); }

// ---- evt / sdf -----------------------------------------------------------------

bool evt::BitCheck(int32_t bit) { return evtBitCheck(bit) != 0; }
uint32_t evt::GetAgeOfMoon() { return evtGetAgeOfMoon(); }
int32_t sdf::GetRandInt(int32_t limit) { return static_cast<int32_t>(sdfGetRandInt(nullptr, static_cast<uint32_t>(limit))); }
ee::Float sdf::GetRandFloat() { return sdfGetRandFloat(nullptr); }
uint32_t sdf::GetRand() { return sdfGetRand(nullptr); }

// ---- diagnostics / traps -----------------------------------------------------

void diag::print(Message message, int64_t a, int64_t b, int64_t c, int64_t d, int64_t e)
{
    ps2LibcPrintf(static_cast<uint32_t>(message), static_cast<uint64_t>(a), static_cast<uint64_t>(b),
                  static_cast<uint64_t>(c), static_cast<uint64_t>(d), static_cast<uint64_t>(e));
}

void divideByZeroTrap() { nocturneCompilerArithmeticTrap(7); }

} // namespace nocturne
