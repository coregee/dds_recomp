// The turn order (original unit: nbMisc). Rewritten from the original
// instructions.
#include "nocturne/battle/order.hpp"

#include <utility>

#include "nocturne/battle/process.hpp"
#include "nocturne/data/types.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr int32_t kOrderSlots = 12;

bool inBattle(const Party& party) { return (party.flag & PartyFlag::Active) && !(party.flag & PartyFlag::Left); }

// A unit's Agility. A party without a unit reads it at guest address 0, as
// the original does.
int32_t agility(MainProcessData& main, int32_t partyindex)
{
    const uint32_t unit = guest::addressOf(GetUnitWorkPointer(main, main.party[partyindex]));
    return dat::param(*guest::table<const UnitWork>(unit), Param::Agility);
}

// order[index] as the original reads it, for any index the byte holds
// (-1 reads the byte before the array).
int8_t orderAt(MainProcessData& main, int32_t index)
{
    return *guest::table<int8_t>(guest::addressOf(&main.order[0]) + static_cast<uint32_t>(index));
}

} // namespace

// nbAddOrder @ 0x00258048: a unit that joined during the turn (a summon, a
// call for help) acts later in it, in the first free slot after the one
// acting.
void addToOrder(int32_t formindex)
{
    MainProcessData& main = *GetMainProcessData();
    const Formation& form = main.form[formindex];
    if (!(form.stat & FormationStat::Present) || !(form.stat & FormationStat::CheckParty))
        return;
    const int32_t start = main.orderindex + 1;
    for (int32_t i = start; i < kOrderSlots; ++i) {
        if (main.order[i] < 0) {
            main.order[i] = static_cast<int8_t>(form.partyindex);
            sortOrder(start);
            return;
        }
    }
}

// nbSortOrder @ 0x002580E8
void sortOrder(int32_t start)
{
    MainProcessData& main = *GetMainProcessData();
    for (int32_t i = start; i < kOrderSlots - 1; ++i) {
        if (main.order[i] < 0)
            continue;
        for (int32_t j = i + 1; j < kOrderSlots; ++j) {
            if (main.order[j] < 0)
                continue;
            const int32_t agilityI = agility(main, main.order[i]);
            const int32_t agilityJ = agility(main, main.order[j]);
            if (agilityI < agilityJ ||
                (agilityI == agilityJ && main.party[main.order[i]].formindex > main.party[main.order[j]].formindex))
                std::swap(main.order[i], main.order[j]);
        }
    }
}

// nbSetOrderSide @ 0x00258280
void buildOrder(int32_t side)
{
    MainProcessData& main = *GetMainProcessData();
    for (int8_t& slot : main.order)
        slot = -1;
    main.orderindex = -1;
    const int32_t first = side == 0 ? 0 : 4, last = side == 0 ? 4 : 14;
    int32_t count = 0;
    for (int32_t i = first; i < last; ++i)
        if (inBattle(main.party[i]))
            main.order[count++] = static_cast<int8_t>(i);
    if (count == 0) {
        main.orderindex = -1;
        main.activeunit = -1;
        return;
    }
    main.orderindex = 0;
    sortOrder(0);
    main.activeunit = main.order[main.orderindex];
}

// nbSetOrder @ 0x002583D8
void resetOrder() { buildOrder((GetMainProcessData()->stat & BattleStat::EnemyTurn) ? 1 : 0); }

// nbSetNextOrder @ 0x00258418: past the order's end it is rebuilt (and the
// first acts again).
void advanceOrder()
{
    MainProcessData& main = *GetMainProcessData();
    if (main.orderindex < 0) {
        resetOrder();
        return;
    }
    for (;;) {
        main.orderindex = static_cast<int8_t>(main.orderindex + 1);
        if (main.orderindex >= kOrderSlots) {
            resetOrder();
            break;
        }
        if (main.order[main.orderindex] >= 0)
            break;
    }
    main.activeunit = orderAt(main, main.orderindex);
}

// nbUpdateOrder @ 0x002584C8
void updateOrder()
{
    MainProcessData& main = *GetMainProcessData();
    for (int8_t& slot : main.order)
        if (slot >= 0 && !inBattle(main.party[slot]))
            slot = -1;
}

} // namespace nocturne::nb
