// Damage, healing and ailment effects (original unit: nbCalc).
//
// How much a skill does: the attacker's power for the skill, scaled by the
// affinity ratio, randomised, and adjusted for difficulty; plus the rolls
// that decide whether an ailment lands or is cured.
#pragma once

#include <cstdint>

#include "nocturne/data/records.hpp"
#include "nocturne/ee/float.hpp"

namespace nocturne::nb {

// ---- Power (before affinity) ------------------------------------------------

// nbGetButuriAttack: physical. Based on (Lv + St) * 2, scaled by the skill's
// power (or a fixed factor for the normal attack), the attacker's Attack
// buff and the defender's Defense buff.
int32_t physicalPower(int32_t skill, int32_t source, int32_t target, int32_t power);
int32_t physicalHealPower(int32_t skill, int32_t source, int32_t target, int32_t power);  // nbGetButuriKaifuku
// nbGetMagicAttack: magic. Based on the skill's magicbase + Lv * power,
// capped at magiclimit, adjusted by Ma.
int32_t magicPower(int32_t skill, int32_t source, int32_t target, int32_t power);
int32_t magicHealPower(int32_t skill, int32_t source, int32_t target, int32_t power);     // nbGetMagicKaifuku
int32_t maxHpPower(int32_t skill, int32_t source, int32_t target, int32_t power);         // nbGetMaxHpWazaPoint [version]
// [version] nbGetMagicAttack's formula before buffs, and whether it retries
// levels above 100; nbGetMagicKaifuku's points by the caster.
ee::Float magicBase(const UnitWork& unit, const NormalSkill& skill, int32_t power);
bool magicRetriesHighLevels();
// [version] nbGetKoukaHp: a skill's HP power, and power% of the target's HP.
int32_t hpPower(int32_t skill, int32_t power);
int32_t hpPercentDamage(int32_t base, int32_t power);
ee::Float healPointsScale(const UnitWork& caster, ee::Float points);

// ---- HP / MP effect ---------------------------------------------------------

// nbGetKoukaHp / nbGetKoukaMp: the amount a skill changes the target's HP
// (MP). With damage set, returns the damage; otherwise the healing (-1 when
// the skill does neither). ratio is the affinity ratio (damageRatio); count
// splits damage among targets for hptype 14.
int32_t hpEffect(ee::Float ratio, bool damage, int32_t skill, int32_t source, int32_t target, int32_t count);
int32_t mpEffect(ee::Float ratio, bool damage, int32_t skill, int32_t source, int32_t target, int32_t count);

// nbGetVirtualKoukaPoint: the AI's score for using a skill on a target: the
// expected HP/MP damage and healing (healing capped at what is missing),
// plus 1 for an ailment inflicted or cured, plus the buff change. Runs every
// roll in preview mode, but still draws RNG for damage spread.
int32_t estimateEffect(int32_t skill, int32_t source, int32_t target);

// ---- Ailments ---------------------------------------------------------------

// nbGetKoukaBadDamage: roll whether the skill inflicts its ailment. Returns
// the ailment (badstat value) or 0. preview skips the roll (AI estimates).
uint32_t rollAilmentInflict(ee::Float ratio, int32_t skill, int32_t source, int32_t target, bool preview);
// nbGetKoukaBadKaifuku: roll whether a curing skill cures the target. Returns
// the skill's cure mask if the target has one of those ailments, else 0.
uint32_t rollAilmentCure(ee::Float ratio, int32_t skill, int32_t source, int32_t target, bool preview);

} // namespace nocturne::nb
