// The encounter's opening (original unit: nbEncProcess): a process
// ("nb_enc") that loads the units' models, shows the enemies appearing one
// by one (or all at once when the battle opens from a fade), and ends when
// every unit stands ready and the opening camera is done.
#pragma once

#include <cstdint>

#include "nocturne/battle/process.hpp"

namespace nocturne::nb {

// Each returns the next process function (0 the same, -1 done).
uint32_t startEncounterLoad(uint32_t process);      // nbEncProcess1: the effect started, the enemies' models requested (group 1)
uint32_t loadEnemyModels(uint32_t process);         // nbEncProcess2: ... loaded, then the party's (group 0)
uint32_t showEnemies(uint32_t process);             // nbEncProcess2_5: the enemies appear, one per eight frames
uint32_t setUpEncounterScene(uint32_t process);     // nbEncProcess2_55: the full-moon glow, the fade in, a back attack's message
uint32_t showPlayers(uint32_t process);             // nbEncProcess2_6: the party appears
uint32_t finishEncounter(uint32_t process);         // nbEncProcess3: every unit ready and the camera done
void shutdownEncounter(uint32_t process);           // nbEncShutdown
void startEncounter(MainProcessData& data);         // nbInitEncProcess

} // namespace nocturne::nb
