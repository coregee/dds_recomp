// Random encounters in the field (original unit: nbEncount).
//
// Walking fills a distance counter; every 100 units of distance add 2..4
// to the encounter count (8..12 under Riberama). Once the count reaches the
// area's threshold (rolled once, 16 up to about twice the base 370 less a
// share of the table's "normal" weight), each step rolls one of the area
// table's encounters by weight out of 1000. Estoma turns away encounters
// the Demi-fiend clearly outlevels, and starts the count over.
//
// An area pack has four tables. Which one applies (its "condition") depends
// on Kagutsuchi's phase, or else on two event bits.
#pragma once

#include <cstdint>

#include "nocturne/ee/float.hpp"

namespace nocturne::nb {

int32_t encounterTable(int32_t pack);                  // nbGetEncountJoken: the pack's table now
int32_t encounterThreshold(int32_t pack);              // nbGetEncountMax: the count needed (0: the table is empty)
int32_t encounterCount();                              // nbGetEncountCnt
int32_t walkForEncounter(int32_t pack, ee::Float length);   // nbEncountCalc: an encounter's data, or 0
bool encounterWorthFighting(int32_t encno);            // nbCheckEncountLevel: Estoma lets it through
void resetEncounterCount();                            // nbResetEncountCount

// An encounter's data: table << 24 | entry << 16 | encounter (NB_MAKE_ENCDATA).
inline int32_t encounterTableOf(uint32_t encdata) { return static_cast<int32_t>(encdata >> 24); }      // NB_GET_PACKNO
inline int32_t encounterOf(uint32_t encdata) { return static_cast<int32_t>(encdata & 0xffff); }        // NB_GET_ENCNO

// The battle music's type: the encounter's own, else its area pack's, else 1.
int32_t encounterMusic(int32_t pack, int32_t encno);   // GetBgmCategory
int32_t battleMusic();                                 // nbGetBgmCategoryInBattle: ... of this battle
int32_t fieldMusic(uint32_t encdata);                  // nbGetBgmCategoryInField: ... of a field encounter's data

} // namespace nocturne::nb
