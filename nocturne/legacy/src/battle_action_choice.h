#ifndef NOCTURNE_BATTLE_ACTION_CHOICE_H
#define NOCTURNE_BATTLE_ACTION_CHOICE_H
#include <stdint.h>
/* Shared actual guest RAM/SP with real typed process/pool/packet callees. */
void *nocturneResolveBattleActionChoiceAddress(uint32_t address);
uint32_t nocturneBattleActionChoiceStackPointer(void);
/* Set synchronizes actual Core/sorter SP and EffectHost CPU29 used by
 * registered native packet wrappers; no guest RAM or result writes. */
void nocturneBattleActionChoiceSetStackPointer(uint32_t address);
void ps2BattleActionChoice_00251EF0(uint64_t p0);
void ps2BattleActionChoice_00251FD8(uint64_t p0,uint64_t p1);
uint64_t ps2BattleActionChoice_00252400(uint64_t p0);
uint64_t ps2BattleActionChoice_002525F0(uint64_t p0);
uint64_t ps2BattleActionChoice_00252720(uint64_t p0);
uint64_t ps2BattleActionChoice_002529D0(uint64_t p0);
void ps2BattleActionChoice_002532A8(uint64_t p0,uint64_t p1);
uint64_t ps2BattleActionChoice_00253490(uint64_t p0);
void ps2BattleActionChoice_00257488(uint64_t p0);
uint64_t ps2BattleActionChoice_002577D8(uint64_t p0);
void ps2BattleActionChoice_00257E30(uint64_t p0);
uint64_t ps2BattleActionChoice_00257EB0(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4);
void ps2BattleActionChoice_00257FA8(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4);
/* All arguments retain raw64 until original operations narrow them.
 * Constructor/init use A0,A1,A2,A3,T0. Shutdown receives processID.
 * Native BREAK7 synchronizes current guestSP before the nonreturning
 * nocturne_break boundary; it does not unwind guest frames on trap.
 * Fullvolatile/HI-LO/private-save-frame identity is outside this ABI. */
#endif
