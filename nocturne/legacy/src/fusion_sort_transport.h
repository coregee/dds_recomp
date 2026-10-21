#ifndef NOCTURNE_FUSION_SORT_TRANSPORT_H
#define NOCTURNE_FUSION_SORT_TRANSPORT_H
#include <stdint.h>
#define NOCTURNE_FUSION_SORT_TRACE_CAPACITY 131072u
#define NOCTURNE_FUSION_SORT_TRACE_WORDS 5u
extern uint64_t g_fusionSortTraceWords[NOCTURNE_FUSION_SORT_TRACE_CAPACITY * NOCTURNE_FUSION_SORT_TRACE_WORDS];
extern uint32_t g_fusionSortTraceCount;
extern uint32_t g_fusionSortScratchSP;
extern uint32_t g_fusionSortScratchDepth;
extern uint64_t g_fusionSortResult;
extern uint32_t g_fusionSortTrapCode;
extern uint32_t g_fusionSortCompleted;
void nocturneFusionSortTelemetryReset(uint32_t initial_sp);
void nocturneFusionSortSetScratchSP(uint32_t sp);
uint32_t nocturneFusionSortScratchPush(uint32_t bytes);
void nocturneFusionSortScratchPop(uint32_t address,uint32_t bytes);
uint32_t nocturneFusionSortGetScratchSP(void);
uint32_t nocturneFusionSortGetScratchDepth(void);
uint32_t nocturneFusionSortGetTraceCount(void);
uint32_t nocturneFusionSortGetTrace(uint32_t index,uint64_t output[5]);
void nocturneQsortNoteCompare(uint32_t pc,uint64_t callback,uint64_t left,uint64_t right,uint64_t result);
uint32_t nocturneFusionSortObserveCall(void (*function)(void),uint32_t argc,const uint64_t *arguments,uint32_t return_width);
_Noreturn void nocturneFusionSortArithmeticTrap(uint32_t code);
#endif
