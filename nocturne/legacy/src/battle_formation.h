#ifndef NOCTURNE_BATTLE_FORMATION_H
#define NOCTURNE_BATTLE_FORMATION_H
#include <stdint.h>
/* Actual ordinary RAM/SP shared with real typed constructor/pose calls. */
void *nocturneResolveBattleFormationAddress(uint32_t address);
uint32_t nocturneBattleFormationStackPointer(void);
void nocturneBattleFormationSetStackPointer(uint32_t address);
/* Private transport boundaries: real incoming banks and existing whole-native callees. */
uint64_t nocturneBattleFormationReadGpr(unsigned reg);
uint32_t nocturneBattleFormationReadFpr(unsigned reg);
uint64_t nocturneBattleFormationNativePrintf(uint32_t pc,uint64_t a0,uint64_t sp,uint64_t ra);
uint64_t nocturneBattleFormationNativeScaleLookup(uint32_t pc,uint64_t a0,uint64_t sp,uint64_t ra,uint64_t s0,uint64_t s1);
uint64_t ps2BattleFormation_0024D490(uint64_t p0,uint64_t p1);
void ps2BattleFormation_0024D550(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3);
void ps2BattleFormation_0024D8C0(uint64_t p0,uint64_t p1,uint64_t p2);
void ps2BattleFormation_0024E178(uint64_t p0,uint64_t p1,uint64_t p2);
void ps2BattleFormation_00259740(uint64_t p0,uint64_t p1);
void ps2BattleFormation_0028A2E0(uint64_t p0);
void ps2BattleFormation_0028A340(uint64_t p0,uint64_t p1);
void ps2BattleFormation_0028A758(uint64_t p0);
/* 24D490 defines endtype byte in V0; other scalar roles are VOID.
 * 28A2E0 nevertheless defines raw128 VF10 through existing actual VU
 * primitive hooks. Observe that bank explicitly; no hidden V0 answer.
 * VF transfers require independently backed16-aligned resource/frame
 * vectors. No arbitrary unaligned COP2-fault profile is claimed.
 * All integer args stay raw64 until native narrowing operations.
 * Fullvolatile/HI-LO/private-saveframe identity is excluded. */
#endif
