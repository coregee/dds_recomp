#ifndef NOCTURNE_BATTLE_CALLBACK_NATIVE_TRANSPORT_H
#define NOCTURNE_BATTLE_CALLBACK_NATIVE_TRANSPORT_H
#include "battle_callback_native.h"
/* Passive actual call receipts. Entry/Outcome竊辰hoice have width0;
 * Update/Printf width64. Kinds1/2/3/4 respectively.
 * Slot is reserved before publication/call, and completed only after genuine
 * normal return. A trapped/nonreturning callback leaves an incomplete slot.
 * Ordinals are entry order, including nested callbacks. No result is supplied.
 * Only the most recent4096 slots are retained, addressed by absolute ordinal.
 * At UINT32_MAX Count saturates and recording stops; callbacks still execute.
 * Nested eviction leaves the newer slot intact on an outer normal return.
 */
typedef struct BattleCallbackNativeReceipt {
 uint32_t version,ordinal,kind,target,return_width,completed;
 BattleCallbackNativeBoundary boundary;
 uint64_t gp;
 uint32_t f20_f25[6];
 uint64_t return_sp,result;
} BattleCallbackNativeReceipt;
_Static_assert(sizeof(BattleCallbackNativeReceipt)==144,"Callback receipt size");
_Static_assert(offsetof(BattleCallbackNativeReceipt,boundary)==24&&offsetof(BattleCallbackNativeReceipt,gp)==96&&offsetof(BattleCallbackNativeReceipt,f20_f25)==104&&offsetof(BattleCallbackNativeReceipt,return_sp)==128&&offsetof(BattleCallbackNativeReceipt,result)==136,"Callback receipt offsets");
/* Caller-owned reset outside invocation, after storing any trapped receipt.
 * No hidden active/reentry flag survives a nonlocal arithmetic-trap unwind. */
void nocturneBattleCallbackNativeReceiptReset(void);
uint32_t nocturneBattleCallbackNativeReceiptCount(void);
void nocturneBattleCallbackNativeReceiptGet(uint32_t index,BattleCallbackNativeReceipt *out);
#endif
