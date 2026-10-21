#ifndef NOCTURNE_FIELD_SKILL_H
#define NOCTURNE_FIELD_SKILL_H
#include <stdint.h>

/* SLUS_209.11 raw EE integer arguments. The four formula interfaces retain
 * their actual A0..A3 calling slots even where a slot is not semantically read.
 * AffinityRate returns F0; the other non-void functions return raw64 V0 bits.
 * This readable algorithm unit does not transport volatile CPU/FPR banks or
 * original guest private frames. Those are separate full-machine obligations. */
uint64_t ps2FieldSkillPhysicalPower_00242E00(uint64_t skill,uint64_t source,uint64_t target,uint64_t power);
uint64_t ps2FieldSkillPhysicalRecovery_00242FE0(uint64_t skill,uint64_t source,uint64_t target,uint64_t power);
uint64_t ps2FieldSkillMagicPower_00242FF8(uint64_t skill,uint64_t source,uint64_t target,uint64_t power);
uint64_t ps2FieldSkillMagicRecovery_00243170(uint64_t skill,uint64_t source,uint64_t target,uint64_t power);
uint64_t ps2FieldSkillMaxHpPower_00243200(uint64_t skill,uint64_t source,uint64_t target,uint64_t power);
float ps2FieldSkillAffinityRate_002432D0(uint64_t skill,uint64_t source,uint64_t target);
uint64_t ps2FieldSkillEffectAmount_00243368(uint64_t skill,uint64_t type,uint64_t source,uint64_t target);
uint64_t ps2FieldSkillStatus_00243760(uint64_t skill,uint64_t source,uint64_t target);
uint64_t ps2FieldSkillExecute_00243998(uint64_t skill,uint64_t source,uint64_t target);
void ps2FieldSkillPartyDamage_002447C0(uint64_t type);
void ps2FieldSkillPartyStatusDamage_00244A38(uint64_t type);
void ps2FieldSkillPartyPipeDamage_00244CC0(uint64_t first,uint64_t second);
void ps2FieldSkillPartyRecover_00244DD8(void);
uint64_t ps2FieldSkillScriptPartyDamage_0010D078(void);
uint64_t ps2FieldSkillScriptPartyRecover_0010D0A0(void);
uint64_t ps2FieldSkillScriptPartyRecoverSilent_0010D0D0(void);

/* Resolves actual guest RAM, including the original read-only data tables.
 * Bind canonical dat/RNG/event/script/sound dependencies to the same graph.
 * No game-function result callback or detached record copy is permitted. */
void *nocturneResolveFieldSkillAddress(uint32_t address);
#endif
