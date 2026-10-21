#ifndef NOCTURNE_BATTLE_TIMER3_CLOCK_H
#define NOCTURNE_BATTLE_TIMER3_CLOCK_H
#include <stdint.h>
/* Explicit external-HBLNK, no-gate, no-zero-return Timer3 profile.
 * Caller owns edge timing. This device never changes a CPU, callback or thread.
 * target_future retains the pending-target state across MODE writes; COMP
 * reads expose only16 bits. One object owns timer and INTC state. */
typedef struct NocturneTimer3Clock {
 uint32_t count,mode,comp,target_future,intc_stat,intc_mask;
 uint64_t edges,compare_requests,overflow_requests;
} NocturneTimer3Clock;
#ifdef __cplusplus
extern "C" {
#endif
int nocturneTimer3ClockValid(const NocturneTimer3Clock *);
int nocturneTimer3ClockRead(const NocturneTimer3Clock *,uint32_t physical,uint32_t *);
int nocturneTimer3ClockWrite(NocturneTimer3Clock *,uint32_t physical,uint32_t value);
int nocturneTimer3ClockHblank(NocturneTimer3Clock *);
int nocturneTimer3ClockIntcEligible(const NocturneTimer3Clock *,uint32_t status);
#ifdef __cplusplus
}
#endif
#endif
