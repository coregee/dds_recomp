// Fusion accidents and devils fusion may not produce (original unit: cmb).
//
// An accident (likelier under a new or full Kagutsuchi) replaces the fusion
// result with a random devil near the Demi-fiend's level, whose stats are
// then raised by a fifth.
#pragma once

#include <cstdint>

#include "nocturne/data/records.hpp"

namespace nocturne::cmb {

bool isEventLocked(uint16_t devil);              // cmbChkEventDevil: until a story event
bool isSpecialFusionOnly(uint16_t devil);        // cmbChkMetaOnlyDevil: DevilFormat flag 0x2

bool rollAccident();                             // cmbChkAccident: 1/16 at new/full moon, else 1/256
int8_t rollAccidentType();                       // cmbChkAccidentType: always 0 (one RNG draw)
uint16_t accidentFallbackDevil(uint16_t excluded);   // cmbGetAccidentFailDevil
uint16_t randomAccidentDevil(uint16_t excluded);     // cmbRndGetAccidentBirthDevil
void boostAccidentDevil(UnitWork& unit);         // cmbAddParamAccidentBirthDevil: stats +1/5

} // namespace nocturne::cmb
