#ifndef NOCTURNE_BATTLE_CALLBACK_CHOICE_H
#define NOCTURNE_BATTLE_CALLBACK_CHOICE_H
#include <stdint.h>
#include <stddef.h>
/* Existing identities, new bank-entry variants. No new recovery credit. */
uint64_t ps2BattleCallbackChoice_00253490(uint64_t context);
void ps2BattleCallbackChoice_00257488(uint64_t context);
uint64_t ps2BattleCallbackChoice_002577D8(uint64_t context);
void ps2BattleCallbackChoice_002532A8(uint64_t context,uint64_t value);
void *nocturneResolveBattleCallbackChoiceAddress(uint32_t address);
uint32_t nocturneBattleCallbackChoiceStackPointer(void);
void nocturneBattleCallbackChoiceSetStackPointer(uint32_t address);
uint64_t nocturneBattleCallbackChoiceReadGpr(unsigned reg);
/* Only masked low64 entries carry source-defined or genuine inherited values.
 * Unmasked array cells are placeholders, not native register initials. */
typedef struct BattleCallbackChoiceBoundary {
 uint32_t pc,defined_mask;
 uint64_t gpr[32];
} BattleCallbackChoiceBoundary;
_Static_assert(sizeof(BattleCallbackChoiceBoundary)==264,"Choice boundary size");
_Static_assert(offsetof(BattleCallbackChoiceBoundary,gpr)==8,"Choice boundary offset");
/* kind1: whole native printf; kind2: whole native246AB8 lookup. Normal
 * restoration retains actual RAM/private-frame/stdio/FCSR/Status effects.
 * Tail printf2577CC retains restored incoming RA, not invented PC+8. */
uint64_t nocturneBattleCallbackChoiceNativeCall(uint32_t kind,const BattleCallbackChoiceBoundary *request);
#endif
