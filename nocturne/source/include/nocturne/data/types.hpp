// Core game vocabulary: stats, elements, ailments, affinities and well-known IDs.
//
// Evidence for each value is listed in docs/glossary.md. Names marked
// "tentative" are inferred from behaviour and not yet confirmed by a symbol,
// string or data table.
#pragma once

#include <cstdint>

#include "nocturne/data/ids.hpp"

namespace nocturne {

// Index into UnitWork::param / DevilFormat::param ("paratype").
// Nocturne shows five stats; slot 1 exists in the data but no UI shows it.
enum class Param : int32_t {
    Strength = 0,
    Unused1  = 1,
    Magic    = 2,
    Vitality = 3,
    Agility  = 4,
    Luck     = 5,
};

// Skill element ("attr"). Indexes rows of the affinity tables.
enum class Attribute : int32_t {
    None     = -1,
    Physical = 0,
    Fire     = 1,
    Ice      = 2,
    Elec     = 3,
    Force    = 4,
    Almighty = 5,
    Expel    = 6,
    Death    = 7,
    Curse    = 8,
    Nerve    = 9,
    Mind     = 10,
    // 11..15 are non-elemental skill classes (healing, support, ...); battle
    // calculations skip 12..14 entirely.
};

// Bad status ("badstat"). The low 12 bits hold *one* ailment at a time, as a
// value rather than a set: datSetBadStat only replaces the current ailment
// with a numerically larger one, so the numeric order is also the priority
// order (Dead beats Stone beats Fly ...). The high nibble holds extra flags.
enum class Ailment : uint16_t {
    None   = 0x000,
    Shock  = 0x001,
    Freeze = 0x002,
    Sleep  = 0x004,
    Panic  = 0x008,
    Bind   = 0x010,
    Mute   = 0x020,
    Poison = 0x040,
    Charm  = 0x080,
    Stun   = 0x100,
    Fly    = 0x200,
    Stone  = 0x400,
    Dead   = 0x800,
};
inline constexpr uint16_t kAilmentMask = 0x0fff;
inline constexpr uint16_t kBadStatCurse = 0x8000; // flag bit, independent of the ailment

// UnitWork::flag bits.
namespace UnitFlag {
inline constexpr uint32_t Valid           = 0x01;
inline constexpr uint32_t InParty         = 0x02; // with Valid: an active stock member
inline constexpr uint32_t PlayerCharacter = 0x04; // the Demi-fiend (tentative name)
inline constexpr uint32_t Enemy           = 0x20;
} // namespace UnitFlag

// Packed affinity word returned by nbGetAisyo / stored in affinity tables.
// Low 16 bits: damage rate in percent (100 = normal, 50 = resist,
// 150 = weak, 200 = Fly). High bits: how the hit resolves.
struct Affinity {
    static constexpr uint32_t Null  = 0x00010000;
    static constexpr uint32_t Repel = 0x00020000;
    static constexpr uint32_t Drain = 0x00040000;
    static constexpr uint32_t Unknown100000 = 0x00100000; // present in data, role unknown
    static constexpr uint32_t Weak  = 0x80000000;

    uint32_t raw = 0;

    int32_t ratePercent() const { return static_cast<int32_t>(raw & 0xffff); }
    bool has(uint32_t flag) const { return (raw & flag) != 0; }
};

// The same ailments as bit masks, for fields that hold a set of them
// (e.g. NormalSkill::badstatus: the ailments a skill can inflict).
namespace ailment {
inline constexpr uint16_t Shock = 0x001, Freeze = 0x002, Sleep = 0x004, Panic = 0x008,
                          Bind = 0x010, Mute = 0x020, Poison = 0x040, Charm = 0x080,
                          Stun = 0x100, Fly = 0x200, Stone = 0x400, Dead = 0x800;
} // namespace ailment

// Skill, devil and item IDs are generated into ids.hpp (skill::Might,
// devil::Pixie, item::Bead ...). Passive resistance families are indexed by
// element: Anti/Void/Drain/Repel <element> = AntiPhys/VoidPhys/PhysDrain/
// PhysRepel + element, with Expel and above skipping Almighty.

// Event flags (evtBitCheck).
namespace EventBit {
// Set when "Normal" is chosen on the US difficulty menu (code at 0x229880),
// clear on Hard.
inline constexpr int32_t NormalDifficulty = 0xaf2;
} // namespace EventBit

// evtGetAgeOfMoon: 0 = new Kagutsuchi, 8 = full.
inline constexpr uint32_t kMoonFull = 8;

} // namespace nocturne
