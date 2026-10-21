#ifndef NOCTURNE_BATTLE_STATUS_PAIRS_H
#define NOCTURNE_BATTLE_STATUS_PAIRS_H
#include <stdint.h>
#include <stddef.h>
/* Real guest backing/shared native SP. Hooks intentionally unimplemented here. */
void *nocturneResolveBattleStatusPairsAddress(uint32_t address);
uint32_t nocturneBattleStatusPairsStackPointer(void);
void nocturneBattleStatusPairsSetStackPointer(uint32_t address);
uint64_t nocturneBattleStatusPairsReadGpr(unsigned reg);
uint32_t nocturneBattleStatusPairsReadFpr(unsigned reg);
void nocturneBattleStatusPairsWriteFpr(unsigned reg,uint32_t bits);
typedef struct BattleStatusPairsBoundary {uint32_t pc,defined_mask;uint64_t gpr[32];} BattleStatusPairsBoundary;
_Static_assert(sizeof(BattleStatusPairsBoundary)==264,"native frame request size");
_Static_assert(offsetof(BattleStatusPairsBoundary,gpr)==8,"native frame request lanes");
/* kind1=whole native printf;kind2=whole native246AB8. Publish only masked
 * lows, preserve actual upper lanes, then retain real RAM/frame side effects.
 * Unmasked zero placeholders are not native register values or publications. */
uint64_t nocturneBattleStatusPairsNativeCall(uint32_t kind,const BattleStatusPairsBoundary *request);
void ps2BattleStatusPairs_00253DE0(void);
uint64_t ps2BattleStatusPairs_00253E00(uint64_t context);
void ps2BattleStatusPairs_00254010(uint64_t context);
uint64_t ps2BattleStatusPairs_00254058(uint64_t context);
void ps2BattleStatusPairs_00254178(uint64_t context);
uint64_t ps2BattleStatusPairs_00254190(uint64_t context);
void ps2BattleStatusPairs_00254360(uint64_t context);
uint64_t ps2BattleStatusPairs_002543A0(uint64_t context);
/* All66 complete bodies are private native local-state functions; only the
 * eight source-checked callback roots have scalar public ABI here.
 * No helper identity/return ownership is inferred from an incidental V0. */
#endif
