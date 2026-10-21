#ifndef NOCTURNE_IOP_HEAP_SERVICE_NATIVE_H
#define NOCTURNE_IOP_HEAP_SERVICE_NATIVE_H
#include "iop_sysmem_native.h"
/* Source-bound loaded-module profile, not general IOP firmware emulation.
 * Real FILEIO dispatch + allocator + INTRMANI read-to-clear ICTRL functions.
 * Caller supplies initialized RAM and ICTRL. This value-only bus profile has
 * no pending IRQ delivery or clock owner; it never creates an interrupt/reply.
 * Import jumps are the observed loader bindings, validated against original
 * module exports. Unowned file/stdio/SIFCMD/scheduler code transfers normally. */
typedef struct {uint32_t ictrl,reads,writes;} NocturneIopHeapDevice;
uint32_t nocturneIopHeapServiceResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopHeapDevice *);
#endif
