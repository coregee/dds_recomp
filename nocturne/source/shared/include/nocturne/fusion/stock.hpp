// The devil stock: creating, copying, finding and listing units
// (original unit: cmb, "combine", the Cathedral of Shadows).
//
// Stock functions take a unit array and its length, because the same code
// serves the save game's 16 slots and temporary arrays during fusion.
#pragma once

#include <cstdint>

#include "nocturne/data/records.hpp"

namespace nocturne::cmb {

void clearUnit(UnitWork& unit);                                     // ps2ClearUnitWork (0x1FF050)
void copyDefaultDevil(uint16_t devil, UnitWork& unit);              // cmbCopyDefaultDevilToStock
void copyCustomDevil(UnitWork& destination, const UnitWork& source);// cmbCopyCustomDevilToStock

// Searches. Indexes are relative to `units`; -1 when absent.
int8_t findStockDevil(uint16_t devil, const UnitWork* units, uint8_t count);   // cmbChkStockDevil
int8_t countStockDevils(const UnitWork* units, uint8_t count);                // cmbChkStockDevilNums
int8_t findEmptyStockSlot(const UnitWork* units, uint8_t count);              // cmbGetEmptyStockIndex
int8_t findStockDevilAnyFlag(uint16_t devil, const UnitWork* units, uint8_t count); // cmbGetStockDevilIndex

// The display order of the stock (GlobalWork stock list).
void removeFromStockList(int8_t index);                             // cmbDeleteUnitFromStockList
void appendToStockList(int8_t index);                               // cmbAddUnitToStockList

// Add or remove a devil; return the slot, or -1 when full (delete: -1 on success).
int8_t deleteDevil(uint16_t devil, UnitWork* units, uint8_t count);         // cmbDeleteDevilFromStock
int8_t addDefaultDevil(uint16_t devil, UnitWork* units, uint8_t count);     // cmbAddDefaultDevilToStock
int8_t addCustomDevil(const UnitWork& source, UnitWork* units, uint8_t count); // cmbAddCustomDevilToStock

bool isDarkDevil(uint16_t devil);                                   // cmbChkDarkDevil
int8_t countDarkDevils(const UnitWork* units, uint8_t count);       // cmbChkStockDarkDevilNums
bool cannotBeSacrificed(uint16_t devil);                            // cmbChkIkenieIllegalDevil

} // namespace nocturne::cmb
