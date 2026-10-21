#pragma once
#include <stdint.h>
uint64_t sdfModelNodeNew(void);
uint64_t sdfModelRootNew(void);
void sdfModelAllocNodeList(uint64_t root,uint64_t capacity);
void sdfModelNodeAdd(uint64_t root,uint64_t parent,uint64_t node);
void sdfModelNodeUnlink(uint64_t node);
void sdfModelNodeSetParent(uint64_t node,uint64_t parent);
void ps2ModelMakeMorphList(uint64_t root,uint64_t count);
uint64_t sdfModelMakeRoot(uint64_t textures,uint64_t definition);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolveModelRootCreationAddress(uint32_t address);
#endif
