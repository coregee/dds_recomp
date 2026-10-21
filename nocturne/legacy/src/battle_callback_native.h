#ifndef NOCTURNE_BATTLE_CALLBACK_NATIVE_H
#define NOCTURNE_BATTLE_CALLBACK_NATIVE_H
#include <stdint.h>
#include <stddef.h>
/* Two already registered parent identities. No new function credit. */
void ps2BattleCallbackNative_00257C80(uint64_t context,uint64_t raw_state);
uint64_t ps2BattleCallbackNative_00257CD0(uint64_t process);
/* Named low64 payload, NOT a captured/zero-filled full CPU bank.
 * Only bits in defined_mask carry native values; excluded fields are zero
 * placeholders and MUST NOT be published or interpreted as actual registers.
 * Preserve every active upper64 lane and all unspecified actual bank inputs.
 */
typedef struct BattleCallbackNativeBoundary {
 uint32_t pc,defined_mask;
 uint64_t v0,v1,a0,a1,s0,s1,sp,ra;
} BattleCallbackNativeBoundary;
_Static_assert(sizeof(BattleCallbackNativeBoundary)==72,"Callback boundary layout");
_Static_assert(offsetof(BattleCallbackNativeBoundary,pc)==0&&offsetof(BattleCallbackNativeBoundary,defined_mask)==4&&offsetof(BattleCallbackNativeBoundary,v0)==8&&offsetof(BattleCallbackNativeBoundary,v1)==16&&offsetof(BattleCallbackNativeBoundary,a0)==24&&offsetof(BattleCallbackNativeBoundary,a1)==32&&offsetof(BattleCallbackNativeBoundary,s0)==40&&offsetof(BattleCallbackNativeBoundary,s1)==48&&offsetof(BattleCallbackNativeBoundary,sp)==56&&offsetof(BattleCallbackNativeBoundary,ra)==64,"Callback boundary offsets");
/* Unimplemented genuine providers: real guest RAM, joined Core/sorter+CPU29,
 * and actual incoming saved registers16/17/GP28/RA31. No guessed initials. */
void *nocturneResolveBattleCallbackNativeAddress(uint32_t address);
uint32_t nocturneBattleCallbackNativeStackPointer(void);
void nocturneBattleCallbackNativeSetStackPointer(uint32_t address);
uint64_t nocturneBattleCallbackNativeReadGpr(unsigned reg);
/* All three hooks remain unresolved until independently reviewed bindings.
 * Entry: pc257CB0 maskA000003C; nested Process addsS0/S1→A003003C.
 * Update: pc257DDC maskA003001C. Never publish invented A1 on ADPCM path.
 * Printf: pc257D64 fixed literal5440E8, maskA0030010 includes liveS0/S1.
 * Join source SP/RA and invoke actual typed algorithm, not supplied results.
 * Check normal callback SP/callee-save ABI before transport restoration.
 * Retain real RAM/private-frame/stdio/FCSR/Status/VU/trace effects. Update
 * returns genuine raw64 V0; Entry has no defined scalar result. NativePrintf
 * returns actual native V0. Nonreturn/trap must not be resumed or defaulted.
 */
void nocturneBattleCallbackNativeEntry(const BattleCallbackNativeBoundary *request);
uint64_t nocturneBattleCallbackNativeUpdate(const BattleCallbackNativeBoundary *request);
uint64_t nocturneBattleCallbackNativePrintf(const BattleCallbackNativeBoundary *request);
#endif
