#ifndef NOCTURNE_SCRIPT_COMPARE_H
#define NOCTURNE_SCRIPT_COMPARE_H
#include <stdint.h>
/* Original EE C.EQ.S/C.LT.S/C.LE.S instruction boundary, predicates0/1/2.
 * A target implementation executes COP1 and updates FCSR condition bit23.
 * Host provider uses published PS2 comparisons; other FCSR effects excluded. */
uint32_t EE_FPU_COMPARE_S(uint32_t left,uint32_t right,unsigned predicate);
#endif
