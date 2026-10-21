// The devil stock (original unit: cmb).
#include "nocturne/fusion/stock.hpp"

#include <cstring>

#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/fusion/growth.hpp"

namespace nocturne::cmb {

// ps2ClearUnitWork @ 0x001FF050
void clearUnit(UnitWork& unit)
{
    std::memset(&unit, 0, sizeof unit);
}

// cmbCopyDefaultDevilToStock @ 0x001FEE68: a fresh devil of the species, at
// its base level and stats, full HP/MP, with its starting skills.
void copyDefaultDevil(uint16_t devil, UnitWork& unit)
{
    clearUnit(unit);
    const DevilFormat& format = dat::devilFormat(devil);
    unit.flag = UnitFlag::Valid;
    unit.id = devil;
    unit.level = format.level;
    for (int i = 0; i < 6; ++i)
        unit.param[i] = format.param[i];
    unit.maxhp = unit.hp = static_cast<uint16_t>(dat::maxHp(unit));
    unit.maxmp = unit.mp = static_cast<uint16_t>(dat::maxMp(unit));
    createDefaultSkills(devil, unit);
}

// cmbCopyCustomDevilToStock @ 0x001FEF20: copy a unit, then recompute max
// HP/MP (clamping current HP/MP) and mark the slot valid.
void copyCustomDevil(UnitWork& destination, const UnitWork& source)
{
    // The original copies in 32-byte chunks, each fully read before written,
    // so an overlapping copy behaves like this snapshot.
    UnitWork copy;
    std::memcpy(&copy, &source, sizeof copy);
    std::memcpy(&destination, &copy, sizeof copy);
    destination.maxhp = static_cast<uint16_t>(dat::maxHp(destination));
    destination.maxmp = static_cast<uint16_t>(dat::maxMp(destination));
    if (destination.maxhp < destination.hp) destination.hp = destination.maxhp;
    if (destination.maxmp < destination.mp) destination.mp = destination.maxmp;
    destination.flag |= UnitFlag::Valid;
}

// cmbChkStockDevil @ 0x002228D8
int8_t findStockDevil(uint16_t devil, const UnitWork* units, uint8_t count)
{
    for (int i = 0; i < count; ++i)
        if ((units[i].flag & UnitFlag::Valid) && units[i].id == devil)
            return static_cast<int8_t>(i);
    return -1;
}

// cmbChkStockDevilNums @ 0x00222928: devils, not counting the Demi-fiend.
int8_t countStockDevils(const UnitWork* units, uint8_t count)
{
    uint8_t n = 0;
    for (int i = 0; i < count; ++i)
        if ((units[i].flag & UnitFlag::Valid) && !(units[i].flag & UnitFlag::PlayerCharacter))
            ++n;
    return static_cast<int8_t>(n);
}

// cmbGetEmptyStockIndex @ 0x001FEA98: a slot whose whole flag word is 0.
int8_t findEmptyStockSlot(const UnitWork* units, uint8_t count)
{
    for (int i = 0; i < count; ++i)
        if (units[i].flag == 0)
            return static_cast<int8_t>(i);
    return -1;
}

// cmbGetStockDevilIndex @ 0x001FEAD8: like findStockDevil, but any nonzero
// flag word counts as occupied.
int8_t findStockDevilAnyFlag(uint16_t devil, const UnitWork* units, uint8_t count)
{
    for (int i = 0; i < count; ++i)
        if (units[i].flag != 0 && units[i].id == devil)
            return static_cast<int8_t>(i);
    return -1;
}

// cmbDeleteUnitFromStockList @ 0x001FF178: remove every occurrence of
// `index` from the display list (count drops by exactly one).
void removeFromStockList(int8_t index)
{
    GlobalWork& global = dat::globalWork();
    int8_t write = 0;
    for (int8_t read = 0; read < global.stock_count; ++read) {
        global.stock_list[write] = global.stock_list[read];
        if (static_cast<int32_t>(global.stock_list[read]) != index)
            ++write;
    }
    global.stock_count -= 1;
}

// cmbAddUnitToStockList @ 0x001FF1F8
void appendToStockList(int8_t index)
{
    GlobalWork& global = dat::globalWork();
    global.stock_list[global.stock_count] = static_cast<uint8_t>(index);
    global.stock_count += 1;
}

namespace {

// The stock list numbers slots from the start of the 16-unit array; `units`
// is its last `count` entries.
int8_t listIndex(int8_t slot, uint8_t count) { return static_cast<int8_t>(slot - count + 16); }

} // namespace

// cmbDeleteDevilFromStock @ 0x001FF218: returns -1 on success, 0 if absent.
int8_t deleteDevil(uint16_t devil, UnitWork* units, uint8_t count)
{
    int8_t slot = findStockDevil(devil, units, count);
    if (slot < 0)
        return 0;
    removeFromStockList(listIndex(slot, count));
    clearUnit(units[slot]);
    return -1;
}

// cmbAddDefaultDevilToStock @ 0x001FF298
int8_t addDefaultDevil(uint16_t devil, UnitWork* units, uint8_t count)
{
    int8_t slot = findEmptyStockSlot(units, count);
    if (slot < 0)
        return -1;
    appendToStockList(listIndex(slot, count));
    copyDefaultDevil(devil, units[slot]);
    return slot;
}

// cmbAddCustomDevilToStock @ 0x001FF328
int8_t addCustomDevil(const UnitWork& source, UnitWork* units, uint8_t count)
{
    int8_t slot = findEmptyStockSlot(units, count);
    if (slot < 0)
        return -1;
    appendToStockList(listIndex(slot, count));
    copyCustomDevil(units[slot], source);
    return slot;
}

// cmbChkDarkDevil @ 0x00222CF0
bool isDarkDevil(uint16_t devil)
{
    for (uint16_t dark : dat::kDarkDevil)
        if (dark == devil)
            return true;
    return false;
}

// cmbChkStockDarkDevilNums @ 0x00222D38
int8_t countDarkDevils(const UnitWork* units, uint8_t count)
{
    uint8_t n = 0;
    for (int i = 0; i < count; ++i)
        if ((units[i].flag & UnitFlag::Valid) && !(units[i].flag & UnitFlag::PlayerCharacter) && isDarkDevil(units[i].id))
            ++n;
    return static_cast<int8_t>(n);
}

// cmbChkIkenieIllegalDevil @ 0x001FE9E0 ("ikenie" = 生贄, sacrifice): devils
// with no race, and enemy-only species (DevilFormat flag 0x20).
bool cannotBeSacrificed(uint16_t devil)
{
    const DevilFormat& format = dat::devilFormat(devil);
    if (format.race == Race::None)
        return true;
    return (format.flag & 0x20) != 0;
}

} // namespace nocturne::cmb
