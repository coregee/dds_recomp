#pragma once
#include <stdint.h>
uint64_t ps2ModelPacRecordIsPib(uint64_t record);
uint64_t ps2ModelPibVersion(uint64_t header);
uint64_t ps2ModelPibEffectCount(uint64_t header);
uint64_t ps2ModelPibMotionCount(uint64_t header);
uint64_t ps2PacDiscardRecord(uint64_t record);
uint64_t ps2ModelRegisterLegacyPac(uint64_t record,uint64_t group,uint64_t id,uint64_t flags);
uint64_t ps2ModelRegisterPac(uint64_t record,uint64_t group,uint64_t id,uint64_t flags);
void ps2ModelPacJobRelease(uint64_t job);
void ps2ModelPacLoadComplete(uint64_t request,uint64_t job);
uint64_t ps2ModelRequestPac(uint64_t group,uint64_t id,uint64_t flags,uint64_t path,uint64_t callback,uint64_t parameter);
uint64_t ps2ModelWaitRegistered(uint64_t group,uint64_t id);
uint64_t ps2ModelAcquireResource(uint64_t group,uint64_t id,uint64_t blocking);
uint64_t ps2ModelAcquireResourceBlocking(uint64_t group,uint64_t id);
uint64_t ps2ModelContextCreate(uint64_t group,uint64_t id);
void ps2ModelChangeMotionDefault(uint64_t context,uint64_t group,uint64_t cut);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolveModelPacLoadingAddress(uint32_t address);
uint32_t nocturneModelPacLocal(void *buffer,uint32_t bytes);
void nocturneModelPacEndLocal(void);
uint64_t nocturneModelPacStrchr(uint64_t source,uint64_t character);
void nocturneModelPacNotify(uint32_t target,uint64_t argument);
#endif
