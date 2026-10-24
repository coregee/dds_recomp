// Buffs and debuffs (original unit: nbCalc).
#include "nocturne/battle/buffs.hpp"

#include "nocturne/external.hpp"

namespace nocturne::nb {

using ee::Float;

// nbGetHojoCounter @ 0x00267E90
int32_t buffCounter(int32_t formindex, int32_t type)
{
    Party* party = GetPartyFromFormindex(formindex);
    return party ? party->count[type] : 0;
}

// nbSetHojoCounter @ 0x00267E50
void setBuffCounter(int32_t formindex, int32_t type, int32_t value)
{
    if (Party* party = GetPartyFromFormindex(formindex))
        party->count[type] = static_cast<int16_t>(value);
}

// nbGetHojoCounterMax @ 0x00267EC8
int32_t buffMax(int32_t type)
{
    if (static_cast<uint32_t>(type) >= 20) return 0;
    if (type < 4 || (type >= 16 && type < 19)) return 127;
    if (type < 9) return 4;
    return type == static_cast<int32_t>(BuffKind::AffinityRow) ? 32767 : 1;
}

// nbGetHojoCounterMin @ 0x00267F18: stat counters go down to -4.
int32_t buffMin(int32_t type)
{
    return type >= 4 && type < 9 ? -4 : 0;
}

// nbSetHojoAddCounter @ 0x00267F58
int32_t addBuff(int32_t formindex, int32_t type, int32_t delta, bool preview)
{
    Party* party = GetPartyFromFormindex(formindex);
    if (!party)
        return 0;
    int32_t old = party->count[type];
    int32_t value = old + delta;
    if (type >= 0 && type < 20) {
        if (value > buffMax(type)) value = buffMax(type);
        if (value < buffMin(type)) value = buffMin(type);
    }
    if (!preview)
        party->count[type] = static_cast<int16_t>(value);
    return value - old;
}

// nbSetHojoKouka @ 0x00268030
//
// Mask bits, in the order they are applied:
//   0..9    pairs of (raise, lower) for Attack, Magic, Evasion, Defense, Accuracy
//   10      Dekaja: clear every raised stat counter
//   12..17  set counters 9..14 (elemental nulls, Makarakarn, Tetrakarn)
//   18      Dekunda: clear every lowered stat counter
//   24      Focus
// Note the clears happen last and run even in preview mode.
int32_t applyBuffs(int32_t formindex, uint32_t mask, int32_t amount, bool preview)
{
    int32_t total = 0;
    auto add = [&](int32_t type, int32_t delta) {
        int32_t change = addBuff(formindex, type, delta, preview);
        total += change < 0 ? -change : change;
    };

    for (int bit = 0; bit < 10; ++bit) {
        if (mask & (1u << bit))
            add(4 + bit / 2, (bit & 1) ? -amount : amount);
    }
    for (int bit = 12; bit < 18; ++bit) {
        if (mask & (1u << bit))
            add(9 + bit - 12, amount);
    }
    if (mask & 0x1000000)
        add(static_cast<int32_t>(BuffKind::Focus), amount);

    if (mask & 0x400) {   // Dekaja
        for (int type = 4; type <= 8; ++type) {
            int32_t value = buffCounter(formindex, type);
            if (value > 0) {
                total += value;
                setBuffCounter(formindex, type, 0);
            }
        }
    }
    if (mask & 0x40000) { // Dekunda
        for (int type = 4; type <= 8; ++type) {
            int32_t value = buffCounter(formindex, type);
            if (value < 0) {
                total -= value;
                setBuffCounter(formindex, type, 0);
            }
        }
    }
    return total;
}

// nbGetHojoRitu @ 0x002684B0
//
// A raised counter n gives (8 + 2n) / 8 = 1 + n/4; a lowered one (8 - |n|) / 8.
// Defense and Evasion are inverted (they scale what the *opponent* does), so
// Rakukaja lowers incoming damage by 1/8 per step and Rakunda raises it by 1/4.
// Devil 0x125's counters shift with the moon phase. Focus multiplies the
// attack ratio by 2.5.
Float buffMultiplier(int32_t formindex, int32_t type)
{
    UnitWork& unit = *GetUnitWorkFromFormindex(formindex);
    int32_t counter = buffCounter(formindex, type);
    if (unit.id == 0x125)
        counter += (static_cast<int32_t>(evt::GetAgeOfMoon()) - 4) / 2;

    Float result = 1.0f;
    if (counter != 0) {
        int32_t steps;
        bool inverted = type == static_cast<int32_t>(BuffKind::Evasion) || type == static_cast<int32_t>(BuffKind::Defense);
        if (inverted)
            steps = counter < 0 ? -counter * 2 : -counter;
        else
            steps = counter >= 0 ? counter * 2 : counter;
        result = (Float::fromInt(steps) + 8.0f) * 0.125f;
    }
    if (type == static_cast<int32_t>(BuffKind::Attack) && buffCounter(formindex, static_cast<int32_t>(BuffKind::Focus)) > 0)
        result = result * 2.5f;
    return result;
}

} // namespace nocturne::nb
