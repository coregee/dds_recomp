#pragma once
#include <stdint.h>
uint64_t ps2ModelEnsureWorkspace(uint64_t node);
void ps2ModelFreeCommandLists(uint64_t node);
uint64_t ps2ModelWriteReturnPacket(uint64_t packet);
uint64_t ps2ModelWriteIndexedAssetPacket(uint64_t root,uint64_t index,uint64_t packet,uint64_t frame);
uint64_t ps2ModelMeasureCommandList(uint64_t list,uint64_t count,uint64_t quadwords);
uint64_t ps2ModelBuildIndexedPayload(uint64_t node,uint64_t command,uint64_t packet,uint64_t frame);
uint64_t ps2ModelBuildNodeRefsPayload(uint64_t node,uint64_t command,uint64_t packet,uint64_t frame);
uint64_t ps2ModelPrependCommandNode(uint64_t node,uint64_t selector,uint64_t pass);
void ps2ModelBuildCommandList(uint64_t node,uint64_t list,uint64_t selector,uint64_t alternate,uint64_t pass);
void ps2ModelNodeSetCommands(uint64_t node,uint64_t item);
void ps2ModelResetCommands(uint64_t node,uint64_t list,uint64_t selector);
uint64_t ps2ModelMake(uint64_t textures,uint64_t definition);
void ps2ModelEnsureReferencedWorkspaces(uint64_t root,uint64_t command);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolveModelDrawCommandAddress(uint32_t address);
uint32_t nocturneModelCommandIncomingCount(void);
void nocturneModelCommandStoreCount(uint32_t count);
void nocturneModelCommandBeginItem(void);
void nocturneModelCommandBeginReset(void);
void nocturneModelCommandObserveCount(uint32_t count);
#endif
