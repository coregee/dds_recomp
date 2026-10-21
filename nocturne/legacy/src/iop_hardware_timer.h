#ifndef NOCTURNE_IOP_HARDWARE_TIMER_H
#define NOCTURNE_IOP_HARDWARE_TIMER_H
#include "iop_thread_lifecycle.h"
typedef struct {
 uint32_t hardware_base;int8_t source_mask,width;int16_t max_prescale;
 int8_t irq;uint8_t allocated,irq_registered,reserved0b;
 uint32_t current_mode,desired_mode;uint16_t compare_mode,overflow_mode;
 uint32_t target,callback,argument,unknown24,unknown28;
} NocturneIopHardwareTimerRecord;
_Static_assert(sizeof(NocturneIopHardwareTimerRecord)==44,"Original timer record");
_Static_assert(offsetof(NocturneIopHardwareTimerRecord,current_mode)==12,"Original mode guard");
_Static_assert(offsetof(NocturneIopHardwareTimerRecord,callback)==28,"Original callback");
/* Value-only mode writes. Counter motion, pending bits and interrupt delivery
 * remain explicit peripheral inputs; no timer is advanced by this device. */
typedef struct {
 NocturneIopLibSdEffect prior;
 uint32_t timer_mode[6],timer_event_count,timer_events[16][4];
} NocturneIopHardwareTimer;
uint32_t nocturneIopHardwareTimerIo(NocturneIopHardwareTimer *,uint32_t,uint32_t,uint32_t,uint32_t *);
uint32_t nocturneIopHardwareTimerResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopHardwareTimer *);
uint32_t nocturneIopHardwareTimerRoute(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopHardwareTimer *);
#endif
