#ifndef NOCTURNE_SCRIPT_LIFETIME_H
#define NOCTURNE_SCRIPT_LIFETIME_H
#include <stdint.h>
uint64_t ps2KernelGetFontContextIndex(void);
uint64_t frCombineFontRequestEx(uint64_t first,uint64_t second,uint64_t mode);
uint64_t frDestroyFontRequestAfter(uint64_t request);
void itfPnlRelease(uint64_t panel);
void itfMesMngRequestMessageRelease(uint64_t id,uint64_t speaker);
void itfMesMngRequestSelectRelease(uint64_t id);
void itfMesReleaseAllWindow(uint64_t instance);
void itfMesReleaseAllVariable(uint64_t variable);
void ps2MessageManagerReleaseInner(uint64_t id);
void itfMesMngRelease(uint64_t id);
void scrReleaseScript(uint64_t work);
uint64_t scrAllReleaseScript(void);
void scrScriptShutdown(uint64_t process);
void *nocturneResolveScriptLifetimeAddress(uint32_t address);
#endif
