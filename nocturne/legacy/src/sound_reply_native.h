#ifndef NOCTURNE_SOUND_REPLY_NATIVE_H
#define NOCTURNE_SOUND_REPLY_NATIVE_H
#include "battle_panel_color_native.h"
/* Entire139-member002C2338, actual sharedCPU128 and guest frame/RAM.
 * Body handled1/0 is host recognition only; nativeV0 stays in the bank.
 * Typed entry writes only actual A0/A1 low64 and preserves their upper64.
 * Native frame allocation/saves happen even on an out-of-range selector. */
uint32_t nocturneSoundReplyNativeBody(uint32_t entry);
uint64_t ps2SoundRpcReplyNative_002C2338(uint64_t command,uint64_t request);
/* UNIMPLEMENTED genuine native callee route. Actual RA and delay-slot
 * effects are already published. Execute the real target against this bank
 * and RAM or stop without returning; no supplied semantic result suffices. */
void nocturneSoundReplyNativeInvoke(uint64_t target,uint32_t call_pc);
_Noreturn void nocturneSoundReplyNativeUnprovidedJump(uint64_t target,uint32_t jump_pc);
#endif
