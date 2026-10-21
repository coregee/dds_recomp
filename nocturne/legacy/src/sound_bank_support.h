#ifndef NOCTURNE_SOUND_BANK_SUPPORT_H
#define NOCTURNE_SOUND_BANK_SUPPORT_H
#include <stdint.h>
uint64_t ps2DataCacheScanRange(uint64_t first,uint64_t last);
uint64_t ps2DataCacheInvalidateRange(uint64_t first,uint64_t last);
uint64_t ps2SoundBankStatus(uint64_t sound);
uint64_t ps2SoundBuildPath(uint64_t output,uint64_t name);
uint64_t ps2LibcSprintf(uint64_t output,uint64_t format,...);
/* Cache instructions and observed TagLo values are platform operands. */
void nocturneSoundCacheSync(void);
uint32_t nocturneSoundCacheOperation(uint32_t operation,uint32_t index);
#endif
