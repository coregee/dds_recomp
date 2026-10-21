#ifndef NOCTURNE_IOP_EVENT_HEAP_H
#define NOCTURNE_IOP_EVENT_HEAP_H
#include "iop_libsd.h"
/* Original guest layouts;addresses remain32-bit guest words. */
typedef struct {uint32_t next,prev;uint16_t tag,id;uint32_t attr,waiter_count,wait_next,wait_prev,option,bits,initial_bits;} NocturneIopEventFlag;
typedef struct {uint32_t validation_key,bytes,used_blocks,fragment_previous,fragment_next,fragment_blocks;} NocturneIopHeapChunk;
_Static_assert(sizeof(NocturneIopEventFlag)==40,"Original event object");
_Static_assert(offsetof(NocturneIopEventFlag,bits)==32,"Original bits");
_Static_assert(offsetof(NocturneIopEventFlag,wait_next)==20,"Original wait-list head");
_Static_assert(sizeof(NocturneIopHeapChunk)==24,"Original chunk prefix");
uint32_t nocturneIopEventHeapResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopLibSd *);
uint32_t nocturneIopEventHeapRoute(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopLibSd *);
#endif
