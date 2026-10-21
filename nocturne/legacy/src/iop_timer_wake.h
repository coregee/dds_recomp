#ifndef NOCTURNE_IOP_TIMER_WAKE_H
#define NOCTURNE_IOP_TIMER_WAKE_H
#include "iop_component_sound.h"
/* Mode reads are finite, ordered external peripheral inputs. In particular,
 * writing mode zero does not explain asynchronously raised counter flags.
 * No counter motion, elapsed time, IRQ delivery or callback result is inferred.
 * Native stores own mode/compare values and the full access log. */
typedef struct {
 NocturneIopHardwareTimer prior;
 uint32_t timer_compare[6];
 uint32_t read_count,read_index,read_profile[16][3];
 uint32_t timer_access_count,timer_accesses[64][4];
} NocturneIopTimerWake;
uint32_t nocturneIopTimerWakeIo(NocturneIopTimerWake *,uint32_t,uint32_t,uint32_t,uint32_t *);
uint32_t nocturneIopTimerWakeResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopTimerWake *);
uint32_t nocturneIopTimerWakeRoute(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopTimerWake *);
#endif
