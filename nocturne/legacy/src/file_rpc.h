#ifndef NOCTURNE_FILE_RPC_H
#define NOCTURNE_FILE_RPC_H
#include <stdint.h>
void ps2SifSyncDataCache(uint64_t address,uint64_t bytes);
uint64_t ps2SifRpcPacketTake(uint64_t queue);
void ps2SifRpcPacketRelease(uint64_t packet);
uint64_t ps2SifSendCommand(uint64_t command,uint64_t mode,uint64_t packet,uint64_t packet_bytes,uint64_t source,uint64_t destination,uint64_t bytes);
uint64_t ps2SifSendCommandDefault(uint64_t command,uint64_t packet,uint64_t packet_bytes,uint64_t source,uint64_t destination,uint64_t bytes);
uint64_t ps2SifRpcCall(uint64_t client,uint64_t command,uint64_t mode,uint64_t send,uint64_t send_bytes,uint64_t receive,uint64_t receive_bytes,uint64_t callback,uint32_t callback_parameter);
uint64_t ps2SifRpcBind(uint64_t client,uint64_t server,uint64_t mode);
uint64_t ps2KernelSifSetDma(const void *packets,uint64_t count);
uint64_t ps2KernelSifSetDmaInterrupt(const void *packets,uint64_t count);
uint64_t ps2KernelDeleteSema(uint64_t id);
void ps2FileRpcDescriptorInitialize(void);
uint64_t ps2FileRpcDescriptorTake(void);
uint64_t ps2FileRpcDescriptorLookup(uint64_t id);
void ps2FileRpcLockInitialize(void);
uint64_t ps2FileRpcLock(uint64_t command);
uint64_t ps2FileRpcUnlock(void);
uint64_t ps2FileRpcVersionMismatch(void);
/* Host relocation, syscall/cache value and unwritten stack operand boundaries. */
void *nocturneResolveFileRpcAddress(uint32_t address);
uint64_t nocturneRpcDmaValue(uint32_t selector,const void *packets,uint64_t count);
uint64_t nocturneRpcDeleteSemaValue(uint64_t id);
void nocturneRpcCacheValue(uint32_t operation,uint32_t address);
void nocturneRpcSyncValue(uint32_t type);
uint32_t nocturneRpcSemaUnwrittenOption(void);
#endif
