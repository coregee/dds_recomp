#ifndef NOCTURNE_BATTLE_REWARD_DEPENDENCIES_H
#define NOCTURNE_BATTLE_REWARD_DEPENDENCIES_H
#include <stdint.h>
/* Complete fixed native bodies. External routes must execute actual registered callees;no invented result or native clobber is permitted. */
uint32_t nocturneBattleRewardDependencyBody(uint32_t entry);
void nocturneBattleRewardNativeExternal(uint32_t target,uint32_t pc);
void nocturneBattleRewardNativeIndirect(uint64_t target,uint32_t pc);
_Noreturn void nocturneBattleRewardNativeTrap(uint32_t code,uint32_t pc);
void nocturneBattleRewardNativeCpuRead(unsigned reg,uint32_t words[4]);
void nocturneBattleRewardNativeCpuWrite(unsigned reg,const uint32_t words[4]);
void nocturneBattleRewardNativeVuRead(unsigned reg,uint32_t words[4]);
void nocturneBattleRewardNativeVuWrite(unsigned reg,const uint32_t words[4]);
uint32_t nocturneBattleRewardNativeStackPointer(void);
void nocturneBattleRewardNativeSetStackPointer(uint32_t address);
uint32_t nocturneBattleRewardNativeFcsr(void);
void *nocturneResolveBattleRewardNativeAddress(uint32_t address);
uint64_t ps2BattleRewardDependency_0021F838(void);
uint64_t ps2BattleRewardDependency_0021F898(void);
uint64_t ps2BattleRewardDependency_00223628(void);
uint64_t ps2BattleRewardDependency_00223668(void);
uint64_t ps2BattleRewardDependency_00223728(void);
uint64_t ps2BattleRewardDependency_00223928(void);
uint64_t ps2BattleRewardDependency_001FEF20(void);
uint64_t ps2BattleRewardDependency_00243C28(void);
uint64_t ps2BattleRewardDependency_00243D28(void);
uint64_t ps2BattleRewardDependency_00244238(void);
uint64_t ps2BattleRewardDependency_002442E0(void);
uint64_t ps2BattleRewardDependency_002138C0(void);
uint64_t ps2BattleRewardDependency_001E0ED0(void);
uint64_t ps2BattleRewardDependency_001E0F10(void);
uint64_t ps2BattleRewardDependency_001005E8(void);
uint64_t ps2BattleRewardDependency_00100760(void);
uint64_t ps2BattleRewardDependency_001009A0(void);
uint64_t ps2BattleRewardDependency_00100D70(void);
uint64_t ps2BattleRewardDependency_00100E08(void);
uint64_t ps2BattleRewardDependency_001015B0(void);
uint64_t ps2BattleRewardDependency_00101738(void);
uint64_t ps2BattleRewardDependency_00101AF8(void);
uint64_t ps2BattleRewardDependency_00101B80(void);
uint64_t ps2BattleRewardDependency_002452B8(void);
uint64_t ps2BattleRewardDependency_00269318(void);
uint64_t ps2BattleRewardDependency_0026A840(void);
uint64_t ps2BattleRewardDependency_0026A870(void);
uint64_t ps2BattleRewardDependency_00242AE8(void);
uint64_t ps2BattleRewardDependency_002D1B88(void);
uint64_t ps2BattleRewardDependency_002D1C40(void);
uint64_t ps2BattleRewardDependency_002D34A0(void);
uint64_t ps2BattleRewardDependency_002D3578(void);
uint64_t ps2BattleRewardDependency_002452C8(void);
uint64_t ps2BattleRewardDependency_00222550(void);
uint64_t ps2BattleRewardDependency_00232880(void);
uint64_t ps2BattleRewardDependency_002328C8(void);
uint64_t ps2BattleRewardDependency_002224D8(void);
uint64_t ps2BattleRewardDependency_002221D0(void);
#endif
