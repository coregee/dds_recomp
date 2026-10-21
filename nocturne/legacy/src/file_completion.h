#ifndef NOCTURNE_FILE_COMPLETION_H
#define NOCTURNE_FILE_COMPLETION_H
#include <stdint.h>
void ps2SifRpcResponse(uint64_t packet);
void ps2SifRpcServerRequest(uint64_t packet);
void ps2FileRpcComplete(void);
void ps2FileRpcNotification(uint64_t packet,uint64_t callback_record);
void *nocturneResolveFileCompletionAddress(uint32_t address);
void nocturneFileCompletionInvoke(uint32_t entry,uint64_t argument);
#endif
