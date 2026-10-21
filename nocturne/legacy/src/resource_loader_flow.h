#pragma once
#include <stdint.h>
void ps2ResourceProcessPhase(void);
uint64_t ps2ResourcePacFileEvent(uint64_t job,uint64_t event,uint64_t unused,uint64_t processed,uint64_t request);
uint64_t ps2ResourceReadFileEvent(uint64_t job,uint64_t event,uint64_t unused,uint64_t processed,uint64_t request);
uint64_t ps2ResourceWriteFileEvent(uint64_t job,uint64_t event,uint64_t unused,uint64_t processed,uint64_t request);
uint64_t ps2ResourcePump(void);
void nocturneResourcePacCompletionCallback(uint32_t entry,uint64_t request,uint64_t parameter);
#if UINTPTR_MAX > UINT32_MAX
/* Host transport context for diagnostic buffers passed at guest stack offsets. */
void nocturneResourceFrameEnter(uint32_t bytes);
void nocturneResourceFrameLeave(uint32_t bytes);
#endif
