#ifndef NOCTURNE_IOP_THREAD_LIFECYCLE_H
#define NOCTURNE_IOP_THREAD_LIFECYCLE_H
#include "iop_libsd_dma_callback.h"
typedef struct {uint32_t attr,option,entry,stack_size,priority;} NocturneIopThreadDescriptor;
typedef struct {
 uint32_t next,prev;uint16_t tag,id;uint8_t status,unknown0d;int16_t priority;
 uint32_t saved_frame,unknown14,unknown18;uint16_t wait_type,wakeup_count;
 uint32_t wait_object,all_thread_next,event_bits;uint16_t event_mode,initial_priority;
 uint32_t run_clock_hi,run_clock_lo,entry,stack,stack_size,gp,attr,option;
 uint32_t unknown50,reason_counter,irq_preemption_count,thread_preemption_count,release_count;
} NocturneIopCreatedThread;
_Static_assert(sizeof(NocturneIopThreadDescriptor)==20,"Original public descriptor");
_Static_assert(sizeof(NocturneIopCreatedThread)==100,"Original allocated TCB");
_Static_assert(offsetof(NocturneIopCreatedThread,all_thread_next)==36,"Original all-thread chain");
_Static_assert(offsetof(NocturneIopCreatedThread,stack_size)==64,"Original stack size");
uint32_t nocturneIopThreadLifecycleResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopLibSdEffect *);
uint32_t nocturneIopThreadLifecycleRoute(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopLibSdEffect *);
#endif
