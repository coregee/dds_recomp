#ifndef NOCTURNE_UNIT_PROGRESSION_H
#define NOCTURNE_UNIT_PROGRESSION_H
#include <stdint.h>

/* SLUS_209.11 integer argument slots. Pointers are low32 guest addresses;
 * comparisons retain full64 inputs where the original branch does so.
 * Defined integer results retain the original sign-extended word in V0.
 * This readable unit does not transport original volatile registers, HI/LO
 * banks or private guest save frames. ReasonRank's normal rank domain is0..2;
 * other indexes address original private/saved-frame RAM, not a fourth rank. */
void ps2UnitRecalculateMaxHpMp_00240A98(uint64_t unit);
uint64_t ps2UnitMagicHitPower_00242CB0(uint64_t unit);
uint64_t ps2UnitEvasionPower_00242D50(uint64_t unit);
uint64_t ps2UnitAffinityFlags_00244098(uint64_t unit,uint64_t attribute);
void ps2UnitAddMakaPercent_00244268(uint64_t percent);
uint64_t ps2UnitPlayerParameter_002445C0(uint64_t parameter);
void ps2UnitAddPlayerParameter_00244610(uint64_t parameter,uint64_t amount);
uint64_t ps2UnitCompanionParameter_00244668(uint64_t species,uint64_t parameter);
uint64_t ps2UnitPlayerAlignment_002446B0(void);
void ps2UnitKillCompanion_002446F8(uint64_t species);
void ps2UnitInitializeCompanion_00244EF8(uint64_t species,uint64_t unit);
uint64_t ps2UnitAddCompanion_00245020(uint64_t species,uint64_t join_party);
void ps2UnitAddUniqueCompanion_00245180(uint64_t species,uint64_t join_party,uint64_t unique_id);
uint64_t ps2UnitFindUniqueCompanion_002451F0(uint64_t unique_id);
void ps2UnitAddExperience_002452B8(uint64_t unit,uint64_t experience);
void ps2UnitRemoveMagatama_00245380(void);
void ps2UnitEquipMagatama_002453E8(uint64_t id);
void ps2UnitApplyRecoverySkill_00245478(uint64_t unit,uint64_t skill);
void ps2UnitRecoverFieldParty_002455B8(void);
uint64_t ps2UnitFindTreasureSkillOwner_002456D0(void);
void ps2UnitClearPartyCommandMemory_00245808(void);
void ps2UnitAddReasonPoints_00245890(uint64_t reason,uint64_t amount);
uint64_t ps2UnitReasonRank_002458D0(uint64_t rank);
void ps2UnitRefreshCompanion_00245D30(uint64_t species,uint64_t unit);
/* These two original bodies are exactly JR RA / NOP and read no arguments. */
void ps2UnitMagatamaEquipHook_00221550(void);
void ps2UnitMagatamaUnequipHook_00221558(void);

/* All dependencies must share the same backed guest graph, descriptor tables,
 * globals and real RNG/processor primitives. This is address transport only. */
void *nocturneResolveUnitProgressionAddress(uint32_t address);
#endif
