#ifndef NOCTURNE_SCRIPT_PROCESS_H
#define NOCTURNE_SCRIPT_PROCESS_H
#include <stdint.h>
void scrLinkScriptHandleList(uint64_t work);
void scrUnlinkScriptHandleList(uint64_t work);
uint64_t scrStartScriptProcess(uint64_t priority,uint64_t work);
void scrInitGlobalWork(void);
uint64_t scrSearchScriptName(uint64_t name);
uint64_t scrSearchProcedureName(uint64_t data,uint64_t name);
void scrSetUserData(uint64_t process,uint64_t data);
uint64_t ps2ScriptGetUserData(uint64_t process);
uint64_t scrScriptProcess(uint64_t process);
void *nocturneResolveScriptProcessAddress(uint32_t address);
#endif
