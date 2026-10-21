#ifndef NOCTURNE_CD_LIFECYCLE_H
#define NOCTURNE_CD_LIFECYCLE_H
#include <stdint.h>
uint64_t ps2CdSetReadCallback(uint64_t callback);
void ps2CdReplyNotify(uint64_t packet);
_Noreturn void ps2CdCallbackThreadMain(void);
uint64_t ps2CdEnsureCallbackThread(uint64_t priority,uint64_t stack,uint64_t stack_bytes);
void ps2CdReadCopyReply(uint64_t packet);
void ps2CdExit(void);
uint64_t ps2CdSetCommandCallback(uint64_t callback,uint64_t parameter);
void ps2CdCommandCallback(void);
uint64_t ps2CdRegisterCommandCallback(void);
uint64_t ps2CdInitialize(uint64_t mode);
void ps2SifRemoveCommandHandler(uint64_t command);
uint64_t ps2KernelExitThreadRaw(void);
void nocturneCdLifecycleCallback(uint32_t callback,uint64_t parameter);
#endif
