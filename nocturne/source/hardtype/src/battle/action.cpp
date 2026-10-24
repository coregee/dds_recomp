// The action process (original unit: nbAction): Hardtype's own (shared/src/battle/action.cpp has the rest).
#include "nocturne/battle/action.hpp"

#include "nocturne/battle/calc.hpp"

#include "nocturne/data/tables.hpp"
#include "nocturne/guest.hpp"
#include "nocturne/hardtype.hpp"

namespace nocturne::nb {

namespace {

// Skills shown with another motion type by every devil but the two that
// have it (0x2FE920: skill, two devils, the motion type; up to a 0).
struct MotionException {
    uint16_t skill, devil, otherDevil, motionType;
};
constexpr uint32_t kMotionExceptions = 0x002fe920;

// The effect a pair starts as instead of its stand-in (0x2FDC80: acting
// skill, stand-in, the effect; up to a 0).
struct EffectStart {
    uint16_t acting, standIn, effect, unused;
};
constexpr uint32_t kEffectStarts = 0x002fdc80;

// Status lines of Hardtype's skills, shown when the last target was hit
// (0x2FF140: skill, message; up to a 0).
struct StatusLine {
    uint16_t skill, message;
};
constexpr uint32_t kStatusLines = 0x002ff140;

uint16_t acting() { return hardtype::actingSkill(); }
uint16_t standIn() { return hardtype::standInSkill(); }

} // namespace

// SetAction_READY @ 0x00254488 (and 0x2FE8D0): a chosen skill plays as its
// stand-in, and the pair is noted (hardtype.hpp); skills 0xA4..0xA6 play as
// themselves and note nothing.
int32_t readySkill(int32_t skill)
{
    if (skill >= 0xa4 && skill < 0xa7)
        return skill;
    const uint16_t standIn = hardtype::standInFor(static_cast<uint16_t>(skill));
    hardtype::actingSkill() = static_cast<uint16_t>(skill);
    hardtype::standInSkill() = standIn;
    return standIn;
}

// ... (and 0x2FE380) the skill's motion, unless an exception names the skill
// and the unit is neither of its devils.
int32_t skillMotionType(const UnitWork& unit)
{
    for (const MotionException* e = guest::table<const MotionException>(kMotionExceptions); e->skill != 0; ++e) {
        if (e->skill != unit.nowindex)
            continue;
        if (e->devil == unit.id || e->otherDevil == unit.id)
            break;
        return e->motionType;
    }
    return hitEffectByte(unit.nowindex, 0);
}

// ... (and 0x2FDF90) a summon notes itself (0xFF) as the pair; the units
// past the Demi-fiend's in memory (his demons, which have no summoning
// motion) use motion type 0.
int32_t summonMotionType(const UnitWork& unit)
{
    hardtype::actingSkill() = 0xff;
    hardtype::standInSkill() = 0xff;
    return guest::addressOf(&unit) > hardtype::kDemiFiend ? 0 : 0x18;
}

// ... (and 0x2FE8B8) the effect data is the noted stand-in's, if any.
int32_t effectSkill(int32_t skill)
{
    const uint16_t standIn = hardtype::standInSkill();
    return standIn != 0 ? standIn : skill;
}

// ... (and 0x2FDC40) the effect starts as the skill, unless the noted pair
// has an effect of its own.
int32_t effectStartSkill(int32_t skill)
{
    for (const EffectStart* e = guest::table<const EffectStart>(kEffectStarts); e->acting != 0; ++e)
        if (e->acting == hardtype::actingSkill() && e->standIn == hardtype::standInSkill())
            return e->effect;
    return skill;
}

// SetAction_SKILL @ 0x00255650 (and 0x2FE89C): a chosen skill plays as the
// noted stand-in.
int32_t skillPlayed(int32_t chosen) { return standIn() != 0 ? standIn() : chosen; }

// ... (and 0x2FE850) an extra-press result reads the acting skill, even none.
int32_t extraPressSkill(int32_t) { return acting(); }

// ... (and 0x2FDFC0) a summon (0xFF) keeps Focus; otherwise the check reads
// the damage class 4 x (16 x the skill played - the acting one) bytes into
// the skills: the right record only when the two are the same.
bool clearsFocus(int32_t skill)
{
    if (skill == 0xff)
        return false;
    const int32_t checked = acting() != 0 ? acting() : skill;
    const uint32_t offset = 4u * static_cast<uint32_t>(16 * skill - checked);
    return *guest::table<uint8_t>(dat::address::NormalSkill + offset + 2) == 0;
}

// ... (and 0x2FE1E0) Drain Attack fires whatever passive fired before, and
// keeps that one's mark.
int32_t drainAttackMark(int32_t autoskill) { return autoskill != 0 ? autoskill : 0x12e; }

// ... (and 0x2FE5D0) for the enemies' units (allocated at 0x116xxxx) the
// share of 0x11E is a sixteenth.
int32_t selfHealPercent(const UnitWork& unit, int8_t amount)
{
    if (guest::addressOf(&unit) >> 16 != 0x116)
        return amount;
    return static_cast<int32_t>(static_cast<uint32_t>(static_cast<int32_t>(amount)) >> 4);
}

// ... (and 0x2FF0E0) the status line is the acting skill's: one of
// Hardtype's own when the last target was hit (but 0x46 keeps its own).
int32_t statusSkill(int32_t skill)
{
    const int16_t noted = static_cast<int16_t>(acting());
    return noted != 0 ? noted : skill;
}
int32_t versionStatusMessage(int32_t skill, int32_t lastKind)
{
    if (skill == 0x46 || lastKind != 0)
        return 0;
    for (const StatusLine* line = guest::table<const StatusLine>(kStatusLines); line->skill != 0; ++line)
        if (line->skill == skill)
            return line->message;
    return 0;
}

// ... Pierce's line shows without a hit: the branches to its check land past
// the hit test, which moved a word earlier.
bool pierceNeedsHit() { return false; }

// ... (and 0x2FE860) after the buff check, the skill is the stand-in again.
int32_t skillAfterStatus(int32_t skill) { return standIn() != 0 ? standIn() : skill; }

// ... (and 0x2FDF10) "no effect" (0x44, 0x45) isn't shown for an acting
// skill that also deals HP.
bool holdsStatusLine(int32_t message)
{
    return (message & 0xfe) == 0x44 && dat::normalSkill(acting()).hpn != 0;
}

// CheckMukanNego @ 0x00252400 (and 0x2FEB80), CheckSenseiNego @ 0x002525F0
// (and 0x2FEBB0): by bit 1 of the option byte (as a boss battle's flag).
bool talksSwitchedOff() { return hardtype::byteAt(hardtype::kOptions) & 1; }

// SetAllPacket @ 0x0024FF60 (and 0x2FE750): a sleeper wakes, and a physical
// hit ends Shock and Freeze (the low byte of the ailment word, bits 1 and 2).
bool hitWakes(const UnitWork* unit, int32_t nskill)
{
    const bool asleep = checkAilment(unit, AilmentCheck::IsAsleep);
    if (dat::normalSkill(nskill).damageClass != 0)
        return asleep;
    const uint8_t low = *guest::table<uint8_t>((unit ? guest::addressOf(unit) : 0u) + 0xe);
    return asleep || (low & 3);
}

} // namespace nocturne::nb
