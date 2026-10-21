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

// ---- evt / sdf -----------------------------------------------------------------

bool evt::BitCheck(int32_t bit) { return evtBitCheck(bit) != 0; }
uint32_t evt::GetAgeOfMoon() { return evtGetAgeOfMoon(); }
int32_t sdf::GetRandInt(int32_t limit) { return static_cast<int32_t>(sdfGetRandInt(nullptr, static_cast<uint32_t>(limit))); }
ee::Float sdf::GetRandFloat() { return sdfGetRandFloat(nullptr); }

// ---- diagnostics / traps -----------------------------------------------------

void diag::print(Message message, int64_t a, int64_t b, int64_t c, int64_t d, int64_t e)
{
    ps2LibcPrintf(static_cast<uint32_t>(message), static_cast<uint64_t>(a), static_cast<uint64_t>(b),
                  static_cast<uint64_t>(c), static_cast<uint64_t>(d), static_cast<uint64_t>(e));
}

void divideByZeroTrap() { nocturneCompilerArithmeticTrap(7); }

} // namespace nocturne
