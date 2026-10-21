#ifndef NOCTURNE_FUSION_SORT_H
#define NOCTURNE_FUSION_SORT_H
#include <stdint.h>

void *nocturneResolveFusionSortAddress(uint32_t address);
/* Provider-owned guest allocation: request96 reserves the native112B frame.
 * No RAM initialization; all96 input bytes (including padding) remain dirty.
 * Pop must validate the same address/size and strict LIFO ordering. */
uint32_t nocturneFusionSortScratchPush(uint32_t bytes);
void nocturneFusionSortScratchPop(uint32_t address,uint32_t bytes);

void ps2FusionSortPack_00213280(uint64_t unit,uint64_t output);
void ps2FusionSortUnpack_002132C0(uint64_t unit,uint64_t input);
void ps2FusionSortSkills_00213350(uint64_t unit);
void ps2FusionSortDescriptors_002133A0(uint64_t output,uint64_t count);
/* Complete auxiliary native leaves; no recognized identity credit. */
uint64_t ps2FusionSortCompareSkill_002131E0(uint64_t left,uint64_t right);
uint64_t ps2FusionSortCompareDescriptor_00213230(uint64_t left,uint64_t right);
#endif
