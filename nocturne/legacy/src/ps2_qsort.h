#ifndef NOCTURNE_PS2_QSORT_H
#define NOCTURNE_PS2_QSORT_H
#include <stdint.h>
void ps2Qsort_002D4860(uint64_t base,uint64_t count,uint64_t size,uint64_t callback);
void *nocturneResolveQsortAddress(uint32_t address);
/* Passive observation after the genuine comparison. Supplies no game value. */
void nocturneQsortNoteCompare(uint32_t pc,uint64_t callback,uint64_t left,uint64_t right,uint64_t result);
#endif
