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
enum BadAction : int32_t {
    kBadWait = 0,       // loses the turn (also 9)
    kBadAttack = 1,     // attacks a random target
    kBadKaifuku = 2,    // casts one of its healing skills (0x24..0x29)
    kBadKaja = 3,       // casts one of its buffs (0x40..0x44)
    kBadMaka = 4,       // throws away Macca (skill 0xF7)
    kBadNego = 5,       // talks to the enemy (the player's side)
    kBadReturn = 6,     // goes back to the stock (a devil ally)
    kBadDamage = 7,     // hurts itself (cursed)
    kBadNothing = 8,    // (never listed)
    kBadWait2 = 9,
};

// The weighted list the action is drawn from (0x575490, its length at
// 0x551558).
struct BadRitu {
    int32_t type;    // BadAction
    int32_t ritu;    // weight; 0 once tried
};

void SetSingleTarget(ActionProcessData& a);
void SetGroupTarget(ActionProcessData& a);
bool SetTarget(ActionProcessData& a, int32_t rev);
bool CheckBadActionSkill(int32_t skill, int32_t type);
int32_t GetBadActionSkill(ActionProcessData& a, int32_t type);   // -1 for none

// The actions: 0 when done, 1 when the unit can't (try another).
int32_t BadKaja(ActionProcessData& a);
int32_t BadKaifuku(ActionProcessData& a);
int32_t BadAttack(ActionProcessData& a);
int32_t BadMaka(ActionProcessData& a);
int32_t BadNego(ActionProcessData& a);
int32_t BadReturn(ActionProcessData& a);
int32_t BadBadWait(ActionProcessData& a);
int32_t BadDamage(ActionProcessData& a);

int32_t GetBadAiAction();    // -1 when every weight is 0
void AddRituList(int32_t type, int32_t ritu);
void MakeRituList(ActionProcessData& a);
int32_t nbRunBadAi(ActionProcessData& a);

// The battle's status line message for an action (nbMisc).
void nbSetJyokyoMes(ActionProcessData& a, int32_t jyokyomes, int32_t var_id, int32_t var_ind);
int32_t nbGetJyokyoMes(const MainProcessData& data, int32_t jyokyomes);

} // namespace nocturne::nb
