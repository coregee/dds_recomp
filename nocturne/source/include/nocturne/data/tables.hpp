// Fixed data tables inside SLUS_209.11, by RAM address.
#pragma once

#include <cstdint>

#include "nocturne/data/records.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::dat {

namespace address {
inline constexpr uint32_t DevilFormat       = 0x003497c0;
inline constexpr uint32_t DefaultUnitVisual = 0x003494b0;
inline constexpr uint32_t UnitVisual        = 0x0034f1e0;
inline constexpr uint32_t Encount           = 0x003aefe0;
inline constexpr uint32_t EncountPack       = 0x003bade0;
inline constexpr uint32_t SkillHitEffect    = 0x003dbd20; // 4-byte rows; byte 3 = "no hit effect"
inline constexpr uint32_t NormalSkill       = 0x003d7998;
inline constexpr uint32_t SpecialSkill      = 0x003dc1e0;
inline constexpr uint32_t SenseiCoefficient = 0x00544d58; // float[6], see nbCheckSensei
inline constexpr uint32_t GlobalWorkPointer = 0x0054ea20;
} // namespace address

inline const NormalSkill& normalSkill(int32_t id) { return guest::table<const NormalSkill>(address::NormalSkill)[id]; }
inline const DevilFormat& devilFormat(int32_t id) { return guest::table<const DevilFormat>(address::DevilFormat)[id]; }
inline const Encount& encount(int32_t id) { return guest::table<const Encount>(address::Encount)[id]; }
inline const EncountPack& encountPack(int32_t id) { return guest::table<const EncountPack>(address::EncountPack)[id]; }

// datSpecialSkill covers passive skills from 0x128 upward.
inline const SpecialSkill& specialSkill(int32_t skill)
{
    return guest::table<const SpecialSkill>(address::SpecialSkill)[skill - 0x128];
}

inline GlobalWork& globalWork()
{
    return *guest::table<GlobalWork>(*guest::table<const uint32_t>(address::GlobalWorkPointer));
}

} // namespace nocturne::dat
