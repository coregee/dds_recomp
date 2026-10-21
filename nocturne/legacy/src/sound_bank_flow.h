#pragma once
#include <stdint.h>
void ps2SoundEnsureBank(uint64_t sound);
uint64_t ps2SoundPlay(uint64_t sound,uint64_t volume,uint64_t pan);
void nocturneSoundWaitCallback(uint32_t entry);
#if UINTPTR_MAX > UINT32_MAX
/* Test transport for the original unwritten private packet word at +4. */
uint32_t nocturneSoundPlayPrivateWord(void);
#endif
