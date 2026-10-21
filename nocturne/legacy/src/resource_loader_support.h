#pragma once
#include <stdint.h>
uint64_t ps2ResourceUnlinkActive(uint64_t request);
void ps2ResourcePushReusable(uint64_t manager,uint64_t request);
void ps2ResourceRemoveReusable(uint64_t manager,uint64_t request);
uint64_t fileGetMemHandle(uint64_t request);
uint64_t fileGetLoadPtr(uint64_t request);
uint64_t fileGetLoadSize(uint64_t request);
uint64_t fileCheckEnd(uint64_t request);
uint64_t ps2ResourcePacCheckEnd(uint64_t request);
uint64_t ps2ResourceQueuePacRead(uint64_t request);
uint64_t ps2ResourceQueueRawRead(uint64_t request);
uint64_t ps2ResourceQueueRawWrite(uint64_t request);
uint64_t ps2ResourceDrainCompleted(void);
void nocturneResourceCompletionCallback(uint32_t entry,uint64_t request,uint64_t parameter);
