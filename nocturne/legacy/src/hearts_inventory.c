/* Connected item/Magatama acquisition and learned skills, SLUS_209.11.
 * Logical game inputs: nonnegative item IDs, Hearts IDs0..25, valid ownership
 * counts and learned-skill slots. The PS2 original adds no capacity checks. */
#include "nocturne.h"

/* 002138c0: table25 bytes at0053d6e8, selected by unsigned16 ID-0x40. */
int8_t fclChkItemHearts(uint16_t itemid)
{
    uint16_t index = (uint16_t)(itemid - 0x40);
    return index < 25 ? g_fclItemHeartsTable[index] : 0;
}

/* 002328c8: byte ownership entries compared with the signed8 argument. */
int8_t cmpChkHaveHearts(int8_t id)
{
    for (uint32_t i = 0; i < g_datGlobalWork->hearts_owned_count; ++i)
        if ((int32_t)g_datGlobalWork->hearts_owned[i] == id) return 1;
    return 0;
}

/* 00232880: normal Hearts1..24, excluding25. */
int32_t cmpChkHaveNormalHeartsAll(void)
{
    for (int8_t id = 1; id <= 24; ++id)
        if (!cmpChkHaveHearts(id)) return 0;
    return 1;
}

/* 002221d0: low nibble of the per-ID byte, upper bits preserved. */
int8_t cmbGetHeartsAfterSkillNums(uint8_t id)
{
    return g_datGlobalWork->hearts_skill_state[id] & 15;
}

/* 002224d8: 12 ushort slots per ID; increment the entire state byte. */
void cmbAddHeartsSkill(int8_t id, uint16_t skill)
{
    uint32_t count = (uint8_t)cmbGetHeartsAfterSkillNums((uint8_t)id);
    g_datGlobalWork->hearts_learned_skills[(uint8_t)id][count] = skill;
    ++g_datGlobalWork->hearts_skill_state[(uint8_t)id];
}

/* 00222550: only nonzero skills whose required level is zero are appended.
 * The PS2 updates both the supplied unit and the global per-Hearts list. */
int8_t cmbCreateDefaultHeartsSkill(uint8_t id, datUnitWork_PS2 *unit)
{
    if (id == 0) return 0;
    for (uint32_t i = 0; i < 8; ++i) {
        const cmbHeartsSkillEntry_PS2 *entry = &g_cmbHeartsSkillRows[id].skills[i];
        if (entry->skill != 0 && entry->level == 0) {
            uint16_t index = unit->skillcnt;
            unit->skillcnt = (uint16_t)(index + 1);
            unit->skill[index] = entry->skill;
            cmbAddHeartsSkill((int8_t)id, entry->skill);
        }
    }
    return (int8_t)unit->skillcnt;
}

/* 002452c8: duplicate search uses the full32-bit ID, stores only low8. */
int32_t datAddHearts(int32_t id)
{
    for (uint32_t i = 0; i < g_datGlobalWork->hearts_owned_count; ++i)
        if ((int32_t)g_datGlobalWork->hearts_owned[i] == id) return 0;
    g_datGlobalWork->hearts_owned[g_datGlobalWork->hearts_owned_count++] = (uint8_t)id;
    g_datGlobalWork->hearts_skill_state[id] = 0;
    if (cmpChkHaveNormalHeartsAll()) evtBitOn(0x860);
    cmbCreateDefaultHeartsSkill((uint8_t)id, &g_datGlobalWork->units[0]);
    return 1;
}

/* 002442e0: signed32 wrapping sums, quantity clamps and special event item.
 * Quantity zero still sets quest ownership; Hearts dispatch ignores quantity. */
void datAddItem(int32_t id, int32_t num)
{
    int8_t hearts = fclChkItemHearts((uint16_t)id);
    if (hearts != 0) { datAddHearts(hearts); return; }
    if (id < 0x70) {
        int32_t sum = (int32_t)((uint32_t)g_datGlobalWork->item_counts[id] + (uint32_t)num);
        if (sum < 0) sum = 0;
        if (sum > 99) sum = 99;
        g_datGlobalWork->item_counts[id] = (uint8_t)sum;
        return;
    }
    evtBitOn(id + 0x360);
    if (id != 0x8d || num == 0) return;
    int32_t sum = (int32_t)((uint32_t)g_datGlobalWork->item_counts[id] + (uint32_t)num);
    if (num > 0) {
        if (sum >= 100) sum = 99;
    } else if (sum <= 0) {
        evtBitOff(0x3ed);
        sum = 0;
    }
    g_datGlobalWork->item_counts[id] = (uint8_t)sum;
}

/* 00213938: dispatch explicitly and return1 even for duplicate acquisition. */
int32_t fclAddItem(uint16_t itemid, int32_t num)
{
    int8_t hearts = fclChkItemHearts(itemid);
    if (hearts != 0) datAddHearts(hearts);
    else datAddItem(itemid, num);
    return 1;
}
