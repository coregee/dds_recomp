// The battle's system effects (original unit: effBattleSystem): their
// lengths. Rewritten from the original instructions.
#include "nocturne/effect/system.hpp"

#include <cstddef>

#include "nocturne/address.hpp"
#include "nocturne/effect/cut.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::eff {

static_assert(sizeof(SystemEffect) == 0xc && offsetof(SystemEffect, pFormation) == 8);

namespace {

constexpr uint32_t kFamilies = addr(0x0031bf00);   // the family table
constexpr uint32_t kFamilySize = 56;
constexpr uint32_t kGetLength = 0x14;              // a row's getLength

uint32_t word(uint32_t address) { return *guest::table<const uint32_t>(address); }

// effBTLSys_Shock_GetLength @ 0x00170150
// effBTLSys_Freeze_GetLength @ 0x001703A8
// effBTLSys_Sleep_GetLength @ 0x00170590
// effBTLSys_Panic_GetLength @ 0x00170778
// effBTLSys_Bind_GetLength @ 0x00170960
// effBTLSys_Close_GetLength @ 0x00170C00
// effBTLSys_Poison_GetLength @ 0x00170E00
// effBTLSys_Charm_GetLength @ 0x00171060
// effBTLSys_Paralyze_GetLength @ 0x00171268
// effBTLSys_Fly_GetLength @ 0x001713D0
// effBTLSys_Stone_GetLength @ 0x00171578
// effBTLSys_Curse_GetLength @ 0x00171728
// effBTLSys_CurseCAMP_GetLength @ 0x00171978
// The ailments' effects loop: no length.
uint32_t ailmentLength(uint32_t) { return 0; }

// effBTLSys_Stone_Dead_GetLength @ 0x00171C40
uint32_t shatterLength(uint32_t) { return 50; }

// effBTLSys_Hansya_GetLength @ 0x001720F0
uint32_t repelLength(uint32_t) { return 15; }

// effBTLSys_Kyusyuu_GetLength @ 0x00172590
uint32_t drainLength(uint32_t) { return 25; }

// effBTLSys_Attack_GetLength @ 0x00172D18
// effBTLSys_AttackC_GetLength @ 0x001735E0
uint32_t attackLength(uint32_t) { return 20; }

// effBTLSys_Return_GetLength @ 0x00172718
// effBTLSys_Encount_GetLength @ 0x00173768
// effBTLSys_Nego_Kaihuku_GetLength @ 0x001738F8
// effBTLSys_Nego_Kyusyu_GetLength @ 0x00173A88
// effBTLSys_Nego_Stone_GetLength @ 0x00173C18
// These play a cut (the effect's word at +8): its end frame.
uint32_t cutLength(uint32_t effect) { return cutEndFrame(*guest::table<const BattleCut>(word(effect + 8))); }

} // namespace

uint32_t familyLength(SystemFamily family, uint32_t effect)
{
    switch (family) {
    case SystemFamily::Shock: case SystemFamily::Freeze: case SystemFamily::Sleep: case SystemFamily::Panic:
    case SystemFamily::Bind: case SystemFamily::Mute: case SystemFamily::Poison: case SystemFamily::Charm:
    case SystemFamily::Stun: case SystemFamily::Fly: case SystemFamily::Stone: case SystemFamily::Curse:
    case SystemFamily::CurseCamp:
        return ailmentLength(effect);
    case SystemFamily::StoneShatter: return shatterLength(effect);
    case SystemFamily::Repel: return repelLength(effect);
    case SystemFamily::Drain: return drainLength(effect);
    case SystemFamily::Attack: case SystemFamily::AttackC: return attackLength(effect);
    case SystemFamily::Return: case SystemFamily::Encounter: case SystemFamily::TalkHeal: case SystemFamily::TalkDrain:
    case SystemFamily::TalkStone:
        return cutLength(effect);
    }
    return 0;
}

// effBTLSystemGetLength @ 0x00173EF0: through the family table's getLength,
// none for an empty row. (A family past the table's rows calls whatever its
// word there points at, as original code.)
uint32_t systemEffectLength(const SystemEffect& effect)
{
    const uint32_t getLength = word(kFamilies + kFamilySize * static_cast<uint32_t>(effect.family) + kGetLength);
    if (getLength == 0)
        return 0;
    if (effect.family < 0 || effect.family > static_cast<int32_t>(SystemFamily::TalkStone))
        return guest::callOriginal(getLength, effect.effect);
    return familyLength(static_cast<SystemFamily>(effect.family), effect.effect);
}

} // namespace nocturne::eff
