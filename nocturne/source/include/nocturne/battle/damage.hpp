// Damage, healing and ailment effects (original unit: nbCalc).
//
// How much a skill does: the attacker's power for the skill, scaled by the
// affinity ratio, randomised, and adjusted for difficulty; plus the rolls
// that decide whether an ailment lands or is cured.
#pragma once

#include <cstdint>

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
int32_t maxHpPower(int32_t skill, int32_t source, int32_t target, int32_t power);         // nbGetMaxHpWazaPoint

// ---- HP / MP effect ---------------------------------------------------------

// nbGetKoukaHp / nbGetKoukaMp: the amount a skill changes the target's HP
// (MP). With damage set, returns the damage; otherwise the healing (-1 when
// the skill does neither). ratio is the affinity ratio (damageRatio); count
// splits damage among targets for hptype 14.
int32_t hpEffect(ee::Float ratio, bool damage, int32_t skill, int32_t source, int32_t target, int32_t count);
int32_t mpEffect(ee::Float ratio, bool damage, int32_t skill, int32_t source, int32_t target, int32_t count);

// ---- Ailments ---------------------------------------------------------------

// nbGetKoukaBadDamage: roll whether the skill inflicts its ailment. Returns
// the ailment (badstat value) or 0. preview skips the roll (AI estimates).
uint32_t rollAilmentInflict(ee::Float ratio, int32_t skill, int32_t source, int32_t target, bool preview);
// nbGetKoukaBadKaifuku: roll whether a curing skill cures the target. Returns
// the skill's cure mask if the target has one of those ailments, else 0.
uint32_t rollAilmentCure(ee::Float ratio, int32_t skill, int32_t source, int32_t target, bool preview);

} // namespace nocturne::nb
