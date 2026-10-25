// Fusion rules: which devil two (or three) devils make
// (original unit: fclCombineCalcCore, "cmb").
//
// Normal fusion: the two races give a result race (the combine table; same
// races give an Element), and the result is the weakest devil of that race
// at or above the average level (+1). Special cases come first:
//   - fixed pairs (Rangda + Barong = Shiva ...), cmbChkExtPattern;
//   - an Element shifts the other devil one rank up or down its race;
//   - two Elements make a Mitama; a Mitama with a devil raises its stats;
//   - with a sacrifice (Kagutsuchi full), fixed trios and race patterns;
//   - Fiends, from a Deathstone and the moon phase (cmbCalcCombineManin).
// Devils locked behind an event or only made by special fusion are skipped.
#pragma once

#include <cstdint>

#include "nocturne/data/records.hpp"

namespace nocturne::cmb {

// What cmbGetBirthDevil / cmbCalcDevil2 produced.
enum class FusionType : uint8_t {
    None             = 0,
    Normal           = 1,  // two races -> race table
    MitamaBoost      = 2,  // a Mitama and a devil: the devil, with stats raised
    Mitama           = 3,  // two Elements
    Element          = 4,  // two devils of the same race
    RankUp           = 5,  // an Element and a devil: one rank up its race
    RankDown         = 6,  // ... one rank down
    SpecialPair      = 7,  // a fixed pair (cmbChkExtPattern)
    Sacrifice        = 8,  // sacrificial fusion by the normal rules
    SacrificeSpecial = 9,  // sacrificial fusion by a fixed pattern
    Accident         = 10,
    AccidentBoost    = 11, // (unused: there is one accident type)
    Fiend            = 12,
};

// ---- Table lookups -------------------------------------------------------------

uint16_t specialPairResult(uint16_t devil1, uint16_t devil2);           // cmbChkExtPattern
bool isSpecialPairResult(uint16_t devil);                                // cmbChkExtPatternBirthDevil
bool isSacrificePatternResult(uint16_t devil);                           // cmbChkIkenieExtPatternBirthDevil
uint16_t mitamaFromElements(uint16_t element1, uint16_t element2);       // cmbGetBirthSpirit
int8_t elementRankShift(uint16_t element, Race race);                    // cmbGetRankUpDown: 1 up, 2 down, -1 none
// cmbGetBirthDevilRace: the race two devils' races combine into (a devil ID,
// an Element, when the races are equal). Fiends count as Tyrants.
uint8_t resultRace(uint16_t devil1, uint16_t devil2, bool cursed);
// cmbGetAverageLevel: species levels, or the units' own (LevelMode).
int32_t averageLevel(const UnitWork& devil1, const UnitWork& devil2, const UnitWork* sacrifice, bool unitLevels);

// ---- Choosing the devil --------------------------------------------------------

// cmbGetTargetDevil: the weakest fusible devil of the race at or above
// `level`, else the strongest; 0 if none.
uint16_t targetDevil(uint8_t race, uint8_t level);
// cmbGetRankUpDownDevil: the next fusible devil of the same race above
// (shift 1) or below (2).
uint16_t rankShiftedDevil(uint16_t devil, uint8_t shift);
uint16_t normalFusion(const UnitWork& devil1, const UnitWork& devil2, bool cursed, bool unitLevels);  // cmbCalcNormal2

// cmbCalcDevil2: two devils, `ids`/`races` ordered higher level first.
uint16_t twoDevilFusion(const UnitWork& devil1, const UnitWork& devil2, bool cursed, bool unitLevels,
                        const uint16_t ids[2], const uint8_t races[2], FusionType* type);

// ---- Sacrificial fusion ------------------------------------------------------------

uint8_t sacrificeRacePattern(uint16_t devil1, uint16_t devil2, uint16_t sacrifice);    // cmbChkIkenieExtPattern
bool isMetatronPair(uint16_t devil1, uint16_t devil2, uint16_t birth);                  // cmbChkMetato
#if !NOCTURNE_VANILLA   // (Maniax's)
uint16_t sacrificeDevilRacePattern(uint16_t devil1, uint16_t devil2, uint16_t sacrifice); // cmbChkIkenieExtPatternDevRace
#endif
uint16_t sacrificeDevilPattern(const UnitWork& devil1, const UnitWork& devil2, const UnitWork& sacrifice,
                               bool cursed, bool unitLevels);                            // cmbChkIkenieExtPatternDev
uint16_t sacrificeFusion(const UnitWork& devil1, const UnitWork& devil2, const UnitWork& sacrifice, bool cursed,
                         bool unitLevels, const uint16_t ids[2], const uint8_t races[2]); // cmbCalcIkenie

// ---- Others -------------------------------------------------------------------------

#if !NOCTURNE_VANILLA   // (Maniax's)
uint16_t fiendFusion(uint16_t devil);                                    // cmbCalcCombineManin
#endif
#if !NOCTURNE_VANILLA   // (Maniax's)
bool involvesDante(const UnitWork& devil1, const UnitWork& devil2, const UnitWork* sacrifice);  // cmbChkDante
#endif

} // namespace nocturne::cmb
