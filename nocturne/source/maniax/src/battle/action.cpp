// The action process (original unit: nbAction): US Maniax's own (shared/src/battle/action.cpp has the rest).
#include "nocturne/battle/action.hpp"

#include "nocturne/battle/calc.hpp"

#include "nocturne/data/tables.hpp"


namespace nocturne::nb {

// SetAction_READY @ 0x00254488: every skill plays as itself; a skill's
// motion is its hit effect's, a summon's type 0x18.
int32_t readySkill(int32_t skill) { return skill; }
int32_t skillMotionType(const UnitWork& unit) { return hitEffectByte(unit.nowindex, 0); }
int32_t summonMotionType(const UnitWork&) { return 0x18; }
int32_t effectSkill(int32_t skill) { return skill; }
int32_t effectStartSkill(int32_t skill) { return skill; }

// SetAction_SKILL @ 0x00255650: the skill chosen throughout; Drain Attack
// only when no other passive fired; 0x11E heals its own share; the status
// line by the skill, Pierce's only after a hit, never held back.
int32_t skillPlayed(int32_t chosen) { return chosen; }
int32_t extraPressSkill(int32_t skill) { return skill; }
bool clearsFocus(int32_t skill) { return dat::normalSkill(skill).damageClass == 0; }
int32_t drainAttackMark(int32_t autoskill) { return autoskill == 0 ? 0x12e : -1; }
int32_t selfHealPercent(const UnitWork&, int8_t amount) { return amount; }
int32_t statusSkill(int32_t skill) { return skill; }
int32_t versionStatusMessage(int32_t, int32_t) { return 0; }
bool pierceNeedsHit() { return true; }
int32_t skillAfterStatus(int32_t skill) { return skill; }
bool holdsStatusLine(int32_t) { return false; }

// CheckMukanNego @ 0x00252400, CheckSenseiNego @ 0x002525F0: never.
bool talksSwitchedOff() { return false; }

// SetAllPacket @ 0x0024FF60: a sleeper wakes.
bool hitWakes(const UnitWork* unit, int32_t) { return checkAilment(unit, AilmentCheck::IsAsleep); }

} // namespace nocturne::nb
