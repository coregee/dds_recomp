#ifndef NOCTURNE_SDK_MEMORY_CARD_CALLBACKS_H
#define NOCTURNE_SDK_MEMORY_CARD_CALLBACKS_H
#include <stdint.h>
/* Two original indirect RPC callbacks, currently omitted from the function
 * inventory. Ordinary initialized RAM only; uncached address bit is retained. */
void ps2McReadFixAlign_002CE330(uint64_t reply);
void ps2McGetInfoApdx_002CE7B0(uint64_t reply);
void *nocturneResolveSdkMemoryCardAddress(uint32_t address);
#endif
