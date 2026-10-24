// What a unit does when an ailment takes its turn (original unit: nbBadAi).
//
// A panicked or charmed unit, or a cursed one, doesn't act as told: each
// turn it draws one of a few actions by weight (MakeRituList) and tries it;
// an action that can't be done is struck from the list and another drawn,
// up to ten times, after which the unit just loses its turn.
//
// Names are the HD remaster's.
#pragma once

#include <cstdint>

#include "nocturne/battle/process.hpp"

namespace nocturne::nb {

// The actions (GetBadAiAction's results).
enum AilmentAction : int32_t {
    kAilmentLoseTurn = 0, // loses the turn (also 9)
    kAilmentAttack = 1, // attacks a random target
    kAilmentHeal = 2,   // casts one of its healing skills (0x24..0x29)
    kAilmentBuff = 3,   // casts one of its buffs (0x40..0x44)
    kAilmentThrowMacca = 4, // throws away Macca (skill 0xF7)
    kAilmentTalk = 5,   // talks to the enemy (the player's side)
    kAilmentReturn = 6, // goes back to the stock (a devil ally)
    kAilmentSelfDamage = 7, // hurts itself (cursed)
    kAilmentNothing = 8, // (never listed)
    kAilmentLoseTurn2 = 9,
};

// The weighted list the action is drawn from (0x575490, its length at
// 0x551558).
struct AilmentWeight {
    int32_t type;    // BadAction
    int32_t weight;  // weight; 0 once tried (HD: ritu)
};

void setSingleTarget(ActionProcessData& a);
void setGroupTarget(ActionProcessData& a);
bool setTarget(ActionProcessData& a, int32_t rev);
bool ailmentSkillUsable(int32_t skill, int32_t type);
int32_t ailmentSkill(ActionProcessData& a, int32_t type);        // -1 for none

// The actions: 0 when done, 1 when the unit can't (try another).
int32_t ailmentBuff(ActionProcessData& a);
int32_t ailmentHeal(ActionProcessData& a);
int32_t ailmentAttack(ActionProcessData& a);
int32_t ailmentThrowMacca(ActionProcessData& a);
int32_t ailmentTalk(ActionProcessData& a);
int32_t ailmentReturn(ActionProcessData& a);
int32_t ailmentLoseTurn(ActionProcessData& a);
int32_t ailmentSelfDamage(ActionProcessData& a);

int32_t chooseAilmentAction(); // -1 when every weight is 0
void addAilmentWeight(int32_t type, int32_t ritu);
void buildAilmentWeights(ActionProcessData& a);
int32_t runAilmentAi(ActionProcessData& a);

// The battle's status line message for an action (nbMisc).
void setStatusMessage(ActionProcessData& a, int32_t jyokyomes, int32_t var_id, int32_t var_ind);
int32_t statusMessage(const MainProcessData& data, int32_t jyokyomes);

} // namespace nocturne::nb
