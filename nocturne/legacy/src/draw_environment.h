#ifndef NOCTURNE_DRAW_ENVIRONMENT_H
#define NOCTURNE_DRAW_ENVIRONMENT_H
#include <stdint.h>
void ps2DrawBuildSingleRegisterGroup(uint32_t arg0,uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4,uint64_t arg5,uint64_t arg6,uint32_t arg7);
void ps2DrawBuildConfiguredEnvironment(uint32_t arg0,uint32_t arg1,uint32_t arg2);
void ps2DrawInitializeEnvironmentRecord(uint32_t arg0,uint32_t arg1);
void ps2DrawLinkEnvironmentRecord(uint32_t arg0,uint32_t arg1,uint32_t arg2);
void ps2DrawBuildContextReference180(uint32_t arg0,uint32_t arg1,uint64_t arg2);
void ps2DrawBuildContextReference70(uint32_t arg0,uint32_t arg1,uint64_t arg2);
void ps2DrawAppendStateReference1a0(uint32_t arg0,uint32_t arg1,uint32_t arg2);
void ps2DrawAppendStateReference1e0(uint32_t arg0,uint32_t arg1,uint32_t arg2);
void ps2DrawInitializeAuxiliaryRecord(uint32_t arg0,uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4);
void ps2DrawStoreNonnegativeModeByte(uint64_t arg0);
void ps2DrawResetGlobalState(void);
void *nocturneResolveDrawGlobalAddress(uint32_t address);
#endif
