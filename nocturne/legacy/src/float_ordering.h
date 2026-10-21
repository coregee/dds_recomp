#pragma once
#include <stdint.h>
uint64_t ps2OrderingRotatePositive(uint64_t child,uint64_t parent);
uint64_t ps2OrderingRotateNegative(uint64_t child,uint64_t parent);
void ps2OrderingRebalanceInsertion(uint64_t ancestors,uint64_t count,uint64_t child,uint64_t rootSlot);
void ps2OrderingInsertFloatKey(uint64_t rootSlot,uint64_t tag);
void ps2OrderingSubmit(uint64_t surface,uint64_t tag);
void ps2OrderingApplyMode(uint64_t surface,uint64_t mode,uint64_t tag);
void ps2OrderingCollectList(uint64_t head,uint64_t firstSlot,uint64_t lastSlot);
void ps2OrderingCollectTree(uint64_t root,uint64_t firstSlot,uint64_t lastSlot);
void ps2OrderingBuildChain(uint64_t surface);
void *nocturneResolveFloatOrderingAddress(uint32_t address);
uint32_t nocturneFloatOrderingFrameAddress(void);
