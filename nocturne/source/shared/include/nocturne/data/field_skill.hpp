// Skills used outside battle, and the field's hazards to the party
// (original unit: datCalc). The skill formulas are the battle ones
// (battle/damage.hpp) without buffs, difficulty or debug prints, on units
// rather than battle slots.
#pragma once

#include <cstdint>

#include "nocturne/data/records.hpp"
#include "nocturne/ee/float.hpp"

namespace nocturne::dat {

// ---- A skill's power (power = the skill's hpn / mpn) ----
int32_t fieldPhysicalPower(int32_t skill, UnitWork& source, UnitWork& target, int32_t power);     // GetButuriAttack
int32_t fieldPhysicalHealPower(int32_t skill, UnitWork& source, UnitWork& target, int32_t power); // GetButuriKaifuku
int32_t fieldMagicPower(int32_t skill, UnitWork& source, UnitWork& target, int32_t power);        // GetMagicAttack
int32_t fieldMagicHealPower(int32_t skill, UnitWork& source, UnitWork& target, int32_t power);    // GetMagicKaifuku
int32_t fieldMaxHpPower(int32_t skill, UnitWork& source, UnitWork& target, int32_t power);        // GetMaxHpWazaPoint
ee::Float fieldAffinityRate(int32_t skill, UnitWork& source, UnitWork& target);                  // GetAisyoRitu

// datGetSkillKouka: the HP (type 0) or MP (type 1) change; negative is damage.
int32_t fieldSkillEffect(int32_t skill, int32_t type, UnitWork& source, UnitWork& target);
// datGetSkillBadKouka: the ailment the skill inflicts or cures this time, or 0.
uint32_t fieldSkillAilment(int32_t skill, UnitWork& source, UnitWork& target);
// datExecSkill: uses a skill on a unit; 0 if it did nothing.
int32_t useFieldSkill(int32_t skill, UnitWork* source, UnitWork* target);

// ---- The party on the field (members in the party with HP left) ----
// datPartyDamage: 1, 4..6 lose a tenth of their HP (4..6 also poisoned,
// stunned, muted), 2 half, 3 all but 1 HP (not Dante).
void partyDamage(int32_t mode);
// datPartyDamageFld: 1 the poisoned lose 3%, 2 everyone 3%, 3 1-2% at
// random, 4 half.
void partyFieldDamage(int32_t mode);
// datPartyDamagePipe: big x a tenth plus small x 3% of each member's HP.
void partyPipeDamage(int32_t big, int32_t small);
void partyRecover();   // datPartyKaifuku: full HP and MP, no ailment

} // namespace nocturne::dat
