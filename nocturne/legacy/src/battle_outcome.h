#ifndef NOCTURNE_BATTLE_OUTCOME_H
#define NOCTURNE_BATTLE_OUTCOME_H
#include <stdint.h>
void *nocturneResolveBattleOutcomeAddress(uint32_t address);
uint32_t nocturneBattleOutcomeStackPointer(void);
void nocturneBattleOutcomeSetStackPointer(uint32_t address);
/* Actual active bank reads; no shadow or expected-return provider. */
uint64_t nocturneBattleOutcomeReadGpr(unsigned reg);
uint32_t nocturneBattleOutcomeReadFpr(unsigned reg);
/* Whole existing native callee/frame bridges; source-defined masks only.
 * The transport must preserve unspecified actual lanes while retaining
 * genuine native RAM/frame/FCSR effects and native V0. */
uint64_t nocturneBattleOutcomeNativePrintf(uint32_t pc,uint64_t a0,uint64_t sp,uint64_t ra);
uint64_t nocturneBattleOutcomeNativeScaleLookup(uint32_t pc,uint64_t a0,uint64_t sp,uint64_t ra,uint64_t s0,uint64_t s1);
void nocturneBattleOutcomeNativeChoice(uint32_t pc,uint64_t a0,uint64_t a1,uint64_t sp,uint64_t ra,uint64_t s0);
void ps2BattleOutcome_001B17E0(uint64_t p0,uint64_t p1);
void ps2BattleOutcome_001E3B68(uint64_t p0,uint64_t p1);
void ps2BattleOutcome_001E3B70(uint64_t p0);
void ps2BattleOutcome_001E3B78(uint64_t p0,uint64_t p1,uint64_t p2);
void ps2BattleOutcome_001E3CC0(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4);
uint64_t ps2BattleOutcome_0024CE78(uint64_t p0,uint64_t p1,uint64_t p2);
void ps2BattleOutcome_0024CFF8(uint64_t p0,uint64_t p1,uint64_t p2);
void ps2BattleOutcome_0024D238(uint64_t p0,uint64_t p1);
uint64_t ps2BattleOutcome_0024D428(uint64_t p0,uint64_t p1);
uint64_t ps2BattleOutcome_00252CD8(uint64_t p0);
void ps2BattleOutcome_00256C00(uint64_t p0);
uint64_t ps2BattleOutcome_00257098(uint64_t p0);
void ps2BattleOutcome_002570B8(uint64_t p0);
uint64_t ps2BattleOutcome_00257210(uint64_t p0);
void ps2BattleOutcome_00257230(uint64_t p0);
uint64_t ps2BattleOutcome_002572C0(uint64_t p0);
void ps2BattleOutcome_002573A8(uint64_t p0);
uint64_t ps2BattleOutcome_00257440(uint64_t p0);
uint64_t ps2BattleOutcome_00262A68(uint64_t p0,uint64_t p1);
uint64_t ps2BattleOutcome_00262AC8(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3);
uint64_t ps2BattleOutcome_00263778(uint64_t p0,uint64_t p1,uint64_t p2);
uint64_t ps2BattleOutcome_002642E0(uint64_t p0,uint64_t p1);
uint64_t ps2BattleOutcome_00264368(uint64_t p0,uint64_t p1,uint64_t p2);
/* 24D428 carrier contains raw32 native F0, never an invented V0.
 * Six resident-F12 entries read the actual bank separately from integer
 * formals. This source is not a full volatile CPU/private-frame model. */
#endif
