#ifndef NOCTURNE_FIELD_ENCOUNTER_H
#define NOCTURNE_FIELD_ENCOUNTER_H
#include <stddef.h>
#include <stdint.h>

/* Original SLUS_209.11 inline pack, not the HD managed object. Names describe
 * the recovered consumers. Original pack indexing is unchecked word arithmetic. */
typedef struct NocturneEncounterChoice_PS2 {
    uint16_t encounter, weight;
    uint32_t unknown;
} NocturneEncounterChoice_PS2;
typedef struct NocturneEncounterCondition_PS2 {
    int32_t rate_adjustment;
    NocturneEncounterChoice_PS2 choices[12];
} NocturneEncounterCondition_PS2;
typedef struct NocturneEncounterPack_PS2 {
    uint8_t unknown_00[4];
    uint16_t music, moon_mask, moon_condition, event_a, event_b;
    uint8_t conditions[4], unknown_12[2];
    NocturneEncounterCondition_PS2 condition[4];
} NocturneEncounterPack_PS2;
_Static_assert(sizeof(NocturneEncounterChoice_PS2)==8,"native weighted choice stride");
_Static_assert(sizeof(NocturneEncounterCondition_PS2)==100,"native condition stride");
_Static_assert(sizeof(NocturneEncounterPack_PS2)==420,"native encounter pack stride");
_Static_assert(offsetof(NocturneEncounterPack_PS2,condition)==0x14,"condition base");

/* Raw integer arguments retain the original low64 ABI. The step input occupies
 * F12 and crosses the host boundary as a float's exact raw32 representation.
 * Guest addresses, arithmetic and halfword counters wrap as on the EE.
 * This readable algorithm layer excludes volatile banks/private frames. */
uint64_t ps2FieldEncounterCondition_0028C9F0(uint64_t pack);
uint64_t ps2FieldEncounterThreshold_0028CB68(uint64_t pack);
uint64_t ps2FieldEncounterCount_0028CC98(void);
uint64_t ps2FieldEncounterAdvance_0028CCA8(uint64_t pack,float distance);
uint64_t ps2FieldEncounterCheckLevel_0028CEE0(uint64_t encounter);
void ps2FieldEncounterReset_0028CFB0(void);
uint64_t ps2FieldEncounterMusic_0028CFC8(uint64_t pack,uint64_t encounter);
uint64_t ps2FieldEncounterBattleMusic_0028D028(void);
uint64_t ps2FieldEncounterFieldMusic_0028D050(uint64_t encoded);
void *nocturneResolveFieldEncounterAddress(uint32_t address);
#endif
