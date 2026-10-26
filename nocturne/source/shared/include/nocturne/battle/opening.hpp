// The battle's opening (original unit: nbMainProcess's "before" process,
// nb_mae): the stage requested, the encounter's event packs, the flight
// model's pack for one encounter, then the music. Each step runs a frame
// and names the next (0 to stay, -1 at the end). Names are descriptive.
#pragma once

#include <cstdint>

#include "nocturne/battle/process.hpp"

namespace nocturne::nb {

void startOpening(MainProcessData& data);   // 0x249BC0: as the battle's child (BeforeProcessID)
void endOpening(uint32_t process);          // 0x249BA0: its shutdown
uint32_t openingRequestStage(uint32_t process);   // 0x249B68
uint32_t openingLoadPacks(uint32_t process);      // 0x249B18
uint32_t openingWaitPacks(uint32_t process);      // 0x249AB0
uint32_t openingLoadMusic(uint32_t process);      // 0x249A88
uint32_t openingWaitMusic(uint32_t process);      // 0x249A58
uint32_t openingPlayMusic(uint32_t process);      // 0x249A38

// (0x24C6C8) the stage to show (record at 0x575350, tentative).
void requestStage(int16_t major, int16_t minor);

// Encounter 0x14D's flight model (flyh, flymem): (0x290B20) its pack
// requested; (0x290B68) once in, its first part kept and the request let
// go (the first release loads it as a plain file). Other encounters need
// none (true).
void requestFlightPack(MainProcessData& data);
bool flightPackLoaded(MainProcessData& data);

} // namespace nocturne::nb
